#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG 21

int main() {
	int opcionAcceso;
	int opcionMenu;
	int InSesionExitoso = 0;	// Bandera para saber si podemos pasar al menú principal
	
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
                if (iniciarSesion() == 1) {
                    InSesionExitoso = 1;
                    opcionAcceso = 3; // Forzamos que la condición del while sea falsa
                }
                break;
            case 2: 
				registrarUsuario(); 	// Llamada a la función
				break;
            case 3: 
				printf("Saliendo del programa...\n"); 
				break;
            default: 
				printf("Opcion no valida.\n");
        }
    } while (opcionAcceso != 3);


    // Abrimos el fichero de los datos
	FILE *pf = fopen("dataset.csv", "r");
    if (pf == NULL) {
        printf("Error al abrir el fichero.\n");
        return -1;
    }
    
    
    if (InSesionExitoso) {
		printf("\n==============================================");
		printf("\n SISTEMA DE GESTION DE ACTIVIDADES DEPORTIVAS ");
		printf("\n==============================================\n");
	    printf("1. Listado de actividades\n");
	    printf("2. Reservar actividad\n");
	    printf("3. Ver popularidad/frecuencia\n");
	    printf("4. Favoritos\n");
	    printf("0. Salir\n");
	    printf("\nSeleccione una opcion: ");
	}
}

void registrarUsuario() {
    char nuevoUsuario[MAX_LONG];
    char nuevaContrasena[MAX_LONG];
    FILE *fichUsuariosContrasenas;

    fichUsuariosContrasenas = fopen("usuarioscontrasenas.txt", "a"); // "a" abre para añadir datos al final del fichero
    if (fichUsuariosContrasenas == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("\n--- Registro de Nuevo Usuario ---\n");
    printf("Introduce nombre de usuario: ");
    scanf("%s", nuevoUsuario);
    printf("Introduce contraseña: ");
    scanf("%s", nuevaContrasena);

    // Guardamos el usuario y la contraseña separados por un espacio
    fprintf(fichUsuariosContrasenas, "%s %s\n", nuevoUsuario, nuevaContrasena);
    fclose(fichUsuariosContrasenas);

    printf("\n¡Registro completado con éxito!\n");
}

int iniciarSesion() {
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