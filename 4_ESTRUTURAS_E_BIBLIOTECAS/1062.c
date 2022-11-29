// 1062 - Trilhos - Accepted

#include <stdio.h>
#include <stdlib.h>

#define N 1000

struct pilha{
    int n;
    int vet[N];
};

typedef struct pilha Pilha;

Pilha* p_cria(void){
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->n = 0; 
    return p;
}

void imprimir_pilha(Pilha *p, char s[]){
    printf("Pilha %s - %d: ", s, p->n);
    for(int i = p->n-1; i>=0; i--){
        printf("|%d|", p->vet[i]);
    }
    printf("\n");
}

int p_vazia(Pilha *p){
    return (p->n == 0);
}

int p_cheia(Pilha *p, int tamanho){
    return (p->n == tamanho);
}

void p_push(Pilha *p, int dado, int tamanho){

    if(p_cheia(p, tamanho)){
        printf("A fila está cheia");
        exit(EXIT_FAILURE);
    }

    p->n++;
    p->vet[p->n-1] = dado;
}

int p_pop(Pilha *p){

    if(p_vazia(p)){
        printf("Não há elementos na pilha\n");
        exit(EXIT_FAILURE);
    }
    p->n--;
    return p->vet[p->n];
}

void p_libera(Pilha *p){
    free(p);
}

Pilha* cria_vagoes(int n){
    Pilha *p = p_cria();

    for(int i=n; i>0; i--){
        p_push(p, i, n);
    }
    
    return p;
}

void imprimir_saida(int s[], int pos, int tam){
    printf("Saida - (%d): ", pos);
    for(int i=pos; i<tam; i++){
        printf("|%d|", s[i]);
    }
    printf("\n");
}


int verifica_organizacao(Pilha *vagoes, int tamanho, int saida[]){
    int organiza = 1;

    Pilha *estacao = p_cria();

    int pos = 0;

    while(!p_vazia(vagoes) || !p_vazia(estacao)){
        /*Teste
        imprimir_pilha(vagoes, "vagoes");
        imprimir_pilha(estacao, "estacao");
        imprimir_saida(saida, pos, tamanho);
        printf("\n");
        */
        int rmV;
        int rmE;

        

        if(!p_vazia(vagoes) && p_vazia(estacao)){
            rmV = p_pop(vagoes);

            if(rmV == saida[pos]){
                pos++;
            }else{
                p_push(estacao, rmV, tamanho);
            }

            continue;
        }

        if(!p_vazia(vagoes) && !p_vazia(estacao)){
            rmV = p_pop(vagoes);
            rmE = p_pop(estacao);

            if(rmV == saida[pos]){
                pos++;
                p_push(estacao, rmE, tamanho);
            }else if(rmE == saida[pos]){
                pos++;
                p_push(vagoes, rmV, tamanho);
            }else{
                p_push(estacao, rmE, tamanho);
                p_push(estacao, rmV, tamanho);
            }

            continue;
        }

        if(p_vazia(vagoes) && !p_vazia(estacao)){
            rmE = p_pop(estacao);

            if(rmE == saida[pos]){
                pos++;
            }else{
                organiza = 0;
                break;
            }
            
            continue;
        }

    }

    p_libera(estacao);

    return organiza;
}

int main(void){
    int num;
    

    while(scanf("%d", &num) && num != 0){
        Pilha *vagoes = p_cria();
        int nSairLoop = 1;

        while(nSairLoop){
            vagoes = cria_vagoes(num);

            int saida[N];

            for(int i=0; i<num; i++){
                scanf("%d", &saida[i]);

                if(saida[0] == 0){
                    nSairLoop = 0;
                    break;
                }
            }

            if(!nSairLoop){
                printf("\n");
                break;
            }

            int org = verifica_organizacao(vagoes, num, saida);

            if(org){
                printf("Yes\n");
            }else{
                printf("No\n");
            }

        }

        
    p_libera(vagoes);
        
    }
    
    return 0;
}