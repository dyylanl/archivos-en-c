#include <stdlib.h>
#include <stdio.h>


char** replicar(char data[], int l1, int l2, int cant) {
    int len = sizeof(data);
    int k=0;
    while (k<l1) {
        printf("%c",data[k]);
        k++;
    }
    for (int j=0; j<cant; j++) {
        for (int i=l1; i<=l2; i++) {
            printf("%c",data[i]);
        }
    }
    int n=l2+1;
    while (n<len) {
        printf("%c",data[n]);
        n++;
    }
    

}

int main() {
    char data[] = "Hola";
    replicar(data,1,2,3);
    return(0);
}