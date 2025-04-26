#-------- 🎨 RISC-V Code Generation using C2RISC-Engine at 2025-04-26 - 11:38:53 🎨 ---------

.data

.text
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -28
        sw    ra, 24(sp)
        sw    s0, 20(sp)
        addi  s0, sp,28
        #  -- ENTRY Activation (end) - main
        li    x12, 43
        lw    x13, -28(s0)
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - main
        sw    x12, -20(s0)
        sw    x13, -28(s0)
        sw    x13, -24(s0)
        #    ~~ Finished Variable Spilling Code
        lw    a1, -16(sp)
        mv    a0, a5
        lw    ra, 24(sp)
        lw    s0, 20(sp)
        addi  sp, sp, 28
        jr    ra
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - main
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------

----------------------------------- SEMANTIC LOG -----------------------------------
----------------------------------- END OF LOG -----------------------------------

