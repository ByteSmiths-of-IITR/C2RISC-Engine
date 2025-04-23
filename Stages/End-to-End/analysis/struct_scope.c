
struct Person
{
    int a : 1;
    struct test
    {
        int b;
    } t;
} c;

int a;

struct test
{
    int b;
};

int main()
{
    c.t.b = 10;

    struct test
    {
        int r;
    } t1;

    {
        struct test
        {
            int g;
        } t2;
    }
    c.t.b = 10;

    struct test t;
    t.r = 10;
}
