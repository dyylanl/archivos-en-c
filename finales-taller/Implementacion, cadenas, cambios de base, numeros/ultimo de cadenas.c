#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *funcion(char *T, int N) {
	int len = strlen(T);
	char *str = malloc(len*N + N);
	memset(str, 0, len*N + N);
	char espacio = ' ';
	for (int i = 0; i < N; i++) {
		sprintf(str + (len + 1)*i, "%s", T);
		if (i != N -1)
		sprintf(str + (len + 1)*i + len, "%s", &espacio);
	}
	str[len*N + N] = '\0';
	return str;
}

int main() {
	char T[600];
	int N;
	printf("Ingrese la cadena: ");
	scanf("%s", T);
	printf("\nIngrese la cantidad: ");
	scanf("%i", &N);

	printf("\n Resultado = %s", funcion (T, N));
	return 0;
}

