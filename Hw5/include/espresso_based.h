#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include "ingredient.h"

class EspressoBased {
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew();
    EspressoBased& operator=(const EspressoBased& esp) = delete;
    std::vector<Ingredient*>& get_ingredients();

    virtual ~EspressoBased();

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    explicit EspressoBased(std::string);

    std::vector<Ingredient*> ingredients;
    std::string name;
};

#endif // ESPRESSO_BASED_H