//
// Created by stanislaw on 17.12.2021.
//

#include "windowpos.h"

int WindowPos::x = 0;
int WindowPos::y = 0;

void WindowPos::save() {
    std::ofstream file;
    file.open("windowpos");
    file << WindowPos::x << " " << WindowPos::y;
}

void WindowPos::load() {
    std::ifstream file;
    file.open("windowpos");
    file >> WindowPos::x >> WindowPos::y;
}