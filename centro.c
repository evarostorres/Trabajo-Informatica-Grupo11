#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datos.h"
#include "centro.h"

void mostrar_actividades_centro(const Centro *c)
{
	int i;
	AnalisisDatos acti;
	
	if (c == NULL)
	{
		printf("Centro no válido\n");
		return;
	}
	
	printf("Centro deportivo: %s\n", c->nombre);
	printf("---------------------------------\n");
	
	if (c->num_actividades == 0)
	{
		printf("Este centro no tiene actividades disponibles\n");
		return;
	}
	
	for (i = 0; i < c->num_actividad; i++)
	{
		actividad == c->num_actividad[i];
		
		printf("Actividad: %s\n", acti.actividad);
		
		if( strcmp(acti.tipo_actividad, "actividad_dirigida") == 0)
		{
			printf("Tipo: Actividad dirigida\n");
		}
		else if (strcmp(acti.tipo_actividad, "uso_libre") == 0)
		{
			print("Tipo: Uso libre\n");
		}
		else
		{
			printf("Tipo: %s\n", acti.tipo_actividad);
		}
		
		printf("Horario: %s - %s\n", acti.hora_inicial, activity.hora_final);
		printf("Plazas totales: %d\n", acti.plazas);
		printf("Plazas ocupadas: %d\n", acti.ocupadas);
		printf("Plazas libres: %d\n", acti.libres);
		
		if (actividad.libres == 0)
		{
			printf("Estado: completo\n");
		}
		else 
		{
			printf("Estado: plazas disponibles");
		}
		printf("---------------------------------\n");
	}
}