#ifndef INCLUDE_CABECALHO
#define INCLUDE_CABECALHO

struct NO {
  int info;
  char letra;
  int altura;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO *ArvAVL;

typedef struct controle {
  ArvAVL *vetor[10];
} Controle;

ArvAVL *cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int data, char letra);
int remove_ArvAVL(ArvAVL *raiz, int valor);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);
int conta_virgula(char *instrucao);
Controle *cria_controle();
void ler(Controle *controle, char *instrucao);

#endif