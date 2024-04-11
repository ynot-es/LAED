#include "cabecalho.h" //inclui os Prototipos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArvAVL *cria_ArvAVL() {
  ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
  if (raiz != NULL)
    *raiz = NULL;
  return raiz;
}

void libera_NO(struct NO *no) {
  if (no == NULL)
    return;
  libera_NO(no->esq);
  libera_NO(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  libera_NO(*raiz); // libera cada no
  free(raiz);       // libera a raiz
}

int altura_NO(struct NO *no) {
  if (no == NULL)
    return -1;
  else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO *no) {
  return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y) {
  if (x > y)
    return x;
  else
    return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return 1;
  if (*raiz == NULL)
    return 1;
  return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
  int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
  return (alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = altura_ArvAVL(&((*raiz)->esq));
  int alt_dir = altura_ArvAVL(&((*raiz)->dir));
  if (alt_esq > alt_dir)
    return (alt_esq + 1);
  else
    return (alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    printf("%c", (*raiz)->letra);
    preOrdem_ArvAVL(&((*raiz)->esq));
    preOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void emOrdem_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    emOrdem_ArvAVL(&((*raiz)->esq));
    printf("%c", (*raiz)->letra);
    emOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void posOrdem_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    posOrdem_ArvAVL(&((*raiz)->esq));
    posOrdem_ArvAVL(&((*raiz)->dir));
    printf("%c", (*raiz)->letra);
  }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor) {
  if (raiz == NULL)
    return 0;
  struct NO *atual = *raiz;
  while (atual != NULL) {
    if (valor == atual->info) {
      return 1;
    }
    if (valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return 0;
}

//=================================
void RotacaoLL(ArvAVL *A) { // LL
  struct NO *B;
  B = (*A)->esq;
  (*A)->esq = B->dir;
  B->dir = *A;
  (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
  B->altura = maior(altura_NO(B->esq), (*A)->altura) + 1;
  *A = B;
}

void RotacaoRR(ArvAVL *A) { // RR
  struct NO *B;
  B = (*A)->dir;
  (*A)->dir = B->esq;
  B->esq = (*A);
  (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
  B->altura = maior(altura_NO(B->dir), (*A)->altura) + 1;
  (*A) = B;
}

void RotacaoLR(ArvAVL *A) { // LR
  RotacaoRR(&(*A)->esq);
  RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A) { // RL
  RotacaoLL(&(*A)->dir);
  RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int valor, char letra) {
  int res;
  if (*raiz == NULL) { //arvore vazia ou no folha
    struct NO *novo;
    novo = (struct NO *)malloc(sizeof(struct NO));
    if (novo == NULL)
      return 0;

    novo->info = valor;
    novo->altura = 0;
    novo->letra = letra;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  struct NO *atual = *raiz;
  if (valor < atual->info) {
    if ((res = insere_ArvAVL(&(atual->esq), valor, letra)) == 1) {
      if (fatorBalanceamento_NO(atual) >= 2) {
        if (valor < (*raiz)->esq->info) {
          RotacaoLL(raiz);
        } else {
          RotacaoLR(raiz);
        }
      }
    }
  } else {
    if (valor > atual->info) {
      if ((res = insere_ArvAVL(&(atual->dir), valor, letra)) == 1) {
        if (fatorBalanceamento_NO(atual) >= 2) {
          if ((*raiz)->dir->info < valor) {
            RotacaoRR(raiz);
          } else {
            RotacaoRL(raiz);
          }
        }
      }
    } else {
      printf("Valor duplicado!\n");
      return 0;
    }
  }

  atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;

  return res;
}

int conta_virgula(char instrucao[]) {
  int contador = 0;
  for (int i = 0; instrucao[i] != '\0'; i++) {
    if (instrucao[i] == ',') {
      contador++;
    }
  }
  return contador;
}

Controle *cria_controle() {
  Controle *controle = (Controle *)malloc(sizeof(Controle));
  for (int i = 0; i < 10; i++) {
    controle->vetor[i] = cria_ArvAVL();
  }
  return controle;
}

void ler(Controle *controle, char nome[]) {
  FILE *file = fopen(nome, "r");
  char instrucao[100];

  int id;
  int verificador;
  char letra;
  int chave;
  int ordem;

  if (file) {
    // Texto lido do arquivo.
    while (!feof(file)) {

      if (fgets(instrucao, 99, file)) {
        // Tudo o que vai acontecer estara aqui.
        verificador = conta_virgula(instrucao);
        id = atoi(&instrucao[0]);

        if (verificador == 1) {
          // Ordem de Percurso.
          ordem = atoi(&instrucao[2]);
          // Percurso.
          switch (ordem) {
          case 1:
            preOrdem_ArvAVL(controle->vetor[id]);
            printf(" ");
            break;
          case 2:
            emOrdem_ArvAVL(controle->vetor[id]);
            printf(" ");
            break;
          case 3:
            posOrdem_ArvAVL(controle->vetor[id]);
            printf(" ");
            break;
          }

        } else {
          letra = instrucao[2];
          // Calculando chave
          char *auxiliar;
          auxiliar = strtok(instrucao, ",");
          for (int i = 0; i < 2; i++) {
            auxiliar = strtok(NULL, ",");
          }

          chave = atoi(auxiliar);
          insere_ArvAVL(controle->vetor[id], chave, letra);
        }
      }
    }
    fclose(file);
  } else {
    printf("\nErro ao abrir arquivo!\n");
  }
}
