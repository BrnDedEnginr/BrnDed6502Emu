#include "bd6502cpu.h"
#include <iostream>

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

bd6502cpu::bd6502cpu() = default;

void bd6502cpu::connectToBus(bd6502bus *bus) {
    this->bus = bus;
}

void bd6502cpu::setOrUnsetBitAt(bool hl, int pos) {
    if(hl){
        this->SR |= 1 << pos;
    }else{
        this->SR &= ~(1 << pos);
    }
}

bool bd6502cpu::isNegativeSet() {
    return CHECK_BIT(this->SR, 7);
}

void bd6502cpu::setNegative(bool hl) {
    setOrUnsetBitAt(hl, 7);
}

bool bd6502cpu::isOverflowSet() {
    return CHECK_BIT(this->SR, 6);
}

void bd6502cpu::setOverflow(bool hl) {
    setOrUnsetBitAt(hl, 6);
}

bool bd6502cpu::isBreakSet() {
    return CHECK_BIT(this->SR, 4);
}

void bd6502cpu::setBreak(bool hl) {
    setOrUnsetBitAt(hl, 4);
}

bool bd6502cpu::isDecimalSet() {
    return CHECK_BIT(this->SR, 3);
}

void bd6502cpu::setDecimal(bool hl) {
    setOrUnsetBitAt(hl, 3);
}

bool bd6502cpu::isInterruptSet() {
    return CHECK_BIT(this->SR, 2);
}

void bd6502cpu::setInterrupt(bool hl) {
    setOrUnsetBitAt(hl, 2);
}

bool bd6502cpu::isZeroSet() {
    return CHECK_BIT(this->SR, 1);
}

void bd6502cpu::setZero(bool hl) {
    setOrUnsetBitAt(hl, 1);
}

bool bd6502cpu::isCarrySet() {
    return CHECK_BIT(this->SR, 0);
}

void bd6502cpu::setCarry(bool hl) {
    setOrUnsetBitAt(hl, 0);
}

uint8_t bd6502cpu::fetchByte() {
    return 0;
}

