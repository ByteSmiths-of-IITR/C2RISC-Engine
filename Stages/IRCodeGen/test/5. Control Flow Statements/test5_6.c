/* while-loop */

int main() {
    int i = 0;
    while (i < 10) {
        while(i < 'a') { // implicit type casting
            i++;
        }
        i++;
    }
    return 0;
}