#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructProtot.h" // Incluimos el archivo donde esta AnalisisDatos

//esta funcion es para ver la ocupacion de cada actividad por centros

// AnalisisDatos datos[] es el tipo de dato y nombre de la variable del vector de estructuras
// int n es para el numero total de actividades

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
            
            // Solo comparamos si ambos registros son del centro elegido
            if (strcmp(datos[j].centro_deportivo, centroElegido) == 0 && strcmp(datos[j+1].centro_deportivo, centroElegido) == 0) {
                
                float p1 = (float)datos[j].ocupadas / datos[j].plazas;
                float p2 = (float)datos[j+1].ocupadas / datos[j+1].plazas;

                if (p1 < p2) { // Ordenamos de mayor a menor popularidad SEGÚN EL PORCENTAJE
                    temp = datos[j];
                    datos[j] = datos[j + 1];
                    datos[j + 1] = temp;
                }
            }
        }
    }



//3. IMPRIMIMOS LAS ACTIVIDADES PARA CADA CENTRO

    printf("\n LAS 10 ACTIVIDADES MAS POPULARES EN %s \n", centroElegido); 
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
    		
    		fprintf (archivo, "LAS 10 ACTIVIDADES MAS POPULARES EN %s\n", centroElegido);
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



/*

prototipo:  void ver_frecuencia(AnalisisDatos datos[], int n);
llamada (ponerlo en el case): ver_frecuencia(datos, actividades);

*/






