#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-28 - 10:55:11) 🎨 ---------

.data
        a:      .word          7

.text
        main:
        #  ~TAC~ ➔ ENTRY (start) - main
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Store return address (PC)
        sw    fp, 12(sp)       # Store old frame pointer
        addi  fp, sp,20        # Set new frame pointer
        #  ~TAC~ ➔ Assign OP 🟰 - a$1 = 3
        #  🙋🏼 GetReg() for a$1 = 3 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        li    x12, 3           # Load constant - 3 into x12(a$1)
        #  ~TAC~ ➔ IF_TRUE - if a$1 goto L(Block_0)
        #  🙋🏼 GetReg() for if a$1 goto L(Block_0) | 🤝 `x12` reg ➜ a$1 |
        bne   x12, x0, Block_0 # Jump to label - Block_0 if a$1 is true
        #  ~TAC~ ➔ GOTO_LABEL - goto L(Block_1)
        j     Block_1          # Unconditional Jump to label - Block_1
        #  ~~ At End of Block Variable Spilling - main
        sw    x12, -20(fp)     # Store Local Var - a$1 via fp in x12
        #  ~~ Finished Spilling Variable at end of block 
        Block_0:
        #  ~TAC~ ➔ Return Statements - return 3
        li    t1, 3            # Load constant - 3 into t1
        mv    a1, t1           # Move return value's reg - t1 to a1
        #  ~TAC~ ➔ GOTO_LABEL - goto L(Block_2)
        j     Block_2          # Unconditional Jump to label - Block_2
        #  ~~ At End of Block Variable Spilling - Block_0
        #  ~~ Finished Spilling Variable at end of block 
        Block_1:
        #  ~TAC~ ➔ Return Statements - return 4
        li    t1, 4            # Load constant - 4 into t1
        mv    a1, t1           # Move return value's reg - t1 to a1
        #  ~~ At End of Block Variable Spilling - Block_1
        #  ~~ Finished Spilling Variable at end of block 
        Block_2:
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - Block_2
        #    ~~ Finished Variable Spilling Code
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 16(sp)       # Restore return address (PC)
        lw    fp, 12(sp)       # Restore old frame pointer
        addi  sp, sp, 20       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - Block_2
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


