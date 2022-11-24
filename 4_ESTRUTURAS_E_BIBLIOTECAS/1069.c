//1069 - Diamantes e Areia - Accepted

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 1001

struct objeto{
    char c;
    struct objeto* ant;
    struct objeto* prox;
};

typedef struct objeto Mina;

Mina* inserir(Mina* m, char fig){
    
    if(fig == '.') return m;

    Mina* novo;

    novo = (Mina*) malloc(sizeof(Mina));
    novo->c = fig;
    novo->prox = m;
    novo->ant = NULL;

    if(m!=NULL) m->ant = novo;

    return novo;
}

//Apenas para visualizar como está a lista

void preOrdem(Mina *m){
    if(m==NULL) return;
    printf("%c", m->c);
    preOrdem(m->prox);
}

Mina* removerDima(Mina *m, int *cont, int *modif){

    Mina *p = m;

    while(p != NULL){
        if((p->prox)!=NULL && p->c == '<' && (p->prox)->c == '>') break;
        p = p->prox;
    }
    if(p==NULL){
        *modif = 0;
        return m;
    } 
    //retira um diamante
    *modif = 1;
    (*cont)++;

    if(p == m){
       m = (p->prox)->prox; //Se o o diamente estiver nas primeiras posições
    }else{
        p->ant->prox = p->prox->prox; //Se o diamante estiver no meio da lista
    }

    if((p->prox)->prox != NULL){
       ((p->prox)->prox)->ant = p->ant;
    }

    return m;
}

int main(){
    int linhas;
    char str[TAM];

    scanf("%d", &linhas);

    for(int i = 0; i<linhas; i++){
        Mina *M = NULL;
        scanf("%s", str);

        for(int j=strlen(str)-1; j>=0; j--){
            M = inserir(M, str[j]);
        }

        int cont = 0;
        int mod;
        
        do{
            mod = 0;
            M = removerDima(M, &cont, &mod);
        }while(mod == 1);
        printf("%d\n", cont);
    }
    return 0;
}
