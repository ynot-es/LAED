#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  Controle *controle;
  controle = cria_controle();

  char instrucao[] = {"hellothere.txt"}; // Modifique instrucao aqui(instrucao.txt ou hellothere.txt)
  ler(controle, instrucao);

  return 0;
}