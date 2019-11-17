typedef struct NO* ArvBin;
ArvBin* criarArvore();
int inserirValor(ArvBin *raiz, int valor);
void liberarArvore(ArvBin *raiz);
int consultarValor(ArvBin *raiz, int valor);
void imprimirArvore(ArvBin *raiz);
