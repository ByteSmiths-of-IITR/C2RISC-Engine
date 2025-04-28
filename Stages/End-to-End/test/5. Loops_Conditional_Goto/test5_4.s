#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 04:02:39) 🎨 ---------

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
        addi    sp, sp, -48    # Allocating Stack Space
        sw      ra, 44(sp)     # Store return address (PC)
        sw      fp, 40(sp)     # Store old frame pointer
        addi    fp, sp,48      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - i$1 = 0
        # 
# 🤙🏼 Calling getReg() for i$1 = 0
        #  🟢 Found Free Register - 12 for i$1
        # 
# 👋 GetReg() for i$1 = 0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ i$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 i$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        li      x12, 0         # Load constant - 0 into x12(i$1)
        Block_4:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_4
        sw      x12, -20(fp)   # Store Local Var - i$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 i$1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = i$1 < 10
        # 
# 🤙🏼 Calling getReg() for $0 = i$1 < 10
        #  🟢 Found Free Register - 12 for i$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - i$1 via fp in x12
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = i$1 < 10 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ i$1 |
        li      t1, 10         # Loading Immediate Value - 10 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        slt     x13, x12, t1   # Less Than Operation - $0 = i$1 < 10
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $0 goto L(Block_0)
        # 
# 🤙🏼 Calling getReg() for if $0 goto L(Block_0)
        #  🔵 Already in register - $0 in 13
        # 
# 👋 GetReg() for if $0 goto L(Block_0) | 🤝 `x13` reg ➜ $0 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x13, -24(fp)   # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x13, x0, Block_0 # Jump to label - Block_0 if $0 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_1)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_1        # Unconditional Jump to label - Block_1
        Block_0:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_0
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = i$1 == 5
        # 
# 🤙🏼 Calling getReg() for $1 = i$1 == 5
        #  🟢 Found Free Register - 12 for i$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - i$1 via fp in x12
        #  🟢 Found Free Register - 13 for $1
        # 
# 👋 GetReg() for $1 = i$1 == 5 | 🤝 `x13` reg ➜ $1 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ i$1 |
        li      t1, 5          # Loading Immediate Value - 5 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 13
        sub     t1, x12, t1    # Part1 of Equality Operation - $1 = i$1 == 5
        seqz    x13, t1        # Part2 of Equality Operation - $1 = i$1 == 5
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $1 goto L(Block_2)
        # 
# 🤙🏼 Calling getReg() for if $1 goto L(Block_2)
        #  🔵 Already in register - $1 in 13
        # 
# 👋 GetReg() for if $1 goto L(Block_2) | 🤝 `x13` reg ➜ $1 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x13, -28(fp)   # Store Local Var - $1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x13, x0, Block_2 # Jump to label - Block_2 if $1 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_3)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_3        # Unconditional Jump to label - Block_3
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $2 = i$1
        # 🪦 Ignoring Assignment ☠️ dead variable $2
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - i$1 = i$1 + 1
        # 
# 🤙🏼 Calling getReg() for i$1 = i$1 + 1
        #  🟢 Found Free Register - 12 for i$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - i$1 via fp in x12
        #  🔵 Already in (ex)register - i$1 in 12
        # 
# 👋 GetReg() for i$1 = i$1 + 1 | 🤝 `x12` reg ➜ i$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 i$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        add     x12, x12, t1   # Addition Operation - i$1 = i$1 + 1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_4)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        sw      x12, -20(fp)   # Store Local Var - i$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 i$1 in memory
        #  🫗 Finished Spilling Code 👌 
        j       Block_4        # Unconditional Jump to label - Block_4
        Block_3:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_3
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - j$5 = 0
        # 
# 🤙🏼 Calling getReg() for j$5 = 0
        #  🟢 Found Free Register - 12 for j$5
        # 
# 👋 GetReg() for j$5 = 0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ j$5 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 j$5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 j$5 to register 12
        li      x12, 0         # Load constant - 0 into x12(j$5)
        Block_7:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_7
        sw      x12, -36(fp)   # Store Local Var - j$5 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 j$5 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = j$5 < 2
        # 
# 🤙🏼 Calling getReg() for $3 = j$5 < 2
        #  🟢 Found Free Register - 12 for j$5
        # 💛 SYM_RECORD 💛 - Adding 🌕 j$5 to register 12
        lw      x12, -36(fp)   # Load Local Var - j$5 via fp in x12
        #  🟢 Found Free Register - 13 for $3
        # 
# 👋 GetReg() for $3 = j$5 < 2 | 🤝 `x13` reg ➜ $3 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ j$5 |
        li      t1, 2          # Loading Immediate Value - 2 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        slt     x13, x12, t1   # Less Than Operation - $3 = j$5 < 2
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $3 goto L(Block_5)
        # 
# 🤙🏼 Calling getReg() for if $3 goto L(Block_5)
        #  🔵 Already in register - $3 in 13
        # 
# 👋 GetReg() for if $3 goto L(Block_5) | 🤝 `x13` reg ➜ $3 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x13, -40(fp)   # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x13, x0, Block_5 # Jump to label - Block_5 if $3 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_6)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_6        # Unconditional Jump to label - Block_6
        Block_5:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_5
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $4 = j$5
        # 🪦 Ignoring Assignment ☠️ dead variable $4
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - j$5 = j$5 + 1
        # 
# 🤙🏼 Calling getReg() for j$5 = j$5 + 1
        #  🟢 Found Free Register - 12 for j$5
        # 💛 SYM_RECORD 💛 - Adding 🌕 j$5 to register 12
        lw      x12, -36(fp)   # Load Local Var - j$5 via fp in x12
        #  🔵 Already in (ex)register - j$5 in 12
        # 
# 👋 GetReg() for j$5 = j$5 + 1 | 🤝 `x12` reg ➜ j$5 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 j$5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 j$5 to register 12
        add     x12, x12, t1   # Addition Operation - j$5 = j$5 + 1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_7)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        sw      x12, -36(fp)   # Store Local Var - j$5 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 j$5 in memory
        #  🫗 Finished Spilling Code 👌 
        j       Block_7        # Unconditional Jump to label - Block_7
        Block_6:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_6
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $5 = i$1
        # 🪦 Ignoring Assignment ☠️ dead variable $5
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - i$1 = i$1 + 1
        # 
# 🤙🏼 Calling getReg() for i$1 = i$1 + 1
        #  🟢 Found Free Register - 12 for i$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - i$1 via fp in x12
        #  🔵 Already in (ex)register - i$1 in 12
        # 
# 👋 GetReg() for i$1 = i$1 + 1 | 🤝 `x12` reg ➜ i$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 i$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$1 to register 12
        add     x12, x12, t1   # Addition Operation - i$1 = i$1 + 1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_4)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        sw      x12, -20(fp)   # Store Local Var - i$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 i$1 in memory
        #  🫗 Finished Spilling Code 👌 
        j       Block_4        # Unconditional Jump to label - Block_4
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 44(sp)     # Restore return address (PC)
        lw      fp, 40(sp)     # Restore old frame pointer
        addi    sp, sp, 48     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


