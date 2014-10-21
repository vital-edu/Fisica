#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100	
#define PONTOS 1000

void inserirParticulas(int *i, int *j, int *k);
void plotarMalha();

int unsigned malha[MAX+1][MAX+1];

int main(){
	int i = 0;
	int j;
	int k;

	srand( (unsigned)time(NULL) );
	malha[ MAX/2 ][ MAX/2 ] = '1';

	inserirParticulas(&i, &j,&k);
	plotarMalha();

	return 0;
}

void gerarValores(int *j, int *k){
	*j = rand()%MAX;
	*k = rand()%MAX;
}

void andar(int *i, int *j, int *k){
	int direcao = rand()%8;

	switch(direcao){
		case 0:
			if (*j != MAX){
				*j = *j + 1;
			}else{
				andar(i, j,k);
			}
			break;
		case 1:
			if (*j != 0){
				*j = *j - 1;
			}else{
				andar(i, j,k);
			}
			break;
		case 2:
			if (*k != MAX){
				*k = *k + 1;
			}else{
				andar(i, j,k);
			}
			break;
		case 3:
			if (*k != 0){
				*k = *k - 1;
			}else{
				andar(i, j,k);
			}
	}
}

void verificarVizinhos(int *i, int *j, int *k){
	if ((malha[*j][*k-1] == '1') ||	(malha[*j][*k+1] == '1') || (malha[*j+1][*k] == '1') || (malha[*j-1][*k] == '1')){
		malha[*j][*k] = '1';
	}else{
		andar(i, j,k);
		verificarVizinhos(i, j,k);
	}
}

void inserirParticulas(int *i, int *j, int *k){
	gerarValores(j,k);
	if(*i < PONTOS){
		if (malha[*j][*k] == '1'){
			inserirParticulas(i, j,k);
		}else{
			verificarVizinhos(i, j,k);
			*i = *i + 1;
			inserirParticulas(i, j,k);
		}
	}
}

void plotarMalha(){
	int j, k;
	FILE *arq;
	arq = fopen("saida.txt", "w+");


	for(j = 0; j < MAX; j++){
		for (k = 0; k < MAX; k++){
			if (malha[j][k] == '1'){
				fprintf(arq, "%d %d\n", j, k);
			}
		}
	}

	fclose(arq);
}
