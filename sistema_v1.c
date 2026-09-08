#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TF 100

//-- Struct's --
typedef struct
{
	char cpf[12]; 
	char nome[50];
	int id_plano;
	int id_pacote;
} Aluno;

typedef struct
{
	char cpf[12]; 
	char nome[50];
	char especialidade[30];
} Instrutor;

typedef struct
{
	int id;
	char nome[50]; 
	char cpf_instrutor[12];
	int vagas;
} Atividade;

typedef struct
{
	int id;
	char nome[50];
	int ids_atividades[10]; 
	int qtd_atividades;
} Pacote;

typedef struct
{
	int id;
	char nome[50];
	char tipo; 
	float valor_base;
} Plano;

//-- Funcoes Auxiliares --
void limparBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *str, int tamanho)
{
	fgets(str, tamanho, stdin);
	str[strcspn(str, "\n")] = '\0';
}

//-- Validacoes e Buscas --
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

int buscaCPFInstrutor(Instrutor Inst[], int TLINST, char cpf[])
{
	int i;
	for (i = 0; i < TLINST; i++)
	{
		if (strcmp(Inst[i].cpf, cpf) == 0)
			return i;
	}
	return -1;
}

int buscaAtividadeID(Atividade Atv[], int TLAT, int id)
{
	int i;
	for (i = 0; i < TLAT; i++)
	{
		if (Atv[i].id == id)
			return i;
	}
	return -1;
}

int buscaPacoteID(Pacote Pc[], int TLPC, int id)
{
	int i;
	for (i = 0; i < TLPC; i++)
	{
		if (Pc[i].id == id)
			return i;
	}
	return -1;
}

int buscaPlanoID(Plano Pl[], int TLPL, int id)
{
	int i;
	for (i = 0; i < TLPL; i++)
	{
		if (Pl[i].id == id)
			return i;
	}
	return -1;
}

//-- Menus --
int menu()
{
	int opc = 0;
	
	printf("\n\n<========== MENU ==========>");
	printf("\n1. GERENCIAR PESSOAS");
	printf("\n2. GERENCIAR ATIVIDADES");
	printf("\n3. GERENCIAR PACOTES");
	printf("\n4. GERENCIAR PLANOS");
	printf("\n5. MOVIMENTACOES");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_Pessoas()
{
	int opc = 0;
	
	printf("\n\n<========== GERENCIAMENTO DE PESSOAS ==========>");
	printf("\n1. CADASTRAR ALUNO");
	printf("\n2. CADASTRAR INSTRUTOR");
	printf("\n3. CONSULTAR");
	printf("\n4. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_al_inst()
{
	int opc = 0;
	
	printf("\n\n<========== CONSULTA DE PESSOAS ==========>");
	printf("\n1. ALUNO");
	printf("\n2. INSTRUTOR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_Exclusao_Al_Inst()
{
	int opc = 0;
	
	printf("\n\n<========== EXCLUSAO DE PESSOAS ==========>");
	printf("\n1. ALUNO");
	printf("\n2. INSTRUTOR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_Atividades()
{
	int opc = 0;
	
	printf("\n\n<========== GERENCIAMENTO DE ATIVIDADES ==========>");
	printf("\n1. CADASTRAR");
	printf("\n2. CONSULTAR");
	printf("\n3. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_Pacotes()
{
	int opc = 0;
	
	printf("\n\n<========== GERENCIAMENTO DE PACOTES ==========>");
	printf("\n1. CADASTRAR");
	printf("\n2. CONSULTAR");
	printf("\n3. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_Planos()
{
	int opc = 0;
	
	printf("\n\n<========== GERENCIAMENTO DE PLANOS ==========>");
	printf("\n1. CADASTRAR");
	printf("\n2. CONSULTAR");
	printf("\n3. EXCLUIR");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

int menu_Movimentacoes()
{
	int opc = 0;
	
	printf("\n\n<========== MOVIMENTACOES ==========>");
	printf("\n1. VINCULAR PLANO AO ALUNO");
	printf("\n2. VINCULAR PACOTE AO ALUNO");
	printf("\n0. SAIR");
	
	printf("\n\n Escolha: ");
	scanf("%d", &opc);
	limparBuffer();
	
	printf("\n============================");
	return opc;
}

//-- Cadastros --
char cadastrar_Aluno(Aluno Al[], char *op, int TLA)
{
	char temp_cpf[20];
	int valido = 0;

	if (TLA < TF)
	{
		printf("\n\n<==== CADASTRO DE ALUNO ===>");

		do
		{
			printf("\nInsira o CPF (apenas 11 numeros): ");
			lerString(temp_cpf, 20);

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

		printf("Insira o nome: ");
		lerString(Al[TLA].nome, 50);

		Al[TLA].id_plano = -1;
		Al[TLA].id_pacote = -1;

		printf("\nContinuar cadastrando alunos? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Sistema cheio **");
		*op = 'N';
	}

	return *op;
}

char cadastrar_Instrutor(Instrutor Inst[], char *op, int TLINST)
{
	char temp_cpf[20];
	int valido = 0;

	if (TLINST < TF)
	{
		printf("\n\n<==== CADASTRO DE INSTRUTOR ===>");

		do
		{
			printf("\nInsira o CPF (apenas 11 numeros): ");
			lerString(temp_cpf, 20);

			if (!validarFormatoCPF(temp_cpf))
			{
				printf("\n** ERRO: CPF invalido! Digite exatamente 11 numeros. **\n");
			}
			else if (buscaCPFInstrutor(Inst, TLINST, temp_cpf) != -1)
			{
				printf("\n** ERRO: CPF ja cadastrado no sistema! **\n");
			}
			else
			{
				valido = 1; 
			}
		} while (!valido);

		strcpy(Inst[TLINST].cpf, temp_cpf);

		printf("Insira o nome: ");
		lerString(Inst[TLINST].nome, 50);
		
		printf("Insira a especialidade: ");
		lerString(Inst[TLINST].especialidade, 30);

		printf("\nContinuar cadastrando instrutores? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Sistema cheio **");
		*op = 'N';
	}

	return *op;
}

char cadastrar_Atividade(Atividade Atv[], Instrutor Inst[], char *op, int TLAT, int TLINST, int *prxid_atv)
{
	int i = 0;
	char temp_nome[50];
	int valido = 0;
	
	if (TLAT < TF)
	{
		printf("\n\n<==== CADASTRO DE ATIVIDADE ===>");
		
		do
		{
			printf("\nInsira o nome: ");
			lerString(temp_nome, 50);

			valido = 1;
			for (i = 0; i < TLAT; i++)
			{
				if (strcmp(temp_nome, Atv[i].nome) == 0)
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
		
		for (i = 0; i < TLINST; i++)
		{
			printf("| %-30s | %-15s |\n", Inst[i].nome, Inst[i].cpf);
		}
		printf("+--------------------------------+-----------------+\n");

		printf("\nInsira o CPF do instrutor responsavel: ");
		lerString(Atv[TLAT].cpf_instrutor, 12);
		
		printf("Insira a quantidade de vagas: ");
		scanf("%d", &Atv[TLAT].vagas);
		limparBuffer();
		
		printf("\nContinuar cadastrando atividades? S/N: ");
		scanf(" %c", op);
		limparBuffer();
		
		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Sistema cheio **");
		*op = 'N';
	}
	
	return *op;
}

char cadastrar_Pacote(Pacote Pc[], Atividade Atv[], char *op, int TLPC, int TLAT, int *prxid_pc)
{
	int i = 0, id_atv = 0;
	char add_mais = 'S';

	if (TLPC < TF)
	{
		printf("\n\n<==== CADASTRO DE PACOTE ===>");

		printf("\nInsira o nome do Pacote: ");
		lerString(Pc[TLPC].nome, 50);

		(*prxid_pc)++;
		Pc[TLPC].id = *prxid_pc;
		Pc[TLPC].qtd_atividades = 0;

		printf("\n<= Atividades disponiveis: =>\n");
		printf("+------+--------------------------------+\n");
		printf("| %-4s | %-30s |\n", "ID", "NOME");
		printf("+------+--------------------------------+\n");
		for (i = 0; i < TLAT; i++)
		{
			printf("| %-4d | %-30s |\n", Atv[i].id, Atv[i].nome);
		}
		printf("+------+--------------------------------+\n");

		while (add_mais == 'S' && Pc[TLPC].qtd_atividades < 10)
		{
			printf("\nInsira o ID da Atividade para incluir no Pacote: ");
			scanf("%d", &id_atv);
			limparBuffer();

			if (buscaAtividadeID(Atv, TLAT, id_atv) != -1)
			{
				Pc[TLPC].ids_atividades[Pc[TLPC].qtd_atividades] = id_atv;
				Pc[TLPC].qtd_atividades++;
				printf("\n** Atividade adicionada com sucesso! **\n");
			}
			else
			{
				printf("\n** ERRO: Atividade nao encontrada! **\n");
			}

			if (Pc[TLPC].qtd_atividades < 10)
			{
				printf("\nDeseja incluir mais uma atividade no pacote? S/N: ");
				scanf(" %c", &add_mais);
				limparBuffer();
				add_mais = toupper(add_mais);
			}
		}

		printf("\nContinuar cadastrando pacotes? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Sistema cheio **");
		*op = 'N';
	}

	return *op;
}

char cadastrar_Plano(Plano Pl[], char *op, int TLPL, int *prxid_pl)
{
	if (TLPL < TF)
	{
		printf("\n\n<==== CADASTRO DE PLANO ===>");

		printf("\nInsira o nome do Plano: ");
		lerString(Pl[TLPL].nome, 50);

		(*prxid_pl)++;
		Pl[TLPL].id = *prxid_pl;

		printf("Insira o tipo do Plano (M - Mensal, A - Anual): ");
		scanf(" %c", &Pl[TLPL].tipo);
		Pl[TLPL].tipo = toupper(Pl[TLPL].tipo);

		printf("Insira o valor base: ");
		scanf("%f", &Pl[TLPL].valor_base);
		limparBuffer();

		printf("\nContinuar cadastrando planos? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Sistema cheio **");
		*op = 'N';
	}

	return *op;
}

//-- Consultas (Atualizadas com redirecionamento de cadastro) --
char consultar_Aluno(Aluno Al[], Plano Pl[], Pacote Pc[], char *op, int TLA, int TLPL, int TLPC, int *quer_cadastrar)
{
	char temp_cpf[20];
	int pos, pos_pl, pos_pc;
	char nome_plano[50], nome_pacote[50];
	*quer_cadastrar = 0;
	
	if (TLA > 0)
	{
		printf("\n\n<==== CONSULTA DE ALUNO ===>");
		printf("\nInsira o CPF do Aluno (11 numeros): ");
		lerString(temp_cpf, 20);

		pos = buscaCPFAluno(Al, TLA, temp_cpf);
		
		if (pos != -1)
		{
			pos_pl = buscaPlanoID(Pl, TLPL, Al[pos].id_plano);
			if (pos_pl != -1)
				strcpy(nome_plano, Pl[pos_pl].nome);
			else
				strcpy(nome_plano, "Nao Vinculado");

			pos_pc = buscaPacoteID(Pc, TLPC, Al[pos].id_pacote);
			if (pos_pc != -1)
				strcpy(nome_pacote, Pc[pos_pc].nome);
			else
				strcpy(nome_pacote, "Nao Vinculado");

			printf("\n\n+--------------------------------+-----------------+--------------------+--------------------+");
			printf("\n| %-30s | %-15s | %-18s | %-18s |", "NOME DO ALUNO", "CPF", "PLANO", "PACOTE");
			printf("\n+--------------------------------+-----------------+--------------------+--------------------+");
			printf("\n| %-30s | %-15s | %-18s | %-18s |", Al[pos].nome, Al[pos].cpf, nome_plano, nome_pacote);
			printf("\n+--------------------------------+-----------------+--------------------+--------------------+\n");

			printf("\nConsultar outro? S/N: ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
		}
		else
		{
			printf("\nNenhum aluno cadastrado com este CPF, deseja cadastrar? (S/N): ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
			if (*op == 'S')
			{
				*quer_cadastrar = 1;
			}
		}
		printf("\n============================");
	}
	else
	{
		printf("\nNenhum aluno cadastrado, deseja cadastrar? (S/N): ");
		scanf(" %c", op);
		limparBuffer();
		*op = toupper(*op);
		if (*op == 'S')
		{
			*quer_cadastrar = 1;
		}
	}
	
	return *op;
}

char consultar_Instrutor(Instrutor Inst[], char *op, int TLINST, int *quer_cadastrar)
{
	char temp_cpf[20];
	int pos;
	*quer_cadastrar = 0;

	if (TLINST > 0)
	{
		printf("\n\n<==== CONSULTA DE INSTRUTOR ===>");
		printf("\nInsira o CPF do Instrutor (11 numeros): ");
		lerString(temp_cpf, 20);

		pos = buscaCPFInstrutor(Inst, TLINST, temp_cpf);

		if (pos != -1)
		{
			printf("\n\n+--------------------------------+-----------------+--------------------+");
			printf("\n| %-30s | %-15s | %-18s |", "NOME DO INSTRUTOR", "CPF", "ESPECIALIDADE");
			printf("\n+--------------------------------+-----------------+--------------------+");
			printf("\n| %-30s | %-15s | %-18s |", Inst[pos].nome, Inst[pos].cpf, Inst[pos].especialidade);
			printf("\n+--------------------------------+-----------------+--------------------+\n");

			printf("\nConsultar outro? S/N: ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
		}
		else
		{
			printf("\nNenhum instrutor cadastrado com este CPF, deseja cadastrar? (S/N): ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
			if (*op == 'S')
			{
				*quer_cadastrar = 1;
			}
		}
		printf("\n============================");
	}
	else
	{
		printf("\nNenhum instrutor cadastrado, deseja cadastrar? (S/N): ");
		scanf(" %c", op);
		limparBuffer();
		*op = toupper(*op);
		if (*op == 'S')
		{
			*quer_cadastrar = 1;
		}
	}

	return *op;
}

char consultar_Atividade(Atividade Atv[], char *op, int TLAT, int *quer_cadastrar)
{
	int id, pos;
	*quer_cadastrar = 0;

	if (TLAT > 0)
	{
		printf("\n\n<==== CONSULTA DE ATIVIDADE ===>");
		printf("\nInsira o ID da Atividade: ");
		scanf("%d", &id);
		limparBuffer();

		pos = buscaAtividadeID(Atv, TLAT, id);

		if (pos != -1)
		{
			printf("\n\n+------+--------------------------------+-----------------+-------+");
			printf("\n| %-4s | %-30s | %-15s | %-5s |", "ID", "NOME", "CPF INSTRUTOR", "VAGAS");
			printf("\n+------+--------------------------------+-----------------+-------+");
			printf("\n| %-4d | %-30s | %-15s | %-5d |", Atv[pos].id, Atv[pos].nome, Atv[pos].cpf_instrutor, Atv[pos].vagas);
			printf("\n+------+--------------------------------+-----------------+-------+\n");

			printf("\nConsultar outra? S/N: ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
		}
		else
		{
			printf("\nNenhuma atividade cadastrada com este ID, deseja cadastrar? (S/N): ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
			if (*op == 'S')
			{
				*quer_cadastrar = 1;
			}
		}
		printf("\n============================");
	}
	else
	{
		printf("\nNenhuma atividade cadastrada, deseja cadastrar? (S/N): ");
		scanf(" %c", op);
		limparBuffer();
		*op = toupper(*op);
		if (*op == 'S')
		{
			*quer_cadastrar = 1;
		}
	}

	return *op;
}

char consultar_Pacote(Pacote Pc[], char *op, int TLPC, int *quer_cadastrar)
{
	int id, pos, i;
	*quer_cadastrar = 0;

	if (TLPC > 0)
	{
		printf("\n\n<==== CONSULTA DE PACOTE ===>");
		printf("\nInsira o ID do Pacote: ");
		scanf("%d", &id);
		limparBuffer();

		pos = buscaPacoteID(Pc, TLPC, id);

		if (pos != -1)
		{
			printf("\n\n+------+--------------------------------+-----------------+");
			printf("\n| %-4s | %-30s | %-15s |", "ID", "NOME DO PACOTE", "QTD ATIVIDADES");
			printf("\n+------+--------------------------------+-----------------+");
			printf("\n| %-4d | %-30s | %-15d |", Pc[pos].id, Pc[pos].nome, Pc[pos].qtd_atividades);
			printf("\n+------+--------------------------------+-----------------+");
			printf("\n| IDs Atividades inclusas: ");
			for (i = 0; i < Pc[pos].qtd_atividades; i++)
			{
				printf("%d ", Pc[pos].ids_atividades[i]);
			}
			printf("\n+---------------------------------------------------------+\n");

			printf("\nConsultar outro? S/N: ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
		}
		else
		{
			printf("\nNenhum pacote cadastrado com este ID, deseja cadastrar? (S/N): ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
			if (*op == 'S')
			{
				*quer_cadastrar = 1;
			}
		}
		printf("\n============================");
	}
	else
	{
		printf("\nNenhum pacote cadastrado, deseja cadastrar? (S/N): ");
		scanf(" %c", op);
		limparBuffer();
		*op = toupper(*op);
		if (*op == 'S')
		{
			*quer_cadastrar = 1;
		}
	}

	return *op;
}

char consultar_Plano(Plano Pl[], char *op, int TLPL, int *quer_cadastrar)
{
	int id, pos;
	*quer_cadastrar = 0;

	if (TLPL > 0)
	{
		printf("\n\n<==== CONSULTA DE PLANO ===>");
		printf("\nInsira o ID do Plano: ");
		scanf("%d", &id);
		limparBuffer();

		pos = buscaPlanoID(Pl, TLPL, id);

		if (pos != -1)
		{
			printf("\n\n+------+--------------------------------+------+------------+");
			printf("\n| %-4s | %-30s | %-4s | %-10s |", "ID", "NOME DO PLANO", "TIPO", "VALOR BASE");
			printf("\n+------+--------------------------------+------+------------+");
			printf("\n| %-4d | %-30s | %-4c | R$ %-7.2f |", Pl[pos].id, Pl[pos].nome, Pl[pos].tipo, Pl[pos].valor_base);
			printf("\n+------+--------------------------------+------+------------+\n");

			printf("\nConsultar outro? S/N: ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
		}
		else
		{
			printf("\nNenhum plano cadastrado com este ID, deseja cadastrar? (S/N): ");
			scanf(" %c", op);
			limparBuffer();
			*op = toupper(*op);
			if (*op == 'S')
			{
				*quer_cadastrar = 1;
			}
		}
		printf("\n============================");
	}
	else
	{
		printf("\nNenhum plano cadastrado, deseja cadastrar? (S/N): ");
		scanf(" %c", op);
		limparBuffer();
		*op = toupper(*op);
		if (*op == 'S')
		{
			*quer_cadastrar = 1;
		}
	}

	return *op;
}

//-- Exclusoes --
char excluir_Aluno(Aluno Al[], char *op, int *TLA)
{
	char temp_cpf[20], confirma;
	int pos, i;
	
	if (*TLA > 0)
	{
		printf("\n\n<==== EXCLUSAO DE ALUNO ===>");
		
		printf("\nInsira o CPF do Aluno (11 numeros): ");
		lerString(temp_cpf, 20);

		pos = buscaCPFAluno(Al, *TLA, temp_cpf);
		
		if (pos != -1)
		{
			printf("\n\n+--------------------------------+-----------------+");
			printf("\n| %-30s | %-15s |", "NOME DO ALUNO", "CPF");
			printf("\n+--------------------------------+-----------------+");
			printf("\n| %-30s | %-15s |", Al[pos].nome, Al[pos].cpf);
			printf("\n+--------------------------------+-----------------+\n");

			printf("\nCONFIRMAR EXCLUSAO? S/N: ");
			scanf(" %c", &confirma);
			limparBuffer();
			confirma = toupper(confirma);

			if (confirma == 'S')
			{
				for (i = pos; i < *TLA - 1; i++)
				{
					Al[i] = Al[i + 1];
				}
				(*TLA)--;
				printf("\n** Aluno excluido com sucesso! **\n");
			}
			else
			{
				printf("\n** Exclusao cancelada! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Aluno nao encontrado no sistema! **\n");
		}
		
		printf("\nExcluir outro? S/N: ");
		scanf(" %c", op);
		limparBuffer();
		
		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Nenhum aluno cadastrado **\n");
		*op = 'N';
	}
	
	return *op;
}

char excluir_Instrutor(Instrutor Inst[], char *op, int *TLINST)
{
	char temp_cpf[20], confirma;
	int pos, i;

	if (*TLINST > 0)
	{
		printf("\n\n<==== EXCLUSAO DE INSTRUTOR ===>");

		printf("\nInsira o CPF do Instrutor (11 numeros): ");
		lerString(temp_cpf, 20);

		pos = buscaCPFInstrutor(Inst, *TLINST, temp_cpf);

		if (pos != -1)
		{
			printf("\n\n+--------------------------------+-----------------+");
			printf("\n| %-30s | %-15s |", "NOME DO INSTRUTOR", "CPF");
			printf("\n+--------------------------------+-----------------+");
			printf("\n| %-30s | %-15s |", Inst[pos].nome, Inst[pos].cpf);
			printf("\n+--------------------------------+-----------------+\n");

			printf("\nCONFIRMAR EXCLUSAO? S/N: ");
			scanf(" %c", &confirma);
			limparBuffer();
			confirma = toupper(confirma);

			if (confirma == 'S')
			{
				for (i = pos; i < *TLINST - 1; i++)
				{
					Inst[i] = Inst[i + 1];
				}
				(*TLINST)--;
				printf("\n** Instrutor excluido com sucesso! **\n");
			}
			else
			{
				printf("\n** Exclusao cancelada! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Instrutor nao encontrado no sistema! **\n");
		}

		printf("\nExcluir outro? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Nenhum instrutor cadastrado **\n");
		*op = 'N';
	}

	return *op;
}

char excluir_Atividade(Atividade Atv[], char *op, int *TLAT)
{
	int id, pos, i;
	char confirma;

	if (*TLAT > 0)
	{
		printf("\n\n<==== EXCLUSAO DE ATIVIDADE ===>");

		printf("\nInsira o ID da Atividade: ");
		scanf("%d", &id);
		limparBuffer();

		pos = buscaAtividadeID(Atv, *TLAT, id);

		if (pos != -1)
		{
			printf("\n\n+------+--------------------------------+");
			printf("\n| %-4s | %-30s |", "ID", "NOME DA ATIVIDADE");
			printf("\n+------+--------------------------------+");
			printf("\n| %-4d | %-30s |", Atv[pos].id, Atv[pos].nome);
			printf("\n+------+--------------------------------+\n");

			printf("\nCONFIRMAR EXCLUSAO? S/N: ");
			scanf(" %c", &confirma);
			limparBuffer();
			confirma = toupper(confirma);

			if (confirma == 'S')
			{
				for (i = pos; i < *TLAT - 1; i++)
				{
					Atv[i] = Atv[i + 1];
				}
				(*TLAT)--;
				printf("\n** Atividade excluida com sucesso! **\n");
			}
			else
			{
				printf("\n** Exclusao cancelada! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Atividade nao encontrada no sistema! **\n");
		}

		printf("\nExcluir outra? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Nenhuma atividade cadastrada **\n");
		*op = 'N';
	}

	return *op;
}

char excluir_Pacote(Pacote Pc[], char *op, int *TLPC)
{
	int id, pos, i;
	char confirma;

	if (*TLPC > 0)
	{
		printf("\n\n<==== EXCLUSAO DE PACOTE ===>");

		printf("\nInsira o ID do Pacote: ");
		scanf("%d", &id);
		limparBuffer();

		pos = buscaPacoteID(Pc, *TLPC, id);

		if (pos != -1)
		{
			printf("\n\n+------+--------------------------------+");
			printf("\n| %-4s | %-30s |", "ID", "NOME DO PACOTE");
			printf("\n+------+--------------------------------+");
			printf("\n| %-4d | %-30s |", Pc[pos].id, Pc[pos].nome);
			printf("\n+------+--------------------------------+\n");

			printf("\nCONFIRMAR EXCLUSAO? S/N: ");
			scanf(" %c", &confirma);
			limparBuffer();
			confirma = toupper(confirma);

			if (confirma == 'S')
			{
				for (i = pos; i < *TLPC - 1; i++)
				{
					Pc[i] = Pc[i + 1];
				}
				(*TLPC)--;
				printf("\n** Pacote excluido com sucesso! **\n");
			}
			else
			{
				printf("\n** Exclusao cancelada! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Pacote nao encontrado no sistema! **\n");
		}

		printf("\nExcluir outro? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Nenhum pacote cadastrado **\n");
		*op = 'N';
	}

	return *op;
}

char excluir_Plano(Plano Pl[], char *op, int *TLPL)
{
	int id, pos, i;
	char confirma;

	if (*TLPL > 0)
	{
		printf("\n\n<==== EXCLUSAO DE PLANO ===>");

		printf("\nInsira o ID do Plano: ");
		scanf("%d", &id);
		limparBuffer();

		pos = buscaPlanoID(Pl, *TLPL, id);

		if (pos != -1)
		{
			printf("\n\n+------+--------------------------------+");
			printf("\n| %-4s | %-30s |", "ID", "NOME DO PLANO");
			printf("\n+------+--------------------------------+");
			printf("\n| %-4d | %-30s |", Pl[pos].id, Pl[pos].nome);
			printf("\n+------+--------------------------------+\n");

			printf("\nCONFIRMAR EXCLUSAO? S/N: ");
			scanf(" %c", &confirma);
			limparBuffer();
			confirma = toupper(confirma);

			if (confirma == 'S')
			{
				for (i = pos; i < *TLPL - 1; i++)
				{
					Pl[i] = Pl[i + 1];
				}
				(*TLPL)--;
				printf("\n** Plano excluido com sucesso! **\n");
			}
			else
			{
				printf("\n** Exclusao cancelada! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Plano nao encontrado no sistema! **\n");
		}

		printf("\nExcluir outro? S/N: ");
		scanf(" %c", op);
		limparBuffer();

		*op = toupper(*op);
		printf("\n============================");
	}
	else
	{
		printf("\n** ERRO: Nenhum plano cadastrado **\n");
		*op = 'N';
	}

	return *op;
}

//-- Movimentacoes --
void vincular_Plano_Aluno(Aluno Al[], Plano Pl[], int TLA, int TLPL)
{
	char temp_cpf[20];
	int pos_al, id_pl, pos_pl;

	if (TLA > 0 && TLPL > 0)
	{
		printf("\n\n<==== VINCULAR PLANO AO ALUNO ===>");

		printf("\nInsira o CPF do Aluno: ");
		lerString(temp_cpf, 20);

		pos_al = buscaCPFAluno(Al, TLA, temp_cpf);

		if (pos_al != -1)
		{
			printf("Insira o ID do Plano: ");
			scanf("%d", &id_pl);
			limparBuffer();

			pos_pl = buscaPlanoID(Pl, TLPL, id_pl);

			if (pos_pl != -1)
			{
				Al[pos_al].id_plano = id_pl;
				printf("\n** Plano vinculado com sucesso ao Aluno! **\n");
			}
			else
			{
				printf("\n** ERRO: Plano nao encontrado! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Aluno nao encontrado! **\n");
		}
	}
	else
	{
		printf("\n** ERRO: Requer ao menos 1 aluno e 1 plano cadastrados! **\n");
	}
}

void vincular_Pacote_Aluno(Aluno Al[], Pacote Pc[], int TLA, int TLPC)
{
	char temp_cpf[20];
	int pos_al, id_pc, pos_pc;

	if (TLA > 0 && TLPC > 0)
	{
		printf("\n\n<==== VINCULAR PACOTE AO ALUNO ===>");

		printf("\nInsira o CPF do Aluno: ");
		lerString(temp_cpf, 20);

		pos_al = buscaCPFAluno(Al, TLA, temp_cpf);

		if (pos_al != -1)
		{
			printf("Insira o ID do Pacote: ");
			scanf("%d", &id_pc);
			limparBuffer();

			pos_pc = buscaPacoteID(Pc, TLPC, id_pc);

			if (pos_pc != -1)
			{
				Al[pos_al].id_pacote = id_pc;
				printf("\n** Pacote vinculado com sucesso ao Aluno! **\n");
			}
			else
			{
				printf("\n** ERRO: Pacote nao encontrado! **\n");
			}
		}
		else
		{
			printf("\n** ERRO: Aluno nao encontrado! **\n");
		}
	}
	else
	{
		printf("\n** ERRO: Requer ao menos 1 aluno e 1 pacote cadastrados! **\n");
	}
}

//-- Main --
int main()
{
	// Variaveis
	int rop, rsub, quer_cadastrar = 0;
	char op;
	int TLA = 0, TLAT = 0, TLINST = 0, TLPC = 0, TLPL = 0;
	int prxid_atv = 0, prxid_pc = 0, prxid_pl = 0;
	
	// Struct's
	Aluno Al[TF];
	Atividade Atv[TF];
	Instrutor Inst[TF];
	Pacote Pc[TF];
	Plano Pl[TF];
	
	// Sistema
	printf("\n<============== SISTEMA ACADEMIA ==============>");
	
	// Menu Principal
	rop = menu();
	
	while (rop != 0)
	{
		switch (rop)
		{
			// Gerenciar Pessoas
			case 1:
				rsub = menu_Pessoas();
				
				switch (rsub)
				{
					// Cadastrar Aluno
					case 1:
						op = 'S';
						while (op == 'S')
						{
							cadastrar_Aluno(Al, &op, TLA);
							if (op == 'S') TLA++;
						}
						break;
						
					// Cadastrar Instrutor
					case 2:
						op = 'S';
						while (op == 'S')
						{
							cadastrar_Instrutor(Inst, &op, TLINST);
							if (op == 'S') TLINST++;
						}
						break;
						
					// Consultar
					case 3:
						rsub = menu_al_inst();
						
						switch (rsub)
						{
							case 1: // Consulta Aluno
								op = 'S';
								while (op == 'S')
								{
									consultar_Aluno(Al, Pl, Pc, &op, TLA, TLPL, TLPC, &quer_cadastrar);
									if (quer_cadastrar)
									{
										op = 'S';
										while (op == 'S')
										{
											cadastrar_Aluno(Al, &op, TLA);
											if (op == 'S') TLA++;
										}
										break;
									}
								}
								break;
							
							case 2: // Consulta Instrutor
								op = 'S';
								while (op == 'S')
								{
									consultar_Instrutor(Inst, &op, TLINST, &quer_cadastrar);
									if (quer_cadastrar)
									{
										op = 'S';
										while (op == 'S')
										{
											cadastrar_Instrutor(Inst, &op, TLINST);
											if (op == 'S') TLINST++;
										}
										break;
									}
								}
								break;
						}
						break;
						
					// Exclusao
					case 4:
						rsub = menu_Exclusao_Al_Inst();
						
						switch (rsub)
						{
							case 1: // Excluir Aluno
								op = 'S';
								while (op == 'S')
								{
									excluir_Aluno(Al, &op, &TLA);
								}
								break;
							
							case 2: // Excluir Instrutor
								op = 'S';
								while (op == 'S')
								{
									excluir_Instrutor(Inst, &op, &TLINST);
								}
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
				
				switch (rsub)
				{
					case 1: // Cadastrar Atividade
						op = 'S';
						while (op == 'S')
						{
							cadastrar_Atividade(Atv, Inst, &op, TLAT, TLINST, &prxid_atv);
							if (op == 'S') TLAT++;
						}
						break;

					case 2: // Consultar Atividade
						op = 'S';
						while (op == 'S')
						{
							consultar_Atividade(Atv, &op, TLAT, &quer_cadastrar);
							if (quer_cadastrar)
							{
								op = 'S';
								while (op == 'S')
								{
									cadastrar_Atividade(Atv, Inst, &op, TLAT, TLINST, &prxid_atv);
									if (op == 'S') TLAT++;
								}
								break;
							}
						}
						break;

					case 3: // Excluir Atividade
						op = 'S';
						while (op == 'S')
						{
							excluir_Atividade(Atv, &op, &TLAT);
						}
						break;

					default:
						break;
				}
				break;
			
			// Gerenciar Pacotes
			case 3:
				rsub = menu_Pacotes();
				
				switch (rsub)
				{
					case 1: // Cadastrar Pacote
						op = 'S';
						while (op == 'S')
						{
							cadastrar_Pacote(Pc, Atv, &op, TLPC, TLAT, &prxid_pc);
							if (op == 'S') TLPC++;
						}
						break;

					case 2: // Consultar Pacote
						op = 'S';
						while (op == 'S')
						{
							consultar_Pacote(Pc, &op, TLPC, &quer_cadastrar);
							if (quer_cadastrar)
							{
								op = 'S';
								while (op == 'S')
								{
									cadastrar_Pacote(Pc, Atv, &op, TLPC, TLAT, &prxid_pc);
									if (op == 'S') TLPC++;
								}
								break;
							}
						}
						break;

					case 3: // Excluir Pacote
						op = 'S';
						while (op == 'S')
						{
							excluir_Pacote(Pc, &op, &TLPC);
						}
						break;

					default:
						break;    
				}
				break;
			
			// Gerenciar Planos
			case 4:
				rsub = menu_Planos();
				
				switch (rsub)
				{
					case 1: // Cadastrar Plano
						op = 'S';
						while (op == 'S')
						{
							cadastrar_Plano(Pl, &op, TLPL, &prxid_pl);
							if (op == 'S') TLPL++;
						}
						break;

					case 2: // Consultar Plano
						op = 'S';
						while (op == 'S')
						{
							consultar_Plano(Pl, &op, TLPL, &quer_cadastrar);
							if (quer_cadastrar)
							{
								op = 'S';
								while (op == 'S')
								{
									cadastrar_Plano(Pl, &op, TLPL, &prxid_pl);
									if (op == 'S') TLPL++;
								}
								break;
							}
						}
						break;

					case 3: // Excluir Plano
						op = 'S';
						while (op == 'S')
						{
							excluir_Plano(Pl, &op, &TLPL);
						}
						break;

					default:
						break;
				}
				break;
			
			// Movimentacoes
			case 5:
				rsub = menu_Movimentacoes();
				
				switch (rsub)
				{
					case 1: // Vincular Plano ao Aluno
						vincular_Plano_Aluno(Al, Pl, TLA, TLPL);
						break;

					case 2: // Vincular Pacote ao Aluno
						vincular_Pacote_Aluno(Al, Pc, TLA, TLPC);
						break;

					default:
						break;
				}
				break;
			
			default:
				break;
		}
		rop = menu();	
	}

	return 0;
}
