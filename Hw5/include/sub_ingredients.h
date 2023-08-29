#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(cname, pval)                       \
class cname : public Ingredient {                   \
public:                                             \
    cname(size_t units) : Ingredient{pval, units}   \
    {                                               \
        this->name = #cname;                        \
    }                                               \
                                                    \
    virtual std::string get_name() override {return this->name;} \
    virtual Ingredient* get_pIng() override {return new cname(*this);} \
}; \

DEFCLASS(Cinnamon, 5)
DEFCLASS(Chocolate, 5)
DEFCLASS(Sugar, 1)
DEFCLASS(Cookie, 10)
DEFCLASS(Espresso, 15)
DEFCLASS(Milk, 10)
DEFCLASS(MilkFoam, 5)
DEFCLASS(Water, 1)

#endif // SUB_INGREDIENTS_H