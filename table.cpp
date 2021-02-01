#include "table.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Goods {
	Table::Table(std::ifstream& table) 
	{
		std::string type, firmName, countryName, a;
		int code, money, num, qb;
		while (!table.eof()) 
		{
			table >> a >> code >> type >> firmName >> countryName >> money >> num >> qb;
			if (a == "�������:") 
			{
				Wholesale* it = new Wholesale(type, firmName, countryName, money, num, qb);
				array.push_back(std::make_pair(code, it));
			}
			else 
			{
				Retail* it = new Retail(type, firmName, countryName, money, num, qb);
				array.push_back(std::make_pair(code, it));
			}
			getline(table, a, '\n');
		}
		std::sort(array.begin(), array.end(),
			[](std::pair<int, Item*> a, std::pair<int, Item*> b) -> bool { return a.first < b.first; });	// ��������� ������ �� ����������� �����
	}

	std::ostream& Table::print(std::ostream& c) const 
	{
		for (int i = 0; i < array.size(); ++i) 
		{
			auto v = array[i].second;	// ��� � ������ ������
			if (dynamic_cast<Wholesale*>(v))
				c << std::setw(17) << "Wholesale:";
			else
				c << std::setw(15) << "Retail:";

			c << std::setw(15) << array[i].first << std::setw(15) << v->getType() << std::setw(15) << v->getFirmName() << std::setw(15) << v->getCountryName() << std::setw(15) << v->getMoney();

			if (dynamic_cast<Wholesale*>(v))
				c << std::setw(15) << dynamic_cast<Wholesale*>(v)->getNum() << std::setw(15) << dynamic_cast<Wholesale*>(v)->getQuantity();
			else
				c << std::setw(15) << dynamic_cast<Retail*>(v)->getNum() << std::setw(15) << dynamic_cast<Retail*>(v)->getBonus();

			if (i + 1 < array.size())
				c << std::endl;
		}
		return c;
	}

	int Table::find(int code) 
	{
		for (auto& var : array) 
		{
			if (var.first == code) 
			{	// ������ ������� � ����� ������ ����
				auto v = var.second;	// ��� � ������ ������
				if (dynamic_cast<Wholesale*>(v))
					std::cout << std::setw(17) << "�������:";
				else
					std::cout << std::setw(15) << "���������:";

				std::cout << std::setw(15) << var.first << std::setw(15) << v->getType() << std::setw(15) << v->getFirmName() << std::setw(15) << v->getCountryName() << std::setw(15) << v->getMoney();

				if (dynamic_cast<Wholesale*>(v))
					std::cout << std::setw(15) << dynamic_cast<Wholesale*>(v)->getNum() << std::setw(15) << dynamic_cast<Wholesale*>(v)->getQuantity();
				else
					std::cout << std::setw(15) << dynamic_cast<Retail*>(v)->getNum() << std::setw(15) << dynamic_cast<Retail*>(v)->getBonus();
				return 1;
			}
		}
		std::cout << "\n������ ������ � ��� ���";
		return 1;
	}

	int Table::deleteElement(int code) 
	{
		for (int i = 0; i < array.size(); ++i) 
		{
			if (array[i].first == code) 
			{	// ������ ������� � ����� ������ ����
				array.erase(array.begin() + i);
				std::cout << "\n����� � ������ " << code << " ������." << std::endl;
				return 1;
			}
		}
		std::cout << "\n������ ������ � ��� ���";
		return 1;
	}
}