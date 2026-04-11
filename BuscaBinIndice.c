#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; 
};

typedef struct _indiceEndereco indiceEndereco;
struct _indiceEndereco
{
    char cep[8];
    unsigned int posicao;
};

int main(int argc, char const *argv[])
{
    
    FILE *cep, *ind;
	Endereco e;
	indiceEndereco *ie;
	int qt;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	cep = fopen("cep.dat","rb");
	ind = fopen("indice.dat", "rb");
  if(cep == NULL || ind == NULL) {
    perror("Erro ao abrir arquivo cep.dat ou indice.dat");
    fclose(cep);
    fclose(ind);
    return 1;
  }
    int ini = 0;
    fseek(ind, 0, SEEK_END);
    int final = (ftell(ind) / sizeof(indiceEndereco)) ;
    ie = (indiceEndereco*) malloc((final)*sizeof(indiceEndereco)); 
    rewind(cep);
    qt = fread(&e,sizeof(Endereco),1,cep);
    while (ini <  final)
    {
        int meio = (ini + final) / 2;
        fseek(ind, meio * sizeof(indiceEndereco), SEEK_SET);
        if (fread(&ie[meio], sizeof(indiceEndereco), 1, ind) != 1) break;
        if(strncmp(argv[1], ie[meio].cep, 8) == 0) {

      fseek(cep, ie[meio].posicao, SEEK_SET);

      if (fread(&e, sizeof(Endereco), 1, cep) != 1) {
        fprintf(stderr, "Erro ao ler o registro do arquivo cep.dat\n");
        fclose(cep);
        fclose(ind);
        free(ie);
        return 1;
      }
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", 
             e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
      break; 
    }else if (strncmp(argv[1], ie[meio].cep, 8) > 0)
    {
            ini = meio + 1;
    }else
    {
            final = meio - 1;
    }
    }
    fclose(ind);
	fclose(cep);
	free(ie);
    return 0;
}
