#include "Ship.h"

Ship::Ship(const int size, const bool horizontal) : size(size), horizontal(horizontal) {}

int Ship::getSize() const {
    return size;
}

void Ship::setSize(const int newSize) {
    size = newSize;
}

bool Ship::isHorizontal() const {
    return horizontal;
}

void Ship::setHorizontal(bool newHorizontal) {
    horizontal = newHorizontal;
}
