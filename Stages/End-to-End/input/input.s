#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:28:08) 🎨 ---------

.data
        fVar_0:     .float  12.300000
        fVar_1:     .float   2.300000

.text
        # #define <stdio.h> NOT INCLUDED
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
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - b$1 = fVar_0
        # 
# 🤙🏼 Calling getReg() for b$1 = fVar_0
        #  🟢 Found Free Register - 40 for fVar_0
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_0 to register 40
        la      t0, fVar_0     # Loading Address of Global Variable - fVar_0
        flw     f8, 0(t0)      # Load Global Var - fVar_0 via t0 in xf8
        #  🍊 Giving b$1 same reg as given to fVar_0 due to ASSIGN-OP
        # 
# 👋 GetReg() for b$1 = fVar_0 | 🤝 `f8` reg ➜ b$1 | 🤝 `f8` reg ➜ fVar_0 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 b$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 b$1 to register 40
        #  🔄 Automatic copy - of fVar_0 into (b$1)
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - a$1 = fVar_1
        # 
# 🤙🏼 Calling getReg() for a$1 = fVar_1
        #  🟢 Found Free Register - 41 for fVar_1
        # 💛 SYM_RECORD 💛 - Adding 🌕 fVar_1 to register 41
        la      t0, fVar_1     # Loading Address of Global Variable - fVar_1
        flw     f9, 0(t0)      # Load Global Var - fVar_1 via t0 in xf9
        #  🍊 Giving a$1 same reg as given to fVar_1 due to ASSIGN-OP
        # 
# 👋 GetReg() for a$1 = fVar_1 | 🤝 `f9` reg ➜ a$1 | 🤝 `f9` reg ➜ fVar_1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 a$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 a$1 to register 41
        #  🔄 Automatic copy - of fVar_1 into (a$1)
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = a$1 + b$1
        # 
# 🤙🏼 Calling getReg() for $0 = a$1 + b$1
        #  🔵 Already in register - a$1 in 41
        #  🔵 Already in register - b$1 in 40
        #  🟢 Found Free Register - 42 for $0
        # 
# 👋 GetReg() for $0 = a$1 + b$1 | 🤝 `f10` reg ➜ $0 | 🤝 `f9` reg ➜ a$1 | 🤝 `f8` reg ➜ b$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 42
        fadd.s  f10, f9, f8    # F_Addition Operation - $0 = a$1 + b$1
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - c$1 = $0
        # 
# 🤙🏼 Calling getReg() for c$1 = $0
        #  🔵 Already in register - $0 in 42
        #  🍊 Giving c$1 same reg as given to $0 due to ASSIGN-OP
        # 
# 👋 GetReg() for c$1 = $0 | 🤝 `f10` reg ➜ $0 | 🤝 `f10` reg ➜ c$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 c$1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 c$1 to register 42
        #  🔄 Automatic copy - of $0 into (c$1)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv      a1, x0         # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        fsw     f8, -20(fp)    # Store Local Var - b$1 via fp in f8
        # 💛 SYM_RECORD 💛 - Setting 🟢 b$1 in memory
        fsw     f9, -24(fp)    # Store Local Var - a$1 via fp in f9
        # 💛 SYM_RECORD 💛 - Setting 🟢 a$1 in memory
        fsw     f10, -32(fp)   # Store Local Var - $0 via fp in f10
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        fsw     f10, -28(fp)   # Store Local Var - c$1 via fp in f10
        # 💛 SYM_RECORD 💛 - Setting 🟢 c$1 in memory
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


