#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:13:58) 🎨 ---------

.data
        fVar_0:     .float  30.000000
        fVar_1:     .float   5.000000

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
        addi    sp, sp, -132   # Allocating Stack Space
        sw      ra, 128(sp)    # Store return address (PC)
        sw      fp, 124(sp)    # Store old frame pointer
        addi    fp, sp,132     # Set new frame pointer
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
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - c$1 = 15
        # 
# 🤙🏼 Calling getReg() for c$1 = 15
        #  🟢 Found Free Register - 14 for c$1
        # 
# 👋 GetReg() for c$1 = 15 | 🤝 `x0` reg ➜ NULL | 🤝 `x14` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 c$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 14
        li      x14, 15        # Load constant - 15 into x14(c$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - d$1 = 20
        # 
# 🤙🏼 Calling getReg() for d$1 = 20
        #  🟢 Found Free Register - 15 for d$1
        # 
# 👋 GetReg() for d$1 = 20 | 🤝 `x0` reg ➜ NULL | 🤝 `x15` reg ➜ d$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 d$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 d$1 to register 15
        li      x15, 20        # Load constant - 20 into x15(d$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a$1 << 1
        # 
# 🤙🏼 Calling getReg() for $0 = a$1 << 1
        #  🔵 Already in register - a$1 in 12
        #  🟢 Found Free Register - 16 for $0
        # 
# 👋 GetReg() for $0 = a$1 << 1 | 🤝 `x16` reg ➜ $0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 16
        sll     x16, x12, t1   # Left Shift Operation - $0 = a$1<< 1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - x$1 = $0
        # 
# 🤙🏼 Calling getReg() for x$1 = $0
        #  🔵 Already in register - $0 in 16
        #  🍊 Giving x$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for x$1 = $0 | 🤝 `x16` reg ➜ $0 | 🤝 `x16` reg ➜ x$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 x$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 x$1 to register 16
        #  🔄 Automatic copy - of $0 into (x$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = a$1 + a$1
        # 
# 🤙🏼 Calling getReg() for $1 = a$1 + a$1
        #  🔵 Already in register - a$1 in 12
        #  🔵 Already in register - a$1 in 12
        #  🟢 Found Free Register - 17 for $1
        # 
# 👋 GetReg() for $1 = a$1 + a$1 | 🤝 `x17` reg ➜ $1 | 🤝 `x12` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 17
        add     x17, x12, x12  # Addition Operation - $1 = a$1 + a$1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - y$1 = $1
        # 
# 🤙🏼 Calling getReg() for y$1 = $1
        #  🔵 Already in register - $1 in 17
        #  🍊 Giving y$1 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for y$1 = $1 | 🤝 `x17` reg ➜ $1 | 🤝 `x17` reg ➜ y$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 y$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 y$1 to register 17
        #  🔄 Automatic copy - of $1 into (y$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $2 = 20
        # 
# 🤙🏼 Calling getReg() for $2 = 20
        #  🟢 Found Free Register - 18 for $2
        # 
# 👋 GetReg() for $2 = 20 | 🤝 `x18` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 18
        li      x18, 20        # Load constant - 20 into x18($2)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - z$1 = $2
        # 
# 🤙🏼 Calling getReg() for z$1 = $2
        #  🔵 Already in register - $2 in 18
        #  🍊 Giving z$1 same reg as given to $2 due to ASSIGN-OP
        # 
# 👋 GetReg() for z$1 = $2 | 🤝 `x18` reg ➜ $2 | 🤝 `x18` reg ➜ z$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 z$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 z$1 to register 18
        #  🔄 Automatic copy - of $2 into (z$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = fVar_0 / fVar_1
        # 
# 🤙🏼 Calling getReg() for $3 = fVar_0 / fVar_1
        #  🟢 Found Free Register - 40 for fVar_0
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_0 to register 40
        la      t0, fVar_0     # Loading Address of Global Variable - fVar_0
        flw     f8, 0(t0)      # Load Global Var - fVar_0 via t0 in xf8
        #  🟢 Found Free Register - 41 for fVar_1
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_1 to register 41
        la      t0, fVar_1     # Loading Address of Global Variable - fVar_1
        flw     f9, 0(t0)      # Load Global Var - fVar_1 via t0 in xf9
        #  🟢 Found Free Register - 42 for $3
        # 
# 👋 GetReg() for $3 = fVar_0 / fVar_1 | 🤝 `f10` reg ➜ $3 | 🤝 `f8` reg ➜ fVar_0 | 🤝 `f9` reg ➜ fVar_1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 42
        fdiv.s  f10, f8, f9    # F_Division Operation - $3 = fVar_0/fVar_1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - w$1 = $3
        # 
# 🤙🏼 Calling getReg() for w$1 = $3
        #  🔵 Already in register - $3 in 42
        #  🍊 Giving w$1 same reg as given to $3 due to ASSIGN-OP
        # 
# 👋 GetReg() for w$1 = $3 | 🤝 `f10` reg ➜ $3 | 🤝 `f10` reg ➜ w$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 w$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 w$1 to register 42
        #  🔄 Automatic copy - of $3 into (w$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $4 = d$1 << 3
        # 
# 🤙🏼 Calling getReg() for $4 = d$1 << 3
        #  🔵 Already in register - d$1 in 15
        #  🟢 Found Free Register - 19 for $4
        # 
# 👋 GetReg() for $4 = d$1 << 3 | 🤝 `x19` reg ➜ $4 | 🤝 `x0` reg ➜ NULL | 🤝 `x15` reg ➜ d$1 |
        li      t1, 3          # Loading Immediate Value - 3 in x15
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 19
        sll     x19, x15, t1   # Left Shift Operation - $4 = d$1<< 3
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - u$1 = $4
        # 
# 🤙🏼 Calling getReg() for u$1 = $4
        #  🔵 Already in register - $4 in 19
        #  🍊 Giving u$1 same reg as given to $4 due to ASSIGN-OP
        # 
# 👋 GetReg() for u$1 = $4 | 🤝 `x19` reg ➜ $4 | 🤝 `x19` reg ➜ u$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 u$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 u$1 to register 19
        #  🔄 Automatic copy - of $4 into (u$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - unused$1 = 100
        # 
# 🤙🏼 Calling getReg() for unused$1 = 100
        #  🟢 Found Free Register - 20 for unused$1
        # 
# 👋 GetReg() for unused$1 = 100 | 🤝 `x0` reg ➜ NULL | 🤝 `x20` reg ➜ unused$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 unused$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 unused$1 to register 20
        li      x20, 100       # Load constant - 100 into x20(unused$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - counter$1 = 0
        # 
# 🤙🏼 Calling getReg() for counter$1 = 0
        #  🟢 Found Free Register - 21 for counter$1
        # 
# 👋 GetReg() for counter$1 = 0 | 🤝 `x0` reg ➜ NULL | 🤝 `x21` reg ➜ counter$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 counter$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 counter$1 to register 21
        li      x21, 0         # Load constant - 0 into x21(counter$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $5 = counter$1 + 1
        # 
# 🤙🏼 Calling getReg() for $5 = counter$1 + 1
        #  🔵 Already in register - counter$1 in 21
        #  🍊 Giving $5 same reg as given to counter$1 since it not used again
        # 
# 👋 GetReg() for $5 = counter$1 + 1 | 🤝 `x21` reg ➜ $5 | 🤝 `x0` reg ➜ NULL | 🤝 `x21` reg ➜ counter$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x21
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 21
        add     x21, x21, t1   # Addition Operation - $5 = counter$1 + 1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - counter$1 = $5
        # 
# 🤙🏼 Calling getReg() for counter$1 = $5
        #  🔵 Already in register - $5 in 21
        #  🍊 Giving counter$1 same reg as given to $5 due to ASSIGN-OP
        # 
# 👋 GetReg() for counter$1 = $5 | 🤝 `x21` reg ➜ $5 | 🤝 `x21` reg ➜ counter$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 counter$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 counter$1 to register 21
        #  🔄 Automatic copy - of $5 into (counter$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $6 = counter$1 + 1
        # 
# 🤙🏼 Calling getReg() for $6 = counter$1 + 1
        #  🔵 Already in register - counter$1 in 21
        #  🟢 Found Free Register - 22 for $6
        # 
# 👋 GetReg() for $6 = counter$1 + 1 | 🤝 `x22` reg ➜ $6 | 🤝 `x0` reg ➜ NULL | 🤝 `x21` reg ➜ counter$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x21
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $6 to register 22
        add     x22, x21, t1   # Addition Operation - $6 = counter$1 + 1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - counter$1 = $6
        # 
# 🤙🏼 Calling getReg() for counter$1 = $6
        #  🔵 Already in register - $6 in 22
        #  🍊 Giving counter$1 same reg as given to $6 due to ASSIGN-OP
        # 
# 👋 GetReg() for counter$1 = $6 | 🤝 `x22` reg ➜ $6 | 🤝 `x22` reg ➜ counter$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 counter$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 counter$1 to register 22
        #  🔄 Automatic copy - of $6 into (counter$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $7 = counter$1 + 1
        # 
# 🤙🏼 Calling getReg() for $7 = counter$1 + 1
        #  🔵 Already in register - counter$1 in 22
        #  🟢 Found Free Register - 23 for $7
        # 
# 👋 GetReg() for $7 = counter$1 + 1 | 🤝 `x23` reg ➜ $7 | 🤝 `x0` reg ➜ NULL | 🤝 `x22` reg ➜ counter$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x22
        # 💛 SYM_RECORD 💛 - Setting 🚫 $7 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 23
        add     x23, x22, t1   # Addition Operation - $7 = counter$1 + 1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - counter$1 = $7
        # 
# 🤙🏼 Calling getReg() for counter$1 = $7
        #  🔵 Already in register - $7 in 23
        #  🍊 Giving counter$1 same reg as given to $7 due to ASSIGN-OP
        # 
# 👋 GetReg() for counter$1 = $7 | 🤝 `x23` reg ➜ $7 | 🤝 `x23` reg ➜ counter$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 counter$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 counter$1 to register 23
        #  🔄 Automatic copy - of $7 into (counter$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - temp$1 = b$1
        # 
# 🤙🏼 Calling getReg() for temp$1 = b$1
        #  🔵 Already in register - b$1 in 13
        #  🍊 Giving temp$1 same reg as given to b$1 due to ASSIGN-OP
        # 
# 👋 GetReg() for temp$1 = b$1 | 🤝 `x13` reg ➜ b$1 | 🤝 `x13` reg ➜ temp$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 temp$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 temp$1 to register 13
        #  🔄 Automatic copy - of b$1 into (temp$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - temp$1 = temp$1
        # 
# 🤙🏼 Calling getReg() for temp$1 = temp$1
        #  🔵 Already in register - temp$1 in 13
        #  🍊 Giving temp$1 same reg as given to temp$1 due to ASSIGN-OP
        # 
# 👋 GetReg() for temp$1 = temp$1 | 🤝 `x13` reg ➜ temp$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 temp$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 temp$1 to register 13
        #  🔄 Automatic copy - of temp$1 into (temp$1)
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if 1 goto L(Block_0)
        # 
# 🤙🏼 Calling getReg() for if 1 goto L(Block_0)
        # 
# 👋 GetReg() for if 1 goto L(Block_0) |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x12, -20(fp)   # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        sw      x13, -24(fp)   # Store Local Var - b$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        sw      x13, -96(fp)   # Store Local Var - temp$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 temp$1 in memory
        sw      x14, -28(fp)   # Store Local Var - c$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 c$1 in memory
        sw      x15, -32(fp)   # Store Local Var - d$1 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 d$1 in memory
        sw      x16, -40(fp)   # Store Local Var - $0 via fp in x16
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x16, -36(fp)   # Store Local Var - x$1 via fp in x16
        # 💛 SYM_RECORD 💛 - Setting 🟢 x$1 in memory
        sw      x17, -48(fp)   # Store Local Var - $1 via fp in x17
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw      x17, -44(fp)   # Store Local Var - y$1 via fp in x17
        # 💛 SYM_RECORD 💛 - Setting 🟢 y$1 in memory
        sw      x18, -56(fp)   # Store Local Var - $2 via fp in x18
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x18, -52(fp)   # Store Local Var - z$1 via fp in x18
        # 💛 SYM_RECORD 💛 - Setting 🟢 z$1 in memory
        sw      x19, -72(fp)   # Store Local Var - $4 via fp in x19
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        sw      x19, -68(fp)   # Store Local Var - u$1 via fp in x19
        # 💛 SYM_RECORD 💛 - Setting 🟢 u$1 in memory
        sw      x20, -76(fp)   # Store Local Var - unused$1 via fp in x20
        # 💛 SYM_RECORD 💛 - Setting 🟢 unused$1 in memory
        sw      x21, -84(fp)   # Store Local Var - $5 via fp in x21
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        sw      x22, -88(fp)   # Store Local Var - $6 via fp in x22
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        sw      x23, -92(fp)   # Store Local Var - $7 via fp in x23
        # 💛 SYM_RECORD 💛 - Setting 🟢 $7 in memory
        sw      x23, -80(fp)   # Store Local Var - counter$1 via fp in x23
        # 💛 SYM_RECORD 💛 - Setting 🟢 counter$1 in memory
        fsw     f10, -64(fp)   # Store Local Var - $3 via fp in f10
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        fsw     f10, -60(fp)   # Store Local Var - w$1 via fp in f10
        # 💛 SYM_RECORD 💛 - Setting 🟢 w$1 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x0, x0, Block_0 # Jump to label - Block_0 if 1 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_1)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_1        # Unconditional Jump to label - Block_1
        Block_0:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_0
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Param - param 1
        # Adding 1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $8 = call printVar, 1
        li      a0, 1          # Load argument - 1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -100(fp)   # Store return value in caller's stack for - $8
        # 💛 SYM_RECORD 💛 - Setting 🚫 $8 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $8 in memory
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_2        # Unconditional Jump to label - Block_2
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Param - param 2
        # Adding 2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $9 = call printVar, 1
        li      a0, 2          # Load argument - 2 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -104(fp)   # Store return value in caller's stack for - $9
        # 💛 SYM_RECORD 💛 - Setting 🚫 $9 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $9 in memory
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Param - param x$1
        # Adding x$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $10 = call printVar, 1
        lw      t2, -36(fp)    # Load Local Var - x$1 via fp in t2
        mv      a0, t2         # Move argument - x$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -108(fp)   # Store return value in caller's stack for - $10
        # 💛 SYM_RECORD 💛 - Setting 🚫 $10 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $10 in memory
        # 
# ‼️ TAC ❗️ ➔ Param - param y$1
        # Adding y$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $11 = call printVar, 1
        lw      t2, -44(fp)    # Load Local Var - y$1 via fp in t2
        mv      a0, t2         # Move argument - y$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -112(fp)   # Store return value in caller's stack for - $11
        # 💛 SYM_RECORD 💛 - Setting 🚫 $11 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $11 in memory
        # 
# ‼️ TAC ❗️ ➔ Param - param z$1
        # Adding z$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $12 = call printVar, 1
        lw      t2, -52(fp)    # Load Local Var - z$1 via fp in t2
        mv      a0, t2         # Move argument - z$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -116(fp)   # Store return value in caller's stack for - $12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $12 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $12 in memory
        # 
# ‼️ TAC ❗️ ➔ Cast - $13 = (int)w$1
        # 
# 🤙🏼 Calling getReg() for $13 = (int)w$1
        # 
# 👋 GetReg() for $13 = (int)w$1 |
        # 
# ‼️ TAC ❗️ ➔ Param - param $13
        # Adding $13 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $14 = call printVar, 1
        lw      t2, -120(fp)   # Load Local Var - $13 via fp in t2
        mv      a0, t2         # Move argument - $13 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -124(fp)   # Store return value in caller's stack for - $14
        # 💛 SYM_RECORD 💛 - Setting 🚫 $14 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $14 in memory
        # 
# ‼️ TAC ❗️ ➔ Param - param u$1
        # Adding u$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $15 = call printVar, 1
        lw      t2, -68(fp)    # Load Local Var - u$1 via fp in t2
        mv      a0, t2         # Move argument - u$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -128(fp)   # Store return value in caller's stack for - $15
        # 💛 SYM_RECORD 💛 - Setting 🚫 $15 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $15 in memory
        # 
# ‼️ TAC ❗️ ➔ Param - param counter$1
        # Adding counter$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $16 = call printVar, 1
        lw      t2, -80(fp)    # Load Local Var - counter$1 via fp in t2
        mv      a0, t2         # Move argument - counter$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -132(fp)   # Store return value in caller's stack for - $16
        # 💛 SYM_RECORD 💛 - Setting 🚫 $16 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $16 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 128(sp)    # Restore return address (PC)
        lw      fp, 124(sp)    # Restore old frame pointer
        addi    sp, sp, 132    # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


