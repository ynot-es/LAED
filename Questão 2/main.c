#include "cabecalho.h"
#include <stdio.h>

int main() {
  Heap *heap = criar();
  int opcao;

  do {
    imprimir_menu();
    printf("Digite a opcao desejada:\n");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      inserir(heap);
      break;
    case 2:
      remover(heap);
      break;
    case 3:
      imprimir(heap);
      break;
    case 4:
      printf("Fechando programa...\n");
      break;
    default:
      printf("Opcao invalida.\n");
      break;
    }
  } while (opcao != 4);
  return 0;
}