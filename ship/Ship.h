#pragma once

class Ship {
public:
    Ship(int size, bool horizontal);

    int getSize() const;
    void setSize(int size);

    bool isHorizontal() const;
    void setHorizontal(bool horizontal);

private:
    int size;
    bool horizontal;
};
