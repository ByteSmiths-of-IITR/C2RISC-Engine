#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:13:58) 🎨 ---------

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
        func:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block func
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - func
        addi    sp, sp, -36    # Allocating Stack Space
        sw      ra, 32(sp)     # Store return address (PC)
        sw      fp, 28(sp)     # Store old frame pointer
        addi    fp, sp,36      # Set new frame pointer
        sw      a0, -20(fp)    # Store argument 0 in stack
        sw      a1, -24(fp)    # Store argument 1 in stack
        sw      a2, -28(fp)    # Store argument 2 in stack
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
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = $0 + c$1
        # 
# 🤙🏼 Calling getReg() for $1 = $0 + c$1
        #  🔵 Already in register - $0 in 14
        #  🟢 Found Free Register - 15 for c$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 15
        lw      x15, -28(fp)   # Load Local Var - c$1 via fp in x15
        #  🍊 Giving $1 same reg as given to $0 since it not used again
        # 
# 👋 GetReg() for $1 = $0 + c$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x14` reg ➜ $1 | 🤝 `x15` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 14
        add     x14, x14, x15  # Addition Operation - $1 = $0 + c$1
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $1
        # 
# 🤙🏼 Calling getReg() for return $1
        #  🔵 Already in register - $1 in 14
        # 
# 👋 GetReg() for return $1 | 🤝 `x14` reg ➜ $1 |
        mv      a1, x14        # Move return value's reg - x14 to a1
        #  -- EXIT Activation (start) - func
        #  🫟 Spilling Code 🫟  due to ➢ End of Function func
        sw      x14, -32(fp)   # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x14, -36(fp)   # Store Local Var - $1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 32(sp)     # Restore return address (PC)
        lw      fp, 28(sp)     # Restore old frame pointer
        addi    sp, sp, 36     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - func
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -28    # Allocating Stack Space
        sw      ra, 24(sp)     # Store return address (PC)
        sw      fp, 20(sp)     # Store old frame pointer
        addi    fp, sp,28      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Param - param 2
        # Adding 2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Param - param 3
        # Adding 3 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Param - param 5
        # Adding 5 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $2 = call func, 3
        li      a0, 2          # Load argument - 2 into a0
        li      a1, 3          # Load argument - 3 into a1
        li      a2, 5          # Load argument - 5 into a2
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, func       # Call function - func
        sw      a0, -24(fp)    # Store return value in caller's stack for - $2
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - ans$2 = $2
        # 
# 🤙🏼 Calling getReg() for ans$2 = $2
        #  🟢 Found Free Register - 12 for $2
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        lw      x12, -24(fp)   # Load Local Var - $2 via fp in x12
        #  🍊 Giving ans$2 same reg as given to $2 due to ASSIGN-OP
        # 
# 👋 GetReg() for ans$2 = $2 | 🤝 `x12` reg ➜ $2 | 🤝 `x12` reg ➜ ans$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 ans$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 ans$2 to register 12
        #  🔄 Automatic copy - of $2 into (ans$2)
        # 
# ‼️ TAC ❗️ ➔ Param - param ans$2
        # Adding ans$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $3 = call printVar, 1
        mv      a0, x12        # Move argument - ans$2 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -20(fp)   # Store Local Var - ans$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 ans$2 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -28(fp)    # Store return value in caller's stack for - $3
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv      a1, x0         # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 24(sp)     # Restore return address (PC)
        lw      fp, 20(sp)     # Restore old frame pointer
        addi    sp, sp, 28     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


