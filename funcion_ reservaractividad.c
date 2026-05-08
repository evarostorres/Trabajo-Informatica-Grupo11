#include <stdio.h>
#include <string.h>
#include "EstructProtot.h"

void reservar_actividad(AnalisisDatos lista[], int n){
  	char centros[100][100];
    char nombre_centro[100];

    int num_centros;
	
	Centro Centro_usuario;
	int opcion_centro;
	int opcion_act;
	int i;
	int salir = 0;

	//LLAMADA FUNCION 1
	num_centros = mostrar_centros(lista, n, centros);
	printf("\n-------Lista de centros -------\n");

	do{ // Este do while sirve para q lo vuelva a pedir hasta q el usuario introduzca el número correcto
	
		
		printf("Selecciona un numero del centro donde se quiere apuntar(1-%d): ", num_centros);
		scanf("%i", &opcion_centro); //Aqui el usuario introduce la posición, del centro.
		
	}while(opcion_centro<1 || opcion_centro>num_centros);
	
	
	//LLAMADA FUNCION 2
	strcpy(nombre_centro, centros[opcion_centro - 1]);	 // En el 1 argumento le restamos 1, pq es una cadena	
	Centro_usuario = crear_centro_por_nombre(nombre_centro, lista, n);

	printf("\n-------Lista de actividades por centro -------\n");
	// imprimios la lista de actividades
	for(i = 0; i<Centro_usuario.num_actividades; i++){ // El punto sirve para acceder a la estructura
		printf("%d. %s || %s - %s || Libres: %d\n", i + 1, // Se pone i + 1 pq el ususario ve eso, ya que si introduce 1, la posición es 0
    	Centro_usuario.lista_actividades[i].actividad,
    	Centro_usuario.lista_actividades[i].hora_inicial,
        Centro_usuario.lista_actividades[i].hora_final,
   		Centro_usuario.lista_actividades[i].libres);
		
	}
	//Selección de la  actividad q desea reservar
	do{
		printf("Selecciona un numero de la actividad a la que se quiere apuntar ", num_centros);
		scanf("%i", &opcion_act);	
	}while(opcion_act<1 || opcion_act > Centro_usuario.num_actividades);
	
	opcion_act--;
	
	while(salir ==0){

	//Ahora reservamos la actividad
	if(Centro_usuario.lista_actividades[opcion_act].libres > 0){
		for(i = 0; i<n; i++){
			if(strcmp(lista[i].centro_deportivo, Centro_usuario.nombre)==0 && strcmp(lista[i].actividad,Centro_usuario.lista_actividades[opcion_act].actividad)==0
			&& strcmp(lista[i].hora_inicial,Centro_usuario.lista_actividades[opcion_act].hora_inicial)== 0){
				
				lista[i].ocupadas++;
                lista[i].libres--;
                printf("RESERVA CONFIRMADA\n");
                
                salir = 1; 
                
                break;
				
			}
		}
	//En el caso q no haya plazas
	}else{
		int opcion;
		int encontrada = 0;
		printf("No hay plazas disponibles\n");
		printf("SUGERENCIAS DENTRO DEL CENTRO CON LOS MISMOS HORARIOS DE LA ACTIVIDAD SELECCIONADA:\n");
		
		
		for(i = 0; i<Centro_usuario.num_actividades; i++){
			if(strcmp(Centro_usuario.lista_actividades[i].hora_inicial, Centro_usuario.lista_actividades[opcion_act].hora_inicial)==0
			&&strcmp(Centro_usuario.lista_actividades[i].hora_final, Centro_usuario.lista_actividades[opcion_act].hora_final)==0
			&& Centro_usuario.lista_actividades[i].libres>0 && i != opcion_act){ 
				printf("%d. %s || %s - %s || Libres: %d\n", i + 1, // Se pone i + 1 pq el ususario ve eso
		    	Centro_usuario.lista_actividades[i].actividad,
		    	Centro_usuario.lista_actividades[i].hora_inicial,
		        Centro_usuario.lista_actividades[i].hora_final,
		   		Centro_usuario.lista_actividades[i].libres);
				
				encontrada = 1;
				
			}
			
		} 
		if(encontrada ==0){
			printf("NO quedan actividades a esa hora\n");
		}
		printf("1. Volver a intentar: \n");
		printf("2. Salir: \n");
	
		scanf("%d", &opcion); 
			if(opcion == 2){
				salir = 1;
			}else{
				do{
				printf("Selecciona otra actividad: ");
           			scanf("%d", &opcion_act);
				}while(opcion_act < 1 || opcion_act > Centro_usuario.num_actividades);
				opcion_act--;
			}
		}		
	}
}
