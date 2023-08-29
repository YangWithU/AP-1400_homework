#ifndef MOCHA_H
#define MOCHA_H

#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"

class Mocha : public EspressoBased {
public:
    Mocha();
    Mocha(const Mocha& cap);
    ~Mocha() override;
    Mocha& operator=(const Mocha& cap);

    std::string get_name() override;
    double price() override;
    void brew() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;
};

#endif // MOCHA_H