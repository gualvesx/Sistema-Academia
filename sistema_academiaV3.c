#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

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
    
int lerFloat()
{
	int valor;
	while(scanf("%f",&valor)!=1)
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

void lerTextoApenasLetras(char mensagem[], char texto[], int tamanhoMax) {
    int valido, i, tamanho;
    do {
        valido = 1;
        printf("%s", mensagem);
        fflush(stdin);
        fgets(texto, tamanhoMax, stdin);
        texto[strcspn(texto, "\n")] = '\0';

        tamanho = strlen(texto);
        if (tamanho == 0) {
            valido = 0;
        } else {
            for (i = 0; i < tamanho; i++) {
                if (!isalpha(texto[i]) && texto[i] != ' ' && texto[i] != 'ç' && texto[i] != 'Ç' && 
                    texto[i] != 'á' && texto[i] != 'é' && texto[i] != 'í' && texto[i] != 'ó' && texto[i] != 'ú' &&
                    texto[i] != 'à' && texto[i] != 'è' && texto[i] != 'ì' && texto[i] != 'ò' && texto[i] != 'ù' &&
                    texto[i] != 'ã' && texto[i] != 'õ' && texto[i] != 'â' && texto[i] != 'ê' && texto[i] != 'ô') {
                    valido = 0;
                    break;
                }
            }
        }

        if (!valido) {
            printf("** ENTRADA INVALIDA! Digite apenas letras: ");
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

            lerTextoApenasLetras("Insira o nome completo: ", Al.nome, sizeof(Al.nome));

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

            lerTextoApenasLetras("Insira o nome completo: ", Inst.nome, sizeof(Inst.nome));

            lerTextoApenasLetras("Insira a especialidade: ", Inst.especialidade, sizeof(Inst.especialidade));

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

//<=====SELEÇÃO / BUSCA INTERATIVA=====>
int selecionarAluno() {
    FILE *arqAluno;
    Aluno Al;
    int opSub, i, idx = -1, qtde = 0;

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) {
        printf("\n** Nenhum aluno cadastrado! **\n");
        system("pause");
        return -1;
    }

    fseek(arqAluno, 0, 2);
    qtde = ftell(arqAluno) / sizeof(Aluno);
    fclose(arqAluno);

    if (qtde == 0) {
        printf("\n** Nenhum aluno cadastrado! **\n");
        system("pause");
        return -1;
    }

    while (1) {
        system("cls");
        printf("\n--- SELECIONAR ALUNO ---");
        printf("\n1. Digitar CPF diretamente");
        printf("\n2. Listar todos os alunos (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            return -1;
        } else if (opSub == 1) {
            char cpf[20];
            printf("CPF do Aluno (apenas numeros): ");
            lerCPF(cpf);
            idx = buscaAluno(cpf);
            if (idx == -1) {
                printf("\n** Aluno nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            arqAluno = fopen("aluno.bin", "rb");
            if (arqAluno != NULL) {
                printf("\n<=== LISTA DE ALUNOS ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Al, sizeof(Aluno), 1, arqAluno);
                    printf("[%d] Nome: %s | CPF: %s | Status: %s\n",
                           i, Al.nome, Al.cpf,
                           Al.status_matricula ? "Ativa" : "Inativa");
                }
                fclose(arqAluno);
                printf("-------------------------\n");
                printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
                idx = lerInteiro();
                if (idx == -1) {
                    return -1;
                } else if (idx >= 0 && idx < qtde) {
                    return idx;
                } else {
                    printf("\n** Indice invalido! **\n");
                    system("pause");
                }
            }
        } else {
            printf("\n** Opcao invalida! **\n");
            system("pause");
        }
    }
}

int selecionarInstrutor() {
    FILE *arqInstrutor;
    Instrutor Inst;
    int opSub, i, idx = -1, qtde = 0;

    arqInstrutor = fopen("instrutor.bin", "rb");
    if (arqInstrutor == NULL) {
        printf("\n** Nenhum instrutor cadastrado! **\n");
        system("pause");
        return -1;
    }

    fseek(arqInstrutor, 0, 2);
    qtde = ftell(arqInstrutor) / sizeof(Instrutor);
    fclose(arqInstrutor);

    if (qtde == 0) {
        printf("\n** Nenhum instrutor cadastrado! **\n");
        system("pause");
        return -1;
    }

    while (1) {
        system("cls");
        printf("\n--- SELECIONAR INSTRUTOR ---");
        printf("\n1. Digitar CPF diretamente");
        printf("\n2. Listar todos os instrutores (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            return -1;
        } else if (opSub == 1) {
            char cpf[20];
            printf("CPF do Instrutor (apenas numeros): ");
            lerCPF(cpf);
            idx = buscaInstrutor(cpf);
            if (idx == -1) {
                printf("\n** Instrutor nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            arqInstrutor = fopen("instrutor.bin", "rb");
            if (arqInstrutor != NULL) {
                printf("\n<=== LISTA DE INSTRUTORES ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
                    printf("[%d] Nome: %s | CPF: %s | Especialidade: %s\n",
                           i, Inst.nome, Inst.cpf, Inst.especialidade);
                }
                fclose(arqInstrutor);
                printf("-----------------------------\n");
                printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
                idx = lerInteiro();
                if (idx == -1) {
                    return -1;
                } else if (idx >= 0 && idx < qtde) {
                    return idx;
                } else {
                    printf("\n** Indice invalido! **\n");
                    system("pause");
                }
            }
        } else {
            printf("\n** Opcao invalida! **\n");
            system("pause");
        }
    }
}

//<=====CONSULTAS=====>
void consultarAluno() 
{
    Aluno Al;
    FILE *arqAluno;

    int pos = selecionarAluno();
    if (pos != -1) {
        arqAluno = fopen("aluno.bin", "rb");
        if (arqAluno != NULL) {
            fseek(arqAluno, pos * sizeof(Aluno), 0);
            fread(&Al, sizeof(Aluno), 1, arqAluno);
            fclose(arqAluno);

            system("cls");
            printf("\n** Aluno encontrado! **\n");
            printf("Nome: %s\n", Al.nome);
            printf("CPF: %s\n", Al.cpf);
            printf("Telefone: %s\n", Al.telefone);
            printf("ID Pacote: %d\n", Al.id_pacote);
            printf("ID Plano: %d\n", Al.id_plano);
            printf("Status Matricula: %d\n", Al.status_matricula);
            system("pause");
        }
    }
}

void consultarInstrutor() 
{
    Instrutor Inst;
    FILE *arqInstrutor;

    int pos = selecionarInstrutor();
    if (pos != -1) {
        arqInstrutor = fopen("instrutor.bin", "rb");
        if (arqInstrutor != NULL) {
            fseek(arqInstrutor, pos * sizeof(Instrutor), 0);
            fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
            fclose(arqInstrutor);

            system("cls");
            printf("\n** Instrutor encontrado! **\n");
            printf("Nome: %s\n", Inst.nome);
            printf("CPF: %s\n", Inst.cpf);
            printf("Especialidade: %s\n", Inst.especialidade);
            system("pause");
        }
    }
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
            case 1: consultarAluno(); break;
            case 2: consultarInstrutor(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

//<=====EXCLUSÕES=====>
void excluirAlunoReal() {
    FILE *arquivo, *temp;
    Aluno Al;
    int pos;

    pos = selecionarAluno();
    if (pos == -1) {
        return;
    }

    arquivo = fopen("aluno.bin", "rb");
    fseek(arquivo, pos * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);

    system("cls");
    printf("\n--- EXCLUIR ALUNO ---");
    printf("\nNome: %s", Al.nome);
    printf("\nCPF: %s", Al.cpf);
    printf("\nTelefone: %s", Al.telefone);
    printf("\n-------------------");
    printf("\nDeseja realmente excluir? (S/N): ");
    
    if (lerOpcaoSN() == 'S') {
        char cpfExcluir[15];
        strcpy(cpfExcluir, Al.cpf);

        arquivo = fopen("aluno.bin", "rb");
        temp = fopen("auxiliar.bin", "wb");
        
        if (arquivo != NULL && temp != NULL) {
            while (fread(&Al, sizeof(Aluno), 1, arquivo) == 1) {
                if (strcmp(Al.cpf, cpfExcluir) != 0) {
                    fwrite(&Al, sizeof(Aluno), 1, temp);
                }
            }
            fclose(temp);
            fclose(arquivo);
            remove("aluno.bin");
            rename("auxiliar.bin", "aluno.bin");
            printf("\n** O aluno foi excluido com sucesso! **\n");
        } else {
            if (arquivo) fclose(arquivo);
            if (temp) fclose(temp);
            printf("\n** Erro ao manipular os arquivos! **\n");
        }
    }
    system("pause");
}

void excluirInstrutor() {
    FILE *arquivo, *temp;
    Instrutor Inst;
    int pos;

    pos = selecionarInstrutor();
    if (pos == -1) {
        return;
    }

    arquivo = fopen("instrutor.bin", "rb");
    fseek(arquivo, pos * sizeof(Instrutor), 0);
    fread(&Inst, sizeof(Instrutor), 1, arquivo);
    fclose(arquivo);

    system("cls");
    printf("\n--- EXCLUIR INSTRUTOR ---");
    printf("\nNome: %s", Inst.nome);
    printf("\nCPF: %s", Inst.cpf);
    printf("\nEspecialidade: %s", Inst.especialidade);
    printf("\n-------------------");
    printf("\nDeseja realmente excluir? (S/N): ");
    
    if (lerOpcaoSN() == 'S') {
        char cpfExcluir[15];
        strcpy(cpfExcluir, Inst.cpf);

        arquivo = fopen("instrutor.bin", "rb");
        temp = fopen("auxiliar.bin", "wb");
        
        if (arquivo != NULL && temp != NULL) {
            while (fread(&Inst, sizeof(Instrutor), 1, arquivo) == 1) {
                if (strcmp(Inst.cpf, cpfExcluir) != 0) {
                    fwrite(&Inst, sizeof(Instrutor), 1, temp);
                }
            }
            fclose(temp);
            fclose(arquivo);
            remove("instrutor.bin");
            rename("auxiliar.bin", "instrutor.bin");
            printf("\n** O instrutor foi excluido com sucesso! **\n");
        } else {
            if (arquivo) fclose(arquivo);
            if (temp) fclose(temp);
            printf("\n** Erro ao manipular os arquivos! **\n");
        }
    }
    system("pause");
}

void excluirPessoa() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- EXCLUIR PESSOA ---");
        printf("\n1. Aluno");
        printf("\n2. Instrutor");
        printf("\n0. Voltar");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: excluirAlunoReal(); break;
            case 2: excluirInstrutor(); break;
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
            case 4: 
                excluirPessoa(); 
                break;
            case 0: 
                break;
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
                */
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
                
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
        }
        
    } while (opcaoPrincipal != 0);

    return 0;
}
