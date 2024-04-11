#ifndef INCLUDE_CABECALHO
#define INCLUDE_CABECALHO

// Define o tamanho maximo do vetor heap.
#define MAX 5 

typedef struct paciente {
  char nome[50];
  int prioridade;
  // Vetor hora, minuto, segundo.
  int hora_chegada[3];
} Paciente;

typedef struct heap {
  int n_pacientes;
  Paciente heap[MAX];
} Heap;

Heap *criar();
void trocar(Heap *heap, int filho, int pai);
int compara_hora(Heap *heap, int i, int j);
void subir(Heap *heap, int filho);
void descer(Heap *heap, int pai);
void inserir(Heap *heap);
void remover(Heap *heap);
void imprimir(Heap *heap);
void imprimir_menu();

#endif