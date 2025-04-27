#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-28 - 01:25:53) 🎨 ---------

.data

.text
        main:
        #  -- ENTRY Activation (start) - main
        addi  sp, sp, -32      # Allocating Stack Space
        sw    ra, 28(sp)       # Store return address (PC)
        sw    fp, 24(sp)       # Store old frame pointer
        addi  fp, sp,32        # Set new frame pointer
        #  ~TAC~ Assign OP 🟰 - a$1 = 5
        #  🙋🏼 GetReg() for a$1 = 5 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        li    x12, 5           # Load constant - 5 into x12
        #  ~TAC~ Assign OP 🟰 - b$1 = 3
        #  🙋🏼 GetReg() for b$1 = 3 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ b$1 |
        li    x13, 3           # Load constant - 3 into x13
        #  ~TAC~ Simple Operation - $0 = a$1 + b$1
        #  🙋🏼 GetReg() for $0 = a$1 + b$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x12` reg ➜ a$1 | 🤝 `x13` reg ➜ b$1 |
        add   x14, x12, x13    # Addition Operation - $0 = a$1 + b$1
        #  ~TAC~ Assign OP 🟰 - sum$1 = $0
        #  🙋🏼 GetReg() for sum$1 = $0 | 🤝 `x14` reg ➜ $0 | 🤝 `x14` reg ➜ sum$1 |
        #  🔄 Automatic copy - of $0 into 
        #  ~TAC~ Return Statements - return 0
        #  🙋🏼 GetReg() for return 0 |
        mv    a0, x0           # Move return value's reg - x0 to a0
        #  -- EXIT Activation (start) - main
        #    ~~ At End of Funcion Spilling Code - main
        sw    x12, -20(fp)     # Store Local Var - a$1 via fp in x12
        sw    x13, -24(fp)     # Store Local Var - b$1 via fp in x13
        sw    x14, -32(fp)     # Store Local Var - $0 via fp in x14
        sw    x14, -28(fp)     # Store Local Var - sum$1 via fp in x14
        #    ~~ Finished Variable Spilling Code
        lw    ra, 28(sp)       # Restore return address (PC)
        lw    fp, 24(sp)       # Restore old frame pointer
        addi  sp, sp, 32       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  ~~ At End of Block Variable Spilling - main
        #  ~~ Finished Spilling Variable at end of block 

#-------------------------------------------------------------------------


