#ifndef BD6502_BD6502BUS_H
#define BD6502_BD6502BUS_H


#include <cstdint>

class bd6502bus {
public:
    uint16_t address{};
    uint8_t data{};
    bd6502bus();
    void setAddressBus(uint16_t address);
    uint16_t readAddressBus();
    void setDataBus(uint8_t data);
    uint8_t readDataBus();
};


#endif //BD6502_BD6502BUS_H
