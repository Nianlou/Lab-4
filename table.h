#ifndef _TABLE_H_
#define _TABLE_H_

#include "item.h"
#include <iostream>

namespace Goods {
	class Table {
	private:
		std::vector<std::pair<int, Item*>> array;	// Элемент таблицы содержит пару (шифр товара и указатель на его описатель)
	public:
		Table(std::ifstream& table);	// Создание таблицы по файлу	

		std::vector<std::pair<int, Item*>>& getArray() { return array; } // Возвращает ссылку на массив

		std::ostream& print(std::ostream& c) const;	// Вывод таблицы
		int find(int code);
		int deleteElement(int code);
	};
}
#endif