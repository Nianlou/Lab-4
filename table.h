#ifndef _TABLE_H_
#define _TABLE_H_

#include "item.h"
#include <iostream>

namespace Goods {
	class Table {
	private:
		std::vector<std::pair<int, Item*>> array;	// ������� ������� �������� ���� (���� ������ � ��������� �� ��� ���������)
	public:
		Table(std::ifstream& table);	// �������� ������� �� �����	

		std::vector<std::pair<int, Item*>>& getArray() { return array; } // ���������� ������ �� ������

		std::ostream& print(std::ostream& c) const;	// ����� �������
		int find(int code);
		int deleteElement(int code);
	};
}
#endif