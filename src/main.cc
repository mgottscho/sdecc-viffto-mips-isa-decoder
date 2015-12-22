#include "MyDecoder.hh"
#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: mipsdecode <INST>" << std::endl;
        std::cout << "where <INST> is a 32-bit MIPS instruction specified in hexadecimal format, e.g., 0xDEADBEEF." << std::endl;
        return 1;
    }

    MipsISA::ExtMachInst inst;
    std::stringstream ss;
    std::string instString(argv[1]);
    ss << std::hex << instString;
    ss >> inst;

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
