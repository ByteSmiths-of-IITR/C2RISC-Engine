#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 02:14:59) 🎨 ---------

.data

.text
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
        lw    a0, -20(fp)      # Loading Address of String Variable
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
        addi  sp, sp, -24      # Allocating Stack Space
        sw    ra, 20(sp)       # Store return address (PC)
        sw    fp, 16(sp)       # Store old frame pointer
        addi  fp, sp,24        # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = 10
        # 
# 🤙🏼 Calling getReg() for a$1 = 10
        #  🟢 Found Free Register - 12 for a$1
        # 
# 👋 GetReg() for a$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        li    x12, 10          # Load constant - 10 into x12(a$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param a$1
        # Adding a$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $0 = call printVar, 1
        mv    a0, x12          # Move argument - a$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw    x12, -20(fp)     # Store Local Var - a$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal   x1, printVar     # Call function - printVar
        sw    a0, -24(fp)      # Store return value in caller's stack for - $0
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 20(sp)       # Restore return address (PC)
        lw    fp, 16(sp)       # Restore old frame pointer
        addi  sp, sp, 24       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


