// DO NOT EDIT
// This file was automatically generated from an ISA description:
//   mips/isa/main.isa

#undef OPCODE
#define OPCODE	bits(machInst, 31, 26)
#undef OPCODE_HI
#define OPCODE_HI	bits(machInst, 31, 29)
#undef OPCODE_LO
#define OPCODE_LO	bits(machInst, 28, 26)
#undef REGIMM
#define REGIMM	bits(machInst, 20, 16)
#undef REGIMM_HI
#define REGIMM_HI	bits(machInst, 20, 19)
#undef REGIMM_LO
#define REGIMM_LO	bits(machInst, 18, 16)
#undef FUNCTION
#define FUNCTION	bits(machInst,  5,  0)
#undef FUNCTION_HI
#define FUNCTION_HI	bits(machInst,  5,  3)
#undef FUNCTION_LO
#define FUNCTION_LO	bits(machInst,  2,  0)
#undef RS
#define RS	bits(machInst, 25, 21)
#undef RS_MSB
#define RS_MSB	bits(machInst, 25, 25)
#undef RS_HI
#define RS_HI	bits(machInst, 25, 24)
#undef RS_LO
#define RS_LO	bits(machInst, 23, 21)
#undef RS_SRL
#define RS_SRL	bits(machInst, 25, 22)
#undef RS_RT
#define RS_RT	bits(machInst, 25, 16)
#undef RT
#define RT	bits(machInst, 20, 16)
#undef RT_HI
#define RT_HI	bits(machInst, 20, 19)
#undef RT_LO
#define RT_LO	bits(machInst, 18, 16)
#undef RT_RD
#define RT_RD	bits(machInst, 20, 11)
#undef RD
#define RD	bits(machInst, 15, 11)
#undef INTIMM
#define INTIMM	bits(machInst, 15,  0)
#undef RS_RT_INTIMM
#define RS_RT_INTIMM	bits(machInst, 25,  0)
#undef FMT
#define FMT	bits(machInst, 25, 21)
#undef FR
#define FR	bits(machInst, 25, 21)
#undef FT
#define FT	bits(machInst, 20, 16)
#undef FS
#define FS	bits(machInst, 15, 11)
#undef FD
#define FD	bits(machInst, 10,  6)
#undef ND
#define ND	bits(machInst, 17, 17)
#undef TF
#define TF	bits(machInst, 16, 16)
#undef MOVCI
#define MOVCI	bits(machInst, 16, 16)
#undef MOVCF
#define MOVCF	bits(machInst, 16, 16)
#undef SRL
#define SRL	bits(machInst, 21, 21)
#undef SRLV
#define SRLV	bits(machInst,  6,  6)
#undef SA
#define SA	bits(machInst, 10,  6)
#undef CC
#define CC	bits(machInst, 10,  8)
#undef BRANCH_CC
#define BRANCH_CC	bits(machInst, 20, 18)
#undef SEL
#define SEL	bits(machInst,  2,  0)
#undef SC
#define SC	bits(machInst,  5,  5)
#undef OFFSET
#define OFFSET	bits(machInst, 15,  0)
#undef JMPTARG
#define JMPTARG	bits(machInst, 25,  0)
#undef HINT
#define HINT	bits(machInst, 10,  6)
#undef SYSCALLCODE
#define SYSCALLCODE	bits(machInst, 25,  6)
#undef TRAPCODE
#define TRAPCODE	bits(machInst, 15, 13)
#undef MSB
#define MSB	bits(machInst, 15, 11)
#undef LSB
#define LSB	bits(machInst, 10,  6)
#undef M5FUNC
#define M5FUNC	bits(machInst,  7,  0)
#undef OP
#define OP	bits(machInst, 10,  6)
#undef OP_HI
#define OP_HI	bits(machInst, 10,  9)
#undef OP_LO
#define OP_LO	bits(machInst,  8,  6)
#undef DSPSA
#define DSPSA	bits(machInst, 23, 21)
#undef HILOSA
#define HILOSA	bits(machInst, 25, 20)
#undef RDDSPMASK
#define RDDSPMASK	bits(machInst, 21, 16)
#undef WRDSPMASK
#define WRDSPMASK	bits(machInst, 16, 11)
#undef ACSRC
#define ACSRC	bits(machInst, 22, 21)
#undef ACDST
#define ACDST	bits(machInst, 12, 11)
#undef BP
#define BP	bits(machInst, 12, 11)
#undef POS
#define POS	bits(machInst, 10,  6)
#undef MT_U
#define MT_U	bits(machInst,  5,  5)
#undef MT_H
#define MT_H	bits(machInst,  4,  4)
#undef CACHE_OP
#define CACHE_OP	bits(machInst, 20, 16)


    using namespace MipsISA;

    /**
     * Base class for all MIPS static instructions.
     */
    class MipsStaticInst : public StaticInst
    {
      protected:

        // Constructor
        MipsStaticInst(const char *mnem, MachInst _machInst, OpClass __opClass)
            : StaticInst(mnem, _machInst, __opClass)
        {
        }

        /// Print a register name for disassembly given the unique
        /// dependence tag number (FP or int).
        void printReg(std::ostream &os, int reg) const;

        std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;

      public:
        void
        advancePC(MipsISA::PCState &pc) const
        {
            pc.advance();
        }
    };


    /**
     * Static instruction class for no-ops.  This is a leaf class.
     */
    class Nop : public MipsStaticInst
    {
        /// Disassembly of original instruction.
        const std::string originalDisassembly;

      public:
        /// Constructor
        Nop(const std::string _originalDisassembly, MachInst _machInst)
            : MipsStaticInst("nop", _machInst, No_OpClass),
              originalDisassembly(_originalDisassembly)
        {
            flags[IsNop] = true;
        }

        ~Nop() { }

        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;

    };

        std::string inst2string(MachInst machInst);


        class CP0Control : public MipsStaticInst
        {
                protected:

                /// Constructor
                CP0Control(const char *mnem, MachInst _machInst, OpClass __opClass) :
                           MipsStaticInst(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };
        class CP0TLB : public MipsStaticInst
        {
                protected:

                /// Constructor
                CP0TLB(const char *mnem, MachInst _machInst, OpClass __opClass) :
                           MipsStaticInst(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };


        class CP1Control : public MipsStaticInst
        {
                protected:

                /// Constructor
                CP1Control(const char *mnem, MachInst _machInst, OpClass __opClass) :
                           MipsStaticInst(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };


        bool isCoprocessorEnabled(ExecContext *xc, unsigned cop_num);

        bool isMMUTLB(ExecContext *xc);


#include <iostream>
    using namespace std;
        /**
         * Base class for integer operations.
         */
        class IntOp : public MipsStaticInst
        {
                protected:

                /// Constructor
                IntOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                                MipsStaticInst(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };


        class HiLoOp: public IntOp
        {
                protected:

                /// Constructor
                HiLoOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                                IntOp(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };

        class HiLoRsSelOp: public HiLoOp
        {
                protected:

                /// Constructor
                HiLoRsSelOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                                HiLoOp(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };

        class HiLoRdSelOp: public HiLoOp
        {
                protected:

                /// Constructor
                HiLoRdSelOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                                HiLoOp(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };

        class HiLoRdSelValOp: public HiLoOp
        {
                protected:

                /// Constructor
                HiLoRdSelValOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                                HiLoOp(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };

        class IntImmOp : public MipsStaticInst
        {
                protected:

                int16_t imm;
                int32_t sextImm;
                uint32_t zextImm;

                /// Constructor
                IntImmOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                    MipsStaticInst(mnem, _machInst, __opClass),imm(INTIMM),
                    sextImm(INTIMM),zextImm(0x0000FFFF & INTIMM)
                {
                    //If Bit 15 is 1 then Sign Extend
                    int32_t temp = sextImm & 0x00008000;
                    if (temp > 0 && strcmp(mnemonic,"lui") != 0) {
                        sextImm |= 0xFFFF0000;
                    }
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;


        };


#include <iostream>
    using namespace std;
    /**
     * Base class for integer operations.
     */
    class DspIntOp : public MipsStaticInst
    {
      protected:

        /// Constructor
        DspIntOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
            MipsStaticInst(mnem, _machInst, __opClass)
        {
        }
    };

    class DspHiLoOp : public MipsStaticInst
    {
      protected:

        /// Constructor
        DspHiLoOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
            MipsStaticInst(mnem, _machInst, __opClass)
        {
        }
    };

    bool isDspEnabled(ExecContext *xc);

    bool isDspPresent(ExecContext *xc);

        /**
         * Base class for FP operations.
         */
        class FPOp : public MipsStaticInst
        {
                protected:

                /// Constructor
                FPOp(const char *mnem, MachInst _machInst, OpClass __opClass) : MipsStaticInst(mnem, _machInst, __opClass)
                {
                }

            //std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;

                //needs function to check for fpEnable or not
        };

        class FPCompareOp : public FPOp
        {
          protected:
            FPCompareOp(const char *mnem, MachInst _machInst, OpClass __opClass) : FPOp(mnem, _machInst, __opClass)
                {
                }

            std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;

        };

        void fpResetCauseBits(ExecContext *cpu);


    /**
     * Base class for general Mips memory-format instructions.
     */
    class Memory : public MipsStaticInst
    {
      protected:
        /// Memory request flags.  See mem_req_base.hh.
        Request::Flags memAccessFlags;

        /// Displacement for EA calculation (signed).
        int32_t disp;

        /// Constructor
        Memory(const char *mnem, MachInst _machInst, OpClass __opClass)
            : MipsStaticInst(mnem, _machInst, __opClass),
              disp(sext<16>(OFFSET))
        {
        }

        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

     /**
     * Base class for a few miscellaneous memory-format insts
     * that don't interpret the disp field
     */
    class MemoryNoDisp : public Memory
    {
      protected:
        /// Constructor
        MemoryNoDisp(const char *mnem, ExtMachInst _machInst, OpClass __opClass)
            : Memory(mnem, _machInst, __opClass)
        {
        }

        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

    uint64_t getMemData(ExecContext *xc, Packet *packet);


        /**
         * Base class for MIPS MT ASE operations.
         */
        class MTOp : public MipsStaticInst
        {
                protected:

                /// Constructor
                MTOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                    MipsStaticInst(mnem, _machInst, __opClass), user_mode(false)
                {
                }

               std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;

                bool user_mode;
        };

        class MTUserModeOp : public MTOp
        {
                protected:

                /// Constructor
                MTUserModeOp(const char *mnem, MachInst _machInst, OpClass __opClass) :
                    MTOp(mnem, _machInst, __opClass)
                {
                    user_mode = true;
                }

            //std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };

   void getThrRegExValues(ExecContext *xc,
                          MipsISA::VPEConf0Reg &vpe_conf0,
                          MipsISA::TCBindReg &tc_bind_mt,
                          MipsISA::TCBindReg &tc_bind,
                          MipsISA::VPEControlReg &vpe_control,
                          MipsISA::MVPConf0Reg &mvp_conf0);

   void getMTExValues(ExecContext *xc, MipsISA::Config3Reg &config3);

        /**
         * Base class for integer operations.
         */
        class Trap : public MipsStaticInst
        {
                protected:

                /// Constructor
                Trap(const char *mnem, MachInst _machInst, OpClass __opClass) : MipsStaticInst(mnem, _machInst, __opClass)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;
        };
        class TrapImm : public MipsStaticInst
        {
                protected:

                int16_t imm;

                /// Constructor
                TrapImm(const char *mnem, MachInst _machInst, OpClass __opClass) :
                    MipsStaticInst(mnem, _machInst, __opClass),imm(INTIMM)
                {
                }

                std::string generateDisassembly(Addr pc, const SymbolTable *symtab) const;


        };



#include <iostream>
    using namespace std;

    /**
     * Base class for instructions whose disassembly is not purely a
     * function of the machine instruction (i.e., it depends on the
     * PC).  This class overrides the disassemble() method to check
     * the PC and symbol table values before re-using a cached
     * disassembly string.  This is necessary for branches and jumps,
     * where the disassembly string includes the target address (which
     * may depend on the PC and/or symbol table).
     */
    class PCDependentDisassembly : public MipsStaticInst
    {
      protected:
        /// Cached program counter from last disassembly
        mutable Addr cachedPC;

        /// Cached symbol table pointer from last disassembly
        mutable const SymbolTable *cachedSymtab;

        /// Constructor
        PCDependentDisassembly(const char *mnem, MachInst _machInst,
                               OpClass __opClass)
            : MipsStaticInst(mnem, _machInst, __opClass),
              cachedPC(0), cachedSymtab(0)
        {
        }

        const std::string &
        disassemble(Addr pc, const SymbolTable *symtab) const;
    };

    /**
     * Base class for branches (PC-relative control transfers),
     * conditional or unconditional.
     */
    class Branch : public PCDependentDisassembly
    {
      protected:
        /// target address (signed) Displacement .
        int32_t disp;

        /// Constructor.
        Branch(const char *mnem, MachInst _machInst, OpClass __opClass)
            : PCDependentDisassembly(mnem, _machInst, __opClass),
              disp(OFFSET << 2)
        {
            //If Bit 17 is 1 then Sign Extend
            if ( (disp & 0x00020000) > 0  ) {
                disp |= 0xFFFE0000;
            }
        }

        MipsISA::PCState branchTarget(const MipsISA::PCState &branchPC) const;

        /// Explicitly import the otherwise hidden branchTarget
        using StaticInst::branchTarget;

        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

    /**
     * Base class for jumps (register-indirect control transfers).  In
     * the Mips ISA, these are always unconditional.
     */
    class Jump : public PCDependentDisassembly
    {
      protected:

        /// Displacement to target address (signed).
        int32_t disp;

        uint32_t target;

      public:
        /// Constructor
        Jump(const char *mnem, MachInst _machInst, OpClass __opClass)
            : PCDependentDisassembly(mnem, _machInst, __opClass),
              disp(JMPTARG << 2)
        {
        }

        MipsISA::PCState branchTarget(ThreadContext *tc) const;

        /// Explicitly import the otherwise hidden branchTarget
        using StaticInst::branchTarget;

        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

    /**
     * Static instruction class for unimplemented instructions that
     * cause simulator termination.  Note that these are recognized
     * (legal) instructions that the simulator does not support; the
     * 'Unknown' class is used for unrecognized/illegal instructions.
     * This is a leaf class.
     */
    class FailUnimplemented : public MipsStaticInst
    {
      public:
        /// Constructor
        FailUnimplemented(const char *_mnemonic, MachInst _machInst)
            : MipsStaticInst(_mnemonic, _machInst, No_OpClass)
        {
            // don't call execute() (which panics) if we're on a
            // speculative path
            flags[IsNonSpeculative] = true;
        }

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };
    class CP0Unimplemented : public MipsStaticInst
    {
      public:
        /// Constructor
        CP0Unimplemented(const char *_mnemonic, MachInst _machInst)
            : MipsStaticInst(_mnemonic, _machInst, No_OpClass)
        {
            // don't call execute() (which panics) if we're on a
            // speculative path
            flags[IsNonSpeculative] = true;
        }

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };
    class CP1Unimplemented : public MipsStaticInst
    {
      public:
        /// Constructor
        CP1Unimplemented(const char *_mnemonic, MachInst _machInst)
            : MipsStaticInst(_mnemonic, _machInst, No_OpClass)
        {
            // don't call execute() (which panics) if we're on a
            // speculative path
            flags[IsNonSpeculative] = true;
        }

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };
    class CP2Unimplemented : public MipsStaticInst
    {
      public:
        /// Constructor
        CP2Unimplemented(const char *_mnemonic, MachInst _machInst)
            : MipsStaticInst(_mnemonic, _machInst, No_OpClass)
        {
            // don't call execute() (which panics) if we're on a
            // speculative path
            flags[IsNonSpeculative] = true;
        }

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

    /**
     * Base class for unimplemented instructions that cause a warning
     * to be printed (but do not terminate simulation).  This
     * implementation is a little screwy in that it will print a
     * warning for each instance of a particular unimplemented machine
     * instruction, not just for each unimplemented opcode.  Should
     * probably make the 'warned' flag a static member of the derived
     * class.
     */
    class WarnUnimplemented : public MipsStaticInst
    {
      private:
        /// Have we warned on this instruction yet?
        mutable bool warned;

      public:
        /// Constructor
        WarnUnimplemented(const char *_mnemonic, MachInst _machInst)
            : MipsStaticInst(_mnemonic, _machInst, No_OpClass), warned(false)
        {
            // don't call execute() (which panics) if we're on a
            // speculative path
            flags[IsNonSpeculative] = true;
        }

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

    /**
     * Static instruction class for unknown (illegal) instructions.
     * These cause simulator termination if they are executed in a
     * non-speculative mode.  This is a leaf class.
     */
    class Unknown : public MipsStaticInst
    {
      public:
        /// Constructor
        Unknown(MachInst _machInst)
            : MipsStaticInst("unknown", _machInst, No_OpClass)
        {
            // don't call execute() (which panics) if we're on a
            // speculative path
            flags[IsNonSpeculative] = true;
        }

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        std::string
        generateDisassembly(Addr pc, const SymbolTable *symtab) const;
    };

// BasicOp::movf(['\n                            Rd = (getCondCode(FCSR, CC) == 0) ? Rd : Rs;\n                        '],{})

        /**
         * Static instruction class for "movf".
         */
        class Movf : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movf(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movt(['\n                            Rd = (getCondCode(FCSR, CC) == 1) ? Rd : Rs;\n                        '],{})

        /**
         * Static instruction class for "movt".
         */
        class Movt : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movt(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::ssnop([';'],{})

        /**
         * Static instruction class for "ssnop".
         */
        class Ssnop : public MipsStaticInst
        {
          public:
                /// Constructor.
                Ssnop(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::ehb([';'],{})

        /**
         * Static instruction class for "ehb".
         */
        class Ehb : public MipsStaticInst
        {
          public:
                /// Constructor.
                Ehb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Nop::nop(([], {}))

// BasicOp::sll([' Rd = Rt_uw << SA; '],{})

        /**
         * Static instruction class for "sll".
         */
        class Sll : public MipsStaticInst
        {
          public:
                /// Constructor.
                Sll(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::srl([' Rd = Rt_uw >> SA; '],{})

        /**
         * Static instruction class for "srl".
         */
        class Srl : public MipsStaticInst
        {
          public:
                /// Constructor.
                Srl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::rotr(['\n                                Rd = (Rt_uw << (32 - SA)) | (Rt_uw >> SA);\n                            '],{})

        /**
         * Static instruction class for "rotr".
         */
        class Rotr : public MipsStaticInst
        {
          public:
                /// Constructor.
                Rotr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::sra(['\n                            uint32_t temp = Rt >> SA;\n                            if ( (Rt & 0x80000000) > 0 ) {\n                                uint32_t mask = 0x80000000;\n                                for(int i=0; i < SA; i++) {\n                                    temp |= mask;\n                                    mask = mask >> 1;\n                                }\n                            }\n                            Rd = temp;\n                        '],{})

        /**
         * Static instruction class for "sra".
         */
        class Sra : public MipsStaticInst
        {
          public:
                /// Constructor.
                Sra(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::sllv([' Rd = Rt_uw << Rs<4:0>; '],{})

        /**
         * Static instruction class for "sllv".
         */
        class Sllv : public MipsStaticInst
        {
          public:
                /// Constructor.
                Sllv(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::srlv([' Rd = Rt_uw >> Rs<4:0>; '],{})

        /**
         * Static instruction class for "srlv".
         */
        class Srlv : public MipsStaticInst
        {
          public:
                /// Constructor.
                Srlv(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::rotrv(['\n                            Rd = (Rt_uw << (32 - Rs<4:0>)) |\n                                 (Rt_uw >> Rs<4:0>);\n                        '],{})

        /**
         * Static instruction class for "rotrv".
         */
        class Rotrv : public MipsStaticInst
        {
          public:
                /// Constructor.
                Rotrv(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::srav(['\n                        int shift_amt = Rs<4:0>;\n\n                        uint32_t temp = Rt >> shift_amt;\n\n                        if ((Rt & 0x80000000) > 0) {\n                            uint32_t mask = 0x80000000;\n                            for (int i = 0; i < shift_amt; i++) {\n                                temp |= mask;\n                                mask = mask >> 1;\n                            }\n                        }\n                        Rd = temp;\n                    '],{})

        /**
         * Static instruction class for "srav".
         */
        class Srav : public MipsStaticInst
        {
          public:
                /// Constructor.
                Srav(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Jump::jr_hb(['\n                            Config1Reg config1 = Config1;\n                            if (config1.ca == 0) {\n                                NNPC = Rs;\n                            } else {\n                                panic("MIPS16e not supported\\n");\n                            }\n                        ', 'IsReturn', 'ClearHazards'],{})

        /**
         * Static instruction class for "jr_hb".
         */
        class Jr_hb : public Jump
        {
          public:
                /// Constructor.
                Jr_hb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Jump::jr(['\n                            Config1Reg config1 = Config1;\n                            if (config1.ca == 0) {\n                                NNPC = Rs;\n                            } else {\n                                panic("MIPS16e not supported\\n");\n                            }\n                        ', 'IsReturn'],{})

        /**
         * Static instruction class for "jr".
         */
        class Jr : public Jump
        {
          public:
                /// Constructor.
                Jr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Jump::jalr_hb(['\n                            Rd = NNPC;\n                            NNPC = Rs;\n                        ', 'IsCall', 'ClearHazards'],{})

        /**
         * Static instruction class for "jalr_hb".
         */
        class Jalr_hb : public Jump
        {
          public:
                /// Constructor.
                Jalr_hb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Jump::jalr(['\n                            Rd = NNPC;\n                            NNPC = Rs;\n                        ', 'IsCall'],{})

        /**
         * Static instruction class for "jalr".
         */
        class Jalr : public Jump
        {
          public:
                /// Constructor.
                Jalr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movz([' Rd = (Rt == 0) ? Rs : Rd; '],{})

        /**
         * Static instruction class for "movz".
         */
        class Movz : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movz(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movn([' Rd = (Rt != 0) ? Rs : Rd; '],{})

        /**
         * Static instruction class for "movn".
         */
        class Movn : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movn(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::syscall_se([' xc->syscall(R2); ', 'IsSerializeAfter', 'IsNonSpeculative'],{})

        /**
         * Static instruction class for "syscall_se".
         */
        class Syscall_se : public MipsStaticInst
        {
          public:
                /// Constructor.
                Syscall_se(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::syscall([' fault = new SystemCallFault(); '],{})

        /**
         * Static instruction class for "syscall".
         */
        class Syscall : public MipsStaticInst
        {
          public:
                /// Constructor.
                Syscall(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::sync([' ; ', 'IsMemBarrier'],{})

        /**
         * Static instruction class for "sync".
         */
        class Sync : public MipsStaticInst
        {
          public:
                /// Constructor.
                Sync(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::break(['fault = new BreakpointFault();'],{})

        /**
         * Static instruction class for "break".
         */
        class Break : public MipsStaticInst
        {
          public:
                /// Constructor.
                Break(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// HiLoRsSelOp::mfhi(([' Rd = HI_RS_SEL; ', 'IntMultOp', 'IsIprAccess'], {}))

        /**
         * Static instruction class for "mfhi".
         */
        class Mfhi : public HiLoRsSelOp
        {
          public:
                /// Constructor.
                Mfhi(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelOp::mthi(([' HI_RD_SEL = Rs; '], {}))

        /**
         * Static instruction class for "mthi".
         */
        class Mthi : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Mthi(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRsSelOp::mflo(([' Rd = LO_RS_SEL; ', 'IntMultOp', 'IsIprAccess'], {}))

        /**
         * Static instruction class for "mflo".
         */
        class Mflo : public HiLoRsSelOp
        {
          public:
                /// Constructor.
                Mflo(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelOp::mtlo(([' LO_RD_SEL = Rs; '], {}))

        /**
         * Static instruction class for "mtlo".
         */
        class Mtlo : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Mtlo(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// HiLoRdSelValOp::mult([' val = Rs_sd * Rt_sd; ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mult".
         */
        class Mult : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Mult(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelValOp::multu([' val = Rs_ud * Rt_ud; ', 'IntMultOp'],{})

        /**
         * Static instruction class for "multu".
         */
        class Multu : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Multu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoOp::div(['\n                        if (Rt_sd != 0) {\n                            HI0 = Rs_sd % Rt_sd;\n                            LO0 = Rs_sd / Rt_sd;\n                        }\n                    ', 'IntDivOp'],{})

        /**
         * Static instruction class for "div".
         */
        class Div : public HiLoOp
        {
          public:
                /// Constructor.
                Div(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoOp::divu(['\n                        if (Rt_ud != 0) {\n                            HI0 = Rs_ud % Rt_ud;\n                            LO0 = Rs_ud / Rt_ud;\n                        }\n                    ', 'IntDivOp'],{})

        /**
         * Static instruction class for "divu".
         */
        class Divu : public HiLoOp
        {
          public:
                /// Constructor.
                Divu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// IntOp::add(['\n                            IntReg result;\n                            Rd = result = Rs + Rt;\n                            if (FullSystem &&\n                                    findOverflow(32, result, Rs, Rt)) {\n                                fault = new IntegerOverflowFault();\n                            }\n                        '],{})

        /**
         * Static instruction class for "add".
         */
        class Add : public IntOp
        {
          public:
                /// Constructor.
                Add(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::addu([' Rd_sw = Rs_sw + Rt_sw;'],{})

        /**
         * Static instruction class for "addu".
         */
        class Addu : public IntOp
        {
          public:
                /// Constructor.
                Addu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::sub(['\n                            IntReg result;\n                            Rd = result = Rs - Rt;\n                            if (FullSystem &&\n                                    findOverflow(32, result, Rs, ~Rt)) {\n                                fault = new IntegerOverflowFault();\n                            }\n                        '],{})

        /**
         * Static instruction class for "sub".
         */
        class Sub : public IntOp
        {
          public:
                /// Constructor.
                Sub(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::subu([' Rd_sw = Rs_sw - Rt_sw; '],{})

        /**
         * Static instruction class for "subu".
         */
        class Subu : public IntOp
        {
          public:
                /// Constructor.
                Subu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::and([' Rd = Rs & Rt; '],{})

        /**
         * Static instruction class for "and".
         */
        class And : public IntOp
        {
          public:
                /// Constructor.
                And(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::or([' Rd = Rs | Rt; '],{})

        /**
         * Static instruction class for "or".
         */
        class Or : public IntOp
        {
          public:
                /// Constructor.
                Or(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::xor([' Rd = Rs ^ Rt; '],{})

        /**
         * Static instruction class for "xor".
         */
        class Xor : public IntOp
        {
          public:
                /// Constructor.
                Xor(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::nor([' Rd = ~(Rs | Rt); '],{})

        /**
         * Static instruction class for "nor".
         */
        class Nor : public IntOp
        {
          public:
                /// Constructor.
                Nor(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// IntOp::slt(['  Rd_sw = (Rs_sw < Rt_sw) ? 1 : 0 '],{})

        /**
         * Static instruction class for "slt".
         */
        class Slt : public IntOp
        {
          public:
                /// Constructor.
                Slt(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::sltu([' Rd_uw = (Rs_uw < Rt_uw) ? 1 : 0 '],{})

        /**
         * Static instruction class for "sltu".
         */
        class Sltu : public IntOp
        {
          public:
                /// Constructor.
                Sltu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Trap::tge(['  cond = (Rs_sw >= Rt_sw); '],{})

        /**
         * Static instruction class for "tge".
         */
        class Tge : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tge(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Trap::tgeu([' cond = (Rs_uw >= Rt_uw); '],{})

        /**
         * Static instruction class for "tgeu".
         */
        class Tgeu : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tgeu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Trap::tlt([' cond = (Rs_sw < Rt_sw); '],{})

        /**
         * Static instruction class for "tlt".
         */
        class Tlt : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tlt(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Trap::tltu([' cond = (Rs_uw < Rt_uw); '],{})

        /**
         * Static instruction class for "tltu".
         */
        class Tltu : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tltu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Trap::teq([' cond = (Rs_sw == Rt_sw); '],{})

        /**
         * Static instruction class for "teq".
         */
        class Teq : public MipsStaticInst
        {
          public:
                /// Constructor.
                Teq(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Trap::tne([' cond = (Rs_sw != Rt_sw); '],{})

        /**
         * Static instruction class for "tne".
         */
        class Tne : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tne(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Branch::bltz([' cond = (Rs_sw < 0); '],{})

        /**
         * Static instruction class for "bltz".
         */
        class Bltz : public Branch
        {
          public:
                /// Constructor.
                Bltz(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bgez([' cond = (Rs_sw >= 0); '],{})

        /**
         * Static instruction class for "bgez".
         */
        class Bgez : public Branch
        {
          public:
                /// Constructor.
                Bgez(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bltzl([' cond = (Rs_sw < 0); ', 'Likely'],{})

        /**
         * Static instruction class for "bltzl".
         */
        class Bltzl : public Branch
        {
          public:
                /// Constructor.
                Bltzl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bgezl([' cond = (Rs_sw >= 0); ', 'Likely'],{})

        /**
         * Static instruction class for "bgezl".
         */
        class Bgezl : public Branch
        {
          public:
                /// Constructor.
                Bgezl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// TrapImm::tgei([' cond = (Rs_sw >= (int16_t)INTIMM); '],{})

        /**
         * Static instruction class for "tgei".
         */
        class Tgei : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tgei(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// TrapImm::tgeiu(['\n                        cond = (Rs_uw >= (uint32_t)(int32_t)(int16_t)INTIMM);\n                    '],{})

        /**
         * Static instruction class for "tgeiu".
         */
        class Tgeiu : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tgeiu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// TrapImm::tlti([' cond = (Rs_sw < (int16_t)INTIMM); '],{})

        /**
         * Static instruction class for "tlti".
         */
        class Tlti : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tlti(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// TrapImm::tltiu(['\n                        cond = (Rs_uw < (uint32_t)(int32_t)(int16_t)INTIMM);\n                    '],{})

        /**
         * Static instruction class for "tltiu".
         */
        class Tltiu : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tltiu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// TrapImm::teqi([' cond = (Rs_sw == (int16_t)INTIMM); '],{})

        /**
         * Static instruction class for "teqi".
         */
        class Teqi : public MipsStaticInst
        {
          public:
                /// Constructor.
                Teqi(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// TrapImm::tnei([' cond = (Rs_sw != (int16_t)INTIMM); '],{})

        /**
         * Static instruction class for "tnei".
         */
        class Tnei : public MipsStaticInst
        {
          public:
                /// Constructor.
                Tnei(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Branch::bltzal([' cond = (Rs_sw < 0); ', 'Link'],{})

        /**
         * Static instruction class for "bltzal".
         */
        class Bltzal : public Branch
        {
          public:
                /// Constructor.
                Bltzal(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bal([' cond = 1; ', 'IsCall', 'Link'],{})

        /**
         * Static instruction class for "bal".
         */
        class Bal : public Branch
        {
          public:
                /// Constructor.
                Bal(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bgezal([' cond = (Rs_sw >= 0); ', 'Link'],{})

        /**
         * Static instruction class for "bgezal".
         */
        class Bgezal : public Branch
        {
          public:
                /// Constructor.
                Bgezal(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bltzall([' cond = (Rs_sw < 0); ', 'Link', 'Likely'],{})

        /**
         * Static instruction class for "bltzall".
         */
        class Bltzall : public Branch
        {
          public:
                /// Constructor.
                Bltzall(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bgezall([' cond = (Rs_sw >= 0); ', 'Link', 'Likely'],{})

        /**
         * Static instruction class for "bgezall".
         */
        class Bgezall : public Branch
        {
          public:
                /// Constructor.
                Bgezall(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspBranch::bposge32(([' cond = (dspctl<5:0> >= 32); '], {}))

        /**
         * Static instruction class for "bposge32".
         */
        class Bposge32 : public Branch
        {
          public:
                /// Constructor.
                Bposge32(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// WarnUnimpl::synci([],{})

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Jump::j([' NNPC = (NPC & 0xF0000000) | (JMPTARG << 2); '],{})

        /**
         * Static instruction class for "j".
         */
        class J : public Jump
        {
          public:
                /// Constructor.
                J(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Jump::jal([' NNPC = (NPC & 0xF0000000) | (JMPTARG << 2); ', 'IsCall', 'Link'],{})

        /**
         * Static instruction class for "jal".
         */
        class Jal : public Jump
        {
          public:
                /// Constructor.
                Jal(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::b([' cond = 1; '],{})

        /**
         * Static instruction class for "b".
         */
        class B : public Branch
        {
          public:
                /// Constructor.
                B(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::beq([' cond = (Rs_sw == Rt_sw); '],{})

        /**
         * Static instruction class for "beq".
         */
        class Beq : public Branch
        {
          public:
                /// Constructor.
                Beq(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bne([' cond = (Rs_sw != Rt_sw); '],{})

        /**
         * Static instruction class for "bne".
         */
        class Bne : public Branch
        {
          public:
                /// Constructor.
                Bne(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::blez([' cond = (Rs_sw <= 0); '],{})

        /**
         * Static instruction class for "blez".
         */
        class Blez : public Branch
        {
          public:
                /// Constructor.
                Blez(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bgtz([' cond = (Rs_sw > 0); '],{})

        /**
         * Static instruction class for "bgtz".
         */
        class Bgtz : public Branch
        {
          public:
                /// Constructor.
                Bgtz(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// IntImmOp::addi(['\n                IntReg result;\n                Rt = result = Rs + imm;\n                if (FullSystem &&\n                        findOverflow(32, result, Rs, imm)) {\n                    fault = new IntegerOverflowFault();\n                }\n            '],{})

        /**
         * Static instruction class for "addi".
         */
        class Addi : public IntImmOp
        {
          public:
                /// Constructor.
                Addi(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::addiu([' Rt_sw = Rs_sw + imm; '],{})

        /**
         * Static instruction class for "addiu".
         */
        class Addiu : public IntImmOp
        {
          public:
                /// Constructor.
                Addiu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::slti([' Rt_sw = (Rs_sw < imm) ? 1 : 0 '],{})

        /**
         * Static instruction class for "slti".
         */
        class Slti : public IntImmOp
        {
          public:
                /// Constructor.
                Slti(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::sltiu([' Rt_uw = (Rs_uw < (uint32_t)sextImm) ? 1 : 0;'],{})

        /**
         * Static instruction class for "sltiu".
         */
        class Sltiu : public IntImmOp
        {
          public:
                /// Constructor.
                Sltiu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::andi([' Rt_sw = Rs_sw & zextImm; '],{})

        /**
         * Static instruction class for "andi".
         */
        class Andi : public IntImmOp
        {
          public:
                /// Constructor.
                Andi(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::ori([' Rt_sw = Rs_sw | zextImm; '],{})

        /**
         * Static instruction class for "ori".
         */
        class Ori : public IntImmOp
        {
          public:
                /// Constructor.
                Ori(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::xori([' Rt_sw = Rs_sw ^ zextImm; '],{})

        /**
         * Static instruction class for "xori".
         */
        class Xori : public IntImmOp
        {
          public:
                /// Constructor.
                Xori(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntImmOp::lui([' Rt = imm << 16; '],{})

        /**
         * Static instruction class for "lui".
         */
        class Lui : public IntImmOp
        {
          public:
                /// Constructor.
                Lui(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP0Control::mfc0(['\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        Rt = CP0_RD_SEL;\n                        /* Hack for PageMask */\n                        if (RD == 5) {\n                            // PageMask\n                            if (config3.sp == 0 || pageGrain.esp == 0)\n                                Rt &= 0xFFFFE7FF;\n                        }\n                    '],{})

        /**
         * Static instruction class for "mfc0".
         */
        class Mfc0 : public CP0Control
        {
          public:
                /// Constructor.
                Mfc0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Control::mtc0([' \n                        CP0_RD_SEL = Rt;\n                        CauseReg cause = Cause;\n                        IntCtlReg intCtl = IntCtl;\n                        if (RD == 11) {\n                            // Compare\n                            if (cause.ti == 1) {\n                                cause.ti = 0;\n                                int offset = 10; // corresponding to cause.ip0\n                                offset += intCtl.ipti - 2;\n                                replaceBits(cause, offset, offset, 0);\n                            }\n                        }\n                        Cause = cause;\n                    '],{})

        /**
         * Static instruction class for "mtc0".
         */
        class Mtc0 : public CP0Control
        {
          public:
                /// Constructor.
                Mtc0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::dmfc0([],{})

// CP0Unimpl::dmtc0([],{})

// CP0Unimpl::unknown([],{})

// MT_MFTR::mftc0(['\n                            data = xc->readRegOtherThread((RT << 3 | SEL) +\n                                                          Misc_Reg_Base);\n                        '],{})

        /**
         * Static instruction class for "mftc0".
         */
        class Mftc0 : public MTOp
        {
          public:
                /// Constructor.
                Mftc0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftgpr(['\n                                data = xc->readRegOtherThread(RT);\n                            '],{})

        /**
         * Static instruction class for "mftgpr".
         */
        class Mftgpr : public MTOp
        {
          public:
                /// Constructor.
                Mftgpr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftlo_dsp0([' data = xc->readRegOtherThread(INTREG_DSP_LO0); '],{})

        /**
         * Static instruction class for "mftlo_dsp0".
         */
        class Mftlo_dsp0 : public MTOp
        {
          public:
                /// Constructor.
                Mftlo_dsp0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mfthi_dsp0([' data = xc->readRegOtherThread(INTREG_DSP_HI0); '],{})

        /**
         * Static instruction class for "mfthi_dsp0".
         */
        class Mfthi_dsp0 : public MTOp
        {
          public:
                /// Constructor.
                Mfthi_dsp0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftacx_dsp0([' data = xc->readRegOtherThread(INTREG_DSP_ACX0); '],{})

        /**
         * Static instruction class for "mftacx_dsp0".
         */
        class Mftacx_dsp0 : public MTOp
        {
          public:
                /// Constructor.
                Mftacx_dsp0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftlo_dsp1([' data = xc->readRegOtherThread(INTREG_DSP_LO1); '],{})

        /**
         * Static instruction class for "mftlo_dsp1".
         */
        class Mftlo_dsp1 : public MTOp
        {
          public:
                /// Constructor.
                Mftlo_dsp1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mfthi_dsp1([' data = xc->readRegOtherThread(INTREG_DSP_HI1); '],{})

        /**
         * Static instruction class for "mfthi_dsp1".
         */
        class Mfthi_dsp1 : public MTOp
        {
          public:
                /// Constructor.
                Mfthi_dsp1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftacx_dsp1([' data = xc->readRegOtherThread(INTREG_DSP_ACX1); '],{})

        /**
         * Static instruction class for "mftacx_dsp1".
         */
        class Mftacx_dsp1 : public MTOp
        {
          public:
                /// Constructor.
                Mftacx_dsp1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftlo_dsp2([' data = xc->readRegOtherThread(INTREG_DSP_LO2); '],{})

        /**
         * Static instruction class for "mftlo_dsp2".
         */
        class Mftlo_dsp2 : public MTOp
        {
          public:
                /// Constructor.
                Mftlo_dsp2(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mfthi_dsp2([' data = xc->readRegOtherThread(INTREG_DSP_HI2); '],{})

        /**
         * Static instruction class for "mfthi_dsp2".
         */
        class Mfthi_dsp2 : public MTOp
        {
          public:
                /// Constructor.
                Mfthi_dsp2(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftacx_dsp2([' data = xc->readRegOtherThread(INTREG_DSP_ACX2); '],{})

        /**
         * Static instruction class for "mftacx_dsp2".
         */
        class Mftacx_dsp2 : public MTOp
        {
          public:
                /// Constructor.
                Mftacx_dsp2(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftlo_dsp3([' data = xc->readRegOtherThread(INTREG_DSP_LO3); '],{})

        /**
         * Static instruction class for "mftlo_dsp3".
         */
        class Mftlo_dsp3 : public MTOp
        {
          public:
                /// Constructor.
                Mftlo_dsp3(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mfthi_dsp3([' data = xc->readRegOtherThread(INTREG_DSP_HI3); '],{})

        /**
         * Static instruction class for "mfthi_dsp3".
         */
        class Mfthi_dsp3 : public MTOp
        {
          public:
                /// Constructor.
                Mfthi_dsp3(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftacx_dsp3([' data = xc->readRegOtherThread(INTREG_DSP_ACX3); '],{})

        /**
         * Static instruction class for "mftacx_dsp3".
         */
        class Mftacx_dsp3 : public MTOp
        {
          public:
                /// Constructor.
                Mftacx_dsp3(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mftdsp([' data = xc->readRegOtherThread(INTREG_DSP_CONTROL); '],{})

        /**
         * Static instruction class for "mftdsp".
         */
        class Mftdsp : public MTOp
        {
          public:
                /// Constructor.
                Mftdsp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// MT_MFTR::mftc1([' data = xc->readRegOtherThread(RT +\n                                                                            FP_Reg_Base);\n                                '],{})

        /**
         * Static instruction class for "mftc1".
         */
        class Mftc1 : public MTOp
        {
          public:
                /// Constructor.
                Mftc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MFTR::mfthc1([' data = xc->readRegOtherThread(RT +\n                                                                             FP_Reg_Base);\n                                '],{})

        /**
         * Static instruction class for "mfthc1".
         */
        class Mfthc1 : public MTOp
        {
          public:
                /// Constructor.
                Mfthc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// MT_MFTR::cftc1(['\n                                uint32_t fcsr_val = xc->readRegOtherThread(FLOATREG_FCSR +\n                                                                            FP_Reg_Base);\n                                switch (RT) {\n                                  case 0:\n                                    data = xc->readRegOtherThread(FLOATREG_FIR +\n                                                                  Misc_Reg_Base);\n                                    break;\n                                  case 25:\n                                    data = (fcsr_val & 0xFE000000 >> 24) |\n                                           (fcsr_val & 0x00800000 >> 23);\n                                    break;\n                                  case 26:\n                                    data = fcsr_val & 0x0003F07C;\n                                    break;\n                                  case 28:\n                                    data = (fcsr_val & 0x00000F80) |\n                                           (fcsr_val & 0x01000000 >> 21) |\n                                           (fcsr_val & 0x00000003);\n                                    break;\n                                  case 31:\n                                    data = fcsr_val;\n                                    break;\n                                  default:\n                                    fatal("FP Control Value (%d) Not Valid");\n                                }\n                            '],{})

        /**
         * Static instruction class for "cftc1".
         */
        class Cftc1 : public MTOp
        {
          public:
                /// Constructor.
                Cftc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// MT_MTTR::mttc0([' xc->setRegOtherThread((RD << 3 | SEL) + Misc_Reg_Base,\n                                                            Rt);\n                                   '],{})

        /**
         * Static instruction class for "mttc0".
         */
        class Mttc0 : public MTOp
        {
          public:
                /// Constructor.
                Mttc0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttgpr([' xc->setRegOtherThread(RD, Rt); '],{})

        /**
         * Static instruction class for "mttgpr".
         */
        class Mttgpr : public MTOp
        {
          public:
                /// Constructor.
                Mttgpr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttlo_dsp0([' xc->setRegOtherThread(INTREG_DSP_LO0, Rt);\n                                                '],{})

        /**
         * Static instruction class for "mttlo_dsp0".
         */
        class Mttlo_dsp0 : public MTOp
        {
          public:
                /// Constructor.
                Mttlo_dsp0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mtthi_dsp0([' xc->setRegOtherThread(INTREG_DSP_HI0,\n                                                                         Rt);\n                                                '],{})

        /**
         * Static instruction class for "mtthi_dsp0".
         */
        class Mtthi_dsp0 : public MTOp
        {
          public:
                /// Constructor.
                Mtthi_dsp0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttacx_dsp0([' xc->setRegOtherThread(INTREG_DSP_ACX0,\n                                                                          Rt);\n                                                 '],{})

        /**
         * Static instruction class for "mttacx_dsp0".
         */
        class Mttacx_dsp0 : public MTOp
        {
          public:
                /// Constructor.
                Mttacx_dsp0(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttlo_dsp1([' xc->setRegOtherThread(INTREG_DSP_LO1,\n                                                                         Rt);\n                                                '],{})

        /**
         * Static instruction class for "mttlo_dsp1".
         */
        class Mttlo_dsp1 : public MTOp
        {
          public:
                /// Constructor.
                Mttlo_dsp1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mtthi_dsp1([' xc->setRegOtherThread(INTREG_DSP_HI1,\n                                                                         Rt);\n                                                '],{})

        /**
         * Static instruction class for "mtthi_dsp1".
         */
        class Mtthi_dsp1 : public MTOp
        {
          public:
                /// Constructor.
                Mtthi_dsp1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttacx_dsp1([' xc->setRegOtherThread(INTREG_DSP_ACX1,\n                                                                          Rt);\n                                                 '],{})

        /**
         * Static instruction class for "mttacx_dsp1".
         */
        class Mttacx_dsp1 : public MTOp
        {
          public:
                /// Constructor.
                Mttacx_dsp1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttlo_dsp2([' xc->setRegOtherThread(INTREG_DSP_LO2,\n                                                                         Rt);\n                                                '],{})

        /**
         * Static instruction class for "mttlo_dsp2".
         */
        class Mttlo_dsp2 : public MTOp
        {
          public:
                /// Constructor.
                Mttlo_dsp2(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mtthi_dsp2([' xc->setRegOtherThread(INTREG_DSP_HI2,\n                                                                         Rt);\n                                                '],{})

        /**
         * Static instruction class for "mtthi_dsp2".
         */
        class Mtthi_dsp2 : public MTOp
        {
          public:
                /// Constructor.
                Mtthi_dsp2(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttacx_dsp2([' xc->setRegOtherThread(INTREG_DSP_ACX2,\n                                                                           Rt);\n                                                  '],{})

        /**
         * Static instruction class for "mttacx_dsp2".
         */
        class Mttacx_dsp2 : public MTOp
        {
          public:
                /// Constructor.
                Mttacx_dsp2(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttlo_dsp3([' xc->setRegOtherThread(INTREG_DSP_LO3,\n                                                                          Rt);\n                                                 '],{})

        /**
         * Static instruction class for "mttlo_dsp3".
         */
        class Mttlo_dsp3 : public MTOp
        {
          public:
                /// Constructor.
                Mttlo_dsp3(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mtthi_dsp3([' xc->setRegOtherThread(INTREG_DSP_HI3,\n                                                                          Rt);\n                                                 '],{})

        /**
         * Static instruction class for "mtthi_dsp3".
         */
        class Mtthi_dsp3 : public MTOp
        {
          public:
                /// Constructor.
                Mtthi_dsp3(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttacx_dsp3([' xc->setRegOtherThread(INTREG_DSP_ACX3, Rt);\n                                                  '],{})

        /**
         * Static instruction class for "mttacx_dsp3".
         */
        class Mttacx_dsp3 : public MTOp
        {
          public:
                /// Constructor.
                Mttacx_dsp3(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::mttdsp([' xc->setRegOtherThread(INTREG_DSP_CONTROL, Rt); '],{})

        /**
         * Static instruction class for "mttdsp".
         */
        class Mttdsp : public MTOp
        {
          public:
                /// Constructor.
                Mttdsp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// MT_MTTR::mttc1(['\n                                uint64_t data = xc->readRegOtherThread(RD +\n                                                                       FP_Reg_Base);\n                                data = insertBits(data, MT_H ? 63 : 31,\n                                                  MT_H ? 32 : 0, Rt);\n                                xc->setRegOtherThread(RD + FP_Reg_Base,\n                                                      data);\n                            '],{})

        /**
         * Static instruction class for "mttc1".
         */
        class Mttc1 : public MTOp
        {
          public:
                /// Constructor.
                Mttc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_MTTR::cttc1(['\n                                uint32_t data;\n                                switch (RD) {\n                                  case 25:\n                                    data = (Rt_uw<7:1> << 25) |  // move 31-25\n                                           (FCSR & 0x01000000) | // bit 24\n                                           (FCSR & 0x004FFFFF);  // bit 22-0\n                                    break;\n                                  case 26:\n                                    data = (FCSR & 0xFFFC0000) | // move 31-18\n                                           Rt_uw<17:12> << 12 |  // bit 17-12\n                                           (FCSR & 0x00000F80) << 7 | // bit 11-7\n                                           Rt_uw<6:2> << 2 |     // bit 6-2\n                                           (FCSR & 0x00000002);  // bit 1...0\n                                    break;\n                                  case 28:\n                                    data = (FCSR & 0xFE000000) | // move 31-25\n                                           Rt_uw<2:2> << 24 |    // bit 24\n                                           (FCSR & 0x00FFF000) << 23 | // bit 23-12\n                                           Rt_uw<11:7> << 7 |    // bit 24\n                                           (FCSR & 0x000007E) |\n                                           Rt_uw<1:0>;           // bit 22-0\n                                    break;\n                                  case 31:\n                                    data = Rt_uw;\n                                    break;\n                                  default:\n                                    panic("FP Control Value (%d) "\n                                            "Not Available. Ignoring "\n                                            "Access to Floating Control "\n                                            "S""tatus Register", FS);\n                                }\n                                xc->setRegOtherThread(FLOATREG_FCSR + FP_Reg_Base, data);\n                            '],{})

        /**
         * Static instruction class for "cttc1".
         */
        class Cttc1 : public MTOp
        {
          public:
                /// Constructor.
                Cttc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// MT_Control::dvpe(['\n                                        MVPControlReg mvpControl = MVPControl;\n                                        VPEConf0Reg vpeConf0 = VPEConf0;\n                                        Rt = MVPControl;\n                                        if (vpeConf0.mvp == 1)\n                                            mvpControl.evp = 0;\n                                        MVPControl = mvpControl;\n                                    '],{})

        /**
         * Static instruction class for "dvpe".
         */
        class Dvpe : public MTOp
        {
          public:
                /// Constructor.
                Dvpe(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_Control::evpe(['\n                                        MVPControlReg mvpControl = MVPControl;\n                                        VPEConf0Reg vpeConf0 = VPEConf0;\n                                        Rt = MVPControl;\n                                        if (vpeConf0.mvp == 1)\n                                            mvpControl.evp = 1;\n                                        MVPControl = mvpControl;\n                                    '],{})

        /**
         * Static instruction class for "evpe".
         */
        class Evpe : public MTOp
        {
          public:
                /// Constructor.
                Evpe(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// MT_Control::dmt(['\n                                        VPEControlReg vpeControl = VPEControl;\n                                        Rt = vpeControl;\n                                        vpeControl.te = 0;\n                                        VPEControl = vpeControl;\n                                    '],{})

        /**
         * Static instruction class for "dmt".
         */
        class Dmt : public MTOp
        {
          public:
                /// Constructor.
                Dmt(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_Control::emt(['\n                                        VPEControlReg vpeControl = VPEControl;\n                                        Rt = vpeControl;\n                                        vpeControl.te = 1;\n                                        VPEControl = vpeControl;\n                                    '],{})

        /**
         * Static instruction class for "emt".
         */
        class Emt : public MTOp
        {
          public:
                /// Constructor.
                Emt(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Control::di((['\n                                StatusReg status = Status;\n                                ConfigReg config = Config;\n                                // Rev 2.0 or beyond?\n                                if (config.ar >= 1) {\n                                    Rt = status;\n                                    status.ie = 0;\n                                } else {\n                                    // Enable this else branch once we\n                                    // actually set values for Config on init\n                                    fault = new ReservedInstructionFault();\n                                }\n                                Status = status;\n                            '], {}))

        /**
         * Static instruction class for "di".
         */
        class Di : public CP0Control
        {
          public:
                /// Constructor.
                Di(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Control::ei((['\n                                StatusReg status = Status;\n                                ConfigReg config = Config;\n                                if (config.ar >= 1) {\n                                    Rt = status;\n                                    status.ie = 1;\n                                } else {\n                                    fault = new ReservedInstructionFault();\n                                }\n                            '], {}))

        /**
         * Static instruction class for "ei".
         */
        class Ei : public CP0Control
        {
          public:
                /// Constructor.
                Ei(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP0Unimpl::unknown(([], {}))

// CP0Control::rdpgpr(['\n                        ConfigReg config = Config;\n                        if (config.ar >= 1) {\n                            // Rev 2 of the architecture\n                            panic("Shadow Sets Not Fully Implemented.\\n");\n                        } else {\n                          fault = new ReservedInstructionFault();\n                        }\n                    '],{})

        /**
         * Static instruction class for "rdpgpr".
         */
        class Rdpgpr : public CP0Control
        {
          public:
                /// Constructor.
                Rdpgpr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Control::wrpgpr(['\n                        ConfigReg config = Config;\n                        if (config.ar >= 1) {\n                            // Rev 2 of the architecture\n                            panic("Shadow Sets Not Fully Implemented.\\n");\n                        } else {\n                            fault = new ReservedInstructionFault();\n                        }\n                    '],{})

        /**
         * Static instruction class for "wrpgpr".
         */
        class Wrpgpr : public CP0Control
        {
          public:
                /// Constructor.
                Wrpgpr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Control::eret(['\n                        StatusReg status = Status;\n                        ConfigReg config = Config;\n                        SRSCtlReg srsCtl = SRSCtl;\n                        DPRINTF(MipsPRA,"Restoring PC - %x\\n",EPC);\n                        if (status.erl == 1) {\n                            status.erl = 0;\n                            NPC = ErrorEPC;\n                            // Need to adjust NNPC, otherwise things break\n                            NNPC = ErrorEPC + sizeof(MachInst);\n                        } else {\n                            NPC = EPC;\n                            // Need to adjust NNPC, otherwise things break\n                            NNPC = EPC + sizeof(MachInst);\n                            status.exl = 0;\n                            if (config.ar >=1 &&\n                                    srsCtl.hss > 0 &&\n                                    status.bev == 0) {\n                                srsCtl.css = srsCtl.pss;\n                                //xc->setShadowSet(srsCtl.pss);\n                            }\n                        }\n                        LLFlag = 0;\n                        Status = status;\n                        SRSCtl = srsCtl;\n                    ', 'IsReturn', 'IsSerializing', 'IsERET'],{})

        /**
         * Static instruction class for "eret".
         */
        class Eret : public CP0Control
        {
          public:
                /// Constructor.
                Eret(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Control::deret(['\n                        DebugReg debug = Debug;\n                        if (debug.dm == 1) {\n                            debug.dm = 1;\n                            debug.iexi = 0;\n                            NPC = DEPC;\n                        } else {\n                            NPC = NPC;\n                            // Undefined;\n                        }\n                        Debug = debug;\n                    ', 'IsReturn', 'IsSerializing', 'IsERET'],{})

        /**
         * Static instruction class for "deret".
         */
        class Deret : public CP0Control
        {
          public:
                /// Constructor.
                Deret(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0TLB::tlbr(['\n                        MipsISA::PTE *PTEntry =\n                            xc->tcBase()->getITBPtr()->\n                                getEntry(Index & 0x7FFFFFFF);\n                        if (PTEntry == NULL) {\n                            fatal("Invalid PTE Entry received on "\n                                "a TLBR instruction\\n");\n                        }\n                        /* Setup PageMask */\n                        // If 1KB pages are not enabled, a read of PageMask\n                        // must return 0b00 in bits 12, 11\n                        PageMask = (PTEntry->Mask << 11);\n                        /* Setup EntryHi */\n                        EntryHi = ((PTEntry->VPN << 11) | (PTEntry->asid));\n                        /* Setup Entry Lo0 */\n                        EntryLo0 = ((PTEntry->PFN0 << 6) |\n                                    (PTEntry->C0 << 3) |\n                                    (PTEntry->D0 << 2) |\n                                    (PTEntry->V0 << 1) |\n                                    PTEntry->G);\n                        /* Setup Entry Lo1 */\n                        EntryLo1 = ((PTEntry->PFN1 << 6) |\n                                    (PTEntry->C1 << 3) |\n                                    (PTEntry->D1 << 2) |\n                                    (PTEntry->V1 << 1) |\n                                    PTEntry->G);\n                    '],{})

        /**
         * Static instruction class for "tlbr".
         */
        class Tlbr : public CP0Control
        {
          public:
                /// Constructor.
                Tlbr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0TLB::tlbwi(['\n                        //Create PTE\n                        MipsISA::PTE newEntry;\n                        //Write PTE\n                        newEntry.Mask = (Addr)(PageMask >> 11);\n                        newEntry.VPN = (Addr)(EntryHi >> 11);\n                        /*  PageGrain _ ESP                    Config3 _ SP */\n                        if (bits(PageGrain, 28) == 0 || bits(Config3, 4) ==0) {\n                            // If 1KB pages are *NOT* enabled, lowest bits of\n                            // the mask are 0b11 for TLB writes\n                            newEntry.Mask |= 0x3;\n                            // Reset bits 0 and 1 if 1KB pages are not enabled\n                            newEntry.VPN &= 0xFFFFFFFC;\n                        }\n                        newEntry.asid = (uint8_t)(EntryHi & 0xFF);\n\n                        newEntry.PFN0 = (Addr)(EntryLo0 >> 6);\n                        newEntry.PFN1 = (Addr)(EntryLo1 >> 6);\n                        newEntry.D0 = (bool)((EntryLo0 >> 2) & 1);\n                        newEntry.D1 = (bool)((EntryLo1 >> 2) & 1);\n                        newEntry.V1 = (bool)((EntryLo1 >> 1) & 1);\n                        newEntry.V0 = (bool)((EntryLo0 >> 1) & 1);\n                        newEntry.G = (bool)((EntryLo0 & EntryLo1) & 1);\n                        newEntry.C0 = (uint8_t)((EntryLo0 >> 3) & 0x7);\n                        newEntry.C1 = (uint8_t)((EntryLo1 >> 3) & 0x7);\n                        /* Now, compute the AddrShiftAmount and OffsetMask -\n                           TLB optimizations */\n                        /* Addr Shift Amount for 1KB or larger pages */\n                        if ((newEntry.Mask & 0xFFFF) == 3) {\n                            newEntry.AddrShiftAmount = 12;\n                        } else if ((newEntry.Mask & 0xFFFF) == 0x0000) {\n                            newEntry.AddrShiftAmount = 10;\n                        } else if ((newEntry.Mask & 0xFFFC) == 0x000C) {\n                            newEntry.AddrShiftAmount = 14;\n                        } else if ((newEntry.Mask & 0xFFF0) == 0x0030) {\n                            newEntry.AddrShiftAmount = 16;\n                        } else if ((newEntry.Mask & 0xFFC0) == 0x00C0) {\n                            newEntry.AddrShiftAmount = 18;\n                        } else if ((newEntry.Mask & 0xFF00) == 0x0300) {\n                            newEntry.AddrShiftAmount = 20;\n                        } else if ((newEntry.Mask & 0xFC00) == 0x0C00) {\n                            newEntry.AddrShiftAmount = 22;\n                        } else if ((newEntry.Mask & 0xF000) == 0x3000) {\n                            newEntry.AddrShiftAmount = 24;\n                        } else if ((newEntry.Mask & 0xC000) == 0xC000) {\n                            newEntry.AddrShiftAmount = 26;\n                        } else if ((newEntry.Mask & 0x30000) == 0x30000) {\n                            newEntry.AddrShiftAmount = 28;\n                        } else {\n                            fatal("Invalid Mask Pattern Detected!\\n");\n                        }\n                        newEntry.OffsetMask =\n                            (1 << newEntry.AddrShiftAmount) - 1;\n\n                        MipsISA::TLB *Ptr = xc->tcBase()->getITBPtr();\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        int SP = 0;\n                        if (bits(config3, config3.sp) == 1 &&\n                            bits(pageGrain, pageGrain.esp) == 1) {\n                            SP = 1;\n                        }\n                        Ptr->insertAt(newEntry, Index & 0x7FFFFFFF, SP);\n                    '],{})

        /**
         * Static instruction class for "tlbwi".
         */
        class Tlbwi : public CP0Control
        {
          public:
                /// Constructor.
                Tlbwi(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0TLB::tlbwr(['\n                        //Create PTE\n                        MipsISA::PTE newEntry;\n                        //Write PTE\n                        newEntry.Mask = (Addr)(PageMask >> 11);\n                        newEntry.VPN = (Addr)(EntryHi >> 11);\n                        /*  PageGrain _ ESP                    Config3 _ SP */\n                        if (bits(PageGrain, 28) == 0 ||\n                            bits(Config3, 4) == 0) {\n                            // If 1KB pages are *NOT* enabled, lowest bits of\n                            // the mask are 0b11 for TLB writes\n                            newEntry.Mask |= 0x3;\n                            // Reset bits 0 and 1 if 1KB pages are not enabled\n                            newEntry.VPN &= 0xFFFFFFFC;\n                        }\n                        newEntry.asid = (uint8_t)(EntryHi & 0xFF);\n\n                        newEntry.PFN0 = (Addr)(EntryLo0 >> 6);\n                        newEntry.PFN1 = (Addr)(EntryLo1 >> 6);\n                        newEntry.D0 = (bool)((EntryLo0 >> 2) & 1);\n                        newEntry.D1 = (bool)((EntryLo1 >> 2) & 1);\n                        newEntry.V1 = (bool)((EntryLo1 >> 1) & 1);\n                        newEntry.V0 = (bool)((EntryLo0 >> 1) & 1);\n                        newEntry.G = (bool)((EntryLo0 & EntryLo1) & 1);\n                        newEntry.C0 = (uint8_t)((EntryLo0 >> 3) & 0x7);\n                        newEntry.C1 = (uint8_t)((EntryLo1 >> 3) & 0x7);\n                        /* Now, compute the AddrShiftAmount and OffsetMask -\n                           TLB optimizations */\n                        /* Addr Shift Amount for 1KB or larger pages */\n                        if ((newEntry.Mask & 0xFFFF) == 3){\n                            newEntry.AddrShiftAmount = 12;\n                        } else if ((newEntry.Mask & 0xFFFF) == 0x0000) {\n                            newEntry.AddrShiftAmount = 10;\n                        } else if ((newEntry.Mask & 0xFFFC) == 0x000C) {\n                            newEntry.AddrShiftAmount = 14;\n                        } else if ((newEntry.Mask & 0xFFF0) == 0x0030) {\n                            newEntry.AddrShiftAmount = 16;\n                        } else if ((newEntry.Mask & 0xFFC0) == 0x00C0) {\n                            newEntry.AddrShiftAmount = 18;\n                        } else if ((newEntry.Mask & 0xFF00) == 0x0300) {\n                            newEntry.AddrShiftAmount = 20;\n                        } else if ((newEntry.Mask & 0xFC00) == 0x0C00) {\n                            newEntry.AddrShiftAmount = 22;\n                        } else if ((newEntry.Mask & 0xF000) == 0x3000) {\n                            newEntry.AddrShiftAmount = 24;\n                        } else if ((newEntry.Mask & 0xC000) == 0xC000) {\n                            newEntry.AddrShiftAmount = 26;\n                        } else if ((newEntry.Mask & 0x30000) == 0x30000) {\n                            newEntry.AddrShiftAmount = 28;\n                        } else {\n                            fatal("Invalid Mask Pattern Detected!\\n");\n                        }\n                        newEntry.OffsetMask =\n                            (1 << newEntry.AddrShiftAmount) - 1;\n\n                        MipsISA::TLB *Ptr = xc->tcBase()->getITBPtr();\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        int SP = 0;\n                        if (bits(config3, config3.sp) == 1 &&\n                            bits(pageGrain, pageGrain.esp) == 1) {\n                            SP = 1;\n                        }\n                        Ptr->insertAt(newEntry, Random, SP);\n                    '],{})

        /**
         * Static instruction class for "tlbwr".
         */
        class Tlbwr : public CP0Control
        {
          public:
                /// Constructor.
                Tlbwr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0TLB::tlbp(['\n                        Config3Reg config3 = Config3;\n                        PageGrainReg pageGrain = PageGrain;\n                        EntryHiReg entryHi = EntryHi;\n                        int tlbIndex;\n                        Addr vpn;\n                        if (pageGrain.esp == 1 && config3.sp ==1) {\n                            vpn = EntryHi >> 11;\n                        } else {\n                            // Mask off lower 2 bits\n                            vpn = ((EntryHi >> 11) & 0xFFFFFFFC);\n                        }\n                        tlbIndex = xc->tcBase()->getITBPtr()->\n                                   probeEntry(vpn, entryHi.asid);\n                        // Check TLB for entry matching EntryHi\n                        if (tlbIndex != -1) {\n                            Index = tlbIndex;\n                        } else {\n                            // else, set Index = 1 << 31\n                            Index = (1 << 31);\n                        }\n                    '],{})

        /**
         * Static instruction class for "tlbp".
         */
        class Tlbp : public CP0Control
        {
          public:
                /// Constructor.
                Tlbp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP0Unimpl::wait([],{})

// CP0Unimpl::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP1Control::mfc1([' Rt_uw = Fs_uw; '],{})

        /**
         * Static instruction class for "mfc1".
         */
        class Mfc1 : public CP1Control
        {
          public:
                /// Constructor.
                Mfc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Control::cfc1(['\n                            switch (FS) {\n                              case 0:\n                                Rt = FIR;\n                                break;\n                              case 25:\n                                Rt = (FCSR & 0xFE000000) >> 24 |\n                                     (FCSR & 0x00800000) >> 23;\n                                break;\n                              case 26:\n                                Rt = (FCSR & 0x0003F07C);\n                                break;\n                              case 28:\n                                Rt = (FCSR & 0x00000F80) |\n                                     (FCSR & 0x01000000) >> 21 |\n                                     (FCSR & 0x00000003);\n                                break;\n                              case 31:\n                                Rt = FCSR;\n                                break;\n                              default:\n                                warn("FP Control Value (%d) Not Valid");\n                            }\n                        '],{})

        /**
         * Static instruction class for "cfc1".
         */
        class Cfc1 : public CP1Control
        {
          public:
                /// Constructor.
                Cfc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Control::mfhc1([' Rt_uw = Fs_ud<63:32>; '],{})

        /**
         * Static instruction class for "mfhc1".
         */
        class Mfhc1 : public CP1Control
        {
          public:
                /// Constructor.
                Mfhc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Control::mtc1([' Fs_uw = Rt_uw; '],{})

        /**
         * Static instruction class for "mtc1".
         */
        class Mtc1 : public CP1Control
        {
          public:
                /// Constructor.
                Mtc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Control::ctc1(['\n                            switch (FS) {\n                              case 25:\n                                FCSR = (Rt_uw<7:1> << 25) |  // move 31-25\n                                       (FCSR & 0x01000000) | // bit 24\n                                       (FCSR & 0x004FFFFF);  // bit 22-0\n                                break;\n                              case 26:\n                                FCSR = (FCSR & 0xFFFC0000) | // move 31-18\n                                       Rt_uw<17:12> << 12 |  // bit 17-12\n                                       (FCSR & 0x00000F80) << 7 | // bit 11-7\n                                       Rt_uw<6:2> << 2 |     // bit 6-2\n                                       (FCSR & 0x00000002);  // bit 1-0\n                                break;\n                              case 28:\n                                FCSR = (FCSR & 0xFE000000) | // move 31-25\n                                       Rt_uw<2:2> << 24 |    // bit 24\n                                       (FCSR & 0x00FFF000) << 23 | // bit 23-12\n                                       Rt_uw<11:7> << 7 |    // bit 24\n                                       (FCSR & 0x000007E) |\n                                       Rt_uw<1:0>;           // bit 22-0\n                                break;\n                              case 31:\n                                FCSR = Rt_uw;\n                                break;\n\n                              default:\n                                panic("FP Control Value (%d) "\n                                        "Not Available. Ignoring Access "\n                                        "to Floating Control Status "\n                                        "Register", FS);\n                            }\n                        '],{})

        /**
         * Static instruction class for "ctc1".
         */
        class Ctc1 : public CP1Control
        {
          public:
                /// Constructor.
                Ctc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Control::mthc1(['\n                             uint64_t fs_hi = Rt_uw;\n                             uint64_t fs_lo = Fs_ud & 0x0FFFFFFFF;\n                             Fs_ud = (fs_hi << 32) | fs_lo;\n                        '],{})

        /**
         * Static instruction class for "mthc1".
         */
        class Mthc1 : public CP1Control
        {
          public:
                /// Constructor.
                Mthc1(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::dmfc1([],{})

// CP1Unimpl::dmtc1([],{})

// Unknown::unknown(([], {}))

// Branch::bc1f(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 0;\n                                '],{})

        /**
         * Static instruction class for "bc1f".
         */
        class Bc1f : public Branch
        {
          public:
                /// Constructor.
                Bc1f(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bc1t(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 1;\n                                '],{})

        /**
         * Static instruction class for "bc1t".
         */
        class Bc1t : public Branch
        {
          public:
                /// Constructor.
                Bc1t(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Branch::bc1fl(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 0;\n                                ', 'Likely'],{})

        /**
         * Static instruction class for "bc1fl".
         */
        class Bc1fl : public Branch
        {
          public:
                /// Constructor.
                Bc1fl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bc1tl(['\n                                    cond = getCondCode(FCSR, BRANCH_CC) == 1;\n                                ', 'Likely'],{})

        /**
         * Static instruction class for "bc1tl".
         */
        class Bc1tl : public Branch
        {
          public:
                /// Constructor.
                Bc1tl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// CP1Unimpl::bc1any2([],{})

// CP1Unimpl::bc1any4([],{})

// CP1Unimpl::unknown([],{})

// Unknown::unknown(([], {}))

// FloatOp::add_s([' Fd_sf = Fs_sf + Ft_sf; '],{})

        /**
         * Static instruction class for "add_s".
         */
        class Add_s : public FPOp
        {
          public:
                /// Constructor.
                Add_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::sub_s([' Fd_sf = Fs_sf - Ft_sf; '],{})

        /**
         * Static instruction class for "sub_s".
         */
        class Sub_s : public FPOp
        {
          public:
                /// Constructor.
                Sub_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::mul_s([' Fd_sf = Fs_sf * Ft_sf; '],{})

        /**
         * Static instruction class for "mul_s".
         */
        class Mul_s : public FPOp
        {
          public:
                /// Constructor.
                Mul_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::div_s([' Fd_sf = Fs_sf / Ft_sf; '],{})

        /**
         * Static instruction class for "div_s".
         */
        class Div_s : public FPOp
        {
          public:
                /// Constructor.
                Div_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::sqrt_s([' Fd_sf = sqrt(Fs_sf); '],{})

        /**
         * Static instruction class for "sqrt_s".
         */
        class Sqrt_s : public FPOp
        {
          public:
                /// Constructor.
                Sqrt_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::abs_s([' Fd_sf = fabs(Fs_sf); '],{})

        /**
         * Static instruction class for "abs_s".
         */
        class Abs_s : public FPOp
        {
          public:
                /// Constructor.
                Abs_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::neg_s([' Fd_sf = -Fs_sf; '],{})

        /**
         * Static instruction class for "neg_s".
         */
        class Neg_s : public FPOp
        {
          public:
                /// Constructor.
                Neg_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::mov_s(([' Fd_sf = Fs_sf; '], {}))

        /**
         * Static instruction class for "mov_s".
         */
        class Mov_s : public MipsStaticInst
        {
          public:
                /// Constructor.
                Mov_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatConvertOp::round_l_s([' val = Fs_sf; ', 'ToLong', 'Round'],{})

        /**
         * Static instruction class for "round_l_s".
         */
        class Round_l_s : public FPOp
        {
          public:
                /// Constructor.
                Round_l_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::trunc_l_s([' val = Fs_sf; ', 'ToLong', 'Trunc'],{})

        /**
         * Static instruction class for "trunc_l_s".
         */
        class Trunc_l_s : public FPOp
        {
          public:
                /// Constructor.
                Trunc_l_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::ceil_l_s([' val = Fs_sf;', 'ToLong', 'Ceil'],{})

        /**
         * Static instruction class for "ceil_l_s".
         */
        class Ceil_l_s : public FPOp
        {
          public:
                /// Constructor.
                Ceil_l_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::floor_l_s([' val = Fs_sf; ', 'ToLong', 'Floor'],{})

        /**
         * Static instruction class for "floor_l_s".
         */
        class Floor_l_s : public FPOp
        {
          public:
                /// Constructor.
                Floor_l_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::round_w_s([' val = Fs_sf; ', 'ToWord', 'Round'],{})

        /**
         * Static instruction class for "round_w_s".
         */
        class Round_w_s : public FPOp
        {
          public:
                /// Constructor.
                Round_w_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::trunc_w_s([' val = Fs_sf; ', 'ToWord', 'Trunc'],{})

        /**
         * Static instruction class for "trunc_w_s".
         */
        class Trunc_w_s : public FPOp
        {
          public:
                /// Constructor.
                Trunc_w_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::ceil_w_s([' val = Fs_sf; ', 'ToWord', 'Ceil'],{})

        /**
         * Static instruction class for "ceil_w_s".
         */
        class Ceil_w_s : public FPOp
        {
          public:
                /// Constructor.
                Ceil_w_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::floor_w_s([' val = Fs_sf; ', 'ToWord', 'Floor'],{})

        /**
         * Static instruction class for "floor_w_s".
         */
        class Floor_w_s : public FPOp
        {
          public:
                /// Constructor.
                Floor_w_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::movf_s(['\n                                        Fd = (getCondCode(FCSR,CC) == 0) ?\n                                             Fs : Fd;\n                                    '],{})

        /**
         * Static instruction class for "movf_s".
         */
        class Movf_s : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movf_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movt_s(['\n                                        Fd = (getCondCode(FCSR,CC) == 1) ?\n                                             Fs : Fd;\n                                    '],{})

        /**
         * Static instruction class for "movt_s".
         */
        class Movt_s : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movt_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::movz_s([' Fd = (Rt == 0) ? Fs : Fd; '],{})

        /**
         * Static instruction class for "movz_s".
         */
        class Movz_s : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movz_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movn_s([' Fd = (Rt != 0) ? Fs : Fd; '],{})

        /**
         * Static instruction class for "movn_s".
         */
        class Movn_s : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movn_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::recip_s([' Fd = 1 / Fs; '],{})

        /**
         * Static instruction class for "recip_s".
         */
        class Recip_s : public FPOp
        {
          public:
                /// Constructor.
                Recip_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::rsqrt_s([' Fd = 1 / sqrt(Fs); '],{})

        /**
         * Static instruction class for "rsqrt_s".
         */
        class Rsqrt_s : public FPOp
        {
          public:
                /// Constructor.
                Rsqrt_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown([],{})

// CP1Unimpl::unknown(([], {}))

// FloatConvertOp::cvt_d_s([' val = Fs_sf; ', 'ToDouble'],{})

        /**
         * Static instruction class for "cvt_d_s".
         */
        class Cvt_d_s : public FPOp
        {
          public:
                /// Constructor.
                Cvt_d_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::cvt_w_s([' val = Fs_sf; ', 'ToWord'],{})

        /**
         * Static instruction class for "cvt_w_s".
         */
        class Cvt_w_s : public FPOp
        {
          public:
                /// Constructor.
                Cvt_w_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::cvt_l_s([' val = Fs_sf; ', 'ToLong'],{})

        /**
         * Static instruction class for "cvt_l_s".
         */
        class Cvt_l_s : public FPOp
        {
          public:
                /// Constructor.
                Cvt_l_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::cvt_ps_s((['\n                                Fd_ud = (uint64_t) Fs_uw << 32 |\n                                        (uint64_t) Ft_uw;\n                            '], {}))

        /**
         * Static instruction class for "cvt_ps_s".
         */
        class Cvt_ps_s : public FPOp
        {
          public:
                /// Constructor.
                Cvt_ps_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown([],{})

// CP1Unimpl::unknown(([], {}))

// FloatCompareOp::c_f_s([' cond = 0; ', 'SinglePrecision', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_f_s".
         */
        class C_f_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_f_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_un_s([' cond = 0; ', 'SinglePrecision', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_un_s".
         */
        class C_un_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_un_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_eq_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_eq_s".
         */
        class C_eq_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_eq_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ueq_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ueq_s".
         */
        class C_ueq_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ueq_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_olt_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_olt_s".
         */
        class C_olt_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_olt_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ult_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ult_s".
         */
        class C_ult_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ult_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ole_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_ole_s".
         */
        class C_ole_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ole_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ule_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ule_s".
         */
        class C_ule_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ule_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatCompareOp::c_sf_s([' cond = 0; ', 'SinglePrecision', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_sf_s".
         */
        class C_sf_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_sf_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ngle_s([' cond = 0; ', 'SinglePrecision', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngle_s".
         */
        class C_ngle_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngle_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_seq_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_seq_s".
         */
        class C_seq_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_seq_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ngl_s([' cond = (Fs_sf == Ft_sf); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngl_s".
         */
        class C_ngl_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngl_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_lt_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_lt_s".
         */
        class C_lt_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_lt_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_nge_s([' cond = (Fs_sf < Ft_sf); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_nge_s".
         */
        class C_nge_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_nge_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_le_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_le_s".
         */
        class C_le_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_le_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ngt_s([' cond = (Fs_sf <= Ft_sf); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngt_s".
         */
        class C_ngt_s : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngt_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// FloatOp::add_d([' Fd_df = Fs_df + Ft_df; '],{})

        /**
         * Static instruction class for "add_d".
         */
        class Add_d : public FPOp
        {
          public:
                /// Constructor.
                Add_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::sub_d([' Fd_df = Fs_df - Ft_df; '],{})

        /**
         * Static instruction class for "sub_d".
         */
        class Sub_d : public FPOp
        {
          public:
                /// Constructor.
                Sub_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::mul_d([' Fd_df = Fs_df * Ft_df; '],{})

        /**
         * Static instruction class for "mul_d".
         */
        class Mul_d : public FPOp
        {
          public:
                /// Constructor.
                Mul_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::div_d([' Fd_df = Fs_df / Ft_df; '],{})

        /**
         * Static instruction class for "div_d".
         */
        class Div_d : public FPOp
        {
          public:
                /// Constructor.
                Div_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::sqrt_d([' Fd_df = sqrt(Fs_df); '],{})

        /**
         * Static instruction class for "sqrt_d".
         */
        class Sqrt_d : public FPOp
        {
          public:
                /// Constructor.
                Sqrt_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::abs_d([' Fd_df = fabs(Fs_df); '],{})

        /**
         * Static instruction class for "abs_d".
         */
        class Abs_d : public FPOp
        {
          public:
                /// Constructor.
                Abs_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::neg_d([' Fd_df = -1 * Fs_df; '],{})

        /**
         * Static instruction class for "neg_d".
         */
        class Neg_d : public FPOp
        {
          public:
                /// Constructor.
                Neg_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::mov_d(([' Fd_df = Fs_df; '], {}))

        /**
         * Static instruction class for "mov_d".
         */
        class Mov_d : public MipsStaticInst
        {
          public:
                /// Constructor.
                Mov_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatConvertOp::round_l_d([' val = Fs_df; ', 'ToLong', 'Round'],{})

        /**
         * Static instruction class for "round_l_d".
         */
        class Round_l_d : public FPOp
        {
          public:
                /// Constructor.
                Round_l_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::trunc_l_d([' val = Fs_df; ', 'ToLong', 'Trunc'],{})

        /**
         * Static instruction class for "trunc_l_d".
         */
        class Trunc_l_d : public FPOp
        {
          public:
                /// Constructor.
                Trunc_l_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::ceil_l_d([' val = Fs_df; ', 'ToLong', 'Ceil'],{})

        /**
         * Static instruction class for "ceil_l_d".
         */
        class Ceil_l_d : public FPOp
        {
          public:
                /// Constructor.
                Ceil_l_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::floor_l_d([' val = Fs_df; ', 'ToLong', 'Floor'],{})

        /**
         * Static instruction class for "floor_l_d".
         */
        class Floor_l_d : public FPOp
        {
          public:
                /// Constructor.
                Floor_l_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::round_w_d([' val = Fs_df; ', 'ToWord', 'Round'],{})

        /**
         * Static instruction class for "round_w_d".
         */
        class Round_w_d : public FPOp
        {
          public:
                /// Constructor.
                Round_w_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::trunc_w_d([' val = Fs_df; ', 'ToWord', 'Trunc'],{})

        /**
         * Static instruction class for "trunc_w_d".
         */
        class Trunc_w_d : public FPOp
        {
          public:
                /// Constructor.
                Trunc_w_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::ceil_w_d([' val = Fs_df; ', 'ToWord', 'Ceil'],{})

        /**
         * Static instruction class for "ceil_w_d".
         */
        class Ceil_w_d : public FPOp
        {
          public:
                /// Constructor.
                Ceil_w_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::floor_w_d([' val = Fs_df; ', 'ToWord', 'Floor'],{})

        /**
         * Static instruction class for "floor_w_d".
         */
        class Floor_w_d : public FPOp
        {
          public:
                /// Constructor.
                Floor_w_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::movf_d(['\n                                        Fd_df = (getCondCode(FCSR,CC) == 0) ?\n                                                       Fs_df : Fd_df;\n                                    '],{})

        /**
         * Static instruction class for "movf_d".
         */
        class Movf_d : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movf_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movt_d(['\n                                        Fd_df = (getCondCode(FCSR,CC) == 1) ?\n                                                       Fs_df : Fd_df;\n                                    '],{})

        /**
         * Static instruction class for "movt_d".
         */
        class Movt_d : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movt_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::movz_d(['\n                                    Fd_df = (Rt == 0) ? Fs_df : Fd_df;\n                                '],{})

        /**
         * Static instruction class for "movz_d".
         */
        class Movz_d : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movz_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::movn_d(['\n                                    Fd_df = (Rt != 0) ? Fs_df : Fd_df;\n                                '],{})

        /**
         * Static instruction class for "movn_d".
         */
        class Movn_d : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movn_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::recip_d([' Fd_df = 1 / Fs_df; '],{})

        /**
         * Static instruction class for "recip_d".
         */
        class Recip_d : public FPOp
        {
          public:
                /// Constructor.
                Recip_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatOp::rsqrt_d([' Fd_df = 1 / sqrt(Fs_df); '],{})

        /**
         * Static instruction class for "rsqrt_d".
         */
        class Rsqrt_d : public FPOp
        {
          public:
                /// Constructor.
                Rsqrt_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown([],{})

// FloatConvertOp::cvt_s_d([' val = Fs_df; ', 'ToSingle'],{})

        /**
         * Static instruction class for "cvt_s_d".
         */
        class Cvt_s_d : public FPOp
        {
          public:
                /// Constructor.
                Cvt_s_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::cvt_w_d([' val = Fs_df; ', 'ToWord'],{})

        /**
         * Static instruction class for "cvt_w_d".
         */
        class Cvt_w_d : public FPOp
        {
          public:
                /// Constructor.
                Cvt_w_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::cvt_l_d([' val = Fs_df; ', 'ToLong'],{})

        /**
         * Static instruction class for "cvt_l_d".
         */
        class Cvt_l_d : public FPOp
        {
          public:
                /// Constructor.
                Cvt_l_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown(([], {}))

// FloatCompareOp::c_f_d([' cond = 0; ', 'DoublePrecision', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_f_d".
         */
        class C_f_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_f_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_un_d([' cond = 0; ', 'DoublePrecision', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_un_d".
         */
        class C_un_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_un_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_eq_d([' cond = (Fs_df == Ft_df); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_eq_d".
         */
        class C_eq_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_eq_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ueq_d([' cond = (Fs_df == Ft_df); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ueq_d".
         */
        class C_ueq_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ueq_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_olt_d([' cond = (Fs_df < Ft_df); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_olt_d".
         */
        class C_olt_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_olt_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ult_d([' cond = (Fs_df < Ft_df); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ult_d".
         */
        class C_ult_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ult_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ole_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_ole_d".
         */
        class C_ole_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ole_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ule_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ule_d".
         */
        class C_ule_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ule_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatCompareOp::c_sf_d([' cond = 0; ', 'DoublePrecision', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_sf_d".
         */
        class C_sf_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_sf_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ngle_d([' cond = 0; ', 'DoublePrecision', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngle_d".
         */
        class C_ngle_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngle_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_seq_d([' cond = (Fs_df == Ft_df); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_seq_d".
         */
        class C_seq_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_seq_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ngl_d([' cond = (Fs_df == Ft_df); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngl_d".
         */
        class C_ngl_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngl_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_lt_d([' cond = (Fs_df < Ft_df); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_lt_d".
         */
        class C_lt_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_lt_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_nge_d([' cond = (Fs_df < Ft_df); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_nge_d".
         */
        class C_nge_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_nge_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_le_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_le_d".
         */
        class C_le_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_le_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatCompareOp::c_ngt_d([' cond = (Fs_df <= Ft_df); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngt_d".
         */
        class C_ngt_d : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngt_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// FloatConvertOp::cvt_s_w([' val = Fs_sw; ', 'ToSingle'],{})

        /**
         * Static instruction class for "cvt_s_w".
         */
        class Cvt_s_w : public FPOp
        {
          public:
                /// Constructor.
                Cvt_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::cvt_d_w([' val = Fs_sw; ', 'ToDouble'],{})

        /**
         * Static instruction class for "cvt_d_w".
         */
        class Cvt_d_w : public FPOp
        {
          public:
                /// Constructor.
                Cvt_d_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::cvt_ps_w(([], {}))

// CP1Unimpl::unknown(([], {}))

// FloatConvertOp::cvt_s_l([' val = Fs_sd; ', 'ToSingle'],{})

        /**
         * Static instruction class for "cvt_s_l".
         */
        class Cvt_s_l : public FPOp
        {
          public:
                /// Constructor.
                Cvt_s_l(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatConvertOp::cvt_d_l([' val = Fs_sd; ', 'ToDouble'],{})

        /**
         * Static instruction class for "cvt_d_l".
         */
        class Cvt_d_l : public FPOp
        {
          public:
                /// Constructor.
                Cvt_d_l(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::cvt_ps_l(([], {}))

// CP1Unimpl::unknown(([], {}))

// Float64Op::add_ps(['\n                                    Fd1_sf = Fs1_sf + Ft2_sf;\n                                    Fd2_sf = Fs2_sf + Ft2_sf;\n                                '],{})

        /**
         * Static instruction class for "add_ps".
         */
        class Add_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Add_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::sub_ps(['\n                                    Fd1_sf = Fs1_sf - Ft2_sf;\n                                    Fd2_sf = Fs2_sf - Ft2_sf;\n                                '],{})

        /**
         * Static instruction class for "sub_ps".
         */
        class Sub_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Sub_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::mul_ps(['\n                                    Fd1_sf = Fs1_sf * Ft2_sf;\n                                    Fd2_sf = Fs2_sf * Ft2_sf;\n                                '],{})

        /**
         * Static instruction class for "mul_ps".
         */
        class Mul_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Mul_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::abs_ps(['\n                                    Fd1_sf = fabs(Fs1_sf);\n                                    Fd2_sf = fabs(Fs2_sf);\n                                '],{})

        /**
         * Static instruction class for "abs_ps".
         */
        class Abs_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Abs_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::mov_ps(['\n                                    Fd1_sf = Fs1_sf;\n                                    Fd2_sf = Fs2_sf;\n                                '],{})

        /**
         * Static instruction class for "mov_ps".
         */
        class Mov_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Mov_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::neg_ps(['\n                                    Fd1_sf = -(Fs1_sf);\n                                    Fd2_sf = -(Fs2_sf);\n                                '],{})

        /**
         * Static instruction class for "neg_ps".
         */
        class Neg_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Neg_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// Float64Op::movf_ps(['\n                                        Fd1 = (getCondCode(FCSR, CC) == 0) ?\n                                            Fs1 : Fd1;\n                                        Fd2 = (getCondCode(FCSR, CC+1) == 0) ?\n                                            Fs2 : Fd2;\n                                    '],{})

        /**
         * Static instruction class for "movf_ps".
         */
        class Movf_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movf_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::movt_ps(['\n                                        Fd2 = (getCondCode(FCSR, CC) == 1) ?\n                                            Fs1 : Fd1;\n                                        Fd2 = (getCondCode(FCSR, CC+1) == 1) ?\n                                            Fs2 : Fd2;\n                                    '],{})

        /**
         * Static instruction class for "movt_ps".
         */
        class Movt_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movt_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Float64Op::movz_ps(['\n                                    Fd1 = (getCondCode(FCSR, CC) == 0) ?\n                                        Fs1 : Fd1;\n                                    Fd2 = (getCondCode(FCSR, CC) == 0) ?\n                                        Fs2 : Fd2;\n                                '],{})

        /**
         * Static instruction class for "movz_ps".
         */
        class Movz_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movz_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::movn_ps(['\n                                    Fd1 = (getCondCode(FCSR, CC) == 1) ?\n                                        Fs1 : Fd1;\n                                    Fd2 = (getCondCode(FCSR, CC) == 1) ?\n                                        Fs2 : Fd2;\n                                '],{})

        /**
         * Static instruction class for "movn_ps".
         */
        class Movn_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Movn_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown(([], {}))

// CP1Unimpl::unknown(([], {}))

// FloatOp::cvt_s_pu(([' Fd_sf = Fs2_sf; '], {}))

        /**
         * Static instruction class for "cvt_s_pu".
         */
        class Cvt_s_pu : public FPOp
        {
          public:
                /// Constructor.
                Cvt_s_pu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown(([], {}))

// FloatOp::cvt_s_pl(([' Fd_sf = Fs1_sf; '], {}))

        /**
         * Static instruction class for "cvt_s_pl".
         */
        class Cvt_s_pl : public FPOp
        {
          public:
                /// Constructor.
                Cvt_s_pl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::pll(['\n                                    Fd_ud = (uint64_t)Fs1_uw << 32 | Ft1_uw;\n                                '],{})

        /**
         * Static instruction class for "pll".
         */
        class Pll : public MipsStaticInst
        {
          public:
                /// Constructor.
                Pll(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::plu(['\n                                    Fd_ud = (uint64_t)Fs1_uw << 32 | Ft2_uw;\n                                '],{})

        /**
         * Static instruction class for "plu".
         */
        class Plu : public MipsStaticInst
        {
          public:
                /// Constructor.
                Plu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::pul(['\n                                    Fd_ud = (uint64_t)Fs2_uw << 32 | Ft1_uw;\n                                '],{})

        /**
         * Static instruction class for "pul".
         */
        class Pul : public MipsStaticInst
        {
          public:
                /// Constructor.
                Pul(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Float64Op::puu(['\n                                    Fd_ud = (uint64_t)Fs2_uw << 32 | Ft2_uw;\n                                '],{})

        /**
         * Static instruction class for "puu".
         */
        class Puu : public MipsStaticInst
        {
          public:
                /// Constructor.
                Puu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// CP1Unimpl::unknown(([], {}))

// FloatPSCompareOp::c_f_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_f_ps".
         */
        class C_f_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_f_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_un_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_un_ps".
         */
        class C_un_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_un_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_eq_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_eq_ps".
         */
        class C_eq_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_eq_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ueq_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ueq_ps".
         */
        class C_ueq_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ueq_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_olt_ps([' cond1 = (Fs1_sf < Ft1_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_olt_ps".
         */
        class C_olt_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_olt_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ult_ps([' cond1 = (Fs_sf < Ft_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ult_ps".
         */
        class C_ult_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ult_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ole_ps([' cond1 = (Fs_sf <= Ft_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedFalse'],{})

        /**
         * Static instruction class for "c_ole_ps".
         */
        class C_ole_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ole_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ule_ps([' cond1 = (Fs1_sf <= Ft1_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedTrue'],{})

        /**
         * Static instruction class for "c_ule_ps".
         */
        class C_ule_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ule_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatPSCompareOp::c_sf_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_sf_ps".
         */
        class C_sf_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_sf_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ngle_ps([' cond1 = 0; ', ' cond2 = 0; ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngle_ps".
         */
        class C_ngle_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngle_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_seq_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_seq_ps".
         */
        class C_seq_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_seq_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ngl_ps([' cond1 = (Fs1_sf == Ft1_sf); ', ' cond2 = (Fs2_sf == Ft2_sf); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngl_ps".
         */
        class C_ngl_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngl_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_lt_ps([' cond1 = (Fs1_sf < Ft1_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_lt_ps".
         */
        class C_lt_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_lt_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_nge_ps([' cond1 = (Fs1_sf < Ft1_sf); ', ' cond2 = (Fs2_sf < Ft2_sf); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_nge_ps".
         */
        class C_nge_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_nge_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_le_ps([' cond1 = (Fs1_sf <= Ft1_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedFalse', 'QnanException'],{})

        /**
         * Static instruction class for "c_le_ps".
         */
        class C_le_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_le_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatPSCompareOp::c_ngt_ps([' cond1 = (Fs1_sf <= Ft1_sf); ', ' cond2 = (Fs2_sf <= Ft2_sf); ', 'UnorderedTrue', 'QnanException'],{})

        /**
         * Static instruction class for "c_ngt_ps".
         */
        class C_ngt_ps : public FPCompareOp
        {
          public:
                /// Constructor.
                C_ngt_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

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

    /**
     * Static instruction class for "lwxc1".
     */
    class Lwxc1 : public Memory
    {
      public:

        /// Constructor.
        Lwxc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadIndexedMemory::ldxc1([' Fd_ud = Mem_ud; '],{})

    /**
     * Static instruction class for "ldxc1".
     */
    class Ldxc1 : public Memory
    {
      public:

        /// Constructor.
        Ldxc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadIndexedMemory::luxc1([' Fd_ud = Mem_ud; ', ' EA = (Rs + Rt) & ~7; '],{})

    /**
     * Static instruction class for "luxc1".
     */
    class Luxc1 : public Memory
    {
      public:

        /// Constructor.
        Luxc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// Unknown::unknown(([], {}))

// StoreIndexedMemory::swxc1([' Mem_uw = Fs_uw; '],{})

    /**
     * Static instruction class for "swxc1".
     */
    class Swxc1 : public Memory
    {
      public:

        /// Constructor.
        Swxc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreIndexedMemory::sdxc1([' Mem_ud = Fs_ud; '],{})

    /**
     * Static instruction class for "sdxc1".
     */
    class Sdxc1 : public Memory
    {
      public:

        /// Constructor.
        Sdxc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreIndexedMemory::suxc1([' Mem_ud = Fs_ud; ', ' EA = (Rs + Rt) & ~7; '],{})

    /**
     * Static instruction class for "suxc1".
     */
    class Suxc1 : public Memory
    {
      public:

        /// Constructor.
        Suxc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// Prefetch::prefx(([' EA = Rs + Rt; '], {}))

    /**
     * Static instruction class for "prefx".
     */
    class Prefx : public Memory
    {
      public:

        /// Constructor.
        Prefx(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// Unknown::unknown(([], {}))

// Float64Op::alnv_ps((['\n                    if (Rs<2:0> == 0) {\n                        Fd_ud = Fs_ud;\n                    } else if (Rs<2:0> == 4) {\n                        if (GuestByteOrder == BigEndianByteOrder)\n                            Fd_ud = Fs_ud<31:0> << 32 | Ft_ud<63:32>;\n                        else\n                            Fd_ud = Ft_ud<31:0> << 32 | Fs_ud<63:32>;\n                    } else {\n                        Fd_ud = Fd_ud;\n                    }\n                '], {}))

        /**
         * Static instruction class for "alnv_ps".
         */
        class Alnv_ps : public MipsStaticInst
        {
          public:
                /// Constructor.
                Alnv_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatAccOp::madd_s([' Fd_sf = (Fs_sf * Ft_sf) + Fr_sf; '],{})

        /**
         * Static instruction class for "madd_s".
         */
        class Madd_s : public FPOp
        {
          public:
                /// Constructor.
                Madd_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::madd_d([' Fd_df = (Fs_df * Ft_df) + Fr_df; '],{})

        /**
         * Static instruction class for "madd_d".
         */
        class Madd_d : public FPOp
        {
          public:
                /// Constructor.
                Madd_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::madd_ps(['\n                        Fd1_sf = (Fs1_df * Ft1_df) + Fr1_df;\n                        Fd2_sf = (Fs2_df * Ft2_df) + Fr2_df;\n                    '],{})

        /**
         * Static instruction class for "madd_ps".
         */
        class Madd_ps : public FPOp
        {
          public:
                /// Constructor.
                Madd_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatAccOp::msub_s([' Fd_sf = (Fs_sf * Ft_sf) - Fr_sf; '],{})

        /**
         * Static instruction class for "msub_s".
         */
        class Msub_s : public FPOp
        {
          public:
                /// Constructor.
                Msub_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::msub_d([' Fd_df = (Fs_df * Ft_df) - Fr_df; '],{})

        /**
         * Static instruction class for "msub_d".
         */
        class Msub_d : public FPOp
        {
          public:
                /// Constructor.
                Msub_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::msub_ps(['\n                        Fd1_sf = (Fs1_df * Ft1_df) - Fr1_df;\n                        Fd2_sf = (Fs2_df * Ft2_df) - Fr2_df;\n                    '],{})

        /**
         * Static instruction class for "msub_ps".
         */
        class Msub_ps : public FPOp
        {
          public:
                /// Constructor.
                Msub_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatAccOp::nmadd_s([' Fd_sf = (-1 * Fs_sf * Ft_sf) - Fr_sf; '],{})

        /**
         * Static instruction class for "nmadd_s".
         */
        class Nmadd_s : public FPOp
        {
          public:
                /// Constructor.
                Nmadd_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::nmadd_d([' Fd_df = (-1 * Fs_df * Ft_df) - Fr_df; '],{})

        /**
         * Static instruction class for "nmadd_d".
         */
        class Nmadd_d : public FPOp
        {
          public:
                /// Constructor.
                Nmadd_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::nmadd_ps(['\n                        Fd1_sf = -((Fs1_df * Ft1_df) + Fr1_df);\n                        Fd2_sf = -((Fs2_df * Ft2_df) + Fr2_df);\n                    '],{})

        /**
         * Static instruction class for "nmadd_ps".
         */
        class Nmadd_ps : public FPOp
        {
          public:
                /// Constructor.
                Nmadd_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FloatAccOp::nmsub_s([' Fd_sf = (-1 * Fs_sf * Ft_sf) + Fr_sf; '],{})

        /**
         * Static instruction class for "nmsub_s".
         */
        class Nmsub_s : public FPOp
        {
          public:
                /// Constructor.
                Nmsub_s(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::nmsub_d([' Fd_df = (-1 * Fs_df * Ft_df) + Fr_df; '],{})

        /**
         * Static instruction class for "nmsub_d".
         */
        class Nmsub_d : public FPOp
        {
          public:
                /// Constructor.
                Nmsub_d(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FloatAccOp::nmsub_ps(['\n                        Fd1_sf = -((Fs1_df * Ft1_df) - Fr1_df);\n                        Fd2_sf = -((Fs2_df * Ft2_df) - Fr2_df);\n                    '],{})

        /**
         * Static instruction class for "nmsub_ps".
         */
        class Nmsub_ps : public FPOp
        {
          public:
                /// Constructor.
                Nmsub_ps(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Branch::beql([' cond = (Rs_sw == Rt_sw); ', 'Likely'],{})

        /**
         * Static instruction class for "beql".
         */
        class Beql : public Branch
        {
          public:
                /// Constructor.
                Beql(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bnel([' cond = (Rs_sw != Rt_sw); ', 'Likely'],{})

        /**
         * Static instruction class for "bnel".
         */
        class Bnel : public Branch
        {
          public:
                /// Constructor.
                Bnel(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::blezl([' cond = (Rs_sw <= 0); ', 'Likely'],{})

        /**
         * Static instruction class for "blezl".
         */
        class Blezl : public Branch
        {
          public:
                /// Constructor.
                Blezl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Branch::bgtzl([' cond = (Rs_sw > 0); ', 'Likely'],{})

        /**
         * Static instruction class for "bgtzl".
         */
        class Bgtzl : public Branch
        {
          public:
                /// Constructor.
                Bgtzl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// IntOp::mul((['\n                    int64_t temp1 = Rs_sd * Rt_sd;\n                    Rd_sw = temp1<31:0>;\n                ', 'IntMultOp'], {}))

        /**
         * Static instruction class for "mul".
         */
        class Mul : public IntOp
        {
          public:
                /// Constructor.
                Mul(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelValOp::madd(['\n                        val = ((int64_t)HI_RD_SEL << 32 | LO_RD_SEL) +\n                              (Rs_sd * Rt_sd);\n                    ', 'IntMultOp'],{})

        /**
         * Static instruction class for "madd".
         */
        class Madd : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Madd(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelValOp::maddu(['\n                        val = ((uint64_t)HI_RD_SEL << 32 | LO_RD_SEL) +\n                              (Rs_ud * Rt_ud);\n                    ', 'IntMultOp'],{})

        /**
         * Static instruction class for "maddu".
         */
        class Maddu : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Maddu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelValOp::msub(['\n                        val = ((int64_t)HI_RD_SEL << 32 | LO_RD_SEL) -\n                              (Rs_sd * Rt_sd);\n                    ', 'IntMultOp'],{})

        /**
         * Static instruction class for "msub".
         */
        class Msub : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Msub(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// HiLoRdSelValOp::msubu(['\n                        val = ((uint64_t)HI_RD_SEL << 32 | LO_RD_SEL) -\n                              (Rs_ud * Rt_ud);\n                    ', 'IntMultOp'],{})

        /**
         * Static instruction class for "msubu".
         */
        class Msubu : public HiLoRdSelOp
        {
          public:
                /// Constructor.
                Msubu(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// BasicOp::clz(['\n                        int cnt = 32;\n                        for (int idx = 31; idx >= 0; idx--) {\n                            if (Rs<idx:idx> == 1) {\n                                cnt = 31 - idx;\n                                break;\n                            }\n                        }\n                        Rd_uw = cnt;\n                    '],{})

        /**
         * Static instruction class for "clz".
         */
        class Clz : public MipsStaticInst
        {
          public:
                /// Constructor.
                Clz(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::clo(['\n                        int cnt = 32;\n                        for (int idx = 31; idx >= 0; idx--) {\n                            if (Rs<idx:idx> == 0) {\n                                cnt = 31 - idx;\n                                break;\n                            }\n                        }\n                        Rd_uw = cnt;\n                    '],{})

        /**
         * Static instruction class for "clo".
         */
        class Clo : public MipsStaticInst
        {
          public:
                /// Constructor.
                Clo(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// FailUnimpl::sdbbp(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::ext([' Rt_uw = bits(Rs_uw, MSB+LSB, LSB); '],{})

        /**
         * Static instruction class for "ext".
         */
        class Ext : public MipsStaticInst
        {
          public:
                /// Constructor.
                Ext(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::ins(['\n                        Rt_uw = bits(Rt_uw, 31, MSB+1) << (MSB+1) |\n                                bits(Rs_uw, MSB-LSB, 0) << LSB |\n                                bits(Rt_uw, LSB-1, 0);\n                    '],{})

        /**
         * Static instruction class for "ins".
         */
        class Ins : public MipsStaticInst
        {
          public:
                /// Constructor.
                Ins(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// MT_Control::fork(['\n                        forkThread(xc->tcBase(), fault, RD, Rs, Rt);\n                    ', 'UserMode'],{})

        /**
         * Static instruction class for "fork".
         */
        class Fork : public MTUserModeOp
        {
          public:
                /// Constructor.
                Fork(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// MT_Control::yield(['\n                        Rd_sw = yieldThread(xc->tcBase(), fault, Rs_sw,\n                                            YQMask);\n                    ', 'UserMode'],{})

        /**
         * Static instruction class for "yield".
         */
        class Yield : public MTUserModeOp
        {
          public:
                /// Constructor.
                Yield(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// LoadIndexedMemory::lwx([' Rd_sw = Mem_sw; '],{})

    /**
     * Static instruction class for "lwx".
     */
    class Lwx : public Memory
    {
      public:

        /// Constructor.
        Lwx(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadIndexedMemory::lhx([' Rd_sw = Mem_sh; '],{})

    /**
     * Static instruction class for "lhx".
     */
    class Lhx : public Memory
    {
      public:

        /// Constructor.
        Lhx(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadIndexedMemory::lbux([' Rd_uw = Mem_ub; '],{})

    /**
     * Static instruction class for "lbux".
     */
    class Lbux : public Memory
    {
      public:

        /// Constructor.
        Lbux(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::insv((['\n                    int pos = dspctl<5:0>;\n                    int size = dspctl<12:7> - 1;\n                    Rt_uw = insertBits(Rt_uw, pos+size,\n                                       pos, Rs_uw<size:0>);\n                '], {}))

        /**
         * Static instruction class for "insv".
         */
        class Insv : public DspIntOp
        {
          public:
                /// Constructor.
                Insv(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::addu_qb(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addu_qb".
         */
        class Addu_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Addu_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subu_qb(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subu_qb".
         */
        class Subu_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Subu_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addu_s_qb(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addu_s_qb".
         */
        class Addu_s_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Addu_s_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subu_s_qb(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subu_s_qb".
         */
        class Subu_s_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Subu_s_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::muleu_s_ph_qbl(['\n                                Rd_uw = dspMuleu(Rs_uw, Rt_uw,\n                                                 MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "muleu_s_ph_qbl".
         */
        class Muleu_s_ph_qbl : public DspIntOp
        {
          public:
                /// Constructor.
                Muleu_s_ph_qbl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::muleu_s_ph_qbr(['\n                                Rd_uw = dspMuleu(Rs_uw, Rt_uw,\n                                                 MODE_R, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "muleu_s_ph_qbr".
         */
        class Muleu_s_ph_qbr : public DspIntOp
        {
          public:
                /// Constructor.
                Muleu_s_ph_qbr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::addu_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addu_ph".
         */
        class Addu_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Addu_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subu_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subu_ph".
         */
        class Subu_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Subu_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addq_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addq_ph".
         */
        class Addq_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Addq_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subq_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subq_ph".
         */
        class Subq_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Subq_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addu_s_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addu_s_ph".
         */
        class Addu_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Addu_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subu_s_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subu_s_ph".
         */
        class Subu_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Subu_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addq_s_ph(['\n                                Rd_uw = dspAdd(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addq_s_ph".
         */
        class Addq_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Addq_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subq_s_ph(['\n                                Rd_uw = dspSub(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subq_s_ph".
         */
        class Subq_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Subq_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::addsc(['\n                                int64_t dresult;\n                                dresult = Rs_ud + Rt_ud;\n                                Rd_sw = dresult<31:0>;\n                                dspctl = insertBits(dspctl, 13, 13,\n                                                    dresult<32:32>);\n                            '],{})

        /**
         * Static instruction class for "addsc".
         */
        class Addsc : public DspIntOp
        {
          public:
                /// Constructor.
                Addsc(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addwc(['\n                                int64_t dresult;\n                                dresult = Rs_sd + Rt_sd + dspctl<13:13>;\n                                Rd_sw = dresult<31:0>;\n                                if (dresult<32:32> != dresult<31:31>)\n                                    dspctl = insertBits(dspctl, 20, 20, 1);\n                            '],{})

        /**
         * Static instruction class for "addwc".
         */
        class Addwc : public DspIntOp
        {
          public:
                /// Constructor.
                Addwc(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::modsub(['\n                                Rd_sw = (Rs_sw == 0) ? Rt_sw<23:8> :\n                                                       Rs_sw - Rt_sw<7:0>;\n                            '],{})

        /**
         * Static instruction class for "modsub".
         */
        class Modsub : public DspIntOp
        {
          public:
                /// Constructor.
                Modsub(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::raddu_w_qb(['\n                                Rd_uw = Rs_uw<31:24> + Rs_uw<23:16> +\n                                        Rs_uw<15:8> + Rs_uw<7:0>;\n                            '],{})

        /**
         * Static instruction class for "raddu_w_qb".
         */
        class Raddu_w_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Raddu_w_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addq_s_w(['\n                                Rd_sw = dspAdd(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "addq_s_w".
         */
        class Addq_s_w : public DspIntOp
        {
          public:
                /// Constructor.
                Addq_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subq_s_w(['\n                                Rd_sw = dspSub(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                               SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "subq_s_w".
         */
        class Subq_s_w : public DspIntOp
        {
          public:
                /// Constructor.
                Subq_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::muleq_s_w_phl(['\n                                Rd_sw = dspMuleq(Rs_sw, Rt_sw,\n                                                 MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "muleq_s_w_phl".
         */
        class Muleq_s_w_phl : public DspIntOp
        {
          public:
                /// Constructor.
                Muleq_s_w_phl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::muleq_s_w_phr(['\n                                Rd_sw = dspMuleq(Rs_sw, Rt_sw,\n                                                 MODE_R, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "muleq_s_w_phr".
         */
        class Muleq_s_w_phr : public DspIntOp
        {
          public:
                /// Constructor.
                Muleq_s_w_phr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::mulq_s_ph(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                SATURATE, NOROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mulq_s_ph".
         */
        class Mulq_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Mulq_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::mulq_rs_ph(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                SATURATE, ROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mulq_rs_ph".
         */
        class Mulq_rs_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Mulq_rs_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::cmpu_eq_qb(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                       UNSIGNED, CMP_EQ, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmpu_eq_qb".
         */
        class Cmpu_eq_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpu_eq_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpu_lt_qb(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                       UNSIGNED, CMP_LT, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmpu_lt_qb".
         */
        class Cmpu_lt_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpu_lt_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpu_le_qb(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                       UNSIGNED, CMP_LE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmpu_le_qb".
         */
        class Cmpu_le_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpu_le_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::pick_qb(['\n                                Rd_uw = dspPick(Rs_uw, Rt_uw,\n                                                SIMD_FMT_QB, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "pick_qb".
         */
        class Pick_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Pick_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpgu_eq_qb(['\n                                Rd_uw = dspCmpg(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                UNSIGNED, CMP_EQ );\n                            '],{})

        /**
         * Static instruction class for "cmpgu_eq_qb".
         */
        class Cmpgu_eq_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpgu_eq_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpgu_lt_qb(['\n                                Rd_uw = dspCmpg(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                UNSIGNED, CMP_LT);\n                            '],{})

        /**
         * Static instruction class for "cmpgu_lt_qb".
         */
        class Cmpgu_lt_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpgu_lt_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpgu_le_qb(['\n                                Rd_uw = dspCmpg(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                UNSIGNED, CMP_LE);\n                            '],{})

        /**
         * Static instruction class for "cmpgu_le_qb".
         */
        class Cmpgu_le_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpgu_le_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::cmp_eq_ph(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                       SIGNED, CMP_EQ, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmp_eq_ph".
         */
        class Cmp_eq_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Cmp_eq_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmp_lt_ph(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                       SIGNED, CMP_LT, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmp_lt_ph".
         */
        class Cmp_lt_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Cmp_lt_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmp_le_ph(['\n                                dspCmp(Rs_uw, Rt_uw, SIMD_FMT_PH,\n                                       SIGNED, CMP_LE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmp_le_ph".
         */
        class Cmp_le_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Cmp_le_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::pick_ph(['\n                                Rd_uw = dspPick(Rs_uw, Rt_uw,\n                                                SIMD_FMT_PH, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "pick_ph".
         */
        class Pick_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Pick_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precrq_qb_ph(['\n                                Rd_uw = Rs_uw<31:24> << 24 |\n                                        Rs_uw<15:8> << 16 |\n                                        Rt_uw<31:24> << 8 |\n                                        Rt_uw<15:8>;\n                            '],{})

        /**
         * Static instruction class for "precrq_qb_ph".
         */
        class Precrq_qb_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Precrq_qb_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precr_qb_ph(['\n                                Rd_uw = Rs_uw<23:16> << 24 |\n                                        Rs_uw<7:0> << 16 |\n                                        Rt_uw<23:16> << 8 |\n                                        Rt_uw<7:0>;\n                            '],{})

        /**
         * Static instruction class for "precr_qb_ph".
         */
        class Precr_qb_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Precr_qb_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::packrl_ph(['\n                                Rd_uw = dspPack(Rs_uw, Rt_uw, SIMD_FMT_PH);\n                            '],{})

        /**
         * Static instruction class for "packrl_ph".
         */
        class Packrl_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Packrl_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precrqu_s_qb_ph(['\n                                Rd_uw = dspPrecrqu(Rs_uw, Rt_uw, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "precrqu_s_qb_ph".
         */
        class Precrqu_s_qb_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Precrqu_s_qb_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::precrq_ph_w(['\n                                Rd_uw = Rs_uw<31:16> << 16 | Rt_uw<31:16>;\n                            '],{})

        /**
         * Static instruction class for "precrq_ph_w".
         */
        class Precrq_ph_w : public DspIntOp
        {
          public:
                /// Constructor.
                Precrq_ph_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precrq_rs_ph_w(['\n                                Rd_uw = dspPrecrq(Rs_uw, Rt_uw,\n                                                  SIMD_FMT_W, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "precrq_rs_ph_w".
         */
        class Precrq_rs_ph_w : public DspIntOp
        {
          public:
                /// Constructor.
                Precrq_rs_ph_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::cmpgdu_eq_qb(['\n                                Rd_uw = dspCmpgd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, CMP_EQ, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmpgdu_eq_qb".
         */
        class Cmpgdu_eq_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpgdu_eq_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpgdu_lt_qb(['\n                                Rd_uw = dspCmpgd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, CMP_LT, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmpgdu_lt_qb".
         */
        class Cmpgdu_lt_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpgdu_lt_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::cmpgdu_le_qb(['\n                                Rd_uw = dspCmpgd(Rs_uw, Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, CMP_LE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "cmpgdu_le_qb".
         */
        class Cmpgdu_le_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Cmpgdu_le_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precr_sra_ph_w(['\n                                Rt_uw = dspPrecrSra(Rt_uw, Rs_uw, RD,\n                                                    SIMD_FMT_W, NOROUND);\n                            '],{})

        /**
         * Static instruction class for "precr_sra_ph_w".
         */
        class Precr_sra_ph_w : public DspIntOp
        {
          public:
                /// Constructor.
                Precr_sra_ph_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precr_sra_r_ph_w(['\n                                Rt_uw = dspPrecrSra(Rt_uw, Rs_uw, RD,\n                                                    SIMD_FMT_W, ROUND); \n                            '],{})

        /**
         * Static instruction class for "precr_sra_r_ph_w".
         */
        class Precr_sra_r_ph_w : public DspIntOp
        {
          public:
                /// Constructor.
                Precr_sra_r_ph_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::absq_s_qb(['\n                                Rd_sw = dspAbs(Rt_sw, SIMD_FMT_QB, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "absq_s_qb".
         */
        class Absq_s_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Absq_s_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::repl_qb(['\n                                Rd_uw = RS_RT<7:0> << 24 |\n                                        RS_RT<7:0> << 16 |\n                                        RS_RT<7:0> << 8 |\n                                        RS_RT<7:0>;\n                            '],{})

        /**
         * Static instruction class for "repl_qb".
         */
        class Repl_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Repl_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::replv_qb(['\n                                Rd_sw = Rt_uw<7:0> << 24 |\n                                        Rt_uw<7:0> << 16 |\n                                        Rt_uw<7:0> << 8 |\n                                        Rt_uw<7:0>;\n                            '],{})

        /**
         * Static instruction class for "replv_qb".
         */
        class Replv_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Replv_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precequ_ph_qbl(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_L);\n                            '],{})

        /**
         * Static instruction class for "precequ_ph_qbl".
         */
        class Precequ_ph_qbl : public DspIntOp
        {
          public:
                /// Constructor.
                Precequ_ph_qbl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precequ_ph_qbr(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_R);\n                            '],{})

        /**
         * Static instruction class for "precequ_ph_qbr".
         */
        class Precequ_ph_qbr : public DspIntOp
        {
          public:
                /// Constructor.
                Precequ_ph_qbr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precequ_ph_qbla(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_LA);\n                            '],{})

        /**
         * Static instruction class for "precequ_ph_qbla".
         */
        class Precequ_ph_qbla : public DspIntOp
        {
          public:
                /// Constructor.
                Precequ_ph_qbla(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::precequ_ph_qbra(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB, UNSIGNED,\n                                                 SIMD_FMT_PH, SIGNED, MODE_RA);\n                            '],{})

        /**
         * Static instruction class for "precequ_ph_qbra".
         */
        class Precequ_ph_qbra : public DspIntOp
        {
          public:
                /// Constructor.
                Precequ_ph_qbra(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::absq_s_ph(['\n                                Rd_sw = dspAbs(Rt_sw, SIMD_FMT_PH, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "absq_s_ph".
         */
        class Absq_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Absq_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::repl_ph(['\n                                Rd_uw = (sext<10>(RS_RT))<15:0> << 16 |\n                                        (sext<10>(RS_RT))<15:0>;\n                            '],{})

        /**
         * Static instruction class for "repl_ph".
         */
        class Repl_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Repl_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::replv_ph(['\n                                Rd_uw = Rt_uw<15:0> << 16 |\n                                        Rt_uw<15:0>;\n                            '],{})

        /**
         * Static instruction class for "replv_ph".
         */
        class Replv_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Replv_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::preceq_w_phl(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_PH, SIGNED,\n                                                 SIMD_FMT_W, SIGNED, MODE_L);\n                            '],{})

        /**
         * Static instruction class for "preceq_w_phl".
         */
        class Preceq_w_phl : public DspIntOp
        {
          public:
                /// Constructor.
                Preceq_w_phl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::preceq_w_phr(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_PH, SIGNED,\n                                                 SIMD_FMT_W, SIGNED, MODE_R);\n                            '],{})

        /**
         * Static instruction class for "preceq_w_phr".
         */
        class Preceq_w_phr : public DspIntOp
        {
          public:
                /// Constructor.
                Preceq_w_phr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::absq_s_w(['\n                                Rd_sw = dspAbs(Rt_sw, SIMD_FMT_W, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "absq_s_w".
         */
        class Absq_s_w : public DspIntOp
        {
          public:
                /// Constructor.
                Absq_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// IntOp::bitrev((['\n                            Rd_uw = bitrev( Rt_uw<15:0> );\n                        '], {}))

        /**
         * Static instruction class for "bitrev".
         */
        class Bitrev : public IntOp
        {
          public:
                /// Constructor.
                Bitrev(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::preceu_ph_qbl(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_L);\n                            '],{})

        /**
         * Static instruction class for "preceu_ph_qbl".
         */
        class Preceu_ph_qbl : public DspIntOp
        {
          public:
                /// Constructor.
                Preceu_ph_qbl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::preceu_ph_qbr(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_R );\n                            '],{})

        /**
         * Static instruction class for "preceu_ph_qbr".
         */
        class Preceu_ph_qbr : public DspIntOp
        {
          public:
                /// Constructor.
                Preceu_ph_qbr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::preceu_ph_qbla(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_LA );\n                            '],{})

        /**
         * Static instruction class for "preceu_ph_qbla".
         */
        class Preceu_ph_qbla : public DspIntOp
        {
          public:
                /// Constructor.
                Preceu_ph_qbla(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::preceu_ph_qbra(['\n                                Rd_uw = dspPrece(Rt_uw, SIMD_FMT_QB,\n                                                 UNSIGNED, SIMD_FMT_PH,\n                                                 UNSIGNED, MODE_RA);\n                            '],{})

        /**
         * Static instruction class for "preceu_ph_qbra".
         */
        class Preceu_ph_qbra : public DspIntOp
        {
          public:
                /// Constructor.
                Preceu_ph_qbra(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::shll_qb(['\n                                Rd_sw = dspShll(Rt_sw, RS, SIMD_FMT_QB,\n                                                NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shll_qb".
         */
        class Shll_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shll_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrl_qb(['\n                                Rd_sw = dspShrl(Rt_sw, RS, SIMD_FMT_QB,\n                                                UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "shrl_qb".
         */
        class Shrl_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shrl_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shllv_qb(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                NOSATURATE, UNSIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shllv_qb".
         */
        class Shllv_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shllv_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrlv_qb(['\n                                Rd_sw = dspShrl(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "shrlv_qb".
         */
        class Shrlv_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shrlv_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shra_qb(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_QB,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shra_qb".
         */
        class Shra_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shra_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shra_r_qb(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_QB,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shra_r_qb".
         */
        class Shra_r_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shra_r_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrav_qb(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shrav_qb".
         */
        class Shrav_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shrav_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrav_r_qb(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_QB,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shrav_r_qb".
         */
        class Shrav_r_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Shrav_r_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::shll_ph(['\n                                Rd_uw = dspShll(Rt_uw, RS, SIMD_FMT_PH,\n                                                NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shll_ph".
         */
        class Shll_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shll_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shra_ph(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_PH,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shra_ph".
         */
        class Shra_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shra_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shllv_ph(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                NOSATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shllv_ph".
         */
        class Shllv_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shllv_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrav_ph(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                NOROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shrav_ph".
         */
        class Shrav_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shrav_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shll_s_ph(['\n                                Rd_sw = dspShll(Rt_sw, RS, SIMD_FMT_PH,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shll_s_ph".
         */
        class Shll_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shll_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shra_r_ph(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_PH,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shra_r_ph".
         */
        class Shra_r_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shra_r_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shllv_s_ph(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shllv_s_ph".
         */
        class Shllv_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shllv_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrav_r_ph(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shrav_r_ph".
         */
        class Shrav_r_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shrav_r_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::shll_s_w(['\n                                Rd_sw = dspShll(Rt_sw, RS, SIMD_FMT_W,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shll_s_w".
         */
        class Shll_s_w : public DspIntOp
        {
          public:
                /// Constructor.
                Shll_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shra_r_w(['\n                                Rd_sw = dspShra(Rt_sw, RS, SIMD_FMT_W,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shra_r_w".
         */
        class Shra_r_w : public DspIntOp
        {
          public:
                /// Constructor.
                Shra_r_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shllv_s_w(['\n                                Rd_sw = dspShll(Rt_sw, Rs_sw, SIMD_FMT_W,\n                                                SATURATE, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shllv_s_w".
         */
        class Shllv_s_w : public DspIntOp
        {
          public:
                /// Constructor.
                Shllv_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrav_r_w(['\n                                Rd_sw = dspShra(Rt_sw, Rs_sw, SIMD_FMT_W,\n                                                ROUND, SIGNED, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "shrav_r_w".
         */
        class Shrav_r_w : public DspIntOp
        {
          public:
                /// Constructor.
                Shrav_r_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::shrl_ph(['\n                                Rd_sw = dspShrl(Rt_sw, RS, SIMD_FMT_PH,\n                                                UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "shrl_ph".
         */
        class Shrl_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shrl_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::shrlv_ph(['\n                                Rd_sw = dspShrl(Rt_sw, Rs_sw, SIMD_FMT_PH,\n                                                UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "shrlv_ph".
         */
        class Shrlv_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Shrlv_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspIntOp::adduh_qb(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                NOROUND, UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "adduh_qb".
         */
        class Adduh_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Adduh_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subuh_qb(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                NOROUND, UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "subuh_qb".
         */
        class Subuh_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Subuh_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::adduh_r_qb(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                ROUND, UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "adduh_r_qb".
         */
        class Adduh_r_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Adduh_r_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subuh_r_qb(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_QB,\n                                                ROUND, UNSIGNED);\n                            '],{})

        /**
         * Static instruction class for "subuh_r_qb".
         */
        class Subuh_r_qb : public DspIntOp
        {
          public:
                /// Constructor.
                Subuh_r_qb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::addqh_ph(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                NOROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "addqh_ph".
         */
        class Addqh_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Addqh_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subqh_ph(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                NOROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "subqh_ph".
         */
        class Subqh_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Subqh_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addqh_r_ph(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                ROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "addqh_r_ph".
         */
        class Addqh_r_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Addqh_r_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subqh_r_ph(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                                ROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "subqh_r_ph".
         */
        class Subqh_r_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Subqh_r_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::mul_ph(['\n                                Rd_sw = dspMul(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                               NOSATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mul_ph".
         */
        class Mul_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Mul_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::mul_s_ph(['\n                                Rd_sw = dspMul(Rs_sw, Rt_sw, SIMD_FMT_PH,\n                                               SATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mul_s_ph".
         */
        class Mul_s_ph : public DspIntOp
        {
          public:
                /// Constructor.
                Mul_s_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::addqh_w(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                NOROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "addqh_w".
         */
        class Addqh_w : public DspIntOp
        {
          public:
                /// Constructor.
                Addqh_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subqh_w(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                NOROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "subqh_w".
         */
        class Subqh_w : public DspIntOp
        {
          public:
                /// Constructor.
                Subqh_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::addqh_r_w(['\n                                Rd_uw = dspAddh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                ROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "addqh_r_w".
         */
        class Addqh_r_w : public DspIntOp
        {
          public:
                /// Constructor.
                Addqh_r_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::subqh_r_w(['\n                                Rd_uw = dspSubh(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                ROUND, SIGNED);\n                            '],{})

        /**
         * Static instruction class for "subqh_r_w".
         */
        class Subqh_r_w : public DspIntOp
        {
          public:
                /// Constructor.
                Subqh_r_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::mulq_s_w(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                SATURATE, NOROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mulq_s_w".
         */
        class Mulq_s_w : public DspIntOp
        {
          public:
                /// Constructor.
                Mulq_s_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::mulq_rs_w(['\n                                Rd_sw = dspMulq(Rs_sw, Rt_sw, SIMD_FMT_W,\n                                                SATURATE, ROUND, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mulq_rs_w".
         */
        class Mulq_rs_w : public DspIntOp
        {
          public:
                /// Constructor.
                Mulq_rs_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::wsbh(['\n                        Rd_uw = Rt_uw<23:16> << 24 |\n                                Rt_uw<31:24> << 16 |\n                                Rt_uw<7:0>   << 8  |\n                                Rt_uw<15:8>;\n                    '],{})

        /**
         * Static instruction class for "wsbh".
         */
        class Wsbh : public MipsStaticInst
        {
          public:
                /// Constructor.
                Wsbh(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::seb([' Rd_sw = Rt_sb; '],{})

        /**
         * Static instruction class for "seb".
         */
        class Seb : public MipsStaticInst
        {
          public:
                /// Constructor.
                Seb(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// BasicOp::seh([' Rd_sw = Rt_sh; '],{})

        /**
         * Static instruction class for "seh".
         */
        class Seh : public MipsStaticInst
        {
          public:
                /// Constructor.
                Seh(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspHiLoOp::dpa_w_ph(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpa_w_ph".
         */
        class Dpa_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpa_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dps_w_ph(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dps_w_ph".
         */
        class Dps_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dps_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::mulsa_w_ph(['\n                                dspac = dspMulsa(dspac, Rs_sw, Rt_sw,\n                                                 ACDST, SIMD_FMT_PH );\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mulsa_w_ph".
         */
        class Mulsa_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Mulsa_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpau_h_qbl(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpau_h_qbl".
         */
        class Dpau_h_qbl : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpau_h_qbl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpaq_s_w_ph(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpaq_s_w_ph".
         */
        class Dpaq_s_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpaq_s_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsq_s_w_ph(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsq_s_w_ph".
         */
        class Dpsq_s_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsq_s_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::mulsaq_s_w_ph(['\n                                dspac = dspMulsaq(dspac, Rs_sw, Rt_sw,\n                                                  ACDST, SIMD_FMT_PH,\n                                                  &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "mulsaq_s_w_ph".
         */
        class Mulsaq_s_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Mulsaq_s_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpau_h_qbr(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_R);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpau_h_qbr".
         */
        class Dpau_h_qbr : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpau_h_qbr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspHiLoOp::dpax_w_ph(['\n                                dspac = dspDpa(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_X);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpax_w_ph".
         */
        class Dpax_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpax_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsx_w_ph(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_PH, SIGNED, MODE_X);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsx_w_ph".
         */
        class Dpsx_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsx_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsu_h_qbl(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_L);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsu_h_qbl".
         */
        class Dpsu_h_qbl : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsu_h_qbl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpaq_sa_l_w(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_W,\n                                                SIMD_FMT_L, SATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpaq_sa_l_w".
         */
        class Dpaq_sa_l_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpaq_sa_l_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsq_sa_l_w(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_W,\n                                                SIMD_FMT_L, SATURATE,\n                                                MODE_L, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsq_sa_l_w".
         */
        class Dpsq_sa_l_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsq_sa_l_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsu_h_qbr(['\n                                dspac = dspDps(dspac, Rs_sw, Rt_sw, ACDST,\n                                               SIMD_FMT_QB, UNSIGNED, MODE_R);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsu_h_qbr".
         */
        class Dpsu_h_qbr : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsu_h_qbr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspHiLoOp::maq_sa_w_phl(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_L, SATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "maq_sa_w_phl".
         */
        class Maq_sa_w_phl : public DspHiLoOp
        {
          public:
                /// Constructor.
                Maq_sa_w_phl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::maq_sa_w_phr(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_R, SATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "maq_sa_w_phr".
         */
        class Maq_sa_w_phr : public DspHiLoOp
        {
          public:
                /// Constructor.
                Maq_sa_w_phr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::maq_s_w_phl(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_L, NOSATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "maq_s_w_phl".
         */
        class Maq_s_w_phl : public DspHiLoOp
        {
          public:
                /// Constructor.
                Maq_s_w_phl(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::maq_s_w_phr(['\n                                dspac = dspMaq(dspac, Rs_uw, Rt_uw,\n                                               ACDST, SIMD_FMT_PH,\n                                               MODE_R, NOSATURATE, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "maq_s_w_phr".
         */
        class Maq_s_w_phr : public DspHiLoOp
        {
          public:
                /// Constructor.
                Maq_s_w_phr(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspHiLoOp::dpaqx_s_w_ph(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpaqx_s_w_ph".
         */
        class Dpaqx_s_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpaqx_s_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsqx_s_w_ph(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, NOSATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsqx_s_w_ph".
         */
        class Dpsqx_s_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsqx_s_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpaqx_sa_w_ph(['\n                                dspac = dspDpaq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, SATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpaqx_sa_w_ph".
         */
        class Dpaqx_sa_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpaqx_sa_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::dpsqx_sa_w_ph(['\n                                dspac = dspDpsq(dspac, Rs_sw, Rt_sw,\n                                                ACDST, SIMD_FMT_PH,\n                                                SIMD_FMT_W, SATURATE,\n                                                MODE_X, &dspctl);\n                            ', 'IntMultOp'],{})

        /**
         * Static instruction class for "dpsqx_sa_w_ph".
         */
        class Dpsqx_sa_w_ph : public DspHiLoOp
        {
          public:
                /// Constructor.
                Dpsqx_sa_w_ph(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// IntOp::append(['\n                                Rt_uw = (Rt_uw << RD) | bits(Rs_uw, RD - 1, 0);\n                                '],{})

        /**
         * Static instruction class for "append".
         */
        class Append : public IntOp
        {
          public:
                /// Constructor.
                Append(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// IntOp::prepend(['\n                                Rt_uw = (Rt_uw >> RD) |\n                                        (bits(Rs_uw, RD - 1, 0) << (32 - RD));\n                            '],{})

        /**
         * Static instruction class for "prepend".
         */
        class Prepend : public IntOp
        {
          public:
                /// Constructor.
                Prepend(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// IntOp::balign(['\n                                Rt_uw = (Rt_uw << (8 * BP)) |\n                                        (Rs_uw >> (8 * (4 - BP)));\n                            '],{})

        /**
         * Static instruction class for "balign".
         */
        class Balign : public IntOp
        {
          public:
                /// Constructor.
                Balign(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// DspHiLoOp::extr_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, RS,\n                                                NOROUND, NOSATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extr_w".
         */
        class Extr_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extr_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extrv_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, Rs_uw,\n                                                NOROUND, NOSATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extrv_w".
         */
        class Extrv_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extrv_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extp(['\n                                Rt_uw = dspExtp(dspac, RS, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extp".
         */
        class Extp : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extpv(['\n                                Rt_uw = dspExtp(dspac, Rs_uw, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extpv".
         */
        class Extpv : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extpv(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extr_r_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, RS,\n                                                ROUND, NOSATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extr_r_w".
         */
        class Extr_r_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extr_r_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extrv_r_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, Rs_uw,\n                                                ROUND, NOSATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extrv_r_w".
         */
        class Extrv_r_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extrv_r_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extr_rs_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, RS,\n                                                ROUND, SATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extr_rs_w".
         */
        class Extr_rs_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extr_rs_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extrv_rs_w(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_W, Rs_uw,\n                                                ROUND, SATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extrv_rs_w".
         */
        class Extrv_rs_w : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extrv_rs_w(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspHiLoOp::extpdp(['\n                                Rt_uw = dspExtpd(dspac, RS, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extpdp".
         */
        class Extpdp : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extpdp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extpdpv(['\n                                Rt_uw = dspExtpd(dspac, Rs_uw, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extpdpv".
         */
        class Extpdpv : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extpdpv(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extr_s_h(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_PH, RS,\n                                                NOROUND, SATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extr_s_h".
         */
        class Extr_s_h : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extr_s_h(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::extrv_s_h(['\n                                Rt_uw = dspExtr(dspac, SIMD_FMT_PH, Rs_uw,\n                                                NOROUND, SATURATE, &dspctl);\n                            '],{})

        /**
         * Static instruction class for "extrv_s_h".
         */
        class Extrv_s_h : public DspHiLoOp
        {
          public:
                /// Constructor.
                Extrv_s_h(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspIntOp::rddsp(['\n                                Rd_uw = readDSPControl(&dspctl, RDDSPMASK);\n                            '],{})

        /**
         * Static instruction class for "rddsp".
         */
        class Rddsp : public DspIntOp
        {
          public:
                /// Constructor.
                Rddsp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspIntOp::wrdsp(['\n                                writeDSPControl(&dspctl, Rs_uw, WRDSPMASK);\n                            '],{})

        /**
         * Static instruction class for "wrdsp".
         */
        class Wrdsp : public DspIntOp
        {
          public:
                /// Constructor.
                Wrdsp(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// DspHiLoOp::shilo(['\n                                if (sext<6>(HILOSA) < 0) {\n                                    dspac = (uint64_t)dspac <<\n                                                -sext<6>(HILOSA);\n                                } else {\n                                    dspac = (uint64_t)dspac >>\n                                                sext<6>(HILOSA);\n                                }\n                            '],{})

        /**
         * Static instruction class for "shilo".
         */
        class Shilo : public DspHiLoOp
        {
          public:
                /// Constructor.
                Shilo(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::shilov(['\n                                if (sext<6>(Rs_sw<5:0>) < 0) {\n                                    dspac = (uint64_t)dspac <<\n                                                -sext<6>(Rs_sw<5:0>);\n                                } else {\n                                    dspac = (uint64_t)dspac >>\n                                                sext<6>(Rs_sw<5:0>);\n                                }\n                            '],{})

        /**
         * Static instruction class for "shilov".
         */
        class Shilov : public DspHiLoOp
        {
          public:
                /// Constructor.
                Shilov(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// DspHiLoOp::mthlip(['\n                                dspac = dspac << 32;\n                                dspac |= Rs_uw;\n                                dspctl = insertBits(dspctl, 5, 0,\n                                                    dspctl<5:0> + 32);\n                            '],{})

        /**
         * Static instruction class for "mthlip".
         */
        class Mthlip : public DspHiLoOp
        {
          public:
                /// Constructor.
                Mthlip(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// BasicOp::rdhwr_se(([' Rt = TpValue; '], {}))

        /**
         * Static instruction class for "rdhwr_se".
         */
        class Rdhwr_se : public MipsStaticInst
        {
          public:
                /// Constructor.
                Rdhwr_se(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// FailUnimpl::rdhwr(([], {}))

// FailUnimpl::rdhwr(([], {}))

// FailUnimpl::rdhwr(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))

// LoadMemory::lb([' Rt_sw = Mem_sb; '],{})

    /**
     * Static instruction class for "lb".
     */
    class Lb : public Memory
    {
      public:

        /// Constructor.
        Lb(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadMemory::lh([' Rt_sw = Mem_sh; '],{})

    /**
     * Static instruction class for "lh".
     */
    class Lh : public Memory
    {
      public:

        /// Constructor.
        Lh(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadMemory::lw([' Rt_sw = Mem_sw; '],{})

    /**
     * Static instruction class for "lw".
     */
    class Lw : public Memory
    {
      public:

        /// Constructor.
        Lw(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadMemory::lbu([' Rt_uw = Mem_ub;'],{})

    /**
     * Static instruction class for "lbu".
     */
    class Lbu : public Memory
    {
      public:

        /// Constructor.
        Lbu(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadMemory::lhu([' Rt_uw = Mem_uh; '],{})

    /**
     * Static instruction class for "lhu".
     */
    class Lhu : public Memory
    {
      public:

        /// Constructor.
        Lhu(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadUnalignedMemory::lwl(['\n                uint32_t mem_shift = 24 - (8 * byte_offset);\n                Rt_uw = mem_word << mem_shift | (Rt_uw & mask(mem_shift));\n            '],{})

    /**
     * Static instruction class for "lwl".
     */
    class Lwl : public Memory
    {
      public:

        /// Constructor.
        Lwl(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadUnalignedMemory::lwr(['\n                uint32_t mem_shift = 8 * byte_offset;\n                Rt_uw = (Rt_uw & (mask(mem_shift) << (32 - mem_shift))) |\n                        (mem_word >> mem_shift);\n            '],{})

    /**
     * Static instruction class for "lwr".
     */
    class Lwr : public Memory
    {
      public:

        /// Constructor.
        Lwr(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// Unknown::unknown(([], {}))

// StoreMemory::sb([' Mem_ub = Rt<7:0>; '],{})

    /**
     * Static instruction class for "sb".
     */
    class Sb : public Memory
    {
      public:

        /// Constructor.
        Sb(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreMemory::sh([' Mem_uh = Rt<15:0>; '],{})

    /**
     * Static instruction class for "sh".
     */
    class Sh : public Memory
    {
      public:

        /// Constructor.
        Sh(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreMemory::sw([' Mem_uw = Rt<31:0>; '],{})

    /**
     * Static instruction class for "sw".
     */
    class Sw : public Memory
    {
      public:

        /// Constructor.
        Sw(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreUnalignedMemory::swl(['\n                uint32_t reg_shift = 24 - (8 * byte_offset);\n                uint32_t mem_shift = 32 - reg_shift;\n                mem_word = (mem_word & (mask(reg_shift) << mem_shift)) |\n                           (Rt_uw >> reg_shift);\n                '],{})

    /**
     * Static instruction class for "swl".
     */
    class Swl : public Memory
    {
      public:

        /// Constructor.
        Swl(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreUnalignedMemory::swr(['\n                uint32_t reg_shift = 8 * byte_offset;\n                mem_word = Rt_uw << reg_shift |\n                           (mem_word & (mask(reg_shift)));\n            '],{})

    /**
     * Static instruction class for "swr".
     */
    class Swr : public Memory
    {
      public:

        /// Constructor.
        Swr(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// CP0Control::cache(['\n                //Addr CacheEA = Rs_uw + OFFSET;\n                //fault = xc->CacheOp((uint8_t)CACHE_OP,(Addr) CacheEA);\n            '],{})

        /**
         * Static instruction class for "cache".
         */
        class Cache : public CP0Control
        {
          public:
                /// Constructor.
                Cache(MachInst machInst);
                
        Fault execute(ExecContext *, Trace::InstRecord *) const;

        };

// Unknown::unknown(([], {}))

// LoadMemory::ll([' Rt_uw = Mem_uw; '],{'mem_flags': 'LLSC'})

    /**
     * Static instruction class for "ll".
     */
    class Ll : public Memory
    {
      public:

        /// Constructor.
        Ll(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadMemory::lwc1([' Ft_uw = Mem_uw; '],{})

    /**
     * Static instruction class for "lwc1".
     */
    class Lwc1 : public Memory
    {
      public:

        /// Constructor.
        Lwc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// LoadMemory::ldc1([' Ft_ud = Mem_ud; '],{})

    /**
     * Static instruction class for "ldc1".
     */
    class Ldc1 : public Memory
    {
      public:

        /// Constructor.
        Ldc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// CP2Unimpl::lwc2(([], {}))

// CP2Unimpl::ldc2(([], {}))

// Prefetch::pref(([], {}))

    /**
     * Static instruction class for "pref".
     */
    class Pref : public Memory
    {
      public:

        /// Constructor.
        Pref(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// Unknown::unknown(([], {}))

// StoreCond::sc(([' Mem_uw = Rt_uw; ', ' uint64_t tmp = write_result;\n                              Rt_uw = (tmp == 0 || tmp == 1) ? tmp : Rt_uw;\n                           '], {'inst_flags': 'IsStoreConditional', 'mem_flags': 'LLSC'}))

    /**
     * Static instruction class for "sc".
     */
    class Sc : public Memory
    {
      public:

        /// Constructor.
        Sc(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreMemory::swc1([' Mem_uw = Ft_uw; '],{})

    /**
     * Static instruction class for "swc1".
     */
    class Swc1 : public Memory
    {
      public:

        /// Constructor.
        Swc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// StoreMemory::sdc1([' Mem_ud = Ft_ud; '],{})

    /**
     * Static instruction class for "sdc1".
     */
    class Sdc1 : public Memory
    {
      public:

        /// Constructor.
        Sdc1(ExtMachInst machInst);

        
        Fault execute(ExecContext *, Trace::InstRecord *) const;


        
    Fault eaComp(ExecContext *, Trace::InstRecord *) const;


        
    Fault initiateAcc(ExecContext *, Trace::InstRecord *) const;


        
    Fault completeAcc(Packet *, ExecContext *, Trace::InstRecord *) const;

    };

// CP2Unimpl::swc2(([], {}))

// CP2Unimpl::sdc2(([], {}))

// Unknown::unknown(([], {}))

// Unknown::unknown(([], {}))
