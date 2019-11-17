#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#define REPEAT 1000000.0

typedef struct bloco{
      int valor;
      struct bloco *proximo;
}Bloco;

typedef struct table{
      unsigned int tam;
      unsigned int n;
      struct bloco **b;
}Table;

Bloco* novo(int c){
    Bloco* bloco;
    bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->valor = c;
    bloco->proximo = NULL;

    return bloco;
}

unsigned int hash(int valor, int tam){
	return (valor%tam);
}

void removerBloco(Bloco* bloco){
	Bloco *auxiliar;

	while (bloco != NULL){
		auxiliar = bloco->proximo;
		free(bloco);
		bloco = auxiliar;
	}	
}

void removerTabela(Table* table){
	int i;

	for(i = 0; i< table->tam; i++){
		removerBloco(table->b[i]);
		table->b[i] = NULL;
	}

	table->n = 0;
}

void atualizar(Table *table){
	int i, tam = table->tam;

	Table new;
	new.tam = (tam*2);
	new.b = malloc(sizeof(Bloco *) * new.tam);

	for (i = 0; i < new.tam; i++){
        new.b[i] = NULL;
    }

	for (i = 0; i < tam; i++){
    	Bloco *vOrg;
	    vOrg = table->b[i];
	    while (vOrg != NULL){
	        unsigned int posicao = hash(vOrg->valor, new.tam);

	        Bloco *b = novo(vOrg->valor);

	        if(new.b[posicao] == NULL){
		        new.b[posicao] = b;
	        }else{
				b->proximo = new.b[posicao];
				new.b[posicao] = b;
		   }
			vOrg = vOrg->proximo;
			new.n++;
	    }
    }

    removerTabela(table);

    table->b = new.b;
    table->tam = new.tam;
	table->n = new.n;
}

void adicionar(Table *table, Bloco *bloco){
	if(table->n >= table->tam){
		printf("\n>> Dobrando tamanho <<\n");
		atualizar(table);
	}

	unsigned int posicao = hash(bloco->valor, table->tam);

	if(table->b[posicao] == NULL){
		table->b[posicao] = bloco;
	}else{
		bloco->proximo = table->b[posicao];
		table->b[posicao] = bloco;
	}
	table->n++;
}

void exibirLista(Bloco *x){
    while (x != NULL){
        printf("%d", x->valor);
        printf(" ");
        x = x->proximo;
    }
}

void exibirTabela(Table *t){
    int i;

    for (i = 0; i < t->tam; i++){
        printf("Chave tabela: %d", i);
        printf(" --> ");
        exibirLista(t->b[i]);
        printf("\n");
    }
}

int buscar(Table *table, int valor){
    int posicao;
    Bloco *bloco;
    posicao = hash(valor, table->tam);

    for (bloco = table->b[posicao]; bloco != NULL; bloco = bloco->proximo){    	
        if(bloco->valor == valor){
            return 1;
        }
    }

    return 0;
}

int main(void){
	srand(time(NULL));
	Table table;
    int valor,i,n,k,w,achou, aleatorio;
    struct timeval a, b;
	double t;

    table.b = malloc(sizeof(Bloco*)*(100000));
	table.n = 0;
	table.tam = 100000;

	for(n = 10000; n <= 100000; n+= 1000){
		for(w = 0; w < n; w++){
			table.b[w] = NULL;
		}

		for(k = 0; k < n; k++){
			aleatorio = rand() % (n+1);
			adicionar(&table, novo(aleatorio));
		}

		t = 0;
		for(i = 0; i < REPEAT; i++){
			gettimeofday(&b, NULL);

            achou = buscar(&table, rand() % (n+1));
		 	
            gettimeofday(&a, NULL);

			t = t + ((a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec));
		}

        removerTabela(&table);
		printf("%d %.6lf\n", n, t / REPEAT);
	}
}

