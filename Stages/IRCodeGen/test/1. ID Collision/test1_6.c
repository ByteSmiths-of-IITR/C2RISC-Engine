// same enum ID in different scopes

enum Color { RED, GREEN, BLUE };
enum TrafficLight { RED, YELLOW, BLACK };  // error: redeclaration of enumerator 'RED'

void func(){
    enum Color { RED, INDIGO, YELLOW }; // no error
}

int main() {
    enum Color { RED, INDIGO, YELLOW }; // no error
    return 0;
}