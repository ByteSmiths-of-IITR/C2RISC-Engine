#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-27 - 23:22:48) 🎨 ---------

.data

.text
        foo:
        #  -- ENTRY Activation (start) - foo
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Store return address (PC)
        sw    fp, 12(sp)       # Store old frame pointer
        addi  fp, sp,20        # Set new frame pointer
        #  ~TAC~ Assign OP 🟰 - $0 = 4
        #  🙋🏼 GetReg() for $0 = 4 | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        li    x12, 4           # Load constant - 4 into x12
        #  ~TAC~ Return Statements - return $0
        #  🙋🏼 GetReg() for return $0 | 🤝 `x12` reg ➜ $0 |
        mv    a0, x12          # Move return value's reg - x12 to a0
        #  -- EXIT Activation (start) - foo
        #    ~~ At End of Funcion Spilling Code - foo
        sw    x12, -20(fp)     # Store Local Var - $0 via fp in x12
        #    ~~ Finished Variable Spilling Code
        lw    ra, 16(sp)       # Restore return address (PC)
        lw    fp, 12(sp)       # Restore old frame pointer
        addi  sp, sp, 20       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - foo
        #  ~~ At End of Block Variable Spilling - foo
        #  ~~ Finished Spilling Variable at end of block 
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -24      # Allocating Stack Space
        sw    ra, 20(sp)       # Store return address (PC)
        sw    fp, 16(sp)       # Store old frame pointer
        addi  fp, sp,24        # Set new frame pointer
        #  ~TAC~ Function Call - $1 = call foo, 0
        jal   x1, foo          # Call function - foo
        sw    a0, -24(fp)      # Store return value in caller's stack for - $1
        #  ~TAC~ Assign OP 🟰 - a$2 = $1
        lw    x0, -24(fp)      # Load Local Var - $1 via fp in x0
        #  🙋🏼 GetReg() for a$2 = $1 | 🤝 `x0` reg ➜ $1 | 🤝 `x0` reg ➜ a$2 |
        #  🔄 Automatic copy - of $1 into 
        #  ~TAC~ Return Statements - return 
        mv    a0, x0           # Move return value's reg - x0 to a0
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - main
        sw    x0, -20(fp)      # Store Local Var - a$2 via fp in x0
        #    ~~ Finished Variable Spilling Code
        lw    ra, 20(sp)       # Restore return address (PC)
        lw    fp, 16(sp)       # Restore old frame pointer
        addi  sp, sp, 24       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - main
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


