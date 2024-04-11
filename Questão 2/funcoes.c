#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>

Heap *criar() {
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  heap->n_pacientes = 0;
  // Setando os valores de prioridade antes da 1a insercao.
  for (int i = 0; i < MAX; i++) {
    heap->heap[i].prioridade = -1;
  }
  return heap;
}

// Troca o pai com o filho no heap.
void trocar(Heap *heap, int filho, int pai) {
  Paciente auxiliar;
  auxiliar = heap->heap[filho];
  heap->heap[filho] = heap->heap[pai];
  heap->heap[pai] = auxiliar;
}

// Compara as horas de paciente i com paciente j no vetor, retorna 1 se i tiver
// menor hora.
int compara_hora(Heap *heap, int i, int j) {
  // Se a hora de chegada do i for menor que a do j retorna 1.
  if (heap->heap[i].hora_chegada[0] < heap->heap[j].hora_chegada[0]) {
    return 1;
    // Se a hora de chegada do i for igual a da do j.
  } else if (heap->heap[i].hora_chegada[0] == heap->heap[j].hora_chegada[0]) {
    // Se o minuto de chegada do i for menor que o do j, retorna 1.
    if (heap->heap[i].hora_chegada[1] < heap->heap[j].hora_chegada[1]) {
      return 1;
      // Se o minuto de chegada do i for igual ao do j.
    } else if (heap->heap[i].hora_chegada[1] == heap->heap[j].hora_chegada[1]) {
      // Se o segundo de chegada do i for menor que o do j, retorna 1.
      if (heap->heap[i].hora_chegada[2] < heap->heap[j].hora_chegada[2]) {
        return 1;
      }
    }
  }
  return 0;
}

// Algoritmo de subir no Heap.
void subir(Heap *heap, int filho) {
  int pai = (filho - 1) / 2;
  if (pai >= 0) {
    // Se a prioridade do filho for maior que a do pai, troca.
    if (heap->heap[filho].prioridade > heap->heap[pai].prioridade) {
      trocar(heap, filho, pai);
      subir(heap, pai);
    } else if (heap->heap[filho].prioridade == heap->heap[pai].prioridade) {
      // Se a prioridade do filho for igual a do pai, compara as horas.
      // Se o filho tem menor hora, ele sobe.
      int verificador = compara_hora(heap, filho, pai);
      if (verificador == 1) {
        trocar(heap, filho, pai);
        subir(heap, pai);
      }
    }
  }
}

// Algoritmo de descer no Heap.
void descer(Heap *heap, int pai) {
  int filho = 2 * pai + 1;
  if (filho < heap->n_pacientes) {
    if (filho < heap->n_pacientes - 1) {
      // Se a prioridade do filho da direita for maior que da esquerda,
      // incrementa.
      if (heap->heap[filho + 1].prioridade > heap->heap[filho].prioridade) {
        filho++;
      }
      if (heap->heap[pai].prioridade < heap->heap[filho].prioridade) {
        trocar(heap, pai, filho);
        descer(heap, filho);
      } else if (heap->heap[pai].prioridade == heap->heap[filho].prioridade) {
        // Se a prioridade do filho for igual a do pai, compara as horas.
        // Se o filho tem menor hora, o pai desce.
        int verificador = compara_hora(heap, filho, pai);
        if (verificador == 1) {
          trocar(heap, filho, pai);
          descer(heap, filho);
        }
      }
    }
  }
}

void inserir(Heap *heap) {
  if (heap->n_pacientes < MAX) {
    printf("Digite o nome do paciente:\n");
    scanf("%s", heap->heap[heap->n_pacientes].nome);
    printf("Digite a prioridade  "
           "|0:azul|1:verde|2:amarelo|3:laranja|4:vermelho|:\n");
    scanf("%d", &heap->heap[heap->n_pacientes].prioridade);
    printf("Digite a hora:\n");
    scanf("%d", &heap->heap[heap->n_pacientes].hora_chegada[0]);
    printf("Digite o minuto:\n");
    scanf("%d", &heap->heap[heap->n_pacientes].hora_chegada[1]);
    printf("Digite o segundo:\n");
    scanf("%d", &heap->heap[heap->n_pacientes].hora_chegada[2]);
    heap->n_pacientes++;
    subir(heap, heap->n_pacientes - 1);
  } else {
    printf("Lista cheia.\n");
  }
}

void remover(Heap *heap) {
  if (heap->n_pacientes != 0) {
    printf("Paciente removido: %s.\n.", heap->heap[0].nome);
    heap->heap[0] = heap->heap[heap->n_pacientes - 1];
    heap->n_pacientes--;
    descer(heap, 0);
  } else {
    printf("Lista vazia.\n");
  }
}

void imprimir(Heap *heap) {
  for (int i = 0; i < heap->n_pacientes; i++) {
    printf("[Nome:%s,\n", heap->heap[i].nome);
    printf("Prioridade:%d,\n", heap->heap[i].prioridade);
    printf("Hora:%d;Minuto:%d;Segundo:%d.]\n", heap->heap[i].hora_chegada[0],
           heap->heap[i].hora_chegada[1], heap->heap[i].hora_chegada[2]);
  }
}

void imprimir_menu() {
  printf("-------Opcoes-------\n");
  printf("1...Inserir paciente\n");
  printf("2...Remover paciente\n");
  printf("3.....Imprimir lista\n");
  printf("4...............Sair\n");
}