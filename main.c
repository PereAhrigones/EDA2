#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

User_data* encontrar_usuario(char username[], User_list *lista){
    User_data *element = lista->first;
    while (element != NULL) {
        if (strcmp(username, element->username) == 0) {
            return element;
        }
        element = element->next;
    }
    return NULL;
}

timeline* leer_posts(User_list* lista){
    FILE* fd = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios.txt", "r");
    if (fd == NULL){
        printf("\nError al abrir el archivo.\n");
        return NULL;
    }
    char user[MAX_USERNAME_LENGTH];
    char post[MAX_POST_LENGHT];
    timeline* tl = (timeline *) malloc(sizeof(timeline));
    tl->first = (publicacion *) malloc(sizeof(publicacion));
    if(fgets(post, MAX_POST_LENGHT, fd) != NULL){
        //En el archivo hay un enter depués del post y la siguiente línea es el usuario
        fscanf(fd, "%s", user);
        insert_post(tl->first, encontrar_usuario(user, lista), post);
        tl->first->prev = NULL;
        tl->last = tl->first;
        tl->size = 1;
    }
    //Usar fgets
    while (!feof(fd)){
        fgets(post, MAX_POST_LENGHT, fd);
        fscanf(fd, "%s", user);
        push_post(tl, encontrar_usuario(user, lista), post);
    }
    fclose(fd);
    return tl;
}



int main() {
    //chcp(65001>0) Había algo así para poner los acentos pero no me acuerdo de como era y no lo he conseguido encontrar
    User_list* lista = ficherodatos();//Cargamos lo que está en el fichero de usuarios al empezar
    timeline* tl = leer_posts(lista);//Cargamos todos los posts
    menu(lista, tl);//Antes del menú hay que cargar las cosas
}






