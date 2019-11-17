typedef struct NO* ArvAVL;
ArvAVL* criarArvore();
int inserirValor(ArvAVL *raiz, int valor);
void liberarArvore(ArvAVL *raiz);
int consultarValor(ArvAVL *raiz, int valor);
void imprimirArvore(ArvAVL *raiz);
