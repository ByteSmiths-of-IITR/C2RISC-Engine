/* goto - simpler version */

int main() {
    int a = 0;

    goto label;
    a = 10; // This statement is skipped

    label:
    a = 20;
    
}