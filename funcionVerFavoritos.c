#include <stdio.h>
#include <string.h>
#include "estructProtot.h" 

void ver_favoritos(const char *nombreFichFav, const char *usuarioLogueado){
    
	//Abrimos el archivo de favoritos
	FILE *archivo = fopen(nombreFichFav, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo de favoritos.\n");
        return;
    }

    Favorito lista[100];		//Hacemos un vector de estructuras con la estructura Favorito
    int contador = 0;
    char u[20], c[50], a[50];	//Usuario, centro y actividad leidos del archivo de favoritos (variables temp)


    printf("\n--- TUS FAVORITOS ---\n");

    // Se leen los tres elementos separados por ; y se meten en el vector de estructuras
    while (fscanf(archivo, "%19[^;];%49[^;];%49[^\n]\n", u, c, a) == 3) {
        if (strcmp(u, usuarioLogueado) == 0) {
            strcpy(lista[contador].usuario, u);
            strcpy(lista[contador].centro, c);
            strcpy(lista[contador].actividad, a);
            
            //Se imprimen por pantalla los favoritos
            printf("%d. Centro: %s | Actividad: %s\n", contador + 1, c, a);
            contador++;
        }
    }
    fclose(archivo);

    //Si el contador es 0 quiere decir que el usuario no aparece en el archivo (no tiene favoritos)
	if (contador == 0) {
        printf("No tienes ninguna actividad en favoritos.\n");
        return;
    }

    //El usuario selecciona si quiere gestionar alguna actividad
	int seleccion;
    printf("\nSi desea eliminar una actividad seleccionela (indica su número) o pulse 0 para salir: ");
    scanf("%d", &seleccion);

	if (seleccion > 0 && seleccion <= contador) {
        eliminar_favorito(lista[seleccion - 1], nombreFichFav, usuarioLogueado);	//Llamada a la función de eliminar favorito
    }
}
