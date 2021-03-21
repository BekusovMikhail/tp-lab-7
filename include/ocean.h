// Copyright 2021 BekusovMikhail

#ifndef INCLUDE_OCEAN_H_
#define INCLUDE_OCEAN_H_

#include <list>
#include "common.h"
#include "cell.h"


class Ocean {

 private:
    Cell **cells;
    std::list<Object *> stuff;
    std::list<Object *> killList;
    int M, N, objectsQuantity;

 public:
    Ocean(size_t M, size_t N,
          int objectsQuantity);

    ~Ocean() = default;

    void print() const;

    void addObjects(int quantity);

    Cell *findEmptyCell(Pair coord);

    void start();

    void addObject(Object *obj);

    void addToKillList(Object *obj);

    void clearKillList();

    Cell *findPrey(Pair coord);
};

#endif  // INCLUDE_OCEAN_H_