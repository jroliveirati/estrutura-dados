#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "arvoreAVL.h"
#define REPEAT 1000000.0

struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* criarArvore(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));

    if(raiz != NULL){
        *raiz = NULL;
    }

    return raiz;
}

int alturaNO(struct NO* no){
    if(no == NULL){
        return -1;
    }

    return no->altura;
}

//função que retorna o fator de balanceamento
int fbNO(struct NO* no){
    return labs(alturaNO(no->esq) - alturaNO(no->dir));
}

int maior(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

void rotacaoLL(ArvAVL *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->altura = maior(alturaNO((*raiz)->esq),alturaNO((*raiz)->dir)) + 1;
    
    no->altura = maior(alturaNO(no->esq),(*raiz)->altura) + 1;
    *raiz = no;
}

void rotacaoRR(ArvAVL *raiz){
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->altura = maior(alturaNO((*raiz)->esq),alturaNO((*raiz)->dir)) + 1;
    
    no->altura = maior(alturaNO(no->dir),(*raiz)->altura) + 1;
    (*raiz) = no;
}

void rotacaoLR(ArvAVL *raiz){
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(ArvAVL *raiz){
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

void liberarNo(struct NO* no){
    if(no == NULL){
        return;
    }

    liberarNo(no->esq);
    liberarNo(no->dir);
    free(no);
    no = NULL;
}

void liberarArvore(ArvAVL *raiz){
    if(raiz == NULL){
        return;
    }

    liberarNo(*raiz);
    free(raiz);
}

int inserirValor(ArvAVL *raiz, int valor){
    int res;
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
 
        if(novo == NULL){
            return 0;
        }

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    
    if(valor < atual->info){
        if((res = inserirValor(&(atual->esq), valor)) == 1){
            if(fbNO(atual) >= 2){
                if(valor < (*raiz)->esq->info){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){
            if((res = inserirValor(&(atual->dir),valor)) == 1){
                if(fbNO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        rotacaoRR(raiz);
                    }else{
                        rotacaoRL(raiz);
                    } 
                }
            }
        }else{
            return 0;
        }
    }

    atual->altura = maior(alturaNO(atual->esq), alturaNO(atual->dir)) + 1;

    return res;
}   

int consultarValor(ArvAVL *raiz, int valor){
	if(raiz == NULL){
		return 0;
	}

	struct NO* atual = *raiz;

	while(atual != NULL){
		if(valor == atual->info){
			return 1;
		}

		if(valor > atual->info){
			atual = atual->dir;
		}else{
			atual = atual->esq;
		}
	}

	return 0;
}

void imprimirArvore(ArvAVL *raiz){
    if(raiz == NULL){
        return;
    }

    if(*raiz != NULL){
        imprimirArvore(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        imprimirArvore(&((*raiz)->dir));
    }
}

int main (void){
    ArvAVL* raiz = criarArvore();

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double t;
    int achou;
    int n, k, i,aleatorio;

 	for(n = 10000; n <= 100000; n += 10000){
        for(k = 0; k < n; k++){
            aleatorio = rand() % (n+1);

            while(consultarValor(raiz, aleatorio) == 1){
                aleatorio = rand() % (n+1);
            }

            inserirValor(raiz, aleatorio);
        }

        t = 0;
 		for(i = 0; i < REPEAT; i++){
		 	gettimeofday(&b, NULL);

            achou = consultarValor(raiz, rand() % (n+1));

		 	gettimeofday(&a, NULL);

			t = t + ((a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec));
	 	}

        liberarArvore(raiz);
        raiz = criarArvore();
		printf("%d %.6lf\n", n, t / REPEAT);
	}

    return 0;
}

