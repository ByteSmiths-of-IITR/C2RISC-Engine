int arr[]; // array ‘arr’ assumed to have one element

void func(){
    int arr[][10]; // error: array size missing in ‘arr’
}

int main(){
    int arr[10];
    return 0;
}
