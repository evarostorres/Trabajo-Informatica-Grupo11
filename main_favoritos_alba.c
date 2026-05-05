#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datos.h"
typedef struct {
	char *usuario;
	char *actividad;
	char *centro;
} Favoritos;

typedef struct {
    Favoritos *lista;
    int num_favoritos;
} ListaFavoritos;

AnalisisDatos *cargar_datos_csv(const char *nombre_fichero, int *num_datos);
Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos);
ListaFavoritos cargar_favoritos_usuario(const char *nombreFichFav, const char *usuario);
void anadir_favorito(const char *nombreFichFav, const char *usuario, const Centro *c);

int main(void)
{
    AnalisisDatos *datos;
    int num_datos;

    char nombre_centro[100];
    Centro centro_usuario;
    
    char usuario[50];
    char opcion;

    //Usuario logueado
    printf("Introduce tu nombre de usuario: ");
    fgets(usuario, sizeof(usuario), stdin);
    if (usuario[strlen(usuario) - 1] == '\n')
        usuario[strlen(usuario) - 1] = '\0';

    //Cargar datos del CSV 
    datos = cargar_datos_csv("dataset (2).csv", &num_datos);

    if (datos == NULL || num_datos == 0)
    {
        printf("Error al cargar los datos\n");
        return 1;
    }
	
	/* antes de pedir el centro deportivo hay que mostrar un vector que contenga los centros deportivos*/
    //Pedir centro al usuario 
    printf("Introduce el nombre del centro deportivo: ");
    fgets(nombre_centro, sizeof(nombre_centro), stdin);
    //Sustituir el \n del final del nombre por \0
	if (nombre_centro[strlen(nombre_centro) - 1] == '\n')
	{
	    nombre_centro[strlen(nombre_centro) - 1] = '\0';
	}


    //Crear estructura Centro a partir de los datos
    centro_usuario = crear_centro_por_nombre(nombre_centro, datos, num_datos);

    //Mostrar actividades
    mostrar_actividades_centro(&centro_usuario);

    //Aquí se integra la función favoritos
	printf("\nQuieres anadir alguna actividad a favoritos? (s/n): ");
	scanf(" %c", &opcion);
	
	if (opcion == 's' || opcion == 'S')
	{
	    anadir_favorito("favoritos.txt", usuario, &centro_usuario);
	}
	
	//Opción de ver favoritos (si existan o no)
	printf("\nQuieres ver tus favoritos? (s/n): ");
	scanf(" %c", &opcion);
	
	if (opcion == 's' || opcion == 'S')
	{
	    ListaFavoritos favoritos = cargar_favoritos_usuario("favoritos.txt", usuario);
	
	    if (favoritos.num_favoritos == 0)
	    {
	        printf("\nNo tienes favoritos guardados.\n");
	    }
	    else
	    {
	        printf("\n--- TUS FAVORITOS ---\n");
	        for (int i = 0; i < favoritos.num_favoritos; i++)
	        {
	            printf("%d. Centro: %s | Actividad: %s\n",
	                   i + 1,
	                   favoritos.lista[i].centro,
	                   favoritos.lista[i].actividad);
	        }
	    }
	
	    //Liberar memoria dinámica de favoritos
	    for (int i = 0; i < favoritos.num_favoritos; i++)
	    {
	        free(favoritos.lista[i].usuario);
	        free(favoritos.lista[i].centro);
	        free(favoritos.lista[i].actividad);
	    }
	    free(favoritos.lista);
	}



    //Liberar memoria
    free(centro_usuario.lista_actividades);
    free(datos);
    

    return 0;
}
