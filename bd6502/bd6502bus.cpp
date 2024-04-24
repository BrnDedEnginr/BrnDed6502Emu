#include "bd6502bus.h"

bd6502bus::bd6502bus() = default;

void bd6502bus::setAddressBus(uint16_t address) {
    this->address = address;
}

uint16_t bd6502bus::readAddressBus() {
    return this->address;
}

void bd6502bus::setDataBus(uint8_t data) {
    this->data = data;
}

uint8_t bd6502bus::readDataBus() {
    return this->data;
}