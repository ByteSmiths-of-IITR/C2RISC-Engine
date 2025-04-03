// struct not defined in this scope; 
// struct member not defined
int main()
{
    {
        struct Person
        {
            int gender;
        };

        struct Person p;
        p.gender = 1;
        p.age = 10; // error: ‘struct Person’ has no member named ‘age’
    }

    struct Person p1; // error: storage size of ‘p1’ isn’t known
    p1.age = 20;

    int Person = 190;
}