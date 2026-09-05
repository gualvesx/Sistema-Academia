# GUIA TÉCNICO DE DESENVOLVIMENTO: SISTEMA DE GESTÃO DA ACADEMIA

Este guia serve como documento de referência direta e prática para a codificação do sistema administrativo desktop em C/C++. Apresenta o esqueleto de navegação, a modelagem de dados (structs) e o detalhamento técnico de variáveis e regras de validação para cada função.

---

## 1. ESQUELETO ESTRUTURAL DO SISTEMA DESKTOP (Padrão de Navegação e Repetição)

O sistema é controlado por loops `do-while` em cada tela de menu, garantindo que o usuário possa interagir seguidamente até decidir retornar ou encerrar com o dígito `0`. As escolhas são processadas por estruturas `switch-case`.

```text
- Função Principal (main)
  └── loop principal: do { menuPrincipal(); ... } while(opcao != 0);

menuPrincipal() -> Renderiza o Menu Principal e lê a escolha do usuário
│
├── 1 - Gerenciar Pessoas 
│     └── loop interno: do { menuPessoas(); ... } while(opcao != 0);
│           ├── 1.1 - Cadastrar Aluno ──────> cadastrarAluno()
│           ├── 1.2 - Cadastrar Instrutor ──> cadastrarInstrutor()
│           ├── 1.3 - Consultar Pessoas ────> consultarPessoas()
│           ├── 1.4 - Excluir Pessoa ───────> excluirPessoa() (EXCLUSAO EM TODOS)
│           └── 0 - Voltar
│
├── 2 - Gerenciar Atividades
│     └── loop interno: do { menuAtividades(); ... } while(opcao != 0);
│           ├── 2.1 - Cadastrar Atividade ──> cadastrarAtividade()
│           ├── 2.2 - Consultar Atividades ─> consultarAtividades()
│           ├── 2.3 - Excluir Atividade ────> excluirAtividade() (EXCLUSAO EM TODOS)
│           └── 0 - Voltar
│
├── 3 - Gerenciar Pacotes
│     └── loop interno: do { menuPacotes(); ... } while(opcao != 0);
│           ├── 3.1 - Cadastrar Pacote ─────> cadastrarPacote()
│           ├── 3.2 - Consultar Pacotes ────> consultarPacotes()
│           ├── 3.3 - Excluir Pacote ───────> excluirPacote() (EXCLUSAO EM TODOS)
│           └── 0 - Voltar
│
├── 4 - Gerenciar Planos
│     └── loop interno: do { menuPlanos(); ... } while(opcao != 0);
│           ├── 4.1 - Cadastrar Plano ──────> cadastrarPlano()
│           ├── 4.2 - Consultar Planos ─────> consultarPlanos()
│           ├── 4.3 - Excluir Plano ────────> excluirPlano() (EXCLUSAO EM TODOS)
│           └── 0 - Voltar
│
├── 5 - Movimentações (Nova Tela)
│     └── loop interno: do { menuMovimentacoes(); ... } while(opcao != 0);
│           ├── 5.1 - Matrículas
│           │     ├── 5.1.1 - Efetuar Matrícula ───> efetuarMatricula()
│           │     │     └── [Suporte] calcularDescontoPlano()
│           │     └── 5.1.2 - Cancelar Matrícula ──> efetuarCancelamento()
│           │           └── [Suporte] aplicarMultaCancelamento()
│           ├── 5.2 - Recebimentos ───────────────> efetuarRecebimento()
│           │     └── [Suporte] gerarProximoBoleto()
│           ├── 5.3 - Relatórios Gerais ──────────> relatoriosGerais()
│           │     ├── Filtro 1: Extrato Geral de Recebimentos
│           │     ├── Filtro 2: Matrículas Ativas vs Canceladas
│           │     ├── Filtro 3: Pagamentos por Aluno (CPF)
│           │     └── Filtro 4: Pagamentos por Mês / Período
│           └── 0 - Voltar
│
└── 0 - Sair (Encerra o programa)
```

---

## 2. ESTRUTURAS DE DADOS (STRUCTS) E JUSTIFICATIVAS

Para simular o armazenamento relacional de um banco de dados em memória, definimos as seguintes structs:

### Struct Aluno
```c
struct Aluno {
    char cpf[15];
    char nome[100];
    char telefone[20];
    int id_pacote;
    int status_matricula; // 1 = Ativa, 0 = Cancelada
};
```
*   **`cpf[15]`**: String para CPF formatado (ex: `000.000.000-00`). É a chave primária que identifica unicamente o aluno nas buscas e movimentações.
*   **`nome[100]`**: String para armazenar o nome completo do aluno para fins de identificação visual nos relatórios.
*   **`telefone[20]`**: Contato telefônico direto para relacionamento e cobrança.
*   **`id_pacote`**: Inteiro atuando como chave estrangeira. Vincula o aluno a um pacote específico registrado na memória.
*   **`status_matricula`**: Flag inteiro essencial para a regra de cancelamento e filtro de alunos ativos vs inativos.

### Struct Instrutor
```c
struct Instrutor {
    char cpf[15];
    char nome[100];
    char especialidade[50];
};
```
*   **`cpf[15]`**: Chave primária do instrutor. Utilizado para validar se ele existe antes de associá-lo a uma atividade física.
*   **`nome[100]`**: Nome completo do profissional para relatórios e exibição no sistema.
*   **`especialidade[50]`**: Registra a área de atuação (ex: Pilates, Crossfit, Lutas) para assegurar o alinhamento pedagógico.

### Struct Atividade
```c
struct Atividade {
    int id;
    char nome[50];
    char cpf_instrutor[15];
};
```
*   **`id`**: Código numérico sequencial único gerado automaticamente pelo sistema como chave primária.
*   **`nome[50]`**: Nome da modalidade física (ex: Spinning, Musculação).
*   **`cpf_instrutor[15]`**: Chave estrangeira que aponta para o CPF do instrutor responsável, garantindo integridade de quem ministra a atividade.

### Struct Pacote
```c
struct Pacote {
    int id;
    char nome[50];
    int ids_atividades[10]; // Suporta até 10 atividades por pacote
    int qtd_atividades;
};
```
*   **`id`**: Chave primária do pacote de serviços comercializado pela academia.
*   **`nome[50]`**: Nome do pacote (ex: "Pacote Fitness Total", "Combo Reabilitação").
*   **`ids_atividades[10]`**: Vetor de chaves estrangeiras guardando os IDs das atividades inclusas no pacote.
*   **`qtd_atividades`**: Contador de controle interno para o preenchimento do vetor de atividades sem estourar o limite fixado.

### Struct Plano
```c
struct Plano {
    int id;
    char nome[50];
    char tipo; // 'M' - Mensal, 'T' - Trimestral, 'S' - Semestral, 'A' - Anual
    float valor_base;
};
```
*   **`id`**: Chave primária de identificação do plano.
*   **`nome[50]`**: Nome comercial do plano (ex: "Fidelidade Ouro").
*   **`tipo`**: Caractere crucial para acionar as validações de descontos comerciais e o cálculo percentual de reembolso de cancelamento.
*   **`valor_base`**: Preço padrão sem descontos que sofrerá as deduções matemáticas das regras comerciais.

### Struct Recebimento
```c
struct Recebimento {
    int id_recebimento;
    char cpf_aluno[15];
    int mes_referencia;
    float valor_cobrado;
    int status_pago; // 1 = Pago, 0 = Aberto/Pendente
};
```
*   **`id_recebimento`**: Identificador único de cada transação ou lançamento financeiro gerado pelo sistema.
*   **`cpf_aluno[15]`**: Chave estrangeira ligando o recebimento de forma indissociável a um aluno cadastrado.
*   **`mes_referencia`**: Valor inteiro (ex: 8 para Agosto) para controle temporal e geração futura de parcelas.
*   **`valor_cobrado`**: O valor real a ser pago, calculado no ato da matrícula com base nos descontos fidelidade aplicados.
*   **`status_pago`**: Sinalizador lógico para controlar adimplência/inadimplência.

---

## 3. DESTRINCHANDO AS FUNÇÕES DO SISTEMA (VARIÁVEIS LOCAIS E REGRA DE NEGÓCIO)

Aqui está o mapeamento exato de quais variáveis locais colocar em cada função, e o porquê de suas existências para a lógica de repetição, validação e execução.

### 3.1 Funções de Cadastro (Controle e Validação)

#### `cadastrarAluno()`
*   **Variáveis Locais:**
    *   `Aluno novo` (Struct temporária): Coleta os dados lidos pelo teclado antes de confirmá-los na memória global.
    *   `int idxAluno` (Inteiro): Recebe o retorno de `buscaAluno(novo.cpf)`. Serve para validar se o CPF já está cadastrado, impedindo a duplicação do registro.
    *   `int idxPacote` (Inteiro): Recebe o retorno de `buscaPacote(novo.id_pacote)`. Se retornar `-1`, o sistema exibe mensagem de erro e solicita um pacote válido usando um loop de repetição.
*   **Por que cada uma:** `novo` organiza o escopo de entrada temporariamente. `idxAluno` e `idxPacote` são variáveis de validação estrutural indispensáveis para garantir que não existam dados órfãos ou chaves duplicadas.

#### `cadastrarInstrutor()`
*   **Variáveis Locais:**
    *   `Instrutor novo` (Struct temporária): Armazena as entradas lidas de nome, CPF e especialidade.
    *   `int idxInst` (Inteiro): Recebe o retorno de `buscaInstrutor(novo.cpf)`.
*   **Por que cada uma:** `novo` isola os dados de entrada. `idxInst` serve para verificar se o profissional já existe no banco de dados da academia, garantindo que CPFs idênticos não sejam adicionados ao vetor de instrutores.

#### `cadastrarAtividade()`
*   **Variáveis Locais:**
    *   `Atividade nova` (Struct temporária): Aloca os dados de ID gerado, nome e o CPF do instrutor atribuído.
    *   `int idxInst` (Inteiro): Recebe o resultado de `buscaInstrutor(nova.cpf_instrutor)`.
*   **Por que cada uma:** `nova` serve para encapsular os dados da atividade física. A variável `idxInst` é obrigatória para validar se o CPF digitado aponta de fato para um instrutor cadastrado. Se o instrutor não existir, a atividade não pode ser salva sem um docente responsável.

#### `cadastrarPacote()`
*   **Variáveis Locais:**
    *   `Pacote novo` (Struct temporária): Reúne os dados do pacote a ser registrado.
    *   `int tempId` (Inteiro): ID temporário da atividade inserido pelo operador.
    *   `int idxAtiv` (Inteiro): Retorno de `buscaAtividade(tempId)`.
    *   `char continuar` (Caractere): Sinaliza se o usuário deseja incluir mais uma atividade no pacote atual.
*   **Por que cada uma:** `novo` monta a estrutura comercial. A variável `tempId` lê o ID da atividade que o operador quer agrupar; `idxAtiv` valida se a atividade inserida é real; `continuar` controla o laço interno de repetição `do-while` que permite ao usuário adicionar de 1 a 10 atividades no mesmo pacote comercial antes de encerrar o cadastro.

#### `cadastrarPlano()`
*   **Variáveis Locais:**
    *   `Plano novo` (Struct temporária): Guarda os dados do plano.
*   **Por que cada uma:** `novo` organiza o plano. A função deve rodar um loop `do-while` forçando o operador a escolher entre as letras `'M'`, `'T'`, `'S'` ou `'A'`. Se ele digitar algo fora desse padrão, o laço de validação repete a pergunta de tipo do plano.

---

### 3.2 Funções de Consulta e Exclusão

#### `consultarPessoas()` / `consultarAtividades()` / `consultarPacotes()` / `consultarPlanos()`
*   **Variáveis Locais:**
    *   `int i` (Inteiro): Variável de controle do laço `for` que percorre os índices do vetor linear global correspondente.
    *   `int registros` (Inteiro): Contador simples para saber se existem cadastros ativos na memória.
*   **Por que cada uma:** `i` é o indexador padrão do vetor. A variável `registros` impede o sistema de imprimir uma tela preta vazia caso nenhum registro tenha sido feito, informando elegantemente: "Nenhum registro cadastrado no momento."

#### `excluirPessoa()` (Aplicado aos demais fluxos de Exclusão)
*   **Variáveis Locais:**
    *   `char cpf[15]` (String): CPF que o operador deseja remover do sistema.
    *   `int idx` (Inteiro): Posição no vetor obtida por `buscaAluno(cpf)` ou `buscaInstrutor(cpf)`.
    *   `char confirmacao` (Caractere): Recebe o caractere `'S'` ou `'N'` digitado pelo usuário.
    *   `int j` (Inteiro): Índice do laço de reorganização física do vetor.
*   **Por que cada uma:** `cpf` localiza o registro; `idx` valida se o elemento existe no banco de dados para ser removido; `confirmacao` é um controle de segurança obrigatório para evitar cliques de exclusão acidentais; `j` é usado no laço `for` que "puxa" os elementos seguintes do vetor uma posição para trás, cobrindo o buraco deixado pela exclusão e reorganizando a memória sequencial.

---

### 3.3 Funções Financeiras e Movimentações (Regras de Negócio do Projeto)

#### `efetuarMatricula()`
*   **Variáveis Locais:**
    *   `char cpf[15]` (String): Identifica qual aluno está contratando os serviços.
    *   `int idPlano` (Inteiro): ID do plano comercial escolhido.
    *   `int idxAluno` (Inteiro): Retorno de `buscaAluno(cpf)`.
    *   `int idxPlano` (Inteiro): Retorno de `buscaPlano(idPlano)`.
    *   `float valorFinal` (Decimal): Recebe o retorno matemático de `calcularDescontoPlano()`.
*   **Por que cada uma:** `cpf` e `idPlano` são entradas diretas para configurar a operação. `idxAluno` e `idxPlano` são verificadores que impedem a consolidação de contratos para CPFs inexistentes ou planos comerciais inválidos. O `valorFinal` armazena o preço real recorrente que será cobrado no registro de recebimentos do aluno após a redução aplicada.

#### `calcularDescontoPlano(float valorBase, char tipoPlano)`
*   **Variáveis Locais:**
    *   `float desconto` (Decimal): Armazena o valor decimal da redução calculada (ex: valorBase * 0.10).
*   **Por que cada uma:** Esta função executa uma condicional direta: se `tipoPlano` for `'T'` (Trimestral), aplica **5% de desconto**; se `'S'` (Semestral), aplica **10% de desconto**; se `'A'` (Anual), aplica **15% de desconto**; se for mensal (`'M'`), o desconto é 0. Retorna o valor original subtraído do desconto.

#### `efetuarCancelamento()`
*   **Variáveis Locais:**
    *   `char cpf[15]` (String): CPF do aluno desistente.
    *   `int idxAluno` (Inteiro): Retorno da verificação se o aluno de fato possui uma matrícula ativa.
    *   `int idPlano` (Inteiro): ID do plano associado a essa matrícula.
    *   `char tipoPlano` (Caractere): Tipo do plano ativo capturado da struct de planos.
    *   `float valorContrato` (Decimal): Valor total estipulado para o plano comercial.
    *   `float multa` (Decimal): Guarda o cálculo da taxa de retenção de 30%.
    *   `float reembolso` (Decimal): Armazena os 70% calculados que devem ser restituídos ao cliente.
*   **Por que cada uma:** O sistema exige que, para cancelamentos de planos com fidelidade (Trimestral, Semestral ou Anual), a academia **retenha 30%** do valor residual e **reembolse 70%** ao aluno. Se for plano Mensal ('M'), apenas cancela-se a próxima mensalidade sem cobranças adicionais. Ao final do processamento, a variável `status_matricula` do aluno é redefinida para `0` (Inativa).

#### `efetuarRecebimento()`
*   **Variáveis Locais:**
    *   `char cpf[15]` (String): CPF do aluno pagando sua parcela.
    *   `int mesAtual` (Inteiro): O número do mês que está sendo liquidado (ex: 8).
    *   `int idxReceb` (Inteiro): Armazena o índice da parcela pendente no vetor de recebimentos.
*   **Por que cada uma:** `cpf` e `mesAtual` mapeiam o boleto em aberto do cliente. `idxReceb` é essencial para verificar se a parcela descrita realmente existia e se já não havia sido quitada (`status_pago == 1`). Após mudar `status_pago` para `1`, a função faz um incremento automático e dispara uma chamada interna para `gerarProximoBoleto()` para a competência de valor `mesAtual + 1` de modo a provisionar as finanças futuras.

#### `gerarProximoBoleto(char cpf[], int proximoMes, float valor)`
*   **Variáveis Locais:**
    *   `Recebimento novoBoleto` (Struct temporária): Configura o novo lançamento.
*   **Por que cada uma:** Organiza a data e dados do boleto projetado, registrando o lançamento no banco de dados de memória com `status_pago = 0` (Aberto) para monitoramento de adimplência na próxima competência.

#### `relatoriosGerais()`
*   **Variáveis Locais:**
    *   `int opRelatorio` (Inteiro): Seleciona o relatório específico (1 a 4) desejado no switch-case interno.
    *   `char cpfBusca[15]` (String): Filtro temporário de busca por CPF do aluno para o Filtro 3.
    *   `int mesBusca` (Inteiro): Filtro de mês de competência para o Filtro 4.
    *   `int i` (Inteiro): Variável indexadora dos loops de varredura e impressão.
*   **Por que cada uma:** `opRelatorio` gerencia o fluxo de controle; `cpfBusca` e `mesBusca` são variáveis dinâmicas de restrição para que os laços `for` que percorrem a memória filtrem e imprimam apenas os relatórios que satisfaçam as chaves informadas.

---

## 4. LAÇOS DE REPETIÇÃO E TRATAMENTO DE ENTRADAS DE DADOS

Durante a escrita do código em C/C++, preste especial atenção nestes dois padrões:

### A. Limpeza do Buffer do Teclado (`limparBuffer()`)
O uso consecutivo de funções de leitura como `scanf` para ler números e, logo em seguida, ler strings (`fgets` ou `gets`), faz com que o caractere de quebra de linha `\n` permaneça preso na memória, "pulando" a digitação de textos.
*   **Implementação em C:**
    ```c
    void limparBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    ```
*   **Quando usar:** Chame `limparBuffer()` imediatamente após ler qualquer dado numérico (`int`, `float`, `char` de opção) antes de prosseguir para leituras textuais de strings (CPF, nome completo, etc.).

### B. Proteção contra Loops Infinitos de Leitura
Se o usuário digitar uma letra quando o programa espera ler um número inteiro em opções de menu ou IDs, o fluxo do `scanf` falhará e poderá entrar em loop infinito de travamento.
*   **Tratamento Recomendado:**
    ```c
    int lerOpcao() {
        int opcao;
        if (scanf("%d", &opcao) != 1) {
            limparBuffer(); // descarta a entrada inválida
            return -1;      // indica opção incorreta
        }
        limparBuffer();     // limpa o \n remanescente
        return opcao;
    }
    ```
