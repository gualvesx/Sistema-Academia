# DOCUMENTAÇÃO TÉCNICA: SISTEMA DE GESTÃO DA ACADEMIA

---

## 1. ESCOPO E ARQUITETURA DO SISTEMA

### 1.1 Objetivo e Domínio
O **Sistema de Gestão da Academia** é uma aplicação desktop de console desenvolvida em C/C++ para gerenciamento administrativo, pedagógico e financeiro de academias de ginástica e centros esportivos. O sistema controla todo o ciclo de vida operacional: cadastro de alunos e instrutores, modalidades esportivas, pacotes de atividades, planos de contrato, processamento de matrículas, cálculo de multas rescisórias em cancelamentos e fluxo de caixa recorrente via mensalidades e boletos.

### 1.2 Arquitetura de Persistência e Organização de Arquivos
A aplicação utiliza **arquivos binários sequenciais (`.bin`)** para persistência de dados em disco:

* **`aluno.bin`**: Cadastro contendo identificação pessoal, vínculos contratuais e status da matrícula.
* **`instrutor.bin`**: Cadastro de profissionais e suas respectivas especialidades.
* **`atividade.bin`**: Catálogo de modalidades físicas ofertadas e indicação do instrutor responsável.
* **`pacote.bin`**: Agrupamento promocional de até 10 atividades em um único pacote comercial.
* **`plano.bin`**: Tabela de modalidades contratuais (Mensal, Trimestral, Semestral, Anual) e valores-base.
* **`recebimento.bin`**: Histórico e provisionamento financeiro (boletos gerados, pendentes e quitados).
* **`auxiliar.bin`**: Arquivo binário temporário de transição, utilizado exclusivamente durante operações de exclusão física.

### 1.3 Nomenclatura Padronizada de Manipuladores (`FILE*`)
Para assegurar legibilidade e manutenibilidade do código-fonte, os ponteiros de arquivo utilizam o prefixo padronizado `arq<Entidade>`:

* `arqAluno`
* `arqInstrutor`
* `arqAtividade`
* `arqPacote`
* `arqPlano`
* `arqRecebimento`
* `arqTemp`

---

## 2. ESTRUTURA DE NAVEGAÇÃO DO SISTEMA

O sistema adota um padrão de menus aninhados controlados por laços `do-while` com seleções processadas por `switch-case`.

```text
main()
 └── Loop Principal: do { menuPrincipal(); ... } while(opcaoPrincipal != 0);
      │
      ├── 1. Gerenciar Pessoas ──> gerenciarPessoas()
      │     ├── 1. Cadastrar Aluno ──────> cadastrarAluno() ──> ordenarAluno()
      │     ├── 2. Cadastrar Instrutor ──> cadastrarInstrutor() ──> ordenarInstrutor()
      │     ├── 3. Consultar Pessoas ────> consultarPessoas() [Aluno / Instrutor]
      │     └── 4. Excluir Pessoa ───────> excluirPessoa() [excluirAlunoReal() / excluirInstrutor()]
      │
      ├── 2. Gerenciar Atividades ──> gerenciarAtividades()
      │     ├── 1. Cadastrar Atividade ──> cadastrarAtividade() ──> ordenarAtividade()
      │     ├── 2. Consultar Atividades ─> consultarAtividade()
      │     └── 3. Excluir Atividade ────> excluirAtividade()
      │
      ├── 3. Gerenciar Pacotes ──> gerenciarPacotes()
      │     ├── 1. Cadastrar Pacote ─────> cadastrarPacote() ──> ordenarPacote()
      │     ├── 2. Consultar Pacotes ────> consultarPacote()
      │     └── 3. Excluir Pacote ───────> excluirPacote()
      │
      ├── 4. Gerenciar Planos ──> gerenciarPlanos()
      │     ├── 1. Cadastrar Plano ──────> cadastrarPlano() ──> ordenarPlano()
      │     ├── 2. Consultar Planos ─────> consultarPlano()
      │     └── 3. Excluir Plano ────────> excluirPlano()
      │
      └── 5. Movimentacoes e Financeiro ──> gerenciarMovimentacoes()
            ├── 1. Efetuar Matricula ────> efetuarMatricula()
            ├── 2. Efetuar Cancelamento ─> efetuarCancelamento()
            └── 3. Registrar Recebimento ─> efetuarRecebimento()
```

---

## 3. MODELAGEM DE DADOS (STRUCTS)

| Struct | Atributos | Chave Primária (PK) | Chaves Estrangeiras (FK) | Descrição / Regra no Sistema |
| :--- | :--- | :--- | :--- | :--- |
| **`Aluno`** | `cpf[15]`, `nome[100]`, `telefone[20]`, `id_pacote`, `id_plano`, `status_matricula` | `cpf` | `id_pacote`, `id_plano` | Armazena dados cadastrais e estado da matrícula (`1` = Ativa, `0` = Inativa/Cancelada). |
| **`Instrutor`** | `cpf[15]`, `nome[100]`, `especialidade[50]` | `cpf` | — | Identifica o profissional responsável por ministrar aulas. |
| **`Atividade`** | `id`, `nome[50]`, `cpf_instrutor[15]` | `id` | `cpf_instrutor` | Registra a modalidade física vinculada a um instrutor habilitado. |
| **`Pacote`** | `id`, `nome[50]`, `ids_atividades[10]`, `qtd_atividades` | `id` | `ids_atividades[]` | Associa até 10 atividades a uma oferta comercial agregada. |
| **`Plano`** | `id`, `nome[50]`, `tipo`, `valor_base` | `id` | — | Define periodicidade (`'M'`, `'T'`, `'S'`, `'A'`) e o valor base bruto. |
| **`Recebimento`** | `id_recebimento`, `cpf_aluno[15]`, `mes_referencia`, `valor_cobrado`, `status_pago` | `id_recebimento` | `cpf_aluno` | Controla as mensalidades e parcelas do aluno (`1` = Pago, `0` = Pendente). |

---

## 4. DETALHAMENTO TÉCNICO DAS FUNÇÕES

### 4.1 Validação e Sanitização de Entradas

* **`lerInteiro()` e `lerFloat()`**: Impedem travamentos procedimentais. Utilizam o retorno de conversão da função `scanf` dentro de um laço `while`. Se o operador inserir caracteres não numéricos, a entrada é descartada via `fflush(stdin)` ou limpeza de buffer e a leitura é requisitada novamente.
* **`lerCPF(char cpf[])`**: Garante que a entrada possua exatamente 11 caracteres numéricos (`strlen(cpf) == 11` e `isdigit(cpf[i])`).
* **`lerTextoApenasLetras(...)`**: Captura strings completas via `fgets`, remove a quebra de linha `\n` com `strcspn` e valida a presença exclusiva de caracteres alfabéticos (incluindo vogais acentuadas e cedilha) e espaços.
* **`lerOpcaoSN()`**: Normaliza a leitura para caracteres maiúsculos via `toupper()` e restringe o aceite estritamente a `'S'` ou `'N'`.

---

### 4.2 Métodos de Busca, Ordenação e Seleção Interativa

#### A. Buscas Sequenciais (`buscaAluno`, `buscaInstrutor`, `buscaAtividade`, `buscaPacote`, `buscaPlano`)
* Realizam varreduras sequenciais no arquivo binário com `fread`.
* **Retorno:** Retornam a posição física relativa (`0, 1, 2...`) do registro no arquivo binário ou `-1` caso a chave pesquisada não seja encontrada. A posição devolvida permite posicionamento rápido com `fseek(arq, pos * sizeof(Struct), SEEK_SET)`.

#### B. Ordenação em Disco (`ordenarAluno`, `ordenarInstrutor`, `ordenarAtividade`, `ordenarPacote`, `ordenarPlano`)
* Implementam o algoritmo **Bubble Sort diretamente no arquivo binário**, sem necessidade de carregar todos os dados em vetores de memória RAM.
* O arquivo é aberto em modo de leitura/escrita binária (`"rb+"`). O número de elementos é calculado via `ftell(arq) / sizeof(Struct)`. A comparação de nomes utiliza `strcmp()`. Quando o ordenamento é necessário, os dois registros são sobrescritos nas posições corretas em disco via `fseek` e `fwrite`.

#### C. Seleção Interativa Unificada (`selecionarAluno`, `selecionarInstrutor`, `selecionarAtividade`, `selecionarPacote`, `selecionarPlano`)
Proporcionam uma interface com duas opções ao usuário:
1. **Digitar a chave primária diretamente** (CPF ou ID).
2. **Listar todos os registros cadastrados em tela**, exibindo os dados formatados com um índice entre colchetes (`[0]`, `[1]`, `[2]`), permitindo a escolha direta pelo número da linha.

---

### 4.3 Cadastros Transacionais (`cadastrar...`)

* **Geração de Chaves:** Entidades do tipo pessoa (`Aluno`, `Instrutor`) passam por verificação de unicidade via CPF (`busca...() == -1`). Entidades identificadas por código numérico (`Atividade`, `Pacote`, `Plano`) recebem auto-incremento calculado a partir do tamanho atual do arquivo binário.
* **Integridade Referencial no Cadastro:**
  * `cadastrarAtividade()` obriga a seleção de um instrutor existente através da função `selecionarInstrutor()`.
  * `cadastrarPacote()` permite associar dinamicamente até 10 atividades cadastradas, checando duplicidades no vetor do pacote (`jaExiste`).

---

### 4.4 Exclusão e Auditoria de Dependências (Integridade Referencial)

Todas as rotinas de exclusão executam uma verificação de dependências em duas etapas: **Auditoria de Vínculos** e **Cópia Seletiva via Arquivo Auxiliar**.

#### Etapa 1: Auditoria de Vínculos Cruzados

Antes de autorizar a remoção de qualquer registro, o sistema consulta os demais arquivos do banco de dados binário para verificar a existência de pendências ou relacionamentos ativos:

| Função | Arquivos Consultados | Condições Auditadas |
| :--- | :--- | :--- |
| **`excluirAlunoReal()`** | `aluno.bin`, `recebimento.bin` | 1. Estado da matrícula (`status_matricula == 1`).<br>2. Existência de boletos/recebimentos vinculados ao CPF do aluno em `recebimento.bin`. |
| **`excluirInstrutor()`** | `atividade.bin` | Verificação de modalidades registradas em que `Atv.cpf_instrutor` seja igual ao CPF do instrutor. |
| **`excluirAtividade()`** | `pacote.bin` | Varredura em todos os pacotes para checar se o `Atv.id` está presente no vetor `ids_atividades[]`. |
| **`excluirPacote()`** | `aluno.bin` | Verificação de alunos com matrícula ativa associados ao `id_pacote`. |
| **`excluirPlano()`** | `aluno.bin` | Verificação de alunos com matrícula ativa associados ao `id_plano`. |

#### Etapa 2: Remoção Física via Arquivo Auxiliar

Quando a exclusão é confirmada:
1. O arquivo original é aberto para leitura binária (`"rb"`), e um arquivo temporário `auxiliar.bin` é aberto em modo de escrita (`"wb"`).
2. O sistema lê sequencialmente cada registro e grava no arquivo temporário **somente aqueles que não correspondem à chave excluída**.
3. Os arquivos são fechados, o arquivo binário original é removido (`remove()`) e o `auxiliar.bin` é renomeado para o nome original (`rename()`).

---

### 4.5 Regras Financeiras e Movimentações

#### A. Cálculo de Descontos por Plano (`calcularDescontoPlano`)
* **Plano Mensal (`'M'`):** Valor base integral ($0\%$ de desconto).
* **Plano Trimestral (`'T'`):** $5\%$ de desconto ($ValorFinal = ValorBase \times 0,95$).
* **Plano Semestral (`'S'`):** $10\%$ de desconto ($ValorFinal = ValorBase \times 0,90$).
* **Plano Anual (`'A'`):** $15\%$ de desconto ($ValorFinal = ValorBase \times 0,85$).

#### B. Efetivação de Matrícula (`efetuarMatricula`)
1. Seleciona um aluno inativo, um plano e um pacote promocional usando as rotinas de seleção interativa.
2. Calcula o valor líquido da mensalidade com `calcularDescontoPlano()`.
3. Atualiza os dados do aluno no arquivo `aluno.bin` (`status_matricula = 1`, salva `id_plano` e `id_pacote`).
4. Dispara a função `gerarProximoBoleto()` para registrar a cobrança inicial do mês informado.

#### C. Cancelamento de Matrícula e Retenção Rescisória (`efetuarCancelamento`)
1. Verifica se o aluno possui matrícula ativa (`status_matricula == 1`).
2. Recupera as condições do plano contratado:
   * Se for **Plano Mensal (`'M'`)**: O cancelamento é efetuado sem incidência de taxas rescisórias.
   * Se for **Plano de Fidelidade (`'T'`, `'S'`, `'A'`)**: Aplica-se **30% de multa de retenção** sobre o valor base do contrato ($Multa = ValorBase \times 0,30$) e exibe-se a devolução de **70% de reembolso** ao cliente ($Reembolso = ValorBase \times 0,70$).
3. Atualiza a ficha do aluno para inativo (`status_matricula = 0`, `id_plano = -1`, `id_pacote = -1`).

#### D. Liquidação de Mensalidades e Provisão Recorrente (`efetuarRecebimento` / `gerarProximoBoleto`)
1. `efetuarRecebimento()` pesquisa a parcela referente ao CPF e mês de competência em `recebimento.bin`.
2. Se o título estiver aberto (`status_pago == 0`), altera o status para quitado (`status_pago = 1`) e atualiza o registro em disco.
3. Ao confirmar o pagamento de um mês $M$ (sendo $M < 12$), a rotina chama automaticamente `gerarProximoBoleto()` para o mês $M + 1$.
4. A função `existeBoleto()` realiza uma consulta prévia em `recebimento.bin` para prevenir a geração acidental de parcelas duplicadas para a mesma competência.

---

## 5. REQUISITOS DE COMPILAÇÃO E AMBIENTE

* **Linguagem:** C (compatível com padrões C99/C11) / C++.
* **Compilador Recomendado:** GCC (MinGW para Windows) ou Clang.
* **Bibliotecas Padrão Utilizadas:** `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<ctype.h>`, `<windows.h>`, `<conio.h>`.
```

eof
