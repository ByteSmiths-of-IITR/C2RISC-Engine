
🎨 CFG Code Generation completed successfully 🎨
#-------------------------------------------------------------------------
====================== [ CFG Code ] ======================
.data

.text
ENTRY : 
main : 
    0 : main: Func ENTER          | a_s_1 ☠️           | str_0 ⬇️ ( 2 )     | 
    1 : a_s_1 = 10                | str_0 ⬇️ ( 2 )     | 
    2 : param str_0               | Default            | 
    3 : alloca $0, 0              | $0 ⬇️ ( 4 )        | 
    4 : $0 = call printf, 1       | Default            | 
    5 : return                    | Default            | 
    6 : main ret(4): EXIT         | Default            | 
EXIT : 
#-------------------------------------------------------------------------


#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-28 - 19:57:17) 🎨 ---------

.data
        a_s_1:      .zero          4
        str_0:    .string    "Hello"

.text
        main:
        #  ~TAC~ ➔ ENTRY (start) - main
        addi  sp, sp, -16      # Allocating Stack Space
        sw    ra, 12(sp)       # Store return address (PC)
        sw    fp, 8(sp)        # Store old frame pointer
        addi  fp, sp,16        # Set new frame pointer
        #  ~TAC~ ➔ Assign OP 🟰 - a_s_1 = 10
        #  🙋🏼 GetReg() for a_s_1 = 10 | 🤝 x0` reg ➜ NULL | 🤝 x12` reg ➜ a_s_1 |
        li    x12, 10          # Load constant - 10 into x12(a_s_1)
        #  ~TAC~ ➔ Param - param str_0
        # Adding str_0 to parameter queue
        #  ~TAC~ ➔ Function Call - $0 = call printf, 1
        la    t0, str_0        # Loading Address of Global Variable - str_0
        lw    t2, 0(t0)        # Load Global Var - str_0 via t0 in xt2
        sw    t2, 20(sp)       # Store argument str_0 via t2 to callee's stack
        #  ~~ Spilling Code ~~ 
        la    t0, a_s_1        # Loading Address of Global Variable - a_s_1
        sw    x12, 0(t0)       # Store Global Var - a_s_1 via t0 in xx12
        #  ~~ Finished Spilling Code ~~ 
        jal   x1, printf       # Call function - printf
        sw    a0, -16(fp)      # Store return value in caller's stack for - $0
        #  ~TAC~ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  ~~ Spilling Code ~~ 
        #  ~~ Finished Spilling Code ~~ 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 12(sp)       # Restore return address (PC)
        lw    fp, 8(sp)        # Restore old frame pointer
        addi  sp, sp, 16       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main
        #  ~~ Spilling Code ~~ 
        #  ~~ Finished Spilling Code ~~ 

#-------------------------------------------------------------------------


