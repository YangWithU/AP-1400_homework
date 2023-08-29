#include "mocha.h"

#include "cappuccino.h"

Mocha::Mocha() : EspressoBased("Mocha") {
    this->ingredients.push_back(new Espresso{2});
    this->ingredients.push_back(new Milk{2});
    this->ingredients.push_back(new MilkFoam{1});
    this->ingredients.push_back(new Chocolate{1});
}

Mocha::Mocha(const Mocha &cap) : EspressoBased(cap) {
    for(auto &x : cap.side_items) {
        this->side_items.push_back(x->get_pIng());
    }
    this->name = cap.name;
}

Mocha::~Mocha() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

Mocha& Mocha::operator=(const Mocha& cap) {
    if(&cap != this) {
        for(auto &x : side_items) delete x;
        for(auto &x : ingredients) delete x;
        side_items.clear();
        ingredients.clear();
        this->name = cap.name;
        for(auto &x : cap.side_items) {
            this->side_items.push_back(x->get_pIng());
        }
        for(auto &x : cap.ingredients) {
            this->ingredients.push_back(x->get_pIng());
        }
    }
    return *this;
}

std::string Mocha::get_name() {
    return this->name;
}

void Mocha::add_side_item(Ingredient* side) {
    this->side_items.push_back(side);
}

double Mocha::price() {
    double res = 0;
    for(auto &x : ingredients) {
        res += x->price();
    }
    for(auto &x : side_items) {
        res += x->price();
    }
    return res;
}

std::vector<Ingredient *> &Mocha::get_side_items() {
    return this->side_items;
}

void Mocha::brew() {
    std::cout << "brewing Mocha:" << std::endl;
    for(auto &x : ingredients) {
        std::cout << x << " ";
    }
    std::cout << "Mocha Done!" << std::endl;
}