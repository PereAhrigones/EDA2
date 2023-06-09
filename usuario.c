//
// Created by senyo on 29/5/2023.
//

#include "usuario.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//insert_user igual se puede borrar
void insert_user(User_data* miembro, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota, float nota_max, float nota_min, int valoraciones){
    strcpy(miembro->username, nombre_usuario);
    strcpy(miembro->email, correo);
    strcpy(miembro->password, contraseña);
    strcpy(miembro->city, ciudad);
    miembro->birth = año;
    miembro->user_number = num_usuario;
    strcpy(miembro->likes[0], gusto1);
    strcpy(miembro->likes[1], gusto2);
    strcpy(miembro->likes[2], gusto3);
    strcpy(miembro->likes[3], gusto4);
    strcpy(miembro->likes[4], gusto5);
    miembro->nota = nota;
    miembro->nota_max = nota_max;
    miembro->nota_min = nota_min;
    miembro->num_valoraciones = valoraciones;
    miembro->next = NULL;
}

void push(User_list* lista, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota, float nota_max, float nota_min, int valoraciones) {
    User_data *nuevo_usuario = (User_data*) malloc(sizeof(User_data));  //Crear un nuevo usuario
    strcpy(nuevo_usuario->username, nombre_usuario);
    strcpy(nuevo_usuario->email, correo);
    strcpy(nuevo_usuario->password, contraseña);
    strcpy(nuevo_usuario->city, ciudad);
    nuevo_usuario->birth = año;
    nuevo_usuario->user_number = num_usuario;
    strcpy(nuevo_usuario->likes[0], gusto1);
    strcpy(nuevo_usuario->likes[1], gusto2);
    strcpy(nuevo_usuario->likes[2], gusto3);
    strcpy(nuevo_usuario->likes[3], gusto4);
    strcpy(nuevo_usuario->likes[4], gusto5);
    nuevo_usuario->nota = nota;
    nuevo_usuario->nota_max = nota_max;
    nuevo_usuario->nota_min = nota_min;
    nuevo_usuario->num_valoraciones = valoraciones;
    nuevo_usuario->solicitudes = NULL;
    nuevo_usuario->next = NULL;
    nuevo_usuario->prev = NULL;
    if (lista->first == NULL) {
        lista->first = nuevo_usuario;
        lista->last = nuevo_usuario;
    } else {
        nuevo_usuario->prev = lista->last;
        lista->last->next = nuevo_usuario;
        lista->last = nuevo_usuario;
    }
    lista->size++;  // Incrementar el tamaño de la lista
}

void limpiar_User_data(User_data* guardar) {
    if (guardar == NULL) {
        return;
    }

    free(guardar->email);
    free(guardar->password);
    free(guardar->username);
    free(guardar->city);

    for (int i = 0; i < MAX_LIKE_LENGTH; i++) {
        free(guardar->likes[i]);

    }

    guardar->user_number = 0;
    guardar->birth = 0;

    free(guardar);
}




void borrar_lista_de_usuarios(User_list* lista) {

    if (lista == NULL) {
        return;
    }
    User_data* actual = lista->first;

    while(actual!= NULL){
        limpiar_User_data(actual);
        actual = actual->next;

    }
    lista->first = NULL;
    lista->last = NULL;
    lista->size = 0 ;
}

void initStack(Stack* stack) {
    stack->top = NULL;
}


// Función para verificar si la pila está vacía
int isStackEmpty(Stack* stack) {
    return (stack->top == NULL);
}


void pushRequest(Stack* stack, const char* sender, const char* receiver) {
    // Crear un nuevo nodo para la solicitud
    Friend_request* newRequest = (Friend_request*)malloc(sizeof(Friend_request));
    strcpy(newRequest->sender, sender);
    strcpy(newRequest->receiver, receiver);

    if (stack->top == NULL){
        newRequest->below = NULL;
        stack->top = newRequest;
    } else{
        newRequest->below = stack->top;
        stack->top = newRequest;
    }
}

Friend_request* popRequest(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Error: la pila de solicitudes de amistad está vacía\n");
        return NULL;
    }

    // Obtener la solicitud de amistad en el top de la pila
    Friend_request* topRequest = stack->top;

    // Actualizar el top de la pila al siguiente nodo
    stack->top = stack->top->below;

    // Devolver la solicitud de amistad desempujada
    return topRequest;
}

void enviarSolicitudAmistad(Stack* stack, char usuarioActual[], char usuarioDestino[]) {
    // Verificar si ya hay una solicitud pendiente o si ya son amigos
    Friend_request* solicitudActual = stack->top;
    while (solicitudActual != NULL) {
        if (strcmp(solicitudActual->sender, usuarioActual) == 0 &&
            strcmp(solicitudActual->receiver, usuarioDestino) == 0) {
            printf("Ya has enviado una solicitud de amistad a %s\n", usuarioDestino);
            return;
        }
        solicitudActual = solicitudActual->below;
    }

    // Enviar solicitud de amistad
    pushRequest(stack, usuarioActual, usuarioDestino);
    printf("Se ha enviado una solicitude de amistad de %s a %s\n", usuarioActual, usuarioDestino);
}

void guardar_amigos(User_list* lista){
    FILE *fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\amigos.txt", "w");
    if (fp == NULL){
        printf("Ha habido un error al actualizar la lista de amigos en la base de datos");
        return;
    }
    User_data *actual = lista->first;
    while (actual != NULL){
        int i = 0;
        fprintf(fp, "%s ", actual->username);
        while (strcmp(actual->amigos[i], " ") != 0){
            fprintf(fp, "%s ", actual->amigos[i]);
            i++;
        }
        fprintf(fp, "\n");
        actual = actual->next;
    }
}

void imprimir_lista_amigos(User_data *usuario){
    int i = 0;
    while (strcmp(usuario->amigos[i], " ") != 0){
        printf("%s\n", usuario->amigos[i]);
        i++;
    }
}

void valoracion(User_data* user, float nota_dada){

    if(nota_dada < user->nota_min) user->nota_min = nota_dada;

    if (nota_dada > user->nota_max ) user->nota_max = nota_dada;

    user->nota = (user->nota * user->num_valoraciones + nota_dada) / (user->num_valoraciones+1);

    user->num_valoraciones++;
}