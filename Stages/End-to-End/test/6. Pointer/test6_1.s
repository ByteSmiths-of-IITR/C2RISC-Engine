#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 04:09:22) 🎨 ---------

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
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - value$1 = 42
        # 
# 🤙🏼 Calling getReg() for value$1 = 42
        #  🟢 Found Free Register - 12 for value$1
        # 
# 👋 GetReg() for value$1 = 42 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ value$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 value$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 value$1 to register 12
        li      x12, 42        # Load constant - 42 into x12(value$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $0 = &value$1
        # 
# 🤙🏼 Calling getReg() for $0 = &value$1
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = &value$1 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        addi    x13, fp, -20   # Load address of variable (via fp) - value$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - ptr$1 = $0
        # 
# 🤙🏼 Calling getReg() for ptr$1 = $0
        #  🔵 Already in register - $0 in 13
        #  🍊 Giving ptr$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for ptr$1 = $0 | 🤝 `x13` reg ➜ $0 | 🤝 `x13` reg ➜ ptr$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 ptr$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 ptr$1 to register 13
        #  🔄 Automatic copy - of $0 into (ptr$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $1 = &ptr$1
        # 
# 🤙🏼 Calling getReg() for $1 = &ptr$1
        #  🟢 Found Free Register - 14 for $1
        # 
# 👋 GetReg() for $1 = &ptr$1 | 🤝 `x14` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 14
        addi    x14, fp, -24   # Load address of variable (via fp) - ptr$1 into x14
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - ptr2$1 = $1
        # 
# 🤙🏼 Calling getReg() for ptr2$1 = $1
        #  🔵 Already in register - $1 in 14
        #  🍊 Giving ptr2$1 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for ptr2$1 = $1 | 🤝 `x14` reg ➜ $1 | 🤝 `x14` reg ➜ ptr2$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 ptr2$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 ptr2$1 to register 14
        #  🔄 Automatic copy - of $1 into (ptr2$1)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        sw      x12, -20(fp)   # Store Local Var - value$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 value$1 in memory
        sw      x13, -28(fp)   # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x13, -24(fp)   # Store Local Var - ptr$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 ptr$1 in memory
        sw      x14, -36(fp)   # Store Local Var - $1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw      x14, -32(fp)   # Store Local Var - ptr2$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 ptr2$1 in memory
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


