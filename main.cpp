#include "dialog.h"

int (*fptr[])(Goods::Table*) =
{
	nullptr,
	Goods::d_addElement,		// Добавление товара (как нового, так и отдельных партий или штук)
	Goods::d_findElement,		// Нахождение элемента (по шифру)
	Goods::d_deleteElement,	// Удалить элемент (по шифру)
	Goods::d_show,				// Вывести содержимое таблицы
	Goods::d_sell,				// Продажа товара (по шифру)
	Goods::d_change,			// Изменить стоимость/опт/торговую надбавку
	Goods::d_swap,				// Переместить в розницу
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
	// Запись таблицы в файл
	goodsTable.close();
	std::ofstream ofs("table.txt", std::ofstream::out | std::ofstream::trunc);
	tab->print(ofs);
	ofs.close();
	return 0;
}