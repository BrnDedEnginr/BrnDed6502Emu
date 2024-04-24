#ifndef BD6502_BD6502RAM_H
#define BD6502_BD6502RAM_H


#include "bd6502bus.h"
#include <cstdint>
#include <vector>

class bd6502ram {
public:
    bd6502bus *bus{};
    std::vector<uint8_t> ram;
    bd6502ram();
    void writeData();
    void readData();
    void connectToBus(bd6502bus *bus);
private:
    void initVector();
};


#endif //BD6502_BD6502RAM_H
