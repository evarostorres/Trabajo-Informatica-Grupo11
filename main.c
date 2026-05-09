#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pbPlots.h"
#include "supportLib.h"
#include "estructurasPrototipos.h" 

#define MAX_LONG 20

int main(){
	
	int opcionAcceso;
	int InSesionExitoso = 0;	// Bandera para saber si podemos pasar al menú principal
	char usuarioLogueado[MAX_LONG];
	
	int opcionMenu;
	
	AnalisisDatos *datos;
	
	char centros[100][100];
	int num_centros;
	
    char nombre_centro[100];
    Centro centro_usuario;
	
	char opcion;
	
	// Iniciamos sesión o nos registramos antes de entrar al menú (sistema de acceso)
    do {
        printf("\n********** SISTEMA DE ACCESO **********\n");
        printf("1. Iniciar Sesion\n");
        printf("2. Registrarse\n");
        printf("3. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcionAcceso);

        switch (opcionAcceso) {
            case 1: 
				// Si la función devuelve 1, se ha iniciado sesión y forzamos salida del bucle
                if (iniciar_sesion(usuarioLogueado) == 1) {
                    InSesionExitoso = 1;
                    opcionAcceso = 3; // Forzamos que la condición del while sea falsa
                }
                break;
            case 2: 
				registrar_usuario(); 	// Llamada a la función
				break;
            case 3: 
				printf("Saliendo del programa...\n"); 
				break;
            default: 
				printf("Opcion no valida.\n");
        }
    } while (opcionAcceso != 3);
    
    //Se abre y se lee el fichero de datos
    int n = 0;
    AnalisisDatos *lista = NULL;

    lista = lectura_fichero("dataset.csv", &n);		//Función lectura fichero de datos

    if (lista == NULL) {
        printf("Error: No se pudo cargar el archivo o la memoria.\n");
        return -1;
    }
    
    if (InSesionExitoso) {
		// Menú principal con bucle y switch (sistema de gestión)
	    do {
	        printf("\n==============================================");
			printf("\n SISTEMA DE GESTION DE ACTIVIDADES DEPORTIVAS ");
			printf("\n==============================================\n");
	        printf("1. Listado de actividades\n");
	        printf("2. Reservar actividad\n");
	        printf("3. Ver popularidad/frecuencia por centro\n");
	        printf("4. Ver gráfica de popularidad de los centros\n");
	        printf("5. Favoritos\n");
	        printf("0. Salir\n");
	        printf("\nSeleccione una opcion: ");
	        
	        scanf("%d", &opcionMenu);
	        
			switch (opcionMenu) {
				case 1:
					//Crear estructura Centro a partir de los datos
				    centro_usuario = crear_centro_por_nombre(nombre_centro, lista, n);
				
					//Mostramos al usuario la lista de centros 
					printf("\nLista de centros disponibles:\n");
					
					num_centros = mostrar_centros(lista, n, centros);
					
					
					printf("\nElige un centro (numero): ");
					scanf(" %d", &opcion);
				
					
					//Comprobación de si la opción es válida
					if (opcion < 1 || opcion > num_centros)
					{
					    printf("Opcion no valida\n");
					    return 1;
					}
				
					strcpy(nombre_centro, centros[opcion - 1]);
					
					//Agrupamos las actividades por centro
					centro_usuario = crear_centro_por_nombre(nombre_centro, lista, n);
				
				
				    //Mostrar actividades
				    mostrar_actividades_centro(&centro_usuario);
					
					char opcionAnadirFav;
					printf("\nQuieres anadir alguna actividad a favoritos? (s/n): ");
					scanf(" %c", &opcionAnadirFav);
					
					if (opcionAnadirFav == 's' || opcionAnadirFav == 'S')
					{
					    anadir_favorito("favoritos.txt", usuarioLogueado, &centro_usuario);
					}
					
					//Opción de ver favoritos (si existan o no)
					char opcionVerFav;
					printf("\nQuieres ver tus favoritos? (s/n): ");
					scanf(" %c", &opcionVerFav);
					if (opcionVerFav == 's' || opcionVerFav == 'S'){
						ver_favoritos("favoritos.txt", usuarioLogueado);
					}
	                break;
				case 2:
	                reservar_actividad(lista, n); // Llamada a la función
	                break;
				case 3:
	                //Mostramos al usuario la lista de centros 
					printf("\nLista de centros disponibles:\n");
					num_centros = mostrar_centros(lista, n, centros);
					
					ver_frecuencia(lista, n);     // Llamada a la función
					break;
				case 4:
	                ver_graficas_centros(lista, n);	// Llamada a la función
					break;case 5:
	                ver_favoritos("favoritos.txt", usuarioLogueado);	// Llamada a la función
	                break;
	            case 0:
	                printf("Saliendo del programa. ¡Adios!\n");
	                break;
	            default:
	                printf("Opcion no valida. Vuelve a intentarlo.\n");
	        }
			
	    } while (opcionMenu != 0); // El bucle se repite mientras no se pulse 0
	
	    return 0;
	}
	
	//Liberamos memoria 
	free(centro_usuario.lista_actividades);
	free(lista);
	
	return 0;
}