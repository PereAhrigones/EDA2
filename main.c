#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


timeline* leer_posts(){
    FILE* fd = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios.txt", "r");
    if (fd == NULL){
        printf("\nError al abrir el archivo.\n");
        return NULL;
    }
    char post[MAX_POST_LENGHT];
    timeline* tl = (timeline *) malloc(sizeof(timeline));
    tl->first = (publicacion *) malloc(sizeof(publicacion));
    if(fgets(post, MAX_POST_LENGHT, fd) != NULL){
        //Mirar como hacer lo de saber de que usuario es el post.
    }
    //Usar fgets
    while (fscanf(fd, "%s", post[MAX_POST_LENGHT]) == 1){

    }
    fclose(fd);
}



int main() {
    //chcp(65001>0) Había algo así para poner los acentos pero no me acuerdo de como era y no lo he conseguido encontrar
    User_list* lista = ficherodatos();//Cargamos lo que está en el fichero al empezar
    timeline* tl = leer_posts();
    menu(lista);//Antes del menú hay que cargar las cosas
}






