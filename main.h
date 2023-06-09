#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H
#include "usuario.h"
#include "publicacion.h"

User_data* encontrar_usuario(char username[], User_list *lista);

timeline* leer_posts();

void cargar_solicitudes_amistad(User_list* lista);
void init_amigos(User_list *lista);
void cargar_amigos(User_list *lista);
void initQueue(Queue* queue);


#include "menu.h"
int main();


#endif //EDA2_MAIN_H