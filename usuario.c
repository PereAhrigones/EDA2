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
    strcpy(miembro->likes[1], gusto1);
    strcpy(miembro->likes[2], gusto2);
    strcpy(miembro->likes[3], gusto3);
    strcpy(miembro->likes[4], gusto4);
    strcpy(miembro->likes[5], gusto5);
    miembro->nota = nota;
    miembro->nota_max = nota_max;
    miembro->nota_min = nota_min;
    miembro->num_valoraciones = valoraciones;
    miembro->next = NULL;
}

void push(User_list* lista, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota) {
    User_data *usuario = lista->first;
    while (usuario->next != NULL) {
        usuario = usuario->next;
    }

    usuario->next = (User_data *) malloc(sizeof(User_data));
    //Aquí van todos los datos
    insert_user(usuario->next, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota);
    lista->last = usuario->next;
    usuario->next->prev = usuario;
    lista->size++;
}

void guardar_gustos(User_list* lista,char username[MAX_USERNAME_LENGTH],char gustos[MAX_LIKE_LENGTH],int numero){ //No está revisado si esta función tiene sentido o.
    User_data *user_likes = lista->first;
    while (user_likes->next != NULL) {
        if (strcmp(user_likes->username, username) == 0) { //Creo, no estoy seguro, pero  a esto creo que le falta cosa.
            strcpy(user_likes -> likes[numero] ,gustos);
            return;
        }
    }
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

    // Enlazar el nuevo nodo al nodo anterior en la pila
    if (stack->top != NULL) {
        stack->top->below = newRequest; //creo que ahora está bien
    }
    newRequest->below = NULL;

    // Actualizar el top de la pila
    stack->top = newRequest;
}

Friend_request* popRequest(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Error: la pila de solicitudes de amistad está vacía\n");
        return NULL;
    }

    // Obtener la solicitud de amistad en el top de la pila
    Friend_request* topRequest = stack->top;

    // Actualizar el top de la pila al siguiente nodo
    stack->top = stack->top->next;

    // Devolver la solicitud de amistad desempujada
    return topRequest;
}

void valoracion(User_data* user,float nota_dada){

    if(nota_dada < user->nota_min) user->nota_min = nota_dada;

    if (nota_dada > user->nota_max ) user->nota_max = nota_dada;

    user->nota = (user->nota * user->num_valoraciones + nota_dada) / (user->num_valoraciones+1);

    user->num_valoraciones++;
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
    printf("Enviando solicitud de amistad de %s a %s\n", usuarioActual, usuarioDestino);

}

