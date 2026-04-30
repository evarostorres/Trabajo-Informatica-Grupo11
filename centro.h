#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datos.h"
	
typedef struct {
    char *nombre;                       // Nombre del centro
    int num_actividades;                // Cuántas actividades tiene
    AnalisisDatos *lista_actividades;   // Vector dinámico de actividades
} Centro;

//Prototipo de la función que recorre la lista de actividades 
//dado un centro ya seleccionado
void mostrar_actividades_centro(const Centro *c);