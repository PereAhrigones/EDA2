//
// Created by senyo on 29/5/2023.
//

#ifndef EDA2_PUBLICACION_H
#define EDA2_PUBLICACION_H
#define MAX_WORD_LENGHT 60
#define ITEM_NOT_FOUND 0
#define MAX_NOTIFICACIONES 100
#define MAX_NOTIF_LENGTH 100
#include "usuario.h"

typedef struct _notificacion{
    char notif[MAX_NOTIFICACIONES][MAX_NOTIF_LENGTH];
    int front;
    int rear;
}notificaciones;

typedef struct _post{
    char contenido[MAX_POST_LENGHT];
    char username[MAX_USERNAME_LENGTH];
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

void enqueue(char mensaje[], notificaciones* lista);
void dequeue(notificaciones* lista);
void show(notificaciones* lista);
int isEmpty(notificaciones* lista);
int isFull(notificaciones* lista);
int postsfichero(timeline *tl);
void insert_post(publicacion* publ,char user[] , char post[]);
void push_post(timeline* tl,char user[], char post[]);
void pop_post(timeline* tl);
void bubblesort_dictionary(diccionario* dict[],int n) ;
void show_top(timeline* tl);
diccionario *contar_palabras(timeline *tl, int* contar_palabras); //https://parzibyte.me/blog/2018/11/13/separar-cadena-delimitadores-c-strtok/
diccionario *create_array_dict(diccionario *dict, int tamaño);

void show_old_posts_from_user(char user[], timeline* tl);
void show_last_post_from_user(char user[], timeline* tl);
//https://gist.github.com/kylef/86784/fe97567ec9baf5c0dce3c7fcbec948e21dfcce09
diccionario **dictAlloc();
void dictDealloc(diccionario **dict);
int getItem(diccionario *dict, char *key);
void delItem(diccionario **dict, char *key);


#endif //EDA2_PUBLICACION_H