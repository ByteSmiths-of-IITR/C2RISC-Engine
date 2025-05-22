#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-05-13 - 00:08:07) 🎨 ---------

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
        addi    sp, sp, -44    # Allocating Stack Space
        sw      ra, 40(sp)     # Store return address (PC)
        sw      fp, 36(sp)     # Store old frame pointer
        addi    fp, sp,44      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $0 = arr$1.offset
        # 
# 🤙🏼 Calling getReg() for $0 = arr$1.offset
        #  🟢 Found Free Register - 12 for $0
        # 
# 👋 GetReg() for $0 = arr$1.offset | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 12
        addi    x12, fp, -24   # Load address of variable (via fp) - arr$1 into x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $1 = 4
        # 🪦 Ignoring Assignment ☠️ dead variable $1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $2 = $0 + 4
        # 
# 🤙🏼 Calling getReg() for $2 = $0 + 4
        #  🔵 Already in register - $0 in 12
        #  🍊 Giving $2 same reg as given to $0 since it not used again
        # 
# 👋 GetReg() for $2 = $0 + 4 | 🤝 `x12` reg ➜ $0 | 🤝 `x12` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        li      t1, 4          # Loading Immediate Value - 4 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        add     x12, x12, t1   # Addition Operation - $2 = $0 + 4
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $3 = (4)*$2
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -32(fp)   # Store Local Var - $0 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x12, -40(fp)   # Store Local Var - $2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for $3 = (4)*$2
        #  🟢 Found Free Register - 12 for $2
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        lw      x12, -40(fp)   # Load Local Var - $2 via fp in x12
        #  🍊 Giving $3 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $3 = (4)*$2 | 🤝 `x12` reg ➜ $2 | 🤝 `x12` reg ➜ $3 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 12
        lw      x12, 0(x12)    # Load reg x12 with address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - k$1 = $3
        # 
# 🤙🏼 Calling getReg() for k$1 = $3
        #  🔵 Already in register - $3 in 12
        #  🍊 Giving k$1 same reg as given to $3 due to ASSIGN-OP
        # 
# 👋 GetReg() for k$1 = $3 | 🤝 `x12` reg ➜ $3 | 🤝 `x12` reg ➜ k$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 k$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 k$1 to register 12
        #  🔄 Automatic copy - of $3 into (k$1)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv      a1, x0         # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        sw      x12, -44(fp)   # Store Local Var - $3 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        sw      x12, -28(fp)   # Store Local Var - k$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 k$1 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 40(sp)     # Restore return address (PC)
        lw      fp, 36(sp)     # Restore old frame pointer
        addi    sp, sp, 44     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ At the end of Block
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


