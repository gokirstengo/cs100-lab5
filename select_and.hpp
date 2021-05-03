#ifndef __SELECT_AND_HPP__
#define __SELECT_AND_HPP__

#include "select.hpp"
#include "spreadsheet.hpp"
#include <string>
using namespace std;

class Select_And : public Select{
    protected:
        const Select* left;
        const Select* right;

    public:
        /* Constructors */
        Select_And(const Select* left, const Select* right) : Select() {
            this->left = left;
            this->right = right;
        }

        ~Select_And() {
            delete left;
            delete right;
        }

        /* Pure Virtual Functions */
        virtual bool select(const Spreadsheet* sheet, int row) const {
            bool b1 = false;
            bool b2 = false;

            b1 = left->select(sheet, row);
            b2 = right->select(sheet, row);

            if (b1 && b2) {
                return true;
            }
            else {
                return false;
            }
        }
};

#endif //__SELECT_AND_HPP__
