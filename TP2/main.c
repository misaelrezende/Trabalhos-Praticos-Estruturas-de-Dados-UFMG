#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* 			--> TO-DO <--
	*** Passar todas funcoes daqui para uma biblioteca (MinhaBiblioteca)
		Motivo: Organizacao de codigo
	*** Criar Makefile
 */

// preenche o vetor de acordo com a ordenacao escolhida
void gerarVetor(int *vetorEntrada, int tamanho, char *ordemVetor){
	char *Ale = {"Ale\0"}, *OrdC = {"OrdC\0"};
	int i;

	if(strcmp(Ale, ordemVetor) == 0){ // ordem aleatoria
		srand(time(NULL));
		for(i = 0; i < tamanho; i++)
			vetorEntrada[i] = rand();
	}else if(strcmp(OrdC, ordemVetor) == 0){ // ordem crescente
		for(i = 0; i < tamanho; i++)
			vetorEntrada[i] = i;
	}else{ // ordem decresente
		for(i = tamanho - 1; i >= 0; i--)
			vetorEntrada[i] = i;
	}
}

int main(int argc, char *argv[]){
  char QC[3] = {"QC\0"}, QM3[4] = {"QM3\0"}, QPE[4] = {"QPE\0"};
	char QI1[4] = {"QI1\0"}, QI5[4] = {"QI5\0"}, QI10[5] = {"QI10\0"};
	char entrada[5], ordemVetor[4];
	int tamanho;

	strcpy(entrada, argv[1]);
	strcpy(ordemVetor, argv[2]);
	tamanho = atoi(argv[3]);
	/* 			--> TO-DO <--
	 *** Falta tratar caso de entrada com PARAMETRO -p
	 *** Falta tratar caso de saida para arquivo
	 */
	int vetor[tamanho];
	
	gerarVetor(vetor, tamanho, ordemVetor);

	if(strcmp(entrada, QC) == 0){

	}else if(strcmp(entrada, QM3) == 0){

	}else if(strcmp(entrada, QPE) == 0){

	}else if(strcmp(entrada, QI1) == 0){

	}else if(strcmp(entrada, QI5) == 0){

	}else if(strcmp(entrada, QI10) == 0){

	}else{ // QNR

	}
  
	
  return 0;
}