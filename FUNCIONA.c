//AnalisisDatos AHORA ES ESTRUCTURA DE VECTORES

//EN LAS FUNCIONES DE LAURA HE CAMBIADO LOS PARAMETROS EN EL MAIN Y SU SEGUNDA FUNCION ES DE TIPO INT

//LA FUNCION RESERVAR ACTIVIDAD FUNCIONA PERO ES MUY EXQUISITA PORQUE DEPENDE DE COMO SE METAN LOS DATOS (IDEA: RESERVAR A PARTIR DE UNA LISTA)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pbPlots.h"
#include "supportLib.h"

#define MAX_LONG 20

typedef struct {
    int ano;
    int mes;
    int dia;
    char dia_semana[100];
    char hora_inicial[100];
    char hora_final[100];
    char actividad[100];
    char modalidad[100];
    char centro_deportivo[100];
    int plazas;
    int ocupadas;
    int libres;
    char tipo_actividad[100];    
} AnalisisDatos;

typedef struct {
    char nombre[100];                       // Nombre del centro
    int num_actividades;                // Cuántas actividades tiene
    AnalisisDatos *lista_actividades;   // Vector dinámico de actividades
} Centro;

typedef struct {
	char *usuario;
	char *actividad;
	char *centro;
} Favoritos;


typedef struct {
    Favoritos *lista;
    int num_favoritos;
} ListaFavoritos;


typedef struct {
    char usuario[20];
    char centro[50];
    char actividad[50];
} Favorito;


int iniciar_sesion(char *guardarUsuario);										
void registrar_usuario();
AnalisisDatos *lectura_fichero(const char* nombrearchivo, int* n);

void ver_favoritos(const char *nombre_fichero, const char *usuarioLogueado);
void eliminar_favorito(Favorito fav, const char *nombreFichFav, const char *usuarioLogueado);

void ver_frecuencia(AnalisisDatos datos[], int n);
void ver_graficas_centros(AnalisisDatos datos[], int n);

void reservar_actividad(AnalisisDatos lista[], int n); 

Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos);
int mostrar_centros(AnalisisDatos *datos, int num_datos, char centros[][100]);
void mostrar_actividades_centro(const Centro *c);
void anadir_favorito(const char *nombreFichFav, const char *usuarioLogueado, const Centro *c);


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
					scanf("%d", &opcion);
				
					
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
	            case 5:
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

    
int iniciar_sesion(char *guardarUsuario){
	
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
    if (fichUsuariosContrasenas == NULL) {
        printf("\nError: No se pudo abrir el archivo de credenciales.\n");
        return 0; 	// Salimos de la función si no hay archivo
    }

	// Reiniciamos la bandera de búsqueda en cada intento
    int encontrarCoincidencia = 0;
    
    // Leemos el fichero (pares usuario-contraseña separados por espacio) hasta el final (EOF)
    while (fscanf(fichUsuariosContrasenas, "%s %s", usuarioCorrecto, contrasenaCorrecta) != EOF) {
        // Comprobamos si coinciden ambos
		if (strcmp(usuarioPedido, usuarioCorrecto) == 0 && strcmp(contrasenaPedida, contrasenaCorrecta) == 0){
            encontrarCoincidencia = 1;
            strcpy(guardarUsuario, usuarioPedido);
            break; // Salimos del while de lectura al ver que coinciden
        }
    }

    fclose(fichUsuariosContrasenas); // Cerramos el archivo tras buscar

    if (encontrarCoincidencia) {
        printf("\nAcceso correcto. ¡Bienvenido al sistema!\n");
        return 1; 	// Señal de éxito para la función main
    } else {
        printf("\nUsuario o contrasena incorrectos. Intentalo de nuevo.\n");
        return 0; 	// Señal de fallo
    }
}


void registrar_usuario(){
    char nuevoUsuario[MAX_LONG];
    char nuevaContrasena[MAX_LONG];
    FILE *fichUsuariosContrasenas;

    fichUsuariosContrasenas = fopen("usuarioscontrasenas.txt", "a"); // "a" abre para añadir datos al final del fichero
    if (fichUsuariosContrasenas == NULL) {
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


AnalisisDatos *lectura_fichero(const char* nombrearchivo, int* n) {//Devuelve un puntero a análisis
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

    // 1.Si el archivo tiene datos, saltamos la línea de títulos
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

    // 2. Leer los datos uno por uno sin contar la linea de títulos
    for (i = 0; i < total_lineas; i++) {
        // fscanf leerá cada campo separado por espacios
        fscanf(pf, "%d %d %d %49s %19s %19s %99s %49s %99s %d %d %d %49s",
               &lista[i].ano, &lista[i].mes, &lista[i].dia,
               lista[i].dia_semana, lista[i].hora_inicial, lista[i].hora_final,
               lista[i].actividad, lista[i].modalidad, lista[i].centro_deportivo,
               &lista[i].plazas, &lista[i].ocupadas, &lista[i].libres, 
               lista[i].tipo_actividad);
           
    }

    *n = total_lineas; // Ejemplo: ahora n pasa de ser 30 lineas, a ser total_lineas (que hemos dicho que son 29 lineas). Esto apunta a el main.
    fclose(pf); 
    printf("Fichero leido");
    return lista;
}


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

void eliminar_favorito(Favorito fav, const char *nombreFichFav, const char *usuarioLogueado){
    char opcion;
    printf("\n ¿Seguro que desea borrar %s de favoritos? (s/n): ", fav.actividad);
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') {
    	
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

void ver_frecuencia(AnalisisDatos datos[], int n) {
    
    AnalisisDatos temp; 
    char centroElegido[100];
    int a = 0;
    int b = 0;
    float porcentaje;
    int i,j;
    
    
//1. VALIDAMOS EL CENTRO

    do{
	
    	printf("Introduce el centro del que quieres ver la popularidad: ");
        scanf(" %[^\n]", centroElegido);


        //Vemos si existe el centro que ha introducido comparando con el fichero
        for (i = 0; i < n; i++) {
        
            if (strcmp(datos[i].centro_deportivo, centroElegido) == 0) {
			    a++;
            }
        }
    
        //Si al final el contador "a" sigue en 0, es que el centro no existe o no tiene datos
        if (a == 0) {
            printf("No se han encontrado datos para el centro: %s\n", centroElegido);
        }
    
    
    }while (a == 0);
    
    
//2. ORDENAMOS (Solo las actividades que coinciden con el centro elegido)

    for (i = 0; i < n - 1; i++) {     //este bucle es el que recorre el vector
        for (j = 0; j < n - i - 1; j++) {    //y este es el que va comparando
               
            float p1 = (float)datos[j].ocupadas / datos[j].plazas;
            float p2 = (float)datos[j+1].ocupadas / datos[j+1].plazas;

            if (p1 < p2) { // Ordenamos de mayor a menor popularidad SEGÚN EL PORCENTAJE
                temp = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = temp;
            }
        }
    }



//3. IMPRIMIMOS LAS ACTIVIDADES PARA CADA CENTRO

    printf("\n LO MAS POPULAR EN %s \n", centroElegido); 
    printf("==========================================\n");
     
    for (i = 0; (i < n && b < 10); i++) {
        
        if (strcmp(datos[i].centro_deportivo, centroElegido) == 0) {
            
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
    
    if (respuesta == 's'|| respuesta == 'S'){
    	
        archivo = fopen("Popularidad_actividades.txt", "w");	
    	
    	if (archivo != NULL){
    		
    		fprintf (archivo, "LO MAS POPULAR EN %s \n", centroElegido);
    		fprintf(archivo, "==========================================\n");
    		
        	for (i = 0; (i < n && c < 10); i++) {
                if (strcmp(datos[i].centro_deportivo, centroElegido) == 0) {
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
} //cerramos funcion


void reservar_actividad(AnalisisDatos lista[], int n){ 
	int anio;
	int mes;
	int dian; 
	char centro[100];
	char nombreactividad[50]; 
	char modalidad[30];
	char diasemana[20];
	char horai[10];
	char horaf[10];
	char tipactividad[20];
	int i;
	int encontrado; 
	int opcion = 2;
	

	do{
		encontrado = 0; // Igualamos el encontrado a 0, ya que suponemos que no ha encontrado la actividad, pero en el caso de que haya un cambio no se repite el bucle.
		 printf("\n--- Reserva actividad ---\n");
		
		printf("Introduce el anio:");
		scanf("%i", &anio);
		
		printf("Intrdouce el  mes(numero):");
		scanf("%i", &mes);
		
		printf("Introduce el dia (numero):");
   		scanf("%d", &dian); 
   		
   		printf("Introduce el dia de la semana:");
   		scanf(" %[^\n]", diasemana); 
   					
		printf("Introduce la hora inicial:");
		scanf(" %[^\n]",horai); 
		
		printf("Introduce la hora final:");
		scanf(" %[^\n]",horaf); 
		
		printf("Introduce la actividad a la que se quiere apuntar: "); 
		scanf(" %[^\n]", nombreactividad); 
		
		printf("Modalidad: ");
		scanf(" %[^\n]", modalidad);
		
		printf("Introduce el centro deportivo:");
		scanf(" %[^\n]",centro); 
		
		printf("Introduce el tipo de actividad:");
		scanf(" %[^\n]",tipactividad); 
		
		
		
		//strcmp sirve para comparar cadenas, si devulve 0,que significa que los textos son iguales. 
		// El strcmp compara dos cadenas de caraceteres. En este caso queremos comporar los caracteres de la lista
		// El punto es para que dentro del vector de la lista comprare cada apartado con otro
		for(i = 0; i<n; i++){
			if(lista[i].ano == anio && lista[i].mes == mes &&lista[i].dia == dian && strcmp(lista[i].dia_semana, diasemana)==0 &&strcmp(lista[i].hora_inicial, horai)==0
			&&strcmp(lista[i].hora_final, horaf)==0 && strcmp(lista[i].actividad, nombreactividad)==0 && strcmp(lista[i].modalidad, modalidad)==0
			&&strcmp(lista[i].centro_deportivo,centro)==0	&& strcmp(lista[i].tipo_actividad,tipactividad)==0){
			
			 	
				encontrado=1; // Encuentra a actividad
				
				
				// Ahora hay que ver si hay plazas libres
				if(lista[i].libres > 0){ // Si es mayor a 0, es 1 por lo q hay plazas libres.
					printf("Hay plazas. Reserva confirmada\n ");
					lista[i].libres --;
					lista[i].ocupadas++;
				
					opcion = 2; //Sirve para salir del bucle
				
				}else{
					printf("No quedan plazas disponibles\n");
					printf("Seleccione una opcion: 1 Volver a introducir los datos/ 2 Salir de la opcion reserva\n");
					scanf("%i", &opcion); // Guarda el número en la variable opcion q hay aelegido el usuario
				}
					break; //salimos del for
					
			}
		}
	
		if(encontrado == 0){ //Si no la encuentra entones te da las opciones, si seleccionas 
            printf("No quedan existe la actividad que desea reservar\n");
			printf("Seleccione una opcion: 1 Volver a introducir los datos/ 2 Salir de la opcion reserva\n");
			scanf("%i", &opcion);
		}
		
	}while(opcion==1); //Si encontrado es 0, es decir se cumeple que cuando enontrado = 0 si se repite el bucle. Si el usuario introduce el 1 se repite el bucle
	//Si elige la opción 1, entonces es verdadera la condición y se vuelve a ejecutar el bucle
}


Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos){
	
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

int mostrar_centros(AnalisisDatos *datos, int num_datos, char centros[][100])
{
    //contador de centros
	int num_centros = 0;
    
	int i, j;
	
	//Recorremos la base de datos
    for ( i = 0; i < num_datos; i++)
    {
    	
		//variable bandera inicializada como falso, centro no repetido
    	int repetido = 0;
    	
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
}

void mostrar_actividades_centro(const Centro *c){
	
    int i;

    if (c == NULL)
    {
        printf("Centro no valido\n");
        return;
    }

    printf("Centro deportivo: %s\n", c->nombre);
    printf("---------------------------------\n");

    if (c->num_actividades == 0)
    {
        printf("Este centro no tiene actividades disponibles\n");
        return;
    }

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

void anadir_favorito(const char *nombreFichFav, const char *usuarioLogueado, const Centro *c){
	
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
    fprintf(f, "%s;%s;%s\n", usuarioLogueado, c->nombre, c->lista_actividades[opcion - 1].actividad);

    fclose(f);

    printf("Actividad anadida a favoritos correctamente.\n");
}
