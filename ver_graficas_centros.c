#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pbPlots.h"
#include "supportLib.h"
#include "estructProtot.h"

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
    
    
    
	// 3. REPRESENTAMOS GRÁFICA
    _Bool success;
    StringReference *errorMessage;
    StartArenaAllocator();

    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));

    //para que salgan intervalos de numeros 
    ScatterPlotSettings *settings = DefaultScatterPlotSettings();
    settings->width = 800;
    settings->height = 600;
    settings->autoBoundaries = false; 
    settings->xMin = 0;
    settings->xMax = numCentros + 1;  // El eje X acaba justo después del último centro
    settings->yMin = 0;
    settings->yMax = 100;             // El eje Y siempre será de 0 a 100
    
    //Títulos
    settings->title = CreateStringReference(L"Ocupacion Media por Centro", 25);
    settings->xLabel = CreateStringReference(L"Numero de Centro", 16);
    settings->yLabel = CreateStringReference(L"Porcentaje %", 12);

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = indicesX;
    series->xsLength = numCentros;
    series->ys = mediasY;
    series->ysLength = numCentros;
    series->linearInterpolation = false; // Para que salgan puntos sueltos
    
    ScatterPlotSeries *seriesList[] = {series};
    settings->scatterPlotSeries = seriesList;
    settings->scatterPlotSeriesLength = 1;

    // Esta función es como el ejemplo 2
    success = DrawScatterPlotFromSettings(imageRef, settings, errorMessage);

    if(success){
        ByteArray *pngdata = ConvertToPNG(imageRef->image);
        WriteToFile(pngdata, "analisisOcupacion.png");
        
        printf("\n*****************************************");
        printf("\n Grafica generada con éxito        ");
        printf("\n Archivo generado: analisisOcupacion.png        ");
        printf("\n***************************************\n");
        
      printf("\n-----LEYENDA DE CENTROS: consulte con la gráfica generada-----\n");
        int contadorLeyenda = 1; //lleva la cuenta de los numeros y los centros
        for (i = 0; i < n; i++) {
            // imprimir solo una vez cada nombre
            if (i == 0 || strcmp(datos[i].centro_deportivo, datos[i - 1].centro_deportivo) != 0) {
                printf(" Centro %d: %s\n", contadorLeyenda, datos[i].centro_deportivo);
                contadorLeyenda++;
            }
        }
        printf("--------------------------\n");
        
        DeleteImage(imageRef->image);
    
	}else{
        printf("\n[ERROR] No se pudo generar la grafica.\n");
    }    
        

    FreeAllocations();
    
    
}
    
	
	
	


/*
PROTOTIPO:  void ver_graficas_centros(AnalisisDatos datos[], int n);
LLAMADA(en el case 4):  ver_graficas_centros(datos, actividades);   
*/
