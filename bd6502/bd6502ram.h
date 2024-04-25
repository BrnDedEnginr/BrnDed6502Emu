#ifndef BD6502_BD6502RAM_H
#define BD6502_BD6502RAM_H


#include "bd6502bus.h"
#include <cstdint>
#include <vector>

class bd6502ram {
public:
    bd6502bus *bus{};
    //false read, true write
    bool RW{};
    std::vector<uint8_t> ram;
    bd6502ram();
    void enable();
    void setRW(bool hl);
    void connectToBus(bd6502bus *bus);
private:
    void initVector();
    void writeData();
    void readData();
};


#endif //BD6502_BD6502RAM_H
