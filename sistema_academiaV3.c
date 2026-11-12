#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<string.h>

//<=============STRUCTS=============>

typedef struct {
    char cpf[15];
    char nome[100];
    char telefone[20];
    int id_pacote;
    int id_plano;
    int status_matricula;
} Aluno;

typedef struct {
    char cpf[15];
    char nome[100];
    char especialidade[50];
} Instrutor;

typedef struct {
    int id;
    char nome[50];
    char cpf_instrutor[15];
} Atividade;

typedef struct {
    int id;
    char nome[50];
    int ids_atividades[10];
    int qtd_atividades;
} Pacote;

typedef struct {
    int id;
    char nome[50];
    char tipo;
    float valor_base;
} Plano;

typedef struct {
    int id_recebimento;
    char cpf_aluno[15];
    int mes_referencia;
    float valor_cobrado;
    int status_pago;
} Recebimento;

//<=============FUNCOES=============>

//<=====VALIDACOES=====>
int lerInteiro()
{
	int valor;
	while(scanf("%d",&valor)!=1)
	{
		printf("** ENTRADA INVALIDA! Por favor, digite um numero: ");
        fflush(stdin);
	}
	
	fflush(stdin);
    return valor;
}

void lerCPF(char cpf[]) {
    int valido, i, tamanho;
    do {
        valido = 1;
        fflush(stdin);
        scanf("%14s", cpf);
      
        cpf[14] = '\0';

        tamanho = strlen(cpf);
        if (tamanho != 11) {
            valido = 0;
        } else {
            i = 0;
            while (cpf[i] != '\0' && valido == 1) {
                if (!isdigit(cpf[i])) {
                    valido = 0;
                }
                i++;
            }
        }

        if (!valido) {
            printf("** CPF INVALIDO! Digite exatamente 11 numeros: ");
        }
    } while (!valido);
}

char lerOpcaoSN() {
    char op;
    do {
        fflush(stdin);
        if (scanf("%c", &op) != 1) {
            op = 'X';
        }
        op = toupper(op);
        if (op != 'S' && op != 'N') {
            printf("** OPCAO INVALIDA! Digite 'S' para Sim ou 'N' para Nao: ");
        }
    } while (op != 'S' && op != 'N');
    return op;
}

//<=====BUSCAS=====>
int buscaAluno(char cpf[]) {
    Aluno Al;
    FILE *arqAluno;
    arqAluno = fopen("aluno.bin", "rb");
    
    if (arqAluno == NULL) return -1; 

    int achei = -1;
    int pos = 0;
    
    while (fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
        if (strcmp(cpf, Al.cpf) == 0) {
            achei = pos; 
            break;
        }
        pos++;
    }

    fclose(arqAluno);
    return achei;
}

int buscaInstrutor(char cpf[]) {
    Instrutor Inst;
    FILE *arqInstrutor;
    arqInstrutor = fopen("instrutor.bin", "rb");
    
    if (arqInstrutor == NULL) return -1;

    int achei = -1;
    int pos = 0;
    
    while (fread(&Inst, sizeof(Instrutor), 1, arqInstrutor) == 1) {
        if (strcmp(cpf, Inst.cpf) == 0) {
            achei = pos; 
            break;
        }
        pos++;
    }

    fclose(arqInstrutor);
    return achei;
}

//<=====ORDENAÇÃO=====>
void ordenarAluno()
{
	FILE *arqAluno;
	Aluno Al, Ali;
	int qtde=0, i;
	arqAluno = fopen("aluno.bin", "rb+");
	if(arqAluno == NULL)
		printf("\n** Erro no arquivo **\n");
	else
	{
		fseek(arqAluno, 0, 2);
		qtde = ftell(arqAluno) / sizeof(Aluno);
		while(qtde > 1)
		{
			for(i = 0; i < qtde - 1; i++)
			{
				fseek(arqAluno, i * sizeof(Aluno), 0);
				fread(&Al, sizeof(Aluno), 1, arqAluno);
				fseek(arqAluno, (i + 1) * sizeof(Aluno), 0);
				fread(&Ali, sizeof(Aluno), 1, arqAluno);
				if(strcmp(Al.nome, Ali.nome) > 0)
				{
					fseek(arqAluno, i * sizeof(Aluno), 0);
					fwrite(&Ali, sizeof(Aluno), 1, arqAluno);
					fseek(arqAluno, (i + 1) * sizeof(Aluno), 0);
					fwrite(&Al, sizeof(Aluno), 1, arqAluno);
				}
			}
			qtde--;
		}
		fclose(arqAluno);
		printf("\n** Arquivo de Aluno ordenado com sucesso! **\n");
	}
	system("pause");
	system("cls");		
}

void ordenarInstrutor()
{
	FILE *arqInstrutor;
	Instrutor Inst, Insti;
	int qtde=0, i;
	arqInstrutor = fopen("instrutor.bin", "rb+");
	if(arqInstrutor == NULL)
		printf("\n** Erro no arquivo **\n");
	else
	{
		fseek(arqInstrutor, 0, 2);
		qtde = ftell(arqInstrutor) / sizeof(Instrutor);
		while(qtde > 1)
		{
			for(i = 0; i < qtde - 1; i++)
			{
				fseek(arqInstrutor, i * sizeof(Instrutor), 0);
				fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
				fseek(arqInstrutor, (i + 1) * sizeof(Instrutor), 0);
				fread(&Insti, sizeof(Instrutor), 1, arqInstrutor);
				if(strcmp(Inst.nome, Insti.nome) > 0)
				{
					fseek(arqInstrutor, i * sizeof(Instrutor), 0);
					fwrite(&Insti, sizeof(Instrutor), 1, arqInstrutor);
					fseek(arqInstrutor, (i + 1) * sizeof(Instrutor), 0);
					fwrite(&Inst, sizeof(Instrutor), 1, arqInstrutor);
				}
			}
			qtde--;
		}
		fclose(arqInstrutor);
		printf("\n** Arquivo de Instrutor ordenado com sucesso! **\n");
	}
	system("pause");
	system("cls");		
}

//<=====MENU=====>
int menuPrincipal()
{
	system("cls");
    printf("\n==========================================");
    printf("\n   SISTEMA DE GESTAO DA ACADEMIA");
    printf("\n==========================================");
    printf("\n1. Gerenciar Pessoas");
    printf("\n2. Gerenciar Atividades");
    printf("\n3. Gerenciar Pacotes");
    printf("\n4. Gerenciar Planos");
    printf("\n5. Movimentacoes e Financeiro");
    printf("\n0. Sair");
    printf("\nOpcao: ");
    return 0;
}

//<=====CADASTROS=====>
char cadastrarAluno() {
    Aluno Al;
    FILE *arqAluno;
    arqAluno = fopen("aluno.bin", "ab");
    
    char temp_cpf[20];
    int idx;

    system("cls");
    if (arqAluno != NULL) {
        printf("\n<==== CADASTRO DE ALUNO ====>\n");
        printf("Insira o CPF (apenas numeros): ");
        lerCPF(temp_cpf);

        idx = buscaAluno(temp_cpf);
        if (idx != -1) { 
            printf("\n** ERRO: CPF ja cadastrado! **\n");
        } 
        else {
            strcpy(Al.cpf, temp_cpf);

            printf("Insira o nome completo: ");
            fflush(stdin);
            fgets(Al.nome, sizeof(Al.nome), stdin);
            Al.nome[strcspn(Al.nome, "\n")] = '\0';

            printf("Insira o telefone: ");
            fflush(stdin);
            scanf("%19s", Al.telefone);

            printf("Insira o id do pacote: ");
            scanf("%d", &Al.id_pacote);
            
            printf("Insira o id do plano: ");
            scanf("%d", &Al.id_plano);

            Al.status_matricula = 0;

            fwrite(&Al, sizeof(Aluno), 1, arqAluno);

            printf("\n** Aluno cadastrado com sucesso! **\n");
        }

        fclose(arqAluno); 

        printf("\nDeseja cadastrar outro aluno? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarInstrutor() {
    Instrutor Inst;
    FILE *arqInstrutor;
    arqInstrutor = fopen("instrutor.bin", "ab"); 
    
    char temp_cpf[20];
    int idx;

    system("cls");
    if (arqInstrutor != NULL) {
        printf("\n<==== CADASTRO DE INSTRUTOR ====>\n");
        printf("Insira o CPF (apenas numeros): ");
        lerCPF(temp_cpf);

        idx = buscaInstrutor(temp_cpf);
        if (idx != -1) { 
            printf("\n** ERRO: CPF ja cadastrado! **\n");
        } 
        else {
            strcpy(Inst.cpf, temp_cpf);

            printf("Insira o nome completo: ");
            fflush(stdin);
            fgets(Inst.nome, sizeof(Inst.nome), stdin);
            Inst.nome[strcspn(Inst.nome, "\n")] = '\0';

            printf("Insira a especialidade: ");
            fflush(stdin);
            fgets(Inst.especialidade, sizeof(Inst.especialidade), stdin);
            Inst.especialidade[strcspn(Inst.especialidade, "\n")] = '\0';

            fwrite(&Inst, sizeof(Instrutor), 1, arqInstrutor);

            printf("\n** Instrutor cadastrado com sucesso! **\n");
        }

        fclose(arqInstrutor); 

        printf("\nDeseja cadastrar outro instrutor? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

//<=====CONSULTAS=====>
char consultarAluno() 
{
    char temp_cpf[20];
    Aluno Al;
    FILE *arqAluno;

    system("cls");
    printf("\n--- CONSULTAR ALUNO ---");
    printf("\nInsira o CPF: ");
    lerCPF(temp_cpf);

    int pos = buscaAluno(temp_cpf);
    if (pos != -1) {
        arqAluno = fopen("aluno.bin", "rb");
        if (arqAluno != NULL) {
            fseek(arqAluno, pos * sizeof(Aluno), 0);
            fread(&Al, sizeof(Aluno), 1, arqAluno);
            fclose(arqAluno);

            printf("\n** Aluno encontrado! **\n");
            printf("Nome: %s\n", Al.nome);
            printf("CPF: %s\n", Al.cpf);
            printf("Telefone: %s\n", Al.telefone);
            printf("ID Pacote: %d\n", Al.id_pacote);
            printf("ID Plano: %d\n", Al.id_plano);
            printf("Status Matricula: %d\n", Al.status_matricula);
        }
    } else {
        printf("\n** ERRO: Aluno nao encontrado! **\n");
    }

    printf("\nDeseja consultar outro aluno? (S/N): ");
    return lerOpcaoSN();
}

char consultarInstrutor() 
{
    char temp_cpf[20];
    Instrutor Inst;
    FILE *arqInstrutor;

    system("cls");
    printf("\n--- CONSULTAR INSTRUTOR ---");
    printf("\nInsira o CPF: ");
    lerCPF(temp_cpf);

    int pos = buscaInstrutor(temp_cpf);
    if (pos != -1) {
        arqInstrutor = fopen("instrutor.bin", "rb");
        if (arqInstrutor != NULL) {
            fseek(arqInstrutor, pos * sizeof(Instrutor), 0);
            fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
            fclose(arqInstrutor);

            printf("\n** Instrutor encontrado! **\n");
            printf("Nome: %s\n", Inst.nome);
            printf("CPF: %s\n", Inst.cpf);
            printf("Especialidade: %s\n", Inst.especialidade);
        }
    } else {
        printf("\n** ERRO: Instrutor nao encontrado! **\n");
    }

    printf("\nDeseja consultar outro instrutor? (S/N): ");
    return lerOpcaoSN();
}

void consultarPessoas() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- CONSULTAR PESSOAS ---");
        printf("\n1. Aluno");
        printf("\n2. Instrutor");
        printf("\n0. Voltar");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (consultarAluno() == 'S'); break;
            case 2: while (consultarInstrutor() == 'S'); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

//<=====SUB-MENUS=====>
void gerenciarPessoas(Aluno Al, Instrutor Inst, Atividade Atv, Recebimento Rec) 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- GERENCIAR PESSOAS ---");
        printf("\n1. Cadastrar Aluno");
        printf("\n2. Cadastrar Instrutor");
        printf("\n3. Consultar Pessoas");
        printf("\n4. Excluir Pessoa");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: 
                while (cadastrarAluno() == 'S'); 
                ordenarAluno(); 
                break;
            case 2: 
                while (cadastrarInstrutor() == 'S'); 
                ordenarInstrutor(); 
                break;
            case 3: 
                consultarPessoas(); 
                break;
            /*
            case 4: excluirPessoa(Al, TLA, Inst, TLINST, Atv, TLAT, Rec, TLREC); break;
            case 0: break;
            */
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

int main()
{
	//<===ARQUIVOS===>
	FILE *arqAluno, *arqInstrutor, *arqAtividade, *arqPacote, *arqPlano, *arqRecebimento;
	
	//<===STRUCTS===>
	Aluno Al;
    Instrutor Inst;
    Atividade Atv;
    Pacote Pc;
    Plano Pl;
    Recebimento Rec;
    
    //<===SISTEMA===>
    int opcaoPrincipal;
	
	do
	{
		menuPrincipal();
		opcaoPrincipal = lerInteiro();
		
		switch (opcaoPrincipal) 
		{
            case 1:
                gerenciarPessoas(Al, Inst, Atv, Rec);
                break;
                /*Falta arrumar daqui pra baixo
            case 2:
                gerenciarAtividades(Atv, &TLAT, Inst, TLINST, &prxid_atv, Pc, TLPC);
                break;
            case 3:
                gerenciarPacotes(Pc, &TLPC, Atv, TLAT, &prxid_pc, Al, TLA);
                break;
            case 4:
                gerenciarPlanos(Pl, &TLPL, &prxid_pl, Al, TLA);
                break;
            case 5:
                gerenciarMovimentacoes(Al, TLA, Pl, TLPL, Pc, TLPC, Rec, &TLREC, &prxid_rec);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
                */
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
        }
        
    } while (opcaoPrincipal != 0);

    return 0;
}
