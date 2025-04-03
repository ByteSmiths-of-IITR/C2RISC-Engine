// Forward Declaration Without Definition (struct)
struct A;

int main(){
    struct A obj; // error: storage size of ‘obj’ isn’t known
    return 0;
}
