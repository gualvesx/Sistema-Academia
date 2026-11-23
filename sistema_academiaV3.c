#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

/*
	EQUIPE:

	- GUSTAVO EMANUEL ALVES DA SILVA / RA: 10442613366
	- PEDRO HENRIQUE GOMES DA SILVA / RA: 10442613867
	- KAUENDERSON DE OLIVEIRA RODRIGUES / RA: 10442614800
	- JOÃO PEDRO CRUZ ROCHA / RA: 10442613956
	- JUAN ALEXANDRE JAQUES CARRASCO / RA: 10442614686
	- LUIZ HENRIQUE DAINEZ ALECRIM / RA: 10442614720

*/

//<=============STRUCTS=============>

typedef struct {
    char cpf[15];
    char nome[100];
    char telefone[20];
    char categoria_peso[30];
    char nivel_experiencia[30];
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
    char foco_treino[40];
    char cpf_instrutor[15];
} Atividade;

typedef struct {
    int id;
    char nome[50];
    int ids_atividades[10];
    int qtd_atividades;
    int qtd_aulas_mes;
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
    int ano_referencia;
    float valor_cobrado;
    int status_pago;
} Recebimento;

//<=============PROTÓTIPOS DE FUNÇÕES=============>
int lerInteiro();
float lerFloat();
void lerCPF(char cpf[]);
void lerTelefone(char telefone[]);
void lerTextoApenasLetras(char mensagem[], char texto[], int tamanhoMax);
char lerOpcaoSN();
float calcularDescontoPlano(char tipo, float valorBase);

int buscaAluno(char cpf[]);
int buscaInstrutor(char cpf[]);
int buscaAtividade(int id);
int buscaPacote(int id);
int buscaPlano(int id);

int proximoIdAtividade();
int proximoIdPacote();
int proximoIdPlano();
int proximoIdRecebimento();

void ordenarAluno();
void ordenarInstrutor();
void ordenarAtividade();
void ordenarPacote();
void ordenarPlano();

int selecionarAluno();
int selecionarInstrutor();
int selecionarAtividade();
int selecionarPacote();
int selecionarPlano();

void gerarProximoBoleto(char cpf[], int mes, int ano, float valor);
int existeBoleto(char cpf[], int mes, int ano);
void popularDadosIniciais();

void historicoPagamentosAluno();
void relatorioPagamentosPeriodo();
void relatorioAlunosPorStatus();
void relatorioInadimplentesMesAno();

//<=============FUNÇÕES DE VALIDAÇÃO E LEITURA=============>
int lerInteiro() {
    int valor;
    while (scanf("%d", &valor) != 1) {
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
    int vetCPF[11], mult, n_mult, soma, resto, sub, d1, d2, n_mult2, soma2;
    char s[2];
    int todosIguais;

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

        if (valido == 1) {
            todosIguais = 1;
            for (i = 0; i < 11; i++) {
                s[1] = '\0';
                s[0] = cpf[i];
                vetCPF[i] = atoi(s);
                if (i > 0 && vetCPF[i] != vetCPF[0]) {
                    todosIguais = 0;
                }
            }

            if (todosIguais == 1) {
                valido = 0;
            } else {
                n_mult = 10;
                soma = 0;
                for (i = 0; i < 9; i++) {
                    mult = vetCPF[i] * n_mult;
                    n_mult--;
                    soma = soma + mult;
                }
                resto = soma % 11;
                sub = 11 - resto;
                if (sub == 10 || sub == 11) {
                    d1 = 0;
                } else {
                    d1 = sub;
                }

                n_mult2 = 11;
                soma2 = 0;
                for (i = 0; i < 9; i++) {
                    mult = vetCPF[i] * n_mult2;
                    n_mult2--;
                    soma2 = soma2 + mult;
                }
                soma2 = soma2 + d1 * 2;
                resto = soma2 % 11;
                sub = 11 - resto;
                if (sub == 10 || sub == 11) {
                    d2 = 0;
                } else {
                    d2 = sub;
                }

                if (vetCPF[9] != d1 || vetCPF[10] != d2) {
                    valido = 0;
                }
            }
        }

        if (!valido) {
            printf("** CPF INVALIDO! Digite 11 numeros de um CPF valido: ");
        }
    } while (!valido);
}

void lerTelefone(char telefone[]) {
    int valido, i, tamanho;
    do {
        valido = 1;
        fflush(stdin);
        scanf("%19s", telefone);
        telefone[19] = '\0';

        tamanho = strlen(telefone);
        if (tamanho < 8 || tamanho > 15) {
            valido = 0;
        } else {
            i = 0;
            while (telefone[i] != '\0' && valido == 1) {
                if (!isdigit(telefone[i])) {
                    valido = 0;
                }
                i++;
            }
        }

        if (!valido) {
            printf("** TELEFONE INVALIDO! Digite apenas numeros: ");
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
            i = 0;
            while (i < tamanho && valido == 1) {
                if (!isalpha(texto[i]) && texto[i] != ' ' && texto[i] != '/' &&
                    texto[i] != 'ç' && texto[i] != 'Ç' &&
                    texto[i] != 'á' && texto[i] != 'é' && texto[i] != 'í' && texto[i] != 'ó' && texto[i] != 'ú' &&
                    texto[i] != 'à' && texto[i] != 'è' && texto[i] != 'ì' && texto[i] != 'ò' && texto[i] != 'ù' &&
                    texto[i] != 'ã' && texto[i] != 'õ' && texto[i] != 'â' && texto[i] != 'ê' && texto[i] != 'ô') {
                    valido = 0;
                }
                i++;
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

float calcularDescontoPlano(char tipo, float valorBase) {
    if (tipo == 'T') {
        return valorBase * 0.95f;
    } else if (tipo == 'S') {
        return valorBase * 0.90f;
    } else if (tipo == 'A') {
        return valorBase * 0.85f;
    }
    return valorBase;
}

//<=============MASSA DE DADOS INICIAL=============>
void popularDadosIniciais() {
    FILE *arqTeste = fopen("aluno.bin", "rb");
    if (arqTeste != NULL) {
        fclose(arqTeste);
        return;
    }

    FILE *arqInstrutor = fopen("instrutor.bin", "wb");
    if (arqInstrutor != NULL) {
        Instrutor i1 = {"52998224725", "Carlos Silva", "Boxe Olimpico e Tecnica"};
        Instrutor i2 = {"15350946056", "Roberto Mendes", "Sparring e Preparacao de Luta"};
        fwrite(&i1, sizeof(Instrutor), 1, arqInstrutor);
        fwrite(&i2, sizeof(Instrutor), 1, arqInstrutor);
        fclose(arqInstrutor);
    }

    FILE *arqAtividade = fopen("atividade.bin", "wb");
    if (arqAtividade != NULL) {
        Atividade a1 = {1, "Boxe Tecnico", "Tecnica e Movimentacao", "52998224725"};
        Atividade a2 = {2, "Sparring Controlado", "Sparring / Combate", "15350946056"};
        Atividade a3 = {3, "Preparacao Fisica", "Condicionamento/Saco", "52998224725"};
        fwrite(&a1, sizeof(Atividade), 1, arqAtividade);
        fwrite(&a2, sizeof(Atividade), 1, arqAtividade);
        fwrite(&a3, sizeof(Atividade), 1, arqAtividade);
        fclose(arqAtividade);
    }

    FILE *arqPacote = fopen("pacote.bin", "wb");
    if (arqPacote != NULL) {
        Pacote p1 = {1, "Boxe 3x Semana", {1, 3}, 2, 12};
        Pacote p2 = {2, "Full Boxer", {1, 2, 3}, 3, 24};
        fwrite(&p1, sizeof(Pacote), 1, arqPacote);
        fwrite(&p2, sizeof(Pacote), 1, arqPacote);
        fclose(arqPacote);
    }

    FILE *arqPlano = fopen("plano.bin", "wb");
    if (arqPlano != NULL) {
        Plano pl1 = {1, "Plano Mensal", 'M', 150.00f};
        Plano pl2 = {2, "Plano Trimestral", 'T', 150.00f};
        Plano pl3 = {3, "Plano Semestral", 'S', 150.00f};
        Plano pl4 = {4, "Plano Anual", 'A', 150.00f};
        fwrite(&pl1, sizeof(Plano), 1, arqPlano);
        fwrite(&pl2, sizeof(Plano), 1, arqPlano);
        fwrite(&pl3, sizeof(Plano), 1, arqPlano);
        fwrite(&pl4, sizeof(Plano), 1, arqPlano);
        fclose(arqPlano);
    }

    FILE *arqAluno = fopen("aluno.bin", "wb");
    if (arqAluno != NULL) {
        Aluno al1 = {"71428793860", "Lucas Oliveira", "18997711223", "Peso Medio", "Amador", 2, 3, 1};
        Aluno al2 = {"39053344705", "Mariana Costa", "18996655443", "Peso Leve", "Iniciante", 1, 1, 1};
        Aluno al3 = {"85620714004", "Rafael Santos", "18991122334", "Peso Pesado", "Competidor", -1, -1, 0};
        fwrite(&al1, sizeof(Aluno), 1, arqAluno);
        fwrite(&al2, sizeof(Aluno), 1, arqAluno);
        fwrite(&al3, sizeof(Aluno), 1, arqAluno);
        fclose(arqAluno);
    }

    FILE *arqRecebimento = fopen("recebimento.bin", "wb");
    if (arqRecebimento != NULL) {
        Recebimento r1 = {1, "71428793860", 11, 2026, 135.00f, 1};
        Recebimento r2 = {2, "71428793860", 5, 2027, 135.00f, 0};
        Recebimento r3 = {3, "39053344705", 11, 2026, 150.00f, 0};
        fwrite(&r1, sizeof(Recebimento), 1, arqRecebimento);
        fwrite(&r2, sizeof(Recebimento), 1, arqRecebimento);
        fwrite(&r3, sizeof(Recebimento), 1, arqRecebimento);
        fclose(arqRecebimento);
    }

    ordenarInstrutor();
    ordenarAtividade();
    ordenarPacote();
    ordenarPlano();
    ordenarAluno();
}

//<=============BUSCAS=============>
int buscaAluno(char cpf[]) {
    Aluno Al;
    FILE *arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) return -1;

    int achei = -1;
    int pos = 0;
    int val = 0;
    
    while (val == 0 && fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
        if (strcmp(cpf, Al.cpf) == 0) {
            achei = pos;
            val = 1;
        } else {
            pos++;
        }
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
    int val = 0;
    
    while (val == 0 && fread(&Inst, sizeof(Instrutor), 1, arqInstrutor) == 1) {
        if (strcmp(cpf, Inst.cpf) == 0) {
            achei = pos;
            val = 1;
        } else {
            pos++;
        }
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
    int val = 0;
    
    while (val == 0 && fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
        if (Atv.id == id) {
            achei = pos;
            val = 1;
        } else {
            pos++;
        }
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
    int val = 0;
    
    while (val == 0 && fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
        if (Pc.id == id) {
            achei = pos;
            val = 1;
        } else {
            pos++;
        }
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
    int val = 0;
    
    while (val == 0 && fread(&Pl, sizeof(Plano), 1, arqPlano) == 1) {
        if (Pl.id == id) {
            achei = pos;
            val = 1;
        } else {
            pos++;
        }
    }

    fclose(arqPlano);
    return achei;
}

//<=============GERADORES DE ID SEGUROS=============>
int proximoIdAtividade() {
    Atividade Atv;
    FILE *arqAtividade = fopen("atividade.bin", "rb");
    if (arqAtividade == NULL) return 1;
    int maior = 0;
    while (fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
        if (Atv.id > maior) maior = Atv.id;
    }
    fclose(arqAtividade);
    return maior + 1;
}

int proximoIdPacote() {
    Pacote Pc;
    FILE *arqPacote = fopen("pacote.bin", "rb");
    if (arqPacote == NULL) return 1;
    int maior = 0;
    while (fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
        if (Pc.id > maior) maior = Pc.id;
    }
    fclose(arqPacote);
    return maior + 1;
}

int proximoIdPlano() {
    Plano Pl;
    FILE *arqPlano = fopen("plano.bin", "rb");
    if (arqPlano == NULL) return 1;
    int maior = 0;
    while (fread(&Pl, sizeof(Plano), 1, arqPlano) == 1) {
        if (Pl.id > maior) maior = Pl.id;
    }
    fclose(arqPlano);
    return maior + 1;
}

int proximoIdRecebimento() {
    Recebimento Rec;
    FILE *arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento == NULL) return 1;
    int maior = 0;
    while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
        if (Rec.id_recebimento > maior) maior = Rec.id_recebimento;
    }
    fclose(arqRecebimento);
    return maior + 1;
}

//<=============ORDENAÇÃO SEGURA=============>
void ordenarAluno() {
    FILE *arqAluno = fopen("aluno.bin", "rb+");
    Aluno Al, Ali;
    int qtde = 0, i;
    if (arqAluno == NULL) return;
    
    fseek(arqAluno, 0, 2);
    qtde = ftell(arqAluno) / sizeof(Aluno);
    while (qtde > 1) {
        for (i = 0; i < qtde - 1; i++) {
            fseek(arqAluno, i * sizeof(Aluno), 0);
            fread(&Al, sizeof(Aluno), 1, arqAluno);
            fseek(arqAluno, (i + 1) * sizeof(Aluno), 0);
            fread(&Ali, sizeof(Aluno), 1, arqAluno);
            if (strcmp(Al.nome, Ali.nome) > 0) {
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

void ordenarInstrutor() {
    FILE *arqInstrutor = fopen("instrutor.bin", "rb+");
    Instrutor Inst, Insti;
    int qtde = 0, i;
    if (arqInstrutor == NULL) return;
    
    fseek(arqInstrutor, 0, 2);
    qtde = ftell(arqInstrutor) / sizeof(Instrutor);
    while (qtde > 1) {
        for (i = 0; i < qtde - 1; i++) {
            fseek(arqInstrutor, i * sizeof(Instrutor), 0);
            fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
            fseek(arqInstrutor, (i + 1) * sizeof(Instrutor), 0);
            fread(&Insti, sizeof(Instrutor), 1, arqInstrutor);
            if (strcmp(Inst.nome, Insti.nome) > 0) {
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

void ordenarAtividade() {
    FILE *arqAtividade = fopen("atividade.bin", "rb+");
    Atividade Atv, Atvi;
    int qtde = 0, i;
    if (arqAtividade == NULL) return;
    
    fseek(arqAtividade, 0, 2);
    qtde = ftell(arqAtividade) / sizeof(Atividade);
    while (qtde > 1) {
        for (i = 0; i < qtde - 1; i++) {
            fseek(arqAtividade, i * sizeof(Atividade), 0);
            fread(&Atv, sizeof(Atividade), 1, arqAtividade);
            fseek(arqAtividade, (i + 1) * sizeof(Atividade), 0);
            fread(&Atvi, sizeof(Atividade), 1, arqAtividade);
            if (strcmp(Atv.nome, Atvi.nome) > 0) {
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

void ordenarPacote() {
    FILE *arqPacote = fopen("pacote.bin", "rb+");
    Pacote Pc, Pci;
    int qtde = 0, i;
    if (arqPacote == NULL) return;
    
    fseek(arqPacote, 0, 2);
    qtde = ftell(arqPacote) / sizeof(Pacote);
    while (qtde > 1) {
        for (i = 0; i < qtde - 1; i++) {
            fseek(arqPacote, i * sizeof(Pacote), 0);
            fread(&Pc, sizeof(Pacote), 1, arqPacote);
            fseek(arqPacote, (i + 1) * sizeof(Pacote), 0);
            fread(&Pci, sizeof(Pacote), 1, arqPacote);
            if (strcmp(Pc.nome, Pci.nome) > 0) {
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

void ordenarPlano() {
    FILE *arqPlano = fopen("plano.bin", "rb+");
    Plano Pl, Pli;
    int qtde = 0, i;
    if (arqPlano == NULL) return;
    
    fseek(arqPlano, 0, 2);
    qtde = ftell(arqPlano) / sizeof(Plano);
    while (qtde > 1) {
        for (i = 0; i < qtde - 1; i++) {
            fseek(arqPlano, i * sizeof(Plano), 0);
            fread(&Pl, sizeof(Plano), 1, arqPlano);
            fseek(arqPlano, (i + 1) * sizeof(Plano), 0);
            fread(&Pli, sizeof(Plano), 1, arqPlano);
            if (strcmp(Pl.nome, Pli.nome) > 0) {
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
int menuPrincipal() {
    system("cls");
    printf("\n==========================================");
    printf("\n   HITBOXE - SISTEMA DE GESTAO");
    printf("\n==========================================");
    printf("\n1. Gerenciar Pessoas");
    printf("\n2. Gerenciar Atividades");
    printf("\n3. Gerenciar Pacotes");
    printf("\n4. Gerenciar Planos");
    printf("\n5. Movimentacoes e Financeiro");
    printf("\n6. Relatorios");
    printf("\n0. Sair");
    printf("\nOpcao: ");
    return 0;
}

//<=====SELEÇÃO / BUSCA INTERATIVA=====>
int selecionarAluno() {
    FILE *arqAluno = fopen("aluno.bin", "rb");
    Aluno Al;
    int opSub, i, idx = -1, qtde = 0, val = 0;
    char *statusStr;

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

    while (val == 0) {
        system("cls");
        printf("\n--- HITBOXE | SELECIONAR ALUNO ---");
        printf("\n1. Digitar CPF diretamente");
        printf("\n2. Listar todos os alunos (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            idx = -1;
            val = 1;
        } else if (opSub == 1) {
            char cpf[20];
            printf("CPF do Aluno (apenas numeros): ");
            lerCPF(cpf);
            idx = buscaAluno(cpf);
            if (idx == -1) {
                printf("\n** Aluno nao encontrado! **\n");
                system("pause");
            } else {
                val = 1;
            }
        } else if (opSub == 2) {
            arqAluno = fopen("aluno.bin", "rb");
            if (arqAluno != NULL) {
                printf("\n<=== LISTA DE ALUNOS ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Al, sizeof(Aluno), 1, arqAluno);
                    if (Al.status_matricula == 1) {
                        statusStr = "Ativa";
                    } else {
                        statusStr = "Inativa";
                    }
                    printf("[%d] Nome: %s | CPF: %s | Peso: %s | Nivel: %s | Status: %s\n",
                           i, Al.nome, Al.cpf, Al.categoria_peso, Al.nivel_experiencia, statusStr);
                }
                fclose(arqAluno);
                printf("-------------------------\n");
                printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
                idx = lerInteiro();
                if (idx == -1) {
                    val = 1;
                } else if (idx >= 0 && idx < qtde) {
                    val = 1;
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
    return idx;
}

int selecionarInstrutor() {
    FILE *arqInstrutor = fopen("instrutor.bin", "rb");
    Instrutor Inst;
    int opSub, i, idx = -1, qtde = 0, val = 0;

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

    while (val == 0) {
        system("cls");
        printf("\n--- HITBOXE | SELECIONAR INSTRUTOR ---");
        printf("\n1. Digitar CPF diretamente");
        printf("\n2. Listar todos os instrutores (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            idx = -1;
            val = 1;
        } else if (opSub == 1) {
            char cpf[20];
            printf("CPF do Instrutor (apenas numeros): ");
            lerCPF(cpf);
            idx = buscaInstrutor(cpf);
            if (idx == -1) {
                printf("\n** Instrutor nao encontrado! **\n");
                system("pause");
            } else {
                val = 1;
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
                    val = 1;
                } else if (idx >= 0 && idx < qtde) {
                    val = 1;
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
    return idx;
}

int selecionarAtividade() {
    FILE *arqAtividade = fopen("atividade.bin", "rb");
    Atividade Atv;
    int opSub, i, idx = -1, qtde = 0, id, val = 0;

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

    while (val == 0) {
        system("cls");
        printf("\n--- HITBOXE | SELECIONAR ATIVIDADE ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todas as atividades (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            idx = -1;
            val = 1;
        } else if (opSub == 1) {
            printf("ID da Atividade: ");
            id = lerInteiro();
            idx = buscaAtividade(id);
            if (idx == -1) {
                printf("\n** Atividade nao encontrada! **\n");
                system("pause");
            } else {
                val = 1;
            }
        } else if (opSub == 2) {
            arqAtividade = fopen("atividade.bin", "rb");
            if (arqAtividade != NULL) {
                printf("\n<=== LISTA DE ATIVIDADES ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Atv, sizeof(Atividade), 1, arqAtividade);
                    printf("[%d] ID: %d | Nome: %s | Foco: %s | CPF Instrutor: %s\n",
                           i, Atv.id, Atv.nome, Atv.foco_treino, Atv.cpf_instrutor);
                }
                fclose(arqAtividade);
                printf("----------------------------\n");
                printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
                idx = lerInteiro();
                if (idx == -1) {
                    val = 1;
                } else if (idx >= 0 && idx < qtde) {
                    val = 1;
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
    return idx;
}

int selecionarPacote() {
    FILE *arqPacote = fopen("pacote.bin", "rb");
    Pacote Pc;
    int opSub, i, idx = -1, qtde = 0, id, val = 0;

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

    while (val == 0) {
        system("cls");
        printf("\n--- HITBOXE | SELECIONAR PACOTE ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todos os pacotes (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            idx = -1;
            val = 1;
        } else if (opSub == 1) {
            printf("ID do Pacote: ");
            id = lerInteiro();
            idx = buscaPacote(id);
            if (idx == -1) {
                printf("\n** Pacote nao encontrado! **\n");
                system("pause");
            } else {
                val = 1;
            }
        } else if (opSub == 2) {
            arqPacote = fopen("pacote.bin", "rb");
            if (arqPacote != NULL) {
                printf("\n<=== LISTA DE PACOTES ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Pc, sizeof(Pacote), 1, arqPacote);
                    printf("[%d] ID: %d | Nome: %s | Aulas/Mes: %d\n",
                           i, Pc.id, Pc.nome, Pc.qtd_aulas_mes);
                }
                fclose(arqPacote);
                printf("-------------------------\n");
                printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
                idx = lerInteiro();
                if (idx == -1) {
                    val = 1;
                } else if (idx >= 0 && idx < qtde) {
                    val = 1;
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
    return idx;
}

int selecionarPlano() {
    FILE *arqPlano = fopen("plano.bin", "rb");
    Plano Pl;
    int opSub, i, idx = -1, qtde = 0, id, val = 0;

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

    while (val == 0) {
        system("cls");
        printf("\n--- HITBOXE | SELECIONAR PLANO ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todos os planos (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 0) {
            idx = -1;
            val = 1;
        } else if (opSub == 1) {
            printf("ID do Plano: ");
            id = lerInteiro();
            idx = buscaPlano(id);
            if (idx == -1) {
                printf("\n** Plano nao encontrado! **\n");
                system("pause");
            } else {
                val = 1;
            }
        } else if (opSub == 2) {
            arqPlano = fopen("plano.bin", "rb");
            if (arqPlano != NULL) {
                printf("\n<=== LISTA DE PLANOS ===>\n");
                for (i = 0; i < qtde; i++) {
                    fread(&Pl, sizeof(Plano), 1, arqPlano);
                    printf("[%d] ID: %d | Nome: %s | Tipo: %c | Valor Base: R$ %.2f\n",
                           i, Pl.id, Pl.nome, Pl.tipo, Pl.valor_base);
                }
                fclose(arqPlano);
                printf("------------------------\n");
                printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
                idx = lerInteiro();
                if (idx == -1) {
                    val = 1;
                } else if (idx >= 0 && idx < qtde) {
                    val = 1;
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
    return idx;
}

//<=====CADASTROS COM VERIFICAÇÃO DE ESCRITA=====>
char cadastrarAluno() {
    Aluno Al;
    FILE *arqAluno = fopen("aluno.bin", "ab");
    char temp_cpf[20];
    int idxAl, idxInst;

    system("cls");
    if (arqAluno != NULL) {
        printf("\n<==== HITBOXE | CADASTRO DE ALUNO ====>\n");
        printf("Insira o CPF (apenas numeros): ");
        lerCPF(temp_cpf);

        idxAl = buscaAluno(temp_cpf);
        idxInst = buscaInstrutor(temp_cpf);
        if (idxAl != -1) {
            printf("\n** ERRO: CPF ja cadastrado como Aluno! **\n");
        } else if (idxInst != -1) {
            printf("\n** ERRO: CPF ja cadastrado como Instrutor! **\n");
        } else {
            strcpy(Al.cpf, temp_cpf);
            lerTextoApenasLetras("Insira o nome completo: ", Al.nome, sizeof(Al.nome));

            printf("Insira o telefone (apenas numeros): ");
            lerTelefone(Al.telefone);

            lerTextoApenasLetras("Categoria de Peso (ex: Peso Leve, Medio, Pesado): ", Al.categoria_peso, sizeof(Al.categoria_peso));
            lerTextoApenasLetras("Nivel de Experiencia (Iniciante, Amador, Competidor): ", Al.nivel_experiencia, sizeof(Al.nivel_experiencia));

            Al.id_pacote = -1;
            Al.id_plano = -1;
            Al.status_matricula = 0;

            if (fwrite(&Al, sizeof(Aluno), 1, arqAluno) != 1) {
                printf("\n** ERRO CRITICO: Falha ao gravar dados do aluno no disco! **\n");
            } else {
                printf("\n** Aluno cadastrado com sucesso! **\n");
            }
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
    int idxInst, idxAl;

    system("cls");
    if (arqInstrutor != NULL) {
        printf("\n<==== HITBOXE | CADASTRO DE INSTRUTOR ====>\n");
        printf("Insira o CPF (apenas numeros): ");
        lerCPF(temp_cpf);

        idxInst = buscaInstrutor(temp_cpf);
        idxAl = buscaAluno(temp_cpf);
        if (idxInst != -1) {
            printf("\n** ERRO: CPF ja cadastrado como Instrutor! **\n");
        } else if (idxAl != -1) {
            printf("\n** ERRO: CPF ja cadastrado como Aluno! **\n");
        } else {
            strcpy(Inst.cpf, temp_cpf);
            lerTextoApenasLetras("Insira o nome completo: ", Inst.nome, sizeof(Inst.nome));
            lerTextoApenasLetras("Insira a especialidade: ", Inst.especialidade, sizeof(Inst.especialidade));

            if (fwrite(&Inst, sizeof(Instrutor), 1, arqInstrutor) != 1) {
                printf("\n** ERRO CRITICO: Falha ao gravar instrutor! **\n");
            } else {
                printf("\n** Instrutor cadastrado com sucesso! **\n");
            }
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
    FILE *arqAtividade;
    int proximo_id, idxInst;

    proximo_id = proximoIdAtividade();
    arqAtividade = fopen("atividade.bin", "ab");
    system("cls");
    if (arqAtividade != NULL) {
        printf("\n<==== HITBOXE | CADASTRO DE ATIVIDADE ====>\n");
        Atv.id = proximo_id;

        lerTextoApenasLetras("Insira o nome da Atividade: ", Atv.nome, sizeof(Atv.nome));
        lerTextoApenasLetras("Foco do Treino (Tecnica, Sparring, Condicionamento/Saco): ", Atv.foco_treino, sizeof(Atv.foco_treino));

        idxInst = selecionarInstrutor();
        if (idxInst == -1) {
            fclose(arqAtividade);
            printf("\n** Cadastro de atividade cancelado por falta de instrutor. **\n");
            system("pause");
            return 'N';
        }

        FILE *arqInstrutor = fopen("instrutor.bin", "rb");
        if (arqInstrutor != NULL) {
            Instrutor tempInst;
            fseek(arqInstrutor, idxInst * sizeof(Instrutor), 0);
            fread(&tempInst, sizeof(Instrutor), 1, arqInstrutor);
            fclose(arqInstrutor);
            strcpy(Atv.cpf_instrutor, tempInst.cpf);
        } else {
            strcpy(Atv.cpf_instrutor, "");
        }

        if (fwrite(&Atv, sizeof(Atividade), 1, arqAtividade) != 1) {
            printf("\n** ERRO CRITICO: Falha ao gravar atividade! **\n");
        } else {
            printf("\n** Atividade cadastrada com sucesso! **\n");
        }
        
        fclose(arqAtividade);
        ordenarAtividade();

        printf("Deseja cadastrar outra atividade? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarPacote() {
    Pacote Pc;
    FILE *arqPacote;
    int proximo_id, idxAtiv, jaExiste, k, val = 0;
    char continuar = 'S';

    proximo_id = proximoIdPacote();
    arqPacote = fopen("pacote.bin", "ab");
    system("cls");
    if (arqPacote != NULL) {
        printf("\n<==== HITBOXE | CADASTRO DE PACOTE ====>\n");
        Pc.id = proximo_id;
        Pc.qtd_atividades = 0;

        lerTextoApenasLetras("Insira o nome do Pacote: ", Pc.nome, sizeof(Pc.nome));

        printf("Insira a quantidade de aulas por mes: ");
        Pc.qtd_aulas_mes = lerInteiro();
        while (Pc.qtd_aulas_mes <= 0) {
            printf("** VALOR INVALIDO! Digite uma quantidade maior que zero: ");
            Pc.qtd_aulas_mes = lerInteiro();
        }

        while (val == 0 && continuar == 'S' && Pc.qtd_atividades < 10) {
            idxAtiv = selecionarAtividade();
            if (idxAtiv == -1) {
                val = 1;
            } else {
                Atividade Atv;
                FILE *arqAtividade = fopen("atividade.bin", "rb");
                if (arqAtividade != NULL) {
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
                }

                if (Pc.qtd_atividades < 10) {
                    printf("Deseja incluir mais uma atividade neste pacote? (S/N): ");
                    continuar = lerOpcaoSN();
                }
            }
        }

        if (fwrite(&Pc, sizeof(Pacote), 1, arqPacote) != 1) {
            printf("\n** ERRO CRITICO: Falha ao gravar pacote! **\n");
        } else {
            printf("\n** Pacote cadastrado com sucesso! **\n");
        }

        fclose(arqPacote);
        ordenarPacote();

        printf("\nDeseja cadastrar outro pacote? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

char cadastrarPlano() {
    Plano Pl;
    FILE *arqPlano;
    int proximo_id;
    char tipo;

    proximo_id = proximoIdPlano();
    arqPlano = fopen("plano.bin", "ab");
    system("cls");
    if (arqPlano != NULL) {
        printf("\n<==== HITBOXE | CADASTRO DE PLANO ====>\n");
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

        if (fwrite(&Pl, sizeof(Plano), 1, arqPlano) != 1) {
            printf("\n** ERRO CRITICO: Falha ao gravar plano! **\n");
        } else {
            printf("\n** Plano cadastrado com sucesso! **\n");
        }

        fclose(arqPlano);
        ordenarPlano();

        printf("\nDeseja cadastrar outro plano? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Arquivo com erro ao abrir! **\n");
        return 'N';
    }
}

//<=====CONSULTAS=====>
void consultarAluno() {
    Aluno Al;
    char *statusStr;
    int pos = selecionarAluno();
    if (pos != -1) {
        FILE *arqAluno = fopen("aluno.bin", "rb");
        if (arqAluno != NULL) {
            fseek(arqAluno, pos * sizeof(Aluno), 0);
            fread(&Al, sizeof(Aluno), 1, arqAluno);
            fclose(arqAluno);

            if (Al.status_matricula == 1) {
                statusStr = "Ativa";
            } else {
                statusStr = "Inativa";
            }

            system("cls");
            printf("\n** HITBOXE | Aluno encontrado! **\n");
            printf("Nome: %s\n", Al.nome);
            printf("CPF: %s\n", Al.cpf);
            printf("Telefone: %s\n", Al.telefone);
            printf("Categoria de Peso: %s\n", Al.categoria_peso);
            printf("Nivel de Experiencia: %s\n", Al.nivel_experiencia);
            
            if (Al.id_pacote == -1) {
                printf("Pacote: Nao possui\n");
            } else {
                printf("ID Pacote: %d\n", Al.id_pacote);
            }

            if (Al.id_plano == -1) {
                printf("Plano: Nao possui\n");
            } else {
                printf("ID Plano: %d\n", Al.id_plano);
            }

            printf("Status Matricula: %s\n", statusStr);
            system("pause");
        }
    }
}

void consultarInstrutor() {
    Instrutor Inst;
    int pos = selecionarInstrutor();
    if (pos != -1) {
        FILE *arqInstrutor = fopen("instrutor.bin", "rb");
        if (arqInstrutor != NULL) {
            fseek(arqInstrutor, pos * sizeof(Instrutor), 0);
            fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
            fclose(arqInstrutor);

            system("cls");
            printf("\n** HITBOXE | Instrutor encontrado! **\n");
            printf("Nome: %s\n", Inst.nome);
            printf("CPF: %s\n", Inst.cpf);
            printf("Especialidade: %s\n", Inst.especialidade);
            system("pause");
        }
    }
}

void consultarAtividade() {
    Atividade Atv;
    int pos = selecionarAtividade();
    if (pos != -1) {
        FILE *arqAtividade = fopen("atividade.bin", "rb");
        if (arqAtividade != NULL) {
            fseek(arqAtividade, pos * sizeof(Atividade), 0);
            fread(&Atv, sizeof(Atividade), 1, arqAtividade);
            fclose(arqAtividade);

            system("cls");
            printf("\n** HITBOXE | Atividade encontrada! **\n");
            printf("ID: %d\n", Atv.id);
            printf("Nome: %s\n", Atv.nome);
            printf("Foco do Treino: %s\n", Atv.foco_treino);
            printf("CPF Instrutor: %s\n", Atv.cpf_instrutor);
            system("pause");
        }
    }
}

void consultarPacote() {
    Pacote Pc;
    int pos = selecionarPacote();
    int j;
    if (pos != -1) {
        FILE *arqPacote = fopen("pacote.bin", "rb");
        if (arqPacote != NULL) {
            fseek(arqPacote, pos * sizeof(Pacote), 0);
            fread(&Pc, sizeof(Pacote), 1, arqPacote);
            fclose(arqPacote);

            system("cls");
            printf("\n** HITBOXE | Pacote encontrado! **\n");
            printf("ID: %d\n", Pc.id);
            printf("Nome: %s\n", Pc.nome);
            printf("Quantidade de Aulas por Mes: %d\n", Pc.qtd_aulas_mes);
            printf("Atividades: ");
            if (Pc.qtd_atividades == 0) {
                printf("Nao possui");
            } else {
                for (j = 0; j < Pc.qtd_atividades; j++) {
                    printf("[%d] ", Pc.ids_atividades[j]);
                }
            }
            printf("\n");
            system("pause");
        }
    }
}

void consultarPlano() {
    Plano Pl;
    int pos = selecionarPlano();
    if (pos != -1) {
        FILE *arqPlano = fopen("plano.bin", "rb");
        if (arqPlano != NULL) {
            fseek(arqPlano, pos * sizeof(Plano), 0);
            fread(&Pl, sizeof(Plano), 1, arqPlano);
            fclose(arqPlano);

            system("cls");
            printf("\n** HITBOXE | Plano encontrado! **\n");
            printf("ID: %d\n", Pl.id);
            printf("Nome: %s\n", Pl.nome);
            printf("Tipo: %c\n", Pl.tipo);
            printf("Valor Base: R$ %.2f\n", Pl.valor_base);
            printf("Valor com Desconto: R$ %.2f\n", calcularDescontoPlano(Pl.tipo, Pl.valor_base));
            system("pause");
        }
    }
}

void consultarPessoas() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | CONSULTAR PESSOAS ---");
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

//<=====ALTERAÇÕES DE DADOS COM SEGURANÇA E VERIFICAÇÃO=====>
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
    printf("\n--- HITBOXE | ALTERAR DADOS DO ALUNO ---");
    printf("\nCPF atual: %s", Al.cpf);
    printf("\nDeseja alterar o CPF? (S/N): ");
    if (lerOpcaoSN() == 'S') {
        char novoCpf[20];
        int cpfValido = 0;

        while (!cpfValido) {
            printf("Digite o NOVO CPF (apenas numeros): ");
            lerCPF(novoCpf);

            if (buscaAluno(novoCpf) != -1 || buscaInstrutor(novoCpf) != -1) {
                printf("\n** ERRO: Este CPF ja esta cadastrado no sistema! **\n");
            } else {
                cpfValido = 1;
            }

            if (!cpfValido) {
                printf("Deseja tentar redigir o CPF novamente? (S/N): ");
                if (lerOpcaoSN() == 'N') {
                    printf("\n** Alteracao de CPF cancelada. Mantendo CPF anterior. **\n");
                    break;
                }
            }
        }

        if (cpfValido) {
            char cpfAntigo[15];
            strcpy(cpfAntigo, Al.cpf);
            strcpy(Al.cpf, novoCpf);

            FILE *arqRecebimento = fopen("recebimento.bin", "rb+");
            if (arqRecebimento != NULL) {
                Recebimento Rec;
                long recPos = 0;
                while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
                    if (strcmp(Rec.cpf_aluno, cpfAntigo) == 0) {
                        strcpy(Rec.cpf_aluno, novoCpf);
                        fseek(arqRecebimento, recPos, SEEK_SET);
                        fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
                        fseek(arqRecebimento, recPos + sizeof(Recebimento), SEEK_SET);
                    }
                    recPos = ftell(arqRecebimento);
                }
                fclose(arqRecebimento);
            }
            printf("\n** CPF alterado com sucesso! **\n");
        }
    }

    printf("\nNome atual: %s", Al.nome);
    lerTextoApenasLetras("\nNovo nome completo: ", Al.nome, sizeof(Al.nome));

    printf("Novo telefone (apenas numeros): ");
    lerTelefone(Al.telefone);

    printf("Categoria de Peso atual: %s", Al.categoria_peso);
    lerTextoApenasLetras("\nNova Categoria de Peso: ", Al.categoria_peso, sizeof(Al.categoria_peso));

    printf("Nivel de Experiencia atual: %s", Al.nivel_experiencia);
    lerTextoApenasLetras("\nNovo Nivel de Experiencia: ", Al.nivel_experiencia, sizeof(Al.nivel_experiencia));

    fseek(arqAluno, pos * sizeof(Aluno), SEEK_SET);
    if (fwrite(&Al, sizeof(Aluno), 1, arqAluno) != 1) {
        printf("\n** ERRO CRITICO: Falha ao atualizar dados do aluno! **\n");
    } else {
        printf("\n** Aluno alterado com sucesso! **\n");
    }
    fclose(arqAluno);

    ordenarAluno();
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
    printf("\n--- HITBOXE | ALTERAR DADOS DO INSTRUTOR ---");
    printf("\nCPF atual: %s", Inst.cpf);
    printf("\nDeseja alterar o CPF? (S/N): ");
    if (lerOpcaoSN() == 'S') {
        char novoCpf[20];
        int cpfValido = 0;

        while (!cpfValido) {
            printf("Digite o NOVO CPF (apenas numeros): ");
            lerCPF(novoCpf);

            if (buscaAluno(novoCpf) != -1 || buscaInstrutor(novoCpf) != -1) {
                printf("\n** ERRO: Este CPF ja esta cadastrado no sistema! **\n");
            } else {
                cpfValido = 1;
            }

            if (!cpfValido) {
                printf("Deseja tentar redigir o CPF novamente? (S/N): ");
                if (lerOpcaoSN() == 'N') {
                    printf("\n** Alteracao de CPF cancelada. Mantendo CPF anterior. **\n");
                    break;
                }
            }
        }

        if (cpfValido) {
            char cpfAntigo[15];
            strcpy(cpfAntigo, Inst.cpf);
            strcpy(Inst.cpf, novoCpf);

            FILE *arqAtividade = fopen("atividade.bin", "rb+");
            if (arqAtividade != NULL) {
                Atividade Atv;
                long atvPos = 0;
                while (fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
                    if (strcmp(Atv.cpf_instrutor, cpfAntigo) == 0) {
                        strcpy(Atv.cpf_instrutor, novoCpf);
                        fseek(arqAtividade, atvPos, SEEK_SET);
                        fwrite(&Atv, sizeof(Atividade), 1, arqAtividade);
                        fseek(arqAtividade, atvPos + sizeof(Atividade), SEEK_SET);
                    }
                    atvPos = ftell(arqAtividade);
                }
                fclose(arqAtividade);
            }
            printf("\n** CPF do instrutor alterado com sucesso! **\n");
        }
    }

    printf("\nNome atual: %s", Inst.nome);
    lerTextoApenasLetras("\nNovo nome completo: ", Inst.nome, sizeof(Inst.nome));
    lerTextoApenasLetras("Nova especialidade: ", Inst.especialidade, sizeof(Inst.especialidade));

    fseek(arqInstrutor, pos * sizeof(Instrutor), SEEK_SET);
    if (fwrite(&Inst, sizeof(Instrutor), 1, arqInstrutor) != 1) {
        printf("\n** ERRO CRITICO: Falha ao atualizar instrutor! **\n");
    } else {
        printf("\n** Instrutor alterado com sucesso! **\n");
    }
    fclose(arqInstrutor);

    ordenarInstrutor();
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
    printf("\n--- HITBOXE | ALTERAR DADOS DA ATIVIDADE ---");
    printf("\nNome atual: %s", Atv.nome);
    lerTextoApenasLetras("\nNovo nome da Atividade: ", Atv.nome, sizeof(Atv.nome));

    printf("Foco atual: %s", Atv.foco_treino);
    lerTextoApenasLetras("\nNovo Foco do Treino: ", Atv.foco_treino, sizeof(Atv.foco_treino));

    printf("Deseja alterar o Instrutor responsavel? (S/N): ");
    if (lerOpcaoSN() == 'S') {
        int idxInst = selecionarInstrutor();
        if (idxInst != -1) {
            FILE *arqInstrutor = fopen("instrutor.bin", "rb");
            if (arqInstrutor != NULL) {
                Instrutor tempInst;
                fseek(arqInstrutor, idxInst * sizeof(Instrutor), SEEK_SET);
                fread(&tempInst, sizeof(Instrutor), 1, arqInstrutor);
                fclose(arqInstrutor);
                strcpy(Atv.cpf_instrutor, tempInst.cpf);
            }
        }
    }

    fseek(arqAtividade, pos * sizeof(Atividade), SEEK_SET);
    if (fwrite(&Atv, sizeof(Atividade), 1, arqAtividade) != 1) {
        printf("\n** ERRO CRITICO: Falha ao atualizar atividade! **\n");
    } else {
        printf("\n** Atividade alterada com sucesso! **\n");
    }
    fclose(arqAtividade);

    ordenarAtividade();
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
    printf("\n--- HITBOXE | ALTERAR DADOS DO PACOTE ---");
    printf("\nNome atual: %s", Pc.nome);
    lerTextoApenasLetras("\nNovo nome do Pacote: ", Pc.nome, sizeof(Pc.nome));

    printf("\nQuantidade atual de aulas por mes: %d", Pc.qtd_aulas_mes);
    printf("\nNova quantidade de aulas por mes: ");
    Pc.qtd_aulas_mes = lerInteiro();
    while (Pc.qtd_aulas_mes <= 0) {
        printf("** VALOR INVALIDO! Digite uma quantidade maior que zero: ");
        Pc.qtd_aulas_mes = lerInteiro();
    }

    printf("\nDeseja reconfigurar as atividades deste pacote? (S/N): ");
    if (lerOpcaoSN() == 'S') {
        Pc.qtd_atividades = 0;
        char continuar = 'S';
        int idxAtiv, jaExiste, k, val = 0;

        while (val == 0 && continuar == 'S' && Pc.qtd_atividades < 10) {
            idxAtiv = selecionarAtividade();
            if (idxAtiv == -1) {
                val = 1;
            } else {
                Atividade Atv;
                FILE *arqAtividade = fopen("atividade.bin", "rb");
                if (arqAtividade != NULL) {
                    fseek(arqAtividade, idxAtiv * sizeof(Atividade), SEEK_SET);
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
                }

                if (Pc.qtd_atividades < 10) {
                    printf("Deseja incluir mais uma atividade? (S/N): ");
                    continuar = lerOpcaoSN();
                }
            }
        }
    }

    fseek(arqPacote, pos * sizeof(Pacote), SEEK_SET);
    if (fwrite(&Pc, sizeof(Pacote), 1, arqPacote) != 1) {
        printf("\n** ERRO CRITICO: Falha ao atualizar pacote! **\n");
    } else {
        printf("\n** Pacote alterado com sucesso! **\n");
    }
    fclose(arqPacote);

    ordenarPacote();
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

    int idAntigo = Pl.id;

    system("cls");
    printf("\n--- HITBOXE | ALTERAR DADOS DO PLANO ---");
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
    if (fwrite(&Pl, sizeof(Plano), 1, arqPlano) != 1) {
        printf("\n** ERRO CRITICO: Falha ao atualizar plano! **\n");
    }
    fclose(arqPlano);

    float novoValorComDesconto = calcularDescontoPlano(Pl.tipo, Pl.valor_base);

    FILE *arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno != NULL) {
        Aluno tempAl;
        while (fread(&tempAl, sizeof(Aluno), 1, arqAluno) == 1) {
            if (tempAl.id_plano == idAntigo && tempAl.status_matricula == 1) {
                FILE *arqRecebimento = fopen("recebimento.bin", "rb+");
                if (arqRecebimento != NULL) {
                    Recebimento Rec;
                    long recPos = 0;
                    while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
                        if (strcmp(Rec.cpf_aluno, tempAl.cpf) == 0 && Rec.status_pago == 0) {
                            Rec.valor_cobrado = novoValorComDesconto;
                            fseek(arqRecebimento, recPos, SEEK_SET);
                            fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
                            fseek(arqRecebimento, recPos + sizeof(Recebimento), SEEK_SET);
                        }
                        recPos = ftell(arqRecebimento);
                    }
                    fclose(arqRecebimento);
                }
            }
        }
        fclose(arqAluno);
    }

    ordenarPlano();
    printf("\n** Plano alterado com sucesso e boletos pendentes atualizados (R$ %.2f)! **\n", novoValorComDesconto);
    system("pause");
}

void alterarPessoa() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | ALTERAR PESSOA ---");
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

//<=====EXCLUSÕES COM TRANSAÇÃO SEGURA E VALIDAÇÃO DE INTEGRIDADE=====>
void excluirAlunoReal() {
    FILE *arqAluno, *arqTemp;
    Aluno Al;
    int pos, temMatriculaAtiva = 0, temBoletos = 0, val = 0;

    pos = selecionarAluno();
    if (pos == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) return;
    fseek(arqAluno, pos * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    if (Al.status_matricula == 1) {
        temMatriculaAtiva = 1;
    }

    FILE *arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento != NULL) {
        Recebimento Rec;
        while (val == 0 && fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
            if (strcmp(Rec.cpf_aluno, Al.cpf) == 0) {
                temBoletos = 1;
                val = 1;
            }
        }
        fclose(arqRecebimento);
    }

    if (temMatriculaAtiva || temBoletos) {
        printf("\n**************************************************");
        printf("\n**          AVISO DE PENDENCIAS DO ALUNO        **");
        printf("\n**************************************************");
        if (temMatriculaAtiva) printf("\n- Aluno possui MATRICULA ATIVA no sistema!");
        if (temBoletos) printf("\n- Aluno possui BOLETOS / RECEBIMENTOS registrados!");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir este aluno mesmo com essas pendencias? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- HITBOXE | EXCLUIR ALUNO ---");
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
            int sucesso = 1;
            while (fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
                if (strcmp(Al.cpf, cpfExcluir) != 0) {
                    if (fwrite(&Al, sizeof(Aluno), 1, arqTemp) != 1) {
                        sucesso = 0;
                    }
                }
            }
            fclose(arqTemp);
            fclose(arqAluno);

            if (sucesso) {
                remove("aluno.bin");
                if (rename("auxiliar.bin", "aluno.bin") == 0) {
                    ordenarAluno();
                    printf("\n** O aluno foi excluido com sucesso! **\n");
                } else {
                    printf("\n** ERRO CRITICO: Falha ao substituir arquivo de alunos! **\n");
                }
            } else {
                remove("auxiliar.bin");
                printf("\n** ERRO CRITICO: Falha durante a gravacao temporaria! Exclusao cancelada. **\n");
            }
        } else {
            if (arqAluno != NULL) fclose(arqAluno);
            if (arqTemp != NULL) fclose(arqTemp);
            printf("\n** Erro ao manipular os arquivos! **\n");
        }
    }
    system("pause");
}

void excluirInstrutor() {
    FILE *arqInstrutor, *arqTemp;
    Instrutor Inst;
    int pos, atividadesVinculadas = 0, val = 0;

    pos = selecionarInstrutor();
    if (pos == -1) return;

    arqInstrutor = fopen("instrutor.bin", "rb");
    if (arqInstrutor == NULL) return;
    fseek(arqInstrutor, pos * sizeof(Instrutor), 0);
    fread(&Inst, sizeof(Instrutor), 1, arqInstrutor);
    fclose(arqInstrutor);

    FILE *arqAtividade = fopen("atividade.bin", "rb");
    if (arqAtividade != NULL) {
        Atividade Atv;
        while (val == 0 && fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
            if (strcmp(Atv.cpf_instrutor, Inst.cpf) == 0) {
                atividadesVinculadas = 1;
                val = 1;
            }
        }
        fclose(arqAtividade);
    }

    if (atividadesVinculadas) {
        printf("\n**************************************************");
        printf("\n**        AVISO DE VINCULOS DO INSTRUTOR        **");
        printf("\n**************************************************");
        printf("\n- O instrutor possui ATIVIDADES VINCULADAS a ele!");
        printf("\n- AVISO: Se excluir, as atividades ficarao sem instrutor.");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir mesmo com essas atividades? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- HITBOXE | EXCLUIR INSTRUTOR ---");
    printf("\nNome: %s", Inst.nome);
    printf("\nCPF: %s", Inst.cpf);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");
    
    if (lerOpcaoSN() == 'S') {
        char cpfExcluir[15];
        strcpy(cpfExcluir, Inst.cpf);

        FILE *arqAtvRead = fopen("atividade.bin", "rb");
        FILE *arqAtvTemp = fopen("aux_atv.bin", "wb");
        int okAtv = 1;
        if (arqAtvRead != NULL && arqAtvTemp != NULL) {
            Atividade tempAtv;
            while (fread(&tempAtv, sizeof(Atividade), 1, arqAtvRead) == 1) {
                if (strcmp(tempAtv.cpf_instrutor, cpfExcluir) == 0) {
                    strcpy(tempAtv.cpf_instrutor, "");
                }
                if (fwrite(&tempAtv, sizeof(Atividade), 1, arqAtvTemp) != 1) okAtv = 0;
            }
            fclose(arqAtvTemp);
            fclose(arqAtvRead);
            if (okAtv) {
                remove("atividade.bin");
                rename("aux_atv.bin", "atividade.bin");
            } else {
                remove("aux_atv.bin");
            }
        }

        arqInstrutor = fopen("instrutor.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");
        
        if (arqInstrutor != NULL && arqTemp != NULL) {
            int sucesso = 1;
            while (fread(&Inst, sizeof(Instrutor), 1, arqInstrutor) == 1) {
                if (strcmp(Inst.cpf, cpfExcluir) != 0) {
                    if (fwrite(&Inst, sizeof(Instrutor), 1, arqTemp) != 1) sucesso = 0;
                }
            }
            fclose(arqTemp);
            fclose(arqInstrutor);

            if (sucesso) {
                remove("instrutor.bin");
                if (rename("auxiliar.bin", "instrutor.bin") == 0) {
                    ordenarInstrutor();
                    printf("\n** O instrutor foi excluido com sucesso! **\n");
                } else {
                    printf("\n** ERRO CRITICO: Falha ao substituir arquivo de instrutores! **\n");
                }
            } else {
                remove("auxiliar.bin");
                printf("\n** ERRO CRITICO: Falha na gravacao transacional! **\n");
            }
        } else {
            if (arqInstrutor != NULL) fclose(arqInstrutor);
            if (arqTemp != NULL) fclose(arqTemp);
            printf("\n** Erro ao manipular os arquivos! **\n");
        }
    }
    system("pause");
}

void excluirAtividade() {
    FILE *arqAtividade, *arqTemp;
    Atividade Atv;
    int pos, pacotesVinculados = 0, val = 0;

    pos = selecionarAtividade();
    if (pos == -1) return;

    arqAtividade = fopen("atividade.bin", "rb");
    if (arqAtividade == NULL) return;
    fseek(arqAtividade, pos * sizeof(Atividade), 0);
    fread(&Atv, sizeof(Atividade), 1, arqAtividade);
    fclose(arqAtividade);

    FILE *arqPacote = fopen("pacote.bin", "rb");
    if (arqPacote != NULL) {
        Pacote Pc;
        while (val == 0 && fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
            int j = 0;
            while (val == 0 && j < Pc.qtd_atividades) {
                if (Pc.ids_atividades[j] == Atv.id) {
                    pacotesVinculados = 1;
                    val = 1;
                }
                j++;
            }
        }
        fclose(arqPacote);
    }

    if (pacotesVinculados) {
        printf("\n**************************************************");
        printf("\n**         AVISO DE VINCULOS DA ATIVIDADE       **");
        printf("\n**************************************************");
        printf("\n- A atividade esta associada a um ou mais PACOTES!");
        printf("\n- AVISO: Se excluir, ela sera removida dos pacotes.");
        printf("\n--------------------------------------------------");
        printf("\nDeseja realmente excluir mesmo assim? (S/N): ");
        if (lerOpcaoSN() == 'N') return;
    }

    system("cls");
    printf("\n--- HITBOXE | EXCLUIR ATIVIDADE ---");
    printf("\nID: %d", Atv.id);
    printf("\nNome: %s", Atv.nome);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");

    if (lerOpcaoSN() == 'S') {
        int idExcluir = Atv.id;

        FILE *arqPcRead = fopen("pacote.bin", "rb");
        FILE *arqPcTemp = fopen("aux_pc.bin", "wb");
        int okPc = 1;
        if (arqPcRead != NULL && arqPcTemp != NULL) {
            Pacote tempPc;
            while (fread(&tempPc, sizeof(Pacote), 1, arqPcRead) == 1) {
                int k = 0, novaQtd = 0;
                int novasAtividades[10];
                while (k < tempPc.qtd_atividades) {
                    if (tempPc.ids_atividades[k] != idExcluir) {
                        novasAtividades[novaQtd] = tempPc.ids_atividades[k];
                        novaQtd++;
                    }
                    k++;
                }
                tempPc.qtd_atividades = novaQtd;
                for (k = 0; k < novaQtd; k++) {
                    tempPc.ids_atividades[k] = novasAtividades[k];
                }
                if (fwrite(&tempPc, sizeof(Pacote), 1, arqPcTemp) != 1) okPc = 0;
            }
            fclose(arqPcTemp);
            fclose(arqPcRead);
            if (okPc) {
                remove("pacote.bin");
                rename("aux_pc.bin", "pacote.bin");
            } else {
                remove("aux_pc.bin");
            }
        }

        arqAtividade = fopen("atividade.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");

        if (arqAtividade != NULL && arqTemp != NULL) {
            int sucesso = 1;
            while (fread(&Atv, sizeof(Atividade), 1, arqAtividade) == 1) {
                if (Atv.id != idExcluir) {
                    if (fwrite(&Atv, sizeof(Atividade), 1, arqTemp) != 1) sucesso = 0;
                }
            }
            fclose(arqTemp);
            fclose(arqAtividade);

            if (sucesso) {
                remove("atividade.bin");
                if (rename("auxiliar.bin", "atividade.bin") == 0) {
                    ordenarAtividade();
                    printf("\n** A atividade foi excluida com sucesso! **\n");
                } else {
                    printf("\n** ERRO CRITICO: Falha ao substituir arquivo de atividades! **\n");
                }
            } else {
                remove("auxiliar.bin");
                printf("\n** ERRO CRITICO: Falha na gravacao transacional! **\n");
            }
        }
    }
    system("pause");
}

void excluirPacote() {
    FILE *arqPacote, *arqTemp;
    Pacote Pc;
    int pos, alunosAtivosVinculados = 0, val = 0;

    pos = selecionarPacote();
    if (pos == -1) return;

    arqPacote = fopen("pacote.bin", "rb");
    if (arqPacote == NULL) return;
    fseek(arqPacote, pos * sizeof(Pacote), 0);
    fread(&Pc, sizeof(Pacote), 1, arqPacote);
    fclose(arqPacote);

    FILE *arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno != NULL) {
        Aluno Al;
        while (val == 0 && fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
            if (Al.id_pacote == Pc.id && Al.status_matricula == 1) {
                alunosAtivosVinculados = 1;
                val = 1;
            }
        }
        fclose(arqAluno);
    }

    if (alunosAtivosVinculados) {
        printf("\n**************************************************");
        printf("\n**          BLOQUEIO DE SEGURANCA               **");
        printf("\n**************************************************");
        printf("\n- O pacote esta vinculado a ALUNOS COM MATRICULA ATIVA!");
        printf("\n- Impossivel excluir pacotes com matriculas ativas.");
        printf("\n- Realize o cancelamento ou alteracao do aluno primeiro.");
        printf("\n--------------------------------------------------");
        system("pause");
        return;
    }

    system("cls");
    printf("\n--- HITBOXE | EXCLUIR PACOTE ---");
    printf("\nID: %d", Pc.id);
    printf("\nNome: %s", Pc.nome);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");

    if (lerOpcaoSN() == 'S') {
        int idExcluir = Pc.id;

        arqPacote = fopen("pacote.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");

        if (arqPacote != NULL && arqTemp != NULL) {
            int sucesso = 1;
            while (fread(&Pc, sizeof(Pacote), 1, arqPacote) == 1) {
                if (Pc.id != idExcluir) {
                    if (fwrite(&Pc, sizeof(Pacote), 1, arqTemp) != 1) sucesso = 0;
                }
            }
            fclose(arqTemp);
            fclose(arqPacote);

            if (sucesso) {
                remove("pacote.bin");
                if (rename("auxiliar.bin", "pacote.bin") == 0) {
                    ordenarPacote();
                    printf("\n** O pacote foi excluido com sucesso! **\n");
                } else {
                    printf("\n** ERRO CRITICO: Falha ao substituir arquivo de pacotes! **\n");
                }
            } else {
                remove("auxiliar.bin");
                printf("\n** ERRO CRITICO: Falha na gravacao transacional! **\n");
            }
        }
    }
    system("pause");
}

void excluirPlano() {
    FILE *arqPlano, *arqTemp;
    Plano Pl;
    int pos, alunosAtivosVinculados = 0, val = 0;

    pos = selecionarPlano();
    if (pos == -1) return;

    arqPlano = fopen("plano.bin", "rb");
    if (arqPlano == NULL) return;
    fseek(arqPlano, pos * sizeof(Plano), 0);
    fread(&Pl, sizeof(Plano), 1, arqPlano);
    fclose(arqPlano);

    FILE *arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno != NULL) {
        Aluno Al;
        while (val == 0 && fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
            if (Al.id_plano == Pl.id && Al.status_matricula == 1) {
                alunosAtivosVinculados = 1;
                val = 1;
            }
        }
        fclose(arqAluno);
    }

    if (alunosAtivosVinculados) {
        printf("\n**************************************************");
        printf("\n**          BLOQUEIO DE SEGURANCA               **");
        printf("\n**************************************************");
        printf("\n- O plano esta vinculado a ALUNOS COM MATRICULA ATIVA!");
        printf("\n- Impossivel excluir planos com matriculas ativas.");
        printf("\n- Realize o cancelamento ou alteracao do aluno primeiro.");
        printf("\n--------------------------------------------------");
        system("pause");
        return;
    }

    system("cls");
    printf("\n--- HITBOXE | EXCLUIR PLANO ---");
    printf("\nID: %d", Pl.id);
    printf("\nNome: %s", Pl.nome);
    printf("\n-------------------");
    printf("\nConfirmar exclusao definitiva? (S/N): ");

    if (lerOpcaoSN() == 'S') {
        int idExcluir = Pl.id;

        arqPlano = fopen("plano.bin", "rb");
        arqTemp = fopen("auxiliar.bin", "wb");

        if (arqPlano != NULL && arqTemp != NULL) {
            int sucesso = 1;
            while (fread(&Pl, sizeof(Plano), 1, arqPlano) == 1) {
                if (Pl.id != idExcluir) {
                    if (fwrite(&Pl, sizeof(Plano), 1, arqTemp) != 1) sucesso = 0;
                }
            }
            fclose(arqTemp);
            fclose(arqPlano);

            if (sucesso) {
                remove("plano.bin");
                if (rename("auxiliar.bin", "plano.bin") == 0) {
                    ordenarPlano();
                    printf("\n** O plano foi excluido com sucesso! **\n");
                } else {
                    printf("\n** ERRO CRITICO: Falha ao substituir arquivo de planos! **\n");
                }
            } else {
                remove("auxiliar.bin");
                printf("\n** ERRO CRITICO: Falha na gravacao transacional! **\n");
            }
        }
    }
    system("pause");
}

void excluirPessoa() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | EXCLUIR PESSOA ---");
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

//<=====REGRAS FINANCEIRAS E MOVIMENTAÇÕES ROBUSTAS=====>
int existeBoleto(char cpf[], int mes, int ano) {
    Recebimento Rec;
    int val = 0, achou = 0;
    FILE *arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento == NULL) return 0;
    
    while (val == 0 && fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
        if (strcmp(Rec.cpf_aluno, cpf) == 0 && Rec.mes_referencia == mes && Rec.ano_referencia == ano && Rec.status_pago != 2) {
            achou = 1;
            val = 1;
        }
    }
    fclose(arqRecebimento);
    return achou;
}

void gerarProximoBoleto(char cpf[], int mes, int ano, float valor) {
    Recebimento Rec;
    FILE *arqRecebimento;
    int proximo_id;

    int idxAl = buscaAluno(cpf);
    if (idxAl != -1) {
        FILE *arqAluno = fopen("aluno.bin", "rb");
        if (arqAluno != NULL) {
            Aluno tempAl;
            fseek(arqAluno, idxAl * sizeof(Aluno), SEEK_SET);
            fread(&tempAl, sizeof(Aluno), 1, arqAluno);
            fclose(arqAluno);
            
            if (tempAl.status_matricula == 0) return;

            int idxPl = buscaPlano(tempAl.id_plano);
            if (idxPl != -1) {
                FILE *arqPlano = fopen("plano.bin", "rb");
                if (arqPlano != NULL) {
                    Plano tempPl;
                    fseek(arqPlano, idxPl * sizeof(Plano), SEEK_SET);
                    fread(&tempPl, sizeof(Plano), 1, arqPlano);
                    fclose(arqPlano);

                    int incrementoMeses = 1;
                    if (tempPl.tipo == 'T') incrementoMeses = 3;
                    else if (tempPl.tipo == 'S') incrementoMeses = 6;
                    else if (tempPl.tipo == 'A') incrementoMeses = 12;

                    mes += incrementoMeses;
                    while (mes > 12) {
                        mes -= 12;
                        ano++;
                    }
                }
            }
        }
    }

    if (existeBoleto(cpf, mes, ano)) return;

    proximo_id = proximoIdRecebimento();
    arqRecebimento = fopen("recebimento.bin", "ab");
    if (arqRecebimento != NULL) {
        Rec.id_recebimento = proximo_id;
        strcpy(Rec.cpf_aluno, cpf);
        Rec.mes_referencia = mes;
        Rec.ano_referencia = ano;
        Rec.valor_cobrado = valor;
        Rec.status_pago = 0;
        
        if (fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento) != 1) {
            printf("\n** AVISO: Falha ao gravar boleto gerado no disco! **\n");
        }
        fclose(arqRecebimento);
    }
}

void efetuarMatricula() {
    int idxAluno, idxPlano, idxPacote, mesInicio, anoInicio;
    float valorFinal;
    Aluno Al;
    Plano Pl;
    Pacote Pc;
    FILE *arqAluno, *arqPlano, *arqPacote, *arqRecebimento;

    system("cls");
    printf("\n<==== HITBOXE | EFETUAR MATRICULA ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) return;
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
    if (arqPlano == NULL) return;
    fseek(arqPlano, idxPlano * sizeof(Plano), 0);
    fread(&Pl, sizeof(Plano), 1, arqPlano);
    fclose(arqPlano);

    idxPacote = selecionarPacote();
    if (idxPacote == -1) return;

    arqPacote = fopen("pacote.bin", "rb");
    if (arqPacote == NULL) return;
    fseek(arqPacote, idxPacote * sizeof(Pacote), 0);
    fread(&Pc, sizeof(Pacote), 1, arqPacote);
    fclose(arqPacote);

    printf("Mes inicial da cobranca (1-12): ");
    do {
        mesInicio = lerInteiro();
        if (mesInicio < 1 || mesInicio > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mesInicio < 1 || mesInicio > 12);

    printf("Ano inicial da cobranca (ex: 2026): ");
    anoInicio = lerInteiro();
    while (anoInicio < 2024 || anoInicio > 2100) {
        printf("** ANO INVALIDO! Digite um ano valido: ");
        anoInicio = lerInteiro();
    }

    valorFinal = calcularDescontoPlano(Pl.tipo, Pl.valor_base);

    Al.id_plano = Pl.id;
    Al.id_pacote = Pc.id;
    Al.status_matricula = 1;

    arqAluno = fopen("aluno.bin", "rb+");
    if (arqAluno != NULL) {
        fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
        if (fwrite(&Al, sizeof(Aluno), 1, arqAluno) != 1) {
            printf("\n** ERRO CRITICO: Falha ao gravar matricula no disco! **\n");
            fclose(arqAluno);
            system("pause");
            return;
        }
        fclose(arqAluno);
    } else {
        printf("\n** ERRO CRITICO: Impossivel abrir arquivo de alunos para gravacao! **\n");
        system("pause");
        return;
    }

    if (!existeBoleto(Al.cpf, mesInicio, anoInicio)) {
        int idRec = proximoIdRecebimento();
        arqRecebimento = fopen("recebimento.bin", "ab");
        if (arqRecebimento != NULL) {
            Recebimento Rec;
            Rec.id_recebimento = idRec;
            strcpy(Rec.cpf_aluno, Al.cpf);
            Rec.mes_referencia = mesInicio;
            Rec.ano_referencia = anoInicio;
            Rec.valor_cobrado = valorFinal;
            Rec.status_pago = 0;
            fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
            fclose(arqRecebimento);
        }
    }

    printf("\n[MATRICULA REGISTRADA COM SUCESSO]");
    printf("\nAluno: %s", Al.nome);
    printf("\nPlano: %s | Valor Base: R$ %.2f | Valor Final c/ Desconto: R$ %.2f\n",
           Pl.nome, Pl.valor_base, valorFinal);
    system("pause");
}

void efetuarCancelamento() {
    int idxAluno, idxPlano;
    float multa = 0.0, reembolso = 0.0, valorEfetivo = 0.0;
    Aluno Al;
    Plano Pl;
    FILE *arqAluno, *arqPlano;

    system("cls");
    printf("\n<==== HITBOXE | CANCELAMENTO DE MATRICULA ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) return;
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
        printf("\n** AVISO: Plano vinculado nao existe mais. Cancelamento sem multa. **\n");
    } else {
        arqPlano = fopen("plano.bin", "rb");
        if (arqPlano != NULL) {
            fseek(arqPlano, idxPlano * sizeof(Plano), 0);
            fread(&Pl, sizeof(Plano), 1, arqPlano);
            fclose(arqPlano);

            valorEfetivo = calcularDescontoPlano(Pl.tipo, Pl.valor_base);

            if (Pl.tipo != 'M') {
                multa = valorEfetivo * 0.30f;
                reembolso = valorEfetivo * 0.70f;
                printf("\nMulta de Retencao (30%%): R$ %.2f", multa);
                printf("\nValor Reembolsado ao Aluno (70%%): R$ %.2f\n", reembolso);
            } else {
                printf("\nPlano Mensal cancelado sem taxas adicionais.\n");
            }
        }
    }

    FILE *arqRecebimento = fopen("recebimento.bin", "rb+");
    if (arqRecebimento != NULL) {
        Recebimento Rec;
        long recPos = 0;
        while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
            if (strcmp(Rec.cpf_aluno, Al.cpf) == 0 && Rec.status_pago == 0) {
                Rec.status_pago = 2;
                fseek(arqRecebimento, recPos, SEEK_SET);
                fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
                fseek(arqRecebimento, recPos + sizeof(Recebimento), SEEK_SET);
            }
            recPos = ftell(arqRecebimento);
        }
        fclose(arqRecebimento);
    }

    Al.status_matricula = 0;
    Al.id_plano = -1;
    Al.id_pacote = -1;

    arqAluno = fopen("aluno.bin", "rb+");
    if (arqAluno != NULL) {
        fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
        if (fwrite(&Al, sizeof(Aluno), 1, arqAluno) != 1) {
            printf("\n** ERRO CRITICO: Falha ao salvar cancelamento no disco! **\n");
        }
        fclose(arqAluno);
    }

    printf("\n** Matricula cancelada com sucesso e boletos pendentes invalidados! **\n");
    system("pause");
}

void efetuarRecebimento() {
    int idxAluno, mes, ano, achou = 0, val = 0;
    Aluno Al;
    Recebimento Rec;
    FILE *arqAluno, *arqRecebimento;

    system("cls");
    printf("\n<==== HITBOXE | REGISTRAR RECEBIMENTO ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) return;
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    if (Al.status_matricula == 0) {
        printf("\n** ERRO: Este aluno nao possui matricula ativa no sistema! **\n");
        system("pause");
        return;
    }

    printf("Mes do Boleto (1-12): ");
    do {
        mes = lerInteiro();
        if (mes < 1 || mes > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mes < 1 || mes > 12);

    printf("Ano do Boleto (ex: 2026): ");
    ano = lerInteiro();

    arqRecebimento = fopen("recebimento.bin", "rb+");
    if (arqRecebimento != NULL) {
        long pos = 0;
        while (val == 0 && fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
            if (strcmp(Rec.cpf_aluno, Al.cpf) == 0 && Rec.mes_referencia == mes && Rec.ano_referencia == ano && Rec.status_pago == 0) {
                achou = 1;
                val = 1;
                
                Rec.status_pago = 1;
                fseek(arqRecebimento, pos, 0);
                fwrite(&Rec, sizeof(Recebimento), 1, arqRecebimento);
                printf("\n** Boleto #%d Pago com sucesso! Valor: R$ %.2f **\n", Rec.id_recebimento, Rec.valor_cobrado);
                
                if (Al.status_matricula == 1) {
                    gerarProximoBoleto(Al.cpf, mes, ano, Rec.valor_cobrado);
                }
            } else {
                pos = ftell(arqRecebimento);
            }
        }
        fclose(arqRecebimento);
    }

    if (!achou) printf("\n** Nenhum boleto pendente (em aberto) localizado para este CPF, mes e ano. **\n");
    system("pause");
}

//<=====RELATÓRIOS GERENCIAIS=====>
void historicoPagamentosAluno() {
    int idxAluno;
    Aluno Al;
    Recebimento Rec;
    FILE *arqAluno, *arqRecebimento;
    int contador = 0;
    char *statusStr;

    system("cls");
    printf("\n<==== HITBOXE | HISTORICO DE PAGAMENTOS POR ALUNO ====>\n");

    idxAluno = selecionarAluno();
    if (idxAluno == -1) return;

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) return;
    fseek(arqAluno, idxAluno * sizeof(Aluno), 0);
    fread(&Al, sizeof(Aluno), 1, arqAluno);
    fclose(arqAluno);

    system("cls");
    printf("\n--------------------------------------------------");
    printf("\n HITBOXE - Historico de Boletos - Aluno: %s", Al.nome);
    printf("\n CPF: %s | Peso: %s | Nivel: %s", Al.cpf, Al.categoria_peso, Al.nivel_experiencia);
    printf("\n--------------------------------------------------\n");

    arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento == NULL) {
        printf("\n** Nenhum registro financeiro encontrado no sistema. **\n");
        system("pause");
        return;
    }

    while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
        if (strcmp(Rec.cpf_aluno, Al.cpf) == 0) {
            contador++;
            if (Rec.status_pago == 0) {
                statusStr = "EM ABERTO";
            } else if (Rec.status_pago == 1) {
                statusStr = "PAGO";
            } else {
                statusStr = "CANCELADO";
            }

            printf("Boleto #%d | Mes/Ano: %02d/%d | Valor: R$ %.2f | Status: %s\n",
                   Rec.id_recebimento, Rec.mes_referencia, Rec.ano_referencia, Rec.valor_cobrado, statusStr);
        }
    }
    fclose(arqRecebimento);

    if (contador == 0) {
        printf("\n** Este aluno nao possui nenhum boleto registrado. **\n");
    }

    printf("\n--------------------------------------------------\n");
    system("pause");
}

void relatorioPagamentosPeriodo() {
    int mesIni, anoIni, mesFim, anoFim;
    int compIni, compFim, compRec;
    int encontrados = 0;
    float totalRecebido = 0.0f;
    Recebimento Rec;
    FILE *arqRecebimento;
    char *statusStr;

    system("cls");
    printf("\n<==== HITBOXE | EXTRATO DE PAGAMENTOS POR PERIODO ====>\n");

    printf("Mes Inicial (1-12): ");
    do {
        mesIni = lerInteiro();
        if (mesIni < 1 || mesIni > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mesIni < 1 || mesIni > 12);

    printf("Ano Inicial (ex: 2026): ");
    anoIni = lerInteiro();

    printf("Mes Final (1-12): ");
    do {
        mesFim = lerInteiro();
        if (mesFim < 1 || mesFim > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mesFim < 1 || mesFim > 12);

    printf("Ano Final (ex: 2027): ");
    anoFim = lerInteiro();

    compIni = anoIni * 100 + mesIni;
    compFim = anoFim * 100 + mesFim;

    if (compIni > compFim) {
        printf("\n** ERRO: A data inicial nao pode ser maior que a data final! **\n");
        system("pause");
        return;
    }

    arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento == NULL) {
        printf("\n** Nenhum registro financeiro encontrado no sistema. **\n");
        system("pause");
        return;
    }

    printf("\n---------------------------------------------------------------");
    printf("\n HITBOXE - EXTRATO (%02d/%d a %02d/%d)", mesIni, anoIni, mesFim, anoFim);
    printf("\n---------------------------------------------------------------\n");

    while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
        compRec = Rec.ano_referencia * 100 + Rec.mes_referencia;
        if (compRec >= compIni && compRec <= compFim) {
            encontrados++;
            if (Rec.status_pago == 0) {
                statusStr = "EM ABERTO";
            } else if (Rec.status_pago == 1) {
                statusStr = "PAGO";
                totalRecebido += Rec.valor_cobrado;
            } else {
                statusStr = "CANCELADO";
            }

            printf("Boleto #%d | CPF: %s | Ref: %02d/%d | R$ %.2f | %s\n",
                   Rec.id_recebimento, Rec.cpf_aluno, Rec.mes_referencia, Rec.ano_referencia, Rec.valor_cobrado, statusStr);
        }
    }
    fclose(arqRecebimento);

    if (encontrados == 0) {
        printf("\n** Nenhum boleto encontrado neste periodo. **\n");
    } else {
        printf("\n---------------------------------------------------------------");
        printf("\nTotal de Boletos: %d | Total Efetivamente Pago: R$ %.2f", encontrados, totalRecebido);
    }
    printf("\n---------------------------------------------------------------\n");
    system("pause");
}

void relatorioAlunosPorStatus() {
    int filtroStatus, encontrados = 0;
    Aluno Al;
    FILE *arqAluno;
    char *tituloStatus;

    system("cls");
    printf("\n<==== HITBOXE | RELATORIO DE ALUNOS POR STATUS ====>\n");
    printf("1. Listar apenas Matricula ATIVA\n");
    printf("2. Listar apenas Matricula INATIVA\n");
    printf("Opcao: ");
    filtroStatus = lerInteiro();

    if (filtroStatus != 1 && filtroStatus != 2) {
        printf("\n** Opcao invalida! **\n");
        system("pause");
        return;
    }

    if (filtroStatus == 2) {
        filtroStatus = 0;
        tituloStatus = "INATIVOS";
    } else {
        tituloStatus = "ATIVOS";
    }

    arqAluno = fopen("aluno.bin", "rb");
    if (arqAluno == NULL) {
        printf("\n** Nenhum aluno cadastrado no sistema. **\n");
        system("pause");
        return;
    }

    printf("\n---------------------------------------------------------------");
    printf("\n HITBOXE - ALUNOS (%s)", tituloStatus);
    printf("\n---------------------------------------------------------------\n");

    while (fread(&Al, sizeof(Aluno), 1, arqAluno) == 1) {
        if (Al.status_matricula == filtroStatus) {
            encontrados++;
            printf("Nome: %s | CPF: %s | Peso: %s | Nivel: %s\n",
                   Al.nome, Al.cpf, Al.categoria_peso, Al.nivel_experiencia);
        }
    }
    fclose(arqAluno);

    if (encontrados == 0) {
        printf("\n** Nenhum aluno encontrado com este status. **\n");
    } else {
        printf("\nTotal listado: %d aluno(s).", encontrados);
    }
    printf("\n---------------------------------------------------------------\n");
    system("pause");
}

void relatorioInadimplentesMesAno() {
    int mes, ano, encontrados = 0;
    float totalAberto = 0.0f;
    Recebimento Rec;
    Aluno Al;
    FILE *arqRecebimento, *arqAluno;
    int idxAl;

    system("cls");
    printf("\n<==== HITBOXE | RELATORIO DE INADIMPLENTES ====>\n");

    printf("Mes de Referencia (1-12): ");
    do {
        mes = lerInteiro();
        if (mes < 1 || mes > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mes < 1 || mes > 12);

    printf("Ano de Referencia (ex: 2026): ");
    ano = lerInteiro();

    arqRecebimento = fopen("recebimento.bin", "rb");
    if (arqRecebimento == NULL) {
        printf("\n** Nenhum registro financeiro encontrado no sistema. **\n");
        system("pause");
        return;
    }

    printf("\n---------------------------------------------------------------");
    printf("\n HITBOXE - BOLETOS EM ABERTO (%02d/%d)", mes, ano);
    printf("\n---------------------------------------------------------------\n");

    while (fread(&Rec, sizeof(Recebimento), 1, arqRecebimento) == 1) {
        if (Rec.mes_referencia == mes && Rec.ano_referencia == ano && Rec.status_pago == 0) {
            encontrados++;
            totalAberto += Rec.valor_cobrado;

            char nomeAluno[100];
            strcpy(nomeAluno, "Aluno Nao Localizado");
            idxAl = buscaAluno(Rec.cpf_aluno);
            if (idxAl != -1) {
                arqAluno = fopen("aluno.bin", "rb");
                if (arqAluno != NULL) {
                    fseek(arqAluno, idxAl * sizeof(Aluno), SEEK_SET);
                    fread(&Al, sizeof(Aluno), 1, arqAluno);
                    fclose(arqAluno);
                    strcpy(nomeAluno, Al.nome);
                }
            }

            printf("Boleto #%d | Aluno: %s (CPF: %s) | Valor: R$ %.2f\n",
                   Rec.id_recebimento, nomeAluno, Rec.cpf_aluno, Rec.valor_cobrado);
        }
    }
    fclose(arqRecebimento);

    if (encontrados == 0) {
        printf("\n** Nenhum boleto em aberto encontrado para %02d/%d! **\n", mes, ano);
    } else {
        printf("\n---------------------------------------------------------------");
        printf("\nTotal de Inadimplentes: %d | Valor Total Pendente: R$ %.2f", encontrados, totalAberto);
    }
    printf("\n---------------------------------------------------------------\n");
    system("pause");
}

//<=====SUB-MENUS=====>
void gerenciarPessoas() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | GERENCIAR PESSOAS ---");
        printf("\n1. Cadastrar Aluno");
        printf("\n2. Cadastrar Instrutor");
        printf("\n3. Consultar Pessoas");
        printf("\n4. Alterar Pessoa");
        printf("\n5. Excluir Pessoa");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarAluno() == 'S'); break;
            case 2: while (cadastrarInstrutor() == 'S'); break;
            case 3: consultarPessoas(); break;
            case 4: alterarPessoa(); break;
            case 5: excluirPessoa(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarAtividades() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | GERENCIAR ATIVIDADES ---");
        printf("\n1. Cadastrar Atividade");
        printf("\n2. Consultar Atividades");
        printf("\n3. Alterar Atividade");
        printf("\n4. Excluir Atividade");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarAtividade() == 'S'); break;
            case 2: consultarAtividade(); break;
            case 3: alterarAtividade(); break;
            case 4: excluirAtividade(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarPacotes() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | GERENCIAR PACOTES ---");
        printf("\n1. Cadastrar Pacote");
        printf("\n2. Consultar Pacotes");
        printf("\n3. Alterar Pacote");
        printf("\n4. Excluir Pacote");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarPacote() == 'S'); break;
            case 2: consultarPacote(); break;
            case 3: alterarPacote(); break;
            case 4: excluirPacote(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarPlanos() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | GERENCIAR PLANOS ---");
        printf("\n1. Cadastrar Plano");
        printf("\n2. Consultar Planos");
        printf("\n3. Alterar Plano");
        printf("\n4. Excluir Plano");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarPlano() == 'S'); break;
            case 2: consultarPlano(); break;
            case 3: alterarPlano(); break;
            case 4: excluirPlano(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarMovimentacoes() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | MOVIMENTACOES E FINANCEIRO ---");
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

void gerenciarRelatorios() {
    int op;
    do {
        system("cls");
        printf("\n--- HITBOXE | RELATORIOS ---");
        printf("\n1. Historico de Pagamentos por Aluno");
        printf("\n2. Extrato de Pagamentos por Periodo");
        printf("\n3. Relatorio de Alunos por Status");
        printf("\n4. Relatorio de Inadimplentes (Mes/Ano)");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: historicoPagamentosAluno(); break;
            case 2: relatorioPagamentosPeriodo(); break;
            case 3: relatorioAlunosPorStatus(); break;
            case 4: relatorioInadimplentesMesAno(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

int main() {
    int opcaoPrincipal;
    
    popularDadosIniciais();

    do {
        menuPrincipal();
        opcaoPrincipal = lerInteiro();

        switch (opcaoPrincipal) {
            case 1: gerenciarPessoas(); break;
            case 2: gerenciarAtividades(); break;
            case 3: gerenciarPacotes(); break;
            case 4: gerenciarPlanos(); break;
            case 5: gerenciarMovimentacoes(); break;
            case 6: gerenciarRelatorios(); break;
            case 0: printf("\nEncerrando o sistema HITBOXE...\n"); break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
