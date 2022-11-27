//1110 - Jogando Cartas Fora - Accepted 

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

struct fila{
    int ini;
    int n_elem;
    int *vet;
};

typedef struct fila Fila;

Fila* fila_criar(int tam){
    Fila* f;
    f = (Fila*)malloc(sizeof(Fila));
    f->ini = 0;
    f->n_elem = 0;
    f->vet = (int*) malloc(sizeof(int)*tam);
    return f;
}

int fila_vazia(Fila* f){
    return (f->n_elem == 0);
}

void fila_inserir(Fila* f, int dado, int tam){
    
    if(f->n_elem == tam){
        printf("Capacidade de fila estourou\n");
        exit(EXIT_FAILURE);
    }

    int fim = (f->ini+f->n_elem)%tam;
    f->vet[fim] = dado;
    f->n_elem++;
}

int fila_retirar(Fila* f, int tam){

    if(fila_vazia(f)){
        printf("A fila está vazia.\n");
        exit(EXIT_FAILURE);
    }

    int dado = f->vet[f->ini];
    f->ini = (f->ini + 1)%tam;
    f->n_elem--;

    return dado;
}

void fila_libera(Fila* f){
    free(f);
}

void preencher_cartas(Fila *Cartas, int num_cartas){
    for(int i=1; i<=num_cartas; i++){
        fila_inserir(Cartas, i, num_cartas);
    }
}

void passa_pro_fim(Fila *Cartas, int num_cartas){
    fila_inserir(Cartas, fila_retirar(Cartas, num_cartas), num_cartas);
}

void jogar_fora(Fila *Cartas, int num_cartas){
    printf("Discarded cards:");
    while(Cartas->n_elem > 1){
        printf(" %d", fila_retirar(Cartas, num_cartas));
        passa_pro_fim(Cartas, num_cartas); 
        if(Cartas->n_elem > 1){
            printf(",");
        }
    }
    printf("\n");
}

int main(){
    int n_cartas;
    
    while(scanf("%d", &n_cartas)==1 && n_cartas !=0){
        Fila* C = fila_criar(n_cartas);
        preencher_cartas(C, n_cartas);
        jogar_fora(C, n_cartas);
        printf("Remaining card: %d", fila_retirar(C, n_cartas));
        printf("\n");
        fila_libera(C);
    }

    
    return 0;
}
