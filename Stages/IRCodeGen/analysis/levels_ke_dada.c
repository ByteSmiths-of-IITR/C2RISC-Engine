// int func(int a, int b);

int (*funcPtr)(int (*nextLeveFunc)(int, int), int, int);
// type - [base-int] ? [args { [base-int] ? [args{[base-int],[base-int]}] | [*]  , [base-int], [base-int] }] | [*]

/*
[pointer]
args
    {
        {   
            [pointer]
            args
            {
                [base-int],
                [base-int]
            }
            [base-int]
        }
        [base-int],
        [base-int]
    }
[base-int]
*/

// int function(int a,b)

// int function(int a, int b);

// int function(int a, int b){
//     return a + b;
// }

// int main(){
//     int b=4, c=5;
//     int a = function(b, c);
// }

// int func(int a);

// int (*(*func2)(int a));

// int (*func)(int a);

int *var42141;
int (*var2);



int *(*(*var242));

int (var122(int a));
// type - [base-int] ? [] | [ args{ [base-int] }]

int *( *(var232)(int a) )[8];
// type - [base-int] ? [* ;8] | [*] | [ args{ [base-int] }]
// Works since var1 is function
// it's return type is pointer (not array or function)

int *(*(*(var342)(int a))[8]);
// Works since var3 is function
// it's return type is pointer (not array or function)

// int main(){
//     var = 'c';
//     *var = 'c';
//     **var = 'c';
//     ***var = 'c';
//     ****var = 'c';
// }

int (*var78)[5](int a); // At same LevelExpression - we can't have array & argList
int (*var2)(int a)[5];

int (var12(int a))(int b); // At the LevelExpression below a function 
// i.e. it's return type can't be array or function

int var32(int);

int (var10[3])[5]; // At the same LevelExpression - we can't have array & argList
