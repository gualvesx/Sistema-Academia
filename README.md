# DOCUMENTAÇÃO TÉCNICA: SISTEMA DE GESTÃO DA ACADEMIA

## 1. ESCOPO E ARQUITETURA DO SISTEMA

### 1.1 Objetivo e Domínio

O **Sistema de Gestão da Academia** é uma aplicação desktop de console desenvolvida em C/C++ para gerenciamento administrativo, pedagógico e financeiro de academias de ginástica e centros esportivos. O sistema controla todo o ciclo de vida operacional: cadastro de alunos e instrutores, modalidades esportivas, pacotes de atividades, planos de contrato, processamento de matrículas, alteração integral de registros cadastrais, cálculo de multas rescisórias em cancelamentos e fluxo de caixa recorrente via mensalidades e boletos.

### 1.2 Arquitetura de Persistência e Organização de Arquivos

A aplicação utiliza **arquivos binários sequenciais (`.bin`)** para persistência de dados em disco:

* **`aluno.bin`**: Cadastro contendo identificação pessoal (CPF, nome, telefone), vínculos contratuais e status da matrícula.
* **`instrutor.bin`**: Cadastro de profissionais contendo CPF, nome completo e especialidade.
* **`atividade.bin`**: Catálogo de modalidades físicas ofertadas (ID, nome) e indicação do instrutor responsável via CPF.
* **`pacote.bin`**: Agrupamento promocional de até 10 atividades em um único pacote comercial.
* **`plano.bin`**: Tabela de modalidades contratuais (Mensal, Trimestral, Semestral, Anual) e seus respectivos valores-base.
* **`recebimento.bin`**: Histórico e provisionamento financeiro (boletos gerados, pendentes e quitados).
* **`auxiliar.bin`**: Arquivo binário temporário de transição, utilizado exclusivamente durante operações de exclusão física por cópia seletiva.

### 1.3 Nomenclatura Padronizada de Manipuladores (`FILE*`)

Para assegurar legibilidade e manutenibilidade do código-fonte, todos os ponteiros de arquivo utilizam estritamente o prefixo padronizado `arq<Entidade>`:

* `arqAluno`
* `arqInstrutor`
* `arqAtividade`
* `arqPacote`
* `arqPlano`
* `arqRecebimento`
* `arqTemp`

---

## 2. ESTRUTURA DE NAVEGAÇÃO DO SISTEMA

O sistema adota um padrão de menus aninhados controlados por laços `do-while` com seleções processadas por `switch-case`. Toda operação que altera os dados em disco (cadastro, alteração ou exclusão) aciona automaticamente a reordenação em disco (`ordenar...()`) da respectiva entidade.

```text
main()
 └── Loop Principal: do { menuPrincipal(); ... } while(opcaoPrincipal != 0);
      │
      ├── 1. Gerenciar Pessoas ──> gerenciarPessoas()
      │     ├── 1. Cadastrar Aluno ──────> cadastrarAluno() ──> ordenarAluno()
      │     ├── 2. Cadastrar Instrutor ──> cadastrarInstrutor() ──> ordenarInstrutor()
      │     ├── 3. Consultar Pessoas ────> consultarPessoas() [Aluno / Instrutor]
      │     ├── 4. Alterar Pessoa ───────> alterarPessoa() [alterarAluno() / alterarInstrutor()] ──> ordenar...()
      │     └── 5. Excluir Pessoa ───────> excluirPessoa() [excluirAlunoReal() / excluirInstrutor()] ──> ordenar...()
      │
      ├── 2. Gerenciar Atividades ──> gerenciarAtividades()
      │     ├── 1. Cadastrar Atividade ──> cadastrarAtividade() ──> ordenarAtividade()
      │     ├── 2. Consultar Atividades ─> consultarAtividade()
      │     ├── 3. Alterar Atividade ────> alterarAtividade() ──> ordenarAtividade()
      │     └── 4. Excluir Atividade ────> excluirAtividade() ──> ordenarAtividade()
      │
      ├── 3. Gerenciar Pacotes ──> gerenciarPacotes()
      │     ├── 1. Cadastrar Pacote ─────> cadastrarPacote() ──> ordenarPacote()
      │     ├── 2. Consultar Pacotes ────> consultarPacote()
      │     ├── 3. Alterar Pacote ───────> alterarPacote() ──> ordenarPacote()
      │     └── 4. Excluir Pacote ───────> excluirPacote() ──> ordenarPacote()
      │
      ├── 4. Gerenciar Planos ──> gerenciarPlanos()
      │     ├── 1. Cadastrar Plano ──────> cadastrarPlano() ──> ordenarPlano()
      │     ├── 2. Consultar Planos ─────> consultarPlano()
      │     ├── 3. Alterar Plano ────────> alterarPlano() ──> ordenarPlano()
      │     └── 4. Excluir Plano ────────> excluirPlano() ──> ordenarPlano()
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
| **`Aluno`** | `cpf[15]`, `nome[100]`, `telefone[20]`, `id_pacote`, `id_plano`, `status_matricula` | `cpf` | `id_pacote`, `id_plano` | Armazena dados cadastrais e estado da matrícula (`1` = Ativa, `0` = Inativa). |
| **`Instrutor`** | `cpf[15]`, `nome[100]`, `especialidade[50]` | `cpf` | — | Identifica o profissional responsável por ministrar aulas. |
| **`Atividade`** | `id`, `nome[50]`, `cpf_instrutor[15]` | `id` | `cpf_instrutor` | Registra a modalidade física vinculada a um instrutor habilitado. |
| **`Pacote`** | `id`, `nome[50]`, `ids_atividades[10]`, `qtd_atividades` | `id` | `ids_atividades[]` | Associa até 10 atividades a uma oferta comercial agregada. |
| **`Plano`** | `id`, `nome[50]`, `tipo`, `valor_base` | `id` | — | Define a periodicidade (`'M'`, `'T'`, `'S'`, `'A'`) e o valor-base bruto. |
| **`Recebimento`** | `id_recebimento`, `cpf_aluno[15]`, `mes_referencia`, `valor_cobrado`, `status_pago` | `id_recebimento` | `cpf_aluno` | Controla as mensalidades e parcelas do aluno (`1` = Pago, `0` = Pendente). |

---

## 4. DETALHAMENTO TÉCNICO DAS FUNÇÕES

### 4.1 Validação e Sanitização de Entradas

* **`lerInteiro()` e `lerFloat()`**: Impedem travamentos procedimentais. Utilizam o retorno de conversão da função `scanf` dentro de um laço `while`. Se o operador inserir caracteres não numéricos, a entrada é descartada via `fflush(stdin)` e a leitura é requisitada novamente.
* **`lerCPF(char cpf[])`**: Garante que a entrada possua exatamente 11 caracteres numéricos (`strlen(cpf) == 11` e `isdigit(cpf[i])`).
* **`lerTextoApenasLetras(...)`**: Captura strings completas via `fgets`, remove a quebra de linha `\n` com `strcspn` e valida a presença exclusiva de caracteres alfabéticos (incluindo vogais acentuadas e cedilha) e espaços.
* **`lerOpcaoSN()`**: Normaliza a leitura para caracteres maiúsculos via `toupper()` e restringe o aceite estritamente a `'S'` ou `'N'`.

---

### 4.2 Métodos de Busca, Ordenação e Seleção Interativa

#### A. Buscas Sequenciais (`buscaAluno`, `buscaInstrutor`, `buscaAtividade`, `buscaPacote`, `buscaPlano`)
* Realizam varreduras sequenciais no arquivo binário com `fread`.
* **Retorno:** Devolvem a posição física relativa (`0, 1, 2...`) do registro no arquivo binário ou `-1` caso a chave pesquisada não seja encontrada. A posição devolvida permite posicionamento direto em disco com `fseek(arq, pos * sizeof(Struct), SEEK_SET)`.

#### B. Ordenação Automática em Disco (`ordenarAluno`, `ordenarInstrutor`, `ordenarAtividade`, `ordenarPacote`, `ordenarPlano`)
* Implementam o algoritmo **Bubble Sort diretamente no arquivo binário**, sem necessidade de carregar todos os dados em vetores de memória RAM.
* O arquivo é aberto em modo de leitura/escrita binária (`"rb+"`). O número de elementos é calculado via `ftell(arq) / sizeof(Struct)`. A comparação de nomes utiliza `strcmp()`. Quando a ordenação é necessária, os dois registros são sobrescritos nas posições corretas em disco via `fseek` e `fwrite`.
* **Garantia de Execução:** A função de ordenação é invocada automaticamente ao final de **qualquer operação de mutação**:
  1. Após o cadastro (`cadastrar...()`).
  2. Após a alteração (`alterar...()`).
  3. Após a exclusão (`excluir...()`).

#### C. Seleção Interativa Unificada (`selecionarAluno`, `selecionarInstrutor`, `selecionarAtividade`, `selecionarPacote`, `selecionarPlano`)
Proporcionam uma interface com duas vias de seleção:
1. **Digitar a chave primária diretamente** (CPF ou ID).
2. Listar **todos os registros cadastrados em tela**, exibindo os dados formatados com um índice entre colchetes (`[0]`, `[1]`, `[2]`), permitindo a escolha direta pelo número da linha.

---

### 4.3 Cadastros Transacionais (`cadastrar...`)

* **Geração de Chaves:** Entidades do tipo pessoa (`Aluno`, `Instrutor`) passam por verificação de unicidade via CPF (`busca...() == -1`). Entidades identificadas por código numérico (`Atividade`, `Pacote`, `Plano`) recebem auto-incremento calculado a partir do tamanho atual do arquivo binário: `(ftell(arq) / sizeof(Struct)) + 1`.
* **Integridade Referencial no Cadastro:**
  * `cadastrarAtividade()` obriga a seleção de um instrutor existente através da função `selecionarInstrutor()`.
  * `cadastrarPacote()` permite associar dinamicamente até 10 atividades cadastradas, checando duplicidades no vetor do pacote (`jaExiste`).
* **Pós-Cadastro:** Fecha o arquivo binário e invoca a função de ordenação correspondente.

---

### 4.4 Alteração de Dados em Disco (`alterar...`)

As rotinas de alteração de dados transmitem flexibilidade ao operador, permitindo atualizar qualquer campo modificável da entidade mantendo a integridade referencial do sistema:

#### A. Mecanismo de Atualização In-Place
1. A função invoca a **Seleção Interativa Unificada** (`selecionar...()`) para obter a posição física (`pos`) do registro.
2. Abre o arquivo binário em modo leitura/escrita (`"rb+"`).
3. Posiciona o ponteiro de arquivo na posição exata: `fseek(arq, pos * sizeof(Struct), SEEK_SET)`.
4. Lê o registro atual via `fread`, solicita ao operador a digitação dos novos valores para os campos e efetua a sobrescrita imediata com `fwrite`.
5. Fecha o arquivo e executa a reordenação em disco (`ordenar...()`).

#### B. Campos Editáveis por Entidade

* **`alterarAluno()`**: Atualiza o nome completo e o telefone de contato. Mantém a chave primária (`cpf`) e o histórico de matrícula intactos.
* **`alterarInstrutor()`**: Atualiza o nome completo e a especialidade do docente.
* **`alterarAtividade()`**: Atualiza o nome da atividade e possibilita vincular a modalidade a um novo docente via `selecionarInstrutor()`.
* **`alterarPacote()`**: Atualiza o nome comercial e permite a reconfiguração completa das atividades associadas (redefinindo `ids_atividades[]` e `qtd_atividades`).
* **`alterarPlano()`**: Atualiza o nome comercial, a vigência/tipo (`'M'`, `'T'`, `'S'`, `'A'`) e o valor-base do plano (com validação `valor_base > 0`).

---

### 4.5 Exclusão com Auditoria de Dependências e Integridade Referencial

Todas as rotinas de exclusão executam uma verificação de dependências em duas etapas: **Auditoria de Vínculos** e **Cópia Seletiva via Arquivo Auxiliar**.

#### Etapa 1: Auditoria de Vínculos Cruzados
Antes de autorizar a remoção de qualquer registro, o sistema consulta os demais arquivos do banco de dados binário para verificar a existência de pendências ou relacionamentos ativos:

| Função | Arquivos Consultados | Condições Auditadas |
| :--- | :--- | :--- |
| **`excluirAlunoReal()`** | `aluno.bin`, `recebimento.bin` | 1. Verifica se `Al.status_matricula == 1` (Matrícula Ativa).<br>2. Varre `recebimento.bin` buscando boletos lançados para o `Al.cpf`. |
| **`excluirInstrutor()`** | `atividade.bin` | Varre `atividade.bin` verificando se alguma modalidade possui `Atv.cpf_instrutor == Inst.cpf`. |
| **`excluirAtividade()`** | `pacote.bin` | Varre todos os pacotes e seus vetores `Pc.ids_atividades[]` verificando se o `Atv.id` compõe algum pacote. |
| **`excluirPacote()`** | `aluno.bin` | Varre `aluno.bin` verificando se existe algum aluno com `Al.id_pacote == Pc.id` e `Al.status_matricula == 1`. |
| **`excluirPlano()`** | `aluno.bin` | Varre `aluno.bin` verificando se existe algum aluno com `Al.id_plano == Pl.id` e `Al.status_matricula == 1`. |

#### Etapa 2: Remoção Física via Arquivo Auxiliar
Caso não haja pendências (ou o operador confirme explicitamente que deseja prosseguir):
1. Abre o arquivo original em modo leitura (`"rb"`) e cria o arquivo temporário `auxiliar.bin` em modo escrita (`"wb"`).
2. Percorre sequencialmente os registros e copia para `auxiliar.bin` apenas os elementos cuja chave primária difira da chave marcada para exclusão.
3. Fecha os ponteiros de arquivo, remove o arquivo original (`remove()`), renomeia o arquivo temporário (`rename("auxiliar.bin", "entidade.bin")`) e executa a reordenação em disco (`ordenar...()`).

---

### 4.6 Camada Financeira e Movimentações

#### A. `efetuarMatricula()` e `calcularDescontoPlano()`
* **Regra Comercial de Desconto:**
  * Plano Mensal (`'M'`): $0\%$ de desconto ($ValorFinal = ValorBase$).
  * Plano Trimestral (`'T'`): $5\%$ de desconto ($ValorFinal = ValorBase \times 0.95$).
  * Plano Semestral (`'S'`): $10\%$ de desconto ($ValorFinal = ValorBase \times 0.90$).
  * Plano Anual (`'A'`): $15\%$ de desconto ($ValorFinal = ValorBase \times 0.85$).
* **Efeito no Banco:** Atualiza `Al.status_matricula = 1`, grava o `id_plano` e `id_pacote` no cadastro do aluno em disco (`"rb+"`) e dispara a geração da parcela inicial via `gerarProximoBoleto()`.

#### B. `efetuarCancelamento()`
* **Regra de Multa Rescisória:**
  * Se `Pl.tipo == 'M'` (Mensal): Cancelamento isento de multa.
  * Se `Pl.tipo != 'M'` (Fidelidade Trimestral, Semestral ou Anual): Calcula **30% de multa de retenção** retida pela academia ($valor \times 0.30$) e **70% de reembolso** restituído ao aluno ($valor \times 0.70$).
* **Efeito no Banco:** Reseta `Al.status_matricula = 0`, `Al.id_plano = -1` e `Al.id_pacote = -1`.

#### C. `efetuarRecebimento()`, `existeBoleto()` e `gerarProximoBoleto()`
* **Baixa Financeira:** Localiza a parcela pendente em `recebimento.bin` por `cpf_aluno` e `mes_referencia`. Altera `Rec.status_pago = 1`.
* **Provisão Futura:** Se `mes < 12`, aciona `gerarProximoBoleto()` para o mês `mes + 1`. A função auxiliar `existeBoleto()` valida previamente se o título do mês seguinte já não existe em disco, impedindo duplicidades financeiras.
