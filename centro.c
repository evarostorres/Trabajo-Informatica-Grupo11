#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datos.h"
//Estructuras para función añadir a favoritos
typedef struct {
	char *usuario;
	char *actividad;
	char *centro;
} Favoritos;

typedef struct {
    Favoritos *lista;
    int num_favoritos;
} ListaFavoritos;

void mostrar_actividades_centro(const Centro *c)
{
	int i;
	AnalisisDatos acti;
	
	// El usuario selecciona una opción no válida
	if (c == NULL)
	{
		printf("Centro no válido\n");
		return;
	}
	
	//Se imprime el centro deportivo que ha seleccionado y se le asigna a c
	printf("Centro deportivo: %s\n", c->nombre);
	printf("---------------------------------\n");
	
	
    //printf("Añadir a favoritos\n");
	
	// Si el numero de actividades del que dispone el centro es 0
	if (c->num_actividades == 0)
	{
		printf("Este centro no tiene actividades disponibles\n");
		return;
	}
	
	// Se muestra la lista de actividades según el tipo
	for (i = 0; i < c->num_actividades; i++)
	{
		AnalisisDatos acti = c->lista_actividades[i];

    	printf("Actividad: %s\n", acti.actividad);
		
		//Comparamos cadenas para ver si son actividades dirigidas o de uso libre
		if (acti.tipo_actividad != NULL && strcmp(acti.tipo_actividad, "actividad_dirigida") == 0)
	    {
	        printf("Tipo: Actividad dirigida\n");
	    }
	    else if (acti.tipo_actividad != NULL && strcmp(acti.tipo_actividad, "uso_libre") == 0)
	    {
	        printf("Tipo: Uso libre\n");
	    }
	    else if (acti.tipo_actividad != NULL)
	    {
	        printf("Tipo: %s\n", acti.tipo_actividad);
	    }
	    else
	    {
	        printf("Tipo: No especificado\n");
	    }
	
	    printf("Horario: %s - %s\n", acti.hora_inicial, acti.hora_final);
	    printf("Plazas totales: %d\n", acti.plazas);
	    printf("Plazas ocupadas: %d\n", acti.ocupadas);
	    printf("Plazas libres: %d\n", acti.libres);
	
	    printf("Estado: %s\n", acti.libres == 0 ? "Completo" : "Plazas disponibles");
	    printf("---------------------------------\n");
	}
}

Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos)
{
	
Centro c;
    int i;
    int contador = 0;

    //Copiar el nombre del centro
    c.nombre = malloc(strlen(nombre) + 1);
    strcpy(c.nombre, nombre);

    //Primero contamos actividades
    for (i = 0; i < num_datos; i++)
    {
        if (strcmp(datos[i].centro_deportivo, nombre) == 0)
        {
            contador++;
        }
    }

    c.num_actividades = contador;

    //Reservamos memoria para las actividades del centro
    c.lista_actividades = malloc(contador * sizeof(AnalisisDatos));

    //Después copiamos las actividades
    int indice = 0;
    for (i = 0; i < num_datos; i++)
    {
        if (strcmp(datos[i].centro_deportivo, nombre) == 0)
        {
            c.lista_actividades[indice] = datos[i];
            indice++;
        }
    }

    return c;
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
	
void anadir_favorito(const char *nombreFichFav, const char *usuario, const Centro *c)
{
	
if (c == NULL || c->num_actividades == 0)
    {
        printf("No hay actividades para anadir a favoritos.\n");
        return;
    }

    int opcion;

    //Mostrar actividades numeradas
    printf("\nElige una actividad para anadir a favoritos:\n");
    for (int i = 0; i < c->num_actividades; i++)
    {
        printf("%d. %s (%s - %s)\n", i + 1, c->lista_actividades[i].actividad,
			c->lista_actividades[i].hora_inicial, c->lista_actividades[i].hora_final);
    }

    printf("Indica el número de la actividad (0 para cancelar): ");
    scanf("%d", &opcion);

    if (opcion <= 0 || opcion > c->num_actividades)
    {
        printf("Operación cancelada.\n");
        return;
    }

    AnalisisDatos act = c->lista_actividades[opcion - 1];

    //Abrir fichero en modo añadir
    FILE *f = fopen(nombreFichFav, "a");
    if (f == NULL)
    {
        printf("Error: no se pudo abrir el fichero de favoritos.\n");
        return;
    }

    //Escribir favorito
    fprintf(f, "%s;%s;%s\n", usuario, c->nombre, act.actividad);

    fclose(f);

    printf("Actividad anadida a favoritos correctamente.\n");
}
	
	//cerramos el fichero y devolvemos los favoritos con los datos almacenados
    fclose(f);
    return favoritos;
}
