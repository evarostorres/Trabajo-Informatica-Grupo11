#include <stdio.h>
#include <string.h>
#include "estructProtot.h" 

#define MAX_LONG 21

void registrar_usuario() {
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