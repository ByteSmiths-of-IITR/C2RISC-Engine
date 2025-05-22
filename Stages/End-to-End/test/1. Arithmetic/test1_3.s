#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:37:05) 🎨 ---------

.data
        fVar_0:     .float   3.200000

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
# ‼️ TAC ❗️ ➔ Cast - $0 = (float)5
        # 
# 🤙🏼 Calling getReg() for $0 = (float)5
        # 
# 👋 GetReg() for $0 = (float)5 |
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = $0
        # 
# 🤙🏼 Calling getReg() for a$1 = $0
        #  🟢 Found Free Register - 40 for $0
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 40
        flw     f8, -24(fp)    # Load Local Var - $0 via fp in f8
        #  🍊 Giving a$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for a$1 = $0 | 🤝 `f8` reg ➜ $0 | 🤝 `f8` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 40
        #  🔄 Automatic copy - of $0 into (a$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = fVar_0
        # 
# 🤙🏼 Calling getReg() for b$1 = fVar_0
        #  🟢 Found Free Register - 41 for fVar_0
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_0 to register 41
        la      t0, fVar_0     # Loading Address of Global Variable - fVar_0
        flw     f9, 0(t0)      # Load Global Var - fVar_0 via t0 in xf9
        #  🍊 Giving b$1 same reg as given to fVar_0 due to ASSIGN-OP
        # 
# 👋 GetReg() for b$1 = fVar_0 | 🤝 `f9` reg ➜ b$1 | 🤝 `f9` reg ➜ fVar_0 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 41
        #  🔄 Automatic copy - of fVar_0 into (b$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = a$1 + b$1
        # 
# 🤙🏼 Calling getReg() for $1 = a$1 + b$1
        #  🔵 Already in register - a$1 in 40
        #  🔵 Already in register - b$1 in 41
        #  🟢 Found Free Register - 42 for $1
        # 
# 👋 GetReg() for $1 = a$1 + b$1 | 🤝 `f10` reg ➜ $1 | 🤝 `f8` reg ➜ a$1 | 🤝 `f9` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 42
        fadd.s  f10, f8, f9    # F_Addition Operation - $1 = a$1 + b$1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - sum$1 = $1
        # 
# 🤙🏼 Calling getReg() for sum$1 = $1
        #  🔵 Already in register - $1 in 42
        #  🍊 Giving sum$1 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for sum$1 = $1 | 🤝 `f10` reg ➜ $1 | 🤝 `f10` reg ➜ sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 sum$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 sum$1 to register 42
        #  🔄 Automatic copy - of $1 into (sum$1)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        fsw     f8, -20(fp)    # Store Local Var - a$1 via fp in f8
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        fsw     f9, -28(fp)    # Store Local Var - b$1 via fp in f9
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        fsw     f10, -36(fp)   # Store Local Var - $1 via fp in f10
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        fsw     f10, -32(fp)   # Store Local Var - sum$1 via fp in f10
        # 💛 SYM_RECORD 💛 - Setting 🟢 sum$1 in memory
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


