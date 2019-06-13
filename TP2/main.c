#include "Bibliotecas/Quicksort.h"
#include <time.h>

/* 			ÚLTIMAS MUDANÇAS:
		** Adicionei p/ pegar a mediana do tempo porem nao tenho certeza se está
		** corretamente implementado
		**

				PROBLEMA/DÚVIDAS
		** Tive que criar uma funcao extra gerarVetorSem()
			(caso não fosse inserido o parametro -p) -- como resolver?
		** como realizar a medição de tempo corretamente?

*/

int main(int argc, char *argv[]){
	struct timespec start, end;
	long int elapsed_time, valoresTempo[20], medianaTempo;

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
	Item Itens[tamanho], **Auxiliar = NULL;

	if(argc == 5){ // ou seja, se incluiu o parametro p
		parametroOpcional = 1;

		Auxiliar = (Item**) malloc(20*sizeof(Item*));
		for(i = 0; i < 20; i++)
			Auxiliar[i] = (Item*) malloc(tamanho*sizeof(Item));
	}

	srand(time(NULL));
	for(i = 0; i < 20; i++){

		// Pega o horário do sistema antes da execuçao do código
		clock_gettime(CLOCK_REALTIME, &start);

		if(parametroOpcional == 1)
			gerarVetor(Itens, tamanho, tipo, Auxiliar[i], parametroOpcional); // gera vetor novo a cada iteracao
		else
			gerarVetorSem(Itens, tamanho, tipo); // gera vetor novo a cada iteracao

		// se QuickSort Clássico
		if(strcmp(variacao, QC) == 0){
			QuickSort(Itens, tamanho, &qtdeComparacao, &qtdeMovimentacao); // executa a ordenação no vetor
		}else if(strcmp(variacao, QM3) == 0){ // se QuickSort c/ Mediana de 3

		}else if(strcmp(variacao, QPE) == 0){ // se QuickSort Primeiro Elemento

		}else if(strcmp(variacao, QI1) == 0){ // se QuickSort 1%

		}else if(strcmp(variacao, QI5) == 0){ // se QuickSort 5%

		}else if(strcmp(variacao, QI10) == 0){ // se QuickSort 10%

		}else{ // // se QuickSort Não Recursivo

		}

		// // impressão dos elementos ordenados
		// for(j = 0; j < tamanho; j++)
		// 	printf("%d ", Itens[j].Chave);
		// printf("--\n");

		mediaQtdeComparacao += (qtdeComparacao/20);
		mediaqtdeMovimentacao += (qtdeMovimentacao/20);

		// Pega o horário do sistema depois da execuçao do código
		clock_gettime(CLOCK_REALTIME, &end);
		// Obtém a diferença entre o horário de fim e o de inı́cio
		elapsed_time = 1.e+6 * (double) (end.tv_sec - start.tv_sec)
		+ 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);

		valoresTempo[i] = elapsed_time;

	}

	escolheMediana(valoresTempo, &medianaTempo);
	imprimeResultados(variacao, tipo, tamanho, mediaQtdeComparacao,
						mediaqtdeMovimentacao, medianaTempo);

	if(parametroOpcional == 1){
		for(i = 0; i < 20; i++){ // troquei de (tamanho*2) para (20)
			for(j = 0; j < tamanho; j++)
				printf("%d ", Auxiliar[i][j].Chave);
			printf("\n");
		}
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
