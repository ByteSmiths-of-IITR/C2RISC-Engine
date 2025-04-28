#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:57:44) 🎨 ---------

.data

.text
        # #define <stdio.h> NOT INCLUDED
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
        #  -- EXIT Activation (start) - foo
        #  🫟 Spilling Code 🫟  due to ➢ End of Function foo
        sw      x14, -28(fp)   # Store Local Var - $0 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
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
        addi    sp, sp, -32    # Allocating Stack Space
        sw      ra, 28(sp)     # Store return address (PC)
        sw      fp, 24(sp)     # Store old frame pointer
        addi    fp, sp,32      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$2 = 5
        # 
# 🤙🏼 Calling getReg() for a$2 = 5
        #  🟢 Found Free Register - 12 for a$2
        # 
# 👋 GetReg() for a$2 = 5 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ a$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$2 to register 12
        li      x12, 5         # Load constant - 5 into x12(a$2)
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
# ‼️ TAC ❗️ ➔ Function Call - $1 = call foo, 2
        mv      a0, x12        # Move argument - a$2 into a0
        mv      a1, x13        # Move argument - b$2 into a1
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -20(fp)   # Store Local Var - a$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$2 in memory
        sw      x13, -24(fp)   # Store Local Var - b$2 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$2 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, foo        # Call function - foo
        sw      a0, -32(fp)    # Store return value in caller's stack for - $1
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - c$2 = $1
        # 
# 🤙🏼 Calling getReg() for c$2 = $1
        #  🟢 Found Free Register - 12 for $1
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        lw      x12, -32(fp)   # Load Local Var - $1 via fp in x12
        #  🍊 Giving c$2 same reg as given to $1 due to ASSIGN-OP
        # 
# 👋 GetReg() for c$2 = $1 | 🤝 `x12` reg ➜ $1 | 🤝 `x12` reg ➜ c$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 c$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$2 to register 12
        #  🔄 Automatic copy - of $1 into (c$2)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        sw      x12, -28(fp)   # Store Local Var - c$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 c$2 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 28(sp)     # Restore return address (PC)
        lw      fp, 24(sp)     # Restore old frame pointer
        addi    sp, sp, 32     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


