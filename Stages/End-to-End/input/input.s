#-------- 🎨 RISC-V Code Generation using C2RISC-Engine 🎨 -------

.data

.text
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -20
        sw    ra, 16(sp)
        sw    s0, 12(sp)
        addi  s0, sp,20
        #  -- ENTRY Activation (end) - main
        li    x12, 9
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - main
        sw    x12, -20(s0)
        #    ~~ Finished Variable Spilling Code
        lw    a1, -8(sp)
        mv    a0, a5
        lw    ra, 16(sp)
        lw    s0, 12(sp)
        addi  sp, sp, 20
        jr    ra
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - main
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


