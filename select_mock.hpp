#ifndef __SELECT_MOCK_HPP__
#define __SELECT_MOCK_HPP__

#include "select.hpp"
#include "spreadsheet.hpp"
using namespace std;


class Select_Mock_True: public Select
{
    public:
        Select_Mock_True() : Select() {}
        
        virtual bool select(const Spreadsheet* sheet, int row) const
        {
            bool b = true;
            return b;
        }

};

class Select_Mock_False: public Select
{
    public:
        Select_Mock_False() : Select() {}
        
        virtual bool select(const Spreadsheet* sheet, int row) const
        {
            bool b = false;
            return b;
        }

};

#endif //__SELECT_MOCK_HPP__
