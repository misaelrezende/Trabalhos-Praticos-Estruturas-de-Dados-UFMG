#include "Bibliotecas/Quicksort.h"

/* 

	------///---- CODIGO CONTINUA RODANDO LISO MEU IRMAO!  ------///----

*/

int main(int argc, char *argv[]){
  char QC[3] = {"QC\0"}, QM3[4] = {"QM3\0"}, QPE[4] = {"QPE\0"};
	char QI1[4] = {"QI1\0"}, QI5[4] = {"QI5\0"}, QI10[5] = {"QI10\0"};
	char variacao[5], tipo[4];
	int i, j, tamanho;
	int qtdeComparacao = 0, qtdeMovimentacao = 0, parametroOpcional = 0;
	int mediaQtdeComparacao = 0, mediaqtdeMovimentacao = 0;

	strcpy(variacao, argv[1]);
	strcpy(tipo, argv[2]);
	tamanho = atoi(argv[3]);
	
	Item Itens[tamanho], **Auxiliar;
	
	if(argc == 5){ // ou seja, se incluiu o parametro p
		parametroOpcional = 1;
		Auxiliar = (Item**) malloc((tamanho*2)*sizeof(Item*));
		for(i = 0; i < (tamanho*2); i++)
			Auxiliar[i] = (Item*) malloc(tamanho*sizeof(Item));
	}

	/*								 			--> TO-DO <--
						 *** Falta tratar caso de saida para arquivo txt
	*/
	
	if(strcmp(variacao, QC) == 0){
		srand(time(NULL));
		for(i = 0; i < 20; i++){
			gerarVetor(Itens, tamanho, tipo, Auxiliar[i], parametroOpcional); // gera vetor novo a cada iteracao
			
			QuickSort(Itens, tamanho, &qtdeComparacao, &qtdeMovimentacao);
			mediaQtdeComparacao += (qtdeComparacao/20);
			mediaqtdeMovimentacao += (qtdeMovimentacao/20);
		}
		imprimeResultados(variacao, tipo, tamanho, mediaQtdeComparacao,
						mediaqtdeMovimentacao);
		if(parametroOpcional == 1){
			for(i = 0; i < (tamanho*2); i++){
				for(j = 0; j < tamanho; j++)
					printf("%d ", Auxiliar[i][j].Chave);
				printf("\n");
			}
		}
	}else if(strcmp(variacao, QM3) == 0){

	}else if(strcmp(variacao, QPE) == 0){

	}else if(strcmp(variacao, QI1) == 0){

	}else if(strcmp(variacao, QI5) == 0){

	}else if(strcmp(variacao, QI10) == 0){

	}else{ // QNR

	}
  
	/* LIBERAR Item Auxiliar da MEMORIA*/
	
  return 0;
}