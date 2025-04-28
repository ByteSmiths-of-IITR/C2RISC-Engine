#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-29 - 03:57:44) 🎨 ---------

.data

.text
        # #define <stdio.h> NOT INCLUDED
        fibonacci:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block fibonacci
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - fibonacci
        addi    sp, sp, -44    # Allocating Stack Space
        sw      ra, 40(sp)     # Store return address (PC)
        sw      fp, 36(sp)     # Store old frame pointer
        addi    fp, sp,44      # Set new frame pointer
        sw      a0, -20(fp)    # Store argument 0 in stack
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $0 = n$1 <= 1
        # 
# 🤙🏼 Calling getReg() for $0 = n$1 <= 1
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $0
        # 
# 👋 GetReg() for $0 = n$1 <= 1 | 🤝 `x13` reg ➜ $0 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $0 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $0 to register 13
        slt     t1, t1, x12    # Part1 of Less Than Equal Operation - $0 = n$1 <= 1
        xori    x13, t1, 1     # Part2 of Less Than Equal Operation - $0 = n$1 <= 1
        # 
# ‼️ TAC ❗️ ➔ IF_TRUE - if $0 goto L(Block_0)
        # 
# 🤙🏼 Calling getReg() for if $0 goto L(Block_0)
        #  🔵 Already in register - $0 in 13
        # 
# 👋 GetReg() for if $0 goto L(Block_0) | 🤝 `x13` reg ➜ $0 |
        #  🫟 Spilling Code 🫟  due to ➢ Jump due to if_true
        sw      x13, -24(fp)   # Store Local Var - $0 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $0 in memory
        #  🫗 Finished Spilling Code 👌 
        bne     x13, x0, Block_0 # Jump to label - Block_0 if $0 is true
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_1)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_1        # Unconditional Jump to label - Block_1
        Block_0:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_0
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return n$1
        # 
# 🤙🏼 Calling getReg() for return n$1
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        # 
# 👋 GetReg() for return n$1 | 🤝 `x12` reg ➜ n$1 |
        mv      a1, x12        # Move return value's reg - x12 to a1
        # 
# ‼️ TAC ❗️ ➔ GOTO_LABEL - goto L(Block_2)
        #  🫟 Spilling Code 🫟  due to ➢ Jump Due to goto-label
        #  🫗 Finished Spilling Code 👌 
        j       Block_2        # Unconditional Jump to label - Block_2
        Block_1:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_1
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $1 = n$1 - 1
        # 
# 🤙🏼 Calling getReg() for $1 = n$1 - 1
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $1
        # 
# 👋 GetReg() for $1 = n$1 - 1 | 🤝 `x13` reg ➜ $1 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li      t1, 1          # Loading Immediate Value - 1 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $1 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $1 to register 13
        sub     x13, x12, t1   # Subtraction Operation - $1 = n$1 - 1
        # 
# ‼️ TAC ❗️ ➔ Param - param $1
        # Adding $1 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $2 = call fibonacci, 1
        mv      a0, x13        # Move argument - $1 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x13, -28(fp)   # Store Local Var - $1 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $1 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, fibonacci  # Call function - fibonacci
        sw      a0, -32(fp)    # Store return value in caller's stack for - $2
        # 💛 SYM_RECORD 💛 - Setting 🚫 $2 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $2 in memory
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $3 = n$1 - 2
        # 
# 🤙🏼 Calling getReg() for $3 = n$1 - 2
        #  🟢 Found Free Register - 12 for n$1
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$1 to register 12
        lw      x12, -20(fp)   # Load Local Var - n$1 via fp in x12
        #  🟢 Found Free Register - 13 for $3
        # 
# 👋 GetReg() for $3 = n$1 - 2 | 🤝 `x13` reg ➜ $3 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$1 |
        li      t1, 2          # Loading Immediate Value - 2 in x12
        # 💛 SYM_RECORD 💛 - Setting 🚫 $3 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $3 to register 13
        sub     x13, x12, t1   # Subtraction Operation - $3 = n$1 - 2
        # 
# ‼️ TAC ❗️ ➔ Param - param $3
        # Adding $3 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $4 = call fibonacci, 1
        mv      a0, x13        # Move argument - $3 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x13, -36(fp)   # Store Local Var - $3 via fp in x13
        # 💛 SYM_RECORD 💛 - Setting 🟢 $3 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, fibonacci  # Call function - fibonacci
        sw      a0, -40(fp)    # Store return value in caller's stack for - $4
        # 💛 SYM_RECORD 💛 - Setting 🚫 $4 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $4 in memory
        # 
# ‼️ TAC ❗️ ➔ Simple Operation - $5 = $2 + $4
        # 
# 🤙🏼 Calling getReg() for $5 = $2 + $4
        #  🟢 Found Free Register - 12 for $2
        # 💛 SYM_RECORD 💛 - Adding 🌕 $2 to register 12
        lw      x12, -32(fp)   # Load Local Var - $2 via fp in x12
        #  🟢 Found Free Register - 13 for $4
        # 💛 SYM_RECORD 💛 - Adding 🌕 $4 to register 13
        lw      x13, -40(fp)   # Load Local Var - $4 via fp in x13
        #  🍊 Giving $5 same reg as given to $2 since it not used again
        # 
# 👋 GetReg() for $5 = $2 + $4 | 🤝 `x12` reg ➜ $2 | 🤝 `x13` reg ➜ $4 | 🤝 `x12` reg ➜ $5 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 $5 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 $5 to register 12
        add     x12, x12, x13  # Addition Operation - $5 = $2 + $4
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return $5
        # 
# 🤙🏼 Calling getReg() for return $5
        #  🔵 Already in register - $5 in 12
        # 
# 👋 GetReg() for return $5 | 🤝 `x12` reg ➜ $5 |
        mv      a1, x12        # Move return value's reg - x12 to a1
        Block_2:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block Block_2
        sw      x12, -44(fp)   # Store Local Var - $5 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 $5 in memory
        #  🫗 Finished Spilling Code 👌 
        #  -- EXIT Activation (start) - fibonacci
        #  🫟 Spilling Code 🫟  due to ➢ End of Function fibonacci
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 40(sp)     # Restore return address (PC)
        lw      fp, 36(sp)     # Restore old frame pointer
        addi    sp, sp, 44     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - fibonacci
        main:
        #  🫟 Spilling Code 🫟  due to ➢ Start of Block main
        #  🫗 Finished Spilling Code 👌 
        # 
# ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi    sp, sp, -28    # Allocating Stack Space
        sw      ra, 24(sp)     # Store return address (PC)
        sw      fp, 20(sp)     # Store old frame pointer
        addi    fp, sp,28      # Set new frame pointer
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - n$4 = 6
        # 
# 🤙🏼 Calling getReg() for n$4 = 6
        #  🟢 Found Free Register - 12 for n$4
        # 
# 👋 GetReg() for n$4 = 6 | 🤝 `x0` reg ➜ NULL | 🤝 `x12` reg ➜ n$4 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 n$4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 n$4 to register 12
        li      x12, 6         # Load constant - 6 into x12(n$4)
        # 
# ‼️ TAC ❗️ ➔ Param - param n$4
        # Adding n$4 to parameter queue
        # 
# ‼️ TAC ❗️ ➔ Function Call - $6 = call fibonacci, 1
        mv      a0, x12        # Move argument - n$4 into a0
        #  🫟 Spilling Code 🫟  due to ➢ Going to ☎️ call a Function
        sw      x12, -20(fp)   # Store Local Var - n$4 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 n$4 in memory
        #  🫗 Finished Spilling Code 👌 
        jal     x1, fibonacci  # Call function - fibonacci
        sw      a0, -28(fp)    # Store return value in caller's stack for - $6
        # 💛 SYM_RECORD 💛 - Setting 🚫 $6 NOT in memory
        # 💛 SYM_RECORD 💛 - Setting 🟢 $6 in memory
        # 
# ‼️ TAC ❗️ ➔ Assign OP 🟰 - result$4 = $6
        # 
# 🤙🏼 Calling getReg() for result$4 = $6
        #  🟢 Found Free Register - 12 for $6
        # 💛 SYM_RECORD 💛 - Adding 🌕 $6 to register 12
        lw      x12, -28(fp)   # Load Local Var - $6 via fp in x12
        #  🍊 Giving result$4 same reg as given to $6 due to ASSIGN-OP
        # 
# 👋 GetReg() for result$4 = $6 | 🤝 `x12` reg ➜ $6 | 🤝 `x12` reg ➜ result$4 |
        # 💛 SYM_RECORD 💛 - Setting 🚫 result$4 NOT in memory
        # 💛 SYM_RECORD 💛 - Adding 🌕 result$4 to register 12
        #  🔄 Automatic copy - of $6 into (result$4)
        # 
# ‼️ TAC ❗️ ➔ Return Statements - return 0
        li      t1, 0          # Load constant - 0 into t1
        mv      a1, t1         # Move return value's reg - t1 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of Function main
        sw      x12, -24(fp)   # Store Local Var - result$4 via fp in x12
        # 💛 SYM_RECORD 💛 - Setting 🟢 result$4 in memory
        #  🫗 Finished Spilling Code 👌 
        mv      a0, a1         # Move return value stored by return statement into a1 to a0(default return reg)
        lw      ra, 24(sp)     # Restore return address (PC)
        lw      fp, 20(sp)     # Restore old frame pointer
        addi    sp, sp, 28     # Restore stack pointer
        jr      ra             # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟  due to ➢ End of CodeGen Spilling
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


