#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-26 - 13:44:01) 🎨 ---------

.data

.text
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -32
        sw    ra, 28(sp)
        sw    s0, 24(sp)
        addi  s0, sp,32
        #  -- ENTRY Activation (end) - main
        #  ~~ Assign OP - a$1 = 5
        #  ## GetReg() - a$1 = 5
        #    == NULL is given `x0` reg ==
        #    == a$1 is given `x12` reg ==
        li    x12, 5
        #  ~~ Ampersend (&) - $0 = &a$1
        #  ## GetReg() - $0 = &a$1
        #    == $0 is given `x13` reg ==
        #    == NULL is given `x0` reg ==
        addi  x13, s0, -20
        #  ~~ Assign OP - p$1 = $0
        lw    x14, -28(s0)
        #  ## GetReg() - p$1 = $0
        #    == $0 is given `x14` reg ==
        #    == p$1 is given `x14` reg ==
        #  ~~ Ampersend (&) - $1 = &b$0
        #  ## GetReg() - $1 = &b$0
        #    == $1 is given `x15` reg ==
        #    == NULL is given `x0` reg ==
        la    x15, b$0
        #  ~~ Assign OP - p$1 = $1
        lw    x16, -32(s0)
        #  ## GetReg() - p$1 = $1
        #    == $1 is given `x16` reg ==
        #    == p$1 is given `x16` reg ==
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - main
        sw    x12, -24(s0)
        sw    x14, -32(s0)
        sw    x16, -36(s0)
        sw    x16, -28(s0)
        #    ~~ Finished Variable Spilling Code
        lw    a1, -20(sp)
        mv    a0, a5
        lw    ra, 28(sp)
        lw    s0, 24(sp)
        addi  sp, sp, 32
        jr    ra
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - main
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


