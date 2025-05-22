#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:14:00) 🎨 ---------

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
        add:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block add
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - add
        addi    sp, sp, -28    # Allocating Stack Space
        sw      ra, 24(sp)     # Store return address (PC)
        sw      fp, 20(sp)     # Store old frame pointer
        addi    fp, sp,28      # Set new frame pointer
        sw      a0, -20(fp)    # Store argument 0 in stack
        sw      a1, -24(fp)    # Store argument 1 in stack
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a$1 + b$1
        # 
# 🤙🏼 Calling getReg() for $0 = a$1 + b$1
        #  🟢 Found Free Register - 12 for a$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - a$1 via fp in x12
        #  🟢 Found Free Register - 13 for b$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 13
        lw      x13, -24(fp)   # Load Local Var - b$1 via fp in x13
        #  🟢 Found Free Register - 14 for $0
        # 
# 👋 GetReg() for $0 = a$1 + b$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x12` reg ➜ a$1 | 🤝 `x13` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 14
        add     x14, x12, x13  # Addition Operation - $0 = a$1 + b$1
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $0
        # 
# 🤙🏼 Calling getReg() for return $0
        #  🔵 Already in register - $0 in 14
        # 
# 👋 GetReg() for return $0 | 🤝 `x14` reg ➜ $0 |
        mv      a1, x14        # Move return value's reg - x14 to a1
        #  -- EXIT Activation (start) - add
        #  🫟 Spilling Code 🫟  due to ➢ End of Function add
        sw      x14, -28(fp)   # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 24(sp)     # Restore return address (PC)
        lw      fp, 20(sp)     # Restore old frame pointer
        addi    sp, sp, 28     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - add
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -40    # Allocating Stack Space
        sw      ra, 36(sp)     # Store return address (PC)
        sw      fp, 32(sp)     # Store old frame pointer
        addi    fp, sp,40      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $1 = -5
        # 
# 🤙🏼 Calling getReg() for $1 = -5
        #  🟢 Found Free Register - 12 for $1
        # 
# 👋 GetReg() for $1 = -5 | 🤝 `x12` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        li      x12, -5        # Load constant - -5 into x12($1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$2 = $1
        # 
# 🤙🏼 Calling getReg() for a$2 = $1
        #  🔵 Already in register - $1 in 12
        #  🍊 Giving a$2 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for a$2 = $1 | 🤝 `x12` reg ➜ $1 | 🤝 `x12` reg ➜ a$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$2 to register 12
        #  🔄 Automatic copy - of $1 into (a$2)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$2 = 10
        # 
# 🤙🏼 Calling getReg() for b$2 = 10
        #  🟢 Found Free Register - 13 for b$2
        # 
# 👋 GetReg() for b$2 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ b$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$2 to register 13
        li      x13, 10        # Load constant - 10 into x13(b$2)
        # 
# ‼️ TAC ❗️ ➔ Param - param a$2
        # Adding a$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Param - param b$2
        # Adding b$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $2 = call add, 2
        mv      a0, x12        # Move argument - a$2 into a0
        mv      a1, x13        # Move argument - b$2 into a1
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -24(fp)   # Store Local Var - $1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw      x12, -20(fp)   # Store Local Var - a$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$2 in memory
        sw      x13, -28(fp)   # Store Local Var - b$2 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$2 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, add        # Call function - add
        sw      a0, -36(fp)    # Store return value in caller's stack for - $2
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - result$2 = $2
        # 
# 🤙🏼 Calling getReg() for result$2 = $2
        #  🟢 Found Free Register - 12 for $2
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        lw      x12, -36(fp)   # Load Local Var - $2 via fp in x12
        #  🍊 Giving result$2 same reg as given to $2 due to ASSIGN-OP
        # 
# 👋 GetReg() for result$2 = $2 | 🤝 `x12` reg ➜ $2 | 🤝 `x12` reg ➜ result$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 result$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 result$2 to register 12
        #  🔄 Automatic copy - of $2 into (result$2)
        # 
# ‼️ TAC ❗️ ➔ Param - param result$2
        # Adding result$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $3 = call printVar, 1
        mv      a0, x12        # Move argument - result$2 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -32(fp)   # Store Local Var - result$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 result$2 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -40(fp)    # Store return value in caller's stack for - $3
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 36(sp)     # Restore return address (PC)
        lw      fp, 32(sp)     # Restore old frame pointer
        addi    sp, sp, 40     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


