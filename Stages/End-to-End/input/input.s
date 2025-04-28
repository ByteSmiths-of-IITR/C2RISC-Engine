#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-28 - 22:19:50) 🎨 ---------

.data

.text
        main:
        #  ‼️ TAC ❗️ ➔ ENTRY (start) - main
        addi  sp, sp, -64      # Allocating Stack Space
        sw    ra, 60(sp)       # Store return address (PC)
        sw    fp, 56(sp)       # Store old frame pointer
        addi  fp, sp,64        # Set new frame pointer
        #  ‼️ TAC ❗️ ➔ Offset Load - $0 = arr$1.offset
        #  🟢 Found Free Register - 12 for $0
        #  🙋🏼 GetReg() for $0 = arr$1.offset | 🤝 `x12` reg ➜ $0 | 🤝 `x0` reg ➜ NULL |
        addi  x12, fp, -28     # Load address of variable (via fp) - arr$1 into x12
        #  ‼️ TAC ❗️ ➔ Assign OP 🟰 - $1 = 0
        #  🟢 Found Free Register - 13 for $1
        #  🙋🏼 GetReg() for $1 = 0 | 🤝 `x13` reg ➜ $1 | 🤝 `x0` reg ➜ NULL |
        # Setting 🚫 $1 NOT in memory
        # Adding 🌕 $1 to register 13
        li    x13, 0           # Load constant - 0 into x13($1)
        #  ‼️ TAC ❗️ ➔ Simple Operation - $2 = $0 + $1
        #  🟢 Found Free Register - 14 for $0
        # Adding 🌕 $0 to register 14
        lw    x14, -32(fp)     # Load Local Var - $0 via fp in x14
        #  🔵 Already in register - $1 in 13
        #  🍊 Giving $2 same reg as given to $0 since it not used again
        #  🙋🏼 GetReg() for $2 = $0 + $1 | 🤝 `x14` reg ➜ $0 | 🤝 `x13` reg ➜ $1 | 🤝 `x14` reg ➜ $2 |
        # Setting 🚫 $2 NOT in memory
        # Adding 🌕 $2 to register 14
        add   x14, x14, x13    # Addition Operation - $2 = $0 + $1
        #  ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$2 = 10
        #  🔵 Already in register - $2 in 14
        #  🙋🏼 GetReg() for (4)*$2 = 10 | 🤝 `x14` reg ➜ $2 |
        li    t0, 10           # Load constant - 10 into t0
        sw    t0, 0(x14)       # Store constant of reg t0 at address pointed by x14
        #  ‼️ TAC ❗️ ➔ Offset Load - $3 = arr$1.offset
        #  🟢 Found Free Register - 15 for $3
        #  🙋🏼 GetReg() for $3 = arr$1.offset | 🤝 `x15` reg ➜ $3 | 🤝 `x0` reg ➜ NULL |
        addi  x15, fp, -28     # Load address of variable (via fp) - arr$1 into x15
        #  ‼️ TAC ❗️ ➔ Assign OP 🟰 - $4 = 4
        #  🟢 Found Free Register - 16 for $4
        #  🙋🏼 GetReg() for $4 = 4 | 🤝 `x16` reg ➜ $4 | 🤝 `x0` reg ➜ NULL |
        # Setting 🚫 $4 NOT in memory
        # Adding 🌕 $4 to register 16
        li    x16, 4           # Load constant - 4 into x16($4)
        #  ‼️ TAC ❗️ ➔ Simple Operation - $5 = $3 + $4
        #  🟢 Found Free Register - 17 for $3
        # Adding 🌕 $3 to register 17
        lw    x17, -44(fp)     # Load Local Var - $3 via fp in x17
        #  🔵 Already in register - $4 in 16
        #  🍊 Giving $5 same reg as given to $3 since it not used again
        #  🙋🏼 GetReg() for $5 = $3 + $4 | 🤝 `x17` reg ➜ $3 | 🤝 `x16` reg ➜ $4 | 🤝 `x17` reg ➜ $5 |
        # Setting 🚫 $5 NOT in memory
        # Adding 🌕 $5 to register 17
        add   x17, x17, x16    # Addition Operation - $5 = $3 + $4
        #  ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$5 = 20
        #  🔵 Already in register - $5 in 17
        #  🙋🏼 GetReg() for (4)*$5 = 20 | 🤝 `x17` reg ➜ $5 |
        li    t0, 20           # Load constant - 20 into t0
        sw    t0, 0(x17)       # Store constant of reg t0 at address pointed by x17
        #  ‼️ TAC ❗️ ➔ Offset Load - $6 = arr$1.offset
        #  🟢 Found Free Register - 18 for $6
        #  🙋🏼 GetReg() for $6 = arr$1.offset | 🤝 `x18` reg ➜ $6 | 🤝 `x0` reg ➜ NULL |
        addi  x18, fp, -28     # Load address of variable (via fp) - arr$1 into x18
        #  ‼️ TAC ❗️ ➔ Assign OP 🟰 - $7 = 8
        #  🟢 Found Free Register - 19 for $7
        #  🙋🏼 GetReg() for $7 = 8 | 🤝 `x19` reg ➜ $7 | 🤝 `x0` reg ➜ NULL |
        # Setting 🚫 $7 NOT in memory
        # Adding 🌕 $7 to register 19
        li    x19, 8           # Load constant - 8 into x19($7)
        #  ‼️ TAC ❗️ ➔ Simple Operation - $8 = $6 + $7
        #  🟢 Found Free Register - 20 for $6
        # Adding 🌕 $6 to register 20
        lw    x20, -56(fp)     # Load Local Var - $6 via fp in x20
        #  🔵 Already in register - $7 in 19
        #  🍊 Giving $8 same reg as given to $6 since it not used again
        #  🙋🏼 GetReg() for $8 = $6 + $7 | 🤝 `x20` reg ➜ $6 | 🤝 `x19` reg ➜ $7 | 🤝 `x20` reg ➜ $8 |
        # Setting 🚫 $8 NOT in memory
        # Adding 🌕 $8 to register 20
        add   x20, x20, x19    # Addition Operation - $8 = $6 + $7
        #  ‼️ TAC ❗️ ➔ Left Star 🌟 - (4)*$8 = 30
        #  🔵 Already in register - $8 in 20
        #  🙋🏼 GetReg() for (4)*$8 = 30 | 🤝 `x20` reg ➜ $8 |
        li    t0, 30           # Load constant - 30 into t0
        sw    t0, 0(x20)       # Store constant of reg t0 at address pointed by x20
        #  ‼️ TAC ❗️ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  🫟 Spilling Code 🫟 
        sw    x13, -36(fp)     # Store Local Var - $1 via fp in x13
        # Setting 🟢 $1 in memory
        sw    x14, -40(fp)     # Store Local Var - $2 via fp in x14
        # Setting 🟢 $2 in memory
        sw    x16, -48(fp)     # Store Local Var - $4 via fp in x16
        # Setting 🟢 $4 in memory
        sw    x17, -52(fp)     # Store Local Var - $5 via fp in x17
        # Setting 🟢 $5 in memory
        sw    x19, -60(fp)     # Store Local Var - $7 via fp in x19
        # Setting 🟢 $7 in memory
        sw    x20, -64(fp)     # Store Local Var - $8 via fp in x20
        # Setting 🟢 $8 in memory
        #  🫗 Finished Spilling Code 👌 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 60(sp)       # Restore return address (PC)
        lw    fp, 56(sp)       # Restore old frame pointer
        addi  sp, sp, 64       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  🫟 Spilling Code 🫟 
        #  🫗 Finished Spilling Code 👌 

#-------------------------------------------------------------------------


