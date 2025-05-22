#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:14:02) 🎨 ---------

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
        addi    sp, sp, -96    # Allocating Stack Space
        sw      ra, 92(sp)     # Store return address (PC)
        sw      fp, 88(sp)     # Store old frame pointer
        addi    fp, sp,96      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - size$1 = 5
        # 
# 🤙🏼 Calling getReg() for size$1 = 5
        #  🟢 Found Free Register - 12 for size$1
        # 
# 👋 GetReg() for size$1 = 5 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ size$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 size$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 size$1 to register 12
        li      x12, 5         # Load constant - 5 into x12(size$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - sum$1 = 0
        # 
# 🤙🏼 Calling getReg() for sum$1 = 0
        #  🟢 Found Free Register - 13 for sum$1
        # 
# 👋 GetReg() for sum$1 = 0 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 sum$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 sum$1 to register 13
        li      x13, 0         # Load constant - 0 into x13(sum$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - i$2 = 0
        # 
# 🤙🏼 Calling getReg() for i$2 = 0
        #  🟢 Found Free Register - 14 for i$2
        # 
# 👋 GetReg() for i$2 = 0 | 🤝 `x0` reg ➜ NULL | 🤝 `x14` reg ➜ i$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 i$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$2 to register 14
        li      x14, 0         # Load constant - 0 into x14(i$2)
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        sw      x12, -40(fp)   # Store Local Var - size$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 size$1 in memory
        sw      x13, -44(fp)   # Store Local Var - sum$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 sum$1 in memory
        sw      x14, -48(fp)   # Store Local Var - i$2 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 i$2 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = i$2 < size$1
        # 
# 🤙🏼 Calling getReg() for $0 = i$2 < size$1
        #  🟢 Found Free Register - 12 for i$2
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$2 to register 12
        lw      x12, -48(fp)   # Load Local Var - i$2 via fp in x12
        #  🟢 Found Free Register - 13 for size$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 size$1 to register 13
        lw      x13, -40(fp)   # Load Local Var - size$1 via fp in x13
        #  🟢 Found Free Register - 14 for $0
        # 
# 👋 GetReg() for $0 = i$2 < size$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x12` reg ➜ i$2 | 🤝 `x13` reg ➜ size$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 14
        slt     x14, x12, x13  # Less Than Operation - $0 = i$2 < size$1
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $0 goto L(Block_0)
        # 
# 🤙🏼 Calling getReg() for if $0 goto L(Block_0)
        #  🔵 Already in register - $0 in 14
        # 
# 👋 GetReg() for if $0 goto L(Block_0) | 🤝 `x14` reg ➜ $0 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x14, -52(fp)   # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x14, x0, Block_0 # Jump to label - Block_0 if $0 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_1)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_1        # Unconditional Jump to label - Block_1
        Block_0:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_0
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $1 = arr$1.offset
        # 
# 🤙🏼 Calling getReg() for $1 = arr$1.offset
        #  🟢 Found Free Register - 12 for $1
        # 
# 👋 GetReg() for $1 = arr$1.offset | 🤝 `x12` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        addi    x12, fp, -36   # Load address of variable (via fp) - arr$1 into x12
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $2 = i$2 << 2
        # 
# 🤙🏼 Calling getReg() for $2 = i$2 << 2
        #  🟢 Found Free Register - 13 for i$2
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$2 to register 13
        lw      x13, -48(fp)   # Load Local Var - i$2 via fp in x13
        #  🟢 Found Free Register - 14 for $2
        # 
# 👋 GetReg() for $2 = i$2 << 2 | 🤝 `x14` reg ➜ $2 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ i$2 |
        li      t1, 2          # Loading Immediate Value - 2 in x13
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 14
        sll     x14, x13, t1   # Left Shift Operation - $2 = i$2<< 2
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = $1 + $2
        # 
# 🤙🏼 Calling getReg() for $3 = $1 + $2
        #  🔵 Already in register - $1 in 12
        #  🔵 Already in register - $2 in 14
        #  🍊 Giving $3 same reg as given to $1 since it not used again
        # 
# 👋 GetReg() for $3 = $1 + $2 | 🤝 `x12` reg ➜ $1 | 🤝 `x14` reg ➜ $2 | 🤝 `x12` reg ➜ $3 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 12
        add     x12, x12, x14  # Addition Operation - $3 = $1 + $2
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $4 = i$2 + 1
        # 
# 🤙🏼 Calling getReg() for $4 = i$2 + 1
        #  🔵 Already in register - i$2 in 13
        #  🟢 Found Free Register - 15 for $4
        # 
# 👋 GetReg() for $4 = i$2 + 1 | 🤝 `x15` reg ➜ $4 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ i$2 |
        li      t1, 1          # Loading Immediate Value - 1 in x13
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 15
        add     x15, x13, t1   # Addition Operation - $4 = i$2 + 1
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$3 = $4
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -56(fp)   # Store Local Var - $1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw      x12, -64(fp)   # Store Local Var - $3 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        sw      x14, -60(fp)   # Store Local Var - $2 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x15, -68(fp)   # Store Local Var - $4 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$3 = $4
        #  🟢 Found Free Register - 12 for $4
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 12
        lw      x12, -68(fp)   # Load Local Var - $4 via fp in x12
        #  🟢 Found Free Register - 13 for $3
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        lw      x13, -64(fp)   # Load Local Var - $3 via fp in x13
        # 
# 👋 GetReg() for (4)*$3 = $4 | 🤝 `x13` reg ➜ $3 | 🤝 `x12` reg ➜ $4 |
        sw      x12, 0(x13)    # Store variable of reg x12 at address pointed by x13
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $5 = arr$1.offset
        # 
# 🤙🏼 Calling getReg() for $5 = arr$1.offset
        #  🟢 Found Free Register - 14 for $5
        # 
# 👋 GetReg() for $5 = arr$1.offset | 🤝 `x14` reg ➜ $5 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 14
        addi    x14, fp, -36   # Load address of variable (via fp) - arr$1 into x14
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $6 = i$2 << 2
        # 
# 🤙🏼 Calling getReg() for $6 = i$2 << 2
        #  🟢 Found Free Register - 15 for i$2
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$2 to register 15
        lw      x15, -48(fp)   # Load Local Var - i$2 via fp in x15
        #  🟢 Found Free Register - 16 for $6
        # 
# 👋 GetReg() for $6 = i$2 << 2 | 🤝 `x16` reg ➜ $6 | 🤝 `x0` reg ➜ NULL | 🤝 `x15` reg ➜ i$2 |
        li      t1, 2          # Loading Immediate Value - 2 in x15
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $6 to register 16
        sll     x16, x15, t1   # Left Shift Operation - $6 = i$2<< 2
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $7 = $5 + $6
        # 
# 🤙🏼 Calling getReg() for $7 = $5 + $6
        #  🔵 Already in register - $5 in 14
        #  🔵 Already in register - $6 in 16
        #  🍊 Giving $7 same reg as given to $5 since it not used again
        # 
# 👋 GetReg() for $7 = $5 + $6 | 🤝 `x14` reg ➜ $5 | 🤝 `x16` reg ➜ $6 | 🤝 `x14` reg ➜ $7 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $7 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 14
        add     x14, x14, x16  # Addition Operation - $7 = $5 + $6
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $8 = (4)*$7
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x14, -72(fp)   # Store Local Var - $5 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        sw      x14, -80(fp)   # Store Local Var - $7 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $7 in memory
        sw      x16, -76(fp)   # Store Local Var - $6 via fp in x16
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $8 = (4)*$7
        #  🟢 Found Free Register - 12 for $7
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 12
        lw      x12, -80(fp)   # Load Local Var - $7 via fp in x12
        #  🍊 Giving $8 same reg as given to $7 since it not used again
        # 
# 👋 GetReg() for $8 = (4)*$7 | 🤝 `x12` reg ➜ $7 | 🤝 `x12` reg ➜ $8 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $8 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $8 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $9 = sum$1 + $8
        # 
# 🤙🏼 Calling getReg() for $9 = sum$1 + $8
        #  🟢 Found Free Register - 13 for sum$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 sum$1 to register 13
        lw      x13, -44(fp)   # Load Local Var - sum$1 via fp in x13
        #  🔵 Already in register - $8 in 12
        #  🍊 Giving $9 same reg as given to sum$1 since it not used again
        # 
# 👋 GetReg() for $9 = sum$1 + $8 | 🤝 `x12` reg ➜ $8 | 🤝 `x13` reg ➜ $9 | 🤝 `x13` reg ➜ sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $9 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $9 to register 13
        add     x13, x13, x12  # Addition Operation - $9 = sum$1 + $8
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - sum$1 = $9
        # 
# 🤙🏼 Calling getReg() for sum$1 = $9
        #  🔵 Already in register - $9 in 13
        #  🍊 Giving sum$1 same reg as given to $9 due to ASSIGN-OP
        # 
# 👋 GetReg() for sum$1 = $9 | 🤝 `x13` reg ➜ $9 | 🤝 `x13` reg ➜ sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 sum$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 sum$1 to register 13
        #  🔄 Automatic copy - of $9 into (sum$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $10 = i$2
        # 🪦 Ignoring Assignment ☠️ dead variable $10
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - i$2 = i$2 + 1
        # 
# 🤙🏼 Calling getReg() for i$2 = i$2 + 1
        #  🟢 Found Free Register - 14 for i$2
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$2 to register 14
        lw      x14, -48(fp)   # Load Local Var - i$2 via fp in x14
        #  🔵 Already in (ex)register - i$2 in 14
        # 
# 👋 GetReg() for i$2 = i$2 + 1 | 🤝 `x14` reg ➜ i$2 |
        li      t1, 1          # Loading Immediate Value - 1 in x14
        # 💛 SYM_RECORD 💛 - Setting 🚫 i$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 i$2 to register 14
        add     x14, x14, t1   # Addition Operation - i$2 = i$2 + 1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        sw      x12, -84(fp)   # Store Local Var - $8 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $8 in memory
        sw      x13, -88(fp)   # Store Local Var - $9 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $9 in memory
        sw      x13, -44(fp)   # Store Local Var - sum$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 sum$1 in memory
        sw      x14, -48(fp)   # Store Local Var - i$2 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 i$2 in memory
        #  🫗 Finished Spilling Code 👌 
        j       Block_2        # Unconditional Jump to label - Block_2
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Param - param sum$1
        # Adding sum$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $11 = call printVar, 1
        lw      t2, -44(fp)    # Load Local Var - sum$1 via fp in t2
        mv      a0, t2         # Move argument - sum$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -96(fp)    # Store return value in caller's stack for - $11
        # 💛 SYM_RECORD 💛 - Setting 🚫 $11 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $11 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 92(sp)     # Restore return address (PC)
        lw      fp, 88(sp)     # Restore old frame pointer
        addi    sp, sp, 96     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


