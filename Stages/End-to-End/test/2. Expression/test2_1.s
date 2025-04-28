#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:55:34) 🎨 ---------

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
        addi    sp, sp, -60    # Allocating Stack Space
        sw      ra, 56(sp)     # Store return address (PC)
        sw      fp, 52(sp)     # Store old frame pointer
        addi    fp, sp,60      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = 5
        # 
# 🤙🏼 Calling getReg() for a$1 = 5
        #  🟢 Found Free Register - 12 for a$1
        # 
# 👋 GetReg() for a$1 = 5 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        li      x12, 5         # Load constant - 5 into x12(a$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = 10
        # 
# 🤙🏼 Calling getReg() for b$1 = 10
        #  🟢 Found Free Register - 13 for b$1
        # 
# 👋 GetReg() for b$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 13
        li      x13, 10        # Load constant - 10 into x13(b$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a$1 + b$1
        # 
# 🤙🏼 Calling getReg() for $0 = a$1 + b$1
        #  🔵 Already in register - a$1 in 12
        #  🔵 Already in register - b$1 in 13
        #  🟢 Found Free Register - 14 for $0
        # 
# 👋 GetReg() for $0 = a$1 + b$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x12` reg ➜ a$1 | 🤝 `x13` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 14
        add     x14, x12, x13  # Addition Operation - $0 = a$1 + b$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = $0 << 1
        # 
# 🤙🏼 Calling getReg() for $1 = $0 << 1
        #  🔵 Already in register - $0 in 14
        #  🍊 Giving $1 same reg as given to $0 since it not used again
        # 
# 👋 GetReg() for $1 = $0 << 1 | 🤝 `x14` reg ➜ $0 | 🤝 `x14` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        li      t1, 1          # Loading Immediate Value - 1 in x14
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 14
        sll     x14, x14, t1   # Left Shift Operation - $1 = $0<< 1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - c$1 = $1
        # 
# 🤙🏼 Calling getReg() for c$1 = $1
        #  🔵 Already in register - $1 in 14
        #  🍊 Giving c$1 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for c$1 = $1 | 🤝 `x14` reg ➜ $1 | 🤝 `x14` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 c$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 14
        #  🔄 Automatic copy - of $1 into (c$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $2 = a$1 << 1
        # 
# 🤙🏼 Calling getReg() for $2 = a$1 << 1
        #  🔵 Already in register - a$1 in 12
        #  🟢 Found Free Register - 15 for $2
        # 
# 👋 GetReg() for $2 = a$1 << 1 | 🤝 `x15` reg ➜ $2 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 15
        sll     x15, x12, t1   # Left Shift Operation - $2 = a$1<< 1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = b$1 >> 1
        # 
# 🤙🏼 Calling getReg() for $3 = b$1 >> 1
        #  🔵 Already in register - b$1 in 13
        #  🟢 Found Free Register - 16 for $3
        # 
# 👋 GetReg() for $3 = b$1 >> 1 | 🤝 `x16` reg ➜ $3 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ b$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x13
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 16
        srl     x16, x13, t1   # Right Shift Operation - $3 = b$1>> 1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $4 = $2 + $3
        # 
# 🤙🏼 Calling getReg() for $4 = $2 + $3
        #  🔵 Already in register - $2 in 15
        #  🔵 Already in register - $3 in 16
        #  🍊 Giving $4 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $4 = $2 + $3 | 🤝 `x15` reg ➜ $2 | 🤝 `x16` reg ➜ $3 | 🤝 `x15` reg ➜ $4 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 15
        add     x15, x15, x16  # Addition Operation - $4 = $2 + $3
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - d$1 = $4
        # 
# 🤙🏼 Calling getReg() for d$1 = $4
        #  🔵 Already in register - $4 in 15
        #  🍊 Giving d$1 same reg as given to $4 due to ASSIGN-OP
        # 
# 👋 GetReg() for d$1 = $4 | 🤝 `x15` reg ➜ $4 | 🤝 `x15` reg ➜ d$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 d$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 d$1 to register 15
        #  🔄 Automatic copy - of $4 into (d$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param c$1
        # Adding c$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $5 = call printVar, 1
        mv      a0, x14        # Move argument - c$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -20(fp)   # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        sw      x13, -24(fp)   # Store Local Var - b$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        sw      x14, -32(fp)   # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x14, -36(fp)   # Store Local Var - $1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw      x14, -28(fp)   # Store Local Var - c$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 c$1 in memory
        sw      x15, -44(fp)   # Store Local Var - $2 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x15, -52(fp)   # Store Local Var - $4 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        sw      x15, -40(fp)   # Store Local Var - d$1 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 d$1 in memory
        sw      x16, -48(fp)   # Store Local Var - $3 via fp in x16
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -56(fp)    # Store return value in caller's stack for - $5
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        # 
# ‼️ TAC ❗️ ➔ Param - param d$1
        # Adding d$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $6 = call printVar, 1
        lw      t2, -40(fp)    # Load Local Var - d$1 via fp in t2
        mv      a0, t2         # Move argument - d$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -60(fp)    # Store return value in caller's stack for - $6
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 56(sp)     # Restore return address (PC)
        lw      fp, 52(sp)     # Restore old frame pointer
        addi    sp, sp, 60     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


