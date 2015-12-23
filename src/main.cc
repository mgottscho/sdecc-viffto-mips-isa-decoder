#include "MyDecoder.hh"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdint.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: mipsdecode <INST>" << std::endl;
        std::cout << "where <INST> is a 32-bit MIPS instruction specified in hexadecimal format, e.g., 0xDEADBEEF." << std::endl;
        return 1;
    }

    uint32_t raw;

    std::stringstream ss;
    std::string instString(argv[1]);
    ss << std::hex << instString;
    ss >> raw;

    std::cout << "Raw input:          " << instString << std::endl;
    std::cout.fill('0');
    std::cout << "Interpreted as:   0x" << std::hex << std::setw(8) << raw << std::dec << std::endl;
    std::cout.fill(' ');
    std::cout << std::endl;
    
    MipsISA::ExtMachInst inst = static_cast<MipsISA::ExtMachInst>(raw);

    MipsISA::Decoder decoder;
    bool ret = decoder.decodeInst(inst);
    if (ret) {
        std::cout << "ILLEGAL" << std::endl;
        return ret;
    } else {
        std::cout << "valid" << std::endl;
        return ret;
    }
}
