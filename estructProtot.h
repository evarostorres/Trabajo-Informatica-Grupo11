typedef struct {
    int ano;
    int mes;
    int dia;
    char *dia_semana;
    char *hora_inicial;
    char *hora_final;
    char *actividad;
    char *centro_deportivo;
    int plazas;
    int ocupadas;
    int libres;
    char *tipo_actividad;
} AnalisisDatos;


typedef struct {
    char *nombre;                       // Nombre del centro
    int num_actividades;                // Cuántas actividades tiene
    AnalisisDatos *lista_actividades;   // Vector dinámico de actividades
} Centro;

typedef struct {
    char usuario[20];
    char centro[50];
    char actividad[50];
} Favorito;

// Prototipos de las funciones para que main las reconozca
int iniciar_sesion(char *guardarUsuario);										// Funciones de Eva
void registrar_usuario();
void ver_favoritos(const char *nombre_fichero, const char *usuarioLogueado);
void gestionar_favorito(Favorito fav, const char *nombreFichFav, const char *usuarioLogueado);

void mostrar_actividades_centro(const Centro *c);   	// Función de Alba
void añadir_favoritos(char *centro, char *actividad);

void reservar_actividad(AnalisisDatos lista[], int n);   	// Función de Inés
void verFrecuencia(AnalisisDatos datos[], int n);      // Función de Laura