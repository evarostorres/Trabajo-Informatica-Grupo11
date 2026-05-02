#include <stdio.h>
#include <string.h>
#include "estructProtot.h" 

#define MAX_LONG 20

int iniciar_sesion(char *guardarUsuario) {
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