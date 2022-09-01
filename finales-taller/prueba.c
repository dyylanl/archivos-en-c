/*
 *     Ejercicio [1] final 01/08/06
 *     Se recibe el nombre de un archivo por parametro.
 *     Sin crear nuevos archivos se debe reemplazar todas
 *     los match "UNO", "DOS" , "TRES" por '1','2','3' respectivamente.
 */

/*#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(argv[1], "r");
    //FILE* fdW = fopen(argv[1], "r+");
    FILE* fdW = fopen("test.txt", "w+");
    
    char uno[] = "UNO";
    char dos[] = "DOS";
    char tres[] = "TRES";
    
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    
    char c;
    while (fread(&c, sizeof(char), 1, fdR) == 1) {
        fputc(c, fdW);
        
        if (c == uno[i1])
            i1++;
        else
            i1=0;
        
        if (c == dos[i2])
            i2++;
        else
            i2=0;
        
        if (c == tres[i3])
            i3++;
        else
            i3=0;
        
        if (i1 == strlen(uno)) {
            i1 = 0;
            fseek (fdW, -strlen(uno), SEEK_CUR);
            fputc('1', fdW);
        }
        
        if (i2 == strlen(dos)) {
            i2 = 0;
            fseek (fdW, -strlen(dos), SEEK_CUR);
            fputc('2', fdW);
        }
            
        if (i3 == strlen(tres)) {
            i3 = 0;
            fseek (fdW, -strlen(tres), SEEK_CUR);
            fputc('3', fdW);
        }
    }
   
    ftruncate(fileno(fdW), ftell(fdW));
    fclose(fdR);
    fclose(fdW);
    return 0;
}*/


/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    FILE* fdR = fopen(argv[1], "r");
    //FILE* fdW = fopen(argv[1], "r+");
    FILE* fdW = fopen("test.txt", "w+");
    
    char uno[] = "UNO";
    char dos[] = "DOS";
    char tres[] = "TRES";
    
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    
    char c;
    while (fread(&c, sizeof(char), 1, fdR) == 1) {
        fputc(c, fdW);
        
        if (c == uno[i1])
            i1++;
        else
            i1=0;
        
        if (c == dos[i2])
            i2++;
        else
            i2=0;
        
        if (c == tres[i3])
            i3++;
        else
            i3=0;
        
        if (i1 == strlen(uno)) {
            i1 = 0;
            fdW -= 2;
            fputc('1', fdW);
        }
        
        if (i2 == strlen(dos)) {
            i2 = 0;
            fdW -= 2;
            fputc('2', fdW);
        }
            
        if (i3 == strlen(tres)) {
            i3 = 0;
            fdW -= 2;
            fputc('3', fdW);
        }
    }
   
    ftruncate(fileno(fdW), fdW);
    fclose(fdR);
    fclose(fdW);
    return 0;
}
*/

/*#include <stdio.h>
void foo() {
    static int x = 5;
    x++;
    printf("%d", x);
}

int main() {
    foo();
    foo();
    return 0;
}*/

int* DivEnt(float* a[2]);

int main() {
    return 0;
}