#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-28 - 22:45:58) 🎨 ---------

.data

.text
        main:
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi  sp, sp, -40      # Allocating Stack Space
        sw    ra, 36(sp)       # Store return address (PC)
        sw    fp, 32(sp)       # Store old frame pointer
        addi  fp, sp,40        # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $0 = &a$1
        #  🟢 Found Free Register - 12 for $0
        #  🙋🏼 GetReg() for $0 = &a$1 | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 12
        addi  x12, fp, -20     # Load address of variable (via fp) - a$1 into x12
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - p$1 = $0
        #  🔵 Already in register - $0 in 12
        #  🍊 Giving p$1 same reg as given to $0 due to ASSIGN-OP
        #  🙋🏼 GetReg() for p$1 = $0 | 🤝 `x12` reg ➜ $0 | 🤝 `x12` reg ➜ p$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 p$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 p$1 to register 12
        #  🔄 Automatic copy - of $0 into (p$1)
        # 
# ‼️ TAC ❗️ ➔  Ampersend (&) - $1 = &p$1
        #  🟢 Found Free Register - 13 for $1
        #  🙋🏼 GetReg() for $1 = &p$1 | 🤝 `x13` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 13
        addi  x13, fp, -24     # Load address of variable (via fp) - p$1 into x13
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - pp$1 = $1
        #  🔵 Already in register - $1 in 13
        #  🍊 Giving pp$1 same reg as given to $1 due to ASSIGN-OP
        #  🙋🏼 GetReg() for pp$1 = $1 | 🤝 `x13` reg ➜ $1 | 🤝 `x13` reg ➜ pp$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 pp$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 pp$1 to register 13
        #  🔄 Automatic copy - of $1 into (pp$1)
        # 
# ‼️ TAC ❗️ ➔ Right Star ✨ - $2 = (4)*pp$1
        #  🔵 Already in register - pp$1 in 13
        #  🟢 Found Free Register - 14 for $2
        #  🙋🏼 GetReg() for $2 = (4)*pp$1 | 🤝 `x14` reg ➜ $2 | 🤝 `x0` reg ➜ NULL | 🤝 `x13` reg ➜ pp$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 14
        lw    x14, 0(x13)      # Load reg x13 with value at address pointed by x14
        # 
# ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$2 = 10
        #  🔵 Already in register - $2 in 14
        #  🙋🏼 GetReg() for (4)*$2 = 10 | 🤝 `x14` reg ➜ $2 |
        li    t0, 10           # Load constant - 10 into t0
        sw    t0, 0(x14)       # Store constant of reg t0 at address pointed by x14
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟 
        sw    x12, -28(fp)     # Store Local Var - $0 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        sw    x12, -24(fp)     # Store Local Var - p$1 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 p$1 in memory
        sw    x13, -36(fp)     # Store Local Var - $1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        sw    x13, -32(fp)     # Store Local Var - pp$1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 pp$1 in memory
        sw    x14, -40(fp)     # Store Local Var - $2 via fp in x14
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 36(sp)       # Restore return address (PC)
        lw    fp, 32(sp)       # Restore old frame pointer
        addi  sp, sp, 40       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟 
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


