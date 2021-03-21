// Copyright 2021 BekusovMikhail

#ifndef INCLUDE_PREDATOR_H_
#define INCLUDE_PREDATOR_H_

#include "prey.h"

class Predator : public Prey {
 private:
    size_t eatenPreys;
 public:
    explicit Predator(Cell *cell);

    void live() override;

    void giveBirth() override;
};


#endif  // INCLUDE_PREDATOR_H_