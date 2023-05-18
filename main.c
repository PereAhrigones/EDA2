#include <stdio.h>
#include "main.h"






int main() {
    User_list* lista = ficherodatos();//Cargamos lo que está en el fichero al empezar
    menu(lista);//Antes del menú hay que cargar las cosas
}






