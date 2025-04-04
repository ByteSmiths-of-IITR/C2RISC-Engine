/* goto advanced version */

int main() {
    int i = 0;
    
    loop_start:
    if (i >= 10)
        goto loop_end;
    
    if (i == 5)
        goto break_loop;
    if (i == 3)
        goto continue_loop;
    
    continue_loop:
    i++;
    
    goto loop_start;
    
    break_loop:
    
    loop_end:

    return 0;
}
