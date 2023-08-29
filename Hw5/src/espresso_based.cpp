#include "espresso_based.h"

EspressoBased::EspressoBased() = default;

EspressoBased::EspressoBased(const EspressoBased &esp) {
    for(auto &x : esp.ingredients) {
        this->ingredients.push_back(x->get_pIng());
    }
}

EspressoBased::~EspressoBased() {
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}