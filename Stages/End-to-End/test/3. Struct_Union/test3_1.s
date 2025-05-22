#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:57:41) 🎨 ---------

.data
        fVar_0:     .float   2.000000
        fVar_1:     .float   4.000000

.text
        # #define <stdio.h> NOT INCLUDED
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -64    # Allocating Stack Space
        sw      ra, 60(sp)     # Store return address (PC)
        sw      fp, 56(sp)     # Store old frame pointer
        addi    fp, sp,64      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $0 = a$1.offset
        # 
# 🤙🏼 Calling getReg() for $0 = a$1.offset
        #  🟢 Found Free Register - 12 for $0
        # 
# 👋 GetReg() for $0 = a$1.offset | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 12
        addi    x12, fp, -24   # Load address of variable (via fp) - a$1 into x12
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
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$1 = 1
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x12, -36(fp)   # Store Local Var - $0 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw      x12, -40(fp)   # Store Local Var - $1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$1 = 1
        #  🟢 Found Free Register - 12 for $1
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 12
        lw      x12, -40(fp)   # Load Local Var - $1 via fp in x12
        # 
# 👋 GetReg() for (4)*$1 = 1 | 🤝 `x12` reg ➜ $1 |
        li      t0, 1          # Load constant - 1 into t0
        sw      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $2 = a$1.offset
        # 
# 🤙🏼 Calling getReg() for $2 = a$1.offset
        #  🟢 Found Free Register - 13 for $2
        # 
# 👋 GetReg() for $2 = a$1.offset | 🤝 `x13` reg ➜ $2 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 13
        addi    x13, fp, -24   # Load address of variable (via fp) - a$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = $2 + 4
        # 
# 🤙🏼 Calling getReg() for $3 = $2 + 4
        #  🔵 Already in register - $2 in 13
        #  🍊 Giving $3 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $3 = $2 + 4 | 🤝 `x13` reg ➜ $2 | 🤝 `x13` reg ➜ $3 | 🤝 `x0` reg ➜ NULL |
        li      t1, 4          # Loading Immediate Value - 4 in x13
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        add     x13, x13, t1   # Addition Operation - $3 = $2 + 4
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$3 = fVar_0
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -44(fp)   # Store Local Var - $2 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        sw      x13, -48(fp)   # Store Local Var - $3 via fp in x13
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
        lw      x13, -48(fp)   # Load Local Var - $3 via fp in x13
        # 
# 👋 GetReg() for (4)*$3 = fVar_0 | 🤝 `x13` reg ➜ $3 | 🤝 `x12` reg ➜ fVar_0 |
        sw      x12, 0(x13)    # Store variable of reg x12 at address pointed by x13
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $4 = b$1.offset
        # 
# 🤙🏼 Calling getReg() for $4 = b$1.offset
        #  🟢 Found Free Register - 14 for $4
        # 
# 👋 GetReg() for $4 = b$1.offset | 🤝 `x14` reg ➜ $4 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 14
        addi    x14, fp, -32   # Load address of variable (via fp) - b$1 into x14
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
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$5 = 3
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x14, -52(fp)   # Store Local Var - $4 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        sw      x14, -56(fp)   # Store Local Var - $5 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$5 = 3
        #  🟢 Found Free Register - 12 for $5
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 12
        lw      x12, -56(fp)   # Load Local Var - $5 via fp in x12
        # 
# 👋 GetReg() for (4)*$5 = 3 | 🤝 `x12` reg ➜ $5 |
        li      t0, 3          # Load constant - 3 into t0
        sw      t0, 0(x12)     # Store constant of reg t0 at address pointed by x12
        # 
# ‼️ TAC ❗️ ➔ Offset Load - $6 = b$1.offset
        # 
# 🤙🏼 Calling getReg() for $6 = b$1.offset
        #  🟢 Found Free Register - 13 for $6
        # 
# 👋 GetReg() for $6 = b$1.offset | 🤝 `x13` reg ➜ $6 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $6 to register 13
        addi    x13, fp, -32   # Load address of variable (via fp) - b$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $7 = $6 + 4
        # 
# 🤙🏼 Calling getReg() for $7 = $6 + 4
        #  🔵 Already in register - $6 in 13
        #  🍊 Giving $7 same reg as given to $6 since it not used again
        # 
# 👋 GetReg() for $7 = $6 + 4 | 🤝 `x13` reg ➜ $6 | 🤝 `x13` reg ➜ $7 | 🤝 `x0` reg ➜ NULL |
        li      t1, 4          # Loading Immediate Value - 4 in x13
        # 💛 SYM_RECORD 💛 - Setting 🚫 $7 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 13
        add     x13, x13, t1   # Addition Operation - $7 = $6 + 4
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$7 = fVar_1
        #  🫟 Spilling Code 🫟  due to ➢ 😱 Someone touched addressSpace ☄️
        sw      x13, -60(fp)   # Store Local Var - $6 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        sw      x13, -64(fp)   # Store Local Var - $7 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $7 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# 🤙🏼 Calling getReg() for (4)*$7 = fVar_1
        #  🟢 Found Free Register - 12 for fVar_1
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_1 to register 12
        la      t0, fVar_1     # Loading Address of Global Variable - fVar_1
        flw     x12, 0(t0)     # Load Global Var - fVar_1 via t0 in xx12
        #  🟢 Found Free Register - 13 for $7
        # 💛 SYM_RECORD 💛 - Adding 🌕 $7 to register 13
        lw      x13, -64(fp)   # Load Local Var - $7 via fp in x13
        # 
# 👋 GetReg() for (4)*$7 = fVar_1 | 🤝 `x13` reg ➜ $7 | 🤝 `x12` reg ➜ fVar_1 |
        sw      x12, 0(x13)    # Store variable of reg x12 at address pointed by x13
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 60(sp)     # Restore return address (PC)
        lw      fp, 56(sp)     # Restore old frame pointer
        addi    sp, sp, 64     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


