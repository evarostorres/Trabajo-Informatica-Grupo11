#include "pbPlots.h"
#include "supportLib.h"
#include "estructProtot.h"

//esta funcion es para ver la ocupacion general de cada centro representada graficamente

void ver_graficas_centros(AnalisisDatos datos[], int n){
	
	//1. ORDENAMOS LOS CENTROS PARA QUE LOS QUE SEAN IGUALES ESTÉN JUNTOS
	
	AnalisisDatos aux;
	int i, j, k;
	
	for (i = 0; i < n - 1; i++){     
        for (j = 0; j < n - i - 1; j++){  
            
            //si el nombre del centro es mayor alfabéticamente que el siguiente los cambiamos
            if (strcmp(datos[j].centro_deportivo, datos[j + 1].centro_deportivo) > 0){
                
                aux = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = aux;
            }
        }
    } 
    
    //2. CALCULAMOS LA MEDIA DE OCUPACIÓN EN CADA CENTRO
    
    double indicesX[100];
    double mediasY[100];
    
    char centroActual[100];
    float p;
    
    int numCentros = 0;
	
	
	for (i = 0; i < n - 1; i++){ //recorremos el vector de centros (ya ordenados)
	 	
	 	//si es el primer centro de la lista o si es diferente al anterior
	 	if (i == 0 || strcmp(datos[i].centro_deportivo, datos[i - 1].centro_deportivo) != 0){
	 		
	 		strcpy(centroActual, datos[i].centro_deportivo); //establecemos este centro como el actual
	 		
	 		float sumaPorcentajes = 0;
	        int numActividades = 0;
	 		
			for (k = 0; k < n; k++){
	 			
				if (strcmp(datos[k].centro_deportivo, centroActual) == 0) { //calculamos el porcentaje de ocupación de cada actividad
                    
				    p = ((float)datos[k].ocupadas / datos[k].plazas) * 100;
				    sumaPorcentajes += p;
				    numActividades++;
			    }
		    }
	 	
	 	    mediasY[numCentros] = sumaPorcentajes / numActividades; //calculamos las medias de porcentajes
	 	    indicesX[numCentros] = numCentros + 1;
		 
		    numCentros++; 	 	
	    }
    }
    
    
    //3. REPRESENTAMOS GRÁFICA
    
    _Bool success;
	StringReference *errorMessage;

	StartArenaAllocator();

	RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
	errorMessage = (StringReference *)malloc(sizeof(StringReference));
	success = DrawScatterPlot(imageRef, 800, 600, indicesX, numCentros, mediasY, numCentros, errorMessage);

	if(success){
		ByteArray *pngdata = ConvertToPNG(imageRef->image);
		DeleteImage(imageRef->image);
        WriteToFile(pngdata, "analisisOcupacionCentros.png");
     	
	}else{
		fprintf(stderr, "Error: ");
		for(int i = 0; i < errorMessage->stringLength; i++){
			fprintf(stderr, "%c", errorMessage->string[i]);
		}
		fprintf(stderr, "\n");
    }

	FreeAllocations();

	return success ? 0 : 1;
	
	
	
}
    
	
	
	
/*
PROTOTIPO:  void ver_graficas_centros(AnalisisDatos datos[], int n);
LLAMADA(en el case 4):  ver_graficas_centros(datos, actividades);
*/
   

