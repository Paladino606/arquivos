#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

typedef struct _Endereco Endereco;

int main() {
    
    FILE *arquivo = fopen("cep.dat", "rb");
    FILE *arquivoSaida = fopen("cep_aleatorioArvore.dat", "wb");
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    Endereco e;
    srand(time(NULL));
    while(fread(&e, sizeof(Endereco), 1, arquivo)) {
        float random_num = 1.0*rand()/RAND_MAX;
        if(random_num < 0.8) {
            fwrite(&e, sizeof(Endereco), 1, arquivoSaida);
        }
    }
    fclose(arquivo);
    fclose(arquivoSaida);
    return 0;
}
