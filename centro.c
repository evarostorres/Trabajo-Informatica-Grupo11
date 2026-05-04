#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datos.h"
#include "centro.h"

void mostrar_actividades_centro(const Centro *c)
{
	int i;
	AnalisisDatos acti;
	
	if (c == NULL)
	{
		printf("Centro no válido\n");
		return;
	}
	
	printf("Centro deportivo: %s\n", c->nombre);
	printf("---------------------------------\n");
	
	if (c->num_actividades == 0)
	{
		printf("Este centro no tiene actividades disponibles\n");
		return;
	}
	
	for (i = 0; i < c->num_actividad; i++)
	{
		actividad == c->num_actividad[i];
		
		printf("Actividad: %s\n", acti.actividad);
		
		if( strcmp(acti.tipo_actividad, "actividad_dirigida") == 0)
		{
			printf("Tipo: Actividad dirigida\n");
		}
		else if (strcmp(acti.tipo_actividad, "uso_libre") == 0)
		{
			print("Tipo: Uso libre\n");
		}
		else
		{
			printf("Tipo: %s\n", acti.tipo_actividad);
		}
		
		printf("Horario: %s - %s\n", acti.hora_inicial, activity.hora_final);
		printf("Plazas totales: %d\n", acti.plazas);
		printf("Plazas ocupadas: %d\n", acti.ocupadas);
		printf("Plazas libres: %d\n", acti.libres);
		
		if (actividad.libres == 0)
		{
			printf("Estado: completo\n");
		}
		else 
		{
			printf("Estado: plazas disponibles");
		}
		printf("---------------------------------\n");
	}
}
ListaFavoritos cargar_favoritos_usuario(const char *nombreFichFav, const char *usuario)
{
	ListaFavoritos favoritos;
	//Aún no hay favoritos
	favoritos.lista = NULL;
	//num_favoritos es un contador
	favoritos.num_favoritos = 0;
	
	FILE *f = fopen(nombreFichFav, "r");
	if (f == NULL)
	{
		printf("Error: no se pudo abrir el fichero de favoritos.\n");
		return favoritos;
	}
	
	//u, c, a, son variables temporales que sirven para leer el fichero
	char u[50], c[50], a[50];
	
	//Leemos líneas tipo: usuario;centro;actividad
 	while (fscanf(f, "%49[^;];%49[^;];%49[^\n]\n", u, c, a) == 3)
    {
    	//Si coincide con el usuario se añade a la lista
    	if (strcmp(u, usuario) == 0)
    	{
    		//Ajustamos el tamaño exacto
    		Favoritos *tmp = realloc(favoritos.lista,(favoritos.num_favoritos + 1) * sizeof(Favoritos));
			
			//Si falla nos aseguramos de que no se pierde memoria
			if (tmp == NULL)
            {
                printf("Error de memoria.\n");
                break;
            }
					
    	    favoritos.lista = tmp;
    	    
			//Ahora se copian los datos con memoria dinámica
			favoritos.lista[favoritos.num_favoritos].usuario = malloc(strlen(u) + 1);
			favoritos.lista[favoritos.num_favoritos].centro = malloc(strlen(c) + 1);
			favoritos.lista[favoritos.num_favoritos].actividad = malloc(strlen(a) + 1);
			
			//Copiamos los datos con su memoria ajustada a su tamaño
 			strcpy(favoritos.lista[favoritos.num_favoritos].usuario, u);
            strcpy(favoritos.lista[favoritos.num_favoritos].centro, c);
            strcpy(favoritos.lista[favoritos.num_favoritos].actividad, a);

            favoritos.num_favoritos++;
        }
    }
	
	//cerramos el fichero y devolvemos los favoritos con los datos almacenados
    fclose(f);
    return favoritos;
}
