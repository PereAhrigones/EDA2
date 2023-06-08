//
// Created by senyo on 29/5/2023.
//

#ifndef EDA2_USUARIO_H
#define EDA2_USUARIO_H

#define MAX_USERNAME_LENGTH 16
#define MIN_USERNAME_LENGTH 4
#define MAX_PASSWORD_LENGTH 40
#define MIN_PASSWORD_LENGTH 8
#define MAX_CITY_NAME 58
#define MAX_EMAIL_LENGTH 60
#define MAX_LIKE_LENGTH 50
#define TRUE 1
#define FALSE 0
#define USERNAME_ALREADY_EXISTS -1
#define USER_ALREADY_EXISTS -2
#define USER_DOES_NOT_EXIST -3
#define NO_FILE_FOUND 500
#define MAX_POST_LENGHT 250
#define MAX_SOLICITUDES 10
#define MAX_LIKES 5
#define MAX_AMIGOS 50

typedef struct _friend_request {
    char sender[MAX_USERNAME_LENGTH];
    char receiver[MAX_USERNAME_LENGTH];
    struct _friend_request* below;
} Friend_request;

typedef struct _stack {
    Friend_request* top;
} Stack;

typedef struct _data{
    char username[MAX_USERNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char city[MAX_CITY_NAME];
    int birth;
    int user_number;
    char likes[MAX_LIKES][MAX_LIKE_LENGTH];
    float nota;
    float nota_max;
    float nota_min;
    int num_valoraciones;
    char amigos[MAX_AMIGOS][MAX_USERNAME_LENGTH];
    Stack *solicitudes; //Esto hay que verlo
    struct _data* next;
    struct _data* prev;
}User_data;


typedef struct{
    User_data* first;
    User_data* last;
    int size;
}User_list;


void insert_user(User_data* miembro, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota, float nota_max, float nota_min, int valoraciones);

void push(User_list* lista, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota, float nota_max, float nota_min, int valoraciones);
void limpiar_User_data(User_data* guardar);
int buscar_usuario(User_list* lista, char algo[], char otro[]);// Tengo que mirar como estan declaradas las cosas en el otro proyecto
void borrar_lista_de_usuarios(User_list* lista);
void initStack(Stack* stack);
int isStackEmpty(Stack* stack);
void pushRequest(Stack* stack, const char* sender, const char* receiver);
Friend_request* popRequest(Stack* stack);
void guardar_amigos(User_list* lista);
void imprimir_lista_amigos(User_data *usuario);
void valoracion(User_data* user, float nota_dada);
void enviarSolicitudAmistad(Stack* stack, char usuarioActual[], char usuarioDestino[]);


#endif //EDA2_USUARIO_H
