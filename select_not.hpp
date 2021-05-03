#ifndef __SELECT_NOT_HPP__
#define __SELECT_NOT_HPP__

#include "select.hpp"
#include "spreadsheet.hpp"
#include <string>
using namespace std;


class Select_Not: public Select
{
    protected:
       const Select * s;
    public:
        Select_Not(const Select* s) : Select()
        {
            this->s = s;
        }
        
        ~Select_Not()
        {
            delete s;
        }
        
        virtual bool select(const Spreadsheet* sheet, int row) const
        {
            bool b = s->select(sheet, row);
            return !b;
        }

};

#endif //__SELECT_NOT_HPP__

