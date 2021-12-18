//
// Created by stanislaw on 17.12.2021.
//

#ifndef OTRSP_WINDOWPOS_H
#define OTRSP_WINDOWPOS_H
#include <fstream>
#include <iostream>

class WindowPos {
public:
    static int x, y;
    static void save();
    static void load();
};

#endif //OTRSP_WINDOWPOS_H
