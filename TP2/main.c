#include "Bibliotecas/Quicksort.h"
#include <time.h>

/* 			ÚLTIMAS MUDANÇAS:
	** Implementação do QuickSort Nao Recursivo
	** QuickSort funcionando corretamente
	** Tudo funcionando corretamente (ordenação, ale, OrdC, OrdD)!
	**

				PROBLEMA/DÚVIDAS: 
	** 

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
	}else{
		/* meio para contornar caso não fosse passado o parâmetro -p
		ou seja, será alocado uma matriz (20x1) para passar para a função gerarVetor
		mesmo que, nesse caso, o vetor não seja utilizado. Fiz isso pois senão teria
		que criar uma função igual a gerarVetor porém sem a passagem desse vetor como
		parametro. */
		Auxiliar = (Item**) malloc(20*sizeof(Item*));

		for(i = 0; i < 20; i++)
			Auxiliar[i] = (Item*) malloc(1*sizeof(Item));
	}

	srand(time(NULL));
	for(i = 0; i < 20; i++){
		// gera vetor novo a cada iteracao
		gerarVetor(Itens, tamanho, tipo, Auxiliar[i], parametroOpcional);

		// Pega o horário do sistema antes da execuçao do quicksort
		clock_gettime(CLOCK_REALTIME, &start);

		// se QuickSort Clássico ou se QuickSort c/ Mediana de 3
		if(strcmp(variacao, QC) == 0 || strcmp(variacao, QM3) == 0){
			QuickSort(Itens, tamanho, &qtdeComparacao, &qtdeMovimentacao, variacao); // executa a ordenação no vetor
		}else if(strcmp(variacao, QPE) == 0){ // se QuickSort Primeiro Elemento
			QuickSortPrimeiroElemento(Itens, 0, tamanho, &qtdeComparacao, &qtdeMovimentacao);
		}else if(strcmp(variacao, QI1) == 0){ // se QuickSort 1%

		}else if(strcmp(variacao, QI5) == 0){ // se QuickSort 5%

		}else if(strcmp(variacao, QI10) == 0){ // se QuickSort 10%

		}else{ // // se QuickSort Não Recursivo
			QuickSortNaoRec(Itens, tamanho, &qtdeComparacao, &qtdeMovimentacao);
		}

		// Pega o horário do sistema depois da execuçao do quicksort
		clock_gettime(CLOCK_REALTIME, &end);
		// Obtém a diferença entre o horário de fim e o de inı́cio
		elapsed_time = 1.e+6 * (double) (end.tv_sec - start.tv_sec)
		+ 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);

		valoresTempo[i] = elapsed_time; // guarda esse tempo no vetor

		// impressão dos elementos ordenados
		for(j = 0; j < tamanho; j++)
			printf("%d ", Itens[j].Chave);
		printf("--\n");

		// cálculo da media in-place, ou seja, não precisa salvar os valores de
		// cada iteração pois eu já estou dividindo cada iteração por 20
		mediaQtdeComparacao += (qtdeComparacao/20);
		mediaqtdeMovimentacao += (qtdeMovimentacao/20);

	}

	escolheMediana(valoresTempo, &medianaTempo);
	imprimeResultados(variacao, tipo, tamanho, mediaQtdeComparacao,
						mediaqtdeMovimentacao, medianaTempo);

	if(parametroOpcional == 1){
		for(i = 0; i < 20; i++){
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
	// liberar memória se foi nao inserido o parametro -p
	else{
		for(i = 0; i < 20; i++)
				free(Auxiliar[i]); // esta desalocando corretamente agora?
			free(Auxiliar); // acho que sim
	}

  return 0;
}
