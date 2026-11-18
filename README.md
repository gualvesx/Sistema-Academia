# Sistema de Gestão de Academia (SGA)

Sistema desenvolvido em **C** para gerenciamento completo de academias, estruturado com arquivos binários para persistência de dados e foco total na integridade e validação de regras de negócio.

---

## 🚀 Funcionalidades do Sistema

### 1. Gerenciamento de Pessoas (Alunos e Instrutores)
* **Cadastro de Alunos e Instrutores:** Validação automática de CPF (exatamente 11 dígitos numéricos)[span_0](start_span)[span_0](end_span) e bloqueio contra cadastros duplicados ou cruzados entre perfis.
* **Telefone e Nomes Validados:** O campo de telefone aceita apenas números, e os nomes validam caracteres textuais e acentuações.
* **Ordenação Automática:** Listagem e arquivos mantidos em ordem alfabética por nome automaticamente.
* **Alteração e Exclusão Segura:** Verificação transacional de dependências (impedindo exclusão de alunos com matrículas ativas ou boletos pendentes, e de instrutores com atividades vinculadas).

### 2. Gerenciamento de Atividades e Pacotes
* **Atividades:** Associação direta de atividades físicas a instrutores cadastrados.
* **Pacotes:** Criação de pacotes personalizados contendo limite de aulas mensais e múltiplas atividades associadas (até 10 por pacote).

### 3. Gerenciamento de Planos
* Suporte a 4 tipos de planos diferentes com cálculo automatizado de valores:
  * **M** - Mensal
  * **T** - Trimestral
  * **S** - Semestral
  * **A** - Anual

### 4. Módulo Financeiro e Movimentações
* **Efetuar Matrícula:** Associa o aluno a um plano e pacote, gerando automaticamente a primeira cobrança com base no mês/ano inicial informado.
* **Registro de Recebimento (Pagamento de Boletos):** Baixa de boletos em aberto. Ao registrar o pagamento de um boleto, o sistema **gera automaticamente o próximo boleto** de acordo com a vigência do plano contratado:
  * *Mensal:* Avança 1 mês.
  * *Trimestral:* Avança 3 meses.
  * *Semestral:* Avança 6 meses.
  * *Anual:* Avança 12 meses (com tratamento automático para virada de ano).
* **Cancelamento de Matrícula:** Cálculo automático de retenção/multa (30%) e reembolso (70%) para planos não mensais, além de invalidar automaticamente os boletos pendentes.
* **Histórico de Pagamentos por Aluno:** Consulta detalhada listando todos os boletos vinculados a um aluno específico, exibindo o mês/ano de referência, valor e status atual (*Em Aberto*, *Pago* ou *Cancelado*).

---

## 🛠️ Tecnologias Utilizadas
* Linguagem **C**
* Manipulação de arquivos binários (`FILE *`)
* Alocação de estruturas (`struct`) e algoritmos de ordenação em disco

---

## 📋 Como Compilar e Executar

Certifique-se de ter um compilador C instalado em sua máquina (como o `gcc` do MinGW no Windows).

1. Abra o terminal na pasta do projeto.
2. Compile o código-fonte executando:
   ```bash
   gcc main.c -o sistema_academia.exe
