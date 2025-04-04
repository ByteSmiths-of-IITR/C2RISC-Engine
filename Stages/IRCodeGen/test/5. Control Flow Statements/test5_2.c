/* switch-case */
// NO ERROR

int main() {
    int a = 2;
    const int b = 3, c = 4;

    switch (a) {
        case (b+c):
            a = 10;
            break;
        case 5:
            a++;
            // if(a = 3) {a = 30;}
            break;
        default:
            a = 30;
        // default: // error: multiple default labels in one switch
        //     a = 40;
    }

    // case 3: // error: error: case label not within a switch statement
    //     a = 20;
    //     break;

    return 0;
}