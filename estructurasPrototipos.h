typedef struct {
    int ano;
    int mes;
    int dia;
    char dia_semana[20];
    char hora_inicial[10];
    char hora_final[10];
    char actividad[100];
    char modalidad[10];
    char centro_deportivo[100];
    int plazas;
    int ocupadas;
    int libres;
    char tipo_actividad[50];    
} AnalisisDatos;


typedef struct {
	// Nombre del centro
    char nombre[100]; 
	// Cuántas actividades tiene
    int num_actividades;  
	// Vector dinámico de actividades
    AnalisisDatos *lista_actividades;  
} Centro;


/*Las dos siguientes estructuras son muy parecidas porque 
en una función se ha trabajado con memoria dinamica y en otra no*/
typedef struct {
    char usuario[20];
    char centro[50];
    char actividad[50];
} Favorito;

typedef struct {
	char *usuario;
	char *actividad;
	char *centro;
} Favoritos;


typedef struct {
    Favoritos *lista;
    int num_favoritos;
} ListaFavoritos;


// Prototipos de las funciones para que main las reconozca
// Funciones de Eva
int iniciar_sesion(char *guardarUsuario);										
void registrar_usuario();
void ver_favoritos(const char *nombre_fichero, const char *usuarioLogueado);
void eliminar_favorito(Favorito fav, const char *nombreFichFav, const char *usuarioLogueado);

// Funciones de Alba
Centro crear_centro_por_nombre(const char *nombre, AnalisisDatos *datos, int num_datos); 		
int mostrar_centros(AnalisisDatos *datos, int num_datos, char centros[][100]);	
void mostrar_actividades_centro(const Centro *c);
void anadir_favorito(const char *nombreFichFav, const char *usuarioLogueado, const Centro *c);

// Funciones de Inés
AnalisisDatos *lectura_fichero(const char *nombrearchivo, int *n);	
void reservar_actividad(AnalisisDatos lista[], int n);   			

// Funciones de Laura
void ver_frecuencia(AnalisisDatos datos[], int n);      		
void ver_graficas_centros(AnalisisDatos datos[], int n);
