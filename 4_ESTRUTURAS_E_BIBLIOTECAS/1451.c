//1452 - Teclado Quebrado - Accepted

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MOD -1
#define INI 0
#define FIM 1

struct lista{
    char c;
    struct lista* prox;
    struct lista* ultima_pos;
};

typedef struct lista Lista;

int lista_vazia(Lista *l){
    return (l == NULL);
}

void preOrdem(Lista *l){
    if(lista_vazia(l)){
        printf("\n");
        return;
    } 
    printf("%c", l->c);
    preOrdem(l->prox);
}

Lista* inserir(Lista *l, char c){
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->c = c;
    
    if(lista_vazia(l)){
        l = novo;
        l->ultima_pos = l;
    }else{  
        l->ultima_pos->prox = novo;
        l->ultima_pos = novo;
    }

    return l;
}

Lista* organizar(Lista **orig, Lista *dest, int pos){

    if(lista_vazia(*orig)) return dest;

    Lista *lista_org = NULL;

    if(pos == N_MOD){
        lista_org = *orig;
        *orig = NULL;
        return lista_org;
    }

    
    if(pos == INI){
        (*orig)->ultima_pos->prox = dest;
        if(!lista_vazia(dest)){
            (*orig)->ultima_pos = dest->ultima_pos;
        }
        lista_org = *orig;
        
    }else{
        if(lista_vazia(dest)){
            lista_org = *orig;
        }else{
            dest->ultima_pos->prox = *orig;
            dest->ultima_pos = (*orig)->ultima_pos;
            lista_org = dest;
        }  
    }

    *orig = NULL;
    return lista_org;
}



void liberar_lista(Lista *l){
    if(!lista_vazia(l)){
        liberar_lista(l->prox);
        free(l);
    }
}

int main(){

    Lista *buffer = NULL, *l = NULL;
    
    char c;
    int pos = FIM;

    while(scanf("%c", &c)!=EOF){
        
        if(c == '[' || c == ']' || c == '\n'){
            
            //preOrdem(buffer);
            l = organizar(&buffer, l, pos);

            if(c == '['){
                pos = INI;
            }
                
            else if(c == ']'){
                pos = FIM;
            }
            else{
                preOrdem(l);
                l = NULL;
                buffer = NULL;
            }
            
        }else{
            buffer = inserir(buffer, c);
        }
    }

    
    liberar_lista(l);
    liberar_lista(buffer);
    
    return 0;
}