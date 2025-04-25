# Activation Record

# Features Not supported by Simulator

These Two Instructions are not supported by the simulator: </br>
`lui     a5,%hi(foo)` </br>
`addi    a5,a5,%lo(foo)`</br>

<span style="color:green">**Solution**</span> - Use `la a5,foo` instead of the above two instructions. Where foo can be any memory label </br>

# Complex Compiler Features to Implement

1. _Function pointer_ = Not easy uses the above two instructions - not easy to support -> since the offset of function is a lable and is not known. </br>
This would require some kind of backpathching were we would need to put the address of function's risc-v code start after complete code generation


2. _Global Variable_ = Need to Decide How to calculate there offset and all other required stuffs
    <span style="color:green">**Done**</span>
    2.1 _Global Arrays_

    ```assembly
    .data
        arr: .word   1,2,3 // IMP
            
    .text
        main:
            addi    sp,sp,-32
            sw      ra,28(sp)
            sw      s0,24(sp)
            addi    s0,sp,32
            la a5 arr // IMP
            lw      a5,4(a5)
            sw      a5,-20(s0)
            li      a5,0
            mv      a0,a5
            lw      ra,28(sp)
            lw      s0,24(sp)
            addi    sp,sp,32
            jr      ra
    ```

    2.2
