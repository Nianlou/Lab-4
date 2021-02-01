#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <iostream>
#include "table.h"

namespace Goods 
{

	/* Массив диагностических сообщений об ошибках */
	const std::vector<std::string> errmsgs =
	{
		"Ok",
		"You don't have enougth products",
		"This cipher doesn't exist"
	};

	/* Альтернативы меню для организации выбора алгоритмов */
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

	int d_addElement(Table* table);		// Добавление товара (как нового, так и отдельных партий или штук) 	
	int d_findElement(Table* table);	// Нахождение элемента (по шифру)									
	int d_deleteElement(Table* table);	// Удалить элемент (по шифру)										
	int d_show(Table* table);			// Вывести содержимое таблицы										
	int d_sell(Table* table);			// Продажа товара (по шифру)														
	int d_change(Table* table);			// Изменить стоимость/опт/торговую надбавку (по шифру)
	int d_swap(Table* table);			// Переместить в розницу											


}

#endif