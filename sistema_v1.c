#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TF 100

// ==========================================
// 1. ESTRUTURAS DE DADOS (STRUCTS)
// ==========================================

typedef struct {
    char cpf[15];
    char nome[100];
    char telefone[20];
    int id_pacote;
    int id_plano;
    int status_matricula; // 1 = Ativa, 0 = Cancelada
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
    char tipo; // 'M' - Mensal, 'T' - Trimestral, 'S' - Semestral, 'A' - Anual
    float valor_base;
} Plano;

typedef struct {
    int id_recebimento;
    char cpf_aluno[15];
    int mes_referencia;
    float valor_cobrado;
    int status_pago; // 1 = Pago, 0 = Aberto/Pendente
} Recebimento;

// ==========================================
// 2. FUNCOES AUXILIARES DE BUSCA E LISTAGEM
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

void listarOpcoesInstrutores(Instrutor Inst[], int TLINST) {
    int i;
    printf("\n--- INSTRUTORES DISPONIVEIS ---");
    if (TLINST == 0) {
        printf("\n(Nenhum instrutor cadastrado)\n");
    } else {
        for (i = 0; i < TLINST; i++) {
            printf("\nCPF: %s | Nome: %s | Especialidade: %s", Inst[i].cpf, Inst[i].nome, Inst[i].especialidade);
        }
        printf("\n-------------------------------\n");
    }
}

void listarOpcoesAtividades(Atividade Atv[], int TLAT) {
    int i;
    printf("\n--- ATIVIDADES DISPONIVEIS ---");
    if (TLAT == 0) {
        printf("\n(Nenhuma atividade cadastrada)\n");
    } else {
        for (i = 0; i < TLAT; i++) {
            printf("\nID: %d | Nome: %s", Atv[i].id, Atv[i].nome);
        }
        printf("\n------------------------------\n");
    }
}

void listarOpcoesPacotes(Pacote Pc[], int TLPC) {
    int i;
    printf("\n--- PACOTES DISPONIVEIS ---");
    if (TLPC == 0) {
        printf("\n(Nenhum pacote cadastrado)\n");
    } else {
        for (i = 0; i < TLPC; i++) {
            printf("\nID: %d | Nome: %s", Pc[i].id, Pc[i].nome);
        }
        printf("\n---------------------------\n");
    }
}

void listarOpcoesPlanos(Plano Pl[], int TLPL) {
    int i;
    printf("\n--- PLANOS DISPONIVEIS ---");
    if (TLPL == 0) {
        printf("\n(Nenhum plano cadastrado)\n");
    } else {
        for (i = 0; i < TLPL; i++) {
            printf("\nID: %d | Nome: %s | Tipo: %c | Valor Base: R$ %.2f", Pl[i].id, Pl[i].nome, Pl[i].tipo, Pl[i].valor_base);
        }
        printf("\n--------------------------\n");
    }
}

// ==========================================
// 3. REGRAS FINANCEIRAS DE SUPORTE
// ==========================================

float calcularDescontoPlano(float valorBase, char tipoPlano) {
    float desconto = 0.0;
    if (tipoPlano == 'T' || tipoPlano == 't') desconto = valorBase * 0.05f;
    else if (tipoPlano == 'S' || tipoPlano == 's') desconto = valorBase * 0.10f;
    else if (tipoPlano == 'A' || tipoPlano == 'a') desconto = valorBase * 0.15f;
    return valorBase - desconto;
}

void gerarProximoBoleto(Recebimento Rec[], int *TLREC, int *prxid_rec, char cpf[], int proximoMes, float valor) {
    if (*TLREC < TF) {
        (*prxid_rec)++;
        Rec[*TLREC].id_recebimento = *prxid_rec;
        strcpy(Rec[*TLREC].cpf_aluno, cpf);
        Rec[*TLREC].mes_referencia = proximoMes;
        Rec[*TLREC].valor_cobrado = valor;
        Rec[*TLREC].status_pago = 0; // Aberto
        (*TLREC)++;
        printf("\n[BOLETO GERADO] Novo boleto para o mes %d no valor de R$ %.2f\n", proximoMes, valor);
    }
}

// ==========================================
// 4. CADASTROS
// ==========================================

char cadastrarAluno(Aluno Al[], int *TLA) {
    char temp_cpf[20], op;
    int idx;

    if (*TLA < TF) {
        printf("\n\n<==== CADASTRO DE ALUNO ====>\n");
        printf("Insira o CPF: ");
        fflush(stdin);
        gets(temp_cpf);

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
            gets(Al[*TLA].telefone);

            Al[*TLA].id_pacote = -1;
            Al[*TLA].id_plano = -1;
            Al[*TLA].status_matricula = 0; // Inativa ate matricular

            (*TLA)++;
            printf("\n** Aluno cadastrado com sucesso! **\n");
        }

        printf("Deseja cadastrar outro aluno? (S/N): ");
        fflush(stdin);
        scanf("%c", &op);
        return toupper(op);
    } else {
        printf("\n** ERRO: Limite de alunos atingido! **\n");
        return 'N';
    }
}

char cadastrarInstrutor(Instrutor Inst[], int *TLINST) {
    char temp_cpf[20], op;
    int idx;

    if (*TLINST < TF) {
        printf("\n\n<==== CADASTRO DE INSTRUTOR ====>\n");
        printf("Insira o CPF: ");
        fflush(stdin);
        gets(temp_cpf);

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
        fflush(stdin);
        scanf("%c", &op);
        return toupper(op);
    } else {
        printf("\n** ERRO: Limite de instrutores atingido! **\n");
        return 'N';
    }
}

char cadastrarAtividade(Atividade Atv[], Instrutor Inst[], int *TLAT, int TLINST, int *prxid_atv) {
    char op;
    int idxInst;

    if (*TLAT < TF) {
        printf("\n\n<==== CADASTRO DE ATIVIDADE ====>\n");
        (*prxid_atv)++;
        Atv[*TLAT].id = *prxid_atv;

        printf("Insira o nome da Atividade: ");
        fflush(stdin);
        gets(Atv[*TLAT].nome);

        // Exibe lista de instrutores para orientar a escolha
        listarOpcoesInstrutores(Inst, TLINST);

        printf("Insira o CPF do Instrutor Responsavel: ");
        fflush(stdin);
        gets(Atv[*TLAT].cpf_instrutor);

        idxInst = buscaInstrutor(Inst, TLINST, Atv[*TLAT].cpf_instrutor);

        if (idxInst == -1) {
            printf("** ATENCAO: Instrutor nao encontrado no cadastro atual. **\n");
        }

        (*TLAT)++;
        printf("\n** Atividade cadastrada com sucesso! **\n");

        printf("Deseja cadastrar outra atividade? (S/N): ");
        fflush(stdin);
        scanf("%c", &op);
        return toupper(op);
    } else {
        printf("\n** ERRO: Limite de atividades atingido! **\n");
        return 'N';
    }
}

char cadastrarPacote(Pacote Pc[], Atividade Atv[], int *TLPC, int TLAT, int *prxid_pc) {
    char op, continuar = 'S';
    int tempId, idxAtiv;

    if (*TLPC < TF) {
        printf("\n\n<==== CADASTRO DE PACOTE ====>\n");
        (*prxid_pc)++;
        Pc[*TLPC].id = *prxid_pc;
        Pc[*TLPC].qtd_atividades = 0;

        printf("Insira o nome do Pacote: ");
        fflush(stdin);
        gets(Pc[*TLPC].nome);

        // Exibe lista de atividades para orientar a escolha
        listarOpcoesAtividades(Atv, TLAT);

        while ((continuar == 'S' || continuar == 's') && Pc[*TLPC].qtd_atividades < 10) {
            printf("Insira o ID da Atividade para incluir: ");
            scanf("%d", &tempId);
            idxAtiv = buscaAtividade(Atv, TLAT, tempId);

            if (idxAtiv != -1) {
                Pc[*TLPC].ids_atividades[Pc[*TLPC].qtd_atividades] = tempId;
                Pc[*TLPC].qtd_atividades++;
                printf("** Atividade associada ao pacote! **\n");
            } else {
                printf("** ERRO: ID de atividade invalido! **\n");
            }

            if (Pc[*TLPC].qtd_atividades < 10) {
                printf("Deseja incluir mais uma atividade neste pacote? (S/N): ");
                fflush(stdin);
                scanf("%c", &continuar);
            }
        }

        (*TLPC)++;
        printf("\n** Pacote cadastrado com sucesso! **\n");

        printf("Deseja cadastrar outro pacote? (S/N): ");
        fflush(stdin);
        scanf("%c", &op);
        return toupper(op);
    } else {
        printf("\n** ERRO: Limite de pacotes atingido! **\n");
        return 'N';
    }
}

char cadastrarPlano(Plano Pl[], int *TLPL, int *prxid_pl) {
    char op;

    if (*TLPL < TF) {
        printf("\n\n<==== CADASTRO DE PLANO ====>\n");
        (*prxid_pl)++;
        Pl[*TLPL].id = *prxid_pl;

        printf("Insira o nome do Plano: ");
        fflush(stdin);
        gets(Pl[*TLPL].nome);

        printf("Tipo [M-Mensal, T-Trimestral, S-Semestral, A-Anual]: ");
        fflush(stdin);
        scanf("%c", &Pl[*TLPL].tipo);

        printf("Insira o valor base (R$): ");
        scanf("%f", &Pl[*TLPL].valor_base);

        (*TLPL)++;
        printf("\n** Plano cadastrado com sucesso! **\n");

        printf("Deseja cadastrar outro plano? (S/N): ");
        fflush(stdin);
        scanf("%c", &op);
        return toupper(op);
    } else {
        printf("\n** ERRO: Limite de planos atingido! **\n");
        return 'N';
    }
}

// ==========================================
// 5. CONSULTAS SEM ACENTUACAO
// ==========================================

void consultarPessoas(Aluno Al[], Instrutor Inst[], int TLA, int TLINST) {
    int opCat, opSub, i;
    char cpf[15];

    printf("\n1. Consultar Alunos\n2. Consultar Instrutores\nEscolha: ");
    scanf("%d", &opCat);

    if (opCat == 1) {
        do {
            printf("\n--- CONSULTA DE ALUNOS ---");
            printf("\n1. Consultar CPF Especifico\n2. Exibir Todos\n0. Voltar ao Menu Pessoas\nOpcao: ");
            scanf("%d", &opSub);

            if (opSub == 1) {
                if (TLA == 0) { printf("\nNenhum aluno cadastrado.\n"); }
                else {
                    printf("CPF do Aluno: ");
                    fflush(stdin);
                    gets(cpf);
                    i = buscaAluno(Al, TLA, cpf);
                    if (i != -1) {
                        printf("\nNome: %s | CPF: %s | Tel: %s | Status: %s\n", 
                            Al[i].nome, Al[i].cpf, Al[i].telefone, Al[i].status_matricula ? "Ativa" : "Inativa");
                    } else printf("\nAluno nao encontrado.\n");
                }
            } else if (opSub == 2) {
                if (TLA == 0) { printf("\nNenhum aluno cadastrado.\n"); }
                else {
                    printf("\n<=== LISTA DE TODOS OS ALUNOS ===>\n");
                    for (i = 0; i < TLA; i++) {
                        printf("Nome: %s | CPF: %s | Tel: %s | Status: %s\n", 
                            Al[i].nome, Al[i].cpf, Al[i].telefone, Al[i].status_matricula ? "Ativa" : "Inativa");
                    }
                    printf("----------------------------------\n");
                }
            }
        } while (opSub != 0);

    } else if (opCat == 2) {
        do {
            printf("\n--- CONSULTA DE INSTRUTORES ---");
            printf("\n1. Consultar CPF Especifico\n2. Exibir Todos\n0. Voltar ao Menu Pessoas\nOpcao: ");
            scanf("%d", &opSub);

            if (opSub == 1) {
                if (TLINST == 0) { printf("\nNenhum instrutor cadastrado.\n"); }
                else {
                    printf("CPF do Instrutor: ");
                    fflush(stdin);
                    gets(cpf);
                    i = buscaInstrutor(Inst, TLINST, cpf);
                    if (i != -1) {
                        printf("\nNome: %s | CPF: %s | Espec: %s\n", Inst[i].nome, Inst[i].cpf, Inst[i].especialidade);
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

    do {
        printf("\n--- CONSULTA DE ATIVIDADES ---");
        printf("\n1. Consultar ID Especifico\n2. Exibir Todas\n0. Voltar ao Menu Atividades\nOpcao: ");
        scanf("%d", &opSub);

        if (opSub == 1) {
            if (TLAT == 0) { printf("\nNenhuma atividade cadastrada.\n"); }
            else {
                printf("ID da Atividade: ");
                scanf("%d", &id);
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

    do {
        printf("\n--- CONSULTA DE PACOTES ---");
        printf("\n1. Consultar ID Especifico\n2. Exibir Todos\n0. Voltar ao Menu Pacotes\nOpcao: ");
        scanf("%d", &opSub);

        if (opSub == 1) {
            if (TLPC == 0) { printf("\nNenhum pacote cadastrado.\n"); }
            else {
                printf("ID do Pacote: ");
                scanf("%d", &id);
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

    do {
        printf("\n--- CONSULTA DE PLANOS ---");
        printf("\n1. Consultar ID Especifico\n2. Exibir Todos\n0. Voltar ao Menu Planos\nOpcao: ");
        scanf("%d", &opSub);

        if (opSub == 1) {
            if (TLPL == 0) { printf("\nNenhum plano cadastrado.\n"); }
            else {
                printf("ID do Plano: ");
                scanf("%d", &id);
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
// 6. EXCLUSOES
// ==========================================

void excluirPessoa(Aluno Al[], int *TLA, Instrutor Inst[], int *TLINST) {
    char cpf[15], confirmacao;
    int op, idx, j;

    printf("\n1. Excluir Aluno\n2. Excluir Instrutor\nEscolha: ");
    scanf("%d", &op);

    if (op == 1) {
        printf("CPF do Aluno a excluir: ");
        fflush(stdin);
        gets(cpf);
        idx = buscaAluno(Al, *TLA, cpf);
        if (idx != -1) {
            printf("Confirmar exclusao de %s? (S/N): ", Al[idx].nome);
            fflush(stdin);
            scanf("%c", &confirmacao);
            if (toupper(confirmacao) == 'S') {
                for (j = idx; j < *TLA - 1; j++) Al[j] = Al[j + 1];
                (*TLA)--;
                printf("\n** Aluno excluido com sucesso! **\n");
            }
        } else printf("\nAluno nao encontrado.\n");
    } else if (op == 2) {
        printf("CPF do Instrutor a excluir: ");
        fflush(stdin);
        gets(cpf);
        idx = buscaInstrutor(Inst, *TLINST, cpf);
        if (idx != -1) {
            printf("Confirmar exclusao de %s? (S/N): ", Inst[idx].nome);
            fflush(stdin);
            scanf("%c", &confirmacao);
            if (toupper(confirmacao) == 'S') {
                for (j = idx; j < *TLINST - 1; j++) Inst[j] = Inst[j + 1];
                (*TLINST)--;
                printf("\n** Instrutor excluido com sucesso! **\n");
            }
        } else printf("\nInstrutor nao encontrado.\n");
    }
}

void excluirAtividade(Atividade Atv[], int *TLAT) {
    int id, idx, j;
    char conf;
    printf("ID da Atividade a excluir: ");
    scanf("%d", &id);
    idx = buscaAtividade(Atv, *TLAT, id);
    if (idx != -1) {
        printf("Confirmar exclusao? (S/N): ");
        fflush(stdin);
        scanf("%c", &conf);
        if (toupper(conf) == 'S') {
            for (j = idx; j < *TLAT - 1; j++) Atv[j] = Atv[j + 1];
            (*TLAT)--;
            printf("\n** Atividade excluida! **\n");
        }
    } else printf("\nAtividade nao encontrada.\n");
}

void excluirPacote(Pacote Pc[], int *TLPC) {
    int id, idx, j;
    char conf;
    printf("ID do Pacote a excluir: ");
    scanf("%d", &id);
    idx = buscaPacote(Pc, *TLPC, id);
    if (idx != -1) {
        printf("Confirmar exclusao? (S/N): ");
        fflush(stdin);
        scanf("%c", &conf);
        if (toupper(conf) == 'S') {
            for (j = idx; j < *TLPC - 1; j++) Pc[j] = Pc[j + 1];
            (*TLPC)--;
            printf("\n** Pacote excluido! **\n");
        }
    } else printf("\nPacote nao encontrado.\n");
}

void excluirPlano(Plano Pl[], int *TLPL) {
    int id, idx, j;
    char conf;
    printf("ID do Plano a excluir: ");
    scanf("%d", &id);
    idx = buscaPlano(Pl, *TLPL, id);
    if (idx != -1) {
        printf("Confirmar exclusao? (S/N): ");
        fflush(stdin);
        scanf("%c", &conf);
        if (toupper(conf) == 'S') {
            for (j = idx; j < *TLPL - 1; j++) Pl[j] = Pl[j + 1];
            (*TLPL)--;
            printf("\n** Plano excluido! **\n");
        }
    } else printf("\nPlano nao encontrado.\n");
}

// ==========================================
// 7. MOVIMENTACOES E RECEBIMENTOS
// ==========================================

void efetuarMatricula(Aluno Al[], int TLA, Plano Pl[], int TLPL, Pacote Pc[], int TLPC, Recebimento Rec[], int *TLREC, int *prxid_rec) {
    char cpf[15];
    int idPlano, idPacote, idxAluno, idxPlano, idxPacote, mesInicio;
    float valorFinal;

    printf("\n<==== EFETUAR MATRICULA ====>\n");
    printf("CPF do Aluno: ");
    fflush(stdin);
    gets(cpf);
    idxAluno = buscaAluno(Al, TLA, cpf);

    if (idxAluno == -1) { printf("** ERRO: Aluno nao encontrado! **\n"); return; }

    // Exibe lista de planos para orientar a escolha
    listarOpcoesPlanos(Pl, TLPL);
    printf("ID do Plano: ");
    scanf("%d", &idPlano);
    idxPlano = buscaPlano(Pl, TLPL, idPlano);

    if (idxPlano == -1) { printf("** ERRO: Plano invalido! **\n"); return; }

    // Exibe lista de pacotes para orientar a escolha
    listarOpcoesPacotes(Pc, TLPC);
    printf("ID do Pacote: ");
    scanf("%d", &idPacote);
    idxPacote = buscaPacote(Pc, TLPC, idPacote);

    if (idxPacote == -1) { printf("** ERRO: Pacote invalido! **\n"); return; }

    printf("Mes inicial da cobranca (1-12): ");
    scanf("%d", &mesInicio);

    valorFinal = calcularDescontoPlano(Pl[idxPlano].valor_base, Pl[idxPlano].tipo);

    Al[idxAluno].id_plano = idPlano;
    Al[idxAluno].id_pacote = idPacote;
    Al[idxAluno].status_matricula = 1; // Ativa

    printf("\n[MATRICULA REGISTRADA]");
    printf("\nPlano: %s | Valor Real Final: R$ %.2f\n", Pl[idxPlano].nome, valorFinal);

    gerarProximoBoleto(Rec, TLREC, prxid_rec, cpf, mesInicio, valorFinal);
}

void efetuarCancelamento(Aluno Al[], int TLA, Plano Pl[], int TLPL) {
    char cpf[15];
    int idxAluno, idxPlano;
    float valor, multa, reembolso;

    printf("\n<==== CANCELAMENTO DE MATRICULA ====>\n");
    printf("CPF do Aluno: ");
    fflush(stdin);
    gets(cpf);
    idxAluno = buscaAluno(Al, TLA, cpf);

    if (idxAluno == -1 || Al[idxAluno].status_matricula == 0) {
        printf("** ERRO: Aluno sem matricula ativa! **\n");
        return;
    }

    idxPlano = buscaPlano(Pl, TLPL, Al[idxAluno].id_plano);
    valor = Pl[idxPlano].valor_base;

    if (toupper(Pl[idxPlano].tipo) != 'M') {
        multa = valor * 0.30f;
        reembolso = valor * 0.70f;
        printf("\nMulta de Retencao (30%%): R$ %.2f", multa);
        printf("\nValor Reembolsado ao Aluno (70%%): R$ %.2f\n", reembolso);
    } else {
        printf("\nPlano Mensal cancelado sem taxas adicionais.\n");
    }

    Al[idxAluno].status_matricula = 0;
    printf("\n** Matricula cancelada com sucesso! **\n");
}

void efetuarRecebimento(Recebimento Rec[], int TLREC, int *prxid_rec) {
    char cpf[15];
    int mes, i, achou = 0;

    printf("\n<==== REGISTRAR RECEBIMENTO ====>\n");
    printf("CPF do Aluno: ");
    fflush(stdin);
    gets(cpf);
    printf("Mes do Boleto: ");
    scanf("%d", &mes);

    for (i = 0; i < TLREC; i++) {
        if (strcmp(Rec[i].cpf_aluno, cpf) == 0 && Rec[i].mes_referencia == mes) {
            achou = 1;
            if (Rec[i].status_pago == 1) {
                printf("\n** Boleto ja pago anteriormente! **\n");
            } else {
                Rec[i].status_pago = 1;
                printf("\n** Boleto #%d Pago com sucesso! Valor: R$ %.2f **\n", Rec[i].id_recebimento, Rec[i].valor_cobrado);
                gerarProximoBoleto(Rec, &TLREC, prxid_rec, cpf, mes + 1, Rec[i].valor_cobrado);
            }
            break;
        }
    }
    if (!achou) printf("\n** Nenhum boleto pendente localizado. **\n");
}

void relatoriosGerais(Recebimento Rec[], int TLREC, Aluno Al[], int TLA) {
    int op, i, mesBusca;
    char cpf[15];

    printf("\n<=== RELATORIOS GERAIS ===>\n");
    printf("1. Extrato de Recebimentos\n2. Status das Matriculas\n3. Pagamentos por CPF\n4. Pagamentos por Mes\nEscolha: ");
    scanf("%d", &op);

    if (op == 1) {
        for (i = 0; i < TLREC; i++) {
            printf("ID: %d | CPF: %s | Mes: %d | R$ %.2f | Status: %s\n",
                Rec[i].id_recebimento, Rec[i].cpf_aluno, Rec[i].mes_referencia, Rec[i].valor_cobrado, Rec[i].status_pago ? "PAGO" : "ABERTO");
        }
    } else if (op == 2) {
        for (i = 0; i < TLA; i++) {
            printf("Nome: %s | CPF: %s | Matricula: %s\n", Al[i].nome, Al[i].cpf, Al[i].status_matricula ? "ATIVA" : "INATIVA");
        }
    } else if (op == 3) {
        printf("CPF do Aluno: ");
        fflush(stdin);
        gets(cpf);
        for (i = 0; i < TLREC; i++) {
            if (strcmp(Rec[i].cpf_aluno, cpf) == 0) {
                printf("Mes: %d | Valor: R$ %.2f | Status: %s\n", Rec[i].mes_referencia, Rec[i].valor_cobrado, Rec[i].status_pago ? "PAGO" : "ABERTO");
            }
        }
    } else if (op == 4) {
        printf("Mes: ");
        scanf("%d", &mesBusca);
        for (i = 0; i < TLREC; i++) {
            if (Rec[i].mes_referencia == mesBusca) {
                printf("CPF: %s | Valor: R$ %.2f | Status: %s\n", Rec[i].cpf_aluno, Rec[i].valor_cobrado, Rec[i].status_pago ? "PAGO" : "ABERTO");
            }
        }
    }
}

// ==========================================
// 8. MENU PRINCIPAL
// ==========================================

int main() {
    int opPrincipal, opSub;
    char opContinuar;

    Aluno Al[TF]; int TLA = 0;
    Instrutor Inst[TF]; int TLINST = 0;
    Atividade Atv[TF]; int TLAT = 0, prxid_atv = 0;
    Pacote Pc[TF]; int TLPC = 0, prxid_pc = 0;
    Plano Pl[TF]; int TLPL = 0, prxid_pl = 0;
    Recebimento Rec[TF]; int TLREC = 0, prxid_rec = 0;

    do {
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
        scanf("%d", &opPrincipal);

        switch (opPrincipal) {
            case 1:
                do {
                    printf("\n--- MENU PESSOAS ---");
                    printf("\n1. Cadastrar Aluno\n2. Cadastrar Instrutor\n3. Consultar Pessoas\n4. Excluir Pessoa\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if (opSub == 1) {
                        do { opContinuar = cadastrarAluno(Al, &TLA); } while (opContinuar == 'S');
                    } else if (opSub == 2) {
                        do { opContinuar = cadastrarInstrutor(Inst, &TLINST); } while (opContinuar == 'S');
                    } else if (opSub == 3) consultarPessoas(Al, Inst, TLA, TLINST);
                    else if (opSub == 4) excluirPessoa(Al, &TLA, Inst, &TLINST);
                } while (opSub != 0);
                break;

            case 2:
                do {
                    printf("\n--- MENU ATIVIDADES ---");
                    printf("\n1. Cadastrar Atividade\n2. Consultar Atividades\n3. Excluir Atividade\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if (opSub == 1) {
                        do { opContinuar = cadastrarAtividade(Atv, Inst, &TLAT, TLINST, &prxid_atv); } while (opContinuar == 'S');
                    } else if (opSub == 2) consultarAtividades(Atv, TLAT);
                    else if (opSub == 3) excluirAtividade(Atv, &TLAT);
                } while (opSub != 0);
                break;

            case 3:
                do {
                    printf("\n--- MENU PACOTES ---");
                    printf("\n1. Cadastrar Pacote\n2. Consultar Pacotes\n3. Excluir Pacote\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if (opSub == 1) {
                        do { opContinuar = cadastrarPacote(Pc, Atv, &TLPC, TLAT, &prxid_pc); } while (opContinuar == 'S');
                    } else if (opSub == 2) consultarPacotes(Pc, TLPC);
                    else if (opSub == 3) excluirPacote(Pc, &TLPC);
                } while (opSub != 0);
                break;

            case 4:
                do {
                    printf("\n--- MENU PLANOS ---");
                    printf("\n1. Cadastrar Plano\n2. Consultar Planos\n3. Excluir Plano\n0. Voltar\nOpcao: ");
                    scanf("%d", &opSub);
                    if (opSub == 1) {
                        do { opContinuar = cadastrarPlano(Pl, &TLPL, &prxid_pl); } while (opContinuar == 'S');
                    } else if (opSub == 2) consultarPlanos(Pl, TLPL);
                    else if (opSub == 3) excluirPlano(Pl, &TLPL);
                } while (opSub != 0);
                break;

            case 5:
                do {
                    printf("\n--- MOVIMENTACOES E FINANCEIRO ---");
                    printf("\n1. Efetuar Matricula");
                    printf("\n2. Cancelar Matricula");
                    printf("\n3. Efetuar Recebimento");
                    printf("\n4. Relatorios Gerais");
                    printf("\n0. Voltar");
                    printf("\nOpcao: ");
                    scanf("%d", &opSub);

                    if (opSub == 1) efetuarMatricula(Al, TLA, Pl, TLPL, Pc, TLPC, Rec, &TLREC, &prxid_rec);
                    else if (opSub == 2) efetuarCancelamento(Al, TLA, Pl, TLPL);
                    else if (opSub == 3) efetuarRecebimento(Rec, TLREC, &prxid_rec);
                    else if (opSub == 4) relatoriosGerais(Rec, TLREC, Al, TLA);
                } while (opSub != 0);
                break;
        }
    } while (opPrincipal != 0);

    return 0;
}
