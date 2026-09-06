#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define TFA 100
#define TFAT 100

//--Struct's--
typedef struct
{
	char cpf[12]; 
	char nome[50];
}Aluno;

typedef struct
{
	char cpf[12];
	char nome[50];
}Instrutor;

typedef struct
{
	int id;
	char nome[50]; 
	char cpf_instrutor[12];
	int vagas;
}Atividade;

typedef struct
{
	int id;
	char nome[50];
	int ids_atividades; 
	int qtd_atividades;
}Pacote;

typedef struct
{
	int id;
	char nome[50];
	char tipo; 
	float valor_base;
}Plano;

//--Funcoes--

// Validacoes
int validarFormatoCPF(char cpf[])
{
	int i;
	if (strlen(cpf) != 11)
		return 0;

	for (i = 0; i < 11; i++)
	{
		if (!isdigit(cpf[i]))
			return 0;
	}
	return 1;
}

int buscaCPFAluno(Aluno Al[], int TLA, char cpf[])
{
	int i;
	for (i = 0; i < TLA; i++)
	{
		if (strcmp(Al[i].cpf, cpf) == 0)
			return i;
	}
	return -1;
}

// Menus
int menu()
{
	int opc=0;
	
	printf("\n\n<========== MENU ==========>");
	printf("\n1. GERENCIAR PESSOAS");
	printf("\n2. GERENCIAR ATIVIDADES");
	printf("\n3. GERENCIAR PACOTES");
	printf("\n4. GERENCIAR PLANOS");
	printf("\n5. MOVIMENTACOES");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d",&opc);
	
	printf("\n\n============================");
	
	return opc;
}

int menu_Pessoas()
{
	int opc=0;
	
	printf("\n\n<========== GERENCIAMENTO DE PESSOAS ==========>");
	printf("\n1. CADASTRAR ALUNO");
	printf("\n2. CADASTRAR INSTRUTOR");
	printf("\n3. CONSULTAR");
	printf("\n4. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d",&opc);
	
	printf("\n\n============================");
	
	return opc;
}

int menu_Atividades()
{
	int opc=0;
	
	printf("\n\n<========== GERENCIAMENTO DE ATIVIDADES ==========>");
	printf("\n1. CADASTRAR");
	printf("\n2. CONSULTAR");
	printf("\n3. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d",&opc);
	
	printf("\n\n============================");
	
	return opc;
}

int menu_Pacotes()
{
	int opc=0;
	
	printf("\n\n<========== GERENCIAMENTO DE PACOTES ==========>");
	printf("\n1. CADASTRAR");
	printf("\n2. CONSULTAR");
	printf("\n3. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d",&opc);
	
	printf("\n\n============================");
	
	return opc;
}

int menu_Planos()
{
	int opc=0;
	
	printf("\n\n<========== GERENCIAMENTO DE PLANOS ==========>");
	printf("\n1. CADASTRAR");
	printf("\n2. CONSULTAR");
	printf("\n3. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d",&opc);
	
	printf("\n\n============================");
	
	return opc;
}

// Cadastros
char cadastrar_Aluno(Aluno Al[], char *op, int TLA)
{
	char temp_cpf[20];
	int valido = 0;

	if (TLA < TFA)
	{
		printf("\n\n<==== CADASTRO DE ALUNO ===>");

		do
		{
			printf("\nInsira o CPF (apenas 11 numeros): ");
			fflush(stdin);
			gets(temp_cpf);

			if (!validarFormatoCPF(temp_cpf))
			{
				printf("\n** ERRO: CPF invalido! Digite exatamente 11 numeros. **\n");
			}
			else if (buscaCPFAluno(Al, TLA, temp_cpf) != -1)
			{
				printf("\n** ERRO: CPF ja cadastrado no sistema! **\n");
			}
			else
			{
				valido = 1; 
			}
		} while (!valido);

		strcpy(Al[TLA].cpf, temp_cpf);

		printf("\nInsira o nome: ");
		fflush(stdin);
		gets(Al[TLA].nome);

		printf("\nContinuar? S/N: ");
		fflush(stdin);
		scanf(" %c", op);

		*op = toupper(*op);

		printf("\n\n============================");
	}
	else
	{
		printf("\n**ERRO: Sistema cheio**");
	}

	return *op;
}

char cadastrar_Atividade(Atividade Atv[], Instrutor Inst[], char *op, int TLAT, int TLINST, int *prxid_atv)
{
	int i = 0;
	char temp_nome[50];
	int valido = 0;
	
	if(TLAT < TFAT)
	{
		printf("\n\n<==== CADASTRO DE ATIVIDADE ===>");
		
		do
		{
			printf("\nInsira o nome: ");
			fflush(stdin);
			gets(temp_nome);

			valido = 1;
			for(i = 0; i < TLAT; i++)
			{
				if(strcmp(temp_nome, Atv[i].nome) == 0)
				{
					valido = 0;
					break;
				}
			}
			
			if (!valido)
			{
				printf("\n** ERRO: Atividade ja cadastrada no sistema! **\n");
			}
		} while (!valido);
		
		strcpy(Atv[TLAT].nome, temp_nome);
		
		(*prxid_atv)++;
		Atv[TLAT].id = *prxid_atv;
		
		printf("\n<= Instrutores disponiveis: =>\n");
		printf("+--------------------------------+-----------------+\n");
		printf("| %-30s | %-15s |\n", "NOME", "CPF");
		printf("+--------------------------------+-----------------+\n");
		
		for(i = 0; i < TLINST; i++)
		{
			printf("| %-30s | %-15s |\n", Inst[i].nome, Inst[i].cpf);
		}
		printf("+--------------------------------+-----------------+\n");

		printf("\nInsira o CPF do instrutor responsavel: ");
		fflush(stdin);
		gets(Atv[TLAT].cpf_instrutor);
		
		printf("\nInsira a quantidade de vagas: ");
		scanf("%d", &Atv[TLAT].vagas);
		
		printf("\nContinuar? S/N: ");
		fflush(stdin);
		scanf(" %c", op);
		
		*op = toupper(*op);
		
		printf("\n\n============================");
	}
	else
		printf("\n**ERRO: Sistema cheio**");
	
	return *op;
}

main()
{
	//Variaveis
	int rop, opc, rsub;
	char op;
	int TLA=0, TLAT=0, TLINST=0;
	
	int prxid_atv=0, prxid_pc=0, prxid_pl=0;
	
	//Struct's
	Aluno Al[TFA];
	Atividade Atv[TFAT];
	Instrutor Inst[TFA];
	
	//Sistema
	printf("\n<============== SISTEMA ACADEMIA ==============>");
	
	//Menu
	rop = menu();
	
	while(rop!=0)
	{
		switch(rop)
		{
			// Gerenciar Pessoas
			case 1:
				rsub = menu_Pessoas();
				
				switch(rsub)
				{
					//Cadastrar Aluno
					case 1:
						op='S';
						while(op=='S')
						{
							cadastrar_Aluno(Al, &op, TLA);
							TLA++;
						}
						
						break;
						
					//Cadastrar Instrutor
					case 2:
						op='S';
						while(op=='S')
						{
							//cadastrar_Instrutor(Inst, &op, TLINST);
							TLINST++;
						}
						break;
						
					//Consultar
					case 3:
						//rop=menu_Consulta_Al_Inst();
						
						switch(rop)
						{
							//Consulta Aluno
							case 1:
								//consulta_Aluno();
								break;
							
							//Consulta Instrutor
							case 2:
								//consulta_Instrutor();
								break;
						}
						break;
						
					//Exclusao
					case 4:
						//rop=menu_Exclusao_Al_Inst();
						
						switch(rop)
						{
							//Excluir Aluno
							case 1:
								//excluir_Aluno();
								break;
							
							//Excluir Instrutor
							case 2:
								//excluir_Instrutor();
								break;
						}
						break;
					default:
						break;
				}
				
			break;
				
			// Gerenciar Atividades
			case 2:
				rsub = menu_Atividades();
				
				switch(rsub)
				{
					//Cadastrar Atividade
					case 1:
						op='S';
						while(op=='S')
						{
							cadastrar_Atividade(Atv, Inst, &op, TLAT, TLINST, &prxid_atv);
							TLAT++;
						}
						break;
					default:
						break;
				}
				
			break;
			
			// Gerenciar Pacotes
			case 3:
				//rsub= menu_Pacotes();
				
				switch(rsub)
				{
					default:
						break;    
				}
			break;
			
			// Gerenciar Planos
			case 4:
				//rsub= menu_Planos();
				
				switch(rsub)
				{
					default:
						break;
				}
			break;
			
			// Movimentacoes
			case 5:
				//rsub= menuMovimentacoes();
				
				switch(rsub)
				{
					default:
						break;
				}
			break;
			
			default:
				break;
		}
		rop = menu();	
	}
}
