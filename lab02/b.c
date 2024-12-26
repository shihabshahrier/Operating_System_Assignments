#include <stdio.h>

int perfectNum(int n){
    int div_sum = 0;
    for(int i = 1; i <= n / 2; i++){
        if (n%i == 0){
            div_sum += i;
        }
    }
    return div_sum == n;
}
int main(){
    int s, n;
    printf("enter the starting value: ");
    scanf("%d", &s);

    printf("enter the ending value: ");
    scanf("%d", &n);

    for(int i = s; i <= n; i++){
        if (perfectNum(i))
            printf("%d\n", i);
    }
    
    return 0;
}