#include "pch.h"
#include "gtest/gtest.h"
#include "dialog.h"

TEST(TableConstructor, Constructor) {
	std::ifstream goodsTable("else.txt");
	Goods::Table table(goodsTable);
	Goods::Table* tab = &table;

	ASSERT_EQ(160, tab->getArray()[2].second->getMoney());
	ASSERT_EQ(148888, tab->getArray()[0].first);
	ASSERT_EQ("Banana", tab->getArray()[3].second->getType());
	ASSERT_EQ("Hakunamatata", tab->getArray()[3].second->getFirmName());
	ASSERT_EQ("Turkey", tab->getArray()[4].second->getCountryName());

}

TEST(TableFunctions, Functions) {
	std::ifstream goodsTable("else.txt");
	Goods::Table table(goodsTable);
	Goods::Table* tab = &table;

	ASSERT_EQ(1, tab->find(148888));
	tab->deleteElement(148888);
	ASSERT_EQ(4, tab->getArray().size());
	tab->deleteElement(617041);
	ASSERT_EQ(3, tab->getArray().size());
	ASSERT_EQ(1, tab->find(228228));
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}