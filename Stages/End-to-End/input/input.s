#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 02:37:15) 🎨 ---------

.data
        str_0:    .string "Hello World"

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
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Store return address (PC)
        sw    fp, 12(sp)       # Store old frame pointer
        addi  fp, sp,20        # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Param - param str_0
        # Adding str_0 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $0 = call printString, 1
        la    t0, str_0        # Loading Address of Global Variable - str_0
        lw    t2, 0(t0)        # Load Global Var - str_0 via t0 in xt2
        mv    a0, t2           # Move argument - str_0 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal   x1, printString  # Call function - printString
        sw    a0, -20(fp)      # Store return value in caller's stack for - $0
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li    t1, 0            # Load constant - 0 into t1
        mv    a1, t1           # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 16(sp)       # Restore return address (PC)
        lw    fp, 12(sp)       # Restore old frame pointer
        addi  sp, sp, 20       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


