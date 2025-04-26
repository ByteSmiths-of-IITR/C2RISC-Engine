#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-26 - 16:22:46) 🎨 ---------

.data

.text
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -22      # Allocating Stack Space
        sw    ra, 18(sp)       # Store return address (PC)
        sw    fp, 14(sp)       # Store old frame pointer
        addi  fp, sp,22        # Set new frame pointer
        #  ~~ Assign OP 🟰 - x$1 = $0
        lb    x12, -18(fp)     # Load Local Var - $0 via fp in x12
        #  🙋🏼 GetReg() for x$1 = $0 | 🤝 `x12` reg ➜ $0 | 🤝 `x12` reg ➜ x$1 |
        #  🔄 Automatically Assigned - $0 into x$1
        #  ~~ Assign OP 🟰 - a$1 = 3
        #  🙋🏼 GetReg() for a$1 = 3 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ a$1 |
        li    x13, 3           # Load constant - 3 into x13
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - main
        sb    x12, -18(fp)     # Store Local Var - $0 via fp in x12
        sb    x12, -17(fp)     # Store Local Var - x$1 via fp in x12
        sw    x13, -22(fp)     # Store Local Var - a$1 via fp in x13
        #    ~~ Finished Variable Spilling Code
        mv    a0, a5           # Move return value to a0
        lw    ra, 18(sp)       # Restore return address (PC)
        lw    fp, 14(sp)       # Restore old frame pointer
        addi  sp, sp, 22       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - main
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


