#include "bd6502cpu.h"
#include <iostream>
#include <format>

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

bd6502cpu::bd6502cpu() = default;

void bd6502cpu::connectToBus(bd6502bus *bus) {
    this->bus = bus;
}

void bd6502cpu::connectToRam(bd6502ram *ram){
    this->ram = ram;
}

void bd6502cpu::loadProgram(char *path) {
    this->program.open(path, std::ios::binary | std::ios::in);
}

void bd6502cpu::fetchByte() {
    if(this->program.eof()){
        this->stop = true;
        return;
    }
    this->program.read(reinterpret_cast<char *>(&this->currentByte), 1);
    this->PC += 1;
}

void bd6502cpu::start() {
    std::cout << "Starting..." << std::endl;
    execute();
    std::cout << "Done." << std::endl;
}

void bd6502cpu::execute() {
    while(!this->stop){
        this->fetchByte();
        handleByte();
    }
}

uint16_t bd6502cpu::swapByte(uint8_t LL, uint8_t HH) {
    uint16_t newByte = HH << 8;
    newByte += LL;
    return newByte;
}

uint16_t bd6502cpu::getAddr(){
    this->fetchByte();
    uint8_t LL = this->currentByte;
    this->fetchByte();
    uint8_t HH = this->currentByte;
    return swapByte(LL, HH);
}

void bd6502cpu::handleByte() {
    uint8_t LL, HH;
    uint16_t addr, tmpMemVal;
    switch (this->currentByte) {
        //LDA #oper (immediate)
        case 0xA9:
            this->fetchByte();
            this->AC = this->currentByte;
            break;
        //LDA oper (zeropage)
        case 0xA5:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDA oper,X (zeropage,X)
        case 0xB5:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDA oper (absolute)
        case 0xAD:
            this->bus->setAddressBus(this->getAddr());
            this->ram->setRW(false);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDA oper,X (absolute,X)
        case 0xBD:
            this->bus->setAddressBus(this->getAddr() + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDA oper,Y (absolute,Y)
        case 0xB9:
            this->bus->setAddressBus(this->getAddr() + this->Y);
            this->ram->setRW(false);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDA (oper,X) (indirect,X)
        case 0xA1:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            LL = this->bus->data;
            this->bus->setAddressBus(this->currentByte + this->X + 1);
            this->ram->enable();
            HH = this->bus->data;
            addr = swapByte(LL, HH);
            this->bus->setAddressBus(addr);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDA (oper),Y (indirect),Y
        case 0xB1:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            LL = this->bus->data;
            this->bus->setAddressBus(this->currentByte + 1);
            this->ram->enable();
            HH = this->bus->data;
            addr = swapByte(LL, HH) + this->Y;
            this->bus->setAddressBus(addr);
            this->ram->enable();
            this->AC = this->bus->data;
            break;
        //LDX LDX #oper (immediate)
        case 0xA2:
            this->fetchByte();
            this->X = this->currentByte;
            break;
        //LDX LDX oper (zeropage)
        case 0xA6:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            this->X = this->bus->data;
            break;
        //LDX LDX oper,Y (zeropage,Y)
        case 0xB6:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->Y);
            this->ram->setRW(false);
            this->ram->enable();
            this->X = this->bus->data;
            break;
        //LDX LDX oper (absolute)
        case 0xAE:
            this->bus->setAddressBus(this->getAddr());
            this->ram->setRW(false);
            this->ram->enable();
            this->X = this->bus->data;
            break;
        //LDX LDX oper,Y (absolute,Y)
        case 0xBE:
            this->bus->setAddressBus(this->getAddr() + this->Y);
            this->ram->setRW(false);
            this->ram->enable();
            this->X = this->bus->data;
            break;
        //LDY LDY #oper (immediate)
        case 0xA0:
            this->fetchByte();
            this->Y = this->currentByte;
            break;
        //LDY LDY oper (zeropage)
        case 0xA4:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            this->Y = this->bus->data;
            break;
        //LDY LDY oper,X (zeropage,X)
        case 0xB4:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            this->Y = this->bus->data;
            break;
        //LDY LDY oper (absolute)
        case 0xAC:
            this->bus->setAddressBus(this->getAddr());
            this->ram->setRW(false);
            this->ram->enable();
            this->Y = this->bus->data;
            break;
        //LDY LDY oper,X (absolute,X)
        case 0xBC:
            this->bus->setAddressBus(this->getAddr() + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            this->Y = this->bus->data;
            break;
        //STA STA oper (zeropage)
        case 0x85:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STA STA oper,X (zeropage,X)
        case 0x95:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STA STA oper (absolute)
        case 0x8D:
            this->bus->setAddressBus(this->getAddr());
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STA STA oper,X (absolute,X)
        case 0x9D:
            this->bus->setAddressBus(this->getAddr() + this->X);
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STA STA oper,Y (absolute,Y)
        case 0x99:
            this->bus->setAddressBus(this->getAddr() + this->Y);
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STA STA (oper,X) (indirect,X)
        case 0x81:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            LL = this->bus->data;
            this->bus->setAddressBus(this->currentByte + this->X + 1);
            this->ram->enable();
            HH = this->bus->data;
            addr = swapByte(LL, HH);
            this->bus->setAddressBus(addr);
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STA STA (oper),Y (indirect),Y
        case 0x91:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            LL = this->bus->data;
            this->bus->setAddressBus(this->currentByte + 1);
            this->ram->enable();
            HH = this->bus->data;
            addr = swapByte(LL, HH) + this->Y;
            this->bus->setAddressBus(addr);
            this->bus->setDataBus(this->AC);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STX STX oper (zeropage)
        case 0x86:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->bus->setDataBus(this->X);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STX STX oper,Y (zeropage,Y)
        case 0x96:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->Y);
            this->bus->setDataBus(this->X);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STX STX oper (absolute)
        case 0x8E:
            this->bus->setAddressBus(this->getAddr());
            this->bus->setDataBus(this->X);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STY STY oper (zeropage)
        case 0x84:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->bus->setDataBus(this->Y);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STY STY oper,X (zeropage,X)
        case 0x94:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->bus->setDataBus(this->Y);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //STY STY oper (absolute)
        case 0x8C:
            this->bus->setAddressBus(this->getAddr());
            this->bus->setDataBus(this->Y);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //TAX
        case 0xAA:
            this->X = this->AC;
            break;
        //TAY
        case 0xA8:
            this->Y = this->AC;
            break;
        //TSX
        case 0xBA:
            this->X = this->SP;
            break;
        //TXA
        case 0x8A:
            this->AC = this->X;
            break;
        //TXS
        case 0x9A:
            this->SP = this->X;
            break;
        //TYA
        case 0x98:
            this->AC = this->Y;
            break;
        //PHA
        case 0x48:
            pushToStack(this->AC);
            break;
        //PHP
        case 0x08:
            this->setBreak(true);
            pushToStack(this->SR);
            break;
        //PLA
        case 0x68:
            this->AC = pullFromStack();
            break;
        //PLP
        case 0x28:
            this->SR = pullFromStack();
            break;
        //DEC oper (zeropage)
        case 0xC6:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal - 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //DEC oper,X (zeropage,X)
        case 0xD6:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal - 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //DEC oper (absolute)
        case 0xCE:
            this->bus->setAddressBus(this->getAddr());
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal - 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //DEC oper,X (absolute,X)
        case 0xDE:
            this->bus->setAddressBus(this->getAddr() + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal - 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //DEX
        case 0xCA:
            this->X -= 1;
            break;
        //DEY
        case 0x88:
            this->Y -= 1;
            break;
        //INC oper (zeropage)
        case 0xE6:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte);
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal + 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //INC oper,X (zeropage,X)
        case 0xF6:
            this->fetchByte();
            this->bus->setAddressBus(this->currentByte + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal + 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //INC oper (absolute)
        case 0xEE:
            this->bus->setAddressBus(this->getAddr());
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal + 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //INC oper,X (absolute,X)
        case 0xFE:
            this->bus->setAddressBus(this->getAddr() + this->X);
            this->ram->setRW(false);
            this->ram->enable();
            tmpMemVal = this->bus->data;
            this->bus->setDataBus(tmpMemVal + 1);
            this->ram->setRW(true);
            this->ram->enable();
            break;
        //INX
        case 0xE8:
            this->X += 1;
            break;
        //INY
        case 0xC8:
            this->Y += 1;
            break;

        //illegal opcode
        default:
            this->stop = true;
            break;
    }
}

void bd6502cpu::pushToStack(uint8_t value) {
    uint16_t addr = this->swapByte(this->SP, 0x01);
    this->bus->setAddressBus(addr);
    this->bus->setDataBus(value);
    this->ram->setRW(true);
    this->ram->enable();
    this->SP -= 1;
}

uint8_t bd6502cpu::pullFromStack() {
    uint16_t addr = this->swapByte(this->SP, 0x01);
    this->bus->setAddressBus(addr);
    this->ram->setRW(false);
    this->ram->enable();
    this->SP += 1;
    return this->bus->data;
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
