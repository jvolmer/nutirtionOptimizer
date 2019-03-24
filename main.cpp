#include "food.hpp"
#include "store.hpp"
#include "person.hpp"

int main(){

    Store store("Kueche");
    store.addFood({"Spitzkohl", {0.02, 0.26, 0}, 0, 300, 0});
    store.addFood({"Wirsing", {0.03, 0.34, 0}, 0, 300});
    store.addFood({"Rote Beete", {0.02, 0.00001, 0}, 0, 100});
    store.addFood({"Walnuesse", {.14, .10, 0}, 0, 50});
    store.addFood({"Makrelenfilet", {.19, 0.04549, 0.00792}, 0, 500});
    store.addFood({"Avokado", {.01, .08112, 0}, 0, 20});
    store.addFood({"Leinoel", {0, .18168, 0}, 0, 5});

    Person julia("Julia");
    julia.setNutritionMinima({80, 45, 3});

    store.computeFoodPlan(julia);

    for (const Food& food : store.getFood())
        food.printAmount();
}
