#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _IndiceEndereco indice;


struct _IndiceEndereco
{
    char cep[8];
    unsigned int posicao;
};


int compara(const void *e1, const void *e2)
{
    return strncmp(((indice*)e1)->cep,((indice*)e2)->cep,8);
}


int main(int argc, char**argv){
    FILE *f, *saida;
    indice *e;
    long posicao, qtd, qtd2;


    f = fopen("cep.dat", "rb");
    if (f == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    posicao = ftell(f);
    qtd = posicao/sizeof(indice);
    qtd2 = qtd;
    e = (indice*) malloc(qtd*sizeof(indice));
    rewind(f);


    indice *vet = malloc(qtd * sizeof(indice));
    qtd = fread(e, sizeof(indice), qtd, f);
    int i = 0;
    while( i < qtd){
        strncpy(vet[i].cep, e[i].cep, 8);
        vet[i].posicao = i;
        i++;
        qtd = fread(e, sizeof(indice), qtd, f);
    }


    qsort(e,qtd,sizeof(indice),compara);
    printf("Ordenado = OK\n");
    saida = fopen("indice-ordenado.dat","wb");
    fwrite(vet, sizeof(indice),qtd2, saida);
    fclose(saida);
    fclose(f);
    free(e);
    return 0;
}
