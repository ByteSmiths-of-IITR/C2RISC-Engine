#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 11:13:59) 🎨 ---------

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
        addi    sp, sp, -820   # Allocating Stack Space
        sw      ra, 816(sp)    # Store return address (PC)
        sw      fp, 812(sp)    # Store old frame pointer
        addi    fp, sp,820     # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a1$1 = 10
        # 
# 🤙🏼 Calling getReg() for a1$1 = 10
        #  🟢 Found Free Register - 12 for a1$1
        # 
# 👋 GetReg() for a1$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a1$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a1$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a1$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a1$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a2$1 = 10
        # 
# 🤙🏼 Calling getReg() for a2$1 = 10
        #  🟢 Found Free Register - 13 for a2$1
        # 
# 👋 GetReg() for a2$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ a2$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a2$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a2$1 to register 13
        li      x13, 10        # Load constant - 10 into x13(a2$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a3$1 = 10
        # 
# 🤙🏼 Calling getReg() for a3$1 = 10
        #  🟢 Found Free Register - 14 for a3$1
        # 
# 👋 GetReg() for a3$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x14` reg ➜ a3$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a3$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a3$1 to register 14
        li      x14, 10        # Load constant - 10 into x14(a3$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a4$1 = 10
        # 
# 🤙🏼 Calling getReg() for a4$1 = 10
        #  🟢 Found Free Register - 15 for a4$1
        # 
# 👋 GetReg() for a4$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x15` reg ➜ a4$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a4$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a4$1 to register 15
        li      x15, 10        # Load constant - 10 into x15(a4$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a5$1 = 10
        # 
# 🤙🏼 Calling getReg() for a5$1 = 10
        #  🟢 Found Free Register - 16 for a5$1
        # 
# 👋 GetReg() for a5$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x16` reg ➜ a5$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a5$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a5$1 to register 16
        li      x16, 10        # Load constant - 10 into x16(a5$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a6$1 = 10
        # 
# 🤙🏼 Calling getReg() for a6$1 = 10
        #  🟢 Found Free Register - 17 for a6$1
        # 
# 👋 GetReg() for a6$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x17` reg ➜ a6$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a6$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a6$1 to register 17
        li      x17, 10        # Load constant - 10 into x17(a6$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a7$1 = 10
        # 
# 🤙🏼 Calling getReg() for a7$1 = 10
        #  🟢 Found Free Register - 18 for a7$1
        # 
# 👋 GetReg() for a7$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x18` reg ➜ a7$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a7$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a7$1 to register 18
        li      x18, 10        # Load constant - 10 into x18(a7$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a8$1 = 10
        # 
# 🤙🏼 Calling getReg() for a8$1 = 10
        #  🟢 Found Free Register - 19 for a8$1
        # 
# 👋 GetReg() for a8$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x19` reg ➜ a8$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a8$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a8$1 to register 19
        li      x19, 10        # Load constant - 10 into x19(a8$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a9$1 = 10
        # 
# 🤙🏼 Calling getReg() for a9$1 = 10
        #  🟢 Found Free Register - 20 for a9$1
        # 
# 👋 GetReg() for a9$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x20` reg ➜ a9$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a9$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a9$1 to register 20
        li      x20, 10        # Load constant - 10 into x20(a9$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a10$1 = 10
        # 
# 🤙🏼 Calling getReg() for a10$1 = 10
        #  🟢 Found Free Register - 21 for a10$1
        # 
# 👋 GetReg() for a10$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x21` reg ➜ a10$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a10$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a10$1 to register 21
        li      x21, 10        # Load constant - 10 into x21(a10$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a11$1 = 10
        # 
# 🤙🏼 Calling getReg() for a11$1 = 10
        #  🟢 Found Free Register - 22 for a11$1
        # 
# 👋 GetReg() for a11$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x22` reg ➜ a11$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a11$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a11$1 to register 22
        li      x22, 10        # Load constant - 10 into x22(a11$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a12$1 = 10
        # 
# 🤙🏼 Calling getReg() for a12$1 = 10
        #  🟢 Found Free Register - 23 for a12$1
        # 
# 👋 GetReg() for a12$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x23` reg ➜ a12$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a12$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a12$1 to register 23
        li      x23, 10        # Load constant - 10 into x23(a12$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a13$1 = 10
        # 
# 🤙🏼 Calling getReg() for a13$1 = 10
        #  🟢 Found Free Register - 24 for a13$1
        # 
# 👋 GetReg() for a13$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x24` reg ➜ a13$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a13$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a13$1 to register 24
        li      x24, 10        # Load constant - 10 into x24(a13$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a14$1 = 10
        # 
# 🤙🏼 Calling getReg() for a14$1 = 10
        #  🟢 Found Free Register - 25 for a14$1
        # 
# 👋 GetReg() for a14$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x25` reg ➜ a14$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a14$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a14$1 to register 25
        li      x25, 10        # Load constant - 10 into x25(a14$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a15$1 = 10
        # 
# 🤙🏼 Calling getReg() for a15$1 = 10
        #  🟢 Found Free Register - 26 for a15$1
        # 
# 👋 GetReg() for a15$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x26` reg ➜ a15$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a15$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a15$1 to register 26
        li      x26, 10        # Load constant - 10 into x26(a15$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a16$1 = 10
        # 
# 🤙🏼 Calling getReg() for a16$1 = 10
        #  🟢 Found Free Register - 27 for a16$1
        # 
# 👋 GetReg() for a16$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x27` reg ➜ a16$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a16$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a16$1 to register 27
        li      x27, 10        # Load constant - 10 into x27(a16$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a17$1 = 10
        # 
# 🤙🏼 Calling getReg() for a17$1 = 10
        #  🟢 Found Free Register - 28 for a17$1
        # 
# 👋 GetReg() for a17$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x28` reg ➜ a17$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a17$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a17$1 to register 28
        li      x28, 10        # Load constant - 10 into x28(a17$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a18$1 = 10
        # 
# 🤙🏼 Calling getReg() for a18$1 = 10
        #  🟢 Found Free Register - 29 for a18$1
        # 
# 👋 GetReg() for a18$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x29` reg ➜ a18$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a18$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a18$1 to register 29
        li      x29, 10        # Load constant - 10 into x29(a18$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a19$1 = 10
        # 
# 🤙🏼 Calling getReg() for a19$1 = 10
        #  🟢 Found Free Register - 30 for a19$1
        # 
# 👋 GetReg() for a19$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x30` reg ➜ a19$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a19$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a19$1 to register 30
        li      x30, 10        # Load constant - 10 into x30(a19$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a20$1 = 10
        # 
# 🤙🏼 Calling getReg() for a20$1 = 10
        #  🟢 Found Free Register - 31 for a20$1
        # 
# 👋 GetReg() for a20$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x31` reg ➜ a20$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a20$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a20$1 to register 31
        li      x31, 10        # Load constant - 10 into x31(a20$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a21$1 = 10
        # 
# 🤙🏼 Calling getReg() for a21$1 = 10
        sw      x12, -20(fp)   # Store Local Var - a1$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a1$1 in memory
        # 
# 👋 GetReg() for a21$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a21$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a21$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a21$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a21$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a22$1 = 10
        # 
# 🤙🏼 Calling getReg() for a22$1 = 10
        sw      x12, -100(fp)  # Store Local Var - a21$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a21$1 in memory
        # 
# 👋 GetReg() for a22$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a22$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a22$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a22$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a22$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a23$1 = 10
        # 
# 🤙🏼 Calling getReg() for a23$1 = 10
        sw      x12, -104(fp)  # Store Local Var - a22$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a22$1 in memory
        # 
# 👋 GetReg() for a23$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a23$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a23$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a23$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a23$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a24$1 = 10
        # 
# 🤙🏼 Calling getReg() for a24$1 = 10
        sw      x12, -108(fp)  # Store Local Var - a23$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a23$1 in memory
        # 
# 👋 GetReg() for a24$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a24$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a24$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a24$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a24$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a25$1 = 10
        # 
# 🤙🏼 Calling getReg() for a25$1 = 10
        sw      x12, -112(fp)  # Store Local Var - a24$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a24$1 in memory
        # 
# 👋 GetReg() for a25$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a25$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a25$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a25$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a25$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a26$1 = 10
        # 
# 🤙🏼 Calling getReg() for a26$1 = 10
        sw      x12, -116(fp)  # Store Local Var - a25$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a25$1 in memory
        # 
# 👋 GetReg() for a26$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a26$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a26$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a26$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a26$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a27$1 = 10
        # 
# 🤙🏼 Calling getReg() for a27$1 = 10
        sw      x12, -120(fp)  # Store Local Var - a26$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a26$1 in memory
        # 
# 👋 GetReg() for a27$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a27$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a27$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a27$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a27$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a28$1 = 10
        # 
# 🤙🏼 Calling getReg() for a28$1 = 10
        sw      x12, -124(fp)  # Store Local Var - a27$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a27$1 in memory
        # 
# 👋 GetReg() for a28$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a28$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a28$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a28$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a28$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a29$1 = 10
        # 
# 🤙🏼 Calling getReg() for a29$1 = 10
        sw      x12, -128(fp)  # Store Local Var - a28$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a28$1 in memory
        # 
# 👋 GetReg() for a29$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a29$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a29$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a29$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a29$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a30$1 = 10
        # 
# 🤙🏼 Calling getReg() for a30$1 = 10
        sw      x12, -132(fp)  # Store Local Var - a29$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a29$1 in memory
        # 
# 👋 GetReg() for a30$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a30$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a30$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a30$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a30$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a31$1 = 10
        # 
# 🤙🏼 Calling getReg() for a31$1 = 10
        sw      x12, -136(fp)  # Store Local Var - a30$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a30$1 in memory
        # 
# 👋 GetReg() for a31$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a31$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a31$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a31$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a31$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a32$1 = 10
        # 
# 🤙🏼 Calling getReg() for a32$1 = 10
        sw      x12, -140(fp)  # Store Local Var - a31$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a31$1 in memory
        # 
# 👋 GetReg() for a32$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a32$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a32$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a32$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a32$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a33$1 = 10
        # 
# 🤙🏼 Calling getReg() for a33$1 = 10
        sw      x12, -144(fp)  # Store Local Var - a32$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a32$1 in memory
        # 
# 👋 GetReg() for a33$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a33$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a33$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a33$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a33$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a34$1 = 10
        # 
# 🤙🏼 Calling getReg() for a34$1 = 10
        sw      x12, -148(fp)  # Store Local Var - a33$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a33$1 in memory
        # 
# 👋 GetReg() for a34$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a34$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a34$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a34$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a34$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a35$1 = 10
        # 
# 🤙🏼 Calling getReg() for a35$1 = 10
        sw      x12, -152(fp)  # Store Local Var - a34$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a34$1 in memory
        # 
# 👋 GetReg() for a35$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a35$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a35$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a35$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a35$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a36$1 = 10
        # 
# 🤙🏼 Calling getReg() for a36$1 = 10
        sw      x12, -156(fp)  # Store Local Var - a35$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a35$1 in memory
        # 
# 👋 GetReg() for a36$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a36$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a36$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a36$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a36$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a37$1 = 10
        # 
# 🤙🏼 Calling getReg() for a37$1 = 10
        sw      x12, -160(fp)  # Store Local Var - a36$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a36$1 in memory
        # 
# 👋 GetReg() for a37$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a37$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a37$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a37$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a37$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a38$1 = 10
        # 
# 🤙🏼 Calling getReg() for a38$1 = 10
        sw      x12, -164(fp)  # Store Local Var - a37$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a37$1 in memory
        # 
# 👋 GetReg() for a38$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a38$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a38$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a38$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a38$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a39$1 = 10
        # 
# 🤙🏼 Calling getReg() for a39$1 = 10
        sw      x12, -168(fp)  # Store Local Var - a38$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a38$1 in memory
        # 
# 👋 GetReg() for a39$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a39$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a39$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a39$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a39$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a40$1 = 10
        # 
# 🤙🏼 Calling getReg() for a40$1 = 10
        sw      x12, -172(fp)  # Store Local Var - a39$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a39$1 in memory
        # 
# 👋 GetReg() for a40$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a40$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a40$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a40$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a40$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a41$1 = 10
        # 
# 🤙🏼 Calling getReg() for a41$1 = 10
        sw      x12, -176(fp)  # Store Local Var - a40$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a40$1 in memory
        # 
# 👋 GetReg() for a41$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a41$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a41$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a41$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a41$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a42$1 = 10
        # 
# 🤙🏼 Calling getReg() for a42$1 = 10
        sw      x12, -180(fp)  # Store Local Var - a41$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a41$1 in memory
        # 
# 👋 GetReg() for a42$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a42$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a42$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a42$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a42$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a43$1 = 10
        # 
# 🤙🏼 Calling getReg() for a43$1 = 10
        sw      x12, -184(fp)  # Store Local Var - a42$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a42$1 in memory
        # 
# 👋 GetReg() for a43$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a43$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a43$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a43$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a43$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a44$1 = 10
        # 
# 🤙🏼 Calling getReg() for a44$1 = 10
        sw      x12, -188(fp)  # Store Local Var - a43$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a43$1 in memory
        # 
# 👋 GetReg() for a44$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a44$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a44$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a44$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a44$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a45$1 = 10
        # 
# 🤙🏼 Calling getReg() for a45$1 = 10
        sw      x12, -192(fp)  # Store Local Var - a44$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a44$1 in memory
        # 
# 👋 GetReg() for a45$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a45$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a45$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a45$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a45$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a46$1 = 10
        # 
# 🤙🏼 Calling getReg() for a46$1 = 10
        sw      x12, -196(fp)  # Store Local Var - a45$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a45$1 in memory
        # 
# 👋 GetReg() for a46$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a46$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a46$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a46$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a46$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a47$1 = 10
        # 
# 🤙🏼 Calling getReg() for a47$1 = 10
        sw      x12, -200(fp)  # Store Local Var - a46$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a46$1 in memory
        # 
# 👋 GetReg() for a47$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a47$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a47$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a47$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a47$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a48$1 = 10
        # 
# 🤙🏼 Calling getReg() for a48$1 = 10
        sw      x12, -204(fp)  # Store Local Var - a47$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a47$1 in memory
        # 
# 👋 GetReg() for a48$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a48$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a48$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a48$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a48$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a49$1 = 10
        # 
# 🤙🏼 Calling getReg() for a49$1 = 10
        sw      x12, -208(fp)  # Store Local Var - a48$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a48$1 in memory
        # 
# 👋 GetReg() for a49$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a49$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a49$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a49$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a49$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a50$1 = 10
        # 
# 🤙🏼 Calling getReg() for a50$1 = 10
        sw      x12, -212(fp)  # Store Local Var - a49$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a49$1 in memory
        # 
# 👋 GetReg() for a50$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a50$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a50$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a50$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a50$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a51$1 = 10
        # 
# 🤙🏼 Calling getReg() for a51$1 = 10
        sw      x12, -216(fp)  # Store Local Var - a50$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a50$1 in memory
        # 
# 👋 GetReg() for a51$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a51$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a51$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a51$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a51$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a52$1 = 10
        # 
# 🤙🏼 Calling getReg() for a52$1 = 10
        sw      x12, -220(fp)  # Store Local Var - a51$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a51$1 in memory
        # 
# 👋 GetReg() for a52$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a52$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a52$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a52$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a52$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a53$1 = 10
        # 
# 🤙🏼 Calling getReg() for a53$1 = 10
        sw      x12, -224(fp)  # Store Local Var - a52$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a52$1 in memory
        # 
# 👋 GetReg() for a53$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a53$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a53$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a53$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a53$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a54$1 = 10
        # 
# 🤙🏼 Calling getReg() for a54$1 = 10
        sw      x12, -228(fp)  # Store Local Var - a53$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a53$1 in memory
        # 
# 👋 GetReg() for a54$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a54$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a54$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a54$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a54$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a55$1 = 10
        # 
# 🤙🏼 Calling getReg() for a55$1 = 10
        sw      x12, -232(fp)  # Store Local Var - a54$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a54$1 in memory
        # 
# 👋 GetReg() for a55$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a55$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a55$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a55$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a55$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a56$1 = 10
        # 
# 🤙🏼 Calling getReg() for a56$1 = 10
        sw      x12, -236(fp)  # Store Local Var - a55$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a55$1 in memory
        # 
# 👋 GetReg() for a56$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a56$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a56$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a56$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a56$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a57$1 = 10
        # 
# 🤙🏼 Calling getReg() for a57$1 = 10
        sw      x12, -240(fp)  # Store Local Var - a56$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a56$1 in memory
        # 
# 👋 GetReg() for a57$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a57$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a57$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a57$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a57$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a58$1 = 10
        # 
# 🤙🏼 Calling getReg() for a58$1 = 10
        sw      x12, -244(fp)  # Store Local Var - a57$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a57$1 in memory
        # 
# 👋 GetReg() for a58$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a58$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a58$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a58$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a58$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a59$1 = 10
        # 
# 🤙🏼 Calling getReg() for a59$1 = 10
        sw      x12, -248(fp)  # Store Local Var - a58$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a58$1 in memory
        # 
# 👋 GetReg() for a59$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a59$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a59$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a59$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a59$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a60$1 = 10
        # 
# 🤙🏼 Calling getReg() for a60$1 = 10
        sw      x12, -252(fp)  # Store Local Var - a59$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a59$1 in memory
        # 
# 👋 GetReg() for a60$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a60$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a60$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a60$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a60$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a61$1 = 10
        # 
# 🤙🏼 Calling getReg() for a61$1 = 10
        sw      x12, -256(fp)  # Store Local Var - a60$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a60$1 in memory
        # 
# 👋 GetReg() for a61$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a61$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a61$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a61$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a61$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a62$1 = 10
        # 
# 🤙🏼 Calling getReg() for a62$1 = 10
        sw      x12, -260(fp)  # Store Local Var - a61$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a61$1 in memory
        # 
# 👋 GetReg() for a62$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a62$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a62$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a62$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a62$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a63$1 = 10
        # 
# 🤙🏼 Calling getReg() for a63$1 = 10
        sw      x12, -264(fp)  # Store Local Var - a62$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a62$1 in memory
        # 
# 👋 GetReg() for a63$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a63$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a63$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a63$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a63$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a64$1 = 10
        # 
# 🤙🏼 Calling getReg() for a64$1 = 10
        sw      x12, -268(fp)  # Store Local Var - a63$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a63$1 in memory
        # 
# 👋 GetReg() for a64$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a64$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a64$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a64$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a64$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a65$1 = 10
        # 
# 🤙🏼 Calling getReg() for a65$1 = 10
        sw      x12, -272(fp)  # Store Local Var - a64$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a64$1 in memory
        # 
# 👋 GetReg() for a65$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a65$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a65$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a65$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a65$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a66$1 = 10
        # 
# 🤙🏼 Calling getReg() for a66$1 = 10
        sw      x12, -276(fp)  # Store Local Var - a65$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a65$1 in memory
        # 
# 👋 GetReg() for a66$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a66$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a66$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a66$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a66$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a67$1 = 10
        # 
# 🤙🏼 Calling getReg() for a67$1 = 10
        sw      x12, -280(fp)  # Store Local Var - a66$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a66$1 in memory
        # 
# 👋 GetReg() for a67$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a67$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a67$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a67$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a67$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a68$1 = 10
        # 
# 🤙🏼 Calling getReg() for a68$1 = 10
        sw      x12, -284(fp)  # Store Local Var - a67$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a67$1 in memory
        # 
# 👋 GetReg() for a68$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a68$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a68$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a68$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a68$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a69$1 = 10
        # 
# 🤙🏼 Calling getReg() for a69$1 = 10
        sw      x12, -288(fp)  # Store Local Var - a68$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a68$1 in memory
        # 
# 👋 GetReg() for a69$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a69$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a69$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a69$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a69$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a70$1 = 10
        # 
# 🤙🏼 Calling getReg() for a70$1 = 10
        sw      x12, -292(fp)  # Store Local Var - a69$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a69$1 in memory
        # 
# 👋 GetReg() for a70$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a70$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a70$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a70$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a70$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a71$1 = 10
        # 
# 🤙🏼 Calling getReg() for a71$1 = 10
        sw      x12, -296(fp)  # Store Local Var - a70$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a70$1 in memory
        # 
# 👋 GetReg() for a71$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a71$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a71$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a71$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a71$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a72$1 = 10
        # 
# 🤙🏼 Calling getReg() for a72$1 = 10
        sw      x12, -300(fp)  # Store Local Var - a71$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a71$1 in memory
        # 
# 👋 GetReg() for a72$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a72$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a72$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a72$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a72$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a73$1 = 10
        # 
# 🤙🏼 Calling getReg() for a73$1 = 10
        sw      x12, -304(fp)  # Store Local Var - a72$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a72$1 in memory
        # 
# 👋 GetReg() for a73$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a73$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a73$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a73$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a73$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a74$1 = 10
        # 
# 🤙🏼 Calling getReg() for a74$1 = 10
        sw      x12, -308(fp)  # Store Local Var - a73$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a73$1 in memory
        # 
# 👋 GetReg() for a74$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a74$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a74$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a74$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a74$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a75$1 = 10
        # 
# 🤙🏼 Calling getReg() for a75$1 = 10
        sw      x12, -312(fp)  # Store Local Var - a74$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a74$1 in memory
        # 
# 👋 GetReg() for a75$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a75$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a75$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a75$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a75$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a76$1 = 10
        # 
# 🤙🏼 Calling getReg() for a76$1 = 10
        sw      x12, -316(fp)  # Store Local Var - a75$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a75$1 in memory
        # 
# 👋 GetReg() for a76$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a76$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a76$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a76$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a76$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a77$1 = 10
        # 
# 🤙🏼 Calling getReg() for a77$1 = 10
        sw      x12, -320(fp)  # Store Local Var - a76$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a76$1 in memory
        # 
# 👋 GetReg() for a77$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a77$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a77$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a77$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a77$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a78$1 = 10
        # 
# 🤙🏼 Calling getReg() for a78$1 = 10
        sw      x12, -324(fp)  # Store Local Var - a77$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a77$1 in memory
        # 
# 👋 GetReg() for a78$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a78$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a78$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a78$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a78$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a79$1 = 10
        # 
# 🤙🏼 Calling getReg() for a79$1 = 10
        sw      x12, -328(fp)  # Store Local Var - a78$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a78$1 in memory
        # 
# 👋 GetReg() for a79$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a79$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a79$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a79$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a79$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a80$1 = 10
        # 
# 🤙🏼 Calling getReg() for a80$1 = 10
        sw      x12, -332(fp)  # Store Local Var - a79$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a79$1 in memory
        # 
# 👋 GetReg() for a80$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a80$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a80$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a80$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a80$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a81$1 = 10
        # 
# 🤙🏼 Calling getReg() for a81$1 = 10
        sw      x12, -336(fp)  # Store Local Var - a80$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a80$1 in memory
        # 
# 👋 GetReg() for a81$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a81$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a81$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a81$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a81$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a82$1 = 10
        # 
# 🤙🏼 Calling getReg() for a82$1 = 10
        sw      x12, -340(fp)  # Store Local Var - a81$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a81$1 in memory
        # 
# 👋 GetReg() for a82$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a82$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a82$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a82$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a82$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a83$1 = 10
        # 
# 🤙🏼 Calling getReg() for a83$1 = 10
        sw      x12, -344(fp)  # Store Local Var - a82$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a82$1 in memory
        # 
# 👋 GetReg() for a83$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a83$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a83$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a83$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a83$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a84$1 = 10
        # 
# 🤙🏼 Calling getReg() for a84$1 = 10
        sw      x12, -348(fp)  # Store Local Var - a83$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a83$1 in memory
        # 
# 👋 GetReg() for a84$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a84$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a84$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a84$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a84$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a85$1 = 10
        # 
# 🤙🏼 Calling getReg() for a85$1 = 10
        sw      x12, -352(fp)  # Store Local Var - a84$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a84$1 in memory
        # 
# 👋 GetReg() for a85$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a85$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a85$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a85$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a85$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a86$1 = 10
        # 
# 🤙🏼 Calling getReg() for a86$1 = 10
        sw      x12, -356(fp)  # Store Local Var - a85$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a85$1 in memory
        # 
# 👋 GetReg() for a86$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a86$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a86$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a86$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a86$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a87$1 = 10
        # 
# 🤙🏼 Calling getReg() for a87$1 = 10
        sw      x12, -360(fp)  # Store Local Var - a86$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a86$1 in memory
        # 
# 👋 GetReg() for a87$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a87$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a87$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a87$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a87$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a88$1 = 10
        # 
# 🤙🏼 Calling getReg() for a88$1 = 10
        sw      x12, -364(fp)  # Store Local Var - a87$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a87$1 in memory
        # 
# 👋 GetReg() for a88$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a88$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a88$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a88$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a88$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a89$1 = 10
        # 
# 🤙🏼 Calling getReg() for a89$1 = 10
        sw      x12, -368(fp)  # Store Local Var - a88$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a88$1 in memory
        # 
# 👋 GetReg() for a89$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a89$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a89$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a89$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a89$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a90$1 = 10
        # 
# 🤙🏼 Calling getReg() for a90$1 = 10
        sw      x12, -372(fp)  # Store Local Var - a89$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a89$1 in memory
        # 
# 👋 GetReg() for a90$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a90$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a90$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a90$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a90$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a91$1 = 10
        # 
# 🤙🏼 Calling getReg() for a91$1 = 10
        sw      x12, -376(fp)  # Store Local Var - a90$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a90$1 in memory
        # 
# 👋 GetReg() for a91$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a91$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a91$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a91$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a91$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a92$1 = 10
        # 
# 🤙🏼 Calling getReg() for a92$1 = 10
        sw      x12, -380(fp)  # Store Local Var - a91$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a91$1 in memory
        # 
# 👋 GetReg() for a92$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a92$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a92$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a92$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a92$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a93$1 = 10
        # 
# 🤙🏼 Calling getReg() for a93$1 = 10
        sw      x12, -384(fp)  # Store Local Var - a92$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a92$1 in memory
        # 
# 👋 GetReg() for a93$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a93$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a93$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a93$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a93$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a94$1 = 10
        # 
# 🤙🏼 Calling getReg() for a94$1 = 10
        sw      x12, -388(fp)  # Store Local Var - a93$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a93$1 in memory
        # 
# 👋 GetReg() for a94$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a94$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a94$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a94$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a94$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a95$1 = 10
        # 
# 🤙🏼 Calling getReg() for a95$1 = 10
        sw      x12, -392(fp)  # Store Local Var - a94$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a94$1 in memory
        # 
# 👋 GetReg() for a95$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a95$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a95$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a95$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a95$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a96$1 = 10
        # 
# 🤙🏼 Calling getReg() for a96$1 = 10
        sw      x12, -396(fp)  # Store Local Var - a95$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a95$1 in memory
        # 
# 👋 GetReg() for a96$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a96$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a96$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a96$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a96$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a97$1 = 10
        # 
# 🤙🏼 Calling getReg() for a97$1 = 10
        sw      x12, -400(fp)  # Store Local Var - a96$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a96$1 in memory
        # 
# 👋 GetReg() for a97$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a97$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a97$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a97$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a97$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a98$1 = 10
        # 
# 🤙🏼 Calling getReg() for a98$1 = 10
        sw      x12, -404(fp)  # Store Local Var - a97$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a97$1 in memory
        # 
# 👋 GetReg() for a98$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a98$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a98$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a98$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a98$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a99$1 = 10
        # 
# 🤙🏼 Calling getReg() for a99$1 = 10
        sw      x12, -408(fp)  # Store Local Var - a98$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a98$1 in memory
        # 
# 👋 GetReg() for a99$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a99$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a99$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a99$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a99$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a100$1 = 10
        # 
# 🤙🏼 Calling getReg() for a100$1 = 10
        sw      x12, -412(fp)  # Store Local Var - a99$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a99$1 in memory
        # 
# 👋 GetReg() for a100$1 = 10 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a100$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a100$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a100$1 to register 12
        li      x12, 10        # Load constant - 10 into x12(a100$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a1$1 + a2$1
        # 
# 🤙🏼 Calling getReg() for $0 = a1$1 + a2$1
        sw      x12, -416(fp)  # Store Local Var - a100$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a100$1 in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a1$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - a1$1 via fp in x12
        #  🔵 Already in register - a2$1 in 13
        sw      x14, -28(fp)   # Store Local Var - a3$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 a3$1 in memory
        # 
# 👋 GetReg() for $0 = a1$1 + a2$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x12` reg ➜ a1$1 | 🤝 `x13` reg ➜ a2$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 14
        add     x14, x12, x13  # Addition Operation - $0 = a1$1 + a2$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = $0 + a3$1
        # 
# 🤙🏼 Calling getReg() for $1 = $0 + a3$1
        #  🔵 Already in register - $0 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a3$1 to register 12
        lw      x12, -28(fp)   # Load Local Var - a3$1 via fp in x12
        #  🍊 Giving $1 same reg as given to $0 since it not used again
        # 
# 👋 GetReg() for $1 = $0 + a3$1 | 🤝 `x14` reg ➜ $0 | 🤝 `x14` reg ➜ $1 | 🤝 `x12` reg ➜ a3$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 14
        add     x14, x14, x12  # Addition Operation - $1 = $0 + a3$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $2 = $1 + a4$1
        # 
# 🤙🏼 Calling getReg() for $2 = $1 + a4$1
        #  🔵 Already in register - $1 in 14
        #  🔵 Already in register - a4$1 in 15
        # 
# 👋 GetReg() for $2 = $1 + a4$1 | 🤝 `x14` reg ➜ $1 | 🤝 `x12` reg ➜ $2 | 🤝 `x15` reg ➜ a4$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        add     x12, x14, x15  # Addition Operation - $2 = $1 + a4$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = $2 + a5$1
        # 
# 🤙🏼 Calling getReg() for $3 = $2 + a5$1
        #  🔵 Already in register - $2 in 12
        #  🔵 Already in register - a5$1 in 16
        #  🍊 Giving $3 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $3 = $2 + a5$1 | 🤝 `x12` reg ➜ $2 | 🤝 `x12` reg ➜ $3 | 🤝 `x16` reg ➜ a5$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 12
        add     x12, x12, x16  # Addition Operation - $3 = $2 + a5$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $4 = $3 + a6$1
        # 
# 🤙🏼 Calling getReg() for $4 = $3 + a6$1
        #  🔵 Already in register - $3 in 12
        #  🔵 Already in register - a6$1 in 17
        sw      x14, -424(fp)  # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x14, -428(fp)  # Store Local Var - $1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        # 
# 👋 GetReg() for $4 = $3 + a6$1 | 🤝 `x12` reg ➜ $3 | 🤝 `x14` reg ➜ $4 | 🤝 `x17` reg ➜ a6$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 14
        add     x14, x12, x17  # Addition Operation - $4 = $3 + a6$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $5 = $4 + a7$1
        # 
# 🤙🏼 Calling getReg() for $5 = $4 + a7$1
        #  🔵 Already in register - $4 in 14
        #  🔵 Already in register - a7$1 in 18
        #  🍊 Giving $5 same reg as given to $4 since it not used again
        # 
# 👋 GetReg() for $5 = $4 + a7$1 | 🤝 `x14` reg ➜ $4 | 🤝 `x14` reg ➜ $5 | 🤝 `x18` reg ➜ a7$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 14
        add     x14, x14, x18  # Addition Operation - $5 = $4 + a7$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $6 = $5 + a8$1
        # 
# 🤙🏼 Calling getReg() for $6 = $5 + a8$1
        #  🔵 Already in register - $5 in 14
        #  🔵 Already in register - a8$1 in 19
        sw      x12, -432(fp)  # Store Local Var - $2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x12, -436(fp)  # Store Local Var - $3 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        # 
# 👋 GetReg() for $6 = $5 + a8$1 | 🤝 `x14` reg ➜ $5 | 🤝 `x12` reg ➜ $6 | 🤝 `x19` reg ➜ a8$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $6 to register 12
        add     x12, x14, x19  # Addition Operation - $6 = $5 + a8$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $7 = $6 + a9$1
        # 
# 🤙🏼 Calling getReg() for $7 = $6 + a9$1
        #  🔵 Already in register - $6 in 12
        #  🔵 Already in register - a9$1 in 20
        #  🍊 Giving $7 same reg as given to $6 since it not used again
        # 
# 👋 GetReg() for $7 = $6 + a9$1 | 🤝 `x12` reg ➜ $6 | 🤝 `x12` reg ➜ $7 | 🤝 `x20` reg ➜ a9$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $7 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 12
        add     x12, x12, x20  # Addition Operation - $7 = $6 + a9$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $8 = $7 + a10$1
        # 
# 🤙🏼 Calling getReg() for $8 = $7 + a10$1
        #  🔵 Already in register - $7 in 12
        #  🔵 Already in register - a10$1 in 21
        sw      x14, -440(fp)  # Store Local Var - $4 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        sw      x14, -444(fp)  # Store Local Var - $5 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        # 
# 👋 GetReg() for $8 = $7 + a10$1 | 🤝 `x12` reg ➜ $7 | 🤝 `x14` reg ➜ $8 | 🤝 `x21` reg ➜ a10$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $8 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $8 to register 14
        add     x14, x12, x21  # Addition Operation - $8 = $7 + a10$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $9 = $8 + a11$1
        # 
# 🤙🏼 Calling getReg() for $9 = $8 + a11$1
        #  🔵 Already in register - $8 in 14
        #  🔵 Already in register - a11$1 in 22
        #  🍊 Giving $9 same reg as given to $8 since it not used again
        # 
# 👋 GetReg() for $9 = $8 + a11$1 | 🤝 `x14` reg ➜ $8 | 🤝 `x14` reg ➜ $9 | 🤝 `x22` reg ➜ a11$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $9 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $9 to register 14
        add     x14, x14, x22  # Addition Operation - $9 = $8 + a11$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $10 = $9 + a12$1
        # 
# 🤙🏼 Calling getReg() for $10 = $9 + a12$1
        #  🔵 Already in register - $9 in 14
        #  🔵 Already in register - a12$1 in 23
        sw      x12, -448(fp)  # Store Local Var - $6 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        sw      x12, -452(fp)  # Store Local Var - $7 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $7 in memory
        # 
# 👋 GetReg() for $10 = $9 + a12$1 | 🤝 `x12` reg ➜ $10 | 🤝 `x14` reg ➜ $9 | 🤝 `x23` reg ➜ a12$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $10 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $10 to register 12
        add     x12, x14, x23  # Addition Operation - $10 = $9 + a12$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $11 = $10 + a13$1
        # 
# 🤙🏼 Calling getReg() for $11 = $10 + a13$1
        #  🔵 Already in register - $10 in 12
        #  🔵 Already in register - a13$1 in 24
        #  🍊 Giving $11 same reg as given to $10 since it not used again
        # 
# 👋 GetReg() for $11 = $10 + a13$1 | 🤝 `x12` reg ➜ $10 | 🤝 `x12` reg ➜ $11 | 🤝 `x24` reg ➜ a13$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $11 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $11 to register 12
        add     x12, x12, x24  # Addition Operation - $11 = $10 + a13$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $12 = $11 + a14$1
        # 
# 🤙🏼 Calling getReg() for $12 = $11 + a14$1
        #  🔵 Already in register - $11 in 12
        #  🔵 Already in register - a14$1 in 25
        sw      x14, -456(fp)  # Store Local Var - $8 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $8 in memory
        sw      x14, -460(fp)  # Store Local Var - $9 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $9 in memory
        # 
# 👋 GetReg() for $12 = $11 + a14$1 | 🤝 `x12` reg ➜ $11 | 🤝 `x14` reg ➜ $12 | 🤝 `x25` reg ➜ a14$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $12 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $12 to register 14
        add     x14, x12, x25  # Addition Operation - $12 = $11 + a14$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $13 = $12 + a15$1
        # 
# 🤙🏼 Calling getReg() for $13 = $12 + a15$1
        #  🔵 Already in register - $12 in 14
        #  🔵 Already in register - a15$1 in 26
        #  🍊 Giving $13 same reg as given to $12 since it not used again
        # 
# 👋 GetReg() for $13 = $12 + a15$1 | 🤝 `x14` reg ➜ $12 | 🤝 `x14` reg ➜ $13 | 🤝 `x26` reg ➜ a15$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $13 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $13 to register 14
        add     x14, x14, x26  # Addition Operation - $13 = $12 + a15$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $14 = $13 + a16$1
        # 
# 🤙🏼 Calling getReg() for $14 = $13 + a16$1
        #  🔵 Already in register - $13 in 14
        #  🔵 Already in register - a16$1 in 27
        sw      x12, -464(fp)  # Store Local Var - $10 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $10 in memory
        sw      x12, -468(fp)  # Store Local Var - $11 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $11 in memory
        # 
# 👋 GetReg() for $14 = $13 + a16$1 | 🤝 `x14` reg ➜ $13 | 🤝 `x12` reg ➜ $14 | 🤝 `x27` reg ➜ a16$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $14 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $14 to register 12
        add     x12, x14, x27  # Addition Operation - $14 = $13 + a16$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $15 = $14 + a17$1
        # 
# 🤙🏼 Calling getReg() for $15 = $14 + a17$1
        #  🔵 Already in register - $14 in 12
        #  🔵 Already in register - a17$1 in 28
        #  🍊 Giving $15 same reg as given to $14 since it not used again
        # 
# 👋 GetReg() for $15 = $14 + a17$1 | 🤝 `x12` reg ➜ $14 | 🤝 `x12` reg ➜ $15 | 🤝 `x28` reg ➜ a17$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $15 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $15 to register 12
        add     x12, x12, x28  # Addition Operation - $15 = $14 + a17$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $16 = $15 + a18$1
        # 
# 🤙🏼 Calling getReg() for $16 = $15 + a18$1
        #  🔵 Already in register - $15 in 12
        #  🔵 Already in register - a18$1 in 29
        sw      x14, -472(fp)  # Store Local Var - $12 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $12 in memory
        sw      x14, -476(fp)  # Store Local Var - $13 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $13 in memory
        # 
# 👋 GetReg() for $16 = $15 + a18$1 | 🤝 `x12` reg ➜ $15 | 🤝 `x14` reg ➜ $16 | 🤝 `x29` reg ➜ a18$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $16 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $16 to register 14
        add     x14, x12, x29  # Addition Operation - $16 = $15 + a18$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $17 = $16 + a19$1
        # 
# 🤙🏼 Calling getReg() for $17 = $16 + a19$1
        #  🔵 Already in register - $16 in 14
        #  🔵 Already in register - a19$1 in 30
        #  🍊 Giving $17 same reg as given to $16 since it not used again
        # 
# 👋 GetReg() for $17 = $16 + a19$1 | 🤝 `x14` reg ➜ $16 | 🤝 `x14` reg ➜ $17 | 🤝 `x30` reg ➜ a19$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $17 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $17 to register 14
        add     x14, x14, x30  # Addition Operation - $17 = $16 + a19$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $18 = $17 + a20$1
        # 
# 🤙🏼 Calling getReg() for $18 = $17 + a20$1
        #  🔵 Already in register - $17 in 14
        #  🔵 Already in register - a20$1 in 31
        sw      x12, -480(fp)  # Store Local Var - $14 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $14 in memory
        sw      x12, -484(fp)  # Store Local Var - $15 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $15 in memory
        # 
# 👋 GetReg() for $18 = $17 + a20$1 | 🤝 `x14` reg ➜ $17 | 🤝 `x12` reg ➜ $18 | 🤝 `x31` reg ➜ a20$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $18 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $18 to register 12
        add     x12, x14, x31  # Addition Operation - $18 = $17 + a20$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $19 = $18 + a21$1
        # 
# 🤙🏼 Calling getReg() for $19 = $18 + a21$1
        #  🔵 Already in register - $18 in 12
        sw      x14, -488(fp)  # Store Local Var - $16 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $16 in memory
        sw      x14, -492(fp)  # Store Local Var - $17 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $17 in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a21$1 to register 14
        lw      x14, -100(fp)  # Load Local Var - a21$1 via fp in x14
        #  🍊 Giving $19 same reg as given to $18 since it not used again
        # 
# 👋 GetReg() for $19 = $18 + a21$1 | 🤝 `x12` reg ➜ $18 | 🤝 `x12` reg ➜ $19 | 🤝 `x14` reg ➜ a21$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $19 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $19 to register 12
        add     x12, x12, x14  # Addition Operation - $19 = $18 + a21$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $20 = $19 + a22$1
        # 
# 🤙🏼 Calling getReg() for $20 = $19 + a22$1
        #  🔵 Already in register - $19 in 12
        # 💛 SYM_RECORD 💛 - Adding 🌕 a22$1 to register 14
        lw      x14, -104(fp)  # Load Local Var - a22$1 via fp in x14
        sw      x13, -24(fp)   # Store Local Var - a2$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 a2$1 in memory
        # 
# 👋 GetReg() for $20 = $19 + a22$1 | 🤝 `x12` reg ➜ $19 | 🤝 `x13` reg ➜ $20 | 🤝 `x14` reg ➜ a22$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $20 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $20 to register 13
        add     x13, x12, x14  # Addition Operation - $20 = $19 + a22$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $21 = $20 + a23$1
        # 
# 🤙🏼 Calling getReg() for $21 = $20 + a23$1
        #  🔵 Already in register - $20 in 13
        sw      x12, -496(fp)  # Store Local Var - $18 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $18 in memory
        sw      x12, -500(fp)  # Store Local Var - $19 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $19 in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a23$1 to register 12
        lw      x12, -108(fp)  # Load Local Var - a23$1 via fp in x12
        #  🍊 Giving $21 same reg as given to $20 since it not used again
        # 
# 👋 GetReg() for $21 = $20 + a23$1 | 🤝 `x13` reg ➜ $20 | 🤝 `x13` reg ➜ $21 | 🤝 `x12` reg ➜ a23$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $21 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $21 to register 13
        add     x13, x13, x12  # Addition Operation - $21 = $20 + a23$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $22 = $21 + a24$1
        # 
# 🤙🏼 Calling getReg() for $22 = $21 + a24$1
        #  🔵 Already in register - $21 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a24$1 to register 12
        lw      x12, -112(fp)  # Load Local Var - a24$1 via fp in x12
        # 
# 👋 GetReg() for $22 = $21 + a24$1 | 🤝 `x13` reg ➜ $21 | 🤝 `x14` reg ➜ $22 | 🤝 `x12` reg ➜ a24$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $22 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $22 to register 14
        add     x14, x13, x12  # Addition Operation - $22 = $21 + a24$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $23 = $22 + a25$1
        # 
# 🤙🏼 Calling getReg() for $23 = $22 + a25$1
        #  🔵 Already in register - $22 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a25$1 to register 12
        lw      x12, -116(fp)  # Load Local Var - a25$1 via fp in x12
        #  🍊 Giving $23 same reg as given to $22 since it not used again
        # 
# 👋 GetReg() for $23 = $22 + a25$1 | 🤝 `x14` reg ➜ $22 | 🤝 `x14` reg ➜ $23 | 🤝 `x12` reg ➜ a25$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $23 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $23 to register 14
        add     x14, x14, x12  # Addition Operation - $23 = $22 + a25$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $24 = $23 + a26$1
        # 
# 🤙🏼 Calling getReg() for $24 = $23 + a26$1
        #  🔵 Already in register - $23 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a26$1 to register 12
        lw      x12, -120(fp)  # Load Local Var - a26$1 via fp in x12
        sw      x13, -504(fp)  # Store Local Var - $20 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $20 in memory
        sw      x13, -508(fp)  # Store Local Var - $21 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $21 in memory
        # 
# 👋 GetReg() for $24 = $23 + a26$1 | 🤝 `x14` reg ➜ $23 | 🤝 `x13` reg ➜ $24 | 🤝 `x12` reg ➜ a26$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $24 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $24 to register 13
        add     x13, x14, x12  # Addition Operation - $24 = $23 + a26$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $25 = $24 + a27$1
        # 
# 🤙🏼 Calling getReg() for $25 = $24 + a27$1
        #  🔵 Already in register - $24 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a27$1 to register 12
        lw      x12, -124(fp)  # Load Local Var - a27$1 via fp in x12
        #  🍊 Giving $25 same reg as given to $24 since it not used again
        # 
# 👋 GetReg() for $25 = $24 + a27$1 | 🤝 `x13` reg ➜ $24 | 🤝 `x13` reg ➜ $25 | 🤝 `x12` reg ➜ a27$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $25 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $25 to register 13
        add     x13, x13, x12  # Addition Operation - $25 = $24 + a27$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $26 = $25 + a28$1
        # 
# 🤙🏼 Calling getReg() for $26 = $25 + a28$1
        #  🔵 Already in register - $25 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a28$1 to register 12
        lw      x12, -128(fp)  # Load Local Var - a28$1 via fp in x12
        sw      x14, -512(fp)  # Store Local Var - $22 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $22 in memory
        sw      x14, -516(fp)  # Store Local Var - $23 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $23 in memory
        # 
# 👋 GetReg() for $26 = $25 + a28$1 | 🤝 `x13` reg ➜ $25 | 🤝 `x14` reg ➜ $26 | 🤝 `x12` reg ➜ a28$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $26 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $26 to register 14
        add     x14, x13, x12  # Addition Operation - $26 = $25 + a28$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $27 = $26 + a29$1
        # 
# 🤙🏼 Calling getReg() for $27 = $26 + a29$1
        #  🔵 Already in register - $26 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a29$1 to register 12
        lw      x12, -132(fp)  # Load Local Var - a29$1 via fp in x12
        #  🍊 Giving $27 same reg as given to $26 since it not used again
        # 
# 👋 GetReg() for $27 = $26 + a29$1 | 🤝 `x14` reg ➜ $26 | 🤝 `x14` reg ➜ $27 | 🤝 `x12` reg ➜ a29$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $27 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $27 to register 14
        add     x14, x14, x12  # Addition Operation - $27 = $26 + a29$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $28 = $27 + a30$1
        # 
# 🤙🏼 Calling getReg() for $28 = $27 + a30$1
        #  🔵 Already in register - $27 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a30$1 to register 12
        lw      x12, -136(fp)  # Load Local Var - a30$1 via fp in x12
        sw      x13, -520(fp)  # Store Local Var - $24 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $24 in memory
        sw      x13, -524(fp)  # Store Local Var - $25 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $25 in memory
        # 
# 👋 GetReg() for $28 = $27 + a30$1 | 🤝 `x14` reg ➜ $27 | 🤝 `x13` reg ➜ $28 | 🤝 `x12` reg ➜ a30$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $28 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $28 to register 13
        add     x13, x14, x12  # Addition Operation - $28 = $27 + a30$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $29 = $28 + a31$1
        # 
# 🤙🏼 Calling getReg() for $29 = $28 + a31$1
        #  🔵 Already in register - $28 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a31$1 to register 12
        lw      x12, -140(fp)  # Load Local Var - a31$1 via fp in x12
        #  🍊 Giving $29 same reg as given to $28 since it not used again
        # 
# 👋 GetReg() for $29 = $28 + a31$1 | 🤝 `x13` reg ➜ $28 | 🤝 `x13` reg ➜ $29 | 🤝 `x12` reg ➜ a31$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $29 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $29 to register 13
        add     x13, x13, x12  # Addition Operation - $29 = $28 + a31$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $30 = $29 + a32$1
        # 
# 🤙🏼 Calling getReg() for $30 = $29 + a32$1
        #  🔵 Already in register - $29 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a32$1 to register 12
        lw      x12, -144(fp)  # Load Local Var - a32$1 via fp in x12
        sw      x14, -528(fp)  # Store Local Var - $26 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $26 in memory
        sw      x14, -532(fp)  # Store Local Var - $27 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $27 in memory
        # 
# 👋 GetReg() for $30 = $29 + a32$1 | 🤝 `x13` reg ➜ $29 | 🤝 `x14` reg ➜ $30 | 🤝 `x12` reg ➜ a32$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $30 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $30 to register 14
        add     x14, x13, x12  # Addition Operation - $30 = $29 + a32$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $31 = $30 + a33$1
        # 
# 🤙🏼 Calling getReg() for $31 = $30 + a33$1
        #  🔵 Already in register - $30 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a33$1 to register 12
        lw      x12, -148(fp)  # Load Local Var - a33$1 via fp in x12
        #  🍊 Giving $31 same reg as given to $30 since it not used again
        # 
# 👋 GetReg() for $31 = $30 + a33$1 | 🤝 `x14` reg ➜ $30 | 🤝 `x14` reg ➜ $31 | 🤝 `x12` reg ➜ a33$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $31 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $31 to register 14
        add     x14, x14, x12  # Addition Operation - $31 = $30 + a33$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $32 = $31 + a34$1
        # 
# 🤙🏼 Calling getReg() for $32 = $31 + a34$1
        #  🔵 Already in register - $31 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a34$1 to register 12
        lw      x12, -152(fp)  # Load Local Var - a34$1 via fp in x12
        sw      x13, -536(fp)  # Store Local Var - $28 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $28 in memory
        sw      x13, -540(fp)  # Store Local Var - $29 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $29 in memory
        # 
# 👋 GetReg() for $32 = $31 + a34$1 | 🤝 `x14` reg ➜ $31 | 🤝 `x13` reg ➜ $32 | 🤝 `x12` reg ➜ a34$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $32 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $32 to register 13
        add     x13, x14, x12  # Addition Operation - $32 = $31 + a34$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $33 = $32 + a35$1
        # 
# 🤙🏼 Calling getReg() for $33 = $32 + a35$1
        #  🔵 Already in register - $32 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a35$1 to register 12
        lw      x12, -156(fp)  # Load Local Var - a35$1 via fp in x12
        #  🍊 Giving $33 same reg as given to $32 since it not used again
        # 
# 👋 GetReg() for $33 = $32 + a35$1 | 🤝 `x13` reg ➜ $32 | 🤝 `x13` reg ➜ $33 | 🤝 `x12` reg ➜ a35$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $33 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $33 to register 13
        add     x13, x13, x12  # Addition Operation - $33 = $32 + a35$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $34 = $33 + a36$1
        # 
# 🤙🏼 Calling getReg() for $34 = $33 + a36$1
        #  🔵 Already in register - $33 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a36$1 to register 12
        lw      x12, -160(fp)  # Load Local Var - a36$1 via fp in x12
        sw      x14, -544(fp)  # Store Local Var - $30 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $30 in memory
        sw      x14, -548(fp)  # Store Local Var - $31 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $31 in memory
        # 
# 👋 GetReg() for $34 = $33 + a36$1 | 🤝 `x13` reg ➜ $33 | 🤝 `x14` reg ➜ $34 | 🤝 `x12` reg ➜ a36$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $34 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $34 to register 14
        add     x14, x13, x12  # Addition Operation - $34 = $33 + a36$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $35 = $34 + a37$1
        # 
# 🤙🏼 Calling getReg() for $35 = $34 + a37$1
        #  🔵 Already in register - $34 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a37$1 to register 12
        lw      x12, -164(fp)  # Load Local Var - a37$1 via fp in x12
        #  🍊 Giving $35 same reg as given to $34 since it not used again
        # 
# 👋 GetReg() for $35 = $34 + a37$1 | 🤝 `x14` reg ➜ $34 | 🤝 `x14` reg ➜ $35 | 🤝 `x12` reg ➜ a37$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $35 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $35 to register 14
        add     x14, x14, x12  # Addition Operation - $35 = $34 + a37$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $36 = $35 + a38$1
        # 
# 🤙🏼 Calling getReg() for $36 = $35 + a38$1
        #  🔵 Already in register - $35 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a38$1 to register 12
        lw      x12, -168(fp)  # Load Local Var - a38$1 via fp in x12
        sw      x13, -552(fp)  # Store Local Var - $32 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $32 in memory
        sw      x13, -556(fp)  # Store Local Var - $33 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $33 in memory
        # 
# 👋 GetReg() for $36 = $35 + a38$1 | 🤝 `x14` reg ➜ $35 | 🤝 `x13` reg ➜ $36 | 🤝 `x12` reg ➜ a38$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $36 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $36 to register 13
        add     x13, x14, x12  # Addition Operation - $36 = $35 + a38$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $37 = $36 + a39$1
        # 
# 🤙🏼 Calling getReg() for $37 = $36 + a39$1
        #  🔵 Already in register - $36 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a39$1 to register 12
        lw      x12, -172(fp)  # Load Local Var - a39$1 via fp in x12
        #  🍊 Giving $37 same reg as given to $36 since it not used again
        # 
# 👋 GetReg() for $37 = $36 + a39$1 | 🤝 `x13` reg ➜ $36 | 🤝 `x13` reg ➜ $37 | 🤝 `x12` reg ➜ a39$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $37 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $37 to register 13
        add     x13, x13, x12  # Addition Operation - $37 = $36 + a39$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $38 = $37 + a40$1
        # 
# 🤙🏼 Calling getReg() for $38 = $37 + a40$1
        #  🔵 Already in register - $37 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a40$1 to register 12
        lw      x12, -176(fp)  # Load Local Var - a40$1 via fp in x12
        sw      x14, -560(fp)  # Store Local Var - $34 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $34 in memory
        sw      x14, -564(fp)  # Store Local Var - $35 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $35 in memory
        # 
# 👋 GetReg() for $38 = $37 + a40$1 | 🤝 `x13` reg ➜ $37 | 🤝 `x14` reg ➜ $38 | 🤝 `x12` reg ➜ a40$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $38 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $38 to register 14
        add     x14, x13, x12  # Addition Operation - $38 = $37 + a40$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $39 = $38 + a41$1
        # 
# 🤙🏼 Calling getReg() for $39 = $38 + a41$1
        #  🔵 Already in register - $38 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a41$1 to register 12
        lw      x12, -180(fp)  # Load Local Var - a41$1 via fp in x12
        #  🍊 Giving $39 same reg as given to $38 since it not used again
        # 
# 👋 GetReg() for $39 = $38 + a41$1 | 🤝 `x14` reg ➜ $38 | 🤝 `x14` reg ➜ $39 | 🤝 `x12` reg ➜ a41$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $39 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $39 to register 14
        add     x14, x14, x12  # Addition Operation - $39 = $38 + a41$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $40 = $39 + a42$1
        # 
# 🤙🏼 Calling getReg() for $40 = $39 + a42$1
        #  🔵 Already in register - $39 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a42$1 to register 12
        lw      x12, -184(fp)  # Load Local Var - a42$1 via fp in x12
        sw      x13, -568(fp)  # Store Local Var - $36 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $36 in memory
        sw      x13, -572(fp)  # Store Local Var - $37 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $37 in memory
        # 
# 👋 GetReg() for $40 = $39 + a42$1 | 🤝 `x14` reg ➜ $39 | 🤝 `x13` reg ➜ $40 | 🤝 `x12` reg ➜ a42$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $40 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $40 to register 13
        add     x13, x14, x12  # Addition Operation - $40 = $39 + a42$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $41 = $40 + a43$1
        # 
# 🤙🏼 Calling getReg() for $41 = $40 + a43$1
        #  🔵 Already in register - $40 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a43$1 to register 12
        lw      x12, -188(fp)  # Load Local Var - a43$1 via fp in x12
        #  🍊 Giving $41 same reg as given to $40 since it not used again
        # 
# 👋 GetReg() for $41 = $40 + a43$1 | 🤝 `x13` reg ➜ $40 | 🤝 `x13` reg ➜ $41 | 🤝 `x12` reg ➜ a43$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $41 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $41 to register 13
        add     x13, x13, x12  # Addition Operation - $41 = $40 + a43$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $42 = $41 + a44$1
        # 
# 🤙🏼 Calling getReg() for $42 = $41 + a44$1
        #  🔵 Already in register - $41 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a44$1 to register 12
        lw      x12, -192(fp)  # Load Local Var - a44$1 via fp in x12
        sw      x14, -576(fp)  # Store Local Var - $38 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $38 in memory
        sw      x14, -580(fp)  # Store Local Var - $39 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $39 in memory
        # 
# 👋 GetReg() for $42 = $41 + a44$1 | 🤝 `x13` reg ➜ $41 | 🤝 `x14` reg ➜ $42 | 🤝 `x12` reg ➜ a44$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $42 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $42 to register 14
        add     x14, x13, x12  # Addition Operation - $42 = $41 + a44$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $43 = $42 + a45$1
        # 
# 🤙🏼 Calling getReg() for $43 = $42 + a45$1
        #  🔵 Already in register - $42 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a45$1 to register 12
        lw      x12, -196(fp)  # Load Local Var - a45$1 via fp in x12
        #  🍊 Giving $43 same reg as given to $42 since it not used again
        # 
# 👋 GetReg() for $43 = $42 + a45$1 | 🤝 `x14` reg ➜ $42 | 🤝 `x14` reg ➜ $43 | 🤝 `x12` reg ➜ a45$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $43 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $43 to register 14
        add     x14, x14, x12  # Addition Operation - $43 = $42 + a45$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $44 = $43 + a46$1
        # 
# 🤙🏼 Calling getReg() for $44 = $43 + a46$1
        #  🔵 Already in register - $43 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a46$1 to register 12
        lw      x12, -200(fp)  # Load Local Var - a46$1 via fp in x12
        sw      x13, -584(fp)  # Store Local Var - $40 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $40 in memory
        sw      x13, -588(fp)  # Store Local Var - $41 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $41 in memory
        # 
# 👋 GetReg() for $44 = $43 + a46$1 | 🤝 `x14` reg ➜ $43 | 🤝 `x13` reg ➜ $44 | 🤝 `x12` reg ➜ a46$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $44 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $44 to register 13
        add     x13, x14, x12  # Addition Operation - $44 = $43 + a46$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $45 = $44 + a47$1
        # 
# 🤙🏼 Calling getReg() for $45 = $44 + a47$1
        #  🔵 Already in register - $44 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a47$1 to register 12
        lw      x12, -204(fp)  # Load Local Var - a47$1 via fp in x12
        #  🍊 Giving $45 same reg as given to $44 since it not used again
        # 
# 👋 GetReg() for $45 = $44 + a47$1 | 🤝 `x13` reg ➜ $44 | 🤝 `x13` reg ➜ $45 | 🤝 `x12` reg ➜ a47$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $45 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $45 to register 13
        add     x13, x13, x12  # Addition Operation - $45 = $44 + a47$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $46 = $45 + a48$1
        # 
# 🤙🏼 Calling getReg() for $46 = $45 + a48$1
        #  🔵 Already in register - $45 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a48$1 to register 12
        lw      x12, -208(fp)  # Load Local Var - a48$1 via fp in x12
        sw      x14, -592(fp)  # Store Local Var - $42 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $42 in memory
        sw      x14, -596(fp)  # Store Local Var - $43 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $43 in memory
        # 
# 👋 GetReg() for $46 = $45 + a48$1 | 🤝 `x13` reg ➜ $45 | 🤝 `x14` reg ➜ $46 | 🤝 `x12` reg ➜ a48$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $46 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $46 to register 14
        add     x14, x13, x12  # Addition Operation - $46 = $45 + a48$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $47 = $46 + a49$1
        # 
# 🤙🏼 Calling getReg() for $47 = $46 + a49$1
        #  🔵 Already in register - $46 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a49$1 to register 12
        lw      x12, -212(fp)  # Load Local Var - a49$1 via fp in x12
        #  🍊 Giving $47 same reg as given to $46 since it not used again
        # 
# 👋 GetReg() for $47 = $46 + a49$1 | 🤝 `x14` reg ➜ $46 | 🤝 `x14` reg ➜ $47 | 🤝 `x12` reg ➜ a49$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $47 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $47 to register 14
        add     x14, x14, x12  # Addition Operation - $47 = $46 + a49$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $48 = $47 + a50$1
        # 
# 🤙🏼 Calling getReg() for $48 = $47 + a50$1
        #  🔵 Already in register - $47 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a50$1 to register 12
        lw      x12, -216(fp)  # Load Local Var - a50$1 via fp in x12
        sw      x13, -600(fp)  # Store Local Var - $44 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $44 in memory
        sw      x13, -604(fp)  # Store Local Var - $45 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $45 in memory
        # 
# 👋 GetReg() for $48 = $47 + a50$1 | 🤝 `x14` reg ➜ $47 | 🤝 `x13` reg ➜ $48 | 🤝 `x12` reg ➜ a50$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $48 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $48 to register 13
        add     x13, x14, x12  # Addition Operation - $48 = $47 + a50$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $49 = $48 + a51$1
        # 
# 🤙🏼 Calling getReg() for $49 = $48 + a51$1
        #  🔵 Already in register - $48 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a51$1 to register 12
        lw      x12, -220(fp)  # Load Local Var - a51$1 via fp in x12
        #  🍊 Giving $49 same reg as given to $48 since it not used again
        # 
# 👋 GetReg() for $49 = $48 + a51$1 | 🤝 `x13` reg ➜ $48 | 🤝 `x13` reg ➜ $49 | 🤝 `x12` reg ➜ a51$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $49 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $49 to register 13
        add     x13, x13, x12  # Addition Operation - $49 = $48 + a51$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $50 = $49 + a52$1
        # 
# 🤙🏼 Calling getReg() for $50 = $49 + a52$1
        #  🔵 Already in register - $49 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a52$1 to register 12
        lw      x12, -224(fp)  # Load Local Var - a52$1 via fp in x12
        sw      x14, -608(fp)  # Store Local Var - $46 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $46 in memory
        sw      x14, -612(fp)  # Store Local Var - $47 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $47 in memory
        # 
# 👋 GetReg() for $50 = $49 + a52$1 | 🤝 `x13` reg ➜ $49 | 🤝 `x14` reg ➜ $50 | 🤝 `x12` reg ➜ a52$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $50 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $50 to register 14
        add     x14, x13, x12  # Addition Operation - $50 = $49 + a52$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $51 = $50 + a53$1
        # 
# 🤙🏼 Calling getReg() for $51 = $50 + a53$1
        #  🔵 Already in register - $50 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a53$1 to register 12
        lw      x12, -228(fp)  # Load Local Var - a53$1 via fp in x12
        #  🍊 Giving $51 same reg as given to $50 since it not used again
        # 
# 👋 GetReg() for $51 = $50 + a53$1 | 🤝 `x14` reg ➜ $50 | 🤝 `x14` reg ➜ $51 | 🤝 `x12` reg ➜ a53$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $51 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $51 to register 14
        add     x14, x14, x12  # Addition Operation - $51 = $50 + a53$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $52 = $51 + a54$1
        # 
# 🤙🏼 Calling getReg() for $52 = $51 + a54$1
        #  🔵 Already in register - $51 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a54$1 to register 12
        lw      x12, -232(fp)  # Load Local Var - a54$1 via fp in x12
        sw      x13, -616(fp)  # Store Local Var - $48 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $48 in memory
        sw      x13, -620(fp)  # Store Local Var - $49 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $49 in memory
        # 
# 👋 GetReg() for $52 = $51 + a54$1 | 🤝 `x14` reg ➜ $51 | 🤝 `x13` reg ➜ $52 | 🤝 `x12` reg ➜ a54$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $52 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $52 to register 13
        add     x13, x14, x12  # Addition Operation - $52 = $51 + a54$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $53 = $52 + a55$1
        # 
# 🤙🏼 Calling getReg() for $53 = $52 + a55$1
        #  🔵 Already in register - $52 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a55$1 to register 12
        lw      x12, -236(fp)  # Load Local Var - a55$1 via fp in x12
        #  🍊 Giving $53 same reg as given to $52 since it not used again
        # 
# 👋 GetReg() for $53 = $52 + a55$1 | 🤝 `x13` reg ➜ $52 | 🤝 `x13` reg ➜ $53 | 🤝 `x12` reg ➜ a55$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $53 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $53 to register 13
        add     x13, x13, x12  # Addition Operation - $53 = $52 + a55$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $54 = $53 + a56$1
        # 
# 🤙🏼 Calling getReg() for $54 = $53 + a56$1
        #  🔵 Already in register - $53 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a56$1 to register 12
        lw      x12, -240(fp)  # Load Local Var - a56$1 via fp in x12
        sw      x14, -624(fp)  # Store Local Var - $50 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $50 in memory
        sw      x14, -628(fp)  # Store Local Var - $51 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $51 in memory
        # 
# 👋 GetReg() for $54 = $53 + a56$1 | 🤝 `x13` reg ➜ $53 | 🤝 `x14` reg ➜ $54 | 🤝 `x12` reg ➜ a56$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $54 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $54 to register 14
        add     x14, x13, x12  # Addition Operation - $54 = $53 + a56$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $55 = $54 + a57$1
        # 
# 🤙🏼 Calling getReg() for $55 = $54 + a57$1
        #  🔵 Already in register - $54 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a57$1 to register 12
        lw      x12, -244(fp)  # Load Local Var - a57$1 via fp in x12
        #  🍊 Giving $55 same reg as given to $54 since it not used again
        # 
# 👋 GetReg() for $55 = $54 + a57$1 | 🤝 `x14` reg ➜ $54 | 🤝 `x14` reg ➜ $55 | 🤝 `x12` reg ➜ a57$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $55 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $55 to register 14
        add     x14, x14, x12  # Addition Operation - $55 = $54 + a57$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $56 = $55 + a58$1
        # 
# 🤙🏼 Calling getReg() for $56 = $55 + a58$1
        #  🔵 Already in register - $55 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a58$1 to register 12
        lw      x12, -248(fp)  # Load Local Var - a58$1 via fp in x12
        sw      x13, -632(fp)  # Store Local Var - $52 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $52 in memory
        sw      x13, -636(fp)  # Store Local Var - $53 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $53 in memory
        # 
# 👋 GetReg() for $56 = $55 + a58$1 | 🤝 `x14` reg ➜ $55 | 🤝 `x13` reg ➜ $56 | 🤝 `x12` reg ➜ a58$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $56 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $56 to register 13
        add     x13, x14, x12  # Addition Operation - $56 = $55 + a58$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $57 = $56 + a59$1
        # 
# 🤙🏼 Calling getReg() for $57 = $56 + a59$1
        #  🔵 Already in register - $56 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a59$1 to register 12
        lw      x12, -252(fp)  # Load Local Var - a59$1 via fp in x12
        #  🍊 Giving $57 same reg as given to $56 since it not used again
        # 
# 👋 GetReg() for $57 = $56 + a59$1 | 🤝 `x13` reg ➜ $56 | 🤝 `x13` reg ➜ $57 | 🤝 `x12` reg ➜ a59$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $57 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $57 to register 13
        add     x13, x13, x12  # Addition Operation - $57 = $56 + a59$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $58 = $57 + a60$1
        # 
# 🤙🏼 Calling getReg() for $58 = $57 + a60$1
        #  🔵 Already in register - $57 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a60$1 to register 12
        lw      x12, -256(fp)  # Load Local Var - a60$1 via fp in x12
        sw      x14, -640(fp)  # Store Local Var - $54 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $54 in memory
        sw      x14, -644(fp)  # Store Local Var - $55 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $55 in memory
        # 
# 👋 GetReg() for $58 = $57 + a60$1 | 🤝 `x13` reg ➜ $57 | 🤝 `x14` reg ➜ $58 | 🤝 `x12` reg ➜ a60$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $58 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $58 to register 14
        add     x14, x13, x12  # Addition Operation - $58 = $57 + a60$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $59 = $58 + a61$1
        # 
# 🤙🏼 Calling getReg() for $59 = $58 + a61$1
        #  🔵 Already in register - $58 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a61$1 to register 12
        lw      x12, -260(fp)  # Load Local Var - a61$1 via fp in x12
        #  🍊 Giving $59 same reg as given to $58 since it not used again
        # 
# 👋 GetReg() for $59 = $58 + a61$1 | 🤝 `x14` reg ➜ $58 | 🤝 `x14` reg ➜ $59 | 🤝 `x12` reg ➜ a61$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $59 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $59 to register 14
        add     x14, x14, x12  # Addition Operation - $59 = $58 + a61$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $60 = $59 + a62$1
        # 
# 🤙🏼 Calling getReg() for $60 = $59 + a62$1
        #  🔵 Already in register - $59 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a62$1 to register 12
        lw      x12, -264(fp)  # Load Local Var - a62$1 via fp in x12
        sw      x13, -648(fp)  # Store Local Var - $56 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $56 in memory
        sw      x13, -652(fp)  # Store Local Var - $57 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $57 in memory
        # 
# 👋 GetReg() for $60 = $59 + a62$1 | 🤝 `x14` reg ➜ $59 | 🤝 `x13` reg ➜ $60 | 🤝 `x12` reg ➜ a62$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $60 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $60 to register 13
        add     x13, x14, x12  # Addition Operation - $60 = $59 + a62$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $61 = $60 + a63$1
        # 
# 🤙🏼 Calling getReg() for $61 = $60 + a63$1
        #  🔵 Already in register - $60 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a63$1 to register 12
        lw      x12, -268(fp)  # Load Local Var - a63$1 via fp in x12
        #  🍊 Giving $61 same reg as given to $60 since it not used again
        # 
# 👋 GetReg() for $61 = $60 + a63$1 | 🤝 `x13` reg ➜ $60 | 🤝 `x13` reg ➜ $61 | 🤝 `x12` reg ➜ a63$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $61 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $61 to register 13
        add     x13, x13, x12  # Addition Operation - $61 = $60 + a63$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $62 = $61 + a64$1
        # 
# 🤙🏼 Calling getReg() for $62 = $61 + a64$1
        #  🔵 Already in register - $61 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a64$1 to register 12
        lw      x12, -272(fp)  # Load Local Var - a64$1 via fp in x12
        sw      x14, -656(fp)  # Store Local Var - $58 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $58 in memory
        sw      x14, -660(fp)  # Store Local Var - $59 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $59 in memory
        # 
# 👋 GetReg() for $62 = $61 + a64$1 | 🤝 `x13` reg ➜ $61 | 🤝 `x14` reg ➜ $62 | 🤝 `x12` reg ➜ a64$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $62 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $62 to register 14
        add     x14, x13, x12  # Addition Operation - $62 = $61 + a64$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $63 = $62 + a65$1
        # 
# 🤙🏼 Calling getReg() for $63 = $62 + a65$1
        #  🔵 Already in register - $62 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a65$1 to register 12
        lw      x12, -276(fp)  # Load Local Var - a65$1 via fp in x12
        #  🍊 Giving $63 same reg as given to $62 since it not used again
        # 
# 👋 GetReg() for $63 = $62 + a65$1 | 🤝 `x14` reg ➜ $62 | 🤝 `x14` reg ➜ $63 | 🤝 `x12` reg ➜ a65$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $63 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $63 to register 14
        add     x14, x14, x12  # Addition Operation - $63 = $62 + a65$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $64 = $63 + a66$1
        # 
# 🤙🏼 Calling getReg() for $64 = $63 + a66$1
        #  🔵 Already in register - $63 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a66$1 to register 12
        lw      x12, -280(fp)  # Load Local Var - a66$1 via fp in x12
        sw      x13, -664(fp)  # Store Local Var - $60 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $60 in memory
        sw      x13, -668(fp)  # Store Local Var - $61 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $61 in memory
        # 
# 👋 GetReg() for $64 = $63 + a66$1 | 🤝 `x14` reg ➜ $63 | 🤝 `x13` reg ➜ $64 | 🤝 `x12` reg ➜ a66$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $64 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $64 to register 13
        add     x13, x14, x12  # Addition Operation - $64 = $63 + a66$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $65 = $64 + a67$1
        # 
# 🤙🏼 Calling getReg() for $65 = $64 + a67$1
        #  🔵 Already in register - $64 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a67$1 to register 12
        lw      x12, -284(fp)  # Load Local Var - a67$1 via fp in x12
        #  🍊 Giving $65 same reg as given to $64 since it not used again
        # 
# 👋 GetReg() for $65 = $64 + a67$1 | 🤝 `x13` reg ➜ $64 | 🤝 `x13` reg ➜ $65 | 🤝 `x12` reg ➜ a67$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $65 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $65 to register 13
        add     x13, x13, x12  # Addition Operation - $65 = $64 + a67$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $66 = $65 + a68$1
        # 
# 🤙🏼 Calling getReg() for $66 = $65 + a68$1
        #  🔵 Already in register - $65 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a68$1 to register 12
        lw      x12, -288(fp)  # Load Local Var - a68$1 via fp in x12
        sw      x14, -672(fp)  # Store Local Var - $62 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $62 in memory
        sw      x14, -676(fp)  # Store Local Var - $63 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $63 in memory
        # 
# 👋 GetReg() for $66 = $65 + a68$1 | 🤝 `x13` reg ➜ $65 | 🤝 `x14` reg ➜ $66 | 🤝 `x12` reg ➜ a68$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $66 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $66 to register 14
        add     x14, x13, x12  # Addition Operation - $66 = $65 + a68$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $67 = $66 + a69$1
        # 
# 🤙🏼 Calling getReg() for $67 = $66 + a69$1
        #  🔵 Already in register - $66 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a69$1 to register 12
        lw      x12, -292(fp)  # Load Local Var - a69$1 via fp in x12
        #  🍊 Giving $67 same reg as given to $66 since it not used again
        # 
# 👋 GetReg() for $67 = $66 + a69$1 | 🤝 `x14` reg ➜ $66 | 🤝 `x14` reg ➜ $67 | 🤝 `x12` reg ➜ a69$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $67 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $67 to register 14
        add     x14, x14, x12  # Addition Operation - $67 = $66 + a69$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $68 = $67 + a70$1
        # 
# 🤙🏼 Calling getReg() for $68 = $67 + a70$1
        #  🔵 Already in register - $67 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a70$1 to register 12
        lw      x12, -296(fp)  # Load Local Var - a70$1 via fp in x12
        sw      x13, -680(fp)  # Store Local Var - $64 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $64 in memory
        sw      x13, -684(fp)  # Store Local Var - $65 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $65 in memory
        # 
# 👋 GetReg() for $68 = $67 + a70$1 | 🤝 `x14` reg ➜ $67 | 🤝 `x13` reg ➜ $68 | 🤝 `x12` reg ➜ a70$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $68 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $68 to register 13
        add     x13, x14, x12  # Addition Operation - $68 = $67 + a70$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $69 = $68 + a71$1
        # 
# 🤙🏼 Calling getReg() for $69 = $68 + a71$1
        #  🔵 Already in register - $68 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a71$1 to register 12
        lw      x12, -300(fp)  # Load Local Var - a71$1 via fp in x12
        #  🍊 Giving $69 same reg as given to $68 since it not used again
        # 
# 👋 GetReg() for $69 = $68 + a71$1 | 🤝 `x13` reg ➜ $68 | 🤝 `x13` reg ➜ $69 | 🤝 `x12` reg ➜ a71$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $69 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $69 to register 13
        add     x13, x13, x12  # Addition Operation - $69 = $68 + a71$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $70 = $69 + a72$1
        # 
# 🤙🏼 Calling getReg() for $70 = $69 + a72$1
        #  🔵 Already in register - $69 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a72$1 to register 12
        lw      x12, -304(fp)  # Load Local Var - a72$1 via fp in x12
        sw      x14, -688(fp)  # Store Local Var - $66 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $66 in memory
        sw      x14, -692(fp)  # Store Local Var - $67 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $67 in memory
        # 
# 👋 GetReg() for $70 = $69 + a72$1 | 🤝 `x13` reg ➜ $69 | 🤝 `x14` reg ➜ $70 | 🤝 `x12` reg ➜ a72$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $70 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $70 to register 14
        add     x14, x13, x12  # Addition Operation - $70 = $69 + a72$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $71 = $70 + a73$1
        # 
# 🤙🏼 Calling getReg() for $71 = $70 + a73$1
        #  🔵 Already in register - $70 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a73$1 to register 12
        lw      x12, -308(fp)  # Load Local Var - a73$1 via fp in x12
        #  🍊 Giving $71 same reg as given to $70 since it not used again
        # 
# 👋 GetReg() for $71 = $70 + a73$1 | 🤝 `x14` reg ➜ $70 | 🤝 `x14` reg ➜ $71 | 🤝 `x12` reg ➜ a73$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $71 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $71 to register 14
        add     x14, x14, x12  # Addition Operation - $71 = $70 + a73$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $72 = $71 + a74$1
        # 
# 🤙🏼 Calling getReg() for $72 = $71 + a74$1
        #  🔵 Already in register - $71 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a74$1 to register 12
        lw      x12, -312(fp)  # Load Local Var - a74$1 via fp in x12
        sw      x13, -696(fp)  # Store Local Var - $68 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $68 in memory
        sw      x13, -700(fp)  # Store Local Var - $69 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $69 in memory
        # 
# 👋 GetReg() for $72 = $71 + a74$1 | 🤝 `x14` reg ➜ $71 | 🤝 `x13` reg ➜ $72 | 🤝 `x12` reg ➜ a74$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $72 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $72 to register 13
        add     x13, x14, x12  # Addition Operation - $72 = $71 + a74$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $73 = $72 + a75$1
        # 
# 🤙🏼 Calling getReg() for $73 = $72 + a75$1
        #  🔵 Already in register - $72 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a75$1 to register 12
        lw      x12, -316(fp)  # Load Local Var - a75$1 via fp in x12
        #  🍊 Giving $73 same reg as given to $72 since it not used again
        # 
# 👋 GetReg() for $73 = $72 + a75$1 | 🤝 `x13` reg ➜ $72 | 🤝 `x13` reg ➜ $73 | 🤝 `x12` reg ➜ a75$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $73 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $73 to register 13
        add     x13, x13, x12  # Addition Operation - $73 = $72 + a75$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $74 = $73 + a76$1
        # 
# 🤙🏼 Calling getReg() for $74 = $73 + a76$1
        #  🔵 Already in register - $73 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a76$1 to register 12
        lw      x12, -320(fp)  # Load Local Var - a76$1 via fp in x12
        sw      x14, -704(fp)  # Store Local Var - $70 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $70 in memory
        sw      x14, -708(fp)  # Store Local Var - $71 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $71 in memory
        # 
# 👋 GetReg() for $74 = $73 + a76$1 | 🤝 `x13` reg ➜ $73 | 🤝 `x14` reg ➜ $74 | 🤝 `x12` reg ➜ a76$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $74 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $74 to register 14
        add     x14, x13, x12  # Addition Operation - $74 = $73 + a76$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $75 = $74 + a77$1
        # 
# 🤙🏼 Calling getReg() for $75 = $74 + a77$1
        #  🔵 Already in register - $74 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a77$1 to register 12
        lw      x12, -324(fp)  # Load Local Var - a77$1 via fp in x12
        #  🍊 Giving $75 same reg as given to $74 since it not used again
        # 
# 👋 GetReg() for $75 = $74 + a77$1 | 🤝 `x14` reg ➜ $74 | 🤝 `x14` reg ➜ $75 | 🤝 `x12` reg ➜ a77$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $75 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $75 to register 14
        add     x14, x14, x12  # Addition Operation - $75 = $74 + a77$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $76 = $75 + a78$1
        # 
# 🤙🏼 Calling getReg() for $76 = $75 + a78$1
        #  🔵 Already in register - $75 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a78$1 to register 12
        lw      x12, -328(fp)  # Load Local Var - a78$1 via fp in x12
        sw      x13, -712(fp)  # Store Local Var - $72 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $72 in memory
        sw      x13, -716(fp)  # Store Local Var - $73 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $73 in memory
        # 
# 👋 GetReg() for $76 = $75 + a78$1 | 🤝 `x14` reg ➜ $75 | 🤝 `x13` reg ➜ $76 | 🤝 `x12` reg ➜ a78$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $76 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $76 to register 13
        add     x13, x14, x12  # Addition Operation - $76 = $75 + a78$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $77 = $76 + a79$1
        # 
# 🤙🏼 Calling getReg() for $77 = $76 + a79$1
        #  🔵 Already in register - $76 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a79$1 to register 12
        lw      x12, -332(fp)  # Load Local Var - a79$1 via fp in x12
        #  🍊 Giving $77 same reg as given to $76 since it not used again
        # 
# 👋 GetReg() for $77 = $76 + a79$1 | 🤝 `x13` reg ➜ $76 | 🤝 `x13` reg ➜ $77 | 🤝 `x12` reg ➜ a79$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $77 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $77 to register 13
        add     x13, x13, x12  # Addition Operation - $77 = $76 + a79$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $78 = $77 + a80$1
        # 
# 🤙🏼 Calling getReg() for $78 = $77 + a80$1
        #  🔵 Already in register - $77 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a80$1 to register 12
        lw      x12, -336(fp)  # Load Local Var - a80$1 via fp in x12
        sw      x14, -720(fp)  # Store Local Var - $74 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $74 in memory
        sw      x14, -724(fp)  # Store Local Var - $75 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $75 in memory
        # 
# 👋 GetReg() for $78 = $77 + a80$1 | 🤝 `x13` reg ➜ $77 | 🤝 `x14` reg ➜ $78 | 🤝 `x12` reg ➜ a80$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $78 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $78 to register 14
        add     x14, x13, x12  # Addition Operation - $78 = $77 + a80$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $79 = $78 + a81$1
        # 
# 🤙🏼 Calling getReg() for $79 = $78 + a81$1
        #  🔵 Already in register - $78 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a81$1 to register 12
        lw      x12, -340(fp)  # Load Local Var - a81$1 via fp in x12
        #  🍊 Giving $79 same reg as given to $78 since it not used again
        # 
# 👋 GetReg() for $79 = $78 + a81$1 | 🤝 `x14` reg ➜ $78 | 🤝 `x14` reg ➜ $79 | 🤝 `x12` reg ➜ a81$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $79 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $79 to register 14
        add     x14, x14, x12  # Addition Operation - $79 = $78 + a81$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $80 = $79 + a82$1
        # 
# 🤙🏼 Calling getReg() for $80 = $79 + a82$1
        #  🔵 Already in register - $79 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a82$1 to register 12
        lw      x12, -344(fp)  # Load Local Var - a82$1 via fp in x12
        sw      x13, -728(fp)  # Store Local Var - $76 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $76 in memory
        sw      x13, -732(fp)  # Store Local Var - $77 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $77 in memory
        # 
# 👋 GetReg() for $80 = $79 + a82$1 | 🤝 `x14` reg ➜ $79 | 🤝 `x13` reg ➜ $80 | 🤝 `x12` reg ➜ a82$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $80 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $80 to register 13
        add     x13, x14, x12  # Addition Operation - $80 = $79 + a82$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $81 = $80 + a83$1
        # 
# 🤙🏼 Calling getReg() for $81 = $80 + a83$1
        #  🔵 Already in register - $80 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a83$1 to register 12
        lw      x12, -348(fp)  # Load Local Var - a83$1 via fp in x12
        #  🍊 Giving $81 same reg as given to $80 since it not used again
        # 
# 👋 GetReg() for $81 = $80 + a83$1 | 🤝 `x13` reg ➜ $80 | 🤝 `x13` reg ➜ $81 | 🤝 `x12` reg ➜ a83$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $81 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $81 to register 13
        add     x13, x13, x12  # Addition Operation - $81 = $80 + a83$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $82 = $81 + a84$1
        # 
# 🤙🏼 Calling getReg() for $82 = $81 + a84$1
        #  🔵 Already in register - $81 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a84$1 to register 12
        lw      x12, -352(fp)  # Load Local Var - a84$1 via fp in x12
        sw      x14, -736(fp)  # Store Local Var - $78 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $78 in memory
        sw      x14, -740(fp)  # Store Local Var - $79 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $79 in memory
        # 
# 👋 GetReg() for $82 = $81 + a84$1 | 🤝 `x13` reg ➜ $81 | 🤝 `x14` reg ➜ $82 | 🤝 `x12` reg ➜ a84$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $82 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $82 to register 14
        add     x14, x13, x12  # Addition Operation - $82 = $81 + a84$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $83 = $82 + a85$1
        # 
# 🤙🏼 Calling getReg() for $83 = $82 + a85$1
        #  🔵 Already in register - $82 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a85$1 to register 12
        lw      x12, -356(fp)  # Load Local Var - a85$1 via fp in x12
        #  🍊 Giving $83 same reg as given to $82 since it not used again
        # 
# 👋 GetReg() for $83 = $82 + a85$1 | 🤝 `x14` reg ➜ $82 | 🤝 `x14` reg ➜ $83 | 🤝 `x12` reg ➜ a85$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $83 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $83 to register 14
        add     x14, x14, x12  # Addition Operation - $83 = $82 + a85$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $84 = $83 + a86$1
        # 
# 🤙🏼 Calling getReg() for $84 = $83 + a86$1
        #  🔵 Already in register - $83 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a86$1 to register 12
        lw      x12, -360(fp)  # Load Local Var - a86$1 via fp in x12
        sw      x13, -744(fp)  # Store Local Var - $80 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $80 in memory
        sw      x13, -748(fp)  # Store Local Var - $81 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $81 in memory
        # 
# 👋 GetReg() for $84 = $83 + a86$1 | 🤝 `x14` reg ➜ $83 | 🤝 `x13` reg ➜ $84 | 🤝 `x12` reg ➜ a86$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $84 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $84 to register 13
        add     x13, x14, x12  # Addition Operation - $84 = $83 + a86$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $85 = $84 + a87$1
        # 
# 🤙🏼 Calling getReg() for $85 = $84 + a87$1
        #  🔵 Already in register - $84 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a87$1 to register 12
        lw      x12, -364(fp)  # Load Local Var - a87$1 via fp in x12
        #  🍊 Giving $85 same reg as given to $84 since it not used again
        # 
# 👋 GetReg() for $85 = $84 + a87$1 | 🤝 `x13` reg ➜ $84 | 🤝 `x13` reg ➜ $85 | 🤝 `x12` reg ➜ a87$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $85 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $85 to register 13
        add     x13, x13, x12  # Addition Operation - $85 = $84 + a87$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $86 = $85 + a88$1
        # 
# 🤙🏼 Calling getReg() for $86 = $85 + a88$1
        #  🔵 Already in register - $85 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a88$1 to register 12
        lw      x12, -368(fp)  # Load Local Var - a88$1 via fp in x12
        sw      x14, -752(fp)  # Store Local Var - $82 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $82 in memory
        sw      x14, -756(fp)  # Store Local Var - $83 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $83 in memory
        # 
# 👋 GetReg() for $86 = $85 + a88$1 | 🤝 `x13` reg ➜ $85 | 🤝 `x14` reg ➜ $86 | 🤝 `x12` reg ➜ a88$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $86 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $86 to register 14
        add     x14, x13, x12  # Addition Operation - $86 = $85 + a88$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $87 = $86 + a89$1
        # 
# 🤙🏼 Calling getReg() for $87 = $86 + a89$1
        #  🔵 Already in register - $86 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a89$1 to register 12
        lw      x12, -372(fp)  # Load Local Var - a89$1 via fp in x12
        #  🍊 Giving $87 same reg as given to $86 since it not used again
        # 
# 👋 GetReg() for $87 = $86 + a89$1 | 🤝 `x14` reg ➜ $86 | 🤝 `x14` reg ➜ $87 | 🤝 `x12` reg ➜ a89$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $87 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $87 to register 14
        add     x14, x14, x12  # Addition Operation - $87 = $86 + a89$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $88 = $87 + a90$1
        # 
# 🤙🏼 Calling getReg() for $88 = $87 + a90$1
        #  🔵 Already in register - $87 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a90$1 to register 12
        lw      x12, -376(fp)  # Load Local Var - a90$1 via fp in x12
        sw      x13, -760(fp)  # Store Local Var - $84 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $84 in memory
        sw      x13, -764(fp)  # Store Local Var - $85 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $85 in memory
        # 
# 👋 GetReg() for $88 = $87 + a90$1 | 🤝 `x14` reg ➜ $87 | 🤝 `x13` reg ➜ $88 | 🤝 `x12` reg ➜ a90$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $88 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $88 to register 13
        add     x13, x14, x12  # Addition Operation - $88 = $87 + a90$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $89 = $88 + a91$1
        # 
# 🤙🏼 Calling getReg() for $89 = $88 + a91$1
        #  🔵 Already in register - $88 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a91$1 to register 12
        lw      x12, -380(fp)  # Load Local Var - a91$1 via fp in x12
        #  🍊 Giving $89 same reg as given to $88 since it not used again
        # 
# 👋 GetReg() for $89 = $88 + a91$1 | 🤝 `x13` reg ➜ $88 | 🤝 `x13` reg ➜ $89 | 🤝 `x12` reg ➜ a91$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $89 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $89 to register 13
        add     x13, x13, x12  # Addition Operation - $89 = $88 + a91$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $90 = $89 + a92$1
        # 
# 🤙🏼 Calling getReg() for $90 = $89 + a92$1
        #  🔵 Already in register - $89 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a92$1 to register 12
        lw      x12, -384(fp)  # Load Local Var - a92$1 via fp in x12
        sw      x14, -768(fp)  # Store Local Var - $86 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $86 in memory
        sw      x14, -772(fp)  # Store Local Var - $87 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $87 in memory
        # 
# 👋 GetReg() for $90 = $89 + a92$1 | 🤝 `x13` reg ➜ $89 | 🤝 `x14` reg ➜ $90 | 🤝 `x12` reg ➜ a92$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $90 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $90 to register 14
        add     x14, x13, x12  # Addition Operation - $90 = $89 + a92$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $91 = $90 + a93$1
        # 
# 🤙🏼 Calling getReg() for $91 = $90 + a93$1
        #  🔵 Already in register - $90 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a93$1 to register 12
        lw      x12, -388(fp)  # Load Local Var - a93$1 via fp in x12
        #  🍊 Giving $91 same reg as given to $90 since it not used again
        # 
# 👋 GetReg() for $91 = $90 + a93$1 | 🤝 `x14` reg ➜ $90 | 🤝 `x14` reg ➜ $91 | 🤝 `x12` reg ➜ a93$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $91 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $91 to register 14
        add     x14, x14, x12  # Addition Operation - $91 = $90 + a93$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $92 = $91 + a94$1
        # 
# 🤙🏼 Calling getReg() for $92 = $91 + a94$1
        #  🔵 Already in register - $91 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a94$1 to register 12
        lw      x12, -392(fp)  # Load Local Var - a94$1 via fp in x12
        sw      x13, -776(fp)  # Store Local Var - $88 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $88 in memory
        sw      x13, -780(fp)  # Store Local Var - $89 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $89 in memory
        # 
# 👋 GetReg() for $92 = $91 + a94$1 | 🤝 `x14` reg ➜ $91 | 🤝 `x13` reg ➜ $92 | 🤝 `x12` reg ➜ a94$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $92 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $92 to register 13
        add     x13, x14, x12  # Addition Operation - $92 = $91 + a94$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $93 = $92 + a95$1
        # 
# 🤙🏼 Calling getReg() for $93 = $92 + a95$1
        #  🔵 Already in register - $92 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a95$1 to register 12
        lw      x12, -396(fp)  # Load Local Var - a95$1 via fp in x12
        #  🍊 Giving $93 same reg as given to $92 since it not used again
        # 
# 👋 GetReg() for $93 = $92 + a95$1 | 🤝 `x13` reg ➜ $92 | 🤝 `x13` reg ➜ $93 | 🤝 `x12` reg ➜ a95$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $93 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $93 to register 13
        add     x13, x13, x12  # Addition Operation - $93 = $92 + a95$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $94 = $93 + a96$1
        # 
# 🤙🏼 Calling getReg() for $94 = $93 + a96$1
        #  🔵 Already in register - $93 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a96$1 to register 12
        lw      x12, -400(fp)  # Load Local Var - a96$1 via fp in x12
        sw      x14, -784(fp)  # Store Local Var - $90 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $90 in memory
        sw      x14, -788(fp)  # Store Local Var - $91 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $91 in memory
        # 
# 👋 GetReg() for $94 = $93 + a96$1 | 🤝 `x13` reg ➜ $93 | 🤝 `x14` reg ➜ $94 | 🤝 `x12` reg ➜ a96$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $94 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $94 to register 14
        add     x14, x13, x12  # Addition Operation - $94 = $93 + a96$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $95 = $94 + a97$1
        # 
# 🤙🏼 Calling getReg() for $95 = $94 + a97$1
        #  🔵 Already in register - $94 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a97$1 to register 12
        lw      x12, -404(fp)  # Load Local Var - a97$1 via fp in x12
        #  🍊 Giving $95 same reg as given to $94 since it not used again
        # 
# 👋 GetReg() for $95 = $94 + a97$1 | 🤝 `x14` reg ➜ $94 | 🤝 `x14` reg ➜ $95 | 🤝 `x12` reg ➜ a97$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $95 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $95 to register 14
        add     x14, x14, x12  # Addition Operation - $95 = $94 + a97$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $96 = $95 + a98$1
        # 
# 🤙🏼 Calling getReg() for $96 = $95 + a98$1
        #  🔵 Already in register - $95 in 14
        # 💛 SYM_RECORD 💛 - Adding 🌕 a98$1 to register 12
        lw      x12, -408(fp)  # Load Local Var - a98$1 via fp in x12
        sw      x13, -792(fp)  # Store Local Var - $92 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $92 in memory
        sw      x13, -796(fp)  # Store Local Var - $93 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $93 in memory
        # 
# 👋 GetReg() for $96 = $95 + a98$1 | 🤝 `x14` reg ➜ $95 | 🤝 `x13` reg ➜ $96 | 🤝 `x12` reg ➜ a98$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $96 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $96 to register 13
        add     x13, x14, x12  # Addition Operation - $96 = $95 + a98$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $97 = $96 + a99$1
        # 
# 🤙🏼 Calling getReg() for $97 = $96 + a99$1
        #  🔵 Already in register - $96 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a99$1 to register 12
        lw      x12, -412(fp)  # Load Local Var - a99$1 via fp in x12
        #  🍊 Giving $97 same reg as given to $96 since it not used again
        # 
# 👋 GetReg() for $97 = $96 + a99$1 | 🤝 `x13` reg ➜ $96 | 🤝 `x13` reg ➜ $97 | 🤝 `x12` reg ➜ a99$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $97 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $97 to register 13
        add     x13, x13, x12  # Addition Operation - $97 = $96 + a99$1
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $98 = $97 + a100$1
        # 
# 🤙🏼 Calling getReg() for $98 = $97 + a100$1
        #  🔵 Already in register - $97 in 13
        # 💛 SYM_RECORD 💛 - Adding 🌕 a100$1 to register 12
        lw      x12, -416(fp)  # Load Local Var - a100$1 via fp in x12
        sw      x14, -800(fp)  # Store Local Var - $94 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $94 in memory
        sw      x14, -804(fp)  # Store Local Var - $95 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $95 in memory
        # 
# 👋 GetReg() for $98 = $97 + a100$1 | 🤝 `x13` reg ➜ $97 | 🤝 `x14` reg ➜ $98 | 🤝 `x12` reg ➜ a100$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $98 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $98 to register 14
        add     x14, x13, x12  # Addition Operation - $98 = $97 + a100$1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - sum$1 = $98
        # 
# 🤙🏼 Calling getReg() for sum$1 = $98
        #  🔵 Already in register - $98 in 14
        #  🍊 Giving sum$1 same reg as given to $98 due to ASSIGN-OP
        # 
# 👋 GetReg() for sum$1 = $98 | 🤝 `x14` reg ➜ $98 | 🤝 `x14` reg ➜ sum$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 sum$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 sum$1 to register 14
        #  🔄 Automatic copy - of $98 into (sum$1)
        # 
# ‼️ TAC ❗️ ➔ Param - param sum$1
        # Adding sum$1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $99 = call printVar, 1
        mv      a0, x14        # Move argument - sum$1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x13, -808(fp)  # Store Local Var - $96 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $96 in memory
        sw      x13, -812(fp)  # Store Local Var - $97 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $97 in memory
        sw      x14, -816(fp)  # Store Local Var - $98 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $98 in memory
        sw      x14, -420(fp)  # Store Local Var - sum$1 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 sum$1 in memory
        sw      x15, -32(fp)   # Store Local Var - a4$1 via fp in x15
        # 💛 SYM_RECORD 💛 - Setting 🟢 a4$1 in memory
        sw      x16, -36(fp)   # Store Local Var - a5$1 via fp in x16
        # 💛 SYM_RECORD 💛 - Setting 🟢 a5$1 in memory
        sw      x17, -40(fp)   # Store Local Var - a6$1 via fp in x17
        # 💛 SYM_RECORD 💛 - Setting 🟢 a6$1 in memory
        sw      x18, -44(fp)   # Store Local Var - a7$1 via fp in x18
        # 💛 SYM_RECORD 💛 - Setting 🟢 a7$1 in memory
        sw      x19, -48(fp)   # Store Local Var - a8$1 via fp in x19
        # 💛 SYM_RECORD 💛 - Setting 🟢 a8$1 in memory
        sw      x20, -52(fp)   # Store Local Var - a9$1 via fp in x20
        # 💛 SYM_RECORD 💛 - Setting 🟢 a9$1 in memory
        sw      x21, -56(fp)   # Store Local Var - a10$1 via fp in x21
        # 💛 SYM_RECORD 💛 - Setting 🟢 a10$1 in memory
        sw      x22, -60(fp)   # Store Local Var - a11$1 via fp in x22
        # 💛 SYM_RECORD 💛 - Setting 🟢 a11$1 in memory
        sw      x23, -64(fp)   # Store Local Var - a12$1 via fp in x23
        # 💛 SYM_RECORD 💛 - Setting 🟢 a12$1 in memory
        sw      x24, -68(fp)   # Store Local Var - a13$1 via fp in x24
        # 💛 SYM_RECORD 💛 - Setting 🟢 a13$1 in memory
        sw      x25, -72(fp)   # Store Local Var - a14$1 via fp in x25
        # 💛 SYM_RECORD 💛 - Setting 🟢 a14$1 in memory
        sw      x26, -76(fp)   # Store Local Var - a15$1 via fp in x26
        # 💛 SYM_RECORD 💛 - Setting 🟢 a15$1 in memory
        sw      x27, -80(fp)   # Store Local Var - a16$1 via fp in x27
        # 💛 SYM_RECORD 💛 - Setting 🟢 a16$1 in memory
        sw      x28, -84(fp)   # Store Local Var - a17$1 via fp in x28
        # 💛 SYM_RECORD 💛 - Setting 🟢 a17$1 in memory
        sw      x29, -88(fp)   # Store Local Var - a18$1 via fp in x29
        # 💛 SYM_RECORD 💛 - Setting 🟢 a18$1 in memory
        sw      x30, -92(fp)   # Store Local Var - a19$1 via fp in x30
        # 💛 SYM_RECORD 💛 - Setting 🟢 a19$1 in memory
        sw      x31, -96(fp)   # Store Local Var - a20$1 via fp in x31
        # 💛 SYM_RECORD 💛 - Setting 🟢 a20$1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, printVar   # Call function - printVar
        sw      a0, -820(fp)   # Store return value in caller's stack for - $99
        # 💛 SYM_RECORD 💛 - Setting 🚫 $99 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $99 in memory
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 816(sp)    # Restore return address (PC)
        lw      fp, 812(sp)    # Restore old frame pointer
        addi    sp, sp, 820    # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


