#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:14:01) 🎨 ---------

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
        addi    sp, sp, -76    # Allocating Stack Space
        sw      ra, 72(sp)     # Store return address (PC)
        sw      fp, 68(sp)     # Store old frame pointer
        addi    fp, sp,76      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $0 = p$1.offset
        # 
# 🤙🏼 Calling getReg() for $0 = p$1.offset
        #  🟢 Found Free Register - 12 for $0
        # 
# 👋 GetReg() for $0 = p$1.offset | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 12
        addi    x12, fp, -24   # Load address of variable (via fp) - p$1 into x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $1 = $0
        # 
# 🤙🏼 Calling getReg() for $1 = $0
        #  🔵 Already in register - $0 in 12
        #  🍊 Giving $1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for $1 = $0 | 🤝 `x12` reg ➜ $0 | 🤝 `x12` reg ➜ $1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        #  🔄 Automatic copy - of $0 into ($1)
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$1 = 18
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -28(fp)   # Store Local Var - $0 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x12, -32(fp)   # Store Local Var - $1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$1 = 18
        #  🟢 Found Free Register - 12 for $1
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        lw      x12, -32(fp)   # Load Local Var - $1 via fp in x12
        # 
# 👋 GetReg() for (4)*$1 = 18 | 🤝 `x12` reg ➜ $1 |
        li      t0, 18         # Load constant - 18 into t0
        sw      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $2 = p$1.offset
        # 
# 🤙🏼 Calling getReg() for $2 = p$1.offset
        #  🟢 Found Free Register - 13 for $2
        # 
# 👋 GetReg() for $2 = p$1.offset | 🤝 `x13` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 13
        addi    x13, fp, -24   # Load address of variable (via fp) - p$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = $2 + 4
        # 
# 🤙🏼 Calling getReg() for $3 = $2 + 4
        #  🔵 Already in register - $2 in 13
        #  🍊 Giving $3 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $3 = $2 + 4 | 🤝 `x13` reg ➜ $2 | 🤝 `x13` reg ➜ $3 | 🤝 `x0` reg ➜ NULL |
        li      t1, 4          # Loading Immediate Value - 4 in x13
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        add     x13, x13, t1   # Addition Operation - $3 = $2 + 4
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$3 = 4
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -36(fp)   # Store Local Var - $2 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x13, -40(fp)   # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$3 = 4
        #  🟢 Found Free Register - 12 for $3
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 12
        lw      x12, -40(fp)   # Load Local Var - $3 via fp in x12
        # 
# 👋 GetReg() for (4)*$3 = 4 | 🤝 `x12` reg ➜ $3 |
        li      t0, 4          # Load constant - 4 into t0
        sw      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $4 = p$1.offset
        # 
# 🤙🏼 Calling getReg() for $4 = p$1.offset
        #  🟢 Found Free Register - 13 for $4
        # 
# 👋 GetReg() for $4 = p$1.offset | 🤝 `x13` reg ➜ $4 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 13
        addi    x13, fp, -24   # Load address of variable (via fp) - p$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $5 = $4
        # 
# 🤙🏼 Calling getReg() for $5 = $4
        #  🔵 Already in register - $4 in 13
        #  🍊 Giving $5 same reg as given to $4 due to ASSIGN-OP
        # 
# 👋 GetReg() for $5 = $4 | 🤝 `x13` reg ➜ $4 | 🤝 `x13` reg ➜ $5 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 13
        #  🔄 Automatic copy - of $4 into ($5)
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $6 = p$1.offset
        # 
# 🤙🏼 Calling getReg() for $6 = p$1.offset
        #  🟢 Found Free Register - 14 for $6
        # 
# 👋 GetReg() for $6 = p$1.offset | 🤝 `x14` reg ➜ $6 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $6 to register 14
        addi    x14, fp, -24   # Load address of variable (via fp) - p$1 into x14
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $7 = $6 + 4
        # 
# 🤙🏼 Calling getReg() for $7 = $6 + 4
        #  🔵 Already in register - $6 in 14
        #  🍊 Giving $7 same reg as given to $6 since it not used again
        # 
# 👋 GetReg() for $7 = $6 + 4 | 🤝 `x14` reg ➜ $6 | 🤝 `x14` reg ➜ $7 | 🤝 `x0` reg ➜ NULL |
        li      t1, 4          # Loading Immediate Value - 4 in x14
        # 💛 SYM_RECORD 💛 - Setting 🚫 $7 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 14
        add     x14, x14, t1   # Addition Operation - $7 = $6 + 4
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $8 = (4)*$5
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -48(fp)   # Store Local Var - $4 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        sw      x13, -52(fp)   # Store Local Var - $5 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        sw      x14, -56(fp)   # Store Local Var - $6 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        sw      x14, -60(fp)   # Store Local Var - $7 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $7 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $8 = (4)*$5
        #  🟢 Found Free Register - 12 for $5
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 12
        lw      x12, -52(fp)   # Load Local Var - $5 via fp in x12
        #  🍊 Giving $8 same reg as given to $5 since it not used again
        # 
# 👋 GetReg() for $8 = (4)*$5 | 🤝 `x12` reg ➜ $5 | 🤝 `x12` reg ➜ $8 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $8 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $8 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $9 = (4)*$7
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -64(fp)   # Store Local Var - $8 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $8 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $9 = (4)*$7
        #  🟢 Found Free Register - 12 for $7
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 12
        lw      x12, -60(fp)   # Load Local Var - $7 via fp in x12
        #  🍊 Giving $9 same reg as given to $7 since it not used again
        # 
# 👋 GetReg() for $9 = (4)*$7 | 🤝 `x12` reg ➜ $7 | 🤝 `x12` reg ➜ $9 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $9 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $9 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $10 = $8 / $9
        # 
# 🤙🏼 Calling getReg() for $10 = $8 / $9
        #  🟢 Found Free Register - 13 for $8
        # 💛 SYM_RECORD 💛 - Adding 🌕 $8 to register 13
        lw      x13, -64(fp)   # Load Local Var - $8 via fp in x13
        #  🔵 Already in register - $9 in 12
        #  🍊 Giving $10 same reg as given to $8 since it not used again
        # 
# 👋 GetReg() for $10 = $8 / $9 | 🤝 `x13` reg ➜ $10 | 🤝 `x13` reg ➜ $8 | 🤝 `x12` reg ➜ $9 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $10 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $10 to register 13
        div     x13, x13, x12  # Division Operation - $10 = $8/$9
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - p_sum$1 = $10
        # 
# 🤙🏼 Calling getReg() for p_sum$1 = $10
        #  🔵 Already in register - $10 in 13
        #  🍊 Giving p_sum$1 same reg as given to $10 due to ASSIGN-OP
        # 
# 👋 GetReg() for p_sum$1 = $10 | 🤝 `x13` reg ➜ $10 | 🤝 `x13` reg ➜ p_sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 p_sum$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 p_sum$1 to register 13
        #  🔄 Automatic copy - of $10 into (p_sum$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param p_sum$1
        # Adding p_sum$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $11 = call printVar, 1
        mv      a0, x13        # Move argument - p_sum$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -68(fp)   # Store Local Var - $9 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $9 in memory
        sw      x13, -72(fp)   # Store Local Var - $10 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $10 in memory
        sw      x13, -44(fp)   # Store Local Var - p_sum$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 p_sum$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -76(fp)    # Store return value in caller's stack for - $11
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
        lw      ra, 72(sp)     # Restore return address (PC)
        lw      fp, 68(sp)     # Restore old frame pointer
        addi    sp, sp, 76     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


