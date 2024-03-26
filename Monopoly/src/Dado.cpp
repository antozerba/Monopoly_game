#include <iostream>
#include <random>
#include "Dado.h"
#include <cstdlib> 
#include <ctime>
#include <chrono>

Dado::Dado() {};

int Dado::generateRandomNumbers() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(1, 6);

    int i = dist(gen);
    int j = dist(gen);

    //std::cout << "La somma dei numeri e': " << i + j << "\n";
    return (i + j);
}