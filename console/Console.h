#pragma once
#include "../playLogic/PlayLogic.h"
#include "../player/Player.h"
#include <iostream>
#include <vector>

class Console {
    int boardSize;

public:
    Console() = default;
    explicit Console(int boardSize);
    std::vector<int> cell() const;
    void writeMessage(const char* message);
    void write(const boost::shared_ptr<PlayLogic>& playLogic) const;
};
