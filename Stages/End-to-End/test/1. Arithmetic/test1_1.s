#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:37:05) 🎨 ---------

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
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = 3
        # 
# 🤙🏼 Calling getReg() for b$1 = 3
        #  🟢 Found Free Register - 13 for b$1
        # 
# 👋 GetReg() for b$1 = 3 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 13
        li      x13, 3         # Load constant - 3 into x13(b$1)
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
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - sum$1 = $0
        # 
# 🤙🏼 Calling getReg() for sum$1 = $0
        #  🔵 Already in register - $0 in 14
        #  🍊 Giving sum$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for sum$1 = $0 | 🤝 `x14` reg ➜ $0 | 🤝 `x14` reg ➜ sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 sum$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 sum$1 to register 14
        #  🔄 Automatic copy - of $0 into (sum$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param sum$1
        # Adding sum$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $1 = call printVar, 1
        mv      a0, x14        # Move argument - sum$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -20(fp)   # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        sw      x13, -24(fp)   # Store Local Var - b$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        sw      x14, -32(fp)   # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x14, -28(fp)   # Store Local Var - sum$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 sum$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -36(fp)    # Store return value in caller's stack for - $1
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
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


