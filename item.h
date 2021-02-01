#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>	//  ��� setw

namespace Goods 
{
	// ������� ����� ��� ����� �������
	class Item 
	{
	protected:
		std::string type, firmName, countryName;	// ��� ������, ��� �����, ��� ������-�����������
		int money;	// ��������� ������� ������
	public:
		Item() {}
		Item(std::string tp, std::string fName, std::string cName, int mon) :
			type(tp), firmName(fName), countryName(cName), money(mon) {}

		virtual ~Item() {}	// dinamic_cast

		// Getters
		std::string getType() const { return type; }
		std::string getFirmName() const { return firmName; }
		std::string getCountryName() const { return countryName; }
		int getMoney() const { return money; }

		Item& setMoney(int a) { money = a; return *this; }
	};

	// ����� ������� �������
	class Wholesale : public Item 
	{
	private:
		int num;			// ���������� ������� ������
		int quantity;		// ����� ������ ������ � ������ (������ ����)
	public:
		Wholesale() {}
		Wholesale(std::string type, std::string firmName, std::string countryName, int money, int nm, int qb) :
			num(nm), quantity(qb), Item(type, firmName, countryName, money) {}

		// Getters
		int getNum() const { return num; }
		int getQuantity() const { return quantity; }

		Wholesale& setNum(int k) { num = k; return *this; }
		Wholesale& setQuantity(int k) { quantity = k; return *this; }
	};

	// ����� ��������� �������
	class Retail : public Item 
	{
	private:
		int num;	// ���������� ������ ������
		int bonus;	// �������� (� ���������)
	public:
		Retail() {}
		Retail(std::string type, std::string firmName, std::string countryName, int money, int nm, int qb) :
			num(nm), bonus(qb), Item(type, firmName, countryName, money) {}

		// Getters
		int getNum() const { return num; }
		int getBonus() const { return bonus; }

		Retail& setNum(int k) { num = k; return *this; }
		Retail& setBonus(int k) { bonus = k; return *this; }
	};
}
#endif
