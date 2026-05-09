#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pbPlots.h"
#include "supportLib.h"
#include "estructurasPrototipos.h" 

#define MAX_LONG 20


// FUNCIONES DEL MENU DE ACCESO

int iniciar_sesion(char *guardarUsuario)
{
	
    char usuarioPedido[MAX_LONG];
    char contrasenaPedida[MAX_LONG];
    char usuarioCorrecto[MAX_LONG];
    char contrasenaCorrecta[MAX_LONG];
    FILE *fichUsuariosContrasenas;

    printf("\n--- INICIO DE SESIÓN ---\n");
    printf("Usuario: ");
    scanf("%s", usuarioPedido);
    printf("Contrasena: ");
    scanf("%s", contrasenaPedida);

	// Abrimos el archivo para buscar la coincidencia
    fichUsuariosContrasenas = fopen("usuarioscontrasenas.txt", "r");
    if (fichUsuariosContrasenas == NULL) 
	{
        printf("\nError: No se pudo abrir el archivo de credenciales.\n");
        // Salimos de la función si no hay archivo
		return 0; 	
    }

	// Reiniciamos la bandera de búsqueda en cada intento
    int encontrarCoincidencia = 0;
    
    // Leemos el fichero (pares usuario-contraseña separados por espacio) hasta el final (EOF)
    while (fscanf(fichUsuariosContrasenas, "%s %s", usuarioCorrecto, contrasenaCorrecta) != EOF) 
	{
        // Comprobamos si coinciden ambos
		if (strcmp(usuarioPedido, usuarioCorrecto) == 0 && strcmp(contrasenaPedida, contrasenaCorrecta) == 0)
		{
            encontrarCoincidencia = 1;
            strcpy(guardarUsuario, usuarioPedido);
			// Salimos del while de lectura al ver que coinciden
            break; 
        }
    }
	 // Cerramos el archivo tras buscar
    fclose(fichUsuariosContrasenas); 
	
    if (encontrarCoincidencia) 
	{
        printf("\nAcceso correcto. ¡Bienvenido al sistema!\n");
		// Señal de éxito para la función main
        return 1; 	
    } 
	else
	{
        printf("\nUsuario o contrasena incorrectos. Intentalo de nuevo.\n");
		// Señal de fallo
        return 0; 
    }
}


void registrar_usuario() 
{
    char nuevoUsuario[MAX_LONG];
    char nuevaContrasena[MAX_LONG];
    FILE *fichUsuariosContrasenas;

	// "a" abre para añadir datos al final del fichero
    fichUsuariosContrasenas = fopen("usuarioscontrasenas.txt", "a"); 
    if (fichUsuariosContrasenas == NULL) 
	{
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("\n--- REGISTRO DE NUEVO USUARIO ---\n");
    printf("Introduce nombre de usuario: ");
    scanf("%s", nuevoUsuario);
	
    printf("Introduce contraseña: ");
    scanf("%s", nuevaContrasena);

    // Guardamos el usuario y la contraseña separados por un espacio
    fprintf(fichUsuariosContrasenas, "%s %s\n", nuevoUsuario, nuevaContrasena);
    fclose(fichUsuariosContrasenas);

    printf("¡Registro completado con éxito! Ya puedes iniciar sesión\n");
}

// FUNCIONES DE LECTURA Y DEL MENÚ PRINCIPAL

AnalisisDatos *lectura_fichero(const char* nombrearchivo, int* n) 
{
	// Devuelve un puntero a análisis
    int i;
    char c;
    FILE *pf;
    long int posicion = 0;
    AnalisisDatos *lista = NULL;

	// Abrimos el archivo
    pf = fopen(nombrearchivo, "r");
    if (pf == NULL)
	{
        printf("Error al abrir el archivo %s\n", nombrearchivo);
		// Que devuelva NULL significa q devuelve error
        return NULL;
    }

    *n = 0;
    // Cuenta las líneas del fichero hasta el final
    while ((c = fgetc(pf)) != EOF) 
	{
		// Al encontrar un salto de linea va sumando el número de líneas
        if (c == '\n') 
		{ 
            (*n)++;
            
            if (*n == 1) 
			{
				// La función ftell devuelve la posición actual. Justo después de la 1º línea
                posicion = ftell(pf); 
            }
        }
    }

    // Si el archivo tiene datos, saltamos la línea de títulos
    if (*n > 1) 
	{
        fseek(pf, posicion, SEEK_SET);
    } 
	else
	{
        fclose(pf);
        return NULL;
    }

    int total_lineas = (*n) - 1;
    lista = (AnalisisDatos *)malloc(total_lineas * sizeof(AnalisisDatos));
    
    if (lista == NULL) 
	{
        printf("Error de memoria\n");
        fclose(pf);
        return NULL;
    }

    // Lee los datos uno por uno sin contar la linea de títulos
    for (i = 0; i < total_lineas; i++) 
	{
        // fscanf leerá cada campo separado por espacios
        fscanf(pf, "%d %d %d %49s %19s %19s %99s %49s %99s %d %d %d %49s",
               &lista[i].ano, &lista[i].mes, &lista[i].dia,
               lista[i].dia_semana, lista[i].hora_inicial, lista[i].hora_final,
               lista[i].actividad, lista[i].modalidad, lista[i].centro_deportivo,
               &lista[i].plazas, &lista[i].ocupadas, &lista[i].libres, 
               lista[i].tipo_actividad);
           
    }

	/* Ejemplo: ahora n pasa de ser 30 lineas a ser total_lineas (que hemos dicho que son 29 lineas)
	Esto apunta al main */
    *n = total_lineas; 
    fclose(pf); 
    printf("Fichero leido");
    return lista;
}


Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos)
{
	
	Centro c;
    int i;
    int contador = 0;

    // Copiar el nombre del centro
    strcpy(c.nombre, nombre);

    // Primero contamos actividades
    for (i = 0; i < num_datos; i++)
    {
        if (strcmp(datos[i].centro_deportivo, nombre) == 0)
        {
            contador++;
        }
    }

    c.num_actividades = contador;

    // Reservamos memoria para las actividades del centro
    c.lista_actividades = malloc(contador * sizeof(AnalisisDatos));

	// Comprobación de que se ha reservado bien la memoria
	if (c.lista_actividades == NULL)
	{
	    printf("Error de memoria\n");
	    c.num_actividades = 0;
	    return c;
	}
		
    // Después copiamos las actividades
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


int mostrar_centros(AnalisisDatos *datos, int num_datos, char centros[][100])
{
    // Contador de centros
	int num_centros = 0;
    
	int i, j;
	
	// Recorremos la base de datos
    for ( i = 0; i < num_datos; i++)
    {
    	
		// Variable bandera inicializada como falso, centro no repetido
    	int repetido = 0;
    	
        for (int j = 0; j < num_centros; j++)
        {
        	// Comprobamos si ya existe el centro de la base de datos en el vectos lista de centros
            if (strcmp(centros[j], datos[i].centro_deportivo) == 0)
            {
            	// Si está repetido la bandera toma el valor verdadero
                repetido = 1;
                // Salimos del bucle, ya hemos encontrado centro repetido
                break;
            }
        }

        /* Si repetido entra con valor verdadero (centro repetido) entonces no se ejecuta el "if", 
		pero si entra con valor falso (centro no repetido) se ejecuta */
        if (!repetido)
        {
        	// Copiamos el centro en nuestro vector lista de centros
            strcpy(centros[num_centros], datos[i].centro_deportivo);

            printf("%d. %s\n", num_centros + 1, centros[num_centros]);

            num_centros++;
        }
	}
}


void mostrar_actividades_centro(const Centro *c)
{
	
    int i;

	// Comprueba que se ha elegido una opción válida
    if (c == NULL)
    {
        printf("Centro no valido\n");
        return;
    }

	// Imprime el nombre del centro seleccionado
    printf("Centro deportivo: %s\n", c->nombre);
    printf("---------------------------------\n");

	// Si el centro no tiene actividades
    if (c->num_actividades == 0)
    {
        printf("Este centro no tiene actividades disponibles\n");
        return;
    }
	
	// Si el centro tiene actividades
    for (i = 0; i < c->num_actividades; i++)
    {
        AnalisisDatos acti = c->lista_actividades[i];

        printf("Actividad: %s\n", acti.actividad);

		// Comprueba si la actividad es de tipo dirigida
        if (strcmp(acti.tipo_actividad, "actividad_dirigida") == 0)
        {
            printf("Tipo: Actividad dirigida\n");
        }
		// Comprueba si la actividad es de tipo uso libre
        else if (strcmp(acti.tipo_actividad, "uso_libre") == 0)
        {
            printf("Tipo: Uso libre\n");
        }
        else
        {
            printf("Tipo: %s\n", acti.tipo_actividad);
        }

		// Imprime la hora, las plazas libres y ocupadas 
        printf("Horario: %s - %s\n", acti.hora_inicial, acti.hora_final);
        printf("Plazas totales: %d\n", acti.plazas);
        printf("Plazas ocupadas: %d\n", acti.ocupadas);
        printf("Plazas libres: %d\n", acti.libres);

		// Si no hay actividades libres impreme que el estado es completo
        if (acti.libres == 0)
		{
		    printf("Estado: Completo\n");
		}
		// Si hay actividades entonces imprime que hay plazas disponibles
		else
		{
		    printf("Estado: Plazas disponibles\n");
		}
		
        printf("---------------------------------\n");
    }
}


void reservar_actividad(AnalisisDatos lista[], int n)
{
  	char centros[100][100];
    char nombre_centro[100];

    int num_centros;
	
	Centro Centro_usuario;
	int opcion_centro;
	int opcion_act;
	int i;
	int salir = 0;

	// LLAMADA FUNCION 1
	num_centros = mostrar_centros(lista, n, centros);
	printf("\n-------Lista de centros -------\n");

	// Este do while sirve para q lo vuelva a pedir hasta q el usuario introduzca el número correcto
	do
	{ 
		
		printf("Selecciona un numero del centro donde se quiere apuntar(1-%d): ", num_centros);
		//Aqui el usuario introduce la posición, del centro.
		scanf("%i", &opcion_centro); 
		
	}
	while (opcion_centro<1 || opcion_centro>num_centros);
	// En el primer argumento le restamos 1 porque es una cadena
	strcpy(nombre_centro, centros[opcion_centro - 1]);		
	
	// LLAMADA A FUNCIÓN 2
	Centro_usuario = crear_centro_por_nombre(nombre_centro, lista, n);

	// Imprimios la lista de actividades
	printf("\n-------Lista de actividades por centro -------\n");

	// El punto sirve para acceder a la estructura
	for (i = 0; i<Centro_usuario.num_actividades; i++)
	{ 
		// Se pone i + 1 porque el ususario ve eso, ya que si introduce 1, la posición es 0
		printf("%d. %s || %s - %s || Libres: %d\n", i + 1, 
    	Centro_usuario.lista_actividades[i].actividad,
    	Centro_usuario.lista_actividades[i].hora_inicial,
        Centro_usuario.lista_actividades[i].hora_final,
   		Centro_usuario.lista_actividades[i].libres);
		
	}
	// Selección de la  actividad q desea reservar
	do
	{
		printf("Selecciona un numero de la actividad a la que se quiere apuntar ", num_centros);
		scanf("%i", &opcion_act);	
	}
		while (opcion_act<1 || opcion_act > Centro_usuario.num_actividades);
	
	opcion_act--;
	
	while(salir ==0)
	{

		// Ahora reservamos la actividad
		if (Centro_usuario.lista_actividades[opcion_act].libres > 0)
		{
			for (i = 0; i<n; i++)
			{
				if(strcmp(lista[i].centro_deportivo, Centro_usuario.nombre)==0 && strcmp(lista[i].actividad, 
					Centro_usuario.lista_actividades[opcion_act].actividad)==0 
					&& strcmp(lista[i].hora_inicial,Centro_usuario.lista_actividades[opcion_act].hora_inicial)== 0)
				{
					
					lista[i].ocupadas++;
	                lista[i].libres--;
	                printf("RESERVA CONFIRMADA\n");
	                
	                salir = 1; 
	                break;
					
				}
			}
		}
			
		//En el caso q no haya plazas
		else
		{
			int opcion;
			int encontrada = 0;
			
			printf("No hay plazas disponibles\n");
			printf("SUGERENCIAS DENTRO DEL CENTRO CON LOS MISMOS HORARIOS DE LA ACTIVIDAD SELECCIONADA:\n");
			
			
			for (i = 0; i<Centro_usuario.num_actividades; i++)
			{
				if (strcmp(Centro_usuario.lista_actividades[i].hora_inicial, Centro_usuario.lista_actividades[opcion_act].hora_inicial)==0
				&&strcmp(Centro_usuario.lista_actividades[i].hora_final, Centro_usuario.lista_actividades[opcion_act].hora_final)==0
				&& Centro_usuario.lista_actividades[i].libres>0 && i != opcion_act)
				{ 
					// Se pone i + 1 porque el ususario ve eso
					printf("%d. %s || %s - %s || Libres: %d\n", i + 1,
			    	Centro_usuario.lista_actividades[i].actividad,
			    	Centro_usuario.lista_actividades[i].hora_inicial,
			        Centro_usuario.lista_actividades[i].hora_final,
			   		Centro_usuario.lista_actividades[i].libres);
					
					encontrada = 1;
				}
				
			} 
			
			if (encontrada ==0)
			{
				printf("NO quedan actividades a esa hora\n");
			}
			
			printf("1. Volver a intentar: \n");
			printf("2. Salir: \n");
			scanf("%d", &opcion); 
			
				if (opcion == 2)
				{
					salir = 1;
				}
				else
				{
					do
					{
						printf("Selecciona otra actividad: ");
	           			scanf("%d", &opcion_act);
					}
					while (opcion_act < 1 || opcion_act > Centro_usuario.num_actividades);
					opcion_act--;
				}
			}		
	}
}


void ver_frecuencia(AnalisisDatos datos[], int n) 
{
    
    AnalisisDatos temp; 
    char centroElegido[100];
    int a = 0;
    int b = 0;
    float porcentaje;
    int i,j;
    
    
	// 1. VALIDAMOS EL CENTRO
	
    do
	{
	
    	printf("Introduce el centro del que quieres ver la popularidad: ");
        scanf(" %[^\n]", centroElegido);


        // Vemos si existe el centro que ha introducido comparando con el fichero
        for (i = 0; i < n; i++) 
		{
        
            if (strcmp(datos[i].centro_deportivo, centroElegido) == 0) 
			{
			    a++;
            }
        }
    
        // Si al final el contador "a" sigue en 0, es que el centro no existe o no tiene datos
        if (a == 0) 
		{
            printf("No se han encontrado datos para el centro: %s\n", centroElegido);
        }
    
    
    }
	while (a == 0);
    
    
	// 2. ORDENAMOS (Solo las actividades que coinciden con el centro elegido)
	
	// Este bucle es el que recorre el vector
    for (i = 0; i < n - 1; i++) 
	{     
		// Y este es el que va comparando
        for (j = 0; j < n - i - 1; j++) 
		{    
            float p1 = (float)datos[j].ocupadas / datos[j].plazas;
            float p2 = (float)datos[j+1].ocupadas / datos[j+1].plazas;

            if (p1 < p2) 
			{ 
				// Ordenamos de mayor a menor popularidad SEGÚN EL PORCENTAJE
                temp = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = temp;
            }
        }
    }



	// 3. IMPRIMIMOS LAS ACTIVIDADES PARA CADA CENTRO 
	
    printf("\n LO MAS POPULAR EN %s \n", centroElegido); 
    printf("==========================================\n");
     
    for (i = 0; (i < n && b < 10); i++) 
	{
        
        if (strcmp(datos[i].centro_deportivo, centroElegido) == 0) 
		{
            
            b++;
            
			porcentaje = ((float)datos[i].ocupadas / datos[i].plazas) * 100;

            printf("%d. %s (%s - %s)\n", b, datos[i].actividad, datos[i].hora_inicial, datos[i].hora_final);
            printf("   Ocupacion: %d de %d plazas (%.2f%%)\n", datos[i].ocupadas, datos[i].plazas, porcentaje);
            printf("--------------------------------------------------\n");
        }
    }


	//4. DESCARGAR LOS DATOS 

    FILE *archivo;
    char respuesta;
    int c = 0;
    
    printf("¿Desea descargar los datos?(s/n): ");
    scanf(" %c", &respuesta);
    
    if (respuesta == 's'|| respuesta == 'S')
	{
    	
        archivo = fopen("Popularidad_actividades.txt", "w");	
    	
    	if (archivo != NULL)
		{
    		
    		fprintf (archivo, "LO MAS POPULAR EN %s \n", centroElegido);
    		fprintf(archivo, "==========================================\n");
    		
        	for (i = 0; (i < n && c < 10); i++) 
			{
                if (strcmp(datos[i].centro_deportivo, centroElegido) == 0) 
				{
                    c++;
			        porcentaje = ((float)datos[i].ocupadas / datos[i].plazas) * 100;
                    
					fprintf(archivo, "%d. %s (%s - %s)\n", c, datos[i].actividad, datos[i].hora_inicial, datos[i].hora_final);
                    fprintf(archivo,"   Ocupacion: %d de %d plazas (%.2f%%)\n", datos[i].ocupadas, datos[i].plazas, porcentaje);
                    fprintf(archivo,"--------------------------------------------------\n");
				}
            }
            
            fclose(archivo);
            printf("Archivo guardado con exito.\n");
    		
		}
    		
	}
} 


void ver_graficas_centros(AnalisisDatos datos[], int n){

    // Variables arriba (compatible con Dev-C++ C90) 
    AnalisisDatos aux;
    int i, j, k;
    int numCentros;
    int numActividades;
    int contadorLeyenda;

    double indicesX[100];
    double mediasY[100];

    char centroActual[100];

    double sumaPorcentajes = 0;
	double p;

    _Bool success;
    StringReference *errorMessage = CreateStringReference(L"",0);

    RGBABitmapImageReference *imageRef;
    ScatterPlotSettings *settings;
    ScatterPlotSeries *series;
    ScatterPlotSeries *seriesList[1];

    ByteArray *pngdata;


    /* ================================================= */
    /* 1. ORDENAR CENTROS ALFABÉTICAMENTE                */
    /* ================================================= */

    for (i = 0; i < n - 1; i++)
	{
        for (j = 0; j < n - i - 1; j++)
		{
            if (strcmp(datos[j].centro_deportivo, datos[j + 1].centro_deportivo) > 0)
			{
                aux = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = aux;
            }
        }
    }


    /* ================================================= */
    /* 2. CALCULAR MEDIA DE OCUPACIÓN                    */
    /* ================================================= */

    numCentros = 0;

    for (i = 0; i < n; i++)
	{

        if (i == 0 || strcmp(datos[i].centro_deportivo,datos[i - 1].centro_deportivo) != 0)
		{
            strcpy(centroActual, datos[i].centro_deportivo);

            sumaPorcentajes = 0;
            numActividades = 0;

            for (k = 0; k < n; k++)
			{

                if (strcmp(datos[k].centro_deportivo,centroActual) == 0)
				{

                    p = ((double)datos[k].ocupadas / datos[k].plazas) * 100;

                    sumaPorcentajes += p;
                    numActividades++;
                }
            }

            if (numActividades > 0)
			{

                mediasY[numCentros] =
                    sumaPorcentajes / numActividades;

                indicesX[numCentros] =
                    numCentros + 1;

                numCentros++;
            }
        }
    }


    /* ================================================= */
    /* 3. CREAR GRÁFICA                                 */
    /* ================================================= */

    StartArenaAllocator();

    imageRef = CreateRGBABitmapImageReference();

    settings = GetDefaultScatterPlotSettings();

    settings->width = 800;
    settings->height = 600;

    settings->autoBoundaries = true;
    settings->xMin = 0;
    settings->xMax = numCentros + 1;
    settings->yMin = 0;
    settings->yMax = 100;

    settings->title = L"Ocupacion Media por Centro";
	settings->titleLength = 26;
	
	settings->xLabel = L"Numero de Centro";
	settings->xLabelLength = 16;
	
	settings->yLabel = L"Porcentaje %";
	settings->yLabelLength = 12;

    /* Serie de puntos */

    series = GetDefaultScatterPlotSeriesSettings();

    series->xs = indicesX;
    series->xsLength = numCentros;

    series->ys = mediasY;
    series->ysLength = numCentros;

    series->linearInterpolation = false;

    series->pointType = L"dots";
	series->pointTypeLength = 4;

    seriesList[0] = series;

    settings->scatterPlotSeries = seriesList;
    settings->scatterPlotSeriesLength = 1;


    /* Dibujar */
    success = DrawScatterPlotFromSettings(imageRef, settings, errorMessage);


    /* ================================================= */
    /* 4. GUARDAR PNG                                   */
    /* ================================================= */


    if (success)
	{
        pngdata = ConvertToPNG(imageRef->image);

        WriteToFile(pngdata,"analisisOcupacion.png");

        printf("\nGrafica generada con exito.\n");
        printf("Archivo: analisisOcupacion.png\n");


        /* LEYENDA */

        printf("\n----- LEYENDA -----\n");

        contadorLeyenda = 1;

        for (i = 0; i < n; i++)
		{

            if (i == 0 || strcmp(datos[i].centro_deportivo,datos[i - 1].centro_deportivo) != 0)
			{

                printf("%d. %s\n",contadorLeyenda,datos[i].centro_deportivo);
                contadorLeyenda++;
            }
        }

        printf("-------------------\n");
    }
    else
	{
        printf("\nError al generar la grafica.\n");
    }

    FreeAllocations();
}


// FUNCIONES RELACIONADAS CON FAVORITOS

void anadir_favorito(const char *nombreFichFav, const char *usuarioLogueado, const Centro *c)
{
	
	if (c == NULL || c->num_actividades == 0)
    {
        printf("No hay actividades para anadir a favoritos.\n");
        return;
    }

    int opcion;

    // Mostrar actividades numeradas
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

    // Abrir fichero en modo añadir
    FILE *f = fopen(nombreFichFav, "a");
    if (f == NULL)
    {
        printf("Error: no se pudo abrir el fichero de favoritos.\n");
        return;
    }

    // Escribir favorito
    fprintf(f, "%s;%s;%s\n", usuarioLogueado, c->nombre, c->lista_actividades[opcion - 1].actividad);

    fclose(f);

    printf("Actividad anadida a favoritos correctamente.\n");
}


void ver_favoritos(const char *nombreFichFav, const char *usuarioLogueado)
{
	// Abrimos el archivo de favoritos
	FILE *archivo = fopen(nombreFichFav, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo de favoritos.\n");
        return;
    }

	// Hacemos un vector de estructuras con la estructura Favorito
    Favorito lista[100];		
    int contador = 0;
	// Usuario, centro y actividad leidos del archivo de favoritos (variables temporales)
    char u[20], c[50], a[50];	


    printf("\n--- TUS FAVORITOS ---\n");

    // Se leen los tres elementos separados por ; y se meten en el vector de estructuras
    while (fscanf(archivo, "%19[^;];%49[^;];%49[^\n]\n", u, c, a) == 3) 
	{
        if (strcmp(u, usuarioLogueado) == 0) 
		{
            strcpy(lista[contador].usuario, u);
            strcpy(lista[contador].centro, c);
            strcpy(lista[contador].actividad, a);
            
            // Se imprimen por pantalla los favoritos
            printf("%d. Centro: %s | Actividad: %s\n", contador + 1, c, a);
            contador++;
        }
    }
    fclose(archivo);

    // Si el contador es 0 quiere decir que el usuario no aparece en el archivo (no tiene favoritos)
	if (contador == 0) 
	{
        printf("No tienes ninguna actividad en favoritos.\n");
        return;
    }

    // El usuario selecciona si quiere gestionar alguna actividad
	int seleccion;
	
    printf("\nSi desea eliminar una actividad seleccionela (indica su número) o pulse 0 para salir: ");
    scanf("%d", &seleccion);

	if (seleccion > 0 && seleccion <= contador) 
	{
		// Llamada a la función de eliminar favorito
        eliminar_favorito(lista[seleccion - 1], nombreFichFav, usuarioLogueado);	
    }
}


void eliminar_favorito(Favorito fav, const char *nombreFichFav, const char *usuarioLogueado)
{
    char opcion;
	
    printf("\n ¿Seguro que desea borrar %s de favoritos? (s/n): ", fav.actividad);
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') 
	{
        // Lógica de borrado de favorito
        FILE *origen = fopen(nombreFichFav, "r");
        FILE *temp = fopen("temp.txt", "w");
		//Usuario, centro y actividad leidos del archivo de favoritos (variables temporales)
        char u[20], c[50], a[50];	

        // Leemos todo el archivo original y escribimos en el temporal todo menos el registro seleccionado
        while (fscanf(origen, "%19[^;];%49[^;];%49[^\n]\n", u, c, a) == 3) 
		{
        	/* strcmp=0 nos confirma que el texto en las variables temporales es igual al de las estructuras
			Esa linea es la que no copiamos */
            if (!(strcmp(u, fav.usuario) == 0 && strcmp(c, fav.centro) == 0 && strcmp(a, fav.actividad) == 0)) 
			{
                fprintf(temp, "%s;%s;%s\n", u, c, a);
            }
        }
        fclose(origen);
        fclose(temp);
        
        // Borra el archivo original (tenía el favorito que queríamos quitar)
        remove(nombreFichFav);	
        // Renombra el archivo temporal para que tenga el nombre del original (con el favorito quitado)
        rename("temp.txt", nombreFichFav);	
        printf("Favorito eliminado correctamente.\n");
    }
}
