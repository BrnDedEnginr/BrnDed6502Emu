#ifndef BD6502_BD6502CPU_H
#define BD6502_BD6502CPU_H

#include "bd6502bus.h"

class bd6502cpu {
public:
    bd6502bus *bus = nullptr;
    uint16_t PC{};
    uint8_t AC{};
    uint8_t X{};
    uint8_t Y{};
    uint8_t SR{};
    uint8_t SP{};
    bd6502cpu();
    void connectToBus(bd6502bus *bus);
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

    uint8_t fetchByte();
    void execute();
};


#endif //BD6502_BD6502CPU_H
