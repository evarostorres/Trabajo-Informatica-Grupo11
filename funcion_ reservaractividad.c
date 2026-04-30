#include <stdio.h>
#include <string.h>
#include "EstructProtot.h"

// Aquí es dónde se ejecuta la función
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
	int i;
	int encontrado; 
	int opcion;
		
	
		do{
			encontrado = 0; // Igualamos el encontrado a 0, ya que suponemos que no ha encontrado la actividad, pero en el caso de que haya un cambio no se repite el bucle.
			 printf("\n--- Reserva actividad ---\n");
			
			printf("Introuce el anio:",anio);
			scanf("%i", &anio);
			
			printf("Introuce el  mes(numero):", mes);
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
			

			
			
			//strcmp sirve para comparar cadenas, si devulve 0,que significa que los textos son iguales. 
			// El strcmp compara dos cadenas de caraceteres. En este caso queremos comporar los caracteres de la lista
			// El punto es para que dentro del vector de la lista comprare cada apartado con otro
				for(i = 0; i<n; i++){
					if(lista[i].ano == anio&&lista[i].mes == mes &&lista[i].dia == dian &&strcmp(lista[i].dia_semana, diasemana)==0 &&strcmp(lista[i].hora_inicial, horai)==0
					&&strcmp(lista[i].hora_final, horaf)==0 && strcmp(lista[i].actividad, nombreactividad)==0 && strcmp(lista[i].tipo_actividad, modalidad)==0
					&&strcmp(lista[i].centro_deportivo,centro)==0){
					
					 	
						encontrado=1; // Encuentra a actividad
						
						
						// Ahora hay que ver si hay plazas libres
						if(lista[i].libres > 0){ // Si es mayor a 0, es 1 por lo q hay plazas libres.
							printf("Hay plazas. Reserva confirmada\n ");
							lista[i].libres --;
							lista[i].ocupadas++;
						}else{
							printf("No quedan plazas disponibles\n");
							printf("Seleccione una opcion: 1 Volver a introducir los datos/ 2 Salir de la opción reserva");
							scanf("%i", &opcion); // Guarda el número en la variable opcion q hay aelegido el usuario
							
							if(opcion == 1){
								encontrado = 0; // Se repite el bucle. Si fuese encontrado=1 no se repite el bucle 
							}
				
			
						}
						break; //salimos del for
						
					}
		}
		
	}while(opcion==1); //Si encontrado es 0, es decir se cumeple que cuando enontrado = 0 si se repite el bucle
	
}
//Prototipo void reservar_actividad(AnalisisDatos lista[], int n);
//Llamda  		reservar_actividad(lista, n);