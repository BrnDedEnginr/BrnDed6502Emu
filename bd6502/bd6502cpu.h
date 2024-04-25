#ifndef BD6502_BD6502CPU_H
#define BD6502_BD6502CPU_H

#include <fstream>
#include "bd6502bus.h"
#include "bd6502ram.h"

class bd6502cpu {
public:
    bd6502bus *bus = nullptr;
    bd6502ram *ram = nullptr;
    std::ifstream program;
    uint16_t PC = 0;
    uint8_t AC{};
    uint8_t X{};
    uint8_t Y{};
    uint8_t SR{};
    uint8_t SP = 0xFF;
    bd6502cpu();
    void connectToBus(bd6502bus *bus);
    void connectToRam(bd6502ram *ram);
    void loadProgram(char* path);
    void start();
private:
    void setOrUnsetBitAt(bool hl, int pos);
    bool isNegativeSet();
    void setNegative(bool hl);
    bool isOverflowSet();
    void setOverflow(bool hl);
    bool isBreakSet();
    void setBreak(bool hl);
    bool isDecimalSet();
    void setDecimal(bool hl);
    bool isInterruptSet();
    void setInterrupt(bool hl);
    bool isZeroSet();
    void setZero(bool hl);
    bool isCarrySet();
    void setCarry(bool hl);
    uint8_t currentByte;
    bool stop = false;
    void fetchByte();
    void execute();
    void handleByte();
    uint16_t swapByte(uint8_t LL, uint8_t HH);
    uint16_t getAddr();
    void pushToStack(uint8_t value);
    uint8_t pullFromStack();
};


#endif //BD6502_BD6502CPU_H
