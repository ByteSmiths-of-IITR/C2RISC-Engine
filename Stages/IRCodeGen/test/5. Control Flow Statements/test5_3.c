/* nested for loop */
// NO ERROR

int main() {
    for (int i = 0; i < 10; i++) {
        int a = 0;
        for(int j=0; j < 10; j++) {
            a++;
        }
    }
    return 0;
}