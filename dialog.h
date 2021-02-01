#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <iostream>
#include "table.h"

namespace Goods 
{

	/* ������ ��������������� ��������� �� ������� */
	const std::vector<std::string> errmsgs =
	{
		"Ok",
		"You don't have enougth products",
		"This cipher doesn't exist"
	};

	/* ������������ ���� ��� ����������� ������ ���������� */
	const std::vector<std::string> msgs =
	{
		"0. Save & quit",
		"1. Add product",
		"2. Find product",
		"3. Delete product",
		"4. Show table",
		"5. Sell product",
		"6. Change cost / wholesale / allowance",
		"7. Move product to retail"
	};

	int dialog(const std::vector<std::string> msgs);

	int d_addElement(Table* table);		// ���������� ������ (��� ������, ��� � ��������� ������ ��� ����) 	
	int d_findElement(Table* table);	// ���������� �������� (�� �����)									
	int d_deleteElement(Table* table);	// ������� ������� (�� �����)										
	int d_show(Table* table);			// ������� ���������� �������										
	int d_sell(Table* table);			// ������� ������ (�� �����)														
	int d_change(Table* table);			// �������� ���������/���/�������� �������� (�� �����)
	int d_swap(Table* table);			// ����������� � �������											


}

#endif