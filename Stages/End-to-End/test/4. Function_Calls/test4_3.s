#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:57:45) 🎨 ---------

.data

.text
        # #define <stdio.h> NOT INCLUDED
        bar:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block bar
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - bar
        addi    sp, sp, -24    # Allocating Stack Space
        sw      ra, 20(sp)     # Store return address (PC)
        sw      fp, 16(sp)     # Store old frame pointer
        addi    fp, sp,24      # Set new frame pointer
        sw      a0, -20(fp)    # Store argument 0 in stack
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a$1 + 1
        # 
# 🤙🏼 Calling getReg() for $0 = a$1 + 1
        #  🟢 Found Free Register - 12 for a$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - a$1 via fp in x12
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = a$1 + 1 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        add     x13, x12, t1   # Addition Operation - $0 = a$1 + 1
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $0
        # 
# 🤙🏼 Calling getReg() for return $0
        #  🔵 Already in register - $0 in 13
        # 
# 👋 GetReg() for return $0 | 🤝 `x13` reg ➜ $0 |
        mv      a1, x13        # Move return value's reg - x13 to a1
        #  -- EXIT Activation (start) - bar
        #  🫟 Spilling Code 🫟  due to ➢ End of Function bar
        sw      x13, -24(fp)   # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 20(sp)     # Restore return address (PC)
        lw      fp, 16(sp)     # Restore old frame pointer
        addi    sp, sp, 24     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - bar
        foo:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block foo
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - foo
        addi    sp, sp, -28    # Allocating Stack Space
        sw      ra, 24(sp)     # Store return address (PC)
        sw      fp, 20(sp)     # Store old frame pointer
        addi    fp, sp,28      # Set new frame pointer
        sw      a0, -20(fp)    # Store argument 0 in stack
        # 
# ‼️ TAC ❗️ ➔ Param - param b$2
        # Adding b$2 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $1 = call bar, 1
        lw      t2, -20(fp)    # Load Local Var - b$2 via fp in t2
        mv      a0, t2         # Move argument - b$2 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, bar        # Call function - bar
        sw      a0, -24(fp)    # Store return value in caller's stack for - $1
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $2 = $1 << 1
        # 
# 🤙🏼 Calling getReg() for $2 = $1 << 1
        #  🟢 Found Free Register - 12 for $1
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        lw      x12, -24(fp)   # Load Local Var - $1 via fp in x12
        #  🍊 Giving $2 same reg as given to $1 since it not used again
        # 
# 👋 GetReg() for $2 = $1 << 1 | 🤝 `x12` reg ➜ $1 | 🤝 `x12` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        sll     x12, x12, t1   # Left Shift Operation - $2 = $1<< 1
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $2
        # 
# 🤙🏼 Calling getReg() for return $2
        #  🔵 Already in register - $2 in 12
        # 
# 👋 GetReg() for return $2 | 🤝 `x12` reg ➜ $2 |
        mv      a1, x12        # Move return value's reg - x12 to a1
        #  -- EXIT Activation (start) - foo
        #  🫟 Spilling Code 🫟  due to ➢ End of Function foo
        sw      x12, -28(fp)   # Store Local Var - $2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 24(sp)     # Restore return address (PC)
        lw      fp, 20(sp)     # Restore old frame pointer
        addi    sp, sp, 28     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - foo
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -24    # Allocating Stack Space
        sw      ra, 20(sp)     # Store return address (PC)
        sw      fp, 16(sp)     # Store old frame pointer
        addi    fp, sp,24      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Param - param 5
        # Adding 5 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $3 = call foo, 1
        li      a0, 5          # Load argument - 5 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal     x1, foo        # Call function - foo
        sw      a0, -24(fp)    # Store return value in caller's stack for - $3
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - result$3 = $3
        # 
# 🤙🏼 Calling getReg() for result$3 = $3
        #  🟢 Found Free Register - 12 for $3
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 12
        lw      x12, -24(fp)   # Load Local Var - $3 via fp in x12
        #  🍊 Giving result$3 same reg as given to $3 due to ASSIGN-OP
        # 
# 👋 GetReg() for result$3 = $3 | 🤝 `x12` reg ➜ $3 | 🤝 `x12` reg ➜ result$3 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 result$3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 result$3 to register 12
        #  🔄 Automatic copy - of $3 into (result$3)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        sw      x12, -20(fp)   # Store Local Var - result$3 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 result$3 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 20(sp)     # Restore return address (PC)
        lw      fp, 16(sp)     # Restore old frame pointer
        addi    sp, sp, 24     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


