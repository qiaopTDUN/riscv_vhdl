/*
 *  Copyright 2018 Sergey Khabarov, sergeykhbr@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef __DEBUGGER_SRC_COMMON_CORESERVICES_ICPUARM_H__
#define __DEBUGGER_SRC_COMMON_CORESERVICES_ICPUARM_H__

#include "iface.h"
#include <inttypes.h>

namespace debugger {

static const char *const IFACE_CPU_ARM = "ICpuArm";

/** Signal types */
//static const int CPU_SIGNAL_RESET   = 0;
//static const int CPU_SIGNAL_EXT_IRQ = 1;

enum EInstructionModes {
    ARM_mode,
    THUMB_mode,
    Jazelle_mode,
    InstrModes_Total = 4
};

enum ECoreModes {
    User_mode = 0x10,
    FIQ_mode = 0x11,
    IRQ_mode = 0x12,
    Supervisor_mode = 0x13,
    Abort_mode = 0x17,
    Undefined_mode = 0x1B,
    System_mode = 0x1F,
    CoreModes_Total = 32
};

enum SRType {
    SRType_None,
    SRType_LSL,
    SRType_LSR,
    SRType_ASR,
    SRType_ROR,
    SRType_RRX
};

class ICpuArm : public IFace {
 public:
    ICpuArm() : IFace(IFACE_CPU_ARM) {}

    virtual void setInstrMode(EInstructionModes mode) = 0;
    virtual EInstructionModes getInstrMode() = 0;

    virtual void setReg(int idx, uint64_t val) = 0;

    /** Zero flag */
    virtual uint32_t getZ() = 0;
    virtual void setZ(uint32_t z) = 0;

    /** Unsigned higer or same (carry flag) */
    virtual uint32_t getC() = 0;
    virtual void setC(uint32_t c) = 0;

    /** Negative flag */
    virtual uint32_t getN() = 0;
    virtual void setN(uint32_t n) = 0;

    /** Overflow flag */
    virtual uint32_t getV() = 0;
    virtual void setV(uint32_t v) = 0;

    /** Impersize Data abort */
    virtual uint32_t getA() = 0;
    virtual void setA(uint32_t v) = 0;

    /** IRQ interrupt */
    virtual uint32_t getI() = 0;
    virtual void setI(uint32_t v) = 0;

    /** FIQ interrupt */
    virtual uint32_t getF() = 0;
    virtual void setF(uint32_t v) = 0;

    // DZ = CP15[19] Divide-by-zero (generate fault exception)
    virtual uint32_t getDZ() { return 0; }

    /** This function returns TRUE if execution is currently in an IT block 
        and FALSE otherwise. IT allows one of four following Thumb instructions
        (the IT block) to be conditional */
    virtual bool InITBlock() = 0;
    virtual bool LastInITBlock() = 0;
};

}  // namespace debugger

#endif  // __DEBUGGER_SRC_COMMON_CORESERVICES_ICPUARM_H__

