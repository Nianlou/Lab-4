#include "dialog.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Goods 
{
	int dialog(const std::vector<std::string> msgs) 
	{
		std::cout << std::endl;
		std::string errmsgs = "";
		int rc, i;
		do 
		{
			std::cout << errmsgs;
			errmsgs = "Error. Please, try again";
			for (i = 0; i < msgs.size(); ++i)	// Вывод списка альтернатив
				std::cout << msgs[i] << std::endl;
			std::cout << "-----> ";
			std::cin >> rc;
		} while (rc < 0 || rc >= msgs.size());
		return rc;
	}

	int d_addElement(Table* table) 
	{
		int yes, money, num, qd, code;
		std::string type, firmName, countryName;

		std::cout << "Enter the cipher --> ";
		std::cin >> code;
		for (auto& var : table->getArray()) 
		{
			if (var.first == code) 
			{	// Значит элемент с таким шифром есть и надо просто добавить еще
				if (dynamic_cast<Wholesale*>(var.second)) 
				{	// Значит товар оптовый
					std::cout << "\nEnter pure of paties --> "; //число партий
					std::cin >> num;
					auto opt = dynamic_cast<Wholesale*>(var.second);
					opt->setNum(opt->getNum() + num);
				}
				else 
				{	// Значит товар розничный
					std::cout << "\nEnter quantity of goods --> ";
					std::cin >> num;
					auto opt = dynamic_cast<Retail*>(var.second);
					opt->setNum(opt->getNum() + num);

				}
				return 1;
			}
		}
		// Значит элемента с таким шифром нет, добавляем новый
		std::cout << "\nIs this product wholesale (1 - yes, 0 - not) --> ";
		std::cin >> yes;

		std::cout << "\nEnter product type --> ";
		std::cin >> type;
		std::cout << "\nEnter firm --> ";
		std::cin >> firmName;
		std::cout << "\nEnter country --> ";
		std::cin >> countryName;
		std::cout << "\nEnter cost --> ";
		std::cin >> money;

		if (yes) 
		{
			std::cout << "\nEnter pure of wholesale paties --> ";
			std::cin >> num;
			std::cout << "\nEnter numbers of items in a batch --> ";
			std::cin >> qd;
			Wholesale* it = new Wholesale(type, firmName, countryName, money, num, qd);
			table->getArray().push_back(std::make_pair(code, it));
		}
		else 
		{
			std::cout << "\nEnter number of items --> ";
			std::cin >> num;
			std::cout << "\nEnter allowance --> ";		//надбавка
			std::cin >> qd;
			Retail* it = new Retail(type, firmName, countryName, money, num, qd);
			table->getArray().push_back(std::make_pair(code, it));
		}
		std::sort(table->getArray().begin(), table->getArray().end(),
			[](std::pair<int, Item*> a, std::pair<int, Item*> b) -> bool { return a.first < b.first; });	// Сортируем массив по возрастснию шифра
		return 1;
	}

	int d_findElement(Table* table) 
	{
		int code;
		std::cout << "Enter cipher --> ";
		std::cin >> code;
		table->find(code);
		return 1;
	}

	int d_deleteElement(Table* table) 
	{
		int code;
		std::cout << "Enter cipher --> ";
		std::cin >> code;
		table->deleteElement(code);
		return 1;
	}

	int d_show(Table* table) 
	{
		table->print(std::cout);
		return 1;
	}

	int d_sell(Table* table) 
	{
		int code, num;
		std::cout << "Enter cipher --> ";
		std::cin >> code;
		for (int i = 0; i < table->getArray().size(); ++i) 
		{
			if (table->getArray()[i].first == code) 
			{	// Значит элемент с таким шифром есть
				if (dynamic_cast<Wholesale*>(table->getArray()[i].second)) 
				{
					auto v = dynamic_cast<Wholesale*>(table->getArray()[i].second);
					std::cout << "\nEnter amount of batches you want to sale --> ";
					std::cin >> num;
					int n = v->getNum();
					if (num > v->getNum())
						std::cout << "\nWe don't have this much. You can get only (" << v->getNum() << ") batches;";
					std::cout << "\nYou earned " << fmin(num, v->getNum()) * v->getQuantity() * v->getMoney() << "$";
					if (num >= n)
						table->getArray().erase(table->getArray().begin() + i);
					else 
					{
						v->setNum(n - num);
					}
				}
				else 
				{
					auto v = dynamic_cast<Retail*>(table->getArray()[i].second);
					std::cout << "\nEnter amount of items you want to sale --> ";
					std::cin >> num;
					int n = v->getNum();
					if (num > n)
						std::cout << "\nWe don't have this much. You can get only (" << v->getNum() << ") items;";
					std::cout << "\nYou earned " << fmin(num, v->getNum()) * (v->getBonus() * 0.01 + 1) * v->getMoney() << "$";
					if (num >= n)
						table->getArray().erase(table->getArray().begin() + i);
					else 
					{
						v->setNum(n - num);
					}
				}
				return 1;
			}
		}
		std::cout << "\nWe don't have such product";
		return 1;
	}

	int d_change(Table* table) 
	{
		int code, n;
		std::cout << "Enter cipher of item you want to change --> ";
		std::cin >> code;

		for (auto& var : table->getArray()) 
		{
			if (var.first == code) 
			{	// Значит элемент с таким шифром есть
				auto v = var.second;	// Что б писать меньше
				if (dynamic_cast<Wholesale*>(var.second)) 
				{	// Значит оптовый
					auto v = dynamic_cast<Wholesale*>(var.second);
					std::cout << "\nWhat do you want to change? Cost (0) or amount of items in batch (not 0) --> ";
					std::cin >> n;
					if (n) 
					{
						std::cout << "\nEnter amount of items in batch --> ";
						std::cin >> n;
						int k = v->getQuantity();	// Число товаров в партии было
						v->setQuantity(n);			// Число товаров в партии стало
						v->setNum(v->getNum() + ((k - n) * v->getNum()) / n);	// Изменили число партий
					}
					else 
					{
						std::cout << "\nEnter new cost of items in batch --> ";
						std::cin >> n;
						v->setMoney(n);
					}
				}
				else 
				{
					auto v = dynamic_cast<Retail*>(var.second);
					std::cout << "\nWhat do you want to change? Cost (0) or allowence (not 0) --> ";
					std::cin >> n;
					if (n) 
					{
						std::cout << "\nEnter allowence --> ";
						std::cin >> n;
						v->setBonus(n);	// Изменили надбавку
					}
					else 
					{
						std::cout << "\nEnter new cost --> ";
						std::cin >> n;
						v->setMoney(n);
					}
				}

				return 1;
			}
		}

		std::cout << "\nWe don't have such product";
		return 1;
	}

	int d_swap(Table* table) 
	{
		int code, num, rcode, bonus;
		std::cout << "Enter cipher --> ";
		std::cin >> code;
		for (int i = 0; i < table->getArray().size(); ++i) 
		{
			if (table->getArray()[i].first == code)
			{	// Значит элемент с таким шифром есть
				if (dynamic_cast<Wholesale*>(table->getArray()[i].second)) 
				{
					auto v = dynamic_cast<Wholesale*>(table->getArray()[i].second);
					std::cout << "\nEnter amount of batches to move into retail --> ";
					std::cin >> num;
					int n = v->getNum();
					if (num > v->getNum())
						std::cout << "\nWe don't have this much. You can get only (" << v->getNum() << ") batches;";
					// Добавление в розницу
					// Ищем, вдруг такой товар уже и так есть в рознице
					for (auto& var : table->getArray())
						if (var.second->getType() == v->getType() && var.second->getCountryName() == v->getCountryName() && var.second->getFirmName() == v->getFirmName() && dynamic_cast<Retail*>(var.second)) {	// Значит такой же розничный элемент существовал
							auto r = dynamic_cast<Retail*>(var.second);
							r->setNum(r->getNum() + num * v->getQuantity());

							if (num >= n)
								table->getArray().erase(table->getArray().begin() + i);
							else
								v->setNum(n - num);
							return 1;
						}
					// Понимаем, что такого товара в рознице нет, добавляем его
					std::cout << "Enter cipher for retail --> ";
					std::cin >> rcode;
					std::cout << "Enter allowence for retail --> ";
					std::cin >> bonus;
					Retail* it = new Retail(v->getType(), v->getFirmName(), v->getCountryName(), v->getMoney(), num * v->getQuantity(), bonus);


					if (num >= n)
						table->getArray().erase(table->getArray().begin() + i);
					else
						v->setNum(n - num);

					table->getArray().push_back(std::make_pair(rcode, it));	// Добавили новый элемент в массив
					std::sort(table->getArray().begin(), table->getArray().end(),
						[](std::pair<int, Item*> a, std::pair<int, Item*> b) -> bool { return a.first < b.first; });	// Сортируем массив по возрастанию шифра
				}
				else
					std::cout << "\nThis product already in retail";
				return 1;
			}
		}
		std::cout << "\nWe don't have such product";
		return 1;
	}

}
