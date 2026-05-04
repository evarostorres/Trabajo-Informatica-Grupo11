#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EstructProtot.h"

AnalisisDatos* lectura_fichero(const char* nombrearchivo, int* n) {//Devuelve un puntero a análisis
    int i;
    char c;
    FILE *pf;
    long int posicion = 0;
    AnalisisDatos *lista = NULL;

	//ABRIMOS EL ARCHIVO
    pf = fopen(nombrearchivo, "r");
    if (pf == NULL) {
        printf("Error al abrir el archivo %s\n", nombrearchivo);
        return NULL;//Que devuelva NULL significa q devuelve error
    }

    *n = 0;
    //CUENTA LAS LÍNEAS DEL FICHERO HASTA EL FINAL
    while ((c = fgetc(pf)) != EOF) {
        if (c == '\n') { //al encontrar un salto de linea va sumando el número de líneas
            (*n)++;
            
            if (*n == 1) {
                posicion = ftell(pf); //la función ftell devuelve la posición actual. Justo después de la 1º línea
            }
        }
    }

    // Si el archivo tiene datos, saltamos la línea de títulos
    if (*n > 1) {
        fseek(pf, posicion, SEEK_SET);
    } else {
        fclose(pf);
        return NULL;
    }

    int total_lineas = (*n) - 1;
    lista = (AnalisisDatos *)malloc(total_lineas * sizeof(AnalisisDatos));
    
    if (lista == NULL) {
        printf("Error de memoria\n");
        fclose(pf);
        return NULL;
    }

    // 2. Leer los datos uno por uno
    for (i = 0; i < total_lineas; i++) {
        // fscanf leerá cada campo separado por espacios
        if (fscanf(pf, "%d %d %d %s %s %s %s %s %s %d %d %d %s",
               &lista[i].ano, &lista[i].mes, &lista[i].dia,
               lista[i].dia_semana, lista[i].hora_inicial, lista[i].hora_final,
               lista[i].actividad, lista[i].modalidad, lista[i].centro_deportivo,
               &lista[i].plazas, &lista[i].ocupadas, &lista[i].libres, 
               lista[i].tipo_actividad) != 13) { 
           //Si no lee los 13 campos, descarta esa línea y sigue
           	 while ((c = fgetc(pf)) != '\n' && c != EOF);
        }
    }

    *n = total_lineas;
    fclose(pf); 
    return lista;
}
//Esto es lo que se pone en la main
/*int main() {
    int n = 0;
    AnalisisDatos *lista = NULL;

    // Intentar leer el fichero
    lista = lectura_fichero("dataset (2).csv", &n);

    if (lista == NULL) {
        printf("Error: No se pudo cargar el archivo o la memoria.\n");
        return -1;
    }*/
//Esto se pone en el prototipo
/* AnalisisDatos* lectura_fichero(const char* nombrearchivo, int* n); */
