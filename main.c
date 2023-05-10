#include <stdio.h>
#include "main.h"
#include "menu.c"

void datosfichero(FILE*fp){
    User_data *user_search;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;


}

void ficherodatos(FILE* fp){

}

int main() {
    menu();//Antes del menú hay que cargar
}






