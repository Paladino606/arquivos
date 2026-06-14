#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    FILE *f = fopen("cep_aleatorio.dat", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo cep_aleatorio.dat\n");
        return 1;
    }

    ArvoreB *a = ArvoreB_Abre("arvore_cep.dat");
    if (a == NULL) {
        printf("Erro ao abrir a Arvore B arvore_cep.dat\n");
        fclose(f);
        return 1;
    }

    FILE *saida = fopen("cep_intersecao.dat", "wb");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo cep_intersecao.dat\n");
        fclose(f);
        ArvoreB_Fecha(a);
        return 1;
    }

    Endereco e;
    long total_lidos = 0;
    long total_intersecao = 0;

    printf("Iniciando intersecao buscando registros na Arvore B...\n");

    while (fread(&e, sizeof(Endereco), 1, f)) {
        total_lidos++;
        
        long res = ArvoreB_Busca(a, e.cep);
        if (res != -1) {
            fwrite(&e, sizeof(Endereco), 1, saida);
            total_intersecao++;
        }

    }

    printf("Registros processados: %ld\n", total_lidos);
    printf("Registros em comum: %ld\n", total_intersecao);

    fclose(f);
    fclose(saida);
    ArvoreB_Fecha(a);

    return 0;
}
