#include "Bibliotecas/Quicksort.h"
#include <time.h>

/* 			ÚLTIMAS MUDANÇAS:
		** Ordenação do QC funcionando e imprimindo corretamente
		** Incluso o medidor de tempo no algoritmo
		** Impressao em arquivo funcionando

				PROBLEMA
		** Tive que criar uma funcao extra gerarVetorSem() 
			(caso não fosse inserido o parametro -p)

*/

int main(int argc, char *argv[]){
	struct timespec start, end;
	// Pega o horário do sistema antes da execuçao do código
	clock_gettime(CLOCK_REALTIME, &start);


  char QC[3] = {"QC\0"}, QM3[4] = {"QM3\0"}, QPE[4] = {"QPE\0"};
	char QI1[4] = {"QI1\0"}, QI5[4] = {"QI5\0"}, QI10[5] = {"QI10\0"};
	char variacao[5], tipo[4];
	int i, j, tamanho;
	int qtdeComparacao = 0, qtdeMovimentacao = 0, parametroOpcional = 0;
	int mediaQtdeComparacao = 0, mediaqtdeMovimentacao = 0;

	strcpy(variacao, argv[1]);
	strcpy(tipo, argv[2]);
	tamanho = atoi(argv[3]);
	
	// declaracao de Registro e Registro auxiliar (para impressao caso -p)
	Item Itens[tamanho], **Auxiliar;
	
	if(argc == 5){ // ou seja, se incluiu o parametro p
		parametroOpcional = 1;
		Auxiliar = (Item**) malloc(20*sizeof(Item*)); // troquei de (tamanho*2 sizeof) para (20*sizeof) 
		for(i = 0; i < 20; i++) // // troquei de (i de 0 a tamanho) para (i de 0 a 20)
			Auxiliar[i] = (Item*) malloc(tamanho*sizeof(Item));
	}
	
	if(strcmp(variacao, QC) == 0){
		srand(time(NULL));
		
		for(i = 0; i < 20; i++){
			if(parametroOpcional == 1)
				gerarVetor(Itens, tamanho, tipo, Auxiliar[i], parametroOpcional); // gera vetor novo a cada iteracao
			else
				gerarVetorSem(Itens, tamanho, tipo); // gera vetor novo a cada iteracao
			
			QuickSort(Itens, tamanho, &qtdeComparacao, &qtdeMovimentacao); // executa a ordenação no vetor

			// // teste de ordenacao
			// for(j = 0; j < tamanho; j++)
			// 	printf("%d ", Itens[j].Chave);
			// printf("--\n");

			mediaQtdeComparacao += (qtdeComparacao/20);
			mediaqtdeMovimentacao += (qtdeMovimentacao/20);
		}

		// Pega o horário do sistema depois da execuçao do código
		clock_gettime(CLOCK_REALTIME, &end);
		// Obtém a diferença entre o horário de fim e o de inı́cio
		long elapsed_time = 1.e+6 * (double) (end.tv_sec - start.tv_sec)
		+ 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);
	
		imprimeResultados(variacao, tipo, tamanho, mediaQtdeComparacao,
						mediaqtdeMovimentacao, elapsed_time);

		if(parametroOpcional == 1){
			for(i = 0; i < 20; i++){ // troquei de (tamanho*2) para (20) 
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
  
  // liberar memória se foi inserido o parametro -p
  if(parametroOpcional == 1){
		/* LIBERAR Item Auxiliar da MEMORIA*/
		for(i = 0; i < 20; i++)
				free(Auxiliar[i]);
			free(Auxiliar);
	}


  return 0;
}