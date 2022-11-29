//Estacionamento Linear - Accepted

#include <stdio.h>
#include <stdlib.h>

#define MAX_EST 1000

#define chegouDepoisSaida  (hCheg >= p->saida[p->qtd_carros-1]) 
//Ci chegou depois (ou no msm horario) da saida de Ci-1
#define saiDepoisSaida  (hSaida > p->saida[p->qtd_carros-1]) 
//Ci vai sair depois da saida de Ci-1

struct pilha_carros{
    int qtd_carros;
    int saida[MAX_EST];
};

typedef struct pilha_carros ESTC;

ESTC* estc_criar(void){
    ESTC *p = (ESTC*) malloc(sizeof(ESTC));
    p->qtd_carros = 0; 
    return p;
}

int estc_vazio(ESTC *p){
    return (p->qtd_carros == 0);
}

int estc_cheio(ESTC *p, int max_est){
    return (p->qtd_carros == max_est);
}

int retira_carro(ESTC *p){
    p->qtd_carros--;
    return p->saida[p->qtd_carros];
}

int coloca_carro(ESTC *p,int hCheg ,int hSaida, int max_est){
    int colocou = 1;

    while(!estc_vazio(p) && chegouDepoisSaida){
        retira_carro(p);
    }

    if(!estc_cheio(p, max_est)){
        if(!estc_vazio(p)){
            if(chegouDepoisSaida){
                p->saida[p->qtd_carros-1] = hSaida;
            }else if(saiDepoisSaida){
                colocou = 0;
             }else{
                p->qtd_carros++;
                p->saida[p->qtd_carros-1] = hSaida;
            }
        }else{
            p->qtd_carros++;
            p->saida[p->qtd_carros-1] = hSaida;
        }

    }else{
        if(chegouDepoisSaida){
            retira_carro(p);
            if(saiDepoisSaida){
                colocou = 0;
            }else{
                p->qtd_carros++;
                p->saida[p->qtd_carros-1] = hSaida; 
            }
        }else if(saiDepoisSaida){
            colocou = 0;
        }else{
            colocou = 0;
        }
    }

    return colocou;
}

void p_libera(ESTC *p){
    free(p);
}

int main(void){
    int n, k;

    while(scanf("%d %d", &n, &k) &&  n!=0 && k!=0){
        ESTC* est = estc_criar();
        int c, s;
        int deu = 1;
        for(int i=0; i<n; i++){
            scanf("%d %d", &c, &s);

            if(deu){
                deu = coloca_carro(est,c,s, k);
            }else{
                coloca_carro(est, c, s, k);
            }
            
        }
        if(deu) printf("Sim\n");
        else printf("Nao\n");
        p_libera(est);
    }   

    return 0;
}