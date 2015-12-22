// DO NOT EDIT
// This file was automatically generated from an ISA description:
//   mips/isa/main.isa

#include "decoder.hh"

#include <cmath>

#include "arch/mips/decoder.hh"
#include "arch/mips/dsp.hh"
#include "arch/mips/dt_constants.hh"
#include "arch/mips/faults.hh"
#include "arch/mips/isa_traits.hh"
#include "arch/mips/mt_constants.hh"
#include "arch/mips/pagetable.hh"
#include "arch/mips/pra_constants.hh"
#include "arch/mips/tlb.hh"
#include "arch/mips/utility.hh"
#include "base/loader/symtab.hh"
#include "base/cprintf.hh"
#include "cpu/thread_context.hh"
#include "mem/packet.hh"
#include "sim/full_system.hh"
#if defined(linux)
#include <fenv.h>
#endif

using namespace MipsISA;
