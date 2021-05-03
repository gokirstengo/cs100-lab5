#ifndef __SELECT_TEST_HPP__
#define __SELECT_TEST_HPP__

#include "gtest/gtest.h"
#include "spreadsheet.hpp"
#include "select_contains.hpp"
using namespace std;

//Select_Contains Tests
TEST(ContainTest, GeneralTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Contains c(&sheet, "Species", "Dog");

    EXPECT_EQ(c.select(&sheet, 0), true);
    EXPECT_EQ(c.select(&sheet, 1), true);
    EXPECT_EQ(c.select(&sheet, 2), false);
    EXPECT_EQ(c.select(&sheet, 3), false);
}

TEST(ContainTest, CapitalTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","dog","7","Brown"});
    sheet.add_row({"Cocoa","dog","12","Black"});
    Select_Contains c(&sheet, "Species", "Dog");

    EXPECT_EQ(c.select(&sheet, 0), false);
    EXPECT_EQ(c.select(&sheet, 1), false);

}

TEST(ContainTest, BadCategoryTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Contains c(&sheet, "Animal", "Horse");

    EXPECT_EQ(c.select(&sheet, 0), false);
    EXPECT_EQ(c.select(&sheet, 1), false);
    EXPECT_EQ(c.select(&sheet, 2), false);
    EXPECT_EQ(c.select(&sheet, 3), false);
}

TEST(ContainTest, ContainsSubstringTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    Select_Contains c(&sheet, "Species", "og");

    EXPECT_EQ(c.select(&sheet, 0), true);
    EXPECT_EQ(c.select(&sheet, 1), true);
}

TEST(ContainTest, ContainsBlankTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Contains c(&sheet, "Species", "");

    EXPECT_EQ(c.select(&sheet, 0), true);
    EXPECT_EQ(c.select(&sheet, 1), true);
    EXPECT_EQ(c.select(&sheet, 2), true);
    EXPECT_EQ(c.select(&sheet, 3), true);
}


#endif //__SELECT_TEST_HPP__

