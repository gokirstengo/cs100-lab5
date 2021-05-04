#ifndef __PRINT_TEST_HPP__
#define __PRINT_TEST_HPP__

#include "gtest/gtest.h"
#include "spreadsheet.hpp"
#include "select_contains.hpp"
#include "select_not.hpp"
#include "select_and.hpp"
#include "select_or.hpp"
#include <sstream>

using namespace std;

TEST(PrintTest, NotTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.set_selection(
        new Select_Not(new Select_Contains(&sheet, "Species", "Dog")));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "");
}

TEST(PrintTest, AndTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.add_row({"Casper","Cat"});
    sheet.add_row({"Lucky","Cat"});
    sheet.set_selection(
        new Select_And(new Select_Contains(&sheet, "Species", "Dog"), new Select_Contains(&sheet, "Name", "Hershey")));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "Hershey Dog\n");
}

TEST(PrintTest, AndNotTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.add_row({"Casper","Cat"});
    sheet.add_row({"Lucky","Cat"});
    sheet.set_selection(
        new Select_And(new Select_Contains(&sheet, "Species", "Dog"), new Select_Not(new Select_Contains(&sheet, "Name", "Hershey"))));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "Cocoa Dog\n");
}

TEST(PrintTest, OrNotTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.add_row({"Casper","Cat"});
    sheet.add_row({"Lucky","Cat"});
    sheet.set_selection(
        new Select_Or(new Select_Not(new Select_Contains(&sheet, "Species", "Cat")), new Select_Contains(&sheet, "Name", "Cocoa")));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "Hershey Dog\nCocoa Dog\n");
}

TEST(PrintTest, OrTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.add_row({"Casper","Cat"});
    sheet.add_row({"Lucky","Cat"});
    sheet.set_selection(
        new Select_Or(new Select_Contains(&sheet, "Species", "Cat"), new Select_Contains(&sheet, "Name", "Ca")));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "Casper Cat\nLucky Cat\n");
}

TEST(PrintTest, AndOrTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.set_selection(
        new Select_And(new Select_Contains(&sheet, "Species", "Dog"), new Select_Or(new Select_Contains(&sheet, "Name", "Hershey"), new Select_Contains(&sheet, "Name", "Cocoa"))));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "Hershey Dog\nCocoa Dog\n");
}

TEST(PrintTest, NotAndOrTest) {
    Spreadsheet sheet;
    ostringstream os;
    sheet.set_column_names({"Name","Species"});
    sheet.add_row({"Hershey","Dog"});
    sheet.add_row({"Cocoa","Dog"});
    sheet.set_selection(
        new Select_Not(new Select_And(new Select_Contains(&sheet, "Species", "Dog"), new Select_Or(new Select_Contains(&sheet, "Name", "Hershey"), new Select_Contains(&sheet, "Name", "Cocoa")))));
    
    sheet.print_selection(os);

    EXPECT_EQ(os.str(), "");
}



#endif //__PRINT_TEST_HPP__
