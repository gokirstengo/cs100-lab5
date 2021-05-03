#ifndef __SELECT_TEST_HPP__
#define __SELECT_TEST_HPP__

#include "gtest/gtest.h"
#include "spreadsheet.hpp"
#include "select_contains.hpp"
#include "select_not.hpp"
#include "select_and.hpp"
#include "select_or.hpp"
#include "select_mock.hpp"
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

TEST(ContainTest, BlankInRowTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Contains c(&sheet, "Species", "Dog");

    EXPECT_EQ(c.select(&sheet, 0), false);

}

//Select_Not Tests
TEST(NotTest, MockTrueTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue = new Select_Mock_True();
    Select_Not n(mockTrue);
    
    EXPECT_EQ(n.select(&sheet, 0), false);
}

TEST(NotTest, MockFalseTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_False * mockFalse = new Select_Mock_False();
    Select_Not n(mockFalse);
    
    EXPECT_EQ(n.select(&sheet, 0), true);
}

TEST(NotTest, GeneralTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Not n(new Select_Contains(&sheet, "Species", "Dog"));

    EXPECT_EQ(n.select(&sheet, 0), false);
    EXPECT_EQ(n.select(&sheet, 1), false);
    EXPECT_EQ(n.select(&sheet, 2), true);
    EXPECT_EQ(n.select(&sheet, 3), true);
}

TEST(NotTest, CapitalTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","dog","7","Brown"});
    sheet.add_row({"Cocoa","dog","12","Black"});
    Select_Not n(new Select_Contains(&sheet, "Species", "Dog"));

    EXPECT_EQ(n.select(&sheet, 0), true);
    EXPECT_EQ(n.select(&sheet, 1), true);

}

TEST(NotTest, BadCategoryTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Not n(new Select_Contains(&sheet, "Animal", "Horse"));

    EXPECT_EQ(n.select(&sheet, 0), true);
    EXPECT_EQ(n.select(&sheet, 1), true);
    EXPECT_EQ(n.select(&sheet, 2), true);
    EXPECT_EQ(n.select(&sheet, 3), true);
}

TEST(NotTest, ContainsSubstringTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    Select_Not n(new Select_Contains(&sheet, "Species", "og"));

    EXPECT_EQ(n.select(&sheet, 0), false);
    EXPECT_EQ(n.select(&sheet, 1), false);
}

TEST(NotTest, ContainsBlankTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Not n(new Select_Contains(&sheet, "Species", ""));

    EXPECT_EQ(n.select(&sheet, 0), false);
    EXPECT_EQ(n.select(&sheet, 1), false);
    EXPECT_EQ(n.select(&sheet, 2), false);
    EXPECT_EQ(n.select(&sheet, 3), false);
}

TEST(NotTest, BlankInRowTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Not n(new Select_Contains(&sheet, "Species", "Dog"));

    EXPECT_EQ(n.select(&sheet, 0), true);

}

//Select_And Tests
TEST(AndTest, MockTrueTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue1 = new Select_Mock_True();
    Select_Mock_True * mockTrue2 = new Select_Mock_True();
    Select_And a(mockTrue1, mockTrue2);
    
    EXPECT_EQ(a.select(&sheet, 0), true);
}

TEST(AndTest, MockFalseTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_False * mockFalse1 = new Select_Mock_False();
    Select_Mock_False * mockFalse2 = new Select_Mock_False();
    Select_And a(mockFalse1, mockFalse2);
    
    EXPECT_EQ(a.select(&sheet, 0), false);
}

TEST(AndTest, MockTrueFalseTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue = new Select_Mock_True();
    Select_Mock_False * mockFalse = new Select_Mock_False();
    Select_And a(mockTrue, mockFalse);
    
    EXPECT_EQ(a.select(&sheet, 0), false);
}

TEST(AndTest, MockFalseTrueTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue = new Select_Mock_True();
    Select_Mock_False * mockFalse = new Select_Mock_False();
    Select_And a(mockFalse, mockTrue);
    
    EXPECT_EQ(a.select(&sheet, 0), false);
}

TEST(AndTest, GeneralTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_And a(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Color", "Black"));

    EXPECT_EQ(a.select(&sheet, 0), false);
    EXPECT_EQ(a.select(&sheet, 1), true);
    EXPECT_EQ(a.select(&sheet, 2), false);
    EXPECT_EQ(a.select(&sheet, 3), false);
}

TEST(AndTest, CapitalTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","dog","7","Brown"});
    sheet.add_row({"Cocoa","dog","12","Black"});
    Select_And a(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Color", "black"));

    EXPECT_EQ(a.select(&sheet, 0), false);
    EXPECT_EQ(a.select(&sheet, 1), false);

}

TEST(AndTest, BadCategoryTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_And a(new Select_Contains(&sheet, "Animal", "Horse"), new Select_Contains(&sheet, "Color", "Black"));

    EXPECT_EQ(a.select(&sheet, 0), false);
    EXPECT_EQ(a.select(&sheet, 1), false);
    EXPECT_EQ(a.select(&sheet, 2), false);
    EXPECT_EQ(a.select(&sheet, 3), false);
}

TEST(AndTest, ContainsSubstringTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    Select_And a(new Select_Contains(&sheet, "Species", "og"), new Select_Contains(&sheet, "Color", "B"));

    EXPECT_EQ(a.select(&sheet, 0), true);
    EXPECT_EQ(a.select(&sheet, 1), true);
}

TEST(AndTest, ContainsBlankTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_And a(new Select_Contains(&sheet, "Species", ""), new Select_Contains(&sheet, "", "Black"));

    EXPECT_EQ(a.select(&sheet, 0), false);
    EXPECT_EQ(a.select(&sheet, 1), false);
    EXPECT_EQ(a.select(&sheet, 2), false);
    EXPECT_EQ(a.select(&sheet, 3), false);
}

TEST(AndTest, BlankInRowTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_And a(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Color", "Black"));

    EXPECT_EQ(a.select(&sheet, 0), false);
}

//Select_Or Tests
TEST(OrTest, MockTrueTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue1 = new Select_Mock_True();
    Select_Mock_True * mockTrue2 = new Select_Mock_True();
    Select_Or o(mockTrue1, mockTrue2);
    
    EXPECT_EQ(o.select(&sheet, 0), true);
}

TEST(OrTest, MockFalseTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_False * mockFalse1 = new Select_Mock_False();
    Select_Mock_False * mockFalse2 = new Select_Mock_False();
    Select_Or o(mockFalse1, mockFalse2);
    
    EXPECT_EQ(o.select(&sheet, 0), false);
}

TEST(OrTest, MockTrueFalseTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue = new Select_Mock_True();
    Select_Mock_False * mockFalse = new Select_Mock_False();
    Select_Or o(mockTrue, mockFalse);
    
    EXPECT_EQ(o.select(&sheet, 0), true);
}

TEST(OrTest, MockFalseTrueTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Mock_True * mockTrue = new Select_Mock_True();
    Select_Mock_False * mockFalse = new Select_Mock_False();
    Select_Or o(mockFalse, mockTrue);
    
    EXPECT_EQ(o.select(&sheet, 0), true);
}

TEST(OrTest, GeneralTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Or o(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Color", "Black"));

    EXPECT_EQ(o.select(&sheet, 0), true);
    EXPECT_EQ(o.select(&sheet, 1), true);
    EXPECT_EQ(o.select(&sheet, 2), false);
    EXPECT_EQ(o.select(&sheet, 3), false);
}

TEST(OrTest, CapitalTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","dog","7","Brown"});
    sheet.add_row({"Cocoa","dog","12","Black"});
    Select_Or o(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Color", "black"));

    EXPECT_EQ(o.select(&sheet, 0), false);
    EXPECT_EQ(o.select(&sheet, 1), false);

}

TEST(OrTest, BadCategoryTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Or o(new Select_Contains(&sheet, "Animal", "Horse"), new Select_Contains(&sheet, "Color", "Black"));

    EXPECT_EQ(o.select(&sheet, 0), false);
    EXPECT_EQ(o.select(&sheet, 1), true);
    EXPECT_EQ(o.select(&sheet, 2), false);
    EXPECT_EQ(o.select(&sheet, 3), false);
}

TEST(OrTest, ContainsSubstringTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    Select_Or o(new Select_Contains(&sheet, "Species", "og"), new Select_Contains(&sheet, "Color", "B"));

    EXPECT_EQ(o.select(&sheet, 0), true);
    EXPECT_EQ(o.select(&sheet, 1), true);
}

TEST(OrTest, ContainsBlankTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","Dog","7","Brown"});
    sheet.add_row({"Cocoa","Dog","12","Black"});
    sheet.add_row({"Casper","Cat","8","White"});
    sheet.add_row({"Lucky","Cat","2","Gray"});
    Select_Or o(new Select_Contains(&sheet, "Species", ""), new Select_Contains(&sheet, "", "Black"));

    EXPECT_EQ(o.select(&sheet, 0), true);
    EXPECT_EQ(o.select(&sheet, 1), true);
    EXPECT_EQ(o.select(&sheet, 2), true);
    EXPECT_EQ(o.select(&sheet, 3), true);
}

TEST(OrTest, BlankInRowTest) {
    Spreadsheet sheet;
    sheet.set_column_names({"Name","Species","Age","Color"});
    sheet.add_row({"Hershey","","7","Brown"});
    Select_Or o(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Color", "Black"));

    EXPECT_EQ(o.select(&sheet, 0), false);
}
#endif //__SELECT_TEST_HPP__
