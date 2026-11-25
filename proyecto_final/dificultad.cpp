#include "dificultad.h"
#include <stdexcept>

dificultad creardificultad(int nivel){

    switch (nivel) {
    case 1: return {0.05, 0.50, 2.0, 0.60};
    case 2: return {0.15, 0.25, 1.2, 0.35};
    case 3: return {0.30, 0.05, 0.7, 0.15};

    default: throw std::invalid_argument("dificultad invalida mi pai");
    }

}