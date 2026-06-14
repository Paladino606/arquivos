#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; 
};

typedef struct _Endereco Endereco;

int main() {
    FILE *f = fopen("cep_aleatorioArvore.dat", "rb");
    if(f == NULL) {
        printf("Erro ao abrir o arquivo cep_aleatorioArvore.dat\n");
        return 1;
    }

    ArvoreB *a = ArvoreB_Abre("arvore_cep.dat");
    if (a == NULL) {
        printf("Erro ao criar a Árvore B.\n");
        fclose(f);
        return 1;
    }

    Endereco e;
    long posicao = 0;
    
    printf("Indexando cep_aleatorioArvore.dat...\n");

    while(fread(&e, sizeof(Endereco), 1, f)) {
        ArvoreB_Insere(a, e.cep, posicao);
        posicao++;
    }

    printf("Registros indexados: %ld\n", posicao);

    fclose(f);
    ArvoreB_Fecha(a);

    return 0;
}
