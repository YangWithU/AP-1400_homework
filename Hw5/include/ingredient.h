#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>

class Ingredient {
public:
    double get_price_unit() {
        return price_unit;
    }

    size_t get_units() {
        return units;
    }

    virtual std::string get_name() = 0;

    double price() {
        return price_unit * units;
    }

protected:
    Ingredient(double price_unit, size_t units) {
        this->price_unit = price_unit;
        this->units = units;
    }

    double price_unit;
    size_t units; // number of ingredient
    std::string name; // Espresso, Milk, Chocolate...
};

#endif // INGREDIENT_H