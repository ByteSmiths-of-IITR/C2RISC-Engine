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
        addi    sp, sp, -140   # Allocating Stack Space
        sw      ra, 136(sp)    # Store return address (PC)
        sw      fp, 132(sp)    # Store old frame pointer
        addi    fp, sp,140     # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - y$1 = 50
        # 
# 🤙🏼 Calling getReg() for y$1 = 50
        #  🟢 Found Free Register - 12 for y$1
        # 
# 👋 GetReg() for y$1 = 50 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ y$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 y$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 y$1 to register 12
        li      x12, 50        # Load constant - 50 into x12(y$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $0 = &y$1
        # 
# 🤙🏼 Calling getReg() for $0 = &y$1
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = &y$1 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        addi    x13, fp, -20   # Load address of variable (via fp) - y$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - p1$1 = $0
        # 
# 🤙🏼 Calling getReg() for p1$1 = $0
        #  🔵 Already in register - $0 in 13
        #  🍊 Giving p1$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for p1$1 = $0 | 🤝 `x13` reg ➜ $0 | 🤝 `x13` reg ➜ p1$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 p1$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 p1$1 to register 13
        #  🔄 Automatic copy - of $0 into (p1$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $1 = &p1$1
        # 
# 🤙🏼 Calling getReg() for $1 = &p1$1
        #  🟢 Found Free Register - 14 for $1
        # 
# 👋 GetReg() for $1 = &p1$1 | 🤝 `x14` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 14
        addi    x14, fp, -24   # Load address of variable (via fp) - p1$1 into x14
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - p2$1 = $1
        # 
# 🤙🏼 Calling getReg() for p2$1 = $1
        #  🔵 Already in register - $1 in 14
        #  🍊 Giving p2$1 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for p2$1 = $1 | 🤝 `x14` reg ➜ $1 | 🤝 `x14` reg ➜ p2$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 p2$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 p2$1 to register 14
        #  🔄 Automatic copy - of $1 into (p2$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $2 = &p2$1
        # 
# 🤙🏼 Calling getReg() for $2 = &p2$1
        #  🟢 Found Free Register - 15 for $2
        # 
# 👋 GetReg() for $2 = &p2$1 | 🤝 `x15` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 15
        addi    x15, fp, -32   # Load address of variable (via fp) - p2$1 into x15
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - p3$1 = $2
        # 
# 🤙🏼 Calling getReg() for p3$1 = $2
        #  🔵 Already in register - $2 in 15
        #  🍊 Giving p3$1 same reg as given to $2 due to ASSIGN-OP
        # 
# 👋 GetReg() for p3$1 = $2 | 🤝 `x15` reg ➜ $2 | 🤝 `x15` reg ➜ p3$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 p3$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 p3$1 to register 15
        #  🔄 Automatic copy - of $2 into (p3$1)
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $3 = (4)*p3$1
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -20(fp)   # Store Local Var - y$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 y$1 in memory
        sw      x13, -28(fp)   # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x13, -24(fp)   # Store Local Var - p1$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 p1$1 in memory
        sw      x14, -36(fp)   # Store Local Var - $1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw      x14, -32(fp)   # Store Local Var - p2$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 p2$1 in memory
        sw      x15, -44(fp)   # Store Local Var - $2 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x15, -40(fp)   # Store Local Var - p3$1 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 p3$1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $3 = (4)*p3$1
        #  🟢 Found Free Register - 12 for p3$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 p3$1 to register 12
        lw      x12, -40(fp)   # Load Local Var - p3$1 via fp in x12
        #  🟢 Found Free Register - 13 for $3
        # 
# 👋 GetReg() for $3 = (4)*p3$1 | 🤝 `x13` reg ➜ $3 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ p3$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        lw      x13, 0(x12)    # Load reg x13 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $4 = (4)*$3
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -52(fp)   # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $4 = (4)*$3
        #  🟢 Found Free Register - 12 for $3
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 12
        lw      x12, -52(fp)   # Load Local Var - $3 via fp in x12
        #  🍊 Giving $4 same reg as given to $3 since it not used again
        # 
# 👋 GetReg() for $4 = (4)*$3 | 🤝 `x12` reg ➜ $3 | 🤝 `x12` reg ➜ $4 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $5 = (4)*$4
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -56(fp)   # Store Local Var - $4 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $5 = (4)*$4
        #  🟢 Found Free Register - 12 for $4
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 12
        lw      x12, -56(fp)   # Load Local Var - $4 via fp in x12
        #  🍊 Giving $5 same reg as given to $4 since it not used again
        # 
# 👋 GetReg() for $5 = (4)*$4 | 🤝 `x12` reg ➜ $4 | 🤝 `x12` reg ➜ $5 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - val$1 = $5
        # 
# 🤙🏼 Calling getReg() for val$1 = $5
        #  🔵 Already in register - $5 in 12
        #  🍊 Giving val$1 same reg as given to $5 due to ASSIGN-OP
        # 
# 👋 GetReg() for val$1 = $5 | 🤝 `x12` reg ➜ $5 | 🤝 `x12` reg ➜ val$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 val$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 val$1 to register 12
        #  🔄 Automatic copy - of $5 into (val$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param val$1
        # Adding val$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $6 = call printVar, 1
        mv      a0, x12        # Move argument - val$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -60(fp)   # Store Local Var - $5 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        sw      x12, -48(fp)   # Store Local Var - val$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 val$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -64(fp)    # Store return value in caller's stack for - $6
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $7 = arr$1.offset
        # 
# 🤙🏼 Calling getReg() for $7 = arr$1.offset
        #  🟢 Found Free Register - 12 for $7
        # 
# 👋 GetReg() for $7 = arr$1.offset | 🤝 `x12` reg ➜ $7 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $7 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 12
        addi    x12, fp, -88   # Load address of variable (via fp) - arr$1 into x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $8 = 24
        # 
# 🤙🏼 Calling getReg() for $8 = 24
        #  🟢 Found Free Register - 13 for $8
        # 
# 👋 GetReg() for $8 = 24 | 🤝 `x13` reg ➜ $8 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $8 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $8 to register 13
        li      x13, 24        # Load constant - 24 into x13($8)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $9 = $7 + $8
        # 
# 🤙🏼 Calling getReg() for $9 = $7 + $8
        #  🔵 Already in register - $7 in 12
        #  🔵 Already in register - $8 in 13
        #  🍊 Giving $9 same reg as given to $7 since it not used again
        # 
# 👋 GetReg() for $9 = $7 + $8 | 🤝 `x12` reg ➜ $7 | 🤝 `x13` reg ➜ $8 | 🤝 `x12` reg ➜ $9 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $9 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $9 to register 12
        add     x12, x12, x13  # Addition Operation - $9 = $7 + $8
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $10 = 4
        # 
# 🤙🏼 Calling getReg() for $10 = 4
        #  🟢 Found Free Register - 14 for $10
        # 
# 👋 GetReg() for $10 = 4 | 🤝 `x14` reg ➜ $10 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $10 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $10 to register 14
        li      x14, 4         # Load constant - 4 into x14($10)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $11 = $9 + $10
        # 
# 🤙🏼 Calling getReg() for $11 = $9 + $10
        #  🔵 Already in register - $9 in 12
        #  🔵 Already in register - $10 in 14
        #  🍊 Giving $11 same reg as given to $10 since it not used again
        # 
# 👋 GetReg() for $11 = $9 + $10 | 🤝 `x14` reg ➜ $10 | 🤝 `x14` reg ➜ $11 | 🤝 `x12` reg ➜ $9 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $11 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $11 to register 14
        add     x14, x12, x14  # Addition Operation - $11 = $9 + $10
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$11 = 10
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -92(fp)   # Store Local Var - $7 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $7 in memory
        sw      x12, -100(fp)  # Store Local Var - $9 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $9 in memory
        sw      x13, -96(fp)   # Store Local Var - $8 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $8 in memory
        sw      x14, -104(fp)  # Store Local Var - $10 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $10 in memory
        sw      x14, -108(fp)  # Store Local Var - $11 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $11 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$11 = 10
        #  🟢 Found Free Register - 12 for $11
        # 💛 SYM_RECORD 💛 - Adding 🌕 $11 to register 12
        lw      x12, -108(fp)  # Load Local Var - $11 via fp in x12
        # 
# 👋 GetReg() for (4)*$11 = 10 | 🤝 `x12` reg ➜ $11 |
        li      t0, 10         # Load constant - 10 into t0
        sw      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $12 = arr$1.offset
        # 
# 🤙🏼 Calling getReg() for $12 = arr$1.offset
        #  🟢 Found Free Register - 13 for $12
        # 
# 👋 GetReg() for $12 = arr$1.offset | 🤝 `x13` reg ➜ $12 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $12 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $12 to register 13
        addi    x13, fp, -88   # Load address of variable (via fp) - arr$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $13 = 24
        # 
# 🤙🏼 Calling getReg() for $13 = 24
        #  🟢 Found Free Register - 14 for $13
        # 
# 👋 GetReg() for $13 = 24 | 🤝 `x14` reg ➜ $13 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $13 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $13 to register 14
        li      x14, 24        # Load constant - 24 into x14($13)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $14 = $12 + $13
        # 
# 🤙🏼 Calling getReg() for $14 = $12 + $13
        #  🔵 Already in register - $12 in 13
        #  🔵 Already in register - $13 in 14
        #  🍊 Giving $14 same reg as given to $12 since it not used again
        # 
# 👋 GetReg() for $14 = $12 + $13 | 🤝 `x13` reg ➜ $12 | 🤝 `x14` reg ➜ $13 | 🤝 `x13` reg ➜ $14 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $14 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $14 to register 13
        add     x13, x13, x14  # Addition Operation - $14 = $12 + $13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $15 = 4
        # 
# 🤙🏼 Calling getReg() for $15 = 4
        #  🟢 Found Free Register - 15 for $15
        # 
# 👋 GetReg() for $15 = 4 | 🤝 `x15` reg ➜ $15 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $15 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $15 to register 15
        li      x15, 4         # Load constant - 4 into x15($15)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $16 = $14 + $15
        # 
# 🤙🏼 Calling getReg() for $16 = $14 + $15
        #  🔵 Already in register - $14 in 13
        #  🔵 Already in register - $15 in 15
        #  🍊 Giving $16 same reg as given to $15 since it not used again
        # 
# 👋 GetReg() for $16 = $14 + $15 | 🤝 `x13` reg ➜ $14 | 🤝 `x15` reg ➜ $15 | 🤝 `x15` reg ➜ $16 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $16 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $16 to register 15
        add     x15, x13, x15  # Addition Operation - $16 = $14 + $15
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $17 = (4)*$16
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -116(fp)  # Store Local Var - $12 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $12 in memory
        sw      x13, -124(fp)  # Store Local Var - $14 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $14 in memory
        sw      x14, -120(fp)  # Store Local Var - $13 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $13 in memory
        sw      x15, -128(fp)  # Store Local Var - $15 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $15 in memory
        sw      x15, -132(fp)  # Store Local Var - $16 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 $16 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $17 = (4)*$16
        #  🟢 Found Free Register - 12 for $16
        # 💛 SYM_RECORD 💛 - Adding 🌕 $16 to register 12
        lw      x12, -132(fp)  # Load Local Var - $16 via fp in x12
        #  🍊 Giving $17 same reg as given to $16 since it not used again
        # 
# 👋 GetReg() for $17 = (4)*$16 | 🤝 `x12` reg ➜ $16 | 🤝 `x12` reg ➜ $17 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $17 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $17 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - k$1 = $17
        # 
# 🤙🏼 Calling getReg() for k$1 = $17
        #  🔵 Already in register - $17 in 12
        #  🍊 Giving k$1 same reg as given to $17 due to ASSIGN-OP
        # 
# 👋 GetReg() for k$1 = $17 | 🤝 `x12` reg ➜ $17 | 🤝 `x12` reg ➜ k$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 k$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 k$1 to register 12
        #  🔄 Automatic copy - of $17 into (k$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param k$1
        # Adding k$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $18 = call printVar, 1
        mv      a0, x12        # Move argument - k$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -136(fp)  # Store Local Var - $17 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $17 in memory
        sw      x12, -112(fp)  # Store Local Var - k$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 k$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -140(fp)   # Store return value in caller's stack for - $18
        # 💛 SYM_RECORD 💛 - Setting 🚫 $18 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $18 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv      a1, x0         # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 136(sp)    # Restore return address (PC)
        lw      fp, 132(sp)    # Restore old frame pointer
        addi    sp, sp, 140    # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


