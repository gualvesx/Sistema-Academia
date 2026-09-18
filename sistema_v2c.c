#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#define TF 100

// ==========================================
// FUNÇÕES DE ENTRADA E VALIDAÇÃO BÁSICA
// ==========================================

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

void lerCPF(char cpf[]) {
    int valido, i, tamanho;
    char buffer[50];
    do {
        valido = 1;
        fflush(stdin);
        scanf("%49s", buffer);
        strncpy(cpf, buffer, 14);
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

// ==========================================
// ESTRUTURAS DE DADOS (STRUCTS)
// ==========================================

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

// ==========================================
// FUNÇÕES DE BUSCA
// ==========================================

int buscaAluno(Aluno Al[], int TLA, char cpf[]) {
    int i;
    for (i = 0; i < TLA; i++) {
        if (strcmp(Al[i].cpf, cpf) == 0) return i;
    }
    return -1;
}

int buscaInstrutor(Instrutor Inst[], int TLINST, char cpf[]) {
    int i;
    for (i = 0; i < TLINST; i++) {
        if (strcmp(Inst[i].cpf, cpf) == 0) return i;
    }
    return -1;
}

int buscaAtividade(Atividade Atv[], int TLAT, int id) {
    int i;
    for (i = 0; i < TLAT; i++) {
        if (Atv[i].id == id) return i;
    }
    return -1;
}

int buscaPacote(Pacote Pc[], int TLPC, int id) {
    int i;
    for (i = 0; i < TLPC; i++) {
        if (Pc[i].id == id) return i;
    }
    return -1;
}

int buscaPlano(Plano Pl[], int TLPL, int id) {
    int i;
    for (i = 0; i < TLPL; i++) {
        if (Pl[i].id == id) return i;
    }
    return -1;
}

// ==========================================
// FUNÇÕES DE LISTAGEM (usadas em consultas)
// ==========================================

void listarOpcoesInstrutores(Instrutor Inst[], int TLINST) {
    int i;
    printf("\n--- INSTRUTORES DISPONIVEIS ---");
    if (TLINST == 0) printf("\n(Nenhum instrutor cadastrado)\n");
    else {
        for (i = 0; i < TLINST; i++) {
            printf("\nCPF: %s | Nome: %s | Especialidade: %s", Inst[i].cpf, Inst[i].nome, Inst[i].especialidade);
        }
        printf("\n-------------------------------\n");
    }
}

void listarOpcoesAtividades(Atividade Atv[], int TLAT) {
    int i;
    printf("\n--- ATIVIDADES DISPONIVEIS ---");
    if (TLAT == 0) printf("\n(Nenhuma atividade cadastrada)\n");
    else {
        for (i = 0; i < TLAT; i++) {
            printf("\nID: %d | Nome: %s", Atv[i].id, Atv[i].nome);
        }
        printf("\n------------------------------\n");
    }
}

void listarOpcoesPacotes(Pacote Pc[], int TLPC) {
    int i;
    printf("\n--- PACOTES DISPONIVEIS ---");
    if (TLPC == 0) printf("\n(Nenhum pacote cadastrado)\n");
    else {
        for (i = 0; i < TLPC; i++) {
            printf("\nID: %d | Nome: %s", Pc[i].id, Pc[i].nome);
        }
        printf("\n---------------------------\n");
    }
}

void listarOpcoesPlanos(Plano Pl[], int TLPL) {
    int i;
    printf("\n--- PLANOS DISPONIVEIS ---");
    if (TLPL == 0) printf("\n(Nenhum plano cadastrado)\n");
    else {
        for (i = 0; i < TLPL; i++) {
            printf("\nID: %d | Nome: %s | Tipo: %c | Valor Base: R$ %.2f", Pl[i].id, Pl[i].nome, Pl[i].tipo, Pl[i].valor_base);
        }
        printf("\n--------------------------\n");
    }
}

// ==========================================
// FUNÇÕES DE SELEÇÃO (REUTILIZÁVEIS)
// Retornam o INDICE do item escolhido, ou -1 se cancelar
// ==========================================

int selecionarAluno(Aluno Al[], int TLA) {
    int opSub, i, idx;
    char cpf[20];

    if (TLA == 0) {
        printf("\n** Nenhum aluno cadastrado! **\n");
        system("pause");
        return -1;
    }

    do {
        printf("\n--- SELECIONAR ALUNO ---");
        printf("\n1. Digitar CPF diretamente");
        printf("\n2. Listar todos os alunos (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            printf("CPF do Aluno (apenas numeros): ");
            lerCPF(cpf);
            idx = buscaAluno(Al, TLA, cpf);
            if (idx == -1) {
                printf("** Aluno nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            printf("\n<=== LISTA DE ALUNOS ===>\n");
            for (i = 0; i < TLA; i++) {
                printf("[%d] Nome: %s | CPF: %s | Status: %s\n",
                       i, Al[i].nome, Al[i].cpf,
                       Al[i].status_matricula ? "Ativa" : "Inativa");
            }
            printf("-------------------------\n");
            printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
            idx = lerInteiro();
            if (idx >= 0 && idx < TLA) {
                return idx;
            } else if (idx != -1) {
                printf("** Indice invalido! **\n");
                system("pause");
            }
        }
    } while (opSub != 0);

    return -1;
}

int selecionarInstrutor(Instrutor Inst[], int TLINST) {
    int opSub, i, idx;
    char cpf[20];

    if (TLINST == 0) {
        printf("\n** Nenhum instrutor cadastrado! **\n");
        system("pause");
        return -1;
    }

    do {
        printf("\n--- SELECIONAR INSTRUTOR ---");
        printf("\n1. Digitar CPF diretamente");
        printf("\n2. Listar todos os instrutores (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            printf("CPF do Instrutor (apenas numeros): ");
            lerCPF(cpf);
            idx = buscaInstrutor(Inst, TLINST, cpf);
            if (idx == -1) {
                printf("** Instrutor nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            printf("\n<=== LISTA DE INSTRUTORES ===>\n");
            for (i = 0; i < TLINST; i++) {
                printf("[%d] Nome: %s | CPF: %s | Espec: %s\n",
                       i, Inst[i].nome, Inst[i].cpf, Inst[i].especialidade);
            }
            printf("-----------------------------\n");
            printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
            idx = lerInteiro();
            if (idx >= 0 && idx < TLINST) {
                return idx;
            } else if (idx != -1) {
                printf("** Indice invalido! **\n");
                system("pause");
            }
        }
    } while (opSub != 0);

    return -1;
}

int selecionarAtividade(Atividade Atv[], int TLAT) {
    int opSub, i, idx, id;

    if (TLAT == 0) {
        printf("\n** Nenhuma atividade cadastrada! **\n");
        system("pause");
        return -1;
    }

    do {
        printf("\n--- SELECIONAR ATIVIDADE ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todas as atividades (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            printf("ID da Atividade: ");
            id = lerInteiro();
            idx = buscaAtividade(Atv, TLAT, id);
            if (idx == -1) {
                printf("** Atividade nao encontrada! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            printf("\n<=== LISTA DE ATIVIDADES ===>\n");
            for (i = 0; i < TLAT; i++) {
                printf("[%d] ID: %d | Nome: %s | CPF Instrutor: %s\n",
                       i, Atv[i].id, Atv[i].nome, Atv[i].cpf_instrutor);
            }
            printf("----------------------------\n");
            printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
            idx = lerInteiro();
            if (idx >= 0 && idx < TLAT) {
                return idx;
            } else if (idx != -1) {
                printf("** Indice invalido! **\n");
                system("pause");
            }
        }
    } while (opSub != 0);

    return -1;
}

int selecionarPacote(Pacote Pc[], int TLPC) {
    int opSub, i, j, idx, id;

    if (TLPC == 0) {
        printf("\n** Nenhum pacote cadastrado! **\n");
        system("pause");
        return -1;
    }

    do {
        printf("\n--- SELECIONAR PACOTE ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todos os pacotes (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            printf("ID do Pacote: ");
            id = lerInteiro();
            idx = buscaPacote(Pc, TLPC, id);
            if (idx == -1) {
                printf("** Pacote nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            printf("\n<=== LISTA DE PACOTES ===>\n");
            for (i = 0; i < TLPC; i++) {
                printf("[%d] ID: %d | Nome: %s | Atividades: ",
                       i, Pc[i].id, Pc[i].nome);
                for (j = 0; j < Pc[i].qtd_atividades; j++) {
                    printf("[%d] ", Pc[i].ids_atividades[j]);
                }
                printf("\n");
            }
            printf("-------------------------\n");
            printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
            idx = lerInteiro();
            if (idx >= 0 && idx < TLPC) {
                return idx;
            } else if (idx != -1) {
                printf("** Indice invalido! **\n");
                system("pause");
            }
        }
    } while (opSub != 0);

    return -1;
}

int selecionarPlano(Plano Pl[], int TLPL) {
    int opSub, i, idx, id;

    if (TLPL == 0) {
        printf("\n** Nenhum plano cadastrado! **\n");
        system("pause");
        return -1;
    }

    do {
        printf("\n--- SELECIONAR PLANO ---");
        printf("\n1. Digitar ID diretamente");
        printf("\n2. Listar todos os planos (escolher por numero)");
        printf("\n0. Cancelar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            printf("ID do Plano: ");
            id = lerInteiro();
            idx = buscaPlano(Pl, TLPL, id);
            if (idx == -1) {
                printf("** Plano nao encontrado! **\n");
                system("pause");
            } else {
                return idx;
            }
        } else if (opSub == 2) {
            printf("\n<=== LISTA DE PLANOS ===>\n");
            for (i = 0; i < TLPL; i++) {
                printf("[%d] ID: %d | Nome: %s | Tipo: %c | Valor: R$ %.2f\n",
                       i, Pl[i].id, Pl[i].nome, Pl[i].tipo, Pl[i].valor_base);
            }
            printf("------------------------\n");
            printf("Digite o NUMERO entre colchetes (-1 para cancelar): ");
            idx = lerInteiro();
            if (idx >= 0 && idx < TLPL) {
                return idx;
            } else if (idx != -1) {
                printf("** Indice invalido! **\n");
                system("pause");
            }
        }
    } while (opSub != 0);

    return -1;
}

// ==========================================
// REGRAS FINANCEIRAS
// ==========================================

float calcularDescontoPlano(float valorBase, char tipoPlano) {
    float desconto = 0.0;
    if (tipoPlano == 'T') desconto = valorBase * 0.05f;
    else if (tipoPlano == 'S') desconto = valorBase * 0.10f;
    else if (tipoPlano == 'A') desconto = valorBase * 0.15f;
    return valorBase - desconto;
}

int existeBoleto(Recebimento Rec[], int TLREC, char cpf[], int mes) {
    int i;
    for (i = 0; i < TLREC; i++) {
        if (strcmp(Rec[i].cpf_aluno, cpf) == 0 && Rec[i].mes_referencia == mes) {
            return 1;
        }
    }
    return 0;
}

void gerarProximoBoleto(Recebimento Rec[], int *TLREC, int *prxid_rec, char cpf[], int proximoMes, float valor) {
    if (*TLREC < TF * 5) {
        if (existeBoleto(Rec, *TLREC, cpf, proximoMes)) {
            printf("\n[AVISO] Ja existe boleto para o mes %d. Nao foi gerado duplicado.\n", proximoMes);
            return;
        }
        (*prxid_rec)++;
        Rec[*TLREC].id_recebimento = *prxid_rec;
        strcpy(Rec[*TLREC].cpf_aluno, cpf);
        Rec[*TLREC].mes_referencia = proximoMes;
        Rec[*TLREC].valor_cobrado = valor;
        Rec[*TLREC].status_pago = 0;
        (*TLREC)++;
        printf("\n[BOLETO GERADO] Novo boleto para o mes %d no valor de R$ %.2f\n", proximoMes, valor);
    } else {
        printf("\n** ERRO: Limite de recebimentos atingido! **\n");
    }
}

// ==========================================
// CADASTROS
// ==========================================

char cadastrarAluno(Aluno Al[], int *TLA) {
    char temp_cpf[20];
    int idx;

    system("cls");
    if (*TLA < TF) {
        printf("\n<==== CADASTRO DE ALUNO ====>\n");
        printf("Insira o CPF (apenas numeros): ");
        lerCPF(temp_cpf);

        idx = buscaAluno(Al, *TLA, temp_cpf);
        if (idx != -1) {
            printf("** ERRO: CPF ja cadastrado! **\n");
        } else {
            strcpy(Al[*TLA].cpf, temp_cpf);

            printf("Insira o nome completo: ");
            fflush(stdin);
            gets(Al[*TLA].nome);

            printf("Insira o telefone: ");
            fflush(stdin);
            scanf("%19s", Al[*TLA].telefone);

            Al[*TLA].id_pacote = -1;
            Al[*TLA].id_plano = -1;
            Al[*TLA].status_matricula = 0;

            (*TLA)++;
            printf("\n** Aluno cadastrado com sucesso! **\n");
        }

        printf("Deseja cadastrar outro aluno? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Limite de alunos atingido! **\n");
        return 'N';
    }
}

char cadastrarInstrutor(Instrutor Inst[], int *TLINST) {
    char temp_cpf[20];
    int idx;

    system("cls");
    if (*TLINST < TF) {
        printf("\n<==== CADASTRO DE INSTRUTOR ====>\n");
        printf("Insira o CPF (apenas numeros): ");
        lerCPF(temp_cpf);

        idx = buscaInstrutor(Inst, *TLINST, temp_cpf);
        if (idx != -1) {
            printf("** ERRO: Instrutor ja cadastrado! **\n");
        } else {
            strcpy(Inst[*TLINST].cpf, temp_cpf);

            printf("Insira o nome: ");
            fflush(stdin);
            gets(Inst[*TLINST].nome);

            printf("Insira a especialidade: ");
            fflush(stdin);
            gets(Inst[*TLINST].especialidade);

            (*TLINST)++;
            printf("\n** Instrutor cadastrado com sucesso! **\n");
        }

        printf("Deseja cadastrar outro instrutor? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Limite de instrutores atingido! **\n");
        return 'N';
    }
}

char cadastrarAtividade(Atividade Atv[], Instrutor Inst[], int *TLAT, int TLINST, int *prxid_atv) {
    int idxInst;
    char conf;

    system("cls");
    if (*TLAT < TF) {
        printf("\n<==== CADASTRO DE ATIVIDADE ====>\n");
        (*prxid_atv)++;
        Atv[*TLAT].id = *prxid_atv;

        printf("Insira o nome da Atividade: ");
        fflush(stdin);
        gets(Atv[*TLAT].nome);

        listarOpcoesInstrutores(Inst, TLINST);

        printf("Insira o CPF do Instrutor Responsavel (apenas numeros): ");
        lerCPF(Atv[*TLAT].cpf_instrutor);

        idxInst = buscaInstrutor(Inst, TLINST, Atv[*TLAT].cpf_instrutor);
        if (idxInst == -1) {
            printf("** ATENCAO: Instrutor nao encontrado no cadastro atual. **\n");
            printf("Deseja continuar o cadastro mesmo assim? (S/N): ");
            conf = lerOpcaoSN();
            if (conf == 'N') {
                (*prxid_atv)--;
                printf("\n** Cadastro cancelado. **\n");
                printf("Deseja cadastrar outra atividade? (S/N): ");
                return lerOpcaoSN();
            }
        }

        (*TLAT)++;
        printf("\n** Atividade cadastrada com sucesso! **\n");

        printf("Deseja cadastrar outra atividade? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Limite de atividades atingido! **\n");
        return 'N';
    }
}

char cadastrarPacote(Pacote Pc[], Atividade Atv[], int *TLPC, int TLAT, int *prxid_pc) {
    char continuar = 'S';
    int idxAtiv, jaExiste, k;

    system("cls");
    if (*TLPC < TF) {
        printf("\n<==== CADASTRO DE PACOTE ====>\n");
        (*prxid_pc)++;
        Pc[*TLPC].id = *prxid_pc;
        Pc[*TLPC].qtd_atividades = 0;

        printf("Insira o nome do Pacote: ");
        fflush(stdin);
        gets(Pc[*TLPC].nome);

        while (continuar == 'S' && Pc[*TLPC].qtd_atividades < 10) {
            idxAtiv = selecionarAtividade(Atv, TLAT);

            if (idxAtiv == -1) {
                break;
            }

            jaExiste = 0;
            for (k = 0; k < Pc[*TLPC].qtd_atividades; k++) {
                if (Pc[*TLPC].ids_atividades[k] == Atv[idxAtiv].id) jaExiste = 1;
            }
            if (jaExiste) {
                printf("** AVISO: Atividade ja esta neste pacote! **\n");
            } else {
                Pc[*TLPC].ids_atividades[Pc[*TLPC].qtd_atividades] = Atv[idxAtiv].id;
                Pc[*TLPC].qtd_atividades++;
                printf("** Atividade associada ao pacote! **\n");
            }

            if (Pc[*TLPC].qtd_atividades < 10) {
                printf("Deseja incluir mais uma atividade neste pacote? (S/N): ");
                continuar = lerOpcaoSN();
            }
        }

        (*TLPC)++;
        printf("\n** Pacote cadastrado com sucesso! **\n");

        printf("Deseja cadastrar outro pacote? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Limite de pacotes atingido! **\n");
        return 'N';
    }
}

char cadastrarPlano(Plano Pl[], int *TLPL, int *prxid_pl) {
    char tipo;

    system("cls");
    if (*TLPL < TF) {
        printf("\n<==== CADASTRO DE PLANO ====>\n");
        (*prxid_pl)++;
        Pl[*TLPL].id = *prxid_pl;

        printf("Insira o nome do Plano: ");
        fflush(stdin);
        gets(Pl[*TLPL].nome);

        do {
            printf("Tipo [M-Mensal, T-Trimestral, S-Semestral, A-Anual]: ");
            fflush(stdin);
            scanf("%c", &tipo);
            Pl[*TLPL].tipo = toupper(tipo);
            if (Pl[*TLPL].tipo != 'M' && Pl[*TLPL].tipo != 'T' && Pl[*TLPL].tipo != 'S' && Pl[*TLPL].tipo != 'A') {
                printf("** TIPO INVALIDO! Tente novamente. **\n");
            }
        } while (Pl[*TLPL].tipo != 'M' && Pl[*TLPL].tipo != 'T' && Pl[*TLPL].tipo != 'S' && Pl[*TLPL].tipo != 'A');

        printf("Insira o valor base (R$): ");
        Pl[*TLPL].valor_base = lerFloat();
        while (Pl[*TLPL].valor_base <= 0) {
            printf("** VALOR INVALIDO! Digite um valor positivo: ");
            Pl[*TLPL].valor_base = lerFloat();
        }

        (*TLPL)++;
        printf("\n** Plano cadastrado com sucesso! **\n");

        printf("Deseja cadastrar outro plano? (S/N): ");
        return lerOpcaoSN();
    } else {
        printf("\n** ERRO: Limite de planos atingido! **\n");
        return 'N';
    }
}

// ==========================================
// CONSULTAS
// ==========================================

void consultarPessoas(Aluno Al[], Instrutor Inst[], int TLA, int TLINST) {
    int opCat, opSub, idx, i;
    char cpf[20];

    system("cls");
    printf("\n1. Consultar Alunos\n2. Consultar Instrutores\nEscolha: ");
    do {
        opCat = lerInteiro();
        if (opCat != 1 && opCat != 2) printf("** OPCAO INVALIDA! Escolha 1 ou 2: ");
    } while (opCat != 1 && opCat != 2);

    if (opCat == 1) {
        do {
            printf("\n--- CONSULTA DE ALUNOS ---");
            printf("\n1. Consultar CPF Especifico");
            printf("\n2. Exibir Todos");
            printf("\n0. Voltar");
            printf("\nOpcao: ");
            opSub = lerInteiro();

            if (opSub == 1) {
                if (TLA == 0) { printf("\nNenhum aluno cadastrado.\n"); }
                else {
                    printf("CPF do Aluno (apenas numeros): ");
                    lerCPF(cpf);
                    idx = buscaAluno(Al, TLA, cpf);
                    if (idx != -1) {
                        printf("\nNome: %s | CPF: %s | Tel: %s | Status: %s\n",
                            Al[idx].nome, Al[idx].cpf, Al[idx].telefone,
                            Al[idx].status_matricula ? "Ativa" : "Inativa");
                    } else printf("\nAluno nao encontrado.\n");
                }
            } else if (opSub == 2) {
                if (TLA == 0) { printf("\nNenhum aluno cadastrado.\n"); }
                else {
                    printf("\n<=== LISTA DE TODOS OS ALUNOS ===>\n");
                    for (i = 0; i < TLA; i++) {
                        printf("Nome: %s | CPF: %s | Tel: %s | Status: %s\n",
                            Al[i].nome, Al[i].cpf, Al[i].telefone,
                            Al[i].status_matricula ? "Ativa" : "Inativa");
                    }
                    printf("----------------------------------\n");
                }
            }
        } while (opSub != 0);

    } else if (opCat == 2) {
        do {
            printf("\n--- CONSULTA DE INSTRUTORES ---");
            printf("\n1. Consultar CPF Especifico");
            printf("\n2. Exibir Todos");
            printf("\n0. Voltar");
            printf("\nOpcao: ");
            opSub = lerInteiro();

            if (opSub == 1) {
                if (TLINST == 0) { printf("\nNenhum instrutor cadastrado.\n"); }
                else {
                    printf("CPF do Instrutor (apenas numeros): ");
                    lerCPF(cpf);
                    idx = buscaInstrutor(Inst, TLINST, cpf);
                    if (idx != -1) {
                        printf("\nNome: %s | CPF: %s | Espec: %s\n", Inst[idx].nome, Inst[idx].cpf, Inst[idx].especialidade);
                    } else printf("\nInstrutor nao encontrado.\n");
                }
            } else if (opSub == 2) {
                if (TLINST == 0) { printf("\nNenhum instrutor cadastrado.\n"); }
                else {
                    printf("\n<=== LISTA DE TODOS OS INSTRUTORES ===>\n");
                    for (i = 0; i < TLINST; i++) {
                        printf("Nome: %s | CPF: %s | Espec: %s\n", Inst[i].nome, Inst[i].cpf, Inst[i].especialidade);
                    }
                    printf("---------------------------------------\n");
                }
            }
        } while (opSub != 0);
    }
}

void consultarAtividades(Atividade Atv[], int TLAT) {
    int opSub, i, id;

    system("cls");
    do {
        printf("\n--- CONSULTA DE ATIVIDADES ---");
        printf("\n1. Consultar ID Especifico");
        printf("\n2. Exibir Todas");
        printf("\n0. Voltar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            if (TLAT == 0) { printf("\nNenhuma atividade cadastrada.\n"); }
            else {
                printf("ID da Atividade: ");
                id = lerInteiro();
                i = buscaAtividade(Atv, TLAT, id);
                if (i != -1) {
                    printf("\nID: %d | Nome: %s | CPF Instrutor: %s\n", Atv[i].id, Atv[i].nome, Atv[i].cpf_instrutor);
                } else printf("\nAtividade nao encontrada.\n");
            }
        } else if (opSub == 2) {
            if (TLAT == 0) { printf("\nNenhuma atividade cadastrada.\n"); }
            else {
                printf("\n<=== ATIVIDADES CADASTRADAS ===>\n");
                for (i = 0; i < TLAT; i++) {
                    printf("ID: %d | Nome: %s | CPF Instrutor: %s\n", Atv[i].id, Atv[i].nome, Atv[i].cpf_instrutor);
                }
                printf("--------------------------------\n");
            }
        }
    } while (opSub != 0);
}

void consultarPacotes(Pacote Pc[], int TLPC) {
    int opSub, i, j, id;

    system("cls");
    do {
        printf("\n--- CONSULTA DE PACOTES ---");
        printf("\n1. Consultar ID Especifico");
        printf("\n2. Exibir Todos");
        printf("\n0. Voltar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            if (TLPC == 0) { printf("\nNenhum pacote cadastrado.\n"); }
            else {
                printf("ID do Pacote: ");
                id = lerInteiro();
                i = buscaPacote(Pc, TLPC, id);
                if (i != -1) {
                    printf("\nID: %d | Nome: %s | Atividades: ", Pc[i].id, Pc[i].nome);
                    for (j = 0; j < Pc[i].qtd_atividades; j++) printf("[%d] ", Pc[i].ids_atividades[j]);
                    printf("\n");
                } else printf("\nPacote nao encontrado.\n");
            }
        } else if (opSub == 2) {
            if (TLPC == 0) { printf("\nNenhum pacote cadastrado.\n"); }
            else {
                printf("\n<=== PACOTES CADASTRADOS ===>\n");
                for (i = 0; i < TLPC; i++) {
                    printf("ID: %d | Nome: %s | Atividades: ", Pc[i].id, Pc[i].nome);
                    for (j = 0; j < Pc[i].qtd_atividades; j++) printf("[%d] ", Pc[i].ids_atividades[j]);
                    printf("\n");
                }
                printf("----------------------------\n");
            }
        }
    } while (opSub != 0);
}

void consultarPlanos(Plano Pl[], int TLPL) {
    int opSub, i, id;

    system("cls");
    do {
        printf("\n--- CONSULTA DE PLANOS ---");
        printf("\n1. Consultar ID Especifico");
        printf("\n2. Exibir Todos");
        printf("\n0. Voltar");
        printf("\nOpcao: ");
        opSub = lerInteiro();

        if (opSub == 1) {
            if (TLPL == 0) { printf("\nNenhum plano cadastrado.\n"); }
            else {
                printf("ID do Plano: ");
                id = lerInteiro();
                i = buscaPlano(Pl, TLPL, id);
                if (i != -1) {
                    printf("\nID: %d | Nome: %s | Tipo: %c | Valor Base: R$ %.2f\n", Pl[i].id, Pl[i].nome, Pl[i].tipo, Pl[i].valor_base);
                } else printf("\nPlano nao encontrado.\n");
            }
        } else if (opSub == 2) {
            if (TLPL == 0) { printf("\nNenhum plano cadastrado.\n"); }
            else {
                printf("\n<=== PLANOS CADASTRADOS ===>\n");
                for (i = 0; i < TLPL; i++) {
                    printf("ID: %d | Nome: %s | Tipo: %c | Valor Base: R$ %.2f\n", Pl[i].id, Pl[i].nome, Pl[i].tipo, Pl[i].valor_base);
                }
                printf("---------------------------\n");
            }
        }
    } while (opSub != 0);
}

// ==========================================
// EXCLUSÕES
// ==========================================

void excluirAluno(Aluno Al[], int *TLA, Recebimento Rec[], int TLREC) {
    int idx, j, temDependencia;
    char confirmacao;

    system("cls");
    printf("\n<==== EXCLUIR ALUNO ====>\n");

    idx = selecionarAluno(Al, *TLA);
    if (idx == -1) return;

    if (Al[idx].status_matricula == 1) {
        printf("** AVISO: Aluno possui matricula ATIVA! **\n");
        printf("Deseja realmente excluir mesmo assim? (S/N): ");
        confirmacao = lerOpcaoSN();
        if (confirmacao == 'N') return;
    }

    temDependencia = 0;
    for (j = 0; j < TLREC; j++) {
        if (strcmp(Rec[j].cpf_aluno, Al[idx].cpf) == 0) temDependencia = 1;
    }
    if (temDependencia) {
        printf("** AVISO: Aluno possui boletos/recebimentos registrados! **\n");
        printf("Deseja realmente excluir? (S/N): ");
        confirmacao = lerOpcaoSN();
        if (confirmacao == 'N') return;
    }

    printf("Confirmar exclusao de %s? (S/N): ", Al[idx].nome);
    confirmacao = lerOpcaoSN();
    if (confirmacao == 'S') {
        for (j = idx; j < *TLA - 1; j++) Al[j] = Al[j + 1];
        (*TLA)--;
        printf("\n** Aluno excluido com sucesso! **\n");
    }
    system("pause");
}

void excluirInstrutor(Instrutor Inst[], int *TLINST, Atividade Atv[], int TLAT) {
    int idx, j, temDependencia;
    char confirmacao;

    system("cls");
    printf("\n<==== EXCLUIR INSTRUTOR ====>\n");

    idx = selecionarInstrutor(Inst, *TLINST);
    if (idx == -1) return;

    temDependencia = 0;
    for (j = 0; j < TLAT; j++) {
        if (strcmp(Atv[j].cpf_instrutor, Inst[idx].cpf) == 0) temDependencia = 1;
    }
    if (temDependencia) {
        printf("** AVISO: Instrutor possui atividades vinculadas! **\n");
        printf("Deseja realmente excluir? (S/N): ");
        confirmacao = lerOpcaoSN();
        if (confirmacao == 'N') return;
    }

    printf("Confirmar exclusao de %s? (S/N): ", Inst[idx].nome);
    confirmacao = lerOpcaoSN();
    if (confirmacao == 'S') {
        for (j = idx; j < *TLINST - 1; j++) Inst[j] = Inst[j + 1];
        (*TLINST)--;
        printf("\n** Instrutor excluido com sucesso! **\n");
    }
    system("pause");
}

void excluirPessoa(Aluno Al[], int *TLA, Instrutor Inst[], int *TLINST, Atividade Atv[], int TLAT, Recebimento Rec[], int TLREC) {
    int opCat;

    system("cls");
    printf("\n1. Excluir Aluno\n2. Excluir Instrutor\n0. Voltar\nEscolha: ");
    do {
        opCat = lerInteiro();
        if (opCat < 0 || opCat > 2) printf("** OPCAO INVALIDA! Escolha de 0 a 2: ");
    } while (opCat < 0 || opCat > 2);

    if (opCat == 1) {
        excluirAluno(Al, TLA, Rec, TLREC);
    } else if (opCat == 2) {
        excluirInstrutor(Inst, TLINST, Atv, TLAT);
    }
}

void excluirAtividade(Atividade Atv[], int *TLAT, Pacote Pc[], int TLPC) {
    int idx, j, k, temDependencia;
    char conf;

    system("cls");
    printf("\n<==== EXCLUIR ATIVIDADE ====>\n");

    idx = selecionarAtividade(Atv, *TLAT);
    if (idx == -1) return;

    temDependencia = 0;
    for (k = 0; k < TLPC; k++) {
        for (j = 0; j < Pc[k].qtd_atividades; j++) {
            if (Pc[k].ids_atividades[j] == Atv[idx].id) temDependencia = 1;
        }
    }
    if (temDependencia) {
        printf("** AVISO: Atividade esta vinculada a um ou mais pacotes! **\n");
        printf("Deseja realmente excluir? (S/N): ");
        conf = lerOpcaoSN();
        if (conf == 'N') return;
    }

    printf("Confirmar exclusao de %s? (S/N): ", Atv[idx].nome);
    conf = lerOpcaoSN();
    if (conf == 'S') {
        for (j = idx; j < *TLAT - 1; j++) Atv[j] = Atv[j + 1];
        (*TLAT)--;
        printf("\n** Atividade excluida! **\n");
    }
    system("pause");
}

void excluirPacote(Pacote Pc[], int *TLPC, Aluno Al[], int TLA) {
    int idx, j, temDependencia;
    char conf;

    system("cls");
    printf("\n<==== EXCLUIR PACOTE ====>\n");

    idx = selecionarPacote(Pc, *TLPC);
    if (idx == -1) return;

    temDependencia = 0;
    for (j = 0; j < TLA; j++) {
        if (Al[j].id_pacote == Pc[idx].id && Al[j].status_matricula == 1) temDependencia = 1;
    }
    if (temDependencia) {
        printf("** AVISO: Pacote esta vinculado a alunos com matricula ativa! **\n");
        printf("Deseja realmente excluir? (S/N): ");
        conf = lerOpcaoSN();
        if (conf == 'N') return;
    }

    printf("Confirmar exclusao de %s? (S/N): ", Pc[idx].nome);
    conf = lerOpcaoSN();
    if (conf == 'S') {
        for (j = idx; j < *TLPC - 1; j++) Pc[j] = Pc[j + 1];
        (*TLPC)--;
        printf("\n** Pacote excluido! **\n");
    }
    system("pause");
}

void excluirPlano(Plano Pl[], int *TLPL, Aluno Al[], int TLA) {
    int idx, j, temDependencia;
    char conf;

    system("cls");
    printf("\n<==== EXCLUIR PLANO ====>\n");

    idx = selecionarPlano(Pl, *TLPL);
    if (idx == -1) return;

    temDependencia = 0;
    for (j = 0; j < TLA; j++) {
        if (Al[j].id_plano == Pl[idx].id && Al[j].status_matricula == 1) temDependencia = 1;
    }
    if (temDependencia) {
        printf("** AVISO: Plano esta vinculado a alunos com matricula ativa! **\n");
        printf("Deseja realmente excluir? (S/N): ");
        conf = lerOpcaoSN();
        if (conf == 'N') return;
    }

    printf("Confirmar exclusao de %s? (S/N): ", Pl[idx].nome);
    conf = lerOpcaoSN();
    if (conf == 'S') {
        for (j = idx; j < *TLPL - 1; j++) Pl[j] = Pl[j + 1];
        (*TLPL)--;
        printf("\n** Plano excluido! **\n");
    }
    system("pause");
}

// ==========================================
// MOVIMENTAÇÕES E FINANCEIRO
// ==========================================

void efetuarMatricula(Aluno Al[], int TLA, Plano Pl[], int TLPL, Pacote Pc[], int TLPC, Recebimento Rec[], int *TLREC, int *prxid_rec) {
    int idxAluno, idxPlano, idxPacote, mesInicio;
    float valorFinal;

    system("cls");
    printf("\n<==== EFETUAR MATRICULA ====>\n");

    idxAluno = selecionarAluno(Al, TLA);
    if (idxAluno == -1) return;

    if (Al[idxAluno].status_matricula == 1) {
        printf("** ERRO: Aluno ja possui matricula ATIVA! **\n");
        system("pause");
        return;
    }

    idxPlano = selecionarPlano(Pl, TLPL);
    if (idxPlano == -1) return;

    idxPacote = selecionarPacote(Pc, TLPC);
    if (idxPacote == -1) return;

    printf("Mes inicial da cobranca (1-12): ");
    do {
        mesInicio = lerInteiro();
        if (mesInicio < 1 || mesInicio > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mesInicio < 1 || mesInicio > 12);

    valorFinal = calcularDescontoPlano(Pl[idxPlano].valor_base, Pl[idxPlano].tipo);

    Al[idxAluno].id_plano = Pl[idxPlano].id;
    Al[idxAluno].id_pacote = Pc[idxPacote].id;
    Al[idxAluno].status_matricula = 1;

    printf("\n[MATRICULA REGISTRADA]");
    printf("\nAluno: %s", Al[idxAluno].nome);
    printf("\nPlano: %s | Valor Real Final: R$ %.2f\n", Pl[idxPlano].nome, valorFinal);

    gerarProximoBoleto(Rec, TLREC, prxid_rec, Al[idxAluno].cpf, mesInicio, valorFinal);
    system("pause");
}

void efetuarCancelamento(Aluno Al[], int TLA, Plano Pl[], int TLPL) {
    int idxAluno, idxPlano;
    float valor, multa, reembolso;

    system("cls");
    printf("\n<==== CANCELAMENTO DE MATRICULA ====>\n");

    idxAluno = selecionarAluno(Al, TLA);
    if (idxAluno == -1) return;

    if (Al[idxAluno].status_matricula == 0) {
        printf("** ERRO: Aluno nao possui matricula ativa! **\n");
        system("pause");
        return;
    }

    idxPlano = buscaPlano(Pl, TLPL, Al[idxAluno].id_plano);
    if (idxPlano == -1) {
        printf("\n** AVISO: Plano vinculado nao existe mais. Cancelamento sera aplicado sem calculo de multa. **\n");
    } else {
        valor = Pl[idxPlano].valor_base;

        if (Pl[idxPlano].tipo != 'M') {
            multa = valor * 0.30f;
            reembolso = valor * 0.70f;
            printf("\nMulta de Retencao (30%%): R$ %.2f", multa);
            printf("\nValor Reembolsado ao Aluno (70%%): R$ %.2f\n", reembolso);
        } else {
            printf("\nPlano Mensal cancelado sem taxas adicionais.\n");
        }
    }

    Al[idxAluno].status_matricula = 0;
    printf("\n** Matricula cancelada com sucesso! **\n");
    system("pause");
}

void efetuarRecebimento(Recebimento Rec[], int *TLREC, int *prxid_rec, Aluno Al[], int TLA) {
    int idxAluno, mes, i, achou = 0;

    system("cls");
    printf("\n<==== REGISTRAR RECEBIMENTO ====>\n");

    idxAluno = selecionarAluno(Al, TLA);
    if (idxAluno == -1) return;

    printf("Mes do Boleto (1-12): ");
    do {
        mes = lerInteiro();
        if (mes < 1 || mes > 12) printf("** MES INVALIDO! Digite de 1 a 12: ");
    } while (mes < 1 || mes > 12);

    i = 0;
    while (i < *TLREC && achou == 0) {
        if (strcmp(Rec[i].cpf_aluno, Al[idxAluno].cpf) == 0 && Rec[i].mes_referencia == mes) {
            achou = 1;
            if (Rec[i].status_pago == 1) {
                printf("\n** Boleto ja pago anteriormente! **\n");
            } else {
                Rec[i].status_pago = 1;
                printf("\n** Boleto #%d Pago com sucesso! Valor: R$ %.2f **\n", Rec[i].id_recebimento, Rec[i].valor_cobrado);
                if (mes < 12) {
                    gerarProximoBoleto(Rec, TLREC, prxid_rec, Al[idxAluno].cpf, mes + 1, Rec[i].valor_cobrado);
                } else {
                    printf("\n[INFO] Mes 12 pago. Proximo boleto devera ser gerado no proximo ano.\n");
                }
            }
        }
        i++;
    }

    if (!achou) printf("\n** Nenhum boleto pendente localizado para este CPF e mes. **\n");
    system("pause");
}

// ==========================================
// GERENCIADORES (SUBMENUS)
// ==========================================

void gerenciarPessoas(Aluno Al[], int *TLA, Instrutor Inst[], int *TLINST, Atividade Atv[], int TLAT, Recebimento Rec[], int TLREC) {
    int op;
    do {
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
            case 1: while (cadastrarAluno(Al, TLA) == 'S'); break;
            case 2: while (cadastrarInstrutor(Inst, TLINST) == 'S'); break;
            case 3: consultarPessoas(Al, Inst, *TLA, *TLINST); break;
            case 4: excluirPessoa(Al, TLA, Inst, TLINST, Atv, TLAT, Rec, TLREC); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarAtividades(Atividade Atv[], int *TLAT, Instrutor Inst[], int TLINST, int *prxid_atv, Pacote Pc[], int TLPC) {
    int op;
    do {
        system("cls");
        printf("\n--- GERENCIAR ATIVIDADES ---");
        printf("\n1. Cadastrar Atividade");
        printf("\n2. Consultar Atividades");
        printf("\n3. Excluir Atividade");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarAtividade(Atv, Inst, TLAT, TLINST, prxid_atv) == 'S'); break;
            case 2: consultarAtividades(Atv, *TLAT); break;
            case 3: excluirAtividade(Atv, TLAT, Pc, TLPC); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarPacotes(Pacote Pc[], int *TLPC, Atividade Atv[], int TLAT, int *prxid_pc, Aluno Al[], int TLA) {
    int op;
    do {
        system("cls");
        printf("\n--- GERENCIAR PACOTES ---");
        printf("\n1. Cadastrar Pacote");
        printf("\n2. Consultar Pacotes");
        printf("\n3. Excluir Pacote");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarPacote(Pc, Atv, TLPC, TLAT, prxid_pc) == 'S'); break;
            case 2: consultarPacotes(Pc, *TLPC); break;
            case 3: excluirPacote(Pc, TLPC, Al, TLA); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarPlanos(Plano Pl[], int *TLPL, int *prxid_pl, Aluno Al[], int TLA) {
    int op;
    do {
        system("cls");
        printf("\n--- GERENCIAR PLANOS ---");
        printf("\n1. Cadastrar Plano");
        printf("\n2. Consultar Planos");
        printf("\n3. Excluir Plano");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: while (cadastrarPlano(Pl, TLPL, prxid_pl) == 'S'); break;
            case 2: consultarPlanos(Pl, *TLPL); break;
            case 3: excluirPlano(Pl, TLPL, Al, TLA); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

void gerenciarMovimentacoes(Aluno Al[], int TLA, Plano Pl[], int TLPL, Pacote Pc[], int TLPC, Recebimento Rec[], int *TLREC, int *prxid_rec) {
    int op;
    do {
        system("cls");
        printf("\n--- MOVIMENTACOES E FINANCEIRO ---");
        printf("\n1. Efetuar Matricula");
        printf("\n2. Efetuar Cancelamento");
        printf("\n3. Registrar Recebimento");
        printf("\n0. Voltar ao Menu Principal");
        printf("\nOpcao: ");
        op = lerInteiro();

        switch (op) {
            case 1: efetuarMatricula(Al, TLA, Pl, TLPL, Pc, TLPC, Rec, TLREC, prxid_rec); break;
            case 2: efetuarCancelamento(Al, TLA, Pl, TLPL); break;
            case 3: efetuarRecebimento(Rec, TLREC, prxid_rec, Al, TLA); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); system("pause");
        }
    } while (op != 0);
}

// ==========================================
// MENU PRINCIPAL
// ==========================================

void exibirMenuPrincipal() {
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

main() {
    Aluno Al[TF];
    Instrutor Inst[TF];
    Atividade Atv[TF];
    Pacote Pc[TF];
    Plano Pl[TF];
    Recebimento Rec[TF * 5];

    int TLA = 0, TLINST = 0, TLAT = 0, TLPC = 0, TLPL = 0, TLREC = 0;
    int prxid_atv = 0, prxid_pc = 0, prxid_pl = 0, prxid_rec = 0;
    int opcaoPrincipal;

    do {
        exibirMenuPrincipal();
        opcaoPrincipal = lerInteiro();

        switch (opcaoPrincipal) {
            case 1:
                gerenciarPessoas(Al, &TLA, Inst, &TLINST, Atv, TLAT, Rec, TLREC);
                break;
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
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
        }
    } while (opcaoPrincipal != 0);
}
