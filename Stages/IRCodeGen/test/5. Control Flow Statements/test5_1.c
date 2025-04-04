/* nested if-else */
// NO ERROR

int main() {
    int a = 5;
    if (a > 0)
        a = 10;
    else
        a = 20;
    
    if (a > 0) {
        if (a == 10){
            a = 30;
        }
    }
    else
        a = 40;
    
    return 0;
}