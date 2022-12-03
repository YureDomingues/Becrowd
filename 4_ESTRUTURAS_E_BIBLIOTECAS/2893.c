//Fibonac^{k}i - Accepted

#include <stdio.h>
#include <stdlib.h>

struct fila{
    int *vet;
    int somaK;
    int n_elem;
    int ini;
};

typedef struct fila Fila;

void imprimir_vetor(Fila *f, int k){
    //printf("inicio - fim: %d - %d\n",f->ini,(f->ini+f->n_elem-1)%k);
    for(int i =0; i<k; i++){
        printf("|%d|", f->vet[i]);
    }
}

Fila* criar_fila(int k){
    Fila *nova = (Fila*) malloc(sizeof(Fila));
    nova->n_elem = k;
    nova->ini = 0;
    nova->vet = (int*) malloc(sizeof(int)*k);

    nova->somaK = 0;

    for(int i=0; i<k; i++){
        nova->vet[i] = i%1000007;
        nova->somaK = (nova->somaK+i)%1000007;
    }

    return nova;    
}   

void fila_insere(Fila *f, int dado, int k){
    int fim;
    if(f->n_elem == k){
        printf("Capacidade da fila estourou.\n");
        exit(EXIT_FAILURE);
    }
    fim = (f->ini + f->n_elem) % k;
    f->vet[fim] = dado;
    f->n_elem++;
}

int fila_retira(Fila* f, int k){
    int x;
    if(f->n_elem == 0){
        printf("Fila vazia.\n");
        exit(EXIT_FAILURE);
    }
    
    x = f->vet[f->ini];
    f->ini = (f->ini+1)%k;
    f->n_elem--;
    return x;
}

void encontrar_resto_N(Fila *fib, int N, int k){
    //printf("somaK inicial: %d\n", fib->somaK);
    if(N<=k){
        printf("%d\n", (N-1)%1000007);
        return;
    }

    //imprimir_vetor(fib,k);

    for(int i = k-1; i<N-2; i++){
        int remov = fila_retira(fib, k);
        fila_insere(fib,fib->somaK,k);
        fib->somaK = (1000007+2*(fib->somaK)-remov)%1000007;
    }

    printf("%d\n", fib->somaK);

}

void fila_libera(Fila* f){
    free(f);
}

int main(void){

    int T;
    int k, N;
    
    scanf("%d", &T);

    for(int i=0; i<T; i++){
        Fila *fib = NULL;
        scanf("%d %d", &k, &N);
        fib = criar_fila(k);
        encontrar_resto_N(fib,N, k);
        fila_libera(fib);
    }

    return 0;
}
