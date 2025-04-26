
🎨 CFG Code Generation completed successfully 🎨
#-------------------------------------------------------------------------
====================== [ CFG Code ] ======================
.data

.text
ENTRY : 
main : 
    0 : main: Func ENTER          | Default            | 
    1 : alloca a$1, 4             | a$1 ☠️             | 
    2 : a$1 = 7                   | Default            | 
    3 : goto L(Block_0)           | Default            | 
Block_0 : 
   13 : if a$1 == 1 goto L(Block_1) | Default            | 
Block_1 : 
    4 : a$1 = 1                   | Default            | 
    5 : goto L(Block_2)           | Default            | 
Block_2 : 
   17 : return                    | Default            | 
   18 : main ret(4): EXIT         | Default            | 
EXIT : 
#-------------------------------------------------------------------------


#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-27 - 01:08:51) 🎨 ---------

.data

.text
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Store return address (PC)
        sw    fp, 12(sp)       # Store old frame pointer
        addi  fp, sp,20        # Set new frame pointer
        #  ~~ Assign OP 🟰 - a$1 = 7
        #  🙋🏼 GetReg() for a$1 = 7 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        li    x12, 7           # Load constant - 7 into x12
        j     #####            # Unconditional Jump to label - #####
        #  ~~ At End of Block Variable Spilling - main
        sw    x12, -20(fp)     # Store Local Var - a$1 via fp in x12
        #  ~~ Finished Spilling Variable at end of block 
        Block_0:
        #  🙋🏼 GetReg() for if a$1 == 1 goto L(Block_1) | 🤝 `x12` reg ➜ a$1 |
        beq   x12, x0, Block_1 # Jump to label - Block_1 if a$1 == 1
        #  ~~ At End of Block Variable Spilling - Block_0
        #  ~~ Finished Spilling Variable at end of block 
        Block_1:
        #  ~~ Assign OP 🟰 - a$1 = 1
        #  🙋🏼 GetReg() for a$1 = 1 | 🤝 `x0` reg ➜ NULL | 🤝 `x0` reg ➜ a$1 |
        li    x0, 1            # Load constant - 1 into x0
        j     #####            # Unconditional Jump to label - #####
        #  ~~ At End of Block Variable Spilling - Block_1
        sw    x0, -20(fp)      # Store Local Var - a$1 via fp in x0
        #  ~~ Finished Spilling Variable at end of block 
        Block_2:
        mv    a0, x0           # Move return value's reg - x0 to a0
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - Block_2
        #    ~~ Finished Variable Spilling Code
        lw    ra, 16(sp)       # Restore return address (PC)
        lw    fp, 12(sp)       # Restore old frame pointer
        addi  sp, sp, 20       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - Block_2
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


