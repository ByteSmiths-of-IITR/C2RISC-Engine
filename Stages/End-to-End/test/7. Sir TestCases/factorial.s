#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:13:59) 🎨 ---------

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
        factorial:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block factorial
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - factorial
        addi    sp, sp, -36    # Allocating Stack Space
        sw      ra, 32(sp)     # Store return address (PC)
        sw      fp, 28(sp)     # Store old frame pointer
        addi    fp, sp,36      # Set new frame pointer
        sw      a0, -20(fp)    # Store argument 0 in stack
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = n$1 <= 0
        # 
# 🤙🏼 Calling getReg() for $0 = n$1 <= 0
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = n$1 <= 0 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li      t1, 0          # Loading Immediate Value - 0 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        slt     t1, t1, x12    # Part1 of Less Than Equal Operation - $0 = n$1 <= 0
        xori    x13, t1, 1     # Part2 of Less Than Equal Operation - $0 = n$1 <= 0
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
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_2        # Unconditional Jump to label - Block_2
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = n$1 - 1
        # 
# 🤙🏼 Calling getReg() for $1 = n$1 - 1
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $1
        # 
# 👋 GetReg() for $1 = n$1 - 1 | 🤝 `x13` reg ➜ $1 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 13
        sub     x13, x12, t1   # Subtraction Operation - $1 = n$1 - 1
        # 
# ‼️ TAC ❗️ ➔ Param - param $1
        # Adding $1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $2 = call factorial, 1
        mv      a0, x13        # Move argument - $1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x13, -28(fp)   # Store Local Var - $1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, factorial  # Call function - factorial
        sw      a0, -32(fp)    # Store return value in caller's stack for - $2
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = n$1 * $2
        # 
# 🤙🏼 Calling getReg() for $3 = n$1 * $2
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $2
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 13
        lw      x13, -32(fp)   # Load Local Var - $2 via fp in x13
        #  🍊 Giving $3 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $3 = n$1 * $2 | 🤝 `x13` reg ➜ $2 | 🤝 `x13` reg ➜ $3 | 🤝 `x12` reg ➜ n$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        mul     x13, x12, x13  # Multiplication Operation - $3 = n$1 * $2
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $3
        # 
# 🤙🏼 Calling getReg() for return $3
        #  🔵 Already in register - $3 in 13
        # 
# 👋 GetReg() for return $3 | 🤝 `x13` reg ➜ $3 |
        mv      a1, x13        # Move return value's reg - x13 to a1
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        sw      x13, -36(fp)   # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        #  -- EXIT Activation (start) - factorial
        #  🫟 Spilling Code 🫟  due to ➢ End of Function factorial
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 32(sp)     # Restore return address (PC)
        lw      fp, 28(sp)     # Restore old frame pointer
        addi    sp, sp, 36     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - factorial
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -32    # Allocating Stack Space
        sw      ra, 28(sp)     # Store return address (PC)
        sw      fp, 24(sp)     # Store old frame pointer
        addi    fp, sp,32      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$2 = 5
        # 
# 🤙🏼 Calling getReg() for a$2 = 5
        #  🟢 Found Free Register - 12 for a$2
        # 
# 👋 GetReg() for a$2 = 5 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$2 to register 12
        li      x12, 5         # Load constant - 5 into x12(a$2)
        # 
# ‼️ TAC ❗️ ➔ Param - param a$2
        # Adding a$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $4 = call factorial, 1
        mv      a0, x12        # Move argument - a$2 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -20(fp)   # Store Local Var - a$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$2 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, factorial  # Call function - factorial
        sw      a0, -28(fp)    # Store return value in caller's stack for - $4
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - result$2 = $4
        # 
# 🤙🏼 Calling getReg() for result$2 = $4
        #  🟢 Found Free Register - 12 for $4
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 12
        lw      x12, -28(fp)   # Load Local Var - $4 via fp in x12
        #  🍊 Giving result$2 same reg as given to $4 due to ASSIGN-OP
        # 
# 👋 GetReg() for result$2 = $4 | 🤝 `x12` reg ➜ $4 | 🤝 `x12` reg ➜ result$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 result$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 result$2 to register 12
        #  🔄 Automatic copy - of $4 into (result$2)
        # 
# ‼️ TAC ❗️ ➔ Param - param result$2
        # Adding result$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $5 = call printVar, 1
        mv      a0, x12        # Move argument - result$2 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -24(fp)   # Store Local Var - result$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 result$2 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -32(fp)    # Store return value in caller's stack for - $5
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 28(sp)     # Restore return address (PC)
        lw      fp, 24(sp)     # Restore old frame pointer
        addi    sp, sp, 32     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


