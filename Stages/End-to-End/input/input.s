#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 02:54:45) 🎨 ---------

.data

.text
        # #define <stdio.h> INCLUDED
        #  ==== Adding Print and Scan Library ==== 
        printVar:              # Function Signature - void printVar(int var)
        # Function Entry - printVar
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Saving Return Address
        sw    fp, 12(sp)       # Saving Frame Pointer
        addi  fp, sp, -20      # Setting Frame Pointer
        li    a7, 1            # Loading Print System Call Code
        ecall                  # System Call for Print
        # Function Exit - printVar
        li    a0, 0            # Return value from printVar
        lw    ra, 16(sp)       # Restoring Return Address
        lw    fp, 12(sp)       # Restoring Frame Pointer
        addi  sp, sp, 20       # Deallocating Stack Space
        jr    ra               # Returning from printVar
        # End of Function - printVar
        printString:           # Function Signature - void printString(char *str)
        # Function Entry - printVar
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Saving Return Address
        sw    fp, 12(sp)       # Saving Frame Pointer
        addi  fp, sp, -20      # Setting Frame Pointer
        li    a7, 4            # Loading Print System Call Code
        ecall                  # System Call for Print
        # Function Exit - printString
        li    a0, 0            # Return value from printString
        lw    ra, 16(sp)       # Restoring Return Address
        lw    fp, 12(sp)       # Restoring Frame Pointer
        addi  sp, sp, 20       # Deallocating Stack Space
        jr    ra               # Returning from printString
        # End of Function - printString
        scanVar:               # Function Signature - int scanVar()
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Saving Return Address
        sw    fp, 12(sp)       # Saving Frame Pointer
        addi  fp, sp, -20      # Setting Frame Pointer
        li    a7, 5            # Loading Scan System Call Code
        ecall                  # System Call for Scan
        sw    a0, -20(fp)      # Storing Scan Result in Variable(Redundant)
        # Result already in a0 register
        lw    ra, 16(sp)       # Restoring Return Address
        lw    fp, 12(sp)       # Restoring Frame Pointer
        addi  sp, sp, 20       # Deallocating Stack Space
        jr    ra               # Returning from scanVar
        # End of Function - scanVar
        #  ==== End of Print and Scan Library ==== 
        #  
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi  sp, sp, -40      # Allocating Stack Space
        sw    ra, 36(sp)       # Store return address (PC)
        sw    fp, 32(sp)       # Store old frame pointer
        addi  fp, sp,40        # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = 7
        # 
# 🤙🏼 Calling getReg() for a$1 = 7
        #  🟢 Found Free Register - 12 for a$1
        # 
# 👋 GetReg() for a$1 = 7 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        li    x12, 7           # Load constant - 7 into x12(a$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $0 = &a$1
        # 
# 🤙🏼 Calling getReg() for $0 = &a$1
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = &a$1 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        addi  x13, fp, -20     # Load address of variable (via fp) - a$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - p$1 = $0
        # 
# 🤙🏼 Calling getReg() for p$1 = $0
        #  🔵 Already in register - $0 in 13
        #  🍊 Giving p$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for p$1 = $0 | 🤝 `x13` reg ➜ $0 | 🤝 `x13` reg ➜ p$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 p$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 p$1 to register 13
        #  🔄 Automatic copy - of $0 into (p$1)
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*p$1 = 10
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw    x12, -20(fp)     # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        sw    x13, -28(fp)     # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw    x13, -24(fp)     # Store Local Var - p$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 p$1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*p$1 = 10
        #  🟢 Found Free Register - 12 for p$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 p$1 to register 12
        lw    x12, -24(fp)     # Load Local Var - p$1 via fp in x12
        # 
# 👋 GetReg() for (4)*p$1 = 10 | 🤝 `x12` reg ➜ p$1 |
        li    t0, 10           # Load constant - 10 into t0
        sw    t0, 0(x12)       # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Param - param a$1
        # Adding a$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $1 = call printVar, 1
        lw    t2, -20(fp)      # Load Local Var - a$1 via fp in t2
        mv    a0, t2           # Move argument - a$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal   x1, printVar     # Call function - printVar
        sw    a0, -32(fp)      # Store return value in caller's stack for - $1
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = a$1
        # 
# 🤙🏼 Calling getReg() for b$1 = a$1
        #  🟢 Found Free Register - 12 for a$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        lw    x12, -20(fp)     # Load Local Var - a$1 via fp in x12
        #  🍊 Giving b$1 same reg as given to a$1 due to ASSIGN-OP
        # 
# 👋 GetReg() for b$1 = a$1 | 🤝 `x12` reg ➜ a$1 | 🤝 `x12` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 12
        #  🔄 Automatic copy - of a$1 into (b$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param b$1
        # Adding b$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $2 = call printVar, 1
        mv    a0, x12          # Move argument - b$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw    x12, -36(fp)     # Store Local Var - b$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal   x1, printVar     # Call function - printVar
        sw    a0, -40(fp)      # Store return value in caller's stack for - $2
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 36(sp)       # Restore return address (PC)
        lw    fp, 32(sp)       # Restore old frame pointer
        addi  sp, sp, 40       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


