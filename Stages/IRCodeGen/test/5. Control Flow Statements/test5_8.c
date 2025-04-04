/* IF with break and continue */

int main() {
    for (int i = 0; i < 10; i++) {
        if (i == 5)
            break;
        if (i == 3)
            continue;
    }
    return 0;
}