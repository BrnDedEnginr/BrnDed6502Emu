#include "bd6502cpu.h"
#include "bd6502bus.h"
#include "bd6502ram.h"
#include <iostream>

int main() {
    auto *bus = new bd6502bus();
    auto *ram = new bd6502ram();
    ram->connectToBus(bus);
    auto *cpu = new bd6502cpu();
    cpu->connectToBus(bus);
    return 0;
}
