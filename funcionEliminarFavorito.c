#include <stdio.h>
#include <string.h>
#include "estructProtot.h" 

void eliminar_favorito(Favorito fav, const char *nombreFichFav, const char *usuarioLogueado) {
    int opcion;
    printf("\n ¿Seguro que desea borrar %s de favoritos? (s/n): ", fav.actividad);
    scanf(" %d", &opcion);

    if (opcion == s) {
    	
        // Lógica de borrado de favorito
        FILE *origen = fopen(nombreFichFav, "r");
        FILE *temp = fopen("temp.txt", "w");
        char u[20], c[50], a[50];	//Usuario, centro y actividad leidos del archivo de favoritos (variables temp)

        // Leemos todo el archivo original y escribimos en el temporal todo menos el registro seleccionado
        while (fscanf(origen, "%19[^;];%49[^;];%49[^\n]\n", u, c, a) == 3) {
        	//strcmp=0 nos confirma que el texto en las variables temporales es igual al de las estructuras
			//Esa linea es la que no copiamos 
            if (!(strcmp(u, fav.usuario) == 0 && strcmp(c, fav.centro) == 0 && strcmp(a, fav.actividad) == 0)) {
                fprintf(temp, "%s;%s;%s\n", u, c, a);
            }
        }
        fclose(origen);
        fclose(temp);
        
        //Borra el archivo original (tenía el favorito que queríamos quitar)
        remove(nombreFichFav);	
        //Renombra el archivo temporal para que tenga el nombre del original (con el favorito quitado)
        rename("temp.txt", nombreFichFav);	
        printf("Favorito eliminado correctamente.\n");
    }
}