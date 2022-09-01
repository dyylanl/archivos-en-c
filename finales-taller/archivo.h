#ifndef _ARCHIVO_H_
#define _ARCHIVO_H_
typedef struct alumno_t {
    char nombre[50];
    unsigned int padron;
} alumno_t;
unsigned int alumno_get_padron(alumno_t* a);
void procesar_alumnos(alumno_t* a, unsigned int b, void (*ptrF) (alumno_t*));
#endif /*_ARCHIVO_H_*/