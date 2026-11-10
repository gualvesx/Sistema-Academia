#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>

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
    arqInstrutor = fopen("aluno.bin", "rb");
    
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
            printf("** ERRO: CPF ja cadastrado! **\n");
        } 
        else {
            strcpy(Al.cpf, temp_cpf);

            printf("Insira o nome completo: ");
            fflush(stdin);
            fgets(Al.nome,sizeof(Al.nome),stdin);

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

        printf("Deseja cadastrar outro aluno? (S/N): ");
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
            printf("** ERRO: CPF ja cadastrado! **\n");
        } 
        else {
            strcpy(Inst.cpf, temp_cpf);

            printf("Insira o nome completo: ");
            fflush(stdin);
            fgets(Inst.nome,sizeof(Inst.nome),stdin);

            printf("Insira a especialidade: ");
            fflush(stdin);
            fgets(Inst.especialidade,sizeof(Inst.especialidade),stdin); 

            fwrite(&Inst, sizeof(Instrutor), 1, arqInstrutor);

            printf("\n** Instrutor cadastrado com sucesso! **\n");
        }

        fclose(arqInstrutor); 

        printf("Deseja cadastrar outro instrutor? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}
//<=====CONSULTAS=====>
void consultarAluno() 
{
    int temp_cpf;
    do 
	{
        system("cls");
        printf("\n--- CONSULTAR ALUNO ---");
        printf("\Insira o CPF: ");

        
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
            case 1: while (cadastrarAluno() == 'S'); break;
            case 2: while (cadastrarInstrutor() == 'S'); break;
            case 3: menuConsultarPessoas(); break;
            /*
            case 4: excluirPessoa(Al, TLA, Inst, TLINST, Atv, TLAT, Rec, TLREC); break;
            case 0: break;
            */
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
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
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}



main()
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
		opcaoPrincipal=lerInteiro();
		
		switch (opcaoPrincipal) 
		{
            case 1:
            	//Fazendo
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
}
