#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 04:02:38) 🎨 ---------

.data

.text
        # #define <stdio.h> INCLUDED
        #  ==== Adding Print and Scan Library ==== 
        printVar:              # Function Signature - void printVar(int var)
        # Function Entry - printVar
        addi    sp, sp, -20    # Allocating Stack Space
        sw      ra, 16(sp)     # Saving Return Address
        sw      fp, 12(sp)     # Saving Frame Pointer
        addi    fp, sp, -20    # Setting Frame Pointer
        li      a7, 1          # Loading Print System Call Code
        ecall                  # System Call for Print
        # Function Exit - printVar
        li      a0, 0          # Return value from printVar
        lw      ra, 16(sp)     # Restoring Return Address
        lw      fp, 12(sp)     # Restoring Frame Pointer
        addi    sp, sp, 20     # Deallocating Stack Space
        jr      ra             # Returning from printVar
        # End of Function - printVar
        printString:           # Function Signature - void printString(char *str)
        # Function Entry - printVar
        addi    sp, sp, -20    # Allocating Stack Space
        sw      ra, 16(sp)     # Saving Return Address
        sw      fp, 12(sp)     # Saving Frame Pointer
        addi    fp, sp, -20    # Setting Frame Pointer
        li      a7, 4          # Loading Print System Call Code
        ecall                  # System Call for Print
        # Function Exit - printString
        li      a0, 0          # Return value from printString
        lw      ra, 16(sp)     # Restoring Return Address
        lw      fp, 12(sp)     # Restoring Frame Pointer
        addi    sp, sp, 20     # Deallocating Stack Space
        jr      ra             # Returning from printString
        # End of Function - printString
        scanVar:               # Function Signature - int scanVar()
        addi    sp, sp, -20    # Allocating Stack Space
        sw      ra, 16(sp)     # Saving Return Address
        sw      fp, 12(sp)     # Saving Frame Pointer
        addi    fp, sp, -20    # Setting Frame Pointer
        li      a7, 5          # Loading Scan System Call Code
        ecall                  # System Call for Scan
        sw      a0, -20(fp)    # Storing Scan Result in Variable(Redundant)
        # Result already in a0 register
        lw      ra, 16(sp)     # Restoring Return Address
        lw      fp, 12(sp)     # Restoring Frame Pointer
        addi    sp, sp, 20     # Deallocating Stack Space
        jr      ra             # Returning from scanVar
        # End of Function - scanVar
        #  ==== End of Print and Scan Library ==== 
        #  
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -36    # Allocating Stack Space
        sw      ra, 32(sp)     # Store return address (PC)
        sw      fp, 28(sp)     # Store old frame pointer
        addi    fp, sp,36      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = 10
        # 
# 🤙🏼 Calling getReg() for a$1 = 10
        #  🟢 Found Free Register - 12 for a$1
        # 
# 👋 GetReg() for a$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = 20
        # 
# 🤙🏼 Calling getReg() for b$1 = 20
        #  🟢 Found Free Register - 13 for b$1
        # 
# 👋 GetReg() for b$1 = 20 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 13
        li      x13, 20        # Load constant - 20 into x13(b$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - c$1 = 30
        # 
# 🤙🏼 Calling getReg() for c$1 = 30
        #  🟢 Found Free Register - 14 for c$1
        # 
# 👋 GetReg() for c$1 = 30 | 🤝 `x0` reg ➜ NULL | 🤝 `x14` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 c$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 14
        li      x14, 30        # Load constant - 30 into x14(c$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a$1 > b$1
        # 
# 🤙🏼 Calling getReg() for $0 = a$1 > b$1
        #  🔵 Already in register - a$1 in 12
        #  🔵 Already in register - b$1 in 13
        #  🟢 Found Free Register - 15 for $0
        # 
# 👋 GetReg() for $0 = a$1 > b$1 | 🤝 `x15` reg ➜ $0 | 🤝 `x12` reg ➜ a$1 | 🤝 `x13` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 15
        slt     x15, x13, x12  # Greater Than Operation - $0 = a$1 > b$1
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $0 goto L(Block_0)
        # 
# 🤙🏼 Calling getReg() for if $0 goto L(Block_0)
        #  🔵 Already in register - $0 in 15
        # 
# 👋 GetReg() for if $0 goto L(Block_0) | 🤝 `x15` reg ➜ $0 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x12, -20(fp)   # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        sw      x13, -24(fp)   # Store Local Var - b$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        sw      x14, -28(fp)   # Store Local Var - c$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 c$1 in memory
        sw      x15, -32(fp)   # Store Local Var - $0 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x15, x0, Block_0 # Jump to label - Block_0 if $0 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_1)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_1        # Unconditional Jump to label - Block_1
        Block_0:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_0
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = 3
        # 
# 🤙🏼 Calling getReg() for a$1 = 3
        #  🟢 Found Free Register - 12 for a$1
        # 
# 👋 GetReg() for a$1 = 3 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        li      x12, 3         # Load constant - 3 into x12(a$1)
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        sw      x12, -20(fp)   # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        #  🫗 Finished Spilling Code 👌 
        j       Block_2        # Unconditional Jump to label - Block_2
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = b$1 > c$1
        # 
# 🤙🏼 Calling getReg() for $1 = b$1 > c$1
        #  🟢 Found Free Register - 12 for b$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 12
        lw      x12, -24(fp)   # Load Local Var - b$1 via fp in x12
        #  🟢 Found Free Register - 13 for c$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 13
        lw      x13, -28(fp)   # Load Local Var - c$1 via fp in x13
        #  🟢 Found Free Register - 14 for $1
        # 
# 👋 GetReg() for $1 = b$1 > c$1 | 🤝 `x14` reg ➜ $1 | 🤝 `x12` reg ➜ b$1 | 🤝 `x13` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 14
        slt     x14, x13, x12  # Greater Than Operation - $1 = b$1 > c$1
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $1 goto L(Block_3)
        # 
# 🤙🏼 Calling getReg() for if $1 goto L(Block_3)
        #  🔵 Already in register - $1 in 14
        # 
# 👋 GetReg() for if $1 goto L(Block_3) | 🤝 `x14` reg ➜ $1 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x14, -36(fp)   # Store Local Var - $1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x14, x0, Block_3 # Jump to label - Block_3 if $1 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_4)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_4        # Unconditional Jump to label - Block_4
        Block_3:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_3
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = 2
        # 
# 🤙🏼 Calling getReg() for b$1 = 2
        #  🟢 Found Free Register - 12 for b$1
        # 
# 👋 GetReg() for b$1 = 2 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 12
        li      x12, 2         # Load constant - 2 into x12(b$1)
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        sw      x12, -24(fp)   # Store Local Var - b$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        #  🫗 Finished Spilling Code 👌 
        j       Block_2        # Unconditional Jump to label - Block_2
        Block_4:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_4
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - c$1 = 1
        # 
# 🤙🏼 Calling getReg() for c$1 = 1
        #  🟢 Found Free Register - 12 for c$1
        # 
# 👋 GetReg() for c$1 = 1 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 c$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 12
        li      x12, 1         # Load constant - 1 into x12(c$1)
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        sw      x12, -28(fp)   # Store Local Var - c$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 c$1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 32(sp)     # Restore return address (PC)
        lw      fp, 28(sp)     # Restore old frame pointer
        addi    sp, sp, 36     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


