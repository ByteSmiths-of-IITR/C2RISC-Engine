#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:57:41) 🎨 ---------

.data
        fVar_0:     .float 220.500000

.text
        # #define <stdio.h> NOT INCLUDED
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
# ‼️ TAC ❗️ ➔ Offset Load - $0 = data$1.offset
        # 
# 🤙🏼 Calling getReg() for $0 = data$1.offset
        #  🟢 Found Free Register - 12 for $0
        # 
# 👋 GetReg() for $0 = data$1.offset | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 12
        addi    x12, fp, -20   # Load address of variable (via fp) - data$1 into x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $1 = $0
        # 
# 🤙🏼 Calling getReg() for $1 = $0
        #  🔵 Already in register - $0 in 12
        #  🍊 Giving $1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for $1 = $0 | 🤝 `x12` reg ➜ $0 | 🤝 `x12` reg ➜ $1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        #  🔄 Automatic copy - of $0 into ($1)
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$1 = 10
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -24(fp)   # Store Local Var - $0 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x12, -28(fp)   # Store Local Var - $1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$1 = 10
        #  🟢 Found Free Register - 12 for $1
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        lw      x12, -28(fp)   # Load Local Var - $1 via fp in x12
        # 
# 👋 GetReg() for (4)*$1 = 10 | 🤝 `x12` reg ➜ $1 |
        li      t0, 10         # Load constant - 10 into t0
        sw      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $2 = data$1.offset
        # 
# 🤙🏼 Calling getReg() for $2 = data$1.offset
        #  🟢 Found Free Register - 13 for $2
        # 
# 👋 GetReg() for $2 = data$1.offset | 🤝 `x13` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 13
        addi    x13, fp, -20   # Load address of variable (via fp) - data$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $3 = $2
        # 
# 🤙🏼 Calling getReg() for $3 = $2
        #  🔵 Already in register - $2 in 13
        #  🍊 Giving $3 same reg as given to $2 due to ASSIGN-OP
        # 
# 👋 GetReg() for $3 = $2 | 🤝 `x13` reg ➜ $2 | 🤝 `x13` reg ➜ $3 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        #  🔄 Automatic copy - of $2 into ($3)
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$3 = fVar_0
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -32(fp)   # Store Local Var - $2 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x13, -36(fp)   # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$3 = fVar_0
        #  🟢 Found Free Register - 12 for fVar_0
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_0 to register 12
        la      t0, fVar_0     # Loading Address of Global Variable - fVar_0
        flw     x12, 0(t0)     # Load Global Var - fVar_0 via t0 in xx12
        #  🟢 Found Free Register - 13 for $3
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        lw      x13, -36(fp)   # Load Local Var - $3 via fp in x13
        # 
# 👋 GetReg() for (4)*$3 = fVar_0 | 🤝 `x13` reg ➜ $3 | 🤝 `x12` reg ➜ fVar_0 |
        sw      x12, 0(x13)    # Store variable of reg x12 at address pointed by x13
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $4 = data$1.offset
        # 
# 🤙🏼 Calling getReg() for $4 = data$1.offset
        #  🟢 Found Free Register - 14 for $4
        # 
# 👋 GetReg() for $4 = data$1.offset | 🤝 `x14` reg ➜ $4 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 14
        addi    x14, fp, -20   # Load address of variable (via fp) - data$1 into x14
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - $5 = $4
        # 
# 🤙🏼 Calling getReg() for $5 = $4
        #  🔵 Already in register - $4 in 14
        #  🍊 Giving $5 same reg as given to $4 due to ASSIGN-OP
        # 
# 👋 GetReg() for $5 = $4 | 🤝 `x14` reg ➜ $4 | 🤝 `x14` reg ➜ $5 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 14
        #  🔄 Automatic copy - of $4 into ($5)
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (1)*$5 = A
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x14, -40(fp)   # Store Local Var - $4 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        sw      x14, -44(fp)   # Store Local Var - $5 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (1)*$5 = A
        #  🟢 Found Free Register - 12 for $5
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 12
        lw      x12, -44(fp)   # Load Local Var - $5 via fp in x12
        # 
# 👋 GetReg() for (1)*$5 = A | 🤝 `x12` reg ➜ $5 |
        li      t0, A          # Load constant - A into t0
        sb      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 40(sp)     # Restore return address (PC)
        lw      fp, 36(sp)     # Restore old frame pointer
        addi    sp, sp, 44     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


