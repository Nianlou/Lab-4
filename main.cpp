#include "dialog.h"

int (*fptr[])(Goods::Table*) =
{
	nullptr,
	Goods::d_addElement,		// ���������� ������ (��� ������, ��� � ��������� ������ ��� ����)
	Goods::d_findElement,		// ���������� �������� (�� �����)
	Goods::d_deleteElement,	// ������� ������� (�� �����)
	Goods::d_show,				// ������� ���������� �������
	Goods::d_sell,				// ������� ������ (�� �����)
	Goods::d_change,			// �������� ���������/���/�������� ��������
	Goods::d_swap,				// ����������� � �������
};

int main() 
{
	int rc;
	std::ifstream goodsTable("table.txt");
	Goods::Table table(goodsTable);
	Goods::Table* tab = &table;
	std::cout << "Start";
	while ((rc = Goods::dialog(Goods::msgs))) 
	{
		if (!fptr[rc](tab))
			break;
		std::cout << std::endl;
	}
	// ������ ������� � ����
	goodsTable.close();
	std::ofstream ofs("table.txt", std::ofstream::out | std::ofstream::trunc);
	tab->print(ofs);
	ofs.close();
	return 0;
}