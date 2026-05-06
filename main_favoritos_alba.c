#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datos.h"
int main (void)
{
    AnalisisDatos *datos;
    int num_datos;
	int n;
	
	char centros[100][100];
	int num_centros;
	
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
    datos = lectura_fichero("dataset (2).csv", &num_datos);

    if (datos == NULL || num_datos == 0)
    {
        printf("Error al cargar los datos\n");
        return 1;
    }
    
    //Crear estructura Centro a partir de los datos
    centro_usuario = crear_centro_por_nombre(nombre_centro, datos, num_datos);

	//Mostramos al usuario la lista de centros 
	printf("\nLista de centros disponibles:\n");
	
	num_centros = mostrar_centros(datos, num_datos, centros);
	
	
	printf("\nElige un centro (numero): ");
	scanf("%d", &opcion);

	
	//Comprobación de si la opción es válida
	if (opcion < 1 || opcion > num_centros)
	{
	    printf("Opcion no valida\n");
	    return 1;
	}

	strcpy(nombre_centro, centros[opcion - 1]);
	
	//Agrupamos las actividades por centro
	centro_usuario = crear_centro_por_nombre(nombre_centro, datos, num_datos);


    //Mostrar actividades
    mostrar_actividades_centro(&centro_usuario);
	
	//Liberamos memoria 
	free(centro_usuario.lista_actividades);
	free(datos);
	
	return 0;
}
    return 0;
}
