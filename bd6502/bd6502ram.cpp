#include "bd6502ram.h"

bd6502ram::bd6502ram() {
    initVector();
}

void bd6502ram::initVector() {
    for(int i = 0; i < 64*1024; i++){
        this->ram.push_back(0);
    }
}

void bd6502ram::writeData() {
    this->ram[this->bus->address] = this->bus->data;
}

void bd6502ram::readData() {
    this->bus->data = this->ram[this->bus->address];
}

void bd6502ram::connectToBus(bd6502bus *bus) {
    this->bus = bus;
}
