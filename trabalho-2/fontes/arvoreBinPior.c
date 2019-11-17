#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "arvoreBin.h"
#define REPEAT 1000.0

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* criarArvore(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));

    if(raiz != NULL){
        *raiz = NULL;
    }

    return raiz;
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

void liberarArvore(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }

    liberarNo(*raiz);
    free(raiz);
}

int inserirValor(ArvBin *raiz, int valor){
	if(raiz == NULL){
		return 0;
	}

	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	
	if(novo == NULL){
		return 0;
	}

	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;

	if(*raiz == NULL){
		*raiz = novo;
	}else{
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		
		while(atual != NULL){
			ant = atual;
			
			if(valor == atual->info){
				free(novo);
				return 0;			
			}
			
			if(valor > atual->info){
				atual = atual->dir;
			}else{
				atual = atual->esq;
			}
		}

		if(valor > ant->info){
			ant->dir = novo;
		}else{
			ant->esq = novo;
		}
	}
	
	return 1;
}

int consultarValor(ArvBin *raiz, int valor){
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

void imprimirArvore(ArvBin *raiz){
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
    ArvBin* raiz = criarArvore();

	srand(time(NULL)); 
	struct timeval a;
	struct timeval b;
	double t;
    int achou;
    int n, k, i;

 	for(n = 10000; n <= 100000; n += 10000){
        for(k = 0; k < n; k++){
            inserirValor(raiz, k);
        }

        t = 0;
 		for(i = 0; i < REPEAT; i++){
		 	gettimeofday(&b, NULL);

            achou = consultarValor(raiz, n*2);

		 	gettimeofday(&a, NULL);

			t = t + ((a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec));
	 	}

        liberarArvore(raiz);
        raiz = criarArvore();
		printf("%d %.6lf\n", n, t / REPEAT);
	}

    return 0;
}

