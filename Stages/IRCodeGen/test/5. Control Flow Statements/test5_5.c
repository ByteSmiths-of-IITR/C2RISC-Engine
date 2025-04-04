/*
variations of for statement
*/
int main(){
    int i=0;

    for(;i<5;){
        i++;
    }

    for(i=0;i<5;){
        i++;
    }

    for(i=0;;){
        i++;
        if(i==4) break;
    }
}