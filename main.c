#include <stdio.h>
#include "main.h"






int main() {
    //chcp(65001>0) Había algo así para poner los acentos pero no me acuerdo de como era y no lo he conseguido encontrar
    User_list* lista = ficherodatos();//Cargamos lo que está en el fichero al empezar
    menu(lista);//Antes del menú hay que cargar las cosas
}






