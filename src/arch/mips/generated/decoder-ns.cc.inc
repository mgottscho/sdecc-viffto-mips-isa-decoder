// DO NOT EDIT
// This file was automatically generated from an ISA description:
//   mips/isa/main.isa

#if !defined(__SPLIT) || (__SPLIT == 1)


    void MipsStaticInst::printReg(std::ostream &os, int reg) const
    {
        if (reg < FP_Reg_Base) {
            ccprintf(os, "r%d", reg);
        }
        else {
            ccprintf(os, "f%d", reg - FP_Reg_Base);
        }
    }

    std::string MipsStaticInst::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        std::stringstream ss;

        ccprintf(ss, "%-10s ", mnemonic);

        // Need to find standard way to not print
        // this info. Maybe add bool variable to
        // class?
        if (strcmp(mnemonic, "syscall") != 0) {
            if(_numDestRegs > 0){
                printReg(ss, _destRegIdx[0]);
            }

            if(_numSrcRegs > 0) {
                ss << ", ";
                printReg(ss, _srcRegIdx[0]);
            }

            if(_numSrcRegs > 1) {
                ss << ", ";
                printReg(ss, _srcRegIdx[1]);
            }
        }

        // Should we define a separate inst. class
        // just for two insts?
        if (strcmp(mnemonic, "sll") == 0 || strcmp(mnemonic, "sra") == 0) {
            ccprintf(ss,", %d",SA);
        }

        return ss.str();
    }


    std::string Nop::generateDisassembly(Addr pc,
                                         const SymbolTable *symtab) const
    {
        return csprintf("%-10s %s", "nop", originalDisassembly);
    }

    /// Helper function for decoding nops.  Substitute Nop object
    /// for original inst passed in as arg (and delete latter).
    inline
    MipsStaticInst *
    makeNop(MipsStaticInst *inst)
    {
        std::string nop_str = "(" + inst->disassemble(0) + ")";
        MipsStaticInst *nop = new Nop(nop_str, inst->machInst);
        delete inst;
        return nop;
    }


std::string inst2string(MachInst machInst)
{
    string str = "";
    uint32_t mask = 0x80000000;

    for(int i=0; i < 32; i++) {
        if ((machInst & mask) == 0) {
            str += "0";
        } else {
            str += "1";
        }

        mask = mask >> 1;
    }

    return str;
}


        std::string CP0Control::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;
            ccprintf(ss, "%-10s r%d, %d, %d", mnemonic, RT, RD, SEL);
            return ss.str();
        }
        std::string CP0TLB::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;
            ccprintf(ss, "%-10s r%d, %d, %d", mnemonic, RT, RD, SEL);
            return ss.str();
        }
        std::string CP1Control::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;
            ccprintf(ss, "%-10s r%d, f%d", mnemonic, RT, FS);
            return ss.str();
        }


        std::string IntOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            // just print the first dest... if there's a second one,
            // it's generally implicit
            if (_numDestRegs > 0) {
                printReg(ss, _destRegIdx[0]);
                ss << ", ";
            }

            // just print the first two source regs... if there's
            // a third one, it's a read-modify-write dest (Rc),
            // e.g. for CMOVxx
            if (_numSrcRegs > 0) {
                printReg(ss, _srcRegIdx[0]);
            }

            if (_numSrcRegs > 1) {
                ss << ", ";
                printReg(ss, _srcRegIdx[1]);
            }

            return ss.str();
        }

        std::string HiLoOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            //Destination Registers are implicit for HI/LO ops
            if (_numSrcRegs > 0) {
                printReg(ss, _srcRegIdx[0]);
            }

            if (_numSrcRegs > 1) {
                ss << ", ";
                printReg(ss, _srcRegIdx[1]);
            }

            return ss.str();
        }

        std::string HiLoRsSelOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            if (_numDestRegs > 0 && _destRegIdx[0] < 32) {
                printReg(ss, _destRegIdx[0]);
            } else if (_numSrcRegs > 0 && _srcRegIdx[0] < 32) {
                printReg(ss, _srcRegIdx[0]);
            }

            return ss.str();
        }

        std::string HiLoRdSelOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            if (_numDestRegs > 0 && _destRegIdx[0] < 32) {
                printReg(ss, _destRegIdx[0]);
            } else if (_numSrcRegs > 0 && _srcRegIdx[0] < 32) {
                printReg(ss, _srcRegIdx[0]);
            }

            return ss.str();
        }

        std::string HiLoRdSelValOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            if (_numDestRegs > 0 && _destRegIdx[0] < 32) {
                printReg(ss, _destRegIdx[0]);
            } else if (_numSrcRegs > 0 && _srcRegIdx[0] < 32) {
                printReg(ss, _srcRegIdx[0]);
            }

            return ss.str();
        }

        std::string IntImmOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            if (_numDestRegs > 0) {
                printReg(ss, _destRegIdx[0]);
            }

            ss << ", ";

            if (_numSrcRegs > 0) {
                printReg(ss, _srcRegIdx[0]);
                ss << ", ";
            }

            if(strcmp(mnemonic,"lui") == 0)
                ccprintf(ss, "0x%x ", sextImm);
            else
                ss << (int) sextImm;

            return ss.str();
        }



        std::string FPCompareOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
            std::stringstream ss;

            ccprintf(ss, "%-10s ", mnemonic);

            ccprintf(ss,"%d",CC);

            if(_numSrcRegs > 0) {
                ss << ", ";
                printReg(ss, _srcRegIdx[0]);
            }

            if(_numSrcRegs > 1) {
                ss << ", ";
                printReg(ss, _srcRegIdx[1]);
            }

            return ss.str();
        }

    std::string
    Memory::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        return csprintf("%-10s %c%d, %d(r%d)", mnemonic,
                        flags[IsFloating] ? 'f' : 'r', RT, disp, RS);
    }

    std::string
    MemoryNoDisp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        return csprintf("%-10s %c%d, r%d(r%d)", mnemonic,
                        flags[IsFloating] ? 'f' : 'r',
                        flags[IsFloating] ? FD : RD,
                        RS, RT);
    }


    std::string MTOp::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        std::stringstream ss;

        if (strcmp(mnemonic,"mttc0") == 0 || strcmp(mnemonic,"mftc0") == 0) {
            ccprintf(ss, "%-10s r%d, r%d, %d", mnemonic, RT, RD, SEL);
        } else if (strcmp(mnemonic,"mftgpr") == 0) {
            ccprintf(ss, "%-10s r%d, r%d", mnemonic, RD, RT);
        } else {
            ccprintf(ss, "%-10s r%d, r%d", mnemonic, RT, RD);
        }

        return ss.str();
    }

        std::string Trap::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
                return "Disassembly of trap instruction\n";
        }
        std::string TrapImm::generateDisassembly(Addr pc, const SymbolTable *symtab) const
        {
                return "Disassembly of trap instruction\n";
        }

    MipsISA::PCState
    Branch::branchTarget(const MipsISA::PCState &branchPC) const
    {
        MipsISA::PCState target = branchPC;
        target.advance();
        target.npc(branchPC.pc() + sizeof(MachInst) + disp);
        target.nnpc(target.npc() + sizeof(MachInst));
        return target;
    }

    MipsISA::PCState
    Jump::branchTarget(ThreadContext *tc) const
    {
        MipsISA::PCState target = tc->pcState();
        Addr pc = target.pc();
        target.advance();
        target.npc((pc & 0xF0000000) | disp);
        target.nnpc(target.npc() + sizeof(MachInst));
        return target;
    }

    const std::string &
    PCDependentDisassembly::disassemble(Addr pc,
                                        const SymbolTable *symtab) const
    {
        if (!cachedDisassembly ||
            pc != cachedPC || symtab != cachedSymtab)
        {
            if (cachedDisassembly)
                delete cachedDisassembly;

            cachedDisassembly =
                new std::string(generateDisassembly(pc, symtab));
            cachedPC = pc;
            cachedSymtab = symtab;
        }

        return *cachedDisassembly;
    }

    std::string
    Branch::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        std::stringstream ss;

        ccprintf(ss, "%-10s ", mnemonic);

        // There's only one register arg (RA), but it could be
        // either a source (the condition for conditional
        // branches) or a destination (the link reg for
        // unconditional branches)
        if (_numSrcRegs == 1) {
            printReg(ss, _srcRegIdx[0]);
            ss << ", ";
        } else if(_numSrcRegs == 2) {
            printReg(ss, _srcRegIdx[0]);
            ss << ", ";
            printReg(ss, _srcRegIdx[1]);
            ss << ", ";
        }

        Addr target = pc + 4 + disp;

        std::string str;
        if (symtab && symtab->findSymbol(target, str))
            ss << str;
        else
            ccprintf(ss, "0x%x", target);

        return ss.str();
    }

    std::string
    Jump::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        std::stringstream ss;

        ccprintf(ss, "%-10s ", mnemonic);

        if ( strcmp(mnemonic,"jal") == 0 ) {
            Addr npc = pc + 4;
            ccprintf(ss,"0x%x",(npc & 0xF0000000) | disp);
        } else if (_numSrcRegs == 0) {
            std::string str;
            if (symtab && symtab->findSymbol(disp, str))
                ss << str;
            else
                ccprintf(ss, "0x%x", disp);
        } else if (_numSrcRegs == 1) {
             printReg(ss, _srcRegIdx[0]);
        } else if(_numSrcRegs == 2) {
            printReg(ss, _srcRegIdx[0]);
            ss << ", ";
            printReg(ss, _srcRegIdx[1]);
        }

        return ss.str();
    }

    std::string
    FailUnimplemented::generateDisassembly(Addr pc,
                                           const SymbolTable *symtab) const
    {
        return csprintf("%-10s (unimplemented)", mnemonic);
    }

    std::string
    CP0Unimplemented::generateDisassembly(Addr pc,
                                           const SymbolTable *symtab) const
    {
        return csprintf("%-10s (unimplemented)", mnemonic);
    }

    std::string
    CP1Unimplemented::generateDisassembly(Addr pc,
                                           const SymbolTable *symtab) const
    {
        return csprintf("%-10s (unimplemented)", mnemonic);
    }
    std::string
    CP2Unimplemented::generateDisassembly(Addr pc,
                                           const SymbolTable *symtab) const
    {
        return csprintf("%-10s (unimplemented)", mnemonic);
    }

    std::string
    WarnUnimplemented::generateDisassembly(Addr pc,
                                           const SymbolTable *symtab) const
    {
        return csprintf("%-10s (unimplemented)", mnemonic);
    }

    std::string
    Unknown::generateDisassembly(Addr pc, const SymbolTable *symtab) const
    {
        return csprintf("%-10s (inst 0x%x, opcode 0x%x, binary:%s)",
                        "unknown", machInst, OPCODE, inst2string(machInst));
    }

// BasicOp::movf(['\n                            Rd = (getCondCode(FCSR, CC) == 0) ? Rd : Rs;\n                        '],{})

        Movf::Movf(MachInst machInst)  : MipsStaticInst("movf", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RD;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// BasicOp::movt(['\n                            Rd = (getCondCode(FCSR, CC) == 1) ? Rd : Rs;\n                        '],{})

        Movt::Movt(MachInst machInst)  : MipsStaticInst("movt", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RD;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::ssnop([';'],{})

        Ssnop::Ssnop(MachInst machInst)  : MipsStaticInst("ssnop", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;;
        }

// BasicOp::ehb([';'],{})

        Ehb::Ehb(MachInst machInst)  : MipsStaticInst("ehb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;;
        }

// Nop::nop(([], {}))

// BasicOp::sll([' Rd = Rt_uw << SA; '],{})

        Sll::Sll(MachInst machInst)  : MipsStaticInst("sll", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::srl([' Rd = Rt_uw >> SA; '],{})

        Srl::Srl(MachInst machInst)  : MipsStaticInst("srl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::rotr(['\n                                Rd = (Rt_uw << (32 - SA)) | (Rt_uw >> SA);\n                            '],{})

        Rotr::Rotr(MachInst machInst)  : MipsStaticInst("rotr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::sra(['\n                            uint32_t temp = Rt >> SA;\n                            if ( (Rt & 0x80000000) > 0 ) {\n                                uint32_t mask = 0x80000000;\n                                for(int i=0; i < SA; i++) {\n                                    temp |= mask;\n                                    mask = mask >> 1;\n                                }\n                            }\n                            Rd = temp;\n                        '],{})

        Sra::Sra(MachInst machInst)  : MipsStaticInst("sra", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::sllv([' Rd = Rt_uw << Rs<4:0>; '],{})

        Sllv::Sllv(MachInst machInst)  : MipsStaticInst("sllv", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::srlv([' Rd = Rt_uw >> Rs<4:0>; '],{})

        Srlv::Srlv(MachInst machInst)  : MipsStaticInst("srlv", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::rotrv(['\n                            Rd = (Rt_uw << (32 - Rs<4:0>)) |\n                                 (Rt_uw >> Rs<4:0>);\n                        '],{})

        Rotrv::Rotrv(MachInst machInst)  : MipsStaticInst("rotrv", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::srav(['\n                        int shift_amt = Rs<4:0>;\n\n                        uint32_t temp = Rt >> shift_amt;\n\n                        if ((Rt & 0x80000000) > 0) {\n                            uint32_t mask = 0x80000000;\n                            for (int i = 0; i < shift_amt; i++) {\n                                temp |= mask;\n                                mask = mask >> 1;\n                            }\n                        }\n                        Rd = temp;\n                    '],{})

        Srav::Srav(MachInst machInst)  : MipsStaticInst("srav", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Jump::jr_hb(['\n                            Config1Reg config1 = Config1;\n                            if (config1.ca == 0) {\n                                NNPC = Rs;\n                            } else {\n                                panic("MIPS16e not supported\\n");\n                            }\n                        ', 'IsReturn', 'ClearHazards'],{})

        Jr_hb::Jr_hb(MachInst machInst)  : Jump("jr_hb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG1 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsControl] = true;
	flags[IsIndirectControl] = true;
	flags[IsInteger] = true;
	flags[IsReturn] = true;
	flags[IsUncondControl] = true;;
        }

// Jump::jr(['\n                            Config1Reg config1 = Config1;\n                            if (config1.ca == 0) {\n                                NNPC = Rs;\n                            } else {\n                                panic("MIPS16e not supported\\n");\n                            }\n                        ', 'IsReturn'],{})

        Jr::Jr(MachInst machInst)  : Jump("jr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG1 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsControl] = true;
	flags[IsIndirectControl] = true;
	flags[IsInteger] = true;
	flags[IsReturn] = true;
	flags[IsUncondControl] = true;;
        }

// Jump::jalr_hb(['\n                            Rd = NNPC;\n                            NNPC = Rs;\n                        ', 'IsCall', 'ClearHazards'],{})

        Jalr_hb::Jalr_hb(MachInst machInst)  : Jump("jalr_hb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCall] = true;
	flags[IsControl] = true;
	flags[IsIndirectControl] = true;
	flags[IsInteger] = true;
	flags[IsUncondControl] = true;;
        }

// Jump::jalr(['\n                            Rd = NNPC;\n                            NNPC = Rs;\n                        ', 'IsCall'],{})

        Jalr::Jalr(MachInst machInst)  : Jump("jalr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCall] = true;
	flags[IsControl] = true;
	flags[IsIndirectControl] = true;
	flags[IsInteger] = true;
	flags[IsUncondControl] = true;;
        }

// BasicOp::movz([' Rd = (Rt == 0) ? Rs : Rd; '],{})

        Movz::Movz(MachInst machInst)  : MipsStaticInst("movz", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RD;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::movn([' Rd = (Rt != 0) ? Rs : Rd; '],{})

        Movn::Movn(MachInst machInst)  : MipsStaticInst("movn", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RD;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::syscall_se([' xc->syscall(R2); ', 'IsSerializeAfter', 'IsNonSpeculative'],{})

        Syscall_se::Syscall_se(MachInst machInst)  : MipsStaticInst("syscall_se", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = 2;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;
	flags[IsSerializeAfter] = true;;
        }

// BasicOp::syscall([' fault = new SystemCallFault(); '],{})

        Syscall::Syscall(MachInst machInst)  : MipsStaticInst("syscall", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;;
        }

// BasicOp::sync([' ; ', 'IsMemBarrier'],{})

        Sync::Sync(MachInst machInst)  : MipsStaticInst("sync", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	flags[IsMemBarrier] = true;;
        }

// BasicOp::break(['fault = new BreakpointFault();'],{})

        Break::Break(MachInst machInst)  : MipsStaticInst("break", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;;
        }

// Unknown::unknown(([], {}))

// HiLoRsSelOp::mfhi(([' Rd = HI_RS_SEL; ', 'IntMultOp', 'IsIprAccess'], {}))

        Mfhi::Mfhi(MachInst machInst)  : HiLoRsSelOp("mfhi", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACSRC*3;
	flags[IsInteger] = true;
	flags[IsIprAccess] = true;;
        }

// HiLoRdSelOp::mthi(([' HI_RD_SEL = Rs; '], {}))

        Mthi::Mthi(MachInst machInst)  : HiLoRdSelOp("mthi", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoRsSelOp::mflo(([' Rd = LO_RS_SEL; ', 'IntMultOp', 'IsIprAccess'], {}))

        Mflo::Mflo(MachInst machInst)  : HiLoRsSelOp("mflo", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACSRC*3;
	flags[IsInteger] = true;
	flags[IsIprAccess] = true;;
        }

// HiLoRdSelOp::mtlo(([' LO_RD_SEL = Rs; '], {}))

        Mtlo::Mtlo(MachInst machInst)  : HiLoRdSelOp("mtlo", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// HiLoRdSelValOp::mult([' val = Rs_sd * Rt_sd; ', 'IntMultOp'],{})

        Mult::Mult(MachInst machInst)  : HiLoRdSelOp("mult", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoRdSelValOp::multu([' val = Rs_ud * Rt_ud; ', 'IntMultOp'],{})

        Multu::Multu(MachInst machInst)  : HiLoRdSelOp("multu", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoOp::div(['\n                        if (Rt_sd != 0) {\n                            HI0 = Rs_sd % Rt_sd;\n                            LO0 = Rs_sd / Rt_sd;\n                        }\n                    ', 'IntDivOp'],{})

        Div::Div(MachInst machInst)  : HiLoOp("div", machInst, IntDivOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = INTREG_LO;
	_numIntDestRegs++;
	_destRegIdx[_numDestRegs++] = INTREG_HI;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoOp::divu(['\n                        if (Rt_ud != 0) {\n                            HI0 = Rs_ud % Rt_ud;\n                            LO0 = Rs_ud / Rt_ud;\n                        }\n                    ', 'IntDivOp'],{})

        Divu::Divu(MachInst machInst)  : HiLoOp("divu", machInst, IntDivOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = INTREG_LO;
	_numIntDestRegs++;
	_destRegIdx[_numDestRegs++] = INTREG_HI;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// IntOp::add(['\n                            IntReg result;\n                            Rd = result = Rs + Rt;\n                            if (FullSystem &&\n                                    findOverflow(32, result, Rs, Rt)) {\n                                fault = new IntegerOverflowFault();\n                            }\n                        '],{})

        Add::Add(MachInst machInst)  : IntOp("add", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::addu([' Rd_sw = Rs_sw + Rt_sw;'],{})

        Addu::Addu(MachInst machInst)  : IntOp("addu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::sub(['\n                            IntReg result;\n                            Rd = result = Rs - Rt;\n                            if (FullSystem &&\n                                    findOverflow(32, result, Rs, ~Rt)) {\n                                fault = new IntegerOverflowFault();\n                            }\n                        '],{})

        Sub::Sub(MachInst machInst)  : IntOp("sub", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::subu([' Rd_sw = Rs_sw - Rt_sw; '],{})

        Subu::Subu(MachInst machInst)  : IntOp("subu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::and([' Rd = Rs & Rt; '],{})

        And::And(MachInst machInst)  : IntOp("and", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::or([' Rd = Rs | Rt; '],{})

        Or::Or(MachInst machInst)  : IntOp("or", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::xor([' Rd = Rs ^ Rt; '],{})

        Xor::Xor(MachInst machInst)  : IntOp("xor", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::nor([' Rd = ~(Rs | Rt); '],{})

        Nor::Nor(MachInst machInst)  : IntOp("nor", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// IntOp::slt(['  Rd_sw = (Rs_sw < Rt_sw) ? 1 : 0 '],{})

        Slt::Slt(MachInst machInst)  : IntOp("slt", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// IntOp::sltu([' Rd_uw = (Rs_uw < Rt_uw) ? 1 : 0 '],{})

        Sltu::Sltu(MachInst machInst)  : IntOp("sltu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Trap::tge(['  cond = (Rs_sw >= Rt_sw); '],{})

        Tge::Tge(MachInst machInst)  : MipsStaticInst("tge", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Trap::tgeu([' cond = (Rs_uw >= Rt_uw); '],{})

        Tgeu::Tgeu(MachInst machInst)  : MipsStaticInst("tgeu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Trap::tlt([' cond = (Rs_sw < Rt_sw); '],{})

        Tlt::Tlt(MachInst machInst)  : MipsStaticInst("tlt", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Trap::tltu([' cond = (Rs_uw < Rt_uw); '],{})

        Tltu::Tltu(MachInst machInst)  : MipsStaticInst("tltu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Trap::teq([' cond = (Rs_sw == Rt_sw); '],{})

        Teq::Teq(MachInst machInst)  : MipsStaticInst("teq", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Trap::tne([' cond = (Rs_sw != Rt_sw); '],{})

        Tne::Tne(MachInst machInst)  : MipsStaticInst("tne", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Branch::bltz([' cond = (Rs_sw < 0); '],{})

        Bltz::Bltz(MachInst machInst)  : Branch("bltz", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bgez([' cond = (Rs_sw >= 0); '],{})

        Bgez::Bgez(MachInst machInst)  : Branch("bgez", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bltzl([' cond = (Rs_sw < 0); ', 'Likely'],{})

        Bltzl::Bltzl(MachInst machInst)  : Branch("bltzl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bgezl([' cond = (Rs_sw >= 0); ', 'Likely'],{})

        Bgezl::Bgezl(MachInst machInst)  : Branch("bgezl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// TrapImm::tgei([' cond = (Rs_sw >= (int16_t)INTIMM); '],{})

        Tgei::Tgei(MachInst machInst)  : MipsStaticInst("tgei", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// TrapImm::tgeiu(['\n                        cond = (Rs_uw >= (uint32_t)(int32_t)(int16_t)INTIMM);\n                    '],{})

        Tgeiu::Tgeiu(MachInst machInst)  : MipsStaticInst("tgeiu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// TrapImm::tlti([' cond = (Rs_sw < (int16_t)INTIMM); '],{})

        Tlti::Tlti(MachInst machInst)  : MipsStaticInst("tlti", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// TrapImm::tltiu(['\n                        cond = (Rs_uw < (uint32_t)(int32_t)(int16_t)INTIMM);\n                    '],{})

        Tltiu::Tltiu(MachInst machInst)  : MipsStaticInst("tltiu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// TrapImm::teqi([' cond = (Rs_sw == (int16_t)INTIMM); '],{})

        Teqi::Teqi(MachInst machInst)  : MipsStaticInst("teqi", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// TrapImm::tnei([' cond = (Rs_sw != (int16_t)INTIMM); '],{})

        Tnei::Tnei(MachInst machInst)  : MipsStaticInst("tnei", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Branch::bltzal([' cond = (Rs_sw < 0); ', 'Link'],{})

        Bltzal::Bltzal(MachInst machInst)  : Branch("bltzal", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = 31;
	_numIntDestRegs++;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bal([' cond = 1; ', 'IsCall', 'Link'],{})

        Bal::Bal(MachInst machInst)  : Branch("bal", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = 31;
	_numIntDestRegs++;
	flags[IsCall] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;
	flags[IsUncondControl] = true;;
        }

// Branch::bgezal([' cond = (Rs_sw >= 0); ', 'Link'],{})

        Bgezal::Bgezal(MachInst machInst)  : Branch("bgezal", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = 31;
	_numIntDestRegs++;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bltzall([' cond = (Rs_sw < 0); ', 'Link', 'Likely'],{})

        Bltzall::Bltzall(MachInst machInst)  : Branch("bltzall", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = 31;
	_numIntDestRegs++;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bgezall([' cond = (Rs_sw >= 0); ', 'Link', 'Likely'],{})

        Bgezall::Bgezall(MachInst machInst)  : Branch("bgezall", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = 31;
	_numIntDestRegs++;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspBranch::bposge32(([' cond = (dspctl<5:0> >= 32); '], {}))

        Bposge32::Bposge32(MachInst machInst)  : Branch("bposge32", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;;
        }

// WarnUnimpl::synci([],{})

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Jump::j([' NNPC = (NPC & 0xF0000000) | (JMPTARG << 2); '],{})

        J::J(MachInst machInst)  : Jump("j", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	flags[IsControl] = true;
	flags[IsIndirectControl] = true;
	flags[IsUncondControl] = true;;
        }

// Jump::jal([' NNPC = (NPC & 0xF0000000) | (JMPTARG << 2); ', 'IsCall', 'Link'],{})

        Jal::Jal(MachInst machInst)  : Jump("jal", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = 31;
	_numIntDestRegs++;
	flags[IsCall] = true;
	flags[IsControl] = true;
	flags[IsIndirectControl] = true;
	flags[IsInteger] = true;
	flags[IsUncondControl] = true;;
        }

// Branch::b([' cond = 1; '],{})

        B::B(MachInst machInst)  : Branch("b", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsUncondControl] = true;;
        }

// Branch::beq([' cond = (Rs_sw == Rt_sw); '],{})

        Beq::Beq(MachInst machInst)  : Branch("beq", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bne([' cond = (Rs_sw != Rt_sw); '],{})

        Bne::Bne(MachInst machInst)  : Branch("bne", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::blez([' cond = (Rs_sw <= 0); '],{})

        Blez::Blez(MachInst machInst)  : Branch("blez", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bgtz([' cond = (Rs_sw > 0); '],{})

        Bgtz::Bgtz(MachInst machInst)  : Branch("bgtz", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// IntImmOp::addi(['\n                IntReg result;\n                Rt = result = Rs + imm;\n                if (FullSystem &&\n                        findOverflow(32, result, Rs, imm)) {\n                    fault = new IntegerOverflowFault();\n                }\n            '],{})

        Addi::Addi(MachInst machInst)  : IntImmOp("addi", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::addiu([' Rt_sw = Rs_sw + imm; '],{})

        Addiu::Addiu(MachInst machInst)  : IntImmOp("addiu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::slti([' Rt_sw = (Rs_sw < imm) ? 1 : 0 '],{})

        Slti::Slti(MachInst machInst)  : IntImmOp("slti", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::sltiu([' Rt_uw = (Rs_uw < (uint32_t)sextImm) ? 1 : 0;'],{})

        Sltiu::Sltiu(MachInst machInst)  : IntImmOp("sltiu", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::andi([' Rt_sw = Rs_sw & zextImm; '],{})

        Andi::Andi(MachInst machInst)  : IntImmOp("andi", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::ori([' Rt_sw = Rs_sw | zextImm; '],{})

        Ori::Ori(MachInst machInst)  : IntImmOp("ori", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::xori([' Rt_sw = Rs_sw ^ zextImm; '],{})

        Xori::Xori(MachInst machInst)  : IntImmOp("xori", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntImmOp::lui([' Rt = imm << 16; '],{})

        Lui::Lui(MachInst machInst)  : IntImmOp("lui", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP0Control::mfc0(['\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        Rt = CP0_RD_SEL;\n                        /* Hack for PageMask */\n                        if (RD == 5) {\n                            // PageMask\n                            if (config3.sp == 0 || pageGrain.esp == 0)\n                                Rt &= 0xFFFFE7FF;\n                        }\n                    '],{})

        Mfc0::Mfc0(MachInst machInst)  : CP0Control("mfc0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG3 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_PAGEGRAIN + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = (RD << 3 | SEL) + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Control::mtc0([' \n                        CP0_RD_SEL = Rt;\n                        CauseReg cause = Cause;\n                        IntCtlReg intCtl = IntCtl;\n                        if (RD == 11) {\n                            // Compare\n                            if (cause.ti == 1) {\n                                cause.ti = 0;\n                                int offset = 10; // corresponding to cause.ip0\n                                offset += intCtl.ipti - 2;\n                                replaceBits(cause, offset, offset, 0);\n                            }\n                        }\n                        Cause = cause;\n                    '],{})

        Mtc0::Mtc0(MachInst machInst)  : CP0Control("mtc0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = (RD << 3 | SEL) + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CAUSE + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_CAUSE + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_INTCTL + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::dmfc0([],{})

// CP0Unimpl::dmtc0([],{})

// CP0Unimpl::unknown([],{})

// MT_MFTR::mftc0(['\n                            data = xc->readRegOtherThread((RT << 3 | SEL) +\n                                                          Misc_Reg_Base);\n                        '],{})

        Mftc0::Mftc0(MachInst machInst)  : MTOp("mftc0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftgpr(['\n                                data = xc->readRegOtherThread(RT);\n                            '],{})

        Mftgpr::Mftgpr(MachInst machInst)  : MTOp("mftgpr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftlo_dsp0([' data = xc->readRegOtherThread(INTREG_DSP_LO0); '],{})

        Mftlo_dsp0::Mftlo_dsp0(MachInst machInst)  : MTOp("mftlo_dsp0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mfthi_dsp0([' data = xc->readRegOtherThread(INTREG_DSP_HI0); '],{})

        Mfthi_dsp0::Mfthi_dsp0(MachInst machInst)  : MTOp("mfthi_dsp0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftacx_dsp0([' data = xc->readRegOtherThread(INTREG_DSP_ACX0); '],{})

        Mftacx_dsp0::Mftacx_dsp0(MachInst machInst)  : MTOp("mftacx_dsp0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftlo_dsp1([' data = xc->readRegOtherThread(INTREG_DSP_LO1); '],{})

        Mftlo_dsp1::Mftlo_dsp1(MachInst machInst)  : MTOp("mftlo_dsp1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mfthi_dsp1([' data = xc->readRegOtherThread(INTREG_DSP_HI1); '],{})

        Mfthi_dsp1::Mfthi_dsp1(MachInst machInst)  : MTOp("mfthi_dsp1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftacx_dsp1([' data = xc->readRegOtherThread(INTREG_DSP_ACX1); '],{})

        Mftacx_dsp1::Mftacx_dsp1(MachInst machInst)  : MTOp("mftacx_dsp1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftlo_dsp2([' data = xc->readRegOtherThread(INTREG_DSP_LO2); '],{})

        Mftlo_dsp2::Mftlo_dsp2(MachInst machInst)  : MTOp("mftlo_dsp2", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mfthi_dsp2([' data = xc->readRegOtherThread(INTREG_DSP_HI2); '],{})

        Mfthi_dsp2::Mfthi_dsp2(MachInst machInst)  : MTOp("mfthi_dsp2", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftacx_dsp2([' data = xc->readRegOtherThread(INTREG_DSP_ACX2); '],{})

        Mftacx_dsp2::Mftacx_dsp2(MachInst machInst)  : MTOp("mftacx_dsp2", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftlo_dsp3([' data = xc->readRegOtherThread(INTREG_DSP_LO3); '],{})

        Mftlo_dsp3::Mftlo_dsp3(MachInst machInst)  : MTOp("mftlo_dsp3", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mfthi_dsp3([' data = xc->readRegOtherThread(INTREG_DSP_HI3); '],{})

        Mfthi_dsp3::Mfthi_dsp3(MachInst machInst)  : MTOp("mfthi_dsp3", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftacx_dsp3([' data = xc->readRegOtherThread(INTREG_DSP_ACX3); '],{})

        Mftacx_dsp3::Mftacx_dsp3(MachInst machInst)  : MTOp("mftacx_dsp3", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mftdsp([' data = xc->readRegOtherThread(INTREG_DSP_CONTROL); '],{})

        Mftdsp::Mftdsp(MachInst machInst)  : MTOp("mftdsp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// MT_MFTR::mftc1([' data = xc->readRegOtherThread(RT +\n                                                                            FP_Reg_Base);\n                                '],{})

        Mftc1::Mftc1(MachInst machInst)  : MTOp("mftc1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MFTR::mfthc1([' data = xc->readRegOtherThread(RT +\n                                                                             FP_Reg_Base);\n                                '],{})

        Mfthc1::Mfthc1(MachInst machInst)  : MTOp("mfthc1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// Unknown::unknown(([], {}))

// MT_MFTR::cftc1(['\n                                uint32_t fcsr_val = xc->readRegOtherThread(FLOATREG_FCSR +\n                                                                            FP_Reg_Base);\n                                switch (RT) {\n                                  case 0:\n                                    data = xc->readRegOtherThread(FLOATREG_FIR +\n                                                                  Misc_Reg_Base);\n                                    break;\n                                  case 25:\n                                    data = (fcsr_val & 0xFE000000 >> 24) |\n                                           (fcsr_val & 0x00800000 >> 23);\n                                    break;\n                                  case 26:\n                                    data = fcsr_val & 0x0003F07C;\n                                    break;\n                                  case 28:\n                                    data = (fcsr_val & 0x00000F80) |\n                                           (fcsr_val & 0x01000000 >> 21) |\n                                           (fcsr_val & 0x00000003);\n                                    break;\n                                  case 31:\n                                    data = fcsr_val;\n                                    break;\n                                  default:\n                                    fatal("FP Control Value (%d) Not Valid");\n                                }\n                            '],{})

        Cftc1::Cftc1(MachInst machInst)  : MTOp("cftc1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// MT_MTTR::mttc0([' xc->setRegOtherThread((RD << 3 | SEL) + Misc_Reg_Base,\n                                                            Rt);\n                                   '],{})

        Mttc0::Mttc0(MachInst machInst)  : MTOp("mttc0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttgpr([' xc->setRegOtherThread(RD, Rt); '],{})

        Mttgpr::Mttgpr(MachInst machInst)  : MTOp("mttgpr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttlo_dsp0([' xc->setRegOtherThread(INTREG_DSP_LO0, Rt);\n                                                '],{})

        Mttlo_dsp0::Mttlo_dsp0(MachInst machInst)  : MTOp("mttlo_dsp0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mtthi_dsp0([' xc->setRegOtherThread(INTREG_DSP_HI0,\n                                                                         Rt);\n                                                '],{})

        Mtthi_dsp0::Mtthi_dsp0(MachInst machInst)  : MTOp("mtthi_dsp0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttacx_dsp0([' xc->setRegOtherThread(INTREG_DSP_ACX0,\n                                                                          Rt);\n                                                 '],{})

        Mttacx_dsp0::Mttacx_dsp0(MachInst machInst)  : MTOp("mttacx_dsp0", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttlo_dsp1([' xc->setRegOtherThread(INTREG_DSP_LO1,\n                                                                         Rt);\n                                                '],{})

        Mttlo_dsp1::Mttlo_dsp1(MachInst machInst)  : MTOp("mttlo_dsp1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mtthi_dsp1([' xc->setRegOtherThread(INTREG_DSP_HI1,\n                                                                         Rt);\n                                                '],{})

        Mtthi_dsp1::Mtthi_dsp1(MachInst machInst)  : MTOp("mtthi_dsp1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttacx_dsp1([' xc->setRegOtherThread(INTREG_DSP_ACX1,\n                                                                          Rt);\n                                                 '],{})

        Mttacx_dsp1::Mttacx_dsp1(MachInst machInst)  : MTOp("mttacx_dsp1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttlo_dsp2([' xc->setRegOtherThread(INTREG_DSP_LO2,\n                                                                         Rt);\n                                                '],{})

        Mttlo_dsp2::Mttlo_dsp2(MachInst machInst)  : MTOp("mttlo_dsp2", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mtthi_dsp2([' xc->setRegOtherThread(INTREG_DSP_HI2,\n                                                                         Rt);\n                                                '],{})

        Mtthi_dsp2::Mtthi_dsp2(MachInst machInst)  : MTOp("mtthi_dsp2", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttacx_dsp2([' xc->setRegOtherThread(INTREG_DSP_ACX2,\n                                                                           Rt);\n                                                  '],{})

        Mttacx_dsp2::Mttacx_dsp2(MachInst machInst)  : MTOp("mttacx_dsp2", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttlo_dsp3([' xc->setRegOtherThread(INTREG_DSP_LO3,\n                                                                          Rt);\n                                                 '],{})

        Mttlo_dsp3::Mttlo_dsp3(MachInst machInst)  : MTOp("mttlo_dsp3", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mtthi_dsp3([' xc->setRegOtherThread(INTREG_DSP_HI3,\n                                                                          Rt);\n                                                 '],{})

        Mtthi_dsp3::Mtthi_dsp3(MachInst machInst)  : MTOp("mtthi_dsp3", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttacx_dsp3([' xc->setRegOtherThread(INTREG_DSP_ACX3, Rt);\n                                                  '],{})

        Mttacx_dsp3::Mttacx_dsp3(MachInst machInst)  : MTOp("mttacx_dsp3", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::mttdsp([' xc->setRegOtherThread(INTREG_DSP_CONTROL, Rt); '],{})

        Mttdsp::Mttdsp(MachInst machInst)  : MTOp("mttdsp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// MT_MTTR::mttc1(['\n                                uint64_t data = xc->readRegOtherThread(RD +\n                                                                       FP_Reg_Base);\n                                data = insertBits(data, MT_H ? 63 : 31,\n                                                  MT_H ? 32 : 0, Rt);\n                                xc->setRegOtherThread(RD + FP_Reg_Base,\n                                                      data);\n                            '],{})

        Mttc1::Mttc1(MachInst machInst)  : MTOp("mttc1", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_MTTR::cttc1(['\n                                uint32_t data;\n                                switch (RD) {\n                                  case 25:\n                                    data = (Rt_uw<7:1> << 25) |  // move 31-25\n                                           (FCSR & 0x01000000) | // bit 24\n                                           (FCSR & 0x004FFFFF);  // bit 22-0\n                                    break;\n                                  case 26:\n                                    data = (FCSR & 0xFFFC0000) | // move 31-18\n                                           Rt_uw<17:12> << 12 |  // bit 17-12\n                                           (FCSR & 0x00000F80) << 7 | // bit 11-7\n                                           Rt_uw<6:2> << 2 |     // bit 6-2\n                                           (FCSR & 0x00000002);  // bit 1...0\n                                    break;\n                                  case 28:\n                                    data = (FCSR & 0xFE000000) | // move 31-25\n                                           Rt_uw<2:2> << 24 |    // bit 24\n                                           (FCSR & 0x00FFF000) << 23 | // bit 23-12\n                                           Rt_uw<11:7> << 7 |    // bit 24\n                                           (FCSR & 0x000007E) |\n                                           Rt_uw<1:0>;           // bit 22-0\n                                    break;\n                                  case 31:\n                                    data = Rt_uw;\n                                    break;\n                                  default:\n                                    panic("FP Control Value (%d) "\n                                            "Not Available. Ignoring "\n                                            "Access to Floating Control "\n                                            "S""tatus Register", FS);\n                                }\n                                xc->setRegOtherThread(FLOATREG_FCSR + FP_Reg_Base, data);\n                            '],{})

        Cttc1::Cttc1(MachInst machInst)  : MTOp("cttc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// MT_Control::dvpe(['\n                                        MVPControlReg mvpControl = MVPControl;\n                                        VPEConf0Reg vpeConf0 = VPEConf0;\n                                        Rt = MVPControl;\n                                        if (vpeConf0.mvp == 1)\n                                            mvpControl.evp = 0;\n                                        MVPControl = mvpControl;\n                                    '],{})

        Dvpe::Dvpe(MachInst machInst)  : MTOp("dvpe", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_MVP_CONTROL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_MVP_CONTROL + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_VPE_CONF0 + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_Control::evpe(['\n                                        MVPControlReg mvpControl = MVPControl;\n                                        VPEConf0Reg vpeConf0 = VPEConf0;\n                                        Rt = MVPControl;\n                                        if (vpeConf0.mvp == 1)\n                                            mvpControl.evp = 1;\n                                        MVPControl = mvpControl;\n                                    '],{})

        Evpe::Evpe(MachInst machInst)  : MTOp("evpe", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_MVP_CONTROL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_MVP_CONTROL + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_VPE_CONF0 + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// MT_Control::dmt(['\n                                        VPEControlReg vpeControl = VPEControl;\n                                        Rt = vpeControl;\n                                        vpeControl.te = 0;\n                                        VPEControl = vpeControl;\n                                    '],{})

        Dmt::Dmt(MachInst machInst)  : MTOp("dmt", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_VPE_CONTROL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_VPE_CONTROL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_Control::emt(['\n                                        VPEControlReg vpeControl = VPEControl;\n                                        Rt = vpeControl;\n                                        vpeControl.te = 1;\n                                        VPEControl = vpeControl;\n                                    '],{})

        Emt::Emt(MachInst machInst)  : MTOp("emt", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_VPE_CONTROL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_VPE_CONTROL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Control::di((['\n                                StatusReg status = Status;\n                                ConfigReg config = Config;\n                                // Rev 2.0 or beyond?\n                                if (config.ar >= 1) {\n                                    Rt = status;\n                                    status.ie = 0;\n                                } else {\n                                    // Enable this else branch once we\n                                    // actually set values for Config on init\n                                    fault = new ReservedInstructionFault();\n                                }\n                                Status = status;\n                            '], {}))

        Di::Di(MachInst machInst)  : CP0Control("di", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_STATUS + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_STATUS + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Control::ei((['\n                                StatusReg status = Status;\n                                ConfigReg config = Config;\n                                if (config.ar >= 1) {\n                                    Rt = status;\n                                    status.ie = 1;\n                                } else {\n                                    fault = new ReservedInstructionFault();\n                                }\n                            '], {}))

        Ei::Ei(MachInst machInst)  : CP0Control("ei", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_STATUS + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Control::rdpgpr(['\n                        ConfigReg config = Config;\n                        if (config.ar >= 1) {\n                            // Rev 2 of the architecture\n                            panic("Shadow Sets Not Fully Implemented.\\n");\n                        } else {\n                          fault = new ReservedInstructionFault();\n                        }\n                    '],{})

        Rdpgpr::Rdpgpr(MachInst machInst)  : CP0Control("rdpgpr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG + Misc_Reg_Base;
	flags[IsNonSpeculative] = true;;
        }

// CP0Control::wrpgpr(['\n                        ConfigReg config = Config;\n                        if (config.ar >= 1) {\n                            // Rev 2 of the architecture\n                            panic("Shadow Sets Not Fully Implemented.\\n");\n                        } else {\n                            fault = new ReservedInstructionFault();\n                        }\n                    '],{})

        Wrpgpr::Wrpgpr(MachInst machInst)  : CP0Control("wrpgpr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG + Misc_Reg_Base;
	flags[IsNonSpeculative] = true;;
        }

// CP0Control::eret(['\n                        StatusReg status = Status;\n                        ConfigReg config = Config;\n                        SRSCtlReg srsCtl = SRSCtl;\n                        DPRINTF(MipsPRA,"Restoring PC - %x\\n",EPC);\n                        if (status.erl == 1) {\n                            status.erl = 0;\n                            NPC = ErrorEPC;\n                            // Need to adjust NNPC, otherwise things break\n                            NNPC = ErrorEPC + sizeof(MachInst);\n                        } else {\n                            NPC = EPC;\n                            // Need to adjust NNPC, otherwise things break\n                            NNPC = EPC + sizeof(MachInst);\n                            status.exl = 0;\n                            if (config.ar >=1 &&\n                                    srsCtl.hss > 0 &&\n                                    status.bev == 0) {\n                                srsCtl.css = srsCtl.pss;\n                                //xc->setShadowSet(srsCtl.pss);\n                            }\n                        }\n                        LLFlag = 0;\n                        Status = status;\n                        SRSCtl = srsCtl;\n                    ', 'IsReturn', 'IsSerializing', 'IsERET'],{})

        Eret::Eret(MachInst machInst)  : CP0Control("eret", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_STATUS + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_STATUS + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_SRSCTL + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_SRSCTL + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_EPC + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ERROR_EPC + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_LLFLAG + Misc_Reg_Base;
	flags[IsControl] = true;
	flags[IsERET] = true;
	flags[IsNonSpeculative] = true;
	flags[IsReturn] = true;
	flags[IsSerializing] = true;;
        }

// CP0Control::deret(['\n                        DebugReg debug = Debug;\n                        if (debug.dm == 1) {\n                            debug.dm = 1;\n                            debug.iexi = 0;\n                            NPC = DEPC;\n                        } else {\n                            NPC = NPC;\n                            // Undefined;\n                        }\n                        Debug = debug;\n                    ', 'IsReturn', 'IsSerializing', 'IsERET'],{})

        Deret::Deret(MachInst machInst)  : CP0Control("deret", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_DEBUG + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_DEBUG + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_DEPC + Misc_Reg_Base;
	flags[IsControl] = true;
	flags[IsERET] = true;
	flags[IsNonSpeculative] = true;
	flags[IsReturn] = true;
	flags[IsSerializing] = true;;
        }

// CP0TLB::tlbr(['\n                        MipsISA::PTE *PTEntry =\n                            xc->tcBase()->getITBPtr()->\n                                getEntry(Index & 0x7FFFFFFF);\n                        if (PTEntry == NULL) {\n                            fatal("Invalid PTE Entry received on "\n                                "a TLBR instruction\\n");\n                        }\n                        /* Setup PageMask */\n                        // If 1KB pages are not enabled, a read of PageMask\n                        // must return 0b00 in bits 12, 11\n                        PageMask = (PTEntry->Mask << 11);\n                        /* Setup EntryHi */\n                        EntryHi = ((PTEntry->VPN << 11) | (PTEntry->asid));\n                        /* Setup Entry Lo0 */\n                        EntryLo0 = ((PTEntry->PFN0 << 6) |\n                                    (PTEntry->C0 << 3) |\n                                    (PTEntry->D0 << 2) |\n                                    (PTEntry->V0 << 1) |\n                                    PTEntry->G);\n                        /* Setup Entry Lo1 */\n                        EntryLo1 = ((PTEntry->PFN1 << 6) |\n                                    (PTEntry->C1 << 3) |\n                                    (PTEntry->D1 << 2) |\n                                    (PTEntry->V1 << 1) |\n                                    PTEntry->G);\n                    '],{})

        Tlbr::Tlbr(MachInst machInst)  : CP0Control("tlbr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_INDEX + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_PAGEMASK + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_ENTRYHI + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_ENTRYLO0 + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_ENTRYLO1 + Misc_Reg_Base;
	flags[IsNonSpeculative] = true;;
        }

// CP0TLB::tlbwi(['\n                        //Create PTE\n                        MipsISA::PTE newEntry;\n                        //Write PTE\n                        newEntry.Mask = (Addr)(PageMask >> 11);\n                        newEntry.VPN = (Addr)(EntryHi >> 11);\n                        /*  PageGrain _ ESP                    Config3 _ SP */\n                        if (bits(PageGrain, 28) == 0 || bits(Config3, 4) ==0) {\n                            // If 1KB pages are *NOT* enabled, lowest bits of\n                            // the mask are 0b11 for TLB writes\n                            newEntry.Mask |= 0x3;\n                            // Reset bits 0 and 1 if 1KB pages are not enabled\n                            newEntry.VPN &= 0xFFFFFFFC;\n                        }\n                        newEntry.asid = (uint8_t)(EntryHi & 0xFF);\n\n                        newEntry.PFN0 = (Addr)(EntryLo0 >> 6);\n                        newEntry.PFN1 = (Addr)(EntryLo1 >> 6);\n                        newEntry.D0 = (bool)((EntryLo0 >> 2) & 1);\n                        newEntry.D1 = (bool)((EntryLo1 >> 2) & 1);\n                        newEntry.V1 = (bool)((EntryLo1 >> 1) & 1);\n                        newEntry.V0 = (bool)((EntryLo0 >> 1) & 1);\n                        newEntry.G = (bool)((EntryLo0 & EntryLo1) & 1);\n                        newEntry.C0 = (uint8_t)((EntryLo0 >> 3) & 0x7);\n                        newEntry.C1 = (uint8_t)((EntryLo1 >> 3) & 0x7);\n                        /* Now, compute the AddrShiftAmount and OffsetMask -\n                           TLB optimizations */\n                        /* Addr Shift Amount for 1KB or larger pages */\n                        if ((newEntry.Mask & 0xFFFF) == 3) {\n                            newEntry.AddrShiftAmount = 12;\n                        } else if ((newEntry.Mask & 0xFFFF) == 0x0000) {\n                            newEntry.AddrShiftAmount = 10;\n                        } else if ((newEntry.Mask & 0xFFFC) == 0x000C) {\n                            newEntry.AddrShiftAmount = 14;\n                        } else if ((newEntry.Mask & 0xFFF0) == 0x0030) {\n                            newEntry.AddrShiftAmount = 16;\n                        } else if ((newEntry.Mask & 0xFFC0) == 0x00C0) {\n                            newEntry.AddrShiftAmount = 18;\n                        } else if ((newEntry.Mask & 0xFF00) == 0x0300) {\n                            newEntry.AddrShiftAmount = 20;\n                        } else if ((newEntry.Mask & 0xFC00) == 0x0C00) {\n                            newEntry.AddrShiftAmount = 22;\n                        } else if ((newEntry.Mask & 0xF000) == 0x3000) {\n                            newEntry.AddrShiftAmount = 24;\n                        } else if ((newEntry.Mask & 0xC000) == 0xC000) {\n                            newEntry.AddrShiftAmount = 26;\n                        } else if ((newEntry.Mask & 0x30000) == 0x30000) {\n                            newEntry.AddrShiftAmount = 28;\n                        } else {\n                            fatal("Invalid Mask Pattern Detected!\\n");\n                        }\n                        newEntry.OffsetMask =\n                            (1 << newEntry.AddrShiftAmount) - 1;\n\n                        MipsISA::TLB *Ptr = xc->tcBase()->getITBPtr();\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        int SP = 0;\n                        if (bits(config3, config3.sp) == 1 &&\n                            bits(pageGrain, pageGrain.esp) == 1) {\n                            SP = 1;\n                        }\n                        Ptr->insertAt(newEntry, Index & 0x7FFFFFFF, SP);\n                    '],{})

        Tlbwi::Tlbwi(MachInst machInst)  : CP0Control("tlbwi", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_PAGEMASK + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYHI + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_PAGEGRAIN + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG3 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYLO0 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYLO1 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_INDEX + Misc_Reg_Base;
	flags[IsNonSpeculative] = true;;
        }

// CP0TLB::tlbwr(['\n                        //Create PTE\n                        MipsISA::PTE newEntry;\n                        //Write PTE\n                        newEntry.Mask = (Addr)(PageMask >> 11);\n                        newEntry.VPN = (Addr)(EntryHi >> 11);\n                        /*  PageGrain _ ESP                    Config3 _ SP */\n                        if (bits(PageGrain, 28) == 0 ||\n                            bits(Config3, 4) == 0) {\n                            // If 1KB pages are *NOT* enabled, lowest bits of\n                            // the mask are 0b11 for TLB writes\n                            newEntry.Mask |= 0x3;\n                            // Reset bits 0 and 1 if 1KB pages are not enabled\n                            newEntry.VPN &= 0xFFFFFFFC;\n                        }\n                        newEntry.asid = (uint8_t)(EntryHi & 0xFF);\n\n                        newEntry.PFN0 = (Addr)(EntryLo0 >> 6);\n                        newEntry.PFN1 = (Addr)(EntryLo1 >> 6);\n                        newEntry.D0 = (bool)((EntryLo0 >> 2) & 1);\n                        newEntry.D1 = (bool)((EntryLo1 >> 2) & 1);\n                        newEntry.V1 = (bool)((EntryLo1 >> 1) & 1);\n                        newEntry.V0 = (bool)((EntryLo0 >> 1) & 1);\n                        newEntry.G = (bool)((EntryLo0 & EntryLo1) & 1);\n                        newEntry.C0 = (uint8_t)((EntryLo0 >> 3) & 0x7);\n                        newEntry.C1 = (uint8_t)((EntryLo1 >> 3) & 0x7);\n                        /* Now, compute the AddrShiftAmount and OffsetMask -\n                           TLB optimizations */\n                        /* Addr Shift Amount for 1KB or larger pages */\n                        if ((newEntry.Mask & 0xFFFF) == 3){\n                            newEntry.AddrShiftAmount = 12;\n                        } else if ((newEntry.Mask & 0xFFFF) == 0x0000) {\n                            newEntry.AddrShiftAmount = 10;\n                        } else if ((newEntry.Mask & 0xFFFC) == 0x000C) {\n                            newEntry.AddrShiftAmount = 14;\n                        } else if ((newEntry.Mask & 0xFFF0) == 0x0030) {\n                            newEntry.AddrShiftAmount = 16;\n                        } else if ((newEntry.Mask & 0xFFC0) == 0x00C0) {\n                            newEntry.AddrShiftAmount = 18;\n                        } else if ((newEntry.Mask & 0xFF00) == 0x0300) {\n                            newEntry.AddrShiftAmount = 20;\n                        } else if ((newEntry.Mask & 0xFC00) == 0x0C00) {\n                            newEntry.AddrShiftAmount = 22;\n                        } else if ((newEntry.Mask & 0xF000) == 0x3000) {\n                            newEntry.AddrShiftAmount = 24;\n                        } else if ((newEntry.Mask & 0xC000) == 0xC000) {\n                            newEntry.AddrShiftAmount = 26;\n                        } else if ((newEntry.Mask & 0x30000) == 0x30000) {\n                            newEntry.AddrShiftAmount = 28;\n                        } else {\n                            fatal("Invalid Mask Pattern Detected!\\n");\n                        }\n                        newEntry.OffsetMask =\n                            (1 << newEntry.AddrShiftAmount) - 1;\n\n                        MipsISA::TLB *Ptr = xc->tcBase()->getITBPtr();\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        int SP = 0;\n                        if (bits(config3, config3.sp) == 1 &&\n                            bits(pageGrain, pageGrain.esp) == 1) {\n                            SP = 1;\n                        }\n                        Ptr->insertAt(newEntry, Random, SP);\n                    '],{})

        Tlbwr::Tlbwr(MachInst machInst)  : CP0Control("tlbwr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_PAGEMASK + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYHI + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_PAGEGRAIN + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG3 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYLO0 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYLO1 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CP0_RANDOM + Misc_Reg_Base;
	flags[IsNonSpeculative] = true;;
        }

// CP0TLB::tlbp(['\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        EntryHiReg entryHi = EntryHi;\n                        int tlbIndex;\n                        Addr vpn;\n                        if (pageGrain.esp == 1 && config3.sp ==1) {\n                            vpn = EntryHi >> 11;\n                        } else {\n                            // Mask off lower 2 bits\n                            vpn = ((EntryHi >> 11) & 0xFFFFFFFC);\n                        }\n                        tlbIndex = xc->tcBase()->getITBPtr()->\n                                   probeEntry(vpn, entryHi.asid);\n                        // Check TLB for entry matching EntryHi\n                        if (tlbIndex != -1) {\n                            Index = tlbIndex;\n                        } else {\n                            // else, set Index = 1 << 31\n                            Index = (1 << 31);\n                        }\n                    '],{})

        Tlbp::Tlbp(MachInst machInst)  : CP0Control("tlbp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_CONFIG3 + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_PAGEGRAIN + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = MISCREG_ENTRYHI + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = MISCREG_INDEX + Misc_Reg_Base;
	flags[IsNonSpeculative] = true;;
        }

// CP0Unimpl::wait([],{})

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP1Control::mfc1([' Rt_uw = Fs_uw; '],{})

        Mfc1::Mfc1(MachInst machInst)  : CP1Control("mfc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP1Control::cfc1(['\n                            switch (FS) {\n                              case 0:\n                                Rt = FIR;\n                                break;\n                              case 25:\n                                Rt = (FCSR & 0xFE000000) >> 24 |\n                                     (FCSR & 0x00800000) >> 23;\n                                break;\n                              case 26:\n                                Rt = (FCSR & 0x0003F07C);\n                                break;\n                              case 28:\n                                Rt = (FCSR & 0x00000F80) |\n                                     (FCSR & 0x01000000) >> 21 |\n                                     (FCSR & 0x00000003);\n                                break;\n                              case 31:\n                                Rt = FCSR;\n                                break;\n                              default:\n                                warn("FP Control Value (%d) Not Valid");\n                            }\n                        '],{})

        Cfc1::Cfc1(MachInst machInst)  : CP1Control("cfc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FIR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP1Control::mfhc1([' Rt_uw = Fs_ud<63:32>; '],{})

        Mfhc1::Mfhc1(MachInst machInst)  : CP1Control("mfhc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP1Control::mtc1([' Fs_uw = Rt_uw; '],{})

        Mtc1::Mtc1(MachInst machInst)  : CP1Control("mtc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FS + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP1Control::ctc1(['\n                            switch (FS) {\n                              case 25:\n                                FCSR = (Rt_uw<7:1> << 25) |  // move 31-25\n                                       (FCSR & 0x01000000) | // bit 24\n                                       (FCSR & 0x004FFFFF);  // bit 22-0\n                                break;\n                              case 26:\n                                FCSR = (FCSR & 0xFFFC0000) | // move 31-18\n                                       Rt_uw<17:12> << 12 |  // bit 17-12\n                                       (FCSR & 0x00000F80) << 7 | // bit 11-7\n                                       Rt_uw<6:2> << 2 |     // bit 6-2\n                                       (FCSR & 0x00000002);  // bit 1-0\n                                break;\n                              case 28:\n                                FCSR = (FCSR & 0xFE000000) | // move 31-25\n                                       Rt_uw<2:2> << 24 |    // bit 24\n                                       (FCSR & 0x00FFF000) << 23 | // bit 23-12\n                                       Rt_uw<11:7> << 7 |    // bit 24\n                                       (FCSR & 0x000007E) |\n                                       Rt_uw<1:0>;           // bit 22-0\n                                break;\n                              case 31:\n                                FCSR = Rt_uw;\n                                break;\n\n                              default:\n                                panic("FP Control Value (%d) "\n                                        "Not Available. Ignoring Access "\n                                        "to Floating Control Status "\n                                        "Register", FS);\n                            }\n                        '],{})

        Ctc1::Ctc1(MachInst machInst)  : CP1Control("ctc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP1Control::mthc1(['\n                             uint64_t fs_hi = Rt_uw;\n                             uint64_t fs_lo = Fs_ud & 0x0FFFFFFFF;\n                             Fs_ud = (fs_hi << 32) | fs_lo;\n                        '],{})

        Mthc1::Mthc1(MachInst machInst)  : CP1Control("mthc1", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FS + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// CP1Unimpl::dmfc1([],{})

// CP1Unimpl::dmtc1([],{})

// Unknown::unknown(([], {}))

// Branch::bc1f(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 0;\n                                '],{})

        Bc1f::Bc1f(MachInst machInst)  : Branch("bc1f", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsFloating] = true;;
        }

// Branch::bc1t(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 1;\n                                '],{})

        Bc1t::Bc1t(MachInst machInst)  : Branch("bc1t", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsCondControl] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// Branch::bc1fl(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 0;\n                                ', 'Likely'],{})

        Bc1fl::Bc1fl(MachInst machInst)  : Branch("bc1fl", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsFloating] = true;;
        }

// Branch::bc1tl(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 1;\n                                ', 'Likely'],{})

        Bc1tl::Bc1tl(MachInst machInst)  : Branch("bc1tl", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP1Unimpl::bc1any2([],{})

// CP1Unimpl::bc1any4([],{})

// CP1Unimpl::unknown([],{})

// Unknown::unknown(([], {}))

// FloatOp::add_s([' Fd_sf = Fs_sf + Ft_sf; '],{})

        Add_s::Add_s(MachInst machInst)  : FPOp("add_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::sub_s([' Fd_sf = Fs_sf - Ft_sf; '],{})

        Sub_s::Sub_s(MachInst machInst)  : FPOp("sub_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::mul_s([' Fd_sf = Fs_sf * Ft_sf; '],{})

        Mul_s::Mul_s(MachInst machInst)  : FPOp("mul_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::div_s([' Fd_sf = Fs_sf / Ft_sf; '],{})

        Div_s::Div_s(MachInst machInst)  : FPOp("div_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::sqrt_s([' Fd_sf = sqrt(Fs_sf); '],{})

        Sqrt_s::Sqrt_s(MachInst machInst)  : FPOp("sqrt_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::abs_s([' Fd_sf = fabs(Fs_sf); '],{})

        Abs_s::Abs_s(MachInst machInst)  : FPOp("abs_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::neg_s([' Fd_sf = -Fs_sf; '],{})

        Neg_s::Neg_s(MachInst machInst)  : FPOp("neg_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// BasicOp::mov_s(([' Fd_sf = Fs_sf; '], {}))

        Mov_s::Mov_s(MachInst machInst)  : MipsStaticInst("mov_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatConvertOp::round_l_s([' val = Fs_sf; ', 'ToLong', 'Round'],{})

        Round_l_s::Round_l_s(MachInst machInst)  : FPOp("round_l_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::trunc_l_s([' val = Fs_sf; ', 'ToLong', 'Trunc'],{})

        Trunc_l_s::Trunc_l_s(MachInst machInst)  : FPOp("trunc_l_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::ceil_l_s([' val = Fs_sf;', 'ToLong', 'Ceil'],{})

        Ceil_l_s::Ceil_l_s(MachInst machInst)  : FPOp("ceil_l_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::floor_l_s([' val = Fs_sf; ', 'ToLong', 'Floor'],{})

        Floor_l_s::Floor_l_s(MachInst machInst)  : FPOp("floor_l_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::round_w_s([' val = Fs_sf; ', 'ToWord', 'Round'],{})

        Round_w_s::Round_w_s(MachInst machInst)  : FPOp("round_w_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::trunc_w_s([' val = Fs_sf; ', 'ToWord', 'Trunc'],{})

        Trunc_w_s::Trunc_w_s(MachInst machInst)  : FPOp("trunc_w_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::ceil_w_s([' val = Fs_sf; ', 'ToWord', 'Ceil'],{})

        Ceil_w_s::Ceil_w_s(MachInst machInst)  : FPOp("ceil_w_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::floor_w_s([' val = Fs_sf; ', 'ToWord', 'Floor'],{})

        Floor_w_s::Floor_w_s(MachInst machInst)  : FPOp("floor_w_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::movf_s(['\n                                        Fd = (getCondCode(FCSR,CC) == 0) ?\n                                             Fs : Fd;\n                                    '],{})

        Movf_s::Movf_s(MachInst machInst)  : MipsStaticInst("movf_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// BasicOp::movt_s(['\n                                        Fd = (getCondCode(FCSR,CC) == 1) ?\n                                             Fs : Fd;\n                                    '],{})

        Movt_s::Movt_s(MachInst machInst)  : MipsStaticInst("movt_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::movz_s([' Fd = (Rt == 0) ? Fs : Fd; '],{})

        Movz_s::Movz_s(MachInst machInst)  : MipsStaticInst("movz_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// BasicOp::movn_s([' Fd = (Rt != 0) ? Fs : Fd; '],{})

        Movn_s::Movn_s(MachInst machInst)  : MipsStaticInst("movn_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// FloatOp::recip_s([' Fd = 1 / Fs; '],{})

        Recip_s::Recip_s(MachInst machInst)  : FPOp("recip_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::rsqrt_s([' Fd = 1 / sqrt(Fs); '],{})

        Rsqrt_s::Rsqrt_s(MachInst machInst)  : FPOp("rsqrt_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown([],{})

// CP1Unimpl::unknown(([], {}))

// FloatConvertOp::cvt_d_s([' val = Fs_sf; ', 'ToDouble'],{})

        Cvt_d_s::Cvt_d_s(MachInst machInst)  : FPOp("cvt_d_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::cvt_w_s([' val = Fs_sf; ', 'ToWord'],{})

        Cvt_w_s::Cvt_w_s(MachInst machInst)  : FPOp("cvt_w_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::cvt_l_s([' val = Fs_sf; ', 'ToLong'],{})

        Cvt_l_s::Cvt_l_s(MachInst machInst)  : FPOp("cvt_l_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::cvt_ps_s((['\n                                Fd_ud = (uint64_t) Fs_uw << 32 |\n                                        (uint64_t) Ft_uw;\n                            '], {}))

        Cvt_ps_s::Cvt_ps_s(MachInst machInst)  : FPOp("cvt_ps_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown([],{})

// CP1Unimpl::unknown(([], {}))

// FloatCompareOp::c_f_s([' cond = 0; ', 'SinglePrecision', 'UnorderedFalse'],{})

        C_f_s::C_f_s(MachInst machInst)  : FPCompareOp("c_f_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_un_s([' cond = 0; ', 'SinglePrecision', 'UnorderedTrue'],{})

        C_un_s::C_un_s(MachInst machInst)  : FPCompareOp("c_un_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_eq_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedFalse'],{})

        C_eq_s::C_eq_s(MachInst machInst)  : FPCompareOp("c_eq_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ueq_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedTrue'],{})

        C_ueq_s::C_ueq_s(MachInst machInst)  : FPCompareOp("c_ueq_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_olt_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedFalse'],{})

        C_olt_s::C_olt_s(MachInst machInst)  : FPCompareOp("c_olt_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ult_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedTrue'],{})

        C_ult_s::C_ult_s(MachInst machInst)  : FPCompareOp("c_ult_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ole_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedFalse'],{})

        C_ole_s::C_ole_s(MachInst machInst)  : FPCompareOp("c_ole_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ule_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedTrue'],{})

        C_ule_s::C_ule_s(MachInst machInst)  : FPCompareOp("c_ule_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatCompareOp::c_sf_s([' cond = 0; ', 'SinglePrecision', 'UnorderedFalse', 'QnanException'],{})

        C_sf_s::C_sf_s(MachInst machInst)  : FPCompareOp("c_sf_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ngle_s([' cond = 0; ', 'SinglePrecision', 'UnorderedTrue', 'QnanException'],{})

        C_ngle_s::C_ngle_s(MachInst machInst)  : FPCompareOp("c_ngle_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_seq_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedFalse', 'QnanException'],{})

        C_seq_s::C_seq_s(MachInst machInst)  : FPCompareOp("c_seq_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ngl_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedTrue', 'QnanException'],{})

        C_ngl_s::C_ngl_s(MachInst machInst)  : FPCompareOp("c_ngl_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_lt_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedFalse', 'QnanException'],{})

        C_lt_s::C_lt_s(MachInst machInst)  : FPCompareOp("c_lt_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_nge_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedTrue', 'QnanException'],{})

        C_nge_s::C_nge_s(MachInst machInst)  : FPCompareOp("c_nge_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_le_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedFalse', 'QnanException'],{})

        C_le_s::C_le_s(MachInst machInst)  : FPCompareOp("c_le_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ngt_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedTrue', 'QnanException'],{})

        C_ngt_s::C_ngt_s(MachInst machInst)  : FPCompareOp("c_ngt_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// FloatOp::add_d([' Fd_df = Fs_df + Ft_df; '],{})

        Add_d::Add_d(MachInst machInst)  : FPOp("add_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::sub_d([' Fd_df = Fs_df - Ft_df; '],{})

        Sub_d::Sub_d(MachInst machInst)  : FPOp("sub_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::mul_d([' Fd_df = Fs_df * Ft_df; '],{})

        Mul_d::Mul_d(MachInst machInst)  : FPOp("mul_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::div_d([' Fd_df = Fs_df / Ft_df; '],{})

        Div_d::Div_d(MachInst machInst)  : FPOp("div_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::sqrt_d([' Fd_df = sqrt(Fs_df); '],{})

        Sqrt_d::Sqrt_d(MachInst machInst)  : FPOp("sqrt_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::abs_d([' Fd_df = fabs(Fs_df); '],{})

        Abs_d::Abs_d(MachInst machInst)  : FPOp("abs_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::neg_d([' Fd_df = -1 * Fs_df; '],{})

        Neg_d::Neg_d(MachInst machInst)  : FPOp("neg_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// BasicOp::mov_d(([' Fd_df = Fs_df; '], {}))

        Mov_d::Mov_d(MachInst machInst)  : MipsStaticInst("mov_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatConvertOp::round_l_d([' val = Fs_df; ', 'ToLong', 'Round'],{})

        Round_l_d::Round_l_d(MachInst machInst)  : FPOp("round_l_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::trunc_l_d([' val = Fs_df; ', 'ToLong', 'Trunc'],{})

        Trunc_l_d::Trunc_l_d(MachInst machInst)  : FPOp("trunc_l_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::ceil_l_d([' val = Fs_df; ', 'ToLong', 'Ceil'],{})

        Ceil_l_d::Ceil_l_d(MachInst machInst)  : FPOp("ceil_l_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::floor_l_d([' val = Fs_df; ', 'ToLong', 'Floor'],{})

        Floor_l_d::Floor_l_d(MachInst machInst)  : FPOp("floor_l_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::round_w_d([' val = Fs_df; ', 'ToWord', 'Round'],{})

        Round_w_d::Round_w_d(MachInst machInst)  : FPOp("round_w_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::trunc_w_d([' val = Fs_df; ', 'ToWord', 'Trunc'],{})

        Trunc_w_d::Trunc_w_d(MachInst machInst)  : FPOp("trunc_w_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::ceil_w_d([' val = Fs_df; ', 'ToWord', 'Ceil'],{})

        Ceil_w_d::Ceil_w_d(MachInst machInst)  : FPOp("ceil_w_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::floor_w_d([' val = Fs_df; ', 'ToWord', 'Floor'],{})

        Floor_w_d::Floor_w_d(MachInst machInst)  : FPOp("floor_w_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::movf_d(['\n                                        Fd_df = (getCondCode(FCSR,CC) == 0) ?\n                                                       Fs_df : Fd_df;\n                                    '],{})

        Movf_d::Movf_d(MachInst machInst)  : MipsStaticInst("movf_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// BasicOp::movt_d(['\n                                        Fd_df = (getCondCode(FCSR,CC) == 1) ?\n                                                       Fs_df : Fd_df;\n                                    '],{})

        Movt_d::Movt_d(MachInst machInst)  : MipsStaticInst("movt_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::movz_d(['\n                                    Fd_df = (Rt == 0) ? Fs_df : Fd_df;\n                                '],{})

        Movz_d::Movz_d(MachInst machInst)  : MipsStaticInst("movz_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// BasicOp::movn_d(['\n                                    Fd_df = (Rt != 0) ? Fs_df : Fd_df;\n                                '],{})

        Movn_d::Movn_d(MachInst machInst)  : MipsStaticInst("movn_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// FloatOp::recip_d([' Fd_df = 1 / Fs_df; '],{})

        Recip_d::Recip_d(MachInst machInst)  : FPOp("recip_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatOp::rsqrt_d([' Fd_df = 1 / sqrt(Fs_df); '],{})

        Rsqrt_d::Rsqrt_d(MachInst machInst)  : FPOp("rsqrt_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown([],{})

// FloatConvertOp::cvt_s_d([' val = Fs_df; ', 'ToSingle'],{})

        Cvt_s_d::Cvt_s_d(MachInst machInst)  : FPOp("cvt_s_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::cvt_w_d([' val = Fs_df; ', 'ToWord'],{})

        Cvt_w_d::Cvt_w_d(MachInst machInst)  : FPOp("cvt_w_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::cvt_l_d([' val = Fs_df; ', 'ToLong'],{})

        Cvt_l_d::Cvt_l_d(MachInst machInst)  : FPOp("cvt_l_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown(([], {}))

// FloatCompareOp::c_f_d([' cond = 0; ', 'DoublePrecision', 'UnorderedFalse'],{})

        C_f_d::C_f_d(MachInst machInst)  : FPCompareOp("c_f_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_un_d([' cond = 0; ', 'DoublePrecision', 'UnorderedTrue'],{})

        C_un_d::C_un_d(MachInst machInst)  : FPCompareOp("c_un_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_eq_d([' cond = (Fs_df == Ft_df); ', 'UnorderedFalse'],{})

        C_eq_d::C_eq_d(MachInst machInst)  : FPCompareOp("c_eq_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ueq_d([' cond = (Fs_df == Ft_df); ', 'UnorderedTrue'],{})

        C_ueq_d::C_ueq_d(MachInst machInst)  : FPCompareOp("c_ueq_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_olt_d([' cond = (Fs_df < Ft_df); ', 'UnorderedFalse'],{})

        C_olt_d::C_olt_d(MachInst machInst)  : FPCompareOp("c_olt_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ult_d([' cond = (Fs_df < Ft_df); ', 'UnorderedTrue'],{})

        C_ult_d::C_ult_d(MachInst machInst)  : FPCompareOp("c_ult_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ole_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedFalse'],{})

        C_ole_d::C_ole_d(MachInst machInst)  : FPCompareOp("c_ole_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ule_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedTrue'],{})

        C_ule_d::C_ule_d(MachInst machInst)  : FPCompareOp("c_ule_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatCompareOp::c_sf_d([' cond = 0; ', 'DoublePrecision', 'UnorderedFalse', 'QnanException'],{})

        C_sf_d::C_sf_d(MachInst machInst)  : FPCompareOp("c_sf_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ngle_d([' cond = 0; ', 'DoublePrecision', 'UnorderedTrue', 'QnanException'],{})

        C_ngle_d::C_ngle_d(MachInst machInst)  : FPCompareOp("c_ngle_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_seq_d([' cond = (Fs_df == Ft_df); ', 'UnorderedFalse', 'QnanException'],{})

        C_seq_d::C_seq_d(MachInst machInst)  : FPCompareOp("c_seq_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ngl_d([' cond = (Fs_df == Ft_df); ', 'UnorderedTrue', 'QnanException'],{})

        C_ngl_d::C_ngl_d(MachInst machInst)  : FPCompareOp("c_ngl_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_lt_d([' cond = (Fs_df < Ft_df); ', 'UnorderedFalse', 'QnanException'],{})

        C_lt_d::C_lt_d(MachInst machInst)  : FPCompareOp("c_lt_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_nge_d([' cond = (Fs_df < Ft_df); ', 'UnorderedTrue', 'QnanException'],{})

        C_nge_d::C_nge_d(MachInst machInst)  : FPCompareOp("c_nge_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_le_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedFalse', 'QnanException'],{})

        C_le_d::C_le_d(MachInst machInst)  : FPCompareOp("c_le_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// FloatCompareOp::c_ngt_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedTrue', 'QnanException'],{})

        C_ngt_d::C_ngt_d(MachInst machInst)  : FPCompareOp("c_ngt_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// FloatConvertOp::cvt_s_w([' val = Fs_sw; ', 'ToSingle'],{})

        Cvt_s_w::Cvt_s_w(MachInst machInst)  : FPOp("cvt_s_w", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::cvt_d_w([' val = Fs_sw; ', 'ToDouble'],{})

        Cvt_d_w::Cvt_d_w(MachInst machInst)  : FPOp("cvt_d_w", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::cvt_ps_w(([], {}))

// CP1Unimpl::unknown(([], {}))

// FloatConvertOp::cvt_s_l([' val = Fs_sd; ', 'ToSingle'],{})

        Cvt_s_l::Cvt_s_l(MachInst machInst)  : FPOp("cvt_s_l", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatConvertOp::cvt_d_l([' val = Fs_sd; ', 'ToDouble'],{})

        Cvt_d_l::Cvt_d_l(MachInst machInst)  : FPOp("cvt_d_l", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::cvt_ps_l(([], {}))

// CP1Unimpl::unknown(([], {}))

// Float64Op::add_ps(['\n                                    Fd1_sf = Fs1_sf + Ft2_sf;\n                                    Fd2_sf = Fs2_sf + Ft2_sf;\n                                '],{})

        Add_ps::Add_ps(MachInst machInst)  : MipsStaticInst("add_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::sub_ps(['\n                                    Fd1_sf = Fs1_sf - Ft2_sf;\n                                    Fd2_sf = Fs2_sf - Ft2_sf;\n                                '],{})

        Sub_ps::Sub_ps(MachInst machInst)  : MipsStaticInst("sub_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::mul_ps(['\n                                    Fd1_sf = Fs1_sf * Ft2_sf;\n                                    Fd2_sf = Fs2_sf * Ft2_sf;\n                                '],{})

        Mul_ps::Mul_ps(MachInst machInst)  : MipsStaticInst("mul_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::abs_ps(['\n                                    Fd1_sf = fabs(Fs1_sf);\n                                    Fd2_sf = fabs(Fs2_sf);\n                                '],{})

        Abs_ps::Abs_ps(MachInst machInst)  : MipsStaticInst("abs_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::mov_ps(['\n                                    Fd1_sf = Fs1_sf;\n                                    Fd2_sf = Fs2_sf;\n                                '],{})

        Mov_ps::Mov_ps(MachInst machInst)  : MipsStaticInst("mov_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::neg_ps(['\n                                    Fd1_sf = -(Fs1_sf);\n                                    Fd2_sf = -(Fs2_sf);\n                                '],{})

        Neg_ps::Neg_ps(MachInst machInst)  : MipsStaticInst("neg_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// Float64Op::movf_ps(['\n                                        Fd1 = (getCondCode(FCSR, CC) == 0) ?\n                                            Fs1 : Fd1;\n                                        Fd2 = (getCondCode(FCSR, CC+1) == 0) ?\n                                            Fs2 : Fd2;\n                                    '],{})

        Movf_ps::Movf_ps(MachInst machInst)  : MipsStaticInst("movf_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FD+1 + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::movt_ps(['\n                                        Fd2 = (getCondCode(FCSR, CC) == 1) ?\n                                            Fs1 : Fd1;\n                                        Fd2 = (getCondCode(FCSR, CC+1) == 1) ?\n                                            Fs2 : Fd2;\n                                    '],{})

        Movt_ps::Movt_ps(MachInst machInst)  : MipsStaticInst("movt_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FD+1 + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// Float64Op::movz_ps(['\n                                    Fd1 = (getCondCode(FCSR, CC) == 0) ?\n                                        Fs1 : Fd1;\n                                    Fd2 = (getCondCode(FCSR, CC) == 0) ?\n                                        Fs2 : Fd2;\n                                '],{})

        Movz_ps::Movz_ps(MachInst machInst)  : MipsStaticInst("movz_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FD+1 + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::movn_ps(['\n                                    Fd1 = (getCondCode(FCSR, CC) == 1) ?\n                                        Fs1 : Fd1;\n                                    Fd2 = (getCondCode(FCSR, CC) == 1) ?\n                                        Fs2 : Fd2;\n                                '],{})

        Movn_ps::Movn_ps(MachInst machInst)  : MipsStaticInst("movn_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FD+1 + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// FloatOp::cvt_s_pu(([' Fd_sf = Fs2_sf; '], {}))

        Cvt_s_pu::Cvt_s_pu(MachInst machInst)  : FPOp("cvt_s_pu", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown(([], {}))

// FloatOp::cvt_s_pl(([' Fd_sf = Fs1_sf; '], {}))

        Cvt_s_pl::Cvt_s_pl(MachInst machInst)  : FPOp("cvt_s_pl", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::pll(['\n                                    Fd_ud = (uint64_t)Fs1_uw << 32 | Ft1_uw;\n                                '],{})

        Pll::Pll(MachInst machInst)  : MipsStaticInst("pll", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::plu(['\n                                    Fd_ud = (uint64_t)Fs1_uw << 32 | Ft2_uw;\n                                '],{})

        Plu::Plu(MachInst machInst)  : MipsStaticInst("plu", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::pul(['\n                                    Fd_ud = (uint64_t)Fs2_uw << 32 | Ft1_uw;\n                                '],{})

        Pul::Pul(MachInst machInst)  : MipsStaticInst("pul", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Float64Op::puu(['\n                                    Fd_ud = (uint64_t)Fs2_uw << 32 | Ft2_uw;\n                                '],{})

        Puu::Puu(MachInst machInst)  : MipsStaticInst("puu", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// CP1Unimpl::unknown(([], {}))

// FloatPSCompareOp::c_f_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedFalse'],{})

        C_f_ps::C_f_ps(MachInst machInst)  : FPCompareOp("c_f_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_un_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedTrue'],{})

        C_un_ps::C_un_ps(MachInst machInst)  : FPCompareOp("c_un_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_eq_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedFalse'],{})

        C_eq_ps::C_eq_ps(MachInst machInst)  : FPCompareOp("c_eq_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ueq_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedTrue'],{})

        C_ueq_ps::C_ueq_ps(MachInst machInst)  : FPCompareOp("c_ueq_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_olt_ps([' cond1 = (Fs1_sf < Ft1_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedFalse'],{})

        C_olt_ps::C_olt_ps(MachInst machInst)  : FPCompareOp("c_olt_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ult_ps([' cond1 = (Fs_sf < Ft_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedTrue'],{})

        C_ult_ps::C_ult_ps(MachInst machInst)  : FPCompareOp("c_ult_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ole_ps([' cond1 = (Fs_sf <= Ft_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedFalse'],{})

        C_ole_ps::C_ole_ps(MachInst machInst)  : FPCompareOp("c_ole_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ule_ps([' cond1 = (Fs1_sf <= Ft1_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedTrue'],{})

        C_ule_ps::C_ule_ps(MachInst machInst)  : FPCompareOp("c_ule_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatPSCompareOp::c_sf_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedFalse', 'QnanException'],{})

        C_sf_ps::C_sf_ps(MachInst machInst)  : FPCompareOp("c_sf_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ngle_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedTrue', 'QnanException'],{})

        C_ngle_ps::C_ngle_ps(MachInst machInst)  : FPCompareOp("c_ngle_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_seq_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedFalse', 'QnanException'],{})

        C_seq_ps::C_seq_ps(MachInst machInst)  : FPCompareOp("c_seq_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ngl_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedTrue', 'QnanException'],{})

        C_ngl_ps::C_ngl_ps(MachInst machInst)  : FPCompareOp("c_ngl_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_lt_ps([' cond1 = (Fs1_sf < Ft1_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedFalse', 'QnanException'],{})

        C_lt_ps::C_lt_ps(MachInst machInst)  : FPCompareOp("c_lt_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_nge_ps([' cond1 = (Fs1_sf < Ft1_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedTrue', 'QnanException'],{})

        C_nge_ps::C_nge_ps(MachInst machInst)  : FPCompareOp("c_nge_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_le_ps([' cond1 = (Fs1_sf <= Ft1_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedFalse', 'QnanException'],{})

        C_le_ps::C_le_ps(MachInst machInst)  : FPCompareOp("c_le_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatPSCompareOp::c_ngt_ps([' cond1 = (Fs1_sf <= Ft1_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedTrue', 'QnanException'],{})

        C_ngt_ps::C_ngt_ps(MachInst machInst)  : FPCompareOp("c_ngt_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FLOATREG_FCSR + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP2Unimpl::mfc2([],{})

// CP2Unimpl::cfc2([],{})

// CP2Unimpl::mfhc2([],{})

// CP2Unimpl::mtc2([],{})

// CP2Unimpl::ctc2([],{})

// CP2Unimpl::mftc2([],{})

// CP2Unimpl::unknown([],{})

// CP2Unimpl::bc2f([],{})

// CP2Unimpl::bc2t([],{})

// CP2Unimpl::unknown([],{})

// CP2Unimpl::bc2fl([],{})

// CP2Unimpl::bc2tl([],{})

// CP2Unimpl::unknown([],{})

// CP2Unimpl::unknown([],{})

// CP2Unimpl::unknown([],{})

// CP2Unimpl::unknown([],{})

// LoadIndexedMemory::lwxc1([' Fd_uw = Mem_uw; '],{})

    Lwxc1::Lwxc1(ExtMachInst machInst)
         : Memory("lwxc1", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadIndexedMemory::ldxc1([' Fd_ud = Mem_ud; '],{})

    Ldxc1::Ldxc1(ExtMachInst machInst)
         : Memory("ldxc1", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadIndexedMemory::luxc1([' Fd_ud = Mem_ud; ', ' EA = (Rs + Rt) & ~7; '],{})

    Luxc1::Luxc1(ExtMachInst machInst)
         : Memory("luxc1", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// Unknown::unknown(([], {}))

// StoreIndexedMemory::swxc1([' Mem_uw = Fs_uw; '],{})

    Swxc1::Swxc1(ExtMachInst machInst)
         : Memory("swxc1", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreIndexedMemory::sdxc1([' Mem_ud = Fs_ud; '],{})

    Sdxc1::Sdxc1(ExtMachInst machInst)
         : Memory("sdxc1", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreIndexedMemory::suxc1([' Mem_ud = Fs_ud; ', ' EA = (Rs + Rt) & ~7; '],{})

    Suxc1::Suxc1(ExtMachInst machInst)
         : Memory("suxc1", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsFloating] = true;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// Prefetch::prefx(([' EA = Rs + Rt; '], {}))

    Prefx::Prefx(ExtMachInst machInst)
         : Memory("prefx", machInst, IntAluOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	memAccessFlags = Request::PREFETCH;;
    }

// Unknown::unknown(([], {}))

// Float64Op::alnv_ps((['\n                    if (Rs<2:0> == 0) {\n                        Fd_ud = Fs_ud;\n                    } else if (Rs<2:0> == 4) {\n                        if (GuestByteOrder == BigEndianByteOrder)\n                            Fd_ud = Fs_ud<31:0> << 32 | Ft_ud<63:32>;\n                        else\n                            Fd_ud = Ft_ud<31:0> << 32 | Fs_ud<63:32>;\n                    } else {\n                        Fd_ud = Fd_ud;\n                    }\n                '], {}))

        Alnv_ps::Alnv_ps(MachInst machInst)  : MipsStaticInst("alnv_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = FD + FP_Reg_Base;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// FloatAccOp::madd_s([' Fd_sf = (Fs_sf * Ft_sf) + Fr_sf; '],{})

        Madd_s::Madd_s(MachInst machInst)  : FPOp("madd_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::madd_d([' Fd_df = (Fs_df * Ft_df) + Fr_df; '],{})

        Madd_d::Madd_d(MachInst machInst)  : FPOp("madd_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::madd_ps(['\n                        Fd1_sf = (Fs1_df * Ft1_df) + Fr1_df;\n                        Fd2_sf = (Fs2_df * Ft2_df) + Fr2_df;\n                    '],{})

        Madd_ps::Madd_ps(MachInst machInst)  : FPOp("madd_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatAccOp::msub_s([' Fd_sf = (Fs_sf * Ft_sf) - Fr_sf; '],{})

        Msub_s::Msub_s(MachInst machInst)  : FPOp("msub_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::msub_d([' Fd_df = (Fs_df * Ft_df) - Fr_df; '],{})

        Msub_d::Msub_d(MachInst machInst)  : FPOp("msub_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::msub_ps(['\n                        Fd1_sf = (Fs1_df * Ft1_df) - Fr1_df;\n                        Fd2_sf = (Fs2_df * Ft2_df) - Fr2_df;\n                    '],{})

        Msub_ps::Msub_ps(MachInst machInst)  : FPOp("msub_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatAccOp::nmadd_s([' Fd_sf = (-1 * Fs_sf * Ft_sf) - Fr_sf; '],{})

        Nmadd_s::Nmadd_s(MachInst machInst)  : FPOp("nmadd_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::nmadd_d([' Fd_df = (-1 * Fs_df * Ft_df) - Fr_df; '],{})

        Nmadd_d::Nmadd_d(MachInst machInst)  : FPOp("nmadd_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::nmadd_ps(['\n                        Fd1_sf = -((Fs1_df * Ft1_df) + Fr1_df);\n                        Fd2_sf = -((Fs2_df * Ft2_df) + Fr2_df);\n                    '],{})

        Nmadd_ps::Nmadd_ps(MachInst machInst)  : FPOp("nmadd_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// FloatAccOp::nmsub_s([' Fd_sf = (-1 * Fs_sf * Ft_sf) + Fr_sf; '],{})

        Nmsub_s::Nmsub_s(MachInst machInst)  : FPOp("nmsub_s", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::nmsub_d([' Fd_df = (-1 * Fs_df * Ft_df) + Fr_df; '],{})

        Nmsub_d::Nmsub_d(MachInst machInst)  : FPOp("nmsub_d", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// FloatAccOp::nmsub_ps(['\n                        Fd1_sf = -((Fs1_df * Ft1_df) - Fr1_df);\n                        Fd2_sf = -((Fs2_df * Ft2_df) - Fr2_df);\n                    '],{})

        Nmsub_ps::Nmsub_ps(MachInst machInst)  : FPOp("nmsub_ps", machInst, FloatAddOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = FD + FP_Reg_Base;
	_numFPDestRegs++;
	_destRegIdx[_numDestRegs++] = FD+1 + FP_Reg_Base;
	_numFPDestRegs++;
	_srcRegIdx[_numSrcRegs++] = FS + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FS+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FT+1 + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR + FP_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = FR+1 + FP_Reg_Base;
	flags[IsFloating] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Branch::beql([' cond = (Rs_sw == Rt_sw); ', 'Likely'],{})

        Beql::Beql(MachInst machInst)  : Branch("beql", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bnel([' cond = (Rs_sw != Rt_sw); ', 'Likely'],{})

        Bnel::Bnel(MachInst machInst)  : Branch("bnel", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::blezl([' cond = (Rs_sw <= 0); ', 'Likely'],{})

        Blezl::Blezl(MachInst machInst)  : Branch("blezl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Branch::bgtzl([' cond = (Rs_sw > 0); ', 'Likely'],{})

        Bgtzl::Bgtzl(MachInst machInst)  : Branch("bgtzl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsCondControl] = true;
	flags[IsCondDelaySlot] = true;
	flags[IsControl] = true;
	flags[IsDirectControl] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// IntOp::mul((['\n                    int64_t temp1 = Rs_sd * Rt_sd;\n                    Rd_sw = temp1<31:0>;\n                ', 'IntMultOp'], {}))

        Mul::Mul(MachInst machInst)  : IntOp("mul", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// HiLoRdSelValOp::madd(['\n                        val = ((int64_t)HI_RD_SEL << 32 | LO_RD_SEL) +\n                              (Rs_sd * Rt_sd);\n                    ', 'IntMultOp'],{})

        Madd::Madd(MachInst machInst)  : HiLoRdSelOp("madd", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoRdSelValOp::maddu(['\n                        val = ((uint64_t)HI_RD_SEL << 32 | LO_RD_SEL) +\n                              (Rs_ud * Rt_ud);\n                    ', 'IntMultOp'],{})

        Maddu::Maddu(MachInst machInst)  : HiLoRdSelOp("maddu", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoRdSelValOp::msub(['\n                        val = ((int64_t)HI_RD_SEL << 32 | LO_RD_SEL) -\n                              (Rs_sd * Rt_sd);\n                    ', 'IntMultOp'],{})

        Msub::Msub(MachInst machInst)  : HiLoRdSelOp("msub", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// HiLoRdSelValOp::msubu(['\n                        val = ((uint64_t)HI_RD_SEL << 32 | LO_RD_SEL) -\n                              (Rs_ud * Rt_ud);\n                    ', 'IntMultOp'],{})

        Msubu::Msubu(MachInst machInst)  : HiLoRdSelOp("msubu", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// BasicOp::clz(['\n                        int cnt = 32;\n                        for (int idx = 31; idx >= 0; idx--) {\n                            if (Rs<idx:idx> == 1) {\n                                cnt = 31 - idx;\n                                break;\n                            }\n                        }\n                        Rd_uw = cnt;\n                    '],{})

        Clz::Clz(MachInst machInst)  : MipsStaticInst("clz", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// BasicOp::clo(['\n                        int cnt = 32;\n                        for (int idx = 31; idx >= 0; idx--) {\n                            if (Rs<idx:idx> == 0) {\n                                cnt = 31 - idx;\n                                break;\n                            }\n                        }\n                        Rd_uw = cnt;\n                    '],{})

        Clo::Clo(MachInst machInst)  : MipsStaticInst("clo", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// FailUnimpl::sdbbp(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::ext([' Rt_uw = bits(Rs_uw, MSB+LSB, LSB); '],{})

        Ext::Ext(MachInst machInst)  : MipsStaticInst("ext", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// BasicOp::ins(['\n                        Rt_uw = bits(Rt_uw, 31, MSB+1) << (MSB+1) |\n                                bits(Rs_uw, MSB-LSB, 0) << LSB |\n                                bits(Rt_uw, LSB-1, 0);\n                    '],{})

        Ins::Ins(MachInst machInst)  : MipsStaticInst("ins", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// MT_Control::fork(['\n                        forkThread(xc->tcBase(), fault, RD, Rs, Rt);\n                    ', 'UserMode'],{})

        Fork::Fork(MachInst machInst)  : MTUserModeOp("fork", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// MT_Control::yield(['\n                        Rd_sw = yieldThread(xc->tcBase(), fault, Rs_sw,\n                                            YQMask);\n                    ', 'UserMode'],{})

        Yield::Yield(MachInst machInst)  : MTUserModeOp("yield", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = MISCREG_YQMASK + Misc_Reg_Base;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;
	flags[IsNonSpeculative] = true;;
        }

// LoadIndexedMemory::lwx([' Rd_sw = Mem_sw; '],{})

    Lwx::Lwx(ExtMachInst machInst)
         : Memory("lwx", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadIndexedMemory::lhx([' Rd_sw = Mem_sh; '],{})

    Lhx::Lhx(ExtMachInst machInst)
         : Memory("lhx", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadIndexedMemory::lbux([' Rd_uw = Mem_ub; '],{})

    Lbux::Lbux(ExtMachInst machInst)
         : Memory("lbux", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsIndexed] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::insv((['\n                    int pos = dspctl<5:0>;\n                    int size = dspctl<12:7> - 1;\n                    Rt_uw = insertBits(Rt_uw, pos+size,\n                                       pos, Rs_uw<size:0>);\n                '], {}))

        Insv::Insv(MachInst machInst)  : DspIntOp("insv", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::addu_qb(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Addu_qb::Addu_qb(MachInst machInst)  : DspIntOp("addu_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subu_qb(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Subu_qb::Subu_qb(MachInst machInst)  : DspIntOp("subu_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addu_s_qb(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Addu_s_qb::Addu_s_qb(MachInst machInst)  : DspIntOp("addu_s_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subu_s_qb(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Subu_s_qb::Subu_s_qb(MachInst machInst)  : DspIntOp("subu_s_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::muleu_s_ph_qbl(['\n                                Rd_uw = dspMuleu(Rs_uw, Rt_uw,\n                                                 MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        Muleu_s_ph_qbl::Muleu_s_ph_qbl(MachInst machInst)  : DspIntOp("muleu_s_ph_qbl", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::muleu_s_ph_qbr(['\n                                Rd_uw = dspMuleu(Rs_uw, Rt_uw,\n                                                 MODE_R, &dspctl);\n                            ', 'IntMultOp'],{})

        Muleu_s_ph_qbr::Muleu_s_ph_qbr(MachInst machInst)  : DspIntOp("muleu_s_ph_qbr", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::addu_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Addu_ph::Addu_ph(MachInst machInst)  : DspIntOp("addu_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subu_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Subu_ph::Subu_ph(MachInst machInst)  : DspIntOp("subu_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addq_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        Addq_ph::Addq_ph(MachInst machInst)  : DspIntOp("addq_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subq_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        Subq_ph::Subq_ph(MachInst machInst)  : DspIntOp("subq_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addu_s_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Addu_s_ph::Addu_s_ph(MachInst machInst)  : DspIntOp("addu_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subu_s_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Subu_s_ph::Subu_s_ph(MachInst machInst)  : DspIntOp("subu_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addq_s_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        Addq_s_ph::Addq_s_ph(MachInst machInst)  : DspIntOp("addq_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subq_s_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        Subq_s_ph::Subq_s_ph(MachInst machInst)  : DspIntOp("subq_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::addsc(['\n                                int64_t dresult;\n                                dresult = Rs_ud + Rt_ud;\n                                Rd_sw = dresult<31:0>;\n                                dspctl = insertBits(dspctl, 13, 13,\n                                                    dresult<32:32>);\n                            '],{})

        Addsc::Addsc(MachInst machInst)  : DspIntOp("addsc", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addwc(['\n                                int64_t dresult;\n                                dresult = Rs_sd + Rt_sd + dspctl<13:13>;\n                                Rd_sw = dresult<31:0>;\n                                if (dresult<32:32> != dresult<31:31>)\n                                    dspctl = insertBits(dspctl, 20, 20, 1);\n                            '],{})

        Addwc::Addwc(MachInst machInst)  : DspIntOp("addwc", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::modsub(['\n                                Rd_sw = (Rs_sw == 0) ? Rt_sw<23:8> :\n                                                       Rs_sw - Rt_sw<7:0>;\n                            '],{})

        Modsub::Modsub(MachInst machInst)  : DspIntOp("modsub", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::raddu_w_qb(['\n                                Rd_uw = Rs_uw<31:24> + Rs_uw<23:16> +\n                                        Rs_uw<15:8> + Rs_uw<7:0>;\n                            '],{})

        Raddu_w_qb::Raddu_w_qb(MachInst machInst)  : DspIntOp("raddu_w_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addq_s_w(['\n                                Rd_sw = dspAdd(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        Addq_s_w::Addq_s_w(MachInst machInst)  : DspIntOp("addq_s_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subq_s_w(['\n                                Rd_sw = dspSub(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        Subq_s_w::Subq_s_w(MachInst machInst)  : DspIntOp("subq_s_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::muleq_s_w_phl(['\n                                Rd_sw = dspMuleq(Rs_sw, Rt_sw,\n                                                 MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        Muleq_s_w_phl::Muleq_s_w_phl(MachInst machInst)  : DspIntOp("muleq_s_w_phl", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::muleq_s_w_phr(['\n                                Rd_sw = dspMuleq(Rs_sw, Rt_sw,\n                                                 MODE_R, &dspctl);\n                            ', 'IntMultOp'],{})

        Muleq_s_w_phr::Muleq_s_w_phr(MachInst machInst)  : DspIntOp("muleq_s_w_phr", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::mulq_s_ph(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                SATURATE, NOROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        Mulq_s_ph::Mulq_s_ph(MachInst machInst)  : DspIntOp("mulq_s_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::mulq_rs_ph(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                SATURATE, ROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        Mulq_rs_ph::Mulq_rs_ph(MachInst machInst)  : DspIntOp("mulq_rs_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::cmpu_eq_qb(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                       UNSIGNED, CMP_EQ, &dspctl);\n                            '],{})

        Cmpu_eq_qb::Cmpu_eq_qb(MachInst machInst)  : DspIntOp("cmpu_eq_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpu_lt_qb(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                       UNSIGNED, CMP_LT, &dspctl);\n                            '],{})

        Cmpu_lt_qb::Cmpu_lt_qb(MachInst machInst)  : DspIntOp("cmpu_lt_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpu_le_qb(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                       UNSIGNED, CMP_LE, &dspctl);\n                            '],{})

        Cmpu_le_qb::Cmpu_le_qb(MachInst machInst)  : DspIntOp("cmpu_le_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::pick_qb(['\n                                Rd_uw = dspPick(Rs_uw, Rt_uw,\n                                                SIMD_FMT_QB, &dspctl);\n                            '],{})

        Pick_qb::Pick_qb(MachInst machInst)  : DspIntOp("pick_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpgu_eq_qb(['\n                                Rd_uw = dspCmpg(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                UNSIGNED, CMP_EQ );\n                            '],{})

        Cmpgu_eq_qb::Cmpgu_eq_qb(MachInst machInst)  : DspIntOp("cmpgu_eq_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpgu_lt_qb(['\n                                Rd_uw = dspCmpg(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                UNSIGNED, CMP_LT);\n                            '],{})

        Cmpgu_lt_qb::Cmpgu_lt_qb(MachInst machInst)  : DspIntOp("cmpgu_lt_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpgu_le_qb(['\n                                Rd_uw = dspCmpg(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                UNSIGNED, CMP_LE);\n                            '],{})

        Cmpgu_le_qb::Cmpgu_le_qb(MachInst machInst)  : DspIntOp("cmpgu_le_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::cmp_eq_ph(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                       SIGNED, CMP_EQ, &dspctl);\n                            '],{})

        Cmp_eq_ph::Cmp_eq_ph(MachInst machInst)  : DspIntOp("cmp_eq_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmp_lt_ph(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                       SIGNED, CMP_LT, &dspctl);\n                            '],{})

        Cmp_lt_ph::Cmp_lt_ph(MachInst machInst)  : DspIntOp("cmp_lt_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmp_le_ph(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                       SIGNED, CMP_LE, &dspctl);\n                            '],{})

        Cmp_le_ph::Cmp_le_ph(MachInst machInst)  : DspIntOp("cmp_le_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::pick_ph(['\n                                Rd_uw = dspPick(Rs_uw, Rt_uw,\n                                                SIMD_FMT_PH, &dspctl);\n                            '],{})

        Pick_ph::Pick_ph(MachInst machInst)  : DspIntOp("pick_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precrq_qb_ph(['\n                                Rd_uw = Rs_uw<31:24> << 24 |\n                                        Rs_uw<15:8> << 16 |\n                                        Rt_uw<31:24> << 8 |\n                                        Rt_uw<15:8>;\n                            '],{})

        Precrq_qb_ph::Precrq_qb_ph(MachInst machInst)  : DspIntOp("precrq_qb_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precr_qb_ph(['\n                                Rd_uw = Rs_uw<23:16> << 24 |\n                                        Rs_uw<7:0> << 16 |\n                                        Rt_uw<23:16> << 8 |\n                                        Rt_uw<7:0>;\n                            '],{})

        Precr_qb_ph::Precr_qb_ph(MachInst machInst)  : DspIntOp("precr_qb_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::packrl_ph(['\n                                Rd_uw = dspPack(Rs_uw, Rt_uw, SIMD_FMT_PH);\n                            '],{})

        Packrl_ph::Packrl_ph(MachInst machInst)  : DspIntOp("packrl_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precrqu_s_qb_ph(['\n                                Rd_uw = dspPrecrqu(Rs_uw, Rt_uw, &dspctl);\n                            '],{})

        Precrqu_s_qb_ph::Precrqu_s_qb_ph(MachInst machInst)  : DspIntOp("precrqu_s_qb_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::precrq_ph_w(['\n                                Rd_uw = Rs_uw<31:16> << 16 | Rt_uw<31:16>;\n                            '],{})

        Precrq_ph_w::Precrq_ph_w(MachInst machInst)  : DspIntOp("precrq_ph_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precrq_rs_ph_w(['\n                                Rd_uw = dspPrecrq(Rs_uw, Rt_uw,\n                                                  SIMD_FMT_W, &dspctl);\n                            '],{})

        Precrq_rs_ph_w::Precrq_rs_ph_w(MachInst machInst)  : DspIntOp("precrq_rs_ph_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::cmpgdu_eq_qb(['\n                                Rd_uw = dspCmpgd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, CMP_EQ, &dspctl);\n                            '],{})

        Cmpgdu_eq_qb::Cmpgdu_eq_qb(MachInst machInst)  : DspIntOp("cmpgdu_eq_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpgdu_lt_qb(['\n                                Rd_uw = dspCmpgd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, CMP_LT, &dspctl);\n                            '],{})

        Cmpgdu_lt_qb::Cmpgdu_lt_qb(MachInst machInst)  : DspIntOp("cmpgdu_lt_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::cmpgdu_le_qb(['\n                                Rd_uw = dspCmpgd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, CMP_LE, &dspctl);\n                            '],{})

        Cmpgdu_le_qb::Cmpgdu_le_qb(MachInst machInst)  : DspIntOp("cmpgdu_le_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precr_sra_ph_w(['\n                                Rt_uw = dspPrecrSra(Rt_uw, Rs_uw, RD,\n                                                    SIMD_FMT_W, NOROUND);\n                            '],{})

        Precr_sra_ph_w::Precr_sra_ph_w(MachInst machInst)  : DspIntOp("precr_sra_ph_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precr_sra_r_ph_w(['\n                                Rt_uw = dspPrecrSra(Rt_uw, Rs_uw, RD,\n                                                    SIMD_FMT_W, ROUND); \n                            '],{})

        Precr_sra_r_ph_w::Precr_sra_r_ph_w(MachInst machInst)  : DspIntOp("precr_sra_r_ph_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::absq_s_qb(['\n                                Rd_sw = dspAbs(Rt_sw, SIMD_FMT_QB, &dspctl);\n                            '],{})

        Absq_s_qb::Absq_s_qb(MachInst machInst)  : DspIntOp("absq_s_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::repl_qb(['\n                                Rd_uw = RS_RT<7:0> << 24 |\n                                        RS_RT<7:0> << 16 |\n                                        RS_RT<7:0> << 8 |\n                                        RS_RT<7:0>;\n                            '],{})

        Repl_qb::Repl_qb(MachInst machInst)  : DspIntOp("repl_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::replv_qb(['\n                                Rd_sw = Rt_uw<7:0> << 24 |\n                                        Rt_uw<7:0> << 16 |\n                                        Rt_uw<7:0> << 8 |\n                                        Rt_uw<7:0>;\n                            '],{})

        Replv_qb::Replv_qb(MachInst machInst)  : DspIntOp("replv_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precequ_ph_qbl(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_L);\n                            '],{})

        Precequ_ph_qbl::Precequ_ph_qbl(MachInst machInst)  : DspIntOp("precequ_ph_qbl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precequ_ph_qbr(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_R);\n                            '],{})

        Precequ_ph_qbr::Precequ_ph_qbr(MachInst machInst)  : DspIntOp("precequ_ph_qbr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precequ_ph_qbla(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_LA);\n                            '],{})

        Precequ_ph_qbla::Precequ_ph_qbla(MachInst machInst)  : DspIntOp("precequ_ph_qbla", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::precequ_ph_qbra(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_RA);\n                            '],{})

        Precequ_ph_qbra::Precequ_ph_qbra(MachInst machInst)  : DspIntOp("precequ_ph_qbra", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::absq_s_ph(['\n                                Rd_sw = dspAbs(Rt_sw, SIMD_FMT_PH, &dspctl);\n                            '],{})

        Absq_s_ph::Absq_s_ph(MachInst machInst)  : DspIntOp("absq_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::repl_ph(['\n                                Rd_uw = (sext<10>(RS_RT))<15:0> << 16 |\n                                        (sext<10>(RS_RT))<15:0>;\n                            '],{})

        Repl_ph::Repl_ph(MachInst machInst)  : DspIntOp("repl_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::replv_ph(['\n                                Rd_uw = Rt_uw<15:0> << 16 |\n                                        Rt_uw<15:0>;\n                            '],{})

        Replv_ph::Replv_ph(MachInst machInst)  : DspIntOp("replv_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::preceq_w_phl(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_PH, SIGNED,\n                                                 SIMD_FMT_W, SIGNED, MODE_L);\n                            '],{})

        Preceq_w_phl::Preceq_w_phl(MachInst machInst)  : DspIntOp("preceq_w_phl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::preceq_w_phr(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_PH, SIGNED,\n                                                 SIMD_FMT_W, SIGNED, MODE_R);\n                            '],{})

        Preceq_w_phr::Preceq_w_phr(MachInst machInst)  : DspIntOp("preceq_w_phr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::absq_s_w(['\n                                Rd_sw = dspAbs(Rt_sw, SIMD_FMT_W, &dspctl);\n                            '],{})

        Absq_s_w::Absq_s_w(MachInst machInst)  : DspIntOp("absq_s_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// IntOp::bitrev((['\n                            Rd_uw = bitrev( Rt_uw<15:0> );\n                        '], {}))

        Bitrev::Bitrev(MachInst machInst)  : IntOp("bitrev", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// DspIntOp::preceu_ph_qbl(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_L);\n                            '],{})

        Preceu_ph_qbl::Preceu_ph_qbl(MachInst machInst)  : DspIntOp("preceu_ph_qbl", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::preceu_ph_qbr(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_R );\n                            '],{})

        Preceu_ph_qbr::Preceu_ph_qbr(MachInst machInst)  : DspIntOp("preceu_ph_qbr", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::preceu_ph_qbla(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_LA );\n                            '],{})

        Preceu_ph_qbla::Preceu_ph_qbla(MachInst machInst)  : DspIntOp("preceu_ph_qbla", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::preceu_ph_qbra(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_RA);\n                            '],{})

        Preceu_ph_qbra::Preceu_ph_qbra(MachInst machInst)  : DspIntOp("preceu_ph_qbra", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::shll_qb(['\n                                Rd_sw = dspShll(Rt_sw, RS, SIMD_FMT_QB,\n                                                NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Shll_qb::Shll_qb(MachInst machInst)  : DspIntOp("shll_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrl_qb(['\n                                Rd_sw = dspShrl(Rt_sw, RS, SIMD_FMT_QB,\n                                                UNSIGNED);\n                            '],{})

        Shrl_qb::Shrl_qb(MachInst machInst)  : DspIntOp("shrl_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shllv_qb(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        Shllv_qb::Shllv_qb(MachInst machInst)  : DspIntOp("shllv_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrlv_qb(['\n                                Rd_sw = dspShrl(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                UNSIGNED);\n                            '],{})

        Shrlv_qb::Shrlv_qb(MachInst machInst)  : DspIntOp("shrlv_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shra_qb(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_QB,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        Shra_qb::Shra_qb(MachInst machInst)  : DspIntOp("shra_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shra_r_qb(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_QB,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        Shra_r_qb::Shra_r_qb(MachInst machInst)  : DspIntOp("shra_r_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrav_qb(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        Shrav_qb::Shrav_qb(MachInst machInst)  : DspIntOp("shrav_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrav_r_qb(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        Shrav_r_qb::Shrav_r_qb(MachInst machInst)  : DspIntOp("shrav_r_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::shll_ph(['\n                                Rd_uw = dspShll(Rt_uw, RS, SIMD_FMT_PH,\n                                                NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        Shll_ph::Shll_ph(MachInst machInst)  : DspIntOp("shll_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shra_ph(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_PH,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        Shra_ph::Shra_ph(MachInst machInst)  : DspIntOp("shra_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shllv_ph(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        Shllv_ph::Shllv_ph(MachInst machInst)  : DspIntOp("shllv_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrav_ph(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        Shrav_ph::Shrav_ph(MachInst machInst)  : DspIntOp("shrav_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shll_s_ph(['\n                                Rd_sw = dspShll(Rt_sw, RS, SIMD_FMT_PH,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        Shll_s_ph::Shll_s_ph(MachInst machInst)  : DspIntOp("shll_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shra_r_ph(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_PH,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        Shra_r_ph::Shra_r_ph(MachInst machInst)  : DspIntOp("shra_r_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shllv_s_ph(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        Shllv_s_ph::Shllv_s_ph(MachInst machInst)  : DspIntOp("shllv_s_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrav_r_ph(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        Shrav_r_ph::Shrav_r_ph(MachInst machInst)  : DspIntOp("shrav_r_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::shll_s_w(['\n                                Rd_sw = dspShll(Rt_sw, RS, SIMD_FMT_W,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        Shll_s_w::Shll_s_w(MachInst machInst)  : DspIntOp("shll_s_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shra_r_w(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_W,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        Shra_r_w::Shra_r_w(MachInst machInst)  : DspIntOp("shra_r_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shllv_s_w(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_W,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        Shllv_s_w::Shllv_s_w(MachInst machInst)  : DspIntOp("shllv_s_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrav_r_w(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_W,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        Shrav_r_w::Shrav_r_w(MachInst machInst)  : DspIntOp("shrav_r_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::shrl_ph(['\n                                Rd_sw = dspShrl(Rt_sw, RS, SIMD_FMT_PH,\n                                                UNSIGNED);\n                            '],{})

        Shrl_ph::Shrl_ph(MachInst machInst)  : DspIntOp("shrl_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::shrlv_ph(['\n                                Rd_sw = dspShrl(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                UNSIGNED);\n                            '],{})

        Shrlv_ph::Shrlv_ph(MachInst machInst)  : DspIntOp("shrlv_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::adduh_qb(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                NOROUND, UNSIGNED);\n                            '],{})

        Adduh_qb::Adduh_qb(MachInst machInst)  : DspIntOp("adduh_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subuh_qb(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                NOROUND, UNSIGNED);\n                            '],{})

        Subuh_qb::Subuh_qb(MachInst machInst)  : DspIntOp("subuh_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::adduh_r_qb(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                ROUND, UNSIGNED);\n                            '],{})

        Adduh_r_qb::Adduh_r_qb(MachInst machInst)  : DspIntOp("adduh_r_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subuh_r_qb(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                ROUND, UNSIGNED);\n                            '],{})

        Subuh_r_qb::Subuh_r_qb(MachInst machInst)  : DspIntOp("subuh_r_qb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::addqh_ph(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                NOROUND, SIGNED);\n                            '],{})

        Addqh_ph::Addqh_ph(MachInst machInst)  : DspIntOp("addqh_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subqh_ph(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                NOROUND, SIGNED);\n                            '],{})

        Subqh_ph::Subqh_ph(MachInst machInst)  : DspIntOp("subqh_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addqh_r_ph(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                ROUND, SIGNED);\n                            '],{})

        Addqh_r_ph::Addqh_r_ph(MachInst machInst)  : DspIntOp("addqh_r_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subqh_r_ph(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                ROUND, SIGNED);\n                            '],{})

        Subqh_r_ph::Subqh_r_ph(MachInst machInst)  : DspIntOp("subqh_r_ph", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::mul_ph(['\n                                Rd_sw = dspMul(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                               NOSATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        Mul_ph::Mul_ph(MachInst machInst)  : DspIntOp("mul_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::mul_s_ph(['\n                                Rd_sw = dspMul(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                               SATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        Mul_s_ph::Mul_s_ph(MachInst machInst)  : DspIntOp("mul_s_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::addqh_w(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                NOROUND, SIGNED);\n                            '],{})

        Addqh_w::Addqh_w(MachInst machInst)  : DspIntOp("addqh_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subqh_w(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                NOROUND, SIGNED);\n                            '],{})

        Subqh_w::Subqh_w(MachInst machInst)  : DspIntOp("subqh_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::addqh_r_w(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                ROUND, SIGNED);\n                            '],{})

        Addqh_r_w::Addqh_r_w(MachInst machInst)  : DspIntOp("addqh_r_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::subqh_r_w(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                ROUND, SIGNED);\n                            '],{})

        Subqh_r_w::Subqh_r_w(MachInst machInst)  : DspIntOp("subqh_r_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::mulq_s_w(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                SATURATE, NOROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        Mulq_s_w::Mulq_s_w(MachInst machInst)  : DspIntOp("mulq_s_w", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::mulq_rs_w(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                SATURATE, ROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        Mulq_rs_w::Mulq_rs_w(MachInst machInst)  : DspIntOp("mulq_rs_w", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::wsbh(['\n                        Rd_uw = Rt_uw<23:16> << 24 |\n                                Rt_uw<31:24> << 16 |\n                                Rt_uw<7:0>   << 8  |\n                                Rt_uw<15:8>;\n                    '],{})

        Wsbh::Wsbh(MachInst machInst)  : MipsStaticInst("wsbh", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::seb([' Rd_sw = Rt_sb; '],{})

        Seb::Seb(MachInst machInst)  : MipsStaticInst("seb", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// BasicOp::seh([' Rd_sw = Rt_sh; '],{})

        Seh::Seh(MachInst machInst)  : MipsStaticInst("seh", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspHiLoOp::dpa_w_ph(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        Dpa_w_ph::Dpa_w_ph(MachInst machInst)  : DspHiLoOp("dpa_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dps_w_ph(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        Dps_w_ph::Dps_w_ph(MachInst machInst)  : DspHiLoOp("dps_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::mulsa_w_ph(['\n                                dspac = dspMulsa(dspac, Rs_sw, Rt_sw,\n                                                 ACDST, SIMD_FMT_PH );\n                            ', 'IntMultOp'],{})

        Mulsa_w_ph::Mulsa_w_ph(MachInst machInst)  : DspHiLoOp("mulsa_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpau_h_qbl(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        Dpau_h_qbl::Dpau_h_qbl(MachInst machInst)  : DspHiLoOp("dpau_h_qbl", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpaq_s_w_ph(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpaq_s_w_ph::Dpaq_s_w_ph(MachInst machInst)  : DspHiLoOp("dpaq_s_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsq_s_w_ph(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpsq_s_w_ph::Dpsq_s_w_ph(MachInst machInst)  : DspHiLoOp("dpsq_s_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::mulsaq_s_w_ph(['\n                                dspac = dspMulsaq(dspac, Rs_sw, Rt_sw,\n                                                  ACDST, SIMD_FMT_PH,\n                                                  &dspctl);\n                            ', 'IntMultOp'],{})

        Mulsaq_s_w_ph::Mulsaq_s_w_ph(MachInst machInst)  : DspHiLoOp("mulsaq_s_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpau_h_qbr(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_R);\n                            ', 'IntMultOp'],{})

        Dpau_h_qbr::Dpau_h_qbr(MachInst machInst)  : DspHiLoOp("dpau_h_qbr", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspHiLoOp::dpax_w_ph(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_X);\n                            ', 'IntMultOp'],{})

        Dpax_w_ph::Dpax_w_ph(MachInst machInst)  : DspHiLoOp("dpax_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsx_w_ph(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_X);\n                            ', 'IntMultOp'],{})

        Dpsx_w_ph::Dpsx_w_ph(MachInst machInst)  : DspHiLoOp("dpsx_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsu_h_qbl(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        Dpsu_h_qbl::Dpsu_h_qbl(MachInst machInst)  : DspHiLoOp("dpsu_h_qbl", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpaq_sa_l_w(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_W,\n                                                SIMD_FMT_L, SATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpaq_sa_l_w::Dpaq_sa_l_w(MachInst machInst)  : DspHiLoOp("dpaq_sa_l_w", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsq_sa_l_w(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_W,\n                                                SIMD_FMT_L, SATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpsq_sa_l_w::Dpsq_sa_l_w(MachInst machInst)  : DspHiLoOp("dpsq_sa_l_w", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsu_h_qbr(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_R);\n                            ', 'IntMultOp'],{})

        Dpsu_h_qbr::Dpsu_h_qbr(MachInst machInst)  : DspHiLoOp("dpsu_h_qbr", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspHiLoOp::maq_sa_w_phl(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_L, SATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        Maq_sa_w_phl::Maq_sa_w_phl(MachInst machInst)  : DspHiLoOp("maq_sa_w_phl", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::maq_sa_w_phr(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_R, SATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        Maq_sa_w_phr::Maq_sa_w_phr(MachInst machInst)  : DspHiLoOp("maq_sa_w_phr", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::maq_s_w_phl(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_L, NOSATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        Maq_s_w_phl::Maq_s_w_phl(MachInst machInst)  : DspHiLoOp("maq_s_w_phl", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::maq_s_w_phr(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_R, NOSATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        Maq_s_w_phr::Maq_s_w_phr(MachInst machInst)  : DspHiLoOp("maq_s_w_phr", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspHiLoOp::dpaqx_s_w_ph(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpaqx_s_w_ph::Dpaqx_s_w_ph(MachInst machInst)  : DspHiLoOp("dpaqx_s_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsqx_s_w_ph(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpsqx_s_w_ph::Dpsqx_s_w_ph(MachInst machInst)  : DspHiLoOp("dpsqx_s_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpaqx_sa_w_ph(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, SATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpaqx_sa_w_ph::Dpaqx_sa_w_ph(MachInst machInst)  : DspHiLoOp("dpaqx_sa_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::dpsqx_sa_w_ph(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, SATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        Dpsqx_sa_w_ph::Dpsqx_sa_w_ph(MachInst machInst)  : DspHiLoOp("dpsqx_sa_w_ph", machInst, IntMultOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// IntOp::append(['\n                                Rt_uw = (Rt_uw << RD) | bits(Rs_uw, RD - 1, 0);\n                                '],{})

        Append::Append(MachInst machInst)  : IntOp("append", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// IntOp::prepend(['\n                                Rt_uw = (Rt_uw >> RD) |\n                                        (bits(Rs_uw, RD - 1, 0) << (32 - RD));\n                            '],{})

        Prepend::Prepend(MachInst machInst)  : IntOp("prepend", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// IntOp::balign(['\n                                Rt_uw = (Rt_uw << (8 * BP)) |\n                                        (Rs_uw >> (8 * (4 - BP)));\n                            '],{})

        Balign::Balign(MachInst machInst)  : IntOp("balign", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspHiLoOp::extr_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, RS,\n                                                NOROUND, NOSATURATE, &dspctl);\n                            '],{})

        Extr_w::Extr_w(MachInst machInst)  : DspHiLoOp("extr_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extrv_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, Rs_uw,\n                                                NOROUND, NOSATURATE, &dspctl);\n                            '],{})

        Extrv_w::Extrv_w(MachInst machInst)  : DspHiLoOp("extrv_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extp(['\n                                Rt_uw = dspExtp(dspac, RS, &dspctl);\n                            '],{})

        Extp::Extp(MachInst machInst)  : DspHiLoOp("extp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extpv(['\n                                Rt_uw = dspExtp(dspac, Rs_uw, &dspctl);\n                            '],{})

        Extpv::Extpv(MachInst machInst)  : DspHiLoOp("extpv", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extr_r_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, RS,\n                                                ROUND, NOSATURATE, &dspctl);\n                            '],{})

        Extr_r_w::Extr_r_w(MachInst machInst)  : DspHiLoOp("extr_r_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extrv_r_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, Rs_uw,\n                                                ROUND, NOSATURATE, &dspctl);\n                            '],{})

        Extrv_r_w::Extrv_r_w(MachInst machInst)  : DspHiLoOp("extrv_r_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extr_rs_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, RS,\n                                                ROUND, SATURATE, &dspctl);\n                            '],{})

        Extr_rs_w::Extr_rs_w(MachInst machInst)  : DspHiLoOp("extr_rs_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extrv_rs_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, Rs_uw,\n                                                ROUND, SATURATE, &dspctl);\n                            '],{})

        Extrv_rs_w::Extrv_rs_w(MachInst machInst)  : DspHiLoOp("extrv_rs_w", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspHiLoOp::extpdp(['\n                                Rt_uw = dspExtpd(dspac, RS, &dspctl);\n                            '],{})

        Extpdp::Extpdp(MachInst machInst)  : DspHiLoOp("extpdp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extpdpv(['\n                                Rt_uw = dspExtpd(dspac, Rs_uw, &dspctl);\n                            '],{})

        Extpdpv::Extpdpv(MachInst machInst)  : DspHiLoOp("extpdpv", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extr_s_h(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_PH, RS,\n                                                NOROUND, SATURATE, &dspctl);\n                            '],{})

        Extr_s_h::Extr_s_h(MachInst machInst)  : DspHiLoOp("extr_s_h", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::extrv_s_h(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_PH, Rs_uw,\n                                                NOROUND, SATURATE, &dspctl);\n                            '],{})

        Extrv_s_h::Extrv_s_h(MachInst machInst)  : DspHiLoOp("extrv_s_h", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspIntOp::rddsp(['\n                                Rd_uw = readDSPControl(&dspctl, RDDSPMASK);\n                            '],{})

        Rddsp::Rddsp(MachInst machInst)  : DspIntOp("rddsp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_destRegIdx[_numDestRegs++] = RD;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspIntOp::wrdsp(['\n                                writeDSPControl(&dspctl, Rs_uw, WRDSPMASK);\n                            '],{})

        Wrdsp::Wrdsp(MachInst machInst)  : DspIntOp("wrdsp", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// DspHiLoOp::shilo(['\n                                if (sext<6>(HILOSA) < 0) {\n                                    dspac = (uint64_t)dspac <<\n                                                -sext<6>(HILOSA);\n                                } else {\n                                    dspac = (uint64_t)dspac >>\n                                                sext<6>(HILOSA);\n                                }\n                            '],{})

        Shilo::Shilo(MachInst machInst)  : DspHiLoOp("shilo", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;;
        }

// DspHiLoOp::shilov(['\n                                if (sext<6>(Rs_sw<5:0>) < 0) {\n                                    dspac = (uint64_t)dspac <<\n                                                -sext<6>(Rs_sw<5:0>);\n                                } else {\n                                    dspac = (uint64_t)dspac >>\n                                                sext<6>(Rs_sw<5:0>);\n                                }\n                            '],{})

        Shilov::Shilov(MachInst machInst)  : DspHiLoOp("shilov", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// DspHiLoOp::mthlip(['\n                                dspac = dspac << 32;\n                                dspac |= Rs_uw;\n                                dspctl = insertBits(dspctl, 5, 0,\n                                                    dspctl<5:0> + 32);\n                            '],{})

        Mthlip::Mthlip(MachInst machInst)  : DspHiLoOp("mthlip", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_LO0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_HI0 + ACDST*3;
	_numIntDestRegs++;
	_srcRegIdx[_numSrcRegs++] = INTREG_DSP_CONTROL;
	_destRegIdx[_numDestRegs++] = INTREG_DSP_CONTROL;
	_numIntDestRegs++;
	flags[IsDspOp] = true;
	flags[IsInteger] = true;;
        }

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::rdhwr_se(([' Rt = TpValue; '], {}))

        Rdhwr_se::Rdhwr_se(MachInst machInst)  : MipsStaticInst("rdhwr_se", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = MISCREG_TP_VALUE + Misc_Reg_Base;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;;
        }

// FailUnimpl::rdhwr(([], {}))

// FailUnimpl::rdhwr(([], {}))

// FailUnimpl::rdhwr(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// LoadMemory::lb([' Rt_sw = Mem_sb; '],{})

    Lb::Lb(ExtMachInst machInst)
         : Memory("lb", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadMemory::lh([' Rt_sw = Mem_sh; '],{})

    Lh::Lh(ExtMachInst machInst)
         : Memory("lh", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadMemory::lw([' Rt_sw = Mem_sw; '],{})

    Lw::Lw(ExtMachInst machInst)
         : Memory("lw", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadMemory::lbu([' Rt_uw = Mem_ub;'],{})

    Lbu::Lbu(ExtMachInst machInst)
         : Memory("lbu", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadMemory::lhu([' Rt_uw = Mem_uh; '],{})

    Lhu::Lhu(ExtMachInst machInst)
         : Memory("lhu", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadUnalignedMemory::lwl(['\n                uint32_t mem_shift = 24 - (8 * byte_offset);\n                Rt_uw = mem_word << mem_shift | (Rt_uw & mask(mem_shift));\n            '],{})

    Lwl::Lwl(ExtMachInst machInst)
         : Memory("lwl", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadUnalignedMemory::lwr(['\n                uint32_t mem_shift = 8 * byte_offset;\n                Rt_uw = (Rt_uw & (mask(mem_shift) << (32 - mem_shift))) |\n                        (mem_word >> mem_shift);\n            '],{})

    Lwr::Lwr(ExtMachInst machInst)
         : Memory("lwr", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// Unknown::unknown(([], {}))

// StoreMemory::sb([' Mem_ub = Rt<7:0>; '],{})

    Sb::Sb(ExtMachInst machInst)
         : Memory("sb", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreMemory::sh([' Mem_uh = Rt<15:0>; '],{})

    Sh::Sh(ExtMachInst machInst)
         : Memory("sh", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreMemory::sw([' Mem_uw = Rt<31:0>; '],{})

    Sw::Sw(ExtMachInst machInst)
         : Memory("sw", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreUnalignedMemory::swl(['\n                uint32_t reg_shift = 24 - (8 * byte_offset);\n                uint32_t mem_shift = 32 - reg_shift;\n                mem_word = (mem_word & (mask(reg_shift) << mem_shift)) |\n                           (Rt_uw >> reg_shift);\n                '],{})

    Swl::Swl(ExtMachInst machInst)
         : Memory("swl", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreUnalignedMemory::swr(['\n                uint32_t reg_shift = 8 * byte_offset;\n                mem_word = Rt_uw << reg_shift |\n                           (mem_word & (mask(reg_shift)));\n            '],{})

    Swr::Swr(ExtMachInst machInst)
         : Memory("swr", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// CP0Control::cache(['\n                //Addr CacheEA = Rs_uw + OFFSET;\n                //fault = xc->CacheOp((uint8_t)CACHE_OP,(Addr) CacheEA);\n            '],{})

        Cache::Cache(MachInst machInst)  : CP0Control("cache", machInst, IntAluOp)
        {
                
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	flags[IsNonSpeculative] = true;;
        }

// Unknown::unknown(([], {}))

// LoadMemory::ll([' Rt_uw = Mem_uw; '],{'mem_flags': 'LLSC'})

    Ll::Ll(ExtMachInst machInst)
         : Memory("ll", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;
	memAccessFlags = Request::LLSC;;
    }

// LoadMemory::lwc1([' Ft_uw = Mem_uw; '],{})

    Lwc1::Lwc1(ExtMachInst machInst)
         : Memory("lwc1", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = FT + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// LoadMemory::ldc1([' Ft_ud = Mem_ud; '],{})

    Ldc1::Ldc1(ExtMachInst machInst)
         : Memory("ldc1", machInst, MemReadOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_destRegIdx[_numDestRegs++] = FT + FP_Reg_Base;
	_numFPDestRegs++;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsLoad] = true;
	flags[IsMemRef] = true;;
    }

// CP2Unimpl::lwc2(([], {}))

// CP2Unimpl::ldc2(([], {}))

// Prefetch::pref(([], {}))

    Pref::Pref(ExtMachInst machInst)
         : Memory("pref", machInst, IntAluOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	flags[IsInteger] = true;
	memAccessFlags = Request::PREFETCH;;
    }

// Unknown::unknown(([], {}))

// StoreCond::sc(([' Mem_uw = Rt_uw; ', ' uint64_t tmp = write_result;\n                              Rt_uw = (tmp == 0 || tmp == 1) ? tmp : Rt_uw;\n                           '], {'inst_flags': 'IsStoreConditional', 'mem_flags': 'LLSC'}))

    Sc::Sc(ExtMachInst machInst)
         : Memory("sc", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = RT;
	_destRegIdx[_numDestRegs++] = RT;
	_numIntDestRegs++;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;
	flags[IsStoreConditional] = true;
	memAccessFlags = Request::LLSC;;
    }

// StoreMemory::swc1([' Mem_uw = Ft_uw; '],{})

    Swc1::Swc1(ExtMachInst machInst)
         : Memory("swc1", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// StoreMemory::sdc1([' Mem_ud = Ft_ud; '],{})

    Sdc1::Sdc1(ExtMachInst machInst)
         : Memory("sdc1", machInst, MemWriteOp)
    {
        
	_numSrcRegs = 0;
	_numDestRegs = 0;
	_numFPDestRegs = 0;
	_numIntDestRegs = 0;
	_numCCDestRegs = 0;
	_srcRegIdx[_numSrcRegs++] = RS;
	_srcRegIdx[_numSrcRegs++] = FT + FP_Reg_Base;
	flags[IsFloating] = true;
	flags[IsInteger] = true;
	flags[IsMemRef] = true;
	flags[IsStore] = true;;
    }

// CP2Unimpl::swc2(([], {}))

// CP2Unimpl::sdc2(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

#endif
