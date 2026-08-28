#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TF 100

// ==========================================
// 1. UTILITÁRIOS
// ==========================================

void limparBuffer() {
    /*
      Substitui os multiplos usos de:
      - fflush(stdin);
      - Consumos manuais de quebra de linha ('\n') apos leituras de inteiros/caracteres.
    */
}

// ==========================================
// 2. FUNÇÕES DE BUSCA E VALIDAÇÃO
// ==========================================

int buscaAluno(int vcpfaluno[], int TLA, int cpf_int) {
    /*
      Substitui o laco de busca linear de aluno do codigo antigo:
      posa = 0;
      while (posa < TLA && cpf_int != vcpfaluno[posa]) {
          posa++;
      }
      Retorna o indice encontrado ou -1 caso nao exista.
    */
    return -1;
}

int buscaInstrutor(int vidinst[], int TLI, int idinst) {
    /*
      Substitui o laco de busca linear de instrutor do codigo antigo:
      posc = 0;
      while (posc < TLI && idinst != vidinst[posc]) {
          posc++;
      }
      Retorna o indice encontrado ou -1 caso nao exista.
    */
    return -1;
}

int buscaAtividade(int vidmod[], int TLM, int idmod) {
    /*
      Substitui o laco de busca linear de modalidade do codigo antigo:
      posm = 0;
      while (posm < TLM && idmod != vidmod[posm]) {
          posm++;
      }
      Retorna o indice encontrado ou -1 caso nao exista.
    */
    return -1;
}

int buscaPacote(int vcodpac[], int TLPAC, int codpac) {
    /*
      Funcao nova (Modulo 3):
      Executa a busca sequencial no vetor vcodpac para verificar 
      se o pacote ja existe ou retornar sua posicao no vetor.
    */
    return -1;
}

int buscaPlano(int vcodpl[], int TLPL, int codpl) {
    /*
      Funcao nova (Modulo 4):
      Executa a busca sequencial no vetor vcodpl para verificar 
      se o plano informado e valido no sistema.
    */
    return -1;
}

int buscaMatricula(int vcodmat[], int TLMAT, int codmat) {
    /*
      Funcao nova (Modulo 5):
      Executa a busca sequencial no vetor vcodmat para validar a matricula
      antes de efetuar cancelamentos ou lancamentos de recebimento.
    */
    return -1;
}

// ==========================================
// 3. MENUS DE NAVEGAÇÃO
// ==========================================

int menuPrincipal() {
    /*
      Substitui a exibicao do menu raiz e leitura da variavel 'rop':
      printf("\n <=============== SISTEMA PARA GERENCIAMENTO DE ACADEMIA ===============>");
      printf("\n 1. Gerenciar Pessoas");
      printf("\n 2. Gerenciar Atividades");
      printf("\n 3. Gerenciar Pacotes");
      printf("\n 4. Gerenciar Planos");
      printf("\n 5. Movimentacoes");
      printf("\n 0. Encerrar Sistema");
      scanf("%d", &rop);
    */
    int op = 0;
    return op;
}

int menuPessoas() {
    /*
      Substitui parte do antigo 'case 1' (Cadastro) e submenu:
      printf("\n 1.1 - Cadastrar Aluno");
      printf("\n 1.2 - Cadastrar Instrutor");
      printf("\n 1.3 - Consultar Pessoas");
      printf("\n 0. Retornar");
      scanf("%d", &rc);
    */
    int op = 0;
    return op;
}

int menuAtividades() {
    /*
      Substitui a secao de modalidades do antigo menu:
      printf("\n 2.1 - Cadastrar Atividade");
      printf("\n 2.2 - Consultar Atividades");
      printf("\n 0. Retornar");
      scanf("%d", &rc);
    */
    int op = 0;
    return op;
}

int menuPacotes() {
    /*
      Menu novo (Modulo 3):
      printf("\n 3.1 - Cadastrar Pacote");
      printf("\n 3.2 - Consultar Pacotes");
      printf("\n 0. Retornar");
    */
    int op = 0;
    return op;
}

int menuPlanos() {
    /*
      Menu novo (Modulo 4):
      printf("\n 4.1 - Cadastrar Plano");
      printf("\n 4.2 - Consultar Planos");
      printf("\n 0. Retornar");
    */
    int op = 0;
    return op;
}

int menuMovimentacoes() {
    /*
      Substitui os blocos antigos de Lancamento (case 2) e Exclusao (case 3):
      printf("\n 5.1 - Matriculas (Nova / Cancelar)");
      printf("\n 5.2 - Recebimentos");
      printf("\n 5.3 - Relatorios");
      printf("\n 0. Retornar");
    */
    int op = 0;
    return op;
}

// ==========================================
// 4. MÓDULO 1: GERENCIAR PESSOAS
// ==========================================

void cadastrarAluno(int vcpfaluno[], char valuno[][50], int *TLA) {
    /*
      Substitui o bloco 'case 2: (CADASTRO DE ALUNO)':
      - Leitura de CPF: scanf("%d", &cpf_int);
      - Verificacao de duplicidade usando buscaAluno()
      - Insercao no vetor: vcpfaluno[*TLA] = cpf_int;
      - Leitura do nome: gets(aluno) / strcpy(valuno[*TLA], aluno);
      - Incremento do tamanho logico: (*TLA)++;
    */
}

void cadastrarInstrutor(int vidinst[], char vinst[][50], int *TLI) {
    /*
      Substitui o bloco 'case 1: (CADASTRO DE INSTRUTOR)':
      - Leitura do codigo: scanf("%d", &idinst);
      - Verificacao de duplicidade usando buscaInstrutor()
      - Insercao no vetor: vidinst[*TLI] = idinst;
      - Leitura do nome: gets(inst) / strcpy(vinst[*TLI], inst);
      - Incremento do tamanho logico: (*TLI)++;
    */
}

void consultarPessoas(int vcpfaluno[], char valuno[][50], int TLA, 
                      int vidinst[], char vinst[][50], int TLI) {
    /*
      Substitui a listagem/consulta de Alunos e Instrutores do antigo 'case 4':
      - Laco for para alunos: printf("Aluno: %s | CPF: %d", valuno[i], vcpfaluno[i]);
      - Laco for para instrutores: printf("Instrutor: %s | Codigo: %d", vinst[i], vidinst[i]);
    */
}

// ==========================================
// 5. MÓDULO 2: GERENCIAR ATIVIDADES
// ==========================================

void cadastrarAtividade(int vidmod[], char vmod[][30], float vvaloraula[], int *TLM) {
    /*
      Substitui o bloco 'case 3: (CADASTRO DE MODALIDADE)':
      - Leitura do codigo: scanf("%d", &idmod);
      - Verificacao de existencia via buscaAtividade()
      - Insercao: vidmod[*TLM] = idmod;
      - Leitura da descricao: gets(mod) / strcpy(vmod[*TLM], mod);
      - Leitura do valor: scanf("%f", &vvaloraula[*TLM]);
      - Incremento do tamanho logico: (*TLM)++;
    */
}

void consultarAtividades(int vidmod[], char vmod[][30], float vvaloraula[], int TLM) {
    /*
      Substitui a consulta de modalidades do antigo 'case 4 -> case 3':
      - Laco for para exibicao:
        for (i = 0; i < TLM; i++) {
            printf("Modalidade: %s | Codigo: %d | Valor: %.2f", vmod[i], vidmod[i], vvaloraula[i]);
        }
    */
}

// ==========================================
// 6. MÓDULO 3: GERENCIAR PACOTES
// ==========================================

void cadastrarPacote(int vcodpac[], char vnomepac[][30], int vativ1[], int vativ2[], float vvalorpac[], int *TLPAC,
                      int vidmod[], char vmod[][30], float vvaloraula[], int TLM) {
    /*
      Funcao nova (Modulo 3):
      - Substitui criacao manual de combos.
      - Leitura de dados do pacote, validacao das atividades via buscaAtividade(),
        atribuicao nos vetores de pacote e incremento de (*TLPAC)++.
    */
}

void consultarPacotes(int vcodpac[], char vnomepac[][30], int vativ1[], int vativ2[], float vvalorpac[], int TLPAC) {
    /*
      Funcao nova (Modulo 3):
      - Percorre o vetor de pacotes ate TLPAC e imprime Codigo, Nome, Atividades associadas e Valor combo.
    */
}

// ==========================================
// 7. MÓDULO 4: GERENCIAR PLANOS
// ==========================================

void cadastrarPlano(int vcodpl[], char vnomepl[][30], int vmesespl[], float vdescpl[], int *TLPL) {
    /*
      Funcao nova (Modulo 4):
      - Leitura de codigo, nome do plano (Mensal, Trimestral, Semestral, Anual),
        duracao em meses (1, 3, 6, 12), percentual de desconto (0%, 5%, 10%, 15%)
        e incremento de (*TLPL)++.
    */
}

void consultarPlanos(int vcodpl[], char vnomepl[][30], int vmesespl[], float vdescpl[], int TLPL) {
    /*
      Funcao nova (Modulo 4):
      - Percorre os vetores ate TLPL listando os planos cadastrados e seus descontos.
    */
}

// ==========================================
// 8. MÓDULO 5: MOVIMENTAÇÕES
// ==========================================

void efetuarMatricula(int vcodmat[], int vmatcpf[], int vmatplano[], int vmatmesvenc[], float vmatvalor[], int vmatstatus[], int *TLMAT,
                      int vcpfaluno[], char valuno[][50], int TLA,
                      int vcodpl[], char vnomepl[][30], int vmesespl[], float vdescpl[], int TLPL,
                      int vidmod[], char vmod[][30], float vvaloraula[], int TLM) {
    /*
      Substitui e expande o antigo bloco de avaliacao/lancamento (case 2 antigo: vlinst, vlaluno, vldataaval):
      - Valida se aluno, plano e atividade existem via funcoes de busca.
      - Aplica a regra de calculo de desconto da mensalidade conforme o plano selecionado.
      - Grava a matricula e incrementa (*TLMAT)++.
    */
}

void efetuarCancelamento(int vcodmat[], int vmatcpf[], int vmatplano[], float vmatvalor[], int vmatstatus[], int TLMAT,
                         int vcodpl[], int vmesespl[], int TLPL) {
    /*
      Substitui o antigo bloco 'case 3: (EXCLUSAO DE ALUNO)' que fazia remocao com deslocamento:
      for (i = pose; i < TLA - 1; i++) {
          vcpfaluno[i] = vcpfaluno[i + 1];
          strcpy(valuno[i], valuno[i + 1]);
      }
      - Aplica regra do novo escopo: cancela proximo mes (plano mensal) ou retencao 30% / devolucao 70% (planos longos).
    */
}

void efetuarRecebimento(int vcodmat[], int vmatcpf[], int vmatmesvenc[], float vmatvalor[], int vmatstatus[], int TLMAT,
                        int vcpfaluno[], char valuno[][50], int TLA,
                        int vrecmat[], int vrecmes[], float vrecvalor[], int *TLREC) {
    /*
      Funcao nova de fluxo financeiro:
      - Localiza a matricula ativa pelo codigo.
      - Confirma pagamento do mes atual, registra no historico (*TLREC)++ e
        gera/avanca automaticamente o boleto/vencimento para o mes seguinte (ex: mes 08 -> mes 09).
    */
}

void relatoriosGerais(int vcodmat[], int vmatcpf[], int vmatplano[], float vmatvalor[], int vmatstatus[], int TLMAT,
                      int vcpfaluno[], char valuno[][50], int TLA,
                      int vrecmat[], int vrecmes[], float vrecvalor[], int TLREC) {
    /*
      Substitui a estrutura de filtros do antigo 'case 4: (CONSULTA COM FILTROS)':
      - Implementa os 4 relatorios obrigatorios:
        1. Extrato geral de recebimentos
        2. Relatorio de matriculas (ativas vs canceladas)
        3. Pagamentos filtrados por aluno (CPF)
        4. Pagamentos filtrados por periodo/mes
    */
}

// ==========================================
// 9. FUNÇÃO PRINCIPAL (MAIN)
// ==========================================

int main() {
    // Vetores e TLs de Pessoas (Instrutores e Alunos)[cite: 5]
    int vidinst[TF], TLI = 0; //[cite: 5]
    char vinst[TF][50]; //[cite: 5]

    int vcpfaluno[TF], TLA = 0; //[cite: 5]
    char valuno[TF][50]; //[cite: 5]

    // Vetores e TL de Atividades (antiga Modalidade)[cite: 5]
    int vidmod[TF], TLM = 0; //[cite: 5]
    char vmod[TF][30]; //[cite: 5]
    float vvaloraula[TF]; //[cite: 5]

    // Vetores e TL de Pacotes[cite: 1]
    int vcodpac[TF], vativ1[TF], vativ2[TF], TLPAC = 0;
    char vnomepac[TF][30];
    float vvalorpac[TF];

    // Vetores e TL de Planos[cite: 1]
    int vcodpl[TF], vmesespl[TF], TLPL = 0;
    char vnomepl[TF][30];
    float vdescpl[TF];

    // Vetores e TLs de Movimentacoes (Matriculas e Recebimentos)[cite: 1, 2]
    int vcodmat[TF], vmatcpf[TF], vmatplano[TF], vmatmesvenc[TF], vmatstatus[TF], TLMAT = 0;
    float vmatvalor[TF];

    int vrecmat[TF], vrecmes[TF], TLREC = 0;
    float vrecvalor[TF];

    // Variaveis de controle do Menu
    int rop, rsub, ropmat;

    do {
        rop = menuPrincipal(); //[cite: 1]

        switch (rop) {
            case 1: // 1 - Gerenciar Pessoas[cite: 1]
                do {
                    rsub = menuPessoas(); //[cite: 1]
                    switch (rsub) {
                        case 1:
                            cadastrarAluno(vcpfaluno, valuno, &TLA); //[cite: 1]
                            break;
                        case 2:
                            cadastrarInstrutor(vidinst, vinst, &TLI); //[cite: 1]
                            break;
                        case 3:
                            consultarPessoas(vcpfaluno, valuno, TLA, vidinst, vinst, TLI); //[cite: 1]
                            break;
                    }
                } while (rsub != 0);
                break;

            case 2: // 2 - Gerenciar Atividades[cite: 1]
                do {
                    rsub = menuAtividades(); //[cite: 1]
                    switch (rsub) {
                        case 1:
                            cadastrarAtividade(vidmod, vmod, vvaloraula, &TLM); //[cite: 1]
                            break;
                        case 2:
                            consultarAtividades(vidmod, vmod, vvaloraula, TLM); //[cite: 1]
                            break;
                    }
                } while (rsub != 0);
                break;

            case 3: // 3 - Gerenciar Pacotes[cite: 1]
                do {
                    rsub = menuPacotes(); //[cite: 1]
                    switch (rsub) {
                        case 1:
                            cadastrarPacote(vcodpac, vnomepac, vativ1, vativ2, vvalorpac, &TLPAC, vidmod, vmod, vvaloraula, TLM); //[cite: 1]
                            break;
                        case 2:
                            consultarPacotes(vcodpac, vnomepac, vativ1, vativ2, vvalorpac, TLPAC); //[cite: 1]
                            break;
                    }
                } while (rsub != 0);
                break;

            case 4: // 4 - Gerenciar Planos[cite: 1]
                do {
                    rsub = menuPlanos(); //[cite: 1]
                    switch (rsub) {
                        case 1:
                            cadastrarPlano(vcodpl, vnomepl, vmesespl, vdescpl, &TLPL); //[cite: 1]
                            break;
                        case 2:
                            consultarPlanos(vcodpl, vnomepl, vmesespl, vdescpl, TLPL); //[cite: 1]
                            break;
                    }
                } while (rsub != 0);
                break;

            case 5: // 5 - Movimentacoes[cite: 1]
                do {
                    rsub = menuMovimentacoes(); //[cite: 1]
                    switch (rsub) {
                        case 1: // 5.1 Matriculas[cite: 1]
                            printf("\n1 - Efetuar Matricula\n2 - Cancelar Matricula\nEscolha: "); //[cite: 2]
                            scanf("%d", &ropmat);
                            if (ropmat == 1) {
                                efetuarMatricula(vcodmat, vmatcpf, vmatplano, vmatmesvenc, vmatvalor, vmatstatus, &TLMAT,
                                                 vcpfaluno, valuno, TLA, vcodpl, vnomepl, vmesespl, vdescpl, TLPL,
                                                 vidmod, vmod, vvaloraula, TLM); //[cite: 2]
                            } else if (ropmat == 2) {
                                efetuarCancelamento(vcodmat, vmatcpf, vmatplano, vmatvalor, vmatstatus, TLMAT,
                                                    vcodpl, vmesespl, TLPL); //[cite: 2]
                            }
                            break;

                        case 2: // 5.2 Recebimentos[cite: 1]
                            efetuarRecebimento(vcodmat, vmatcpf, vmatmesvenc, vmatvalor, vmatstatus, TLMAT,
                                               vcpfaluno, valuno, TLA, vrecmat, vrecmes, vrecvalor, &TLREC); //[cite: 2]
                            break;

                        case 3: // 5.3 Relatorios[cite: 1]
                            relatoriosGerais(vcodmat, vmatcpf, vmatplano, vmatvalor, vmatstatus, TLMAT,
                                            vcpfaluno, valuno, TLA, vrecmat, vrecmes, vrecvalor, TLREC); //[cite: 2]
                            break;
                    }
                } while (rsub != 0);
                break;

            case 0: // 0 - Sair[cite: 1]
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (rop != 0);

    return 0;
}
