// Copyright 2021 BekusovMikhail

#include <ctime>
#include <iostream>
#include <vector>
#include "stone.h"
#include "prey.h"
#include "predator.h"
#include "common.h"

unsigned int tmpSeed = time(nullptr);

#include "ocean.h"

Ocean::Ocean(size_t M, size_t N,
             int objectsQuantity) {
    this->N = N;
    this->M = M;
    this->cells = new Cell *[this->M];
    for (auto i = 0; i < this->M; i++) {
        this->cells[i] = new Cell[this->N];
        for (auto j = 0; j < this->N; j++) {
            this->cells[i][j].init({static_cast<coord_t>(i), static_cast<coord_t>(j)}, this);
        }
    }
    addObjects(objectsQuantity);
}

void Ocean::print() const {
    for (auto i = 0; i < this->M; i++) {
        for (auto j = 0; j < this->N; j++) {
            if (this->cells[i][j].getObject()) {
                std::cout << this->cells[i][j].getObject()->getType();
            } else {
                std::cout << EMPTY_N;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl;
}

void Ocean::addObjects(int quantity) {
    int i = 0;
    while (i < quantity) {
        int x = rand() % this->M;
        int y = rand() % this->N;
        int type = rand() % 100;
        if (this->cells[x][y].getObject()) {
            continue;
        }

        Object *obj = nullptr;

        if (type < bounder1) {
            obj = new Predator(&cells[x][y]);
        } else if (type >= bounder1 && type < bounder2) {
            obj = new Stone(&cells[x][y]);
        } else if (type >= bounder2) {
            obj = new Prey(&cells[x][y]);
        }

        this->cells[x][y].setObject(obj);
        this->stuff.push_back(obj);

        i++;
    }
}

Cell *Ocean::findEmptyCell(Pair coord) {
    std::vector<Cell *> emptyCells;
    for (int i = static_cast<int>(coord.x) - 1; i <= coord.x + 1; i++) {
        for (int j = static_cast<int>(coord.y) - 1; j <= coord.y + 1; j++) {
            if (i >= 0 && i < this->M && j >= 0 && j < this->N)
                if (!this->cells[i][j].getObject()) {
                    emptyCells.push_back(&this->cells[i][j]);
                }
        }
    }
    if (emptyCells.empty()) {
        return nullptr;
    } else {
        return emptyCells[rand() % emptyCells.size()];
    }

}

void Ocean::start() {
    this->print();
    while (!this->stuff.empty()) {
        for (auto &obj:this->stuff) {
            obj->live();
        }
        this->clearKillList();
        this->print();
        _sleep(100);
    }
}

void Ocean::addObject(Object *obj) {
    this->stuff.push_back(obj);
}

void Ocean::addToKillList(Object *obj) {
    if (obj) {
        this->killList.push_back(obj);
    }
}

void Ocean::clearKillList() {
    for (auto &elem: this->killList) {
        this->stuff.remove(elem);
        elem->setCell(nullptr);
    }
    killList.clear();
}

Cell *Ocean::findPrey(Pair coord) {
    std::vector<Cell *> preyCells;
    for (int i = static_cast<int>(coord.x) - 1; i <= coord.x + 1; i++) {
        for (int j = static_cast<int>(coord.y) - 1; j <= coord.y + 1; j++) {
            if (i >= 0 && i < this->M && j >= 0 && j < this->N)
                if (this->cells[i][j].getObject())
                    if (this->cells[i][j].getObject()->getType() == PREY_N) {
                        preyCells.push_back(&this->cells[i][j]);
                    }
        }
    }
    if (preyCells.empty()) {
        return nullptr;
    } else {
        return preyCells[rand() % preyCells.size()];
    }
}