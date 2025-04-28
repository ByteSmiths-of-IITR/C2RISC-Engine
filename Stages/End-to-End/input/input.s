
🎨 CFG Code Generation completed successfully 🎨
#-------------------------------------------------------------------------
====================== [ CFG Code ] ======================
.data

.text
ENTRY : 
main : 
    0 : main: Func ENTER          | a_s_1 ☠️           | str$0 ⬇️ ( 3 )     | 
    1 : a_s_1 = 10                | str$0 ⬇️ ( 3 )     | 
    2 : alloca str$1, 4           | str$0 ⬇️ ( 3 )     | 
    3 : str_c_1 = str$0           | Default            | 
    4 : return                    | Default            | 
    5 : main ret(4): EXIT         | Default            | 
EXIT : 
#-------------------------------------------------------------------------


#-------- 🎨 RISC-V Code Gen using C2RISC-Engine Time(2025-04-28 - 19:24:16) 🎨 ---------

.data
        a_s_1:      .zero          4
        str$0:    .string    "Hello"

.text
        main:
        #  ~TAC~ ➔ ENTRY (start) - main
        addi  sp, sp, -20      # Allocating Stack Space
        sw    ra, 16(sp)       # Store return address (PC)
        sw    fp, 12(sp)       # Store old frame pointer
        addi  fp, sp,20        # Set new frame pointer
        #  ~TAC~ ➔ Assign OP 🟰 - a_s_1 = 10
        #  🙋🏼 GetReg() for a_s_1 = 10 | 🤝 x0` reg ➜ NULL | 🤝 x12` reg ➜ a_s_1 |
        li    x12, 10          # Load constant - 10 into x12(a_s_1)
        #  ~TAC~ ➔ Assign OP 🟰 - str_c_1 = str$0
        la    t0, str$0        # Loading Address of Global Variable - str$0
        lw    x13, 0(t0)       # Load Global Var - str$0 via t0 in x13
        #  🙋🏼 GetReg() for str_c_1 = str$0 | 🤝 x13` reg ➜ str$0 |
        #  🔄 Automatic copy - of str$0 into (str_c_1)
        #  ~TAC~ ➔ Return Statements - return 
        mv    a1, x0           # Move return value's reg - x0 to a1
        #  -- EXIT Activation (start) - main
        #  ~~ Spilling Code ~~ 
        la    t0, a_s_1        # Loading Address of Global Variable - a_s_1
        sw    x12, 0(t0)       # Store Global Var - a_s_1 via t0 in x12
        la    t0, str$0        # Loading Address of Global Variable - str$0
        sw    x13, 0(t0)       # Store Global Var - str$0 via t0 in x13
        #  ~~ Finished Spilling Code ~~ 
        mv    a0, a1           # Move return value stored by return statement into a1 to a0(default return reg)
        lw    ra, 16(sp)       # Restore return address (PC)
        lw    fp, 12(sp)       # Restore old frame pointer
        addi  sp, sp, 20       # Restore stack pointer
        jr    ra               # Jump to return address(back to caller)
        #  -- EXIT Activation (end) - main

#-------------------------------------------------------------------------


