//1242 - Ácido Ribonucleico Alienígena  - Accepted

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 301

struct cadeia{
    char c;
    struct cadeia* ant;
    struct cadeia* prox;
};

typedef struct cadeia RNAA;

void preOrdem(RNAA *r){
    if(r==NULL) return;
    printf("%c", r->c);
    preOrdem(r->prox);
}

RNAA* inserir(RNAA* r, char fig){
    RNAA* novo;

    novo = (RNAA*) malloc(sizeof(RNAA));
    novo->c = fig;
    novo->prox = r;
    novo->ant = NULL;

    if(r!=NULL) r->ant = novo;

    return novo;
}

int dobra_cadeia(RNAA *cad){
    int dobrou = 0;

    if(cad == NULL || cad->prox == NULL) return dobrou;

    RNAA *p = cad;

    while(p!=NULL && p->prox !=NULL){
        if(p->c =='C' && p->prox->c == 'F' ||
           p->c == 'F' && p->prox->c == 'C'||
           p->c =='S' && p->prox->c == 'B'||
           p->c =='B' && p->prox->c == 'S')
           {
                if(p == cad){
                    cad = (p->prox)->prox; 
                }else{
                    p->ant->prox = p->prox->prox; 
                }

                if((p->prox)->prox != NULL){
                    ((p->prox)->prox)->ant = p->ant;
                }
                p = cad;
                dobrou += 1; 
           }else{
                p = p->prox;
           }     
    }

    return dobrou;
}

int main(void){
    char str[TAM];

    while (scanf("%s", str) != EOF){
        RNAA *cadeia = NULL;

        for(int j=strlen(str)-1; j>=0; j--){
            cadeia = inserir(cadeia, str[j]);
        }

        int num = dobra_cadeia(cadeia);
        printf("%d\n", num);
    }

    return 0;
}
