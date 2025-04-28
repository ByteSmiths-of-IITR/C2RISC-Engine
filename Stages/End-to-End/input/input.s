#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 01:09:16) 🎨 ---------

.data

.text
        factorial:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block factorial
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - factorial
        addi  sp, sp, -36      # Allocating Stack Space
        sw    ra, 32(sp)       # Store return address (PC)
        sw    fp, 28(sp)       # Store old frame pointer
        addi  fp, sp,36        # Set new frame pointer
        sw    a0, -20(fp)      # Store argument 0 in stack
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = n$1 == 0
        # 
# 🤙🏼 Calling getReg() for $0 = n$1 == 0
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw    x12, -20(fp)     # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = n$1 == 0 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li    t1, 0            # Loading Immediate Value - 0 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        sub   t1, x12, t1      # Part1 of Equality Operation - $0 = n$1 == 0
        seqz  x13, t1          # Part2 of Equality Operation - $0 = n$1 == 0
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $0 goto L(Block_0)
        # 
# 🤙🏼 Calling getReg() for if $0 goto L(Block_0)
        #  🔵 Already in register - $0 in 13
        # 
# 👋 GetReg() for if $0 goto L(Block_0) | 🤝 `x13` reg ➜ $0 |
        bne   x13, x0, Block_0 # Jump to label - Block_0 if $0 is true
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw    x13, -24(fp)     # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_1)
        j     Block_1          # Unconditional Jump to label - Block_1
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        Block_0:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_0
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 1
        li    t1, 1            # Load constant - 1 into t1
        mv    a1, t1           # Move return value's reg - t1 to a1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        j     Block_2          # Unconditional Jump to label - Block_2
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = n$1 - 1
        # 
# 🤙🏼 Calling getReg() for $1 = n$1 - 1
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw    x12, -20(fp)     # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $1
        # 
# 👋 GetReg() for $1 = n$1 - 1 | 🤝 `x13` reg ➜ $1 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li    t1, 1            # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 13
        sub   x13, x12, t1     # Subtraction Operation - $1 = n$1 - 1
        # 
# ‼️ TAC ❗️ ➔ Param - param $1
        # Adding $1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $2 = call factorial, 1
        mv    a0, x13          # Move argument - $1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw    x13, -28(fp)     # Store Local Var - $1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal   x1, factorial    # Call function - factorial
        sw    a0, -32(fp)      # Store return value in caller's stack for - $2
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = n$1 * $2
        # 
# 🤙🏼 Calling getReg() for $3 = n$1 * $2
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw    x12, -20(fp)     # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $2
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 13
        lw    x13, -32(fp)     # Load Local Var - $2 via fp in x13
        #  🍊 Giving $3 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $3 = n$1 * $2 | 🤝 `x13` reg ➜ $2 | 🤝 `x13` reg ➜ $3 | 🤝 `x12` reg ➜ n$1 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        mul   x13, x12, x13    # Multiplication Operation - $3 = n$1 * $2
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $3
        # 
# 🤙🏼 Calling getReg() for return $3
        #  🔵 Already in register - $3 in 13
        # 
# 👋 GetReg() for return $3 | 🤝 `x13` reg ➜ $3 |
        mv    a1, x13          # Move return value's reg - x13 to a1
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        sw    x13, -36(fp)     # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        #  -- EXIT Activation (start) - factorial
        #  🫟 Spilling Code 🫟  due to ➢ End of Function factorial
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 32(sp)       # Restore return address (PC)
        lw    fp, 28(sp)       # Restore old frame pointer
        addi  sp, sp, 36       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - factorial
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
# ‼️ TAC ❗️ ➔ Param - param 3
        # Adding 3 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $4 = call factorial, 1
        li    a0, 3            # Load argument - 3 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        #  🫗 Finished Spilling Code 👌 
        jal   x1, factorial    # Call function - factorial
        sw    a0, -24(fp)      # Store return value in caller's stack for - $4
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - k$2 = $4
        # 
# 🤙🏼 Calling getReg() for k$2 = $4
        #  🟢 Found Free Register - 12 for $4
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 12
        lw    x12, -24(fp)     # Load Local Var - $4 via fp in x12
        #  🍊 Giving k$2 same reg as given to $4 due to ASSIGN-OP
        # 
# 👋 GetReg() for k$2 = $4 | 🤝 `x12` reg ➜ $4 | 🤝 `x12` reg ➜ k$2 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 k$2 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 k$2 to register 12
        #  🔄 Automatic copy - of $4 into (k$2)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        sw    x12, -20(fp)     # Store Local Var - k$2 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 k$2 in memory
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 20(sp)       # Restore return address (PC)
        lw    fp, 16(sp)       # Restore old frame pointer
        addi  sp, sp, 24       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main

#-------------------------------------------------------------------------


