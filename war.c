#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_TERRAIN 5

//--Definição da estrutura--//
typedef struct{
	char nome[50];
	char cor[50];
	int tropas;
} Territorio;

//--Função para limpar o buffer--//
void CleanBufferEntry(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main(){
	Territorio Ter[MAX_TERRAIN];
	int TotalTerritorios = 0;
	int option;

	do{
		printf("=========================\n");
		printf(" Menu - Cadastro paises\n");
		printf("=========================\n");
		printf("1 - Cadastrar novo pais\n");
		printf("2 - Listar paises cadastrados\n");
		printf("3 - Sair\n");
		printf("=========================\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &option);
		CleanBufferEntry();

		switch(option){
		case 1:
			printf("\n--Novo pais--\n");
			if (TotalTerritorios < MAX_TERRAIN){

				printf("Digite o nome do pais: ");
				fgets(Ter[TotalTerritorios].nome, MAX_NOME, stdin);

				printf("Digite a cor do pais: ");
				fgets(Ter[TotalTerritorios].cor, MAX_NOME, stdin);

				Ter[TotalTerritorios].nome[strcspn(Ter[TotalTerritorios].nome, "\n")] = '\0';
				Ter[TotalTerritorios].cor[strcspn(Ter[TotalTerritorios].cor, "\n")] = '\0';

				printf("Digite a quantidade de tropas: ");
				scanf("%d", &Ter[TotalTerritorios].tropas);
				CleanBufferEntry();

				TotalTerritorios++;

				printf("-------------------------\n");
				printf("Pais cadastrado com sucesso!\n");
				printf("Pressione ENTER para continuar...\n");
				getchar();
				system("cls");
				break;
			}else{
				printf("!!!!!!!!!!!!!!!!!!\n");
				printf("Maximo de paises atingido!\n");
				printf("!!!!!!!!!!!!!!!!!!\n");
				printf("\n");
				printf("Pressione ENTER para continuar...\n");
				getchar();
				system("cls");
				break;
			}
		case 2:
			system("cls");

			for (int i = 0; i < TotalTerritorios; ++i)
			{
				printf("-Pais %d-\n", i+1);
				printf("Nome do pais: %s\n", Ter[i].nome);
				printf("Cor do pais: %s\n", Ter[i].cor);
				printf("Quantidade de tropas: %d\n", Ter[i].tropas);
				printf("-------------------------\n");
			}

			printf("Pressione ENTER para continuar...\n");
			getchar();
			system("cls");
			break;

		case 3:
			int j;
			printf("Realmente deseja sair? (y/n)");
			j = getchar();
			
			CleanBufferEntry();

			if (j == 'y' || j == 'Y')
			{
				exit(EXIT_SUCCESS);
			}else{
				system("cls");
				break;
			}

		default:
			printf("Opcao invalida, tente novamente!\n");
			printf("Pressione ENTER para continuar...\n");
			break;
		}
	}while(option != 0);

	return 0;

}