PARTES DEL PROGRAMA: FUNCIONALIDADES

En este trabajo, la organización de un centro deportivo, hemos creado diversas funciones para facilitarle al usuario la entrada en el programa, y la posibilidad de hacer reservas, ver la frecuencia de las actividades, o macar como favoritos las clases que desee. Además, el sistema está pensado para mostrar los centros y las actividades por pantalla, y que a partir de esos datos cada usuario haga sus gestiones.

- Registro e Iniciar sesión → si el usuario no tiene cuenta, creará una para después poder iniciar sesión. Se creará una función que solicite al usuario la contraseña y si  la contraseña no es válida, el programa te lo vuelve a pedir. Para ver si la contraseña es correcta o no, el programa lo compara con un fichero.
  
- Menú principal → Para la gestión del listado de opciones hay que usar switch dentro de un bucle do while. Y en cada case llamar a cada función.

- Listado de actividades: crear una función que nos muestre todas las actividades disponibles. Dónde pida al usuario el nombre del centro, con un vector recorre la lista de actividades e imprime los detalles de cada actividad.

- Reservar actividad: Pide al usuario la actividad, día y hora. Buscamos la coincidencia con un vector. Si en la lista hay plazas libres entonces la reserva está confirmada. En cambio si no hay plazas libres el programa te vuelve a pedir los datos. Para eso usamos una función.
  
- Frecuencia: Crear una función que nos muestre la popularidad. El algoritmo consiste en crear un vector y ordenar de mayor a menor las actividades con más popularidad. Se hace con el algoritmo de la burbuja. Se añadirá también la  representación gráfica.

- Favoritos: crear una función dentro del bloque "listado de actividades" que permita añadir las actividades deseadas que se vean en la lista. Además, crear otra función que permita ver y modificar dichos favoritos (dentro del menú principal).
