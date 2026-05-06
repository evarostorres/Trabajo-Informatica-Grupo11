#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datos.h"

int mostrar_centros(AnalisisDatos *datos, int num_datos, char centros[][100])
{
    //contador de centros
	int num_centros = 0;
    
	int repetido;
	int i, j;
	
	//Recorremos la base de datos
    for ( i = 0; i < num_datos; i++)
    {
    	//variable bandera inicializada como falso, centro no repetido
    	repetido = 0;
    	
        for (int j = 0; j < num_centros; j++)
        {
        	//Comprobamos si ya existe el centro de la base de datos en el vectos lista de centros
            if (strcmp(centros[j], datos[i].centro_deportivo) == 0)
            {
            	//Si está repetido la bandera toma el valor verdadero
                repetido = 1;
                //Salimos del bucle, ya hemos encontrado centro repetido
                break;
            }
        }

        /*Si repetido entra con valor verdadero (centro repetido) entonces no se ejecuta el "if", 
		pero si entra con valor falso (centro no repetido) se ejecuta */
        if (!repetido)
        {
        	//Copiamos el centro en nuestro vector lista de centros
            strcpy(centros[num_centros], datos[i].centro_deportivo);

            printf("%d. %s\n", num_centros + 1, centros[num_centros]);

            num_centros++;
        }
    }

    return num_centros;
}

void mostrar_actividades_centro(const Centro *c)
{
    int i;

	//Comprobamos que no se elija una opción no válida
    if (c == NULL)
    {
        printf("Centro no valido\n");
        return;
    }
	
	//Se imprime el nombre del centro seleccionado
    printf("Centro deportivo: %s\n", c->nombre);
    printf("---------------------------------\n");

	//Comprobamos que el centro tenga actividades disponibles
    if (c->num_actividades == 0)
    {
        printf("Este centro no tiene actividades disponibles\n");
        return;
    }
	
	/*Imprimimos información de las actividades comparando con la base 
	de datos para saber de que tipo es */
    for (i = 0; i < c->num_actividades; i++)
    {
        AnalisisDatos acti = c->lista_actividades[i];

        printf("Actividad: %s\n", acti.actividad);

        if (strcmp(acti.tipo_actividad, "actividad_dirigida") == 0)
        {
            printf("Tipo: Actividad dirigida\n");
        }
        else if (strcmp(acti.tipo_actividad, "uso_libre") == 0)
        {
            printf("Tipo: Uso libre\n");
        }
        else
        {
            printf("Tipo: %s\n", acti.tipo_actividad);
        }

        printf("Horario: %s - %s\n", acti.hora_inicial, acti.hora_final);
        printf("Plazas totales: %d\n", acti.plazas);
        printf("Plazas ocupadas: %d\n", acti.ocupadas);
        printf("Plazas libres: %d\n", acti.libres);

        if (acti.libres == 0)
		{
		    printf("Estado: Completo\n");
		}
		else
		{
		    printf("Estado: Plazas disponibles\n");
		}
		
        printf("---------------------------------\n");
    }
}


Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos)
{
	
	Centro c;
    int i;
    int contador = 0;

    //Copiar el nombre del centro
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

	//Comprobación de que se ha reservado bien la memoria
	if (c.lista_actividades == NULL)
	{
	    printf("Error de memoria\n");
	    c.num_actividades = 0;
	    return c;
	}
		
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
			//Copiamos los datos 
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

    //Abrir fichero en modo añadir
    FILE *f = fopen(nombreFichFav, "a");
    if (f == NULL)
    {
        printf("Error: no se pudo abrir el fichero de favoritos.\n");
        return;
    }

    //Escribir favorito
    fprintf(f, "%s;%s;%s\n", usuario, c->nombre, c->lista_actividades[opcion - 1].actividad);

    fclose(f);

    printf("Actividad anadida a favoritos correctamente.\n");
}
