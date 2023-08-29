#include "cappuccino.h"

Cappuccino::Cappuccino() : EspressoBased("Cappuccino") {
    this->ingredients.push_back(new Espresso{2});
    this->ingredients.push_back(new Milk{2});
    this->ingredients.push_back(new MilkFoam{1});
}

Cappuccino::Cappuccino(const Cappuccino &cap) : EspressoBased(cap) {
    for(auto &x : cap.side_items) {
        this->side_items.push_back(x->get_pIng());
    }
    this->name = cap.name;
}

Cappuccino::~Cappuccino() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

Cappuccino& Cappuccino::operator=(const Cappuccino& cap) {
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

std::string Cappuccino::get_name() {
    return this->name;
}

void Cappuccino::add_side_item(Ingredient* side) {
    this->side_items.push_back(side);
}

double Cappuccino::price() {
    double res = 0;
    for(auto &x : ingredients) {
        res += x->price();
    }
    for(auto &x : side_items) {
        res += x->price();
    }
    return res;
}

std::vector<Ingredient *> &Cappuccino::get_side_items() {
    return this->side_items;
}

void Cappuccino::brew() {
    std::cout << "brewing Cappuccino:" << std::endl;
    for(auto &x : ingredients) {
        std::cout << x << " ";
    }
    std::cout << "Cappuccino Done!" << std::endl;
}