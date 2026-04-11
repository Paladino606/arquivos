#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

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

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char** argv)
{
	FILE *a;
	Endereco *ea;
	long long int qtb, qtdReg, tamBytes;
	int n = 8;
	int sobra;
	char Arq[30];
	a = fopen("cep.dat","rb"); 
	fseek(a,0,SEEK_END);
	tamBytes = ftell(a);
	qtdReg = tamBytes/sizeof(Endereco); 
	qtb = qtdReg/n; 
	sobra = qtdReg%n; 
	
	ea = malloc(sizeof(Endereco)*(qtb+1));
	rewind(a);

	for(int i=0; i<n; i++) 
	{
		int qt = qtb + (i<sobra? 1 : 0); 
		
		fread(ea,sizeof(Endereco)*qt,1,a); 
		qsort(ea,qt,sizeof(Endereco),compara); 
		sprintf(Arq,"08bloco_%d.dat",i); 
		FILE *saida = fopen(Arq,"wb");
		fwrite(ea,sizeof(Endereco)*qt,1,saida); 
		fclose(saida); 
	}

	free(ea);
	fclose(a);
	
	int prox = 0, ultimo = n; 
	while(prox<ultimo-1){
		char Arq1[30];
		char Arq2[30];
		char Arq3[30];
		sprintf(Arq1,"08bloco_%d.dat",prox);
		sprintf(Arq2,"08bloco_%d.dat",prox+1);
		sprintf(Arq3,"08bloco_%d.dat",ultimo);
		FILE *a = fopen(Arq1,"rb");
		FILE *b = fopen(Arq2,"rb");
		FILE *saida = fopen(Arq3,"wb");

		Endereco ea, eb;
		fread(&ea,sizeof(Endereco),1,a);
		fread(&eb,sizeof(Endereco),1,b);

		
		while(!feof(a) && !feof(b))
		{
			if(compara(&ea,&eb)<0) // ea < eb
			{
				fwrite(&ea,sizeof(Endereco),1,saida);
				fread(&ea,sizeof(Endereco),1,a);
			}
			else if(compara(&ea,&eb)>0) // ea > eb
			{
				fwrite(&eb,sizeof(Endereco),1,saida);
				fread(&eb,sizeof(Endereco),1,b);
			} 
			else { // ea == eb
				fwrite(&ea,sizeof(Endereco),1,saida);
				fread(&ea,sizeof(Endereco),1,a);
				fread(&eb,sizeof(Endereco),1,b);
			}
		}

		while(!feof(a))
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);		
		}
		
		while(!feof(b))
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);		
		}

		fclose(a);
		fclose(b);
		fclose(saida);

		prox = prox + 2;
		ultimo++;
	}
	
}
