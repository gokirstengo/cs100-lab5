#ifndef __SELECT_CONTAINS_HPP__
#define __SELECT_CONTAINS_HPP__

#include "select.hpp"
#include "spreadsheet.hpp"
#include <string>
using namespace std;


class Select_Contains: public Select_Column
{
    protected:
        string containName;
    public:
        Select_Contains(const Spreadsheet* sheet, const string& columnName, const string& containName) : Select_Column(sheet, columnName)
        {
            this->containName = containName;
        }
        
        virtual bool select(const Spreadsheet* sheet, int row) const
        {
            bool b = false;
            
            if(column != -1)
            {
                b = Select_Column::select(sheet, row);
            }
            
            return b;
        }

        virtual bool select(const std::string& s) const
        {
            bool b = false;
           
            size_t found = s.find(containName);
            
            if(found != string::npos)
            {
                b = true;
            }
            return b;
        }
};

#endif //__SELECT_CONTAINS_HPP__
