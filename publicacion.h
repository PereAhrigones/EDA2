//
// Created by senyo on 29/5/2023.
//

#ifndef EDA2_PUBLICACION_H
#define EDA2_PUBLICACION_H
#define MAX_WORD_LENGHT 60
#define ITEM_NOT_FOUND 0
#include "usuario.h"

typedef struct _post{
    char contenido[MAX_POST_LENGHT];
    User_data *usuario;
    struct _post* next;
    struct _post* prev;
}publicacion;

typedef struct{
    publicacion *first;
    publicacion *last;
    int size;
}timeline;

typedef struct _dicc{
    int counter;
    char *key;
    struct _dicc *next;
}diccionario;

int postsfichero(timeline *tl);
void insert_post(publicacion* publ,User_data* user , char post[]);
void push_post(timeline* tl,User_data* user, char post[]);
void pop_post(timeline* tl);
void bubblesort_dictionary(diccionario* dict[],int n) ;
void show_top(timeline* tl);
diccionario *contar_palabras(timeline *tl, int* contar_palabras); //https://parzibyte.me/blog/2018/11/13/separar-cadena-delimitadores-c-strtok/
void show_recent_posts_from_user(User_data* user, timeline* tl, int n);
void show_old_posts_from_user(User_data* user, timeline* tl, int n);
diccionario *create_array_dict(diccionario *dict, int tamaño);

//https://gist.github.com/kylef/86784/fe97567ec9baf5c0dce3c7fcbec948e21dfcce09
diccionario **dictAlloc();
void dictDealloc(diccionario **dict);
int getItem(diccionario *dict, char *key);
void delItem(diccionario **dict, char *key);


#endif //EDA2_PUBLICACION_H
