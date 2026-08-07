#include <stdio.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <windows.h> //--Possibilita o uso de carácteres especiais--//

//--Variáveis globais--//
#define MAX_NOME 50
#define MAX_TERRAIN 5
#define MAX_MISSAO 100
const char *missoes[MAX_MISSAO] = {"Eliminar o azul", "Possuir 25 tropas", "Eliminar o verde ou o preto", "Eliminar o branco e possuir 20 tropas"};

//--Objeto territorio--//
typedef struct{
	char nome[MAX_NOME];
	char cor[MAX_NOME];
	int tropas;
	int win;
	int disp;
}territorio;

//--Classe de país escolhido--//
typedef struct{
	int index;
	char user[MAX_NOME];
	char *winCond;
	char cor[MAX_NOME];
}registro;

//--Pré declaração de classes--//
int dado();
int RandNum();
int RandMissao();
void atacar(territorio* atacante, territorio* defensor);
void CBE();
void Free(territorio *ter,registro *reg, int index);
void CadastroPaises(territorio *ter);
void PaisesCadastrados(territorio *ter);
void PaisesEliminados(territorio *ter);
int Registro(int num,registro *reg, territorio *ter);
void MostrarPais(territorio *ter, int index);
void GameLogic(territorio *ter, int index, registro *reg);
void Interface(territorio *ter, int index, registro *reg);
void Preset(territorio *ter);
void RegistroMissao(registro *reg,const char *missoes[MAX_MISSAO], int index);
void MostrarMissao(registro *reg, int index);
int MissionLogic(registro *reg, territorio *ter, int index);



//--Código principal--//
int main(){
	//--Uso da biblioteca windows.h--//
	SetConsoleOutputCP(CP_UTF8);


	//--Váriaveis locais--//
	int Ter;
	int option;
	int num = 0;
	int Def;
	int index;


	//--Definição de ponteiros--//
	territorio *ter;
	registro *reg;


	//--Alocação de memória--//
	ter = (territorio *) calloc(MAX_TERRAIN, sizeof(territorio));
	reg = (registro *) malloc(MAX_TERRAIN * sizeof(registro));


	//--Cadastro de territórios/menu principal--//
	//
	Preset(ter);
	//	
	//--Cadastro de territórios/menu principal--//	
	//--Limpeza do terminal e visualização de países cadastrados--//

	PaisesCadastrados(ter);

	//--Escolha do país--//
	printf("Digite o número do país que deseja escolher:  ");
	scanf("%d", &num);
	CBE();

	index = Registro(num, reg, ter);

	//--Lógica do Jogo--//

	GameLogic(ter, index, reg);


	Free(ter, reg, index);
	return 0;
}

//--Função free memory--//
void Free(territorio *ter,registro *reg, int index){
	free(ter);
	free(reg[index].winCond)
	free(reg);
}

//--Função de quantidade dinâmica de tropas--//
int dado(){
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1,10);
	int numran = distrib(gen);
	return numran;
}

//--Função de rolagem de dado--//
int RandNum(){
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0,6);
	int Numero = distrib(gen);
	return Numero;
}

//--Escolha aleatória de missão--//
int RandMissao(){
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0,3);
	int Numero = distrib(gen);
	return Numero;
}

//--Função de limpeza de buffer--//
void CBE(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

//--Função de ataque--//
void atacar(territorio* atacante, territorio* defensor){
	int tropas;
	int dadoA = RandNum();
	int dadoD = RandNum();

	std::cout << "============================\n";
	std::cout << "Atacando: " << defensor->nome << "\n";
	std::cout << "============================\n";

	std::this_thread::sleep_for(std::chrono::seconds(3));

	if (dadoA == 0 && dadoD == 0){
		std::cout << "Que azar, seu ataque passou perto!";
	}else if (dadoA > dadoD){
		std::cout << "Atacante: " << dadoA << "\n";
		std::cout << "Defensor: " << dadoD << "\n";
		defensor->tropas = defensor->tropas - dadoA;

		std::cout << dadoA << " tropas do defensor foram abatidas!\n";
		if (defensor->tropas <= 0){
			defensor->tropas = 0;
		}

	}else if (dadoD > dadoA){
		std::cout << "Defensor: " << dadoD << "\n";
		std::cout << "Atacante: " << dadoA << "\n";
		atacante->tropas = atacante->tropas - dadoD;

		std::cout << dadoD << " tropas do atacante foram abatidas!\n";
		if (atacante->tropas <= 0){
			atacante->tropas = 0;
		}
	}else if (dadoD == dadoA){
		atacante->tropas = atacante->tropas;
		defensor->tropas = defensor->tropas;
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

//--Função de preset de territorios--//
void Preset(territorio *ter){
	const char *paises[MAX_NOME] = {"África", "Rússia", "USA", "Brasil", "China"};
	const char *cores[MAX_NOME] = {"Branco", "Preto", "Azul", "Verde", "Vermelho"};

	for (int i = 0; i < MAX_TERRAIN; ++i)
	{
		strcpy(ter[i].nome, paises[i]);
		strcpy(ter[i].cor, cores[i]);
		ter[i].tropas = dado();
		ter[i].win = dado();
		ter[i].disp = 1;
	}
}

//--Função para cadastro de países-//
void CadastroPaises(territorio *ter){
	printf("=============================\n");
	printf("-Cadastro de países-\n");
	printf("=============================\n");
	for (int i = 0; i < MAX_TERRAIN; ++i)
	{

		//--Cadastrando os cinco países--//
		printf("---------------País %d--------------\n", i + 1);
		printf("Nome do país:  ");
		fgets(ter[i].nome, MAX_NOME, stdin);

		printf("Cor do país:  ");
		fgets(ter[i].cor, MAX_NOME, stdin);

		//--Limpeza das strings--//
		ter[i].nome[strcspn(ter[i].nome, "\n")] = '\0';
		ter[i].cor[strcspn(ter[i].cor, "\n")] = '\0';

		printf("Quantidade de tropas:  ");
		scanf("%d", &ter[i].tropas);

		ter[i].disp = 1;
		ter[i].win = dado();

		CBE();
	}

}

//--Função de chamada de interface de usuário--//
void Interface(territorio *ter, int index, registro *reg){
	
	PaisesCadastrados(ter);
	MostrarPais(ter, index);
	MostrarMissao(reg, index);

}

void MostrarMissao(registro *reg, int index){
	printf("--------------Sua missão--------------\n");
	printf("-%s-\n", reg[index].winCond);
	printf("======================================\n");
}

//--Interface de países--//
void MostrarPais(territorio *ter, int index){
	printf("--------------Seu país--------------\n");
	printf("-%s-\n", ter[index].nome);
	printf("-%s-\n", ter[index].cor);
	printf("-%d tropas-\n", ter[index].tropas);
	printf("====================================\n");
}

//--Interface de países cadastrados--//
void PaisesCadastrados(territorio *ter){
	printf("==================================\n");

	printf("-Países cadastrados-\n");
	for (int i = 0; i < MAX_TERRAIN; ++i)
	{
		if (ter[i].disp == 0 || ter[i].tropas == 0){continue;}

		printf("--------------%d--------------\n", i+1);
		printf("-%s-\n", ter[i].nome);
		printf("-%s-\n", ter[i].cor);
		printf("-%d tropas-\n", ter[i].tropas);
	}
	printf("==================================\n");
	for (int j = 0; j < MAX_TERRAIN; ++j)
	{
		if (ter[j].tropas == 0)
		{
			PaisesEliminados(ter);
			break;
		}
	}


}

//--Interface de países eliminados--//
void PaisesEliminados(territorio *ter){
	printf("===========!!!ELIMINADO!!!===========\n");
	for (int j = 0; j < MAX_TERRAIN; ++j)
	{
		if (ter[j].tropas == 0)
		{
			
			printf("-%s-\n", ter[j].nome);
			printf("-%s-\n", ter[j].cor);
			printf("-Tropas derrotadas!-\n");
		}else{
			continue;
		}
	}
	printf("=====================================\n");
}

//--Registro de território atacante--//
int Registro(int num, registro *reg, territorio *ter){
	int index = num - 1;
	if (index >= 0 && index < MAX_TERRAIN && ter[index].disp)
	{
		printf("=============================\n");
		printf("-Digite seu nome:  ");
		fgets(reg[index].user, MAX_NOME, stdin);

		reg[index].user[strcspn(reg[index].user, "\n")] = '\0';
		reg[index].index = index;
		strcpy(reg[index].cor, ter[index].cor);
		ter[index].disp = 0;

		RegistroMissao(reg, missoes, index);


		printf("-%s escolhido!-\n", ter[index].nome);
		printf("=============================\n");
		
		printf("Pressione Enter para continuar...");
		getchar();
		
		system("cls");
		CBE();
		return index;
	}else{
		return 0;
	}
}

//--Registro de missões--//
void RegistroMissao(registro *reg,const char *missoes[MAX_MISSAO], int index){
	int nummissao = RandMissao();
	reg[index].winCond = (char *) malloc(strlen(missoes[nummissao]) + 1);

	strcpy(reg[index].winCond, missoes[nummissao]);
}

//--Lógica de jogo--//
void GameLogic(territorio *ter, int index, registro *reg){
	int option = 0;
	int Def = 0;

	do{
		while(ter[index].tropas != 0){
			
			Def = 0;

			Interface(ter, index, reg);

			//--Escolhendo o Defensor--//
			printf("-Escolha um país para atacar-\n");
			scanf("%d", &Def);
			CBE();
			Def = Def - 1;

			//--Ataque--//
			atacar(&ter[index], &ter[Def]);
			
			if (ter[Def].tropas == 0){
				
				system("cls");
				printf("=============================\n");
				printf("-Capitão, rompemos o cerco inimigo! Avançar!-\n");
				printf("=============================\n");

				ter[index].tropas = ter[index].tropas + ter[Def].win;
				ter[Def].disp = 0;

				printf("\n-Excelente! %d homens adicionados a suas tropas-\nTotal: %d tropas\n", ter[Def].win, ter[index].tropas);

				printf("%s conquistado, continue assim!\n", ter[Def].nome);

				std::this_thread::sleep_for(std::chrono::seconds(5));
			}

			int logic = MissionLogic(reg, ter, index);
			switch (logic){
				case 0:
					continue;
				case 1:
					printf("=============================WAR=============================\n");
					printf("-Excelente! Missão concluída senhores, voltem às suas casas.-\n");
					printf("=============================================================\n");
					goto exit_game;
			}


		}

		system("cls");
		printf("=============================\n");
		printf("-Capitão, recuar! Nossas tropas foram abatidas!-\n");
		printf("=============================\n");
		printf("Pressione enter para sair...\n");
		getchar();
		CBE();
		exit_game:
			option = 1;

	}while(option != 1);

}

//--Lógica das missões--//
int MissionLogic(registro *reg, territorio *ter, int index){
	int branco_eliminado = 0, preto_eliminado = 0, azul_eliminado = 0, verde_eliminado = 0, vermelho_eliminado = 0;
	for (int i = 0; i < MAX_TERRAIN; ++i){
		if (strcmp(ter[i].cor, ter[index].cor) == 0){continue;}else
		if (strcmp(ter[i].cor, "Branco") == 0 && ter[i].tropas <= 0){branco_eliminado = 1;}else
		if (strcmp(ter[i].cor, "Preto") == 0 && ter[i].tropas <= 0){preto_eliminado = 1;}else
		if (strcmp(ter[i].cor, "Azul") == 0 && ter[i].tropas <= 0){azul_eliminado = 1;}else
		if (strcmp(ter[i].cor, "Verde") == 0 && ter[i].tropas <= 0){verde_eliminado = 1;}else
		if (strcmp(ter[i].cor, "Vermelho") == 0 && ter[i].tropas <= 0){vermelho_eliminado = 1;}else{
			continue;
		}
	}

	if (strcmp(reg[index].winCond, "Eliminar o azul") == 0 && azul_eliminado == 1){return 1;}else
	if (strcmp(reg[index].winCond, "Possuir 25 tropas") == 0 && ter[index].tropas >= 25){return 1;}else
	if (strcmp(reg[index].winCond, "Eliminar o verde ou o preto") == 0 && (verde_eliminado == 1 || preto_eliminado == 1)){return 1;}else
	if (strcmp(reg[index].winCond, "Eliminar o branco e possuir 20 tropas") == 0 && branco_eliminado == 1 && ter[index].tropas >= 20){return 1;}else{
		return 0;
	}

	return 0;
}