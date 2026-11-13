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
}

float lerFloat() {
    float valor;
    while (scanf("%f", &valor) != 1) {
        printf("** ENTRADA INVALIDA! Por favor, digite um valor numerico: ");
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
    FILE *arqAluno = fopen("aluno.bin", "rb");
    
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
    FILE *arqInstrutor = fopen("instrutor.bin", "rb");
    
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

int buscaAtividade(int id) {
    Atividade Atv;
    FILE *arqAtividade = fopen("atividade.bin", "rb");
    
    if (arqAtividade == NULL) return -1;

    int achei = -1;
    int pos = 0;
    
    while (fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
        if (Atv.id == id) {
            achei = pos; 
            break;
        }
        pos++;
    }

    fclose(arqAtividade);
    return achei;
}

int buscaPacote(int id) {
    Pacote Pc;
    FILE *arqPacote = fopen("pacote.bin", "rb");
    
    if (arqPacote == NULL) return -1;

    int achei = -1;
    int pos = 0;
    
    while (fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
        if (Pc.id == id) {
            achei = pos; 
            break;
        }
        pos++;
    }

    fclose(arqPacote);
    return achei;
}

int buscaPlano(int id) {
    Plano Pl;
    FILE *arqPlano = fopen("plano.bin", "rb");
    
    if (arqPlano == NULL) return -1;

    int achei = -1;
    int pos = 0;
    
    while (fread(&Pl, sizeof(Plano), 1, arqPlano) == 1) {
        if (Pl.id == id) {
            achei = pos; 
            break;
        }
        pos++;
    }

    fclose(arqPlano);
    return achei;
}

//<=====ORDENAÇÃO=====>
void ordenarAluno()
{
	FILE *arqAluno = fopen("aluno.bin", "rb+");
	Aluno Al, Ali;
	int qtde=0, i;
	if(arqAluno == NULL) return;
	
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
}

void ordenarInstrutor()
{
	FILE *arqInstrutor = fopen("instrutor.bin", "rb+");
	Instrutor Inst, Insti;
	int qtde=0, i;
	if(arqInstrutor == NULL) return;
	
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
}

void ordenarAtividade()
{
	FILE *arqAtividade = fopen("atividade.bin", "rb+");
	Atividade Atv, Atvi;
	int qtde=0, i;
	if(arqAtividade == NULL) return;
	
	fseek(arqAtividade, 0, 2);
	qtde = ftell(arqAtividade) / sizeof(Atividade);
	while(qtde > 1)
	{
		for(i = 0; i < qtde - 1; i++)
		{
			fseek(arqAtividade, i * sizeof(Atividade), 0);
			fread(&Atv, sizeof(Atividade), 1, arqAtividade);
			fseek(arqAtividade, (i + 1) * sizeof(Atividade), 0);
			fread(&Atvi, sizeof(Atividade), 1, arqAtividade);
			if(strcmp(Atv.nome, Atvi.nome) > 0)
			{
				fseek(arqAtividade, i * sizeof(Atividade), 0);
				fwrite(&Atvi, sizeof(Atividade), 1, arqAtividade);
				fseek(arqAtividade, (i + 1) * sizeof(Atividade), 0);
				fwrite(&Atv, sizeof(Atividade), 1, arqAtividade);
			}
		}
		qtde--;
	}
	fclose(arqAtividade);
}

void ordenarPacote()
{
	FILE *arqPacote = fopen("pacote.bin", "rb+");
	Pacote Pc, Pci;
	int qtde=0, i;
	if(arqPacote == NULL) return;
	
	fseek(arqPacote, 0, 2);
	qtde = ftell(arqPacote) / sizeof(Pacote);
	while(qtde > 1)
	{
		for(i = 0; i < qtde - 1; i++)
		{
			fseek(arqPacote, i * sizeof(Pacote), 0);
			fread(&Pc, sizeof(Pacote), 1, arqPacote);
			fseek(arqPacote, (i + 1) * sizeof(Pacote), 0);
			fread(&Pci, sizeof(Pacote), 1, arqPacote);
			if(strcmp(Pc.nome, Pci.nome) > 0)
			{
				fseek(arqPacote, i * sizeof(Pacote), 0);
				fwrite(&Pci, sizeof(Pacote), 1, arqPacote);
				fseek(arqPacote, (i + 1) * sizeof(Pacote), 0);
				fwrite(&Pc, sizeof(Pacote), 1, arqPacote);
			}
		}
		qtde--;
	}
	fclose(arqPacote);
}

void ordenarPlano()
{
	FILE *arqPlano = fopen("plano.bin", "rb+");
	Plano Pl, Pli;
	int qtde=0, i;
	if(arqPlano == NULL) return;
	
	fseek(arqPlano, 0, 2);
	qtde = ftell(arqPlano) / sizeof(Plano);
	while(qtde > 1)
	{
		for(i = 0; i < qtde - 1; i++)
		{
			fseek(arqPlano, i * sizeof(Plano), 0);
			fread(&Pl, sizeof(Plano), 1, arqPlano);
			fseek(arqPlano, (i + 1) * sizeof(Plano), 0);
			fread(&Pli, sizeof(Plano), 1, arqPlano);
			if(strcmp(Pl.nome, Pli.nome) > 0)
			{
				fseek(arqPlano, i * sizeof(Plano), 0);
				fwrite(&Pli, sizeof(Plano), 1, arqPlano);
				fseek(arqPlano, (i + 1) * sizeof(Plano), 0);
				fwrite(&Pl, sizeof(Plano), 1, arqPlano);
			}
		}
		qtde--;
	}
	fclose(arqPlano);
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

//<=====SELEÇÃO / BUSCA INTERATIVA=====>
int selecionarAluno() {
    FILE *arqAluno = fopen("aluno.bin", "rb");
    Aluno Al;
    int opSub, i, idx = -1, qtde = 0;

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
    FILE *arqInstrutor = fopen("instrutor.bin", "rb");
    Instrutor Inst;
    int opSub, i, idx = -1, qtde = 0;

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

int selecionarAtividade() {
    FILE *arqAtividade = fopen("atividade.bin", "rb");
    Atividade Atv;
    int opSub, i, idx = -1, qtde = 0, id;

    if (arqAtividade == NULL) {
        printf("\n** Nenhuma atividade cadastrada! **\n");
        system("pause");
        return -1;
    }

    fseek(arqAtividade, 0, 2);
    qtde = ftell(arqAtividade) / sizeof(Atividade);
    fclose(arqAtividade);

    if (qtde == 0) {
        printf("\n** Nenhuma atividade cadastrada! **\n");
        system("pause");
        return -1;
    }

    while (1) {
        system("cls");
        printf("\n--- SELECIONAR ATIVIDADE ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todas as atividades (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            return -1;
        } else if (opSub == 1) {
            printf("ID da Atividade: ");
            id = lerInteiro();
            idx = buscaAtividade(id);
            if (idx == -1) {
                printf("\n** Atividade nao encontrada! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            arqAtividade = fopen("atividade.bin", "rb");
            if (arqAtividade != NULL) {
                printf("\n<=== LISTA DE ATIVIDADES ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Atv, sizeof(Atividade), 1, arqAtividade);
                    printf("[%d] ID: %d | Nome: %s | CPF Instrutor: %s\n",
                           i, Atv.id, Atv.nome, Atv.cpf_instrutor);
                }
                fclose(arqAtividade);
                printf("----------------------------\n");
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

int selecionarPacote() {
    FILE *arqPacote = fopen("pacote.bin", "rb");
    Pacote Pc;
    int opSub, i, j, idx = -1, qtde = 0, id;

    if (arqPacote == NULL) {
        printf("\n** Nenhum pacote cadastrado! **\n");
        system("pause");
        return -1;
    }

    fseek(arqPacote, 0, 2);
    qtde = ftell(arqPacote) / sizeof(Pacote);
    fclose(arqPacote);

    if (qtde == 0) {
        printf("\n** Nenhum pacote cadastrado! **\n");
        system("pause");
        return -1;
    }

    while (1) {
        system("cls");
        printf("\n--- SELECIONAR PACOTE ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todos os pacotes (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            return -1;
        } else if (opSub == 1) {
            printf("ID do Pacote: ");
            id = lerInteiro();
            idx = buscaPacote(id);
            if (idx == -1) {
                printf("\n** Pacote nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            arqPacote = fopen("pacote.bin", "rb");
            if (arqPacote != NULL) {
                printf("\n<=== LISTA DE PACOTES ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Pc, sizeof(Pacote), 1, arqPacote);
                    printf("[%d] ID: %d | Nome: %s | Atividades: ",
                           i, Pc.id, Pc.nome);
                    for (j = 0; j < Pc.qtd_atividades; j++) {
                        printf("[%d] ", Pc.ids_atividades[j]);
                    }
                    printf("\n");
                }
                fclose(arqPacote);
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

int selecionarPlano() {
    FILE *arqPlano = fopen("plano.bin", "rb");
    Plano Pl;
    int opSub, i, idx = -1, qtde = 0, id;

    if (arqPlano == NULL) {
        printf("\n** Nenhum plano cadastrado! **\n");
        system("pause");
        return -1;
    }

    fseek(arqPlano, 0, 2);
    qtde = ftell(arqPlano) / sizeof(Plano);
    fclose(arqPlano);

    if (qtde == 0) {
        printf("\n** Nenhum plano cadastrado! **\n");
        system("pause");
        return -1;
    }

    while (1) {
        system("cls");
        printf("\n--- SELECIONAR PLANO ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todos os planos (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            return -1;
        } else if (opSub == 1) {
            printf("ID do Plano: ");
            id = lerInteiro();
            idx = buscaPlano(id);
            if (idx == -1) {
                printf("\n** Plano nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            arqPlano = fopen("plano.bin", "rb");
            if (arqPlano != NULL) {
                printf("\n<=== LISTA DE PLANOS ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Pl, sizeof(Plano), 1, arqPlano);
                    printf("[%d] ID: %d | Nome: %s | Tipo: %c | Valor: R$ %.2f\n",
                           i, Pl.id, Pl.nome, Pl.tipo, Pl.valor_base);
                }
                fclose(arqPlano);
                printf("------------------------\n");
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

//<=====CADASTROS=====>
char cadastrarAluno() {
    Aluno Al;
    FILE *arqAluno = fopen("aluno.bin", "ab");
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

            Al.id_pacote = -1;
            Al.id_plano = -1;
            Al.status_matricula = 0;

            fwrite(&Al, sizeof(Aluno), 1, arqAluno);
            printf("\n** Aluno cadastrado com sucesso! **\n");
        }

        fclose(arqAluno); 
        ordenarAluno();

        printf("\nDeseja cadastrar outro aluno? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarInstrutor() {
    Instrutor Inst;
    FILE *arqInstrutor = fopen("instrutor.bin", "ab"); 
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
        ordenarInstrutor();

        printf("\nDeseja cadastrar outro instrutor? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarAtividade() {
    Atividade Atv;
    FILE *arqAtividade = fopen("atividade.bin", "rb");
    int proximo_id = 1, idxInst;

    if (arqAtividade != NULL) {
        fseek(arqAtividade, 0, 2);
        proximo_id = (ftell(arqAtividade) / sizeof(Atividade)) + 1;
        fclose(arqAtividade);
    }

    arqAtividade = fopen("atividade.bin", "ab");
    system("cls");
    if (arqAtividade != NULL) {
        printf("\n<==== CADASTRO DE ATIVIDADE ====>\n");
        Atv.id = proximo_id;

        lerTextoApenasLetras("Insira o nome da Atividade: ", Atv.nome, sizeof(Atv.nome));

        idxInst = selecionarInstrutor();
        if (idxInst == -1) {
            fclose(arqAtividade);
            printf("\n** Cadastro de atividade cancelado por falta de instrutor. **\n");
            system("pause");
            return 'N';
        }

        FILE *arqInstrutor = fopen("instrutor.bin", "rb");
        Instrutor tempInst;
        fseek(arqInstrutor, idxInst * sizeof(Instrutor), 0);
        fread(&tempInst, sizeof(Instrutor), 1, arqInstrutor);
        fclose(arqInstrutor);
        strcpy(Atv.cpf_instrutor, tempInst.cpf);

        fwrite(&Atv, sizeof(Atividade), 1, arqAtividade);
        fclose(arqAtividade);
        ordenarAtividade();
        printf("\n** Atividade cadastrada com sucesso! **\n");

        printf("Deseja cadastrar outra atividade? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarPacote() {
    Pacote Pc;
    FILE *arqPacote = fopen("pacote.bin", "rb");
    int proximo_id = 1, idxAtiv, jaExiste, k;
    char continuar = 'S';

    if (arqPacote != NULL) {
        fseek(arqPacote, 0, 2);
        proximo_id = (ftell(arqPacote) / sizeof(Pacote)) + 1;
        fclose(arqPacote);
    }

    arqPacote = fopen("pacote.bin", "ab");
    system("cls");
    if (arqPacote != NULL) {
        printf("\n<==== CADASTRO DE PACOTE ====>\n");
        Pc.id = proximo_id;
        Pc.qtd_atividades = 0;

        lerTextoApenasLetras("Insira o nome do Pacote: ", Pc.nome, sizeof(Pc.nome));

        while (continuar == 'S' && Pc.qtd_atividades < 10) {
            idxAtiv = selecionarAtividade();
            if (idxAtiv == -1) {
                break;
            }

            Atividade Atv;
            FILE *arqAtividade = fopen("atividade.bin", "rb");
            fseek(arqAtividade, idxAtiv * sizeof(Atividade), 0);
            fread(&Atv, sizeof(Atividade), 1, arqAtividade);
            fclose(arqAtividade);

            jaExiste = 0;
            for (k = 0; k < Pc.qtd_atividades; k++) {
                if (Pc.ids_atividades[k] == Atv.id) jaExiste = 1;
            }
            if (jaExiste) {
                printf("** AVISO: Atividade ja esta neste pacote! **\n");
                system("pause");
            } else {
                Pc.ids_atividades[Pc.qtd_atividades] = Atv.id;
                Pc.qtd_atividades++;
                printf("** Atividade associada ao pacote! **\n");
                system("pause");
            }

            if (Pc.qtd_atividades < 10) {
                printf("Deseja incluir mais uma atividade neste pacote? (S/N): ");
                continuar = lerOpcaoSN();
            }
        }

        fwrite(&Pc, sizeof(Pacote), 1, arqPacote);
        fclose(arqPacote);
        ordenarPacote();
        printf("\n** Pacote cadastrado com sucesso! **\n");

        printf("\nDeseja cadastrar outro pacote? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarPlano() {
    Plano Pl;
    FILE *arqPlano = fopen("plano.bin", "rb");
    int proximo_id = 1;
    char tipo;

    if (arqPlano != NULL) {
        fseek(arqPlano, 0, 2);
        proximo_id = (ftell(arqPlano) / sizeof(Plano)) + 1;
        fclose(arqPlano);
    }

    arqPlano = fopen("plano.bin", "ab");
    system("cls");
    if (arqPlano != NULL) {
        printf("\n<==== CADASTRO DE PLANO ====>\n");
        Pl.id = proximo_id;

        lerTextoApenasLetras("Insira o nome do Plano: ", Pl.nome, sizeof(Pl.nome));

        do {
            printf("Tipo [M-Mensal, T-Trimestral, S-Semestral, A-Anual]: ");
            fflush(stdin);
            scanf("%c", &tipo);
            Pl.tipo = toupper(tipo);
            if (Pl.tipo != 'M' && Pl.tipo != 'T' && Pl.tipo != 'S' && Pl.tipo != 'A') {
                printf("** TIPO INVALIDO! Tente novamente. **\n");
            }
        } while (Pl.tipo != 'M' && Pl.tipo != 'T' && Pl.tipo != 'S' && Pl.tipo != 'A');

        printf("Insira o valor base (R$): ");
        Pl.valor_base = lerFloat();
        while (Pl.valor_base <= 0) {
            printf("** VALOR INVALIDO! Digite um valor positivo: ");
            Pl.valor_base = lerFloat();
        }

        fwrite(&Pl, sizeof(Plano), 1, arqPlano);
        fclose(arqPlano);
        ordenarPlano();
        printf("\n** Plano cadastrado com sucesso! **\n");

        printf("\nDeseja cadastrar outro plano? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

//<=====CONSULTAS=====>
void consultarAluno() 
{
    Aluno Al;
    int pos = selecionarAluno();
    if (pos != -1) {
        FILE *arqAluno = fopen("aluno.bin", "rb");
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
            printf("Status Matricula: %s\n", Al.status_matricula ? "Ativa" : "Inativa");
            system("pause");
        }
    }
}

void consultarInstrutor() 
{
    Instrutor Inst;
    int pos = selecionarInstrutor();
    if (pos != -1) {
        FILE *arqInstrutor = fopen("instrutor.bin", "rb");
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

void consultarAtividade() 
{
    Atividade Atv;
    int pos = selecionarAtividade();
    if (pos != -1) {
        FILE *arqAtividade = fopen("atividade.bin", "rb");
        if (arqAtividade != NULL) {
            fseek(arqAtividade, pos * sizeof(Atividade), 0);
            fread(&Atv, sizeof(Atividade), 1, arqAtividade);
            fclose(arqAtividade);

            system("cls");
            printf("\n** Atividade encontrada! **\n");
            printf("ID: %d\n", Atv.id);
            printf("Nome: %s\n", Atv.nome);
            printf("CPF Instrutor: %s\n", Atv.cpf_instrutor);
            system("pause");
        }
    }
}

void consultarPacote() 
{
    Pacote Pc;
    int pos = selecionarPacote();
    if (pos != -1) {
        FILE *arqPacote = fopen("pacote.bin", "rb");
        if (arqPacote != NULL) {
            fseek(arqPacote, pos * sizeof(Pacote), 0);
            fread(&Pc, sizeof(Pacote), 1, arqPacote);
            fclose(arqPacote);

            system("cls");
            printf("\n** Pacote encontrado! **\n");
            printf("ID: %d\n", Pc.id);
            printf("Nome: %s\n", Pc.nome);
            printf("Atividades: ");
            for (int j = 0; j < Pc.qtd_atividades; j++) {
                printf("[%d] ", Pc.ids_atividades[j]);
            }
            printf("\n");
            system("pause");
        }
    }
}

void consultarPlano() 
{
    Plano Pl;
    int pos = selecionarPlano();
    if (pos != -1) {
        FILE *arqPlano = fopen("plano.bin", "rb");
        if (arqPlano != NULL) {
            fseek(arqPlano, pos * sizeof(Plano), 0);
            fread(&Pl, sizeof(Plano), 1, arqPlano);
            fclose(arqPlano);

            system("cls");
            printf("\n** Plano encontrado! **\n");
            printf("ID: %d\n", Pl.id);
            printf("Nome: %s\n", Pl.nome);
            printf("Tipo: %c\n", Pl.tipo);
            printf("Valor Base: R$ %.2f\n", Pl.valor_base);
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

//<=====ALTERAÇÕES=====>
void alterarAluno() {
    int pos = selecionarAluno();
    if (pos == -1) return;

    FILE *arqAluno = fopen("aluno.bin", "rb+");
    if (arqAluno == NULL) {
        printf("\n** Erro ao abrir arquivo de alunos! **\n");
        system("pause");
        return;
    }

    Aluno Al;
    fseek(arqAluno, pos * sizeof(Aluno), SEEK_SET);
    fread(&Al, sizeof(Aluno), 1, arqAluno);

    system("cls");
    printf("\n--- ALTERAR DADOS DO ALUNO ---");
    printf("\nNome atual: %s", Al.nome);
    lerTextoApenasLetras("\nNovo nome completo: ", Al.nome, sizeof(Al.nome));

    printf("Novo telefone: ");
    fflush(stdin);
    scanf("%19s", Al.telefone);

    fseek(arqAluno, pos * sizeof(Aluno), SEEK_SET);
    fwrite(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    ordenarAluno();
    printf("\n** Aluno alterado com sucesso! **\n");
    system("pause");
}

void alterarInstrutor() {
    int pos = selecionarInstrutor();
    if (pos == -1) return;

    FILE *arqInstrutor = fopen("instrutor.bin", "rb+");
    if (arqInstrutor == NULL) {
        printf("\n** Erro ao abrir arquivo de instrutores! **\n");
        system("pause");
        return;
    }

    Instrutor Inst;
    fseek(arqInstrutor, pos * sizeof(Instrutor), SEEK_SET);
    fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);

    system("cls");
    printf("\n--- ALTERAR DADOS DO INSTRUTOR ---");
    printf("\nNome atual: %s", Inst.nome);
    lerTextoApenasLetras("\nNovo nome completo: ", Inst.nome, sizeof(Inst.nome));
    lerTextoApenasLetras("Nova especialidade: ", Inst.especialidade, sizeof(Inst.especialidade));

    fseek(arqInstrutor, pos * sizeof(Instrutor), SEEK_SET);
    fwrite(&Inst, sizeof(Instrutor), 1, arqInstrutor);
    fclose(arqInstrutor);

    ordenarInstrutor();
    printf("\n** Instrutor alterado com sucesso! **\n");
    system("pause");
}

void alterarAtividade() {
    int pos = selecionarAtividade();
    if (pos == -1) return;

    FILE *arqAtividade = fopen("atividade.bin", "rb+");
    if (arqAtividade == NULL) {
        printf("\n** Erro ao abrir arquivo de atividades! **\n");
        system("pause");
        return;
    }

    Atividade Atv;
    fseek(arqAtividade, pos * sizeof(Atividade), SEEK_SET);
    fread(&Atv, sizeof(Atividade), 1, arqAtividade);

    system("cls");
    printf("\n--- ALTERAR DADOS DA ATIVIDADE ---");
    printf("\nNome atual: %s", Atv.nome);
    lerTextoApenasLetras("\nNovo nome da Atividade: ", Atv.nome, sizeof(Atv.nome));

    int idxInst = selecionarInstrutor();
    if (idxInst != -1) {
        FILE *arqInst = fopen("instrutor.bin", "rb");
        Instrutor tempInst;
        fseek(arqInst, idxInst * sizeof(Instrutor), SEEK_SET);
        fread(&tempInst, sizeof(Instrutor), 1, arqInst);
        fclose(arqInst);
        strcpy(Atv.cpf_instrutor, tempInst.cpf);
    }

    fseek(arqAtividade, pos * sizeof(Atividade), SEEK_SET);
    fwrite(&Atv, sizeof(Atividade), 1, arqAtividade);
    fclose(arqAtividade);

    ordenarAtividade();
    printf("\n** Atividade alterada com sucesso! **\n");
    system("pause");
}

void alterarPacote() {
    int pos = selecionarPacote();
    if (pos == -1) return;

    FILE *arqPacote = fopen("pacote.bin", "rb+");
    if (arqPacote == NULL) {
        printf("\n** Erro ao abrir arquivo de pacotes! **\n");
        system("pause");
        return;
    }

    Pacote Pc;
    fseek(arqPacote, pos * sizeof(Pacote), SEEK_SET);
    fread(&Pc, sizeof(Pacote), 1, arqPacote);

    system("cls");
    printf("\n--- ALTERAR DADOS DO PACOTE ---");
    printf("\nNome atual: %s", Pc.nome);
    lerTextoApenasLetras("\nNovo nome do Pacote: ", Pc.nome, sizeof(Pc.nome));

    printf("\nDeseja reconfigurar as atividades deste pacote? (S/N): ");
    if (lerOpcaoSN() == 'S') {
        Pc.qtd_atividades = 0;
        char continuar = 'S';
        int idxAtiv, jaExiste, k;

        while (continuar == 'S' && Pc.qtd_atividades < 10) {
            idxAtiv = selecionarAtividade();
            if (idxAtiv == -1) break;

            Atividade Atv;
            FILE *fAtv = fopen("atividade.bin", "rb");
            fseek(fAtv, idxAtiv * sizeof(Atividade), SEEK_SET);
            fread(&Atv, sizeof(Atividade), 1, fAtv);
            fclose(fAtv);

            jaExiste = 0;
            for (k = 0; k < Pc.qtd_atividades; k++) {
                if (Pc.ids_atividades[k] == Atv.id) jaExiste = 1;
            }
            if (jaExiste) {
                printf("** AVISO: Atividade ja esta neste pacote! **\n");
                system("pause");
            } else {
                Pc.ids_atividades[Pc.qtd_atividades] = Atv.id;
                Pc.qtd_atividades++;
                printf("** Atividade associada ao pacote! **\n");
                system("pause");
            }

            if (Pc.qtd_atividades < 10) {
                printf("Deseja incluir mais uma atividade? (S/N): ");
                continuar = lerOpcaoSN();
            }
        }
    }

    fseek(arqPacote, pos * sizeof(Pacote), SEEK_SET);
    fwrite(&Pc, sizeof(Pacote), 1, arqPacote);
    fclose(arqPacote);

    ordenarPacote();
    printf("\n** Pacote alterado com sucesso! **\n");
    system("pause");
}

void alterarPlano() {
    int pos = selecionarPlano();
    if (pos == -1) return;

    FILE *arqPlano = fopen("plano.bin", "rb+");
    if (arqPlano == NULL) {
        printf("\n** Erro ao abrir arquivo de planos! **\n");
        system("pause");
        return;
    }

    Plano Pl;
    fseek(arqPlano, pos * sizeof(Plano), SEEK_SET);
    fread(&Pl, sizeof(Plano), 1, arqPlano);

    system("cls");
    printf("\n--- ALTERAR DADOS DO PLANO ---");
    printf("\nNome atual: %s", Pl.nome);
    lerTextoApenasLetras("\nNovo nome do Plano: ", Pl.nome, sizeof(Pl.nome));

    char tipo;
    do {
        printf("Novo tipo [M-Mensal, T-Trimestral, S-Semestral, A-Anual]: ");
        fflush(stdin);
        scanf("%c", &tipo);
        Pl.tipo = toupper(tipo);
        if (Pl.tipo != 'M' && Pl.tipo != 'T' && Pl.tipo != 'S' && Pl.tipo != 'A') {
            printf("** TIPO INVALIDO! Tente novamente. **\n");
        }
    } while (Pl.tipo != 'M' && Pl.tipo != 'T' && Pl.tipo != 'S' && Pl.tipo != 'A');

    printf("Novo valor base (R$): ");
    Pl.valor_base = lerFloat();
    while (Pl.valor_base <= 0) {
        printf("** VALOR INVALIDO! Digite um valor positivo: ");
        Pl.valor_base = lerFloat();
    }

    fseek(arqPlano, pos * sizeof(Plano), SEEK_SET);
    fwrite(&Pl, sizeof(Plano), 1, arqPlano);
    fclose(arqPlano);

    ordenarPlano();
    printf("\n** Plano alterado com sucesso! **\n");
    system("pause");
}

void alterarPessoa() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- ALTERAR PESSOA ---");
        printf("\n1. Aluno");
        printf("\n2. Instrutor");
        printf("\n0. Voltar");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: alterarAluno(); break;
            case 2: alterarInstrutor(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

//<=====EXCLUSÕES=====>
void excluirAluno() {
    FILE *arqAluno, *arqTemp;
    Aluno Al;
    int pos, temMatriculaAtiva = 0, temBoletos = 0;

    pos = selecionarAluno();
    if (pos == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    fseek(arqAluno, pos * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    if (Al.status_matricula == 1) {
        temMatriculaAtiva = 1;
    }

    FILE *arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento != NULL) {
        Recebimento Rec;
        while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
            if (strcmp(Rec.cpf_aluno, Al.cpf) == 0) {
                temBoletos = 1;
                break;
            }
        }
        fclose(arqRecebimento);
    }

    if (temMatriculaAtiva || temBoletos) {
        printf("\n**************************************************");
        printf("\n**          AVISO DE PENDENCIAS DO ALUNO        **");
        printf("\n**************************************************");
        if (temMatriculaAtiva) {
            printf("\n- Aluno possui MATRICULA ATIVA no sistema!");
        }
        if (temBoletos) {
            printf("\n- Aluno possui BOLETOS / RECEBIMENTOS registrados!");
        }
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir este aluno mesmo com essas pendencias? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- EXCLUIR ALUNO ---");
    printf("\nNome: %s", Al.nome);
    printf("\nCPF: %s", Al.cpf);
    printf("\nTelefone: %s", Al.telefone);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");
    
    if (lerOpcaoSN() == 'S') {
        char cpfExcluir[15];
        strcpy(cpfExcluir, Al.cpf);

        arqAluno = fopen("aluno.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");
        
        if (arqAluno != NULL && arqTemp != NULL) {
            while (fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
                if (strcmp(Al.cpf, cpfExcluir) != 0) {
                    fwrite(&Al, sizeof(Aluno), 1, arqTemp);
                }
            }
            fclose(arqTemp);
            fclose(arqAluno);
            remove("aluno.bin");
            rename("auxiliar.bin", "aluno.bin");
            ordenarAluno();
            printf("\n** O aluno foi excluido com sucesso! **\n");
        } else {
            if (arqAluno) fclose(arqAluno);
            if (arqTemp) fclose(arqTemp);
            printf("\n** Erro ao manipular os arquivos! **\n");
        }
    }
    system("pause");
}

void excluirInstrutor() {
    FILE *arqInstrutor, *arqTemp;
    Instrutor Inst;
    int pos, atividadesVinculadas = 0;

    pos = selecionarInstrutor();
    if (pos == -1) return;

    arqInstrutor = fopen("instrutor.bin", "rb");
    fseek(arqInstrutor, pos * sizeof(Instrutor), 0);
    fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
    fclose(arqInstrutor);

    FILE *arqAtividade = fopen("atividade.bin", "rb");
    if (arqAtividade != NULL) {
        Atividade Atv;
        while (fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
            if (strcmp(Atv.cpf_instrutor, Inst.cpf) == 0) {
                atividadesVinculadas = 1;
                break;
            }
        }
        fclose(arqAtividade);
    }

    if (atividadesVinculadas) {
        printf("\n**************************************************");
        printf("\n**        AVISO DE VINCULOS DO INSTRUTOR        **");
        printf("\n**************************************************");
        printf("\n- O instrutor possui ATIVIDADES VINCULADAS a ele!");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir mesmo com essas atividades? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- EXCLUIR INSTRUTOR ---");
    printf("\nNome: %s", Inst.nome);
    printf("\nCPF: %s", Inst.cpf);
    printf("\nEspecialidade: %s", Inst.especialidade);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");
    
    if (lerOpcaoSN() == 'S') {
        char cpfExcluir[15];
        strcpy(cpfExcluir, Inst.cpf);

        arqInstrutor = fopen("instrutor.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");
        
        if (arqInstrutor != NULL && arqTemp != NULL) {
            while (fread(&Inst, sizeof(Instrutor), 1, arqInstrutor) == 1) {
                if (strcmp(Inst.cpf, cpfExcluir) != 0) {
                    fwrite(&Inst, sizeof(Instrutor), 1, arqTemp);
                }
            }
            fclose(arqTemp);
            fclose(arqInstrutor);
            remove("instrutor.bin");
            rename("auxiliar.bin", "instrutor.bin");
            ordenarInstrutor();
            printf("\n** O instrutor foi excluido com sucesso! **\n");
        } else {
            if (arqInstrutor) fclose(arqInstrutor);
            if (arqTemp) fclose(arqTemp);
            printf("\n** Erro ao manipular os arquivos! **\n");
        }
    }
    system("pause");
}

void excluirAtividade() {
    FILE *arqAtividade, *arqTemp;
    Atividade Atv;
    int pos, pacotesVinculados = 0;

    pos = selecionarAtividade();
    if (pos == -1) return;

    arqAtividade = fopen("atividade.bin", "rb");
    fseek(arqAtividade, pos * sizeof(Atividade), 0);
    fread(&Atv, sizeof(Atividade), 1, arqAtividade);
    fclose(arqAtividade);

    FILE *arqPacote = fopen("pacote.bin", "rb");
    if (arqPacote != NULL) {
        Pacote Pc;
        while (fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
            for (int j = 0; j < Pc.qtd_atividades; j++) {
                if (Pc.ids_atividades[j] == Atv.id) {
                    pacotesVinculados = 1;
                    break;
                }
            }
            if (pacotesVinculados) break;
        }
        fclose(arqPacote);
    }

    if (pacotesVinculados) {
        printf("\n**************************************************");
        printf("\n**         AVISO DE VINCULOS DA ATIVIDADE       **");
        printf("\n**************************************************");
        printf("\n- A atividade esta associada a um ou mais PACOTES!");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir mesmo assim? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- EXCLUIR ATIVIDADE ---");
    printf("\nID: %d", Atv.id);
    printf("\nNome: %s", Atv.nome);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");

    if (lerOpcaoSN() == 'S') {
        int idExcluir = Atv.id;
        arqAtividade = fopen("atividade.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");

        if (arqAtividade != NULL && arqTemp != NULL) {
            while (fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
                if (Atv.id != idExcluir) {
                    fwrite(&Atv, sizeof(Atividade), 1, arqTemp);
                }
            }
            fclose(arqTemp);
            fclose(arqAtividade);
            remove("atividade.bin");
            rename("auxiliar.bin", "atividade.bin");
            ordenarAtividade();
            printf("\n** A atividade foi excluida com sucesso! **\n");
        }
    }
    system("pause");
}

void excluirPacote() {
    FILE *arqPacote, *arqTemp;
    Pacote Pc;
    int pos, alunosAtivosVinculados = 0;

    pos = selecionarPacote();
    if (pos == -1) return;

    arqPacote = fopen("pacote.bin", "rb");
    fseek(arqPacote, pos * sizeof(Pacote), 0);
    fread(&Pc, sizeof(Pacote), 1, arqPacote);
    fclose(arqPacote);

    FILE *arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno != NULL) {
        Aluno Al;
        while (fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
            if (Al.id_pacote == Pc.id && Al.status_matricula == 1) {
                alunosAtivosVinculados = 1;
                break;
            }
        }
        fclose(arqAluno);
    }

    if (alunosAtivosVinculados) {
        printf("\n**************************************************");
        printf("\n**          AVISO DE VINCULOS DO PACOTE         **");
        printf("\n**************************************************");
        printf("\n- O pacote esta vinculado a ALUNOS COM MATRICULA ATIVA!");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir mesmo assim? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- EXCLUIR PACOTE ---");
    printf("\nID: %d", Pc.id);
    printf("\nNome: %s", Pc.nome);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");

    if (lerOpcaoSN() == 'S') {
        int idExcluir = Pc.id;
        arqPacote = fopen("pacote.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");

        if (arqPacote != NULL && arqTemp != NULL) {
            while (fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
                if (Pc.id != idExcluir) {
                    fwrite(&Pc, sizeof(Pacote), 1, arqTemp);
                }
            }
            fclose(arqTemp);
            fclose(arqPacote);
            remove("pacote.bin");
            rename("auxiliar.bin", "pacote.bin");
            ordenarPacote();
            printf("\n** O pacote foi excluido com sucesso! **\n");
        }
    }
    system("pause");
}

void excluirPlano() {
    FILE *arqPlano, *arqTemp;
    Plano Pl;
    int pos, alunosAtivosVinculados = 0;

    pos = selecionarPlano();
    if (pos == -1) return;

    arqPlano = fopen("plano.bin", "rb");
    fseek(arqPlano, pos * sizeof(Plano), 0);
    fread(&Pl, sizeof(Plano), 1, arqPlano);
    fclose(arqPlano);

    FILE *arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno != NULL) {
        Aluno Al;
        while (fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
            if (Al.id_plano == Pl.id && Al.status_matricula == 1) {
                alunosAtivosVinculados = 1;
                break;
            }
        }
        fclose(arqAluno);
    }

    if (alunosAtivosVinculados) {
        printf("\n**************************************************");
        printf("\n**          AVISO DE VINCULOS DO PLANO          **");
        printf("\n**************************************************");
        printf("\n- O plano esta vinculado a ALUNOS COM MATRICULA ATIVA!");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir mesmo assim? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- EXCLUIR PLANO ---");
    printf("\nID: %d", Pl.id);
    printf("\nNome: %s", Pl.nome);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");

    if (lerOpcaoSN() == 'S') {
        int idExcluir = Pl.id;
        arqPlano = fopen("plano.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");

        if (arqPlano != NULL && arqTemp != NULL) {
            while (fread(&Pl, sizeof(Plano), 1, arqPlano) == 1) {
                if (Pl.id != idExcluir) {
                    fwrite(&Pl, sizeof(Plano), 1, arqTemp);
                }
            }
            fclose(arqTemp);
            fclose(arqPlano);
            remove("plano.bin");
            rename("auxiliar.bin", "plano.bin");
            ordenarPlano();
            printf("\n** O plano foi excluido com sucesso! **\n");
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
            case 1: excluirAluno(); break;
            case 2: excluirInstrutor(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

//<=====REGRAS FINANCEIRAS E MOVIMENTAÇÕES=====>
float calcularDescontoPlano(float valorBase, char tipoPlano) {
    float desconto = 0.0;
    if (tipoPlano == 'T') desconto = valorBase * 0.05f;
    else if (tipoPlano == 'S') desconto = valorBase * 0.10f;
    else if (tipoPlano == 'A') desconto = valorBase * 0.15f;
    return valorBase - desconto;
}

int existeBoleto(char cpf[], int mes) {
    Recebimento Rec;
    FILE *arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento == NULL) return 0;
    while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
        if (strcmp(Rec.cpf_aluno, cpf) == 0 && Rec.mes_referencia == mes) {
            fclose(arqRecebimento);
            return 1;
        }
    }
    fclose(arqRecebimento);
    return 0;
}

void gerarProximoBoleto(char cpf[], int proximoMes, float valor) {
    Recebimento Rec;
    FILE *arqRecebimento;
    int proximo_id = 1;

    if (existeBoleto(cpf, proximoMes)) {
        printf("\n[AVISO] Ja existe boleto para o mes %d. Nao foi gerado duplicado.\n", proximoMes);
        return;
    }

    arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento != NULL) {
        fseek(arqRecebimento, 0, 2);
        proximo_id = (ftell(arqRecebimento) / sizeof(Recebimento)) + 1;
        fclose(arqRecebimento);
    }

    arqRecebimento = fopen("recebimento.bin", "ab");
    if (arqRecebimento != NULL) {
        Rec.id_recebimento = proximo_id;
        strcpy(Rec.cpf_aluno, cpf);
        Rec.mes_referencia = proximoMes;
        Rec.valor_cobrado = valor;
        Rec.status_pago = 0;
        fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
        fclose(arqRecebimento);
        printf("\n[BOLETO GERADO] Novo boleto para o mes %d no valor de R$ %.2f\n", proximoMes, valor);
    }
}

void efetuarMatricula() {
    int idxAluno, idxPlano, idxPacote, mesInicio;
    float valorFinal;
    Aluno Al;
    Plano Pl;
    Pacote Pc;
    FILE *arqAluno, *arqPlano, *arqPacote;

    system("cls");
    printf("\n<==== EFETUAR MATRICULA ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    if (Al.status_matricula == 1) {
        printf("\n** ERRO: Aluno ja possui matricula ATIVA! **\n");
        system("pause");
        return;
    }

    idxPlano = selecionarPlano();
    if (idxPlano == -1) return;

    arqPlano = fopen("plano.bin", "rb");
    fseek(arqPlano, idxPlano * sizeof(Plano), 0);
    fread(&Pl, sizeof(Plano), 1, arqPlano);
    fclose(arqPlano);

    idxPacote = selecionarPacote();
    if (idxPacote == -1) return;

    arqPacote = fopen("pacote.bin", "rb");
    fseek(arqPacote, idxPacote * sizeof(Pacote), 0);
    fread(&Pc, sizeof(Pacote), 1, arqPacote);
    fclose(arqPacote);

    printf("Mes inicial da cobranca (1-12): ");
    do {
        mesInicio = lerInteiro();
        if (mesInicio < 1 || mesInicio > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mesInicio < 1 || mesInicio > 12);

    valorFinal = calcularDescontoPlano(Pl.valor_base, Pl.tipo);

    Al.id_plano = Pl.id;
    Al.id_pacote = Pc.id;
    Al.status_matricula = 1;

    arqAluno = fopen("aluno.bin", "rb+");
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fwrite(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    printf("\n[MATRICULA REGISTRADA]");
    printf("\nAluno: %s", Al.nome);
    printf("\nPlano: %s | Valor Real Final: R$ %.2f\n", Pl.nome, valorFinal);

    gerarProximoBoleto(Al.cpf, mesInicio, valorFinal);
    system("pause");
}

void efetuarCancelamento() {
    int idxAluno, idxPlano;
    float valor, multa, reembolso;
    Aluno Al;
    Plano Pl;
    FILE *arqAluno, *arqPlano;

    system("cls");
    printf("\n<==== CANCELAMENTO DE MATRICULA ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    if (Al.status_matricula == 0) {
        printf("\n** ERRO: Aluno nao possui matricula ativa! **\n");
        system("pause");
        return;
    }

    idxPlano = buscaPlano(Al.id_plano);
    if (idxPlano == -1) {
        printf("\n** AVISO: Plano vinculado nao existe mais. Cancelamento sera aplicado sem calculo de multa. **\n");
    } else {
        arqPlano = fopen("plano.bin", "rb");
        fseek(arqPlano, idxPlano * sizeof(Plano), 0);
        fread(&Pl, sizeof(Plano), 1, arqPlano);
        fclose(arqPlano);

        valor = Pl.valor_base;
        if (Pl.tipo != 'M') {
            multa = valor * 0.30f;
            reembolso = valor * 0.70f;
            printf("\nMulta de Retencao (30%%): R$ %.2f", multa);
            printf("\nValor Reembolsado ao Aluno (70%%): R$ %.2f\n", reembolso);
        } else {
            printf("\nPlano Mensal cancelado sem taxas adicionais.\n");
        }
    }

    Al.status_matricula = 0;
    Al.id_plano = -1;
    Al.id_pacote = -1;

    arqAluno = fopen("aluno.bin", "rb+");
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fwrite(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    printf("\n** Matricula cancelada com sucesso! **\n");
    system("pause");
}

void efetuarRecebimento() {
    int idxAluno, mes, achou = 0;
    Aluno Al;
    Recebimento Rec;
    FILE *arqAluno, *arqRecebimento;

    system("cls");
    printf("\n<==== REGISTRAR RECEBIMENTO ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    printf("Mes do Boleto (1-12): ");
    do {
        mes = lerInteiro();
        if (mes < 1 || mes > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mes < 1 || mes > 12);

    arqRecebimento = fopen("recebimento.bin", "rb+");
    if (arqRecebimento != NULL) {
        long pos = 0;
        while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
            if (strcmp(Rec.cpf_aluno, Al.cpf) == 0 && Rec.mes_referencia == mes) {
                achou = 1;
                if (Rec.status_pago == 1) {
                    printf("\n** Boleto ja pago anteriormente! **\n");
                } else {
                    Rec.status_pago = 1;
                    fseek(arqRecebimento, pos, 0);
                    fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
                    printf("\n** Boleto #%d Pago com sucesso! Valor: R$ %.2f **\n", Rec.id_recebimento, Rec.valor_cobrado);
                    if (mes < 12) {
                        gerarProximoBoleto(Al.cpf, mes + 1, Rec.valor_cobrado);
                    } else {
                        printf("\n[INFO] Mes 12 pago. Proximo boleto devera ser gerado no proximo ano.\n");
                    }
                }
                break;
            }
            pos = ftell(arqRecebimento);
        }
        fclose(arqRecebimento);
    }

    if (!achou) printf("\n** Nenhum boleto pendente localizado para este CPF e mes. **\n");
    system("pause");
}

//<=====SUB-MENUS=====>
void gerenciarPessoas() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- GERENCIAR PESSOAS ---");
        printf("\n1. Cadastrar Aluno");
        printf("\n2. Cadastrar Instrutor");
        printf("\n3. Consultar Pessoas");
        printf("\n4. Alterar Pessoa");
        printf("\n5. Excluir Pessoa");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: 
                while (cadastrarAluno() == 'S'); 
                break;
            case 2: 
                while (cadastrarInstrutor() == 'S'); 
                break;
            case 3: 
                consultarPessoas(); 
                break;
            case 4: 
                alterarPessoa(); 
                break;
            case 5: 
                excluirPessoa(); 
                break;
            case 0: 
                break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarAtividades() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- GERENCIAR ATIVIDADES ---");
        printf("\n1. Cadastrar Atividade");
        printf("\n2. Consultar Atividades");
        printf("\n3. Alterar Atividade");
        printf("\n4. Excluir Atividade");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: 
                while (cadastrarAtividade() == 'S'); 
                break;
            case 2: 
                consultarAtividade(); 
                break;
            case 3: 
                alterarAtividade(); 
                break;
            case 4: 
                excluirAtividade(); 
                break;
            case 0: 
                break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarPacotes() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- GERENCIAR PACOTES ---");
        printf("\n1. Cadastrar Pacote");
        printf("\n2. Consultar Pacotes");
        printf("\n3. Alterar Pacote");
        printf("\n4. Excluir Pacote");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: 
                while (cadastrarPacote() == 'S'); 
                break;
            case 2: 
                consultarPacote(); 
                break;
            case 3: 
                alterarPacote(); 
                break;
            case 4: 
                excluirPacote(); 
                break;
            case 0: 
                break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarPlanos() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- GERENCIAR PLANOS ---");
        printf("\n1. Cadastrar Plano");
        printf("\n2. Consultar Planos");
        printf("\n3. Alterar Plano");
        printf("\n4. Excluir Plano");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: 
                while (cadastrarPlano() == 'S'); 
                break;
            case 2: 
                consultarPlano(); 
                break;
            case 3: 
                alterarPlano(); 
                break;
            case 4: 
                excluirPlano(); 
                break;
            case 0: 
                break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarMovimentacoes() 
{
    int op;
    do 
	{
        system("cls");
        printf("\n--- MOVIMENTACOES E FINANCEIRO ---");
        printf("\n1. Efetuar Matricula");
        printf("\n2. Efetuar Cancelamento");
        printf("\n3. Registrar Recebimento");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: efetuarMatricula(); break;
            case 2: efetuarCancelamento(); break;
            case 3: efetuarRecebimento(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

int main()
{
	FILE *arqAluno, *arqInstrutor, *arqAtividade, *arqPacote, *arqPlano, *arqRecebimento;
	
	Aluno Al;
    Instrutor Inst;
    Atividade Atv;
    Pacote Pc;
    Plano Pl;
    Recebimento Rec;
    
    int opcaoPrincipal;
	
	do
	{
		menuPrincipal();
		opcaoPrincipal = lerInteiro();
		
		switch (opcaoPrincipal) 
		{
            case 1:
                gerenciarPessoas();
                break;
            case 2:
                gerenciarAtividades();
                break;
            case 3:
                gerenciarPacotes();
                break;
            case 4:
                gerenciarPlanos();
                break;
            case 5:
                gerenciarMovimentacoes();
                break;
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
