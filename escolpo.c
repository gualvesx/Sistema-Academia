#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define TFA 100
#define TFAT 100

//--Struct's--
typedef struct
{
	char cpf[11]; 
	//pacote p;
	//plano pl;
	//atividade atv;
    char nome[50];
}cadAluno;

typedef struct
{
	char nome[50]; 
    char nome_inst[50];
    char descricao[200];
	int vagas;
    
}cadAtividade;


//--Funcoes--

// Menus
int menu()
{
    int opc=0;
    
    printf("\n\n<========== MENU ==========>");
    printf("\n1. GERENCIAR PESSOAS");
    printf("\n2. GERENCIAR ATIVIDADES");
    printf("\n3. GERENCIAR PACOTES");
    printf("\n4. GERENCIAR PLANOS");
    printf("\n5. MOVIMENTACOES");
    printf("\n0. SAIR");
    
    printf("\n\n Escolha: ");
    scanf("%d",&opc);
    
    return opc;
}

int menuPessoas()
{
    int opc=0;
    
    printf("\n\n<========== GERENCIAMENTO DE PESSOAS ==========>");
    printf("\n1. CADASTRAR ALUNO");
    printf("\n2. CADASTRAR INSTRUTOR");
    printf("\n3. CONSULTAR");
    printf("\n4. EXCLUIR");
    printf("\n0. SAIR");
    
    printf("\n\n Escolha: ");
    scanf("%d",&opc);
    
    return opc;
}

// Cadastros
char cadastrarAluno(cadAluno cadAl[], char *op, int TLA)
{
	if(TLA<TFA)
	{
		printf("\n\n<==== CADASTRO DE ALUNO ===>");
    
	    printf("\nInsira o CPF: ");
	    fflush(stdin);
	    gets(cadAl[TLA].cpf);
	    
	    printf("\nContinuar? S/N: ");
	    fflush(stdin);
	    scanf(" %c",op);
	    
	    *op=toupper(*op);
	}
	else
	printf("\n**ERRO: Sistema cheio**");
    
    return *op;
}
main()
{
    //Variáveis
    int rop,opc,rsub;
    char op;
    int TLA=0,TLAT=0;
    
    //Struct's
    cadAluno cadAl[TFA];
    cadAtividade cadAtv[TFAT];
    
    //Sistema
    printf("\n<============== SISTEMA ACADEMIA ==============>");
    
    //Menu
    rop = menu();
    
    while(rop!=0)
    {
	    switch(rop)
	    {
	        // Gerenciar Pessoas
	        case 1:
	            rsub = menuPessoas();
	            
	            switch(rsub)
	            {
	                //Cadastrar Aluno
	                case 1:
	                	op='S';
						while(op=='S')
						{
							cadastrarAluno(cadAl, &op, TLA);
							TLA++;
						}
	                    
	                    break;
	                case 2:
	                	
	                	break;
	                default:
	                    break;
	            }
	            
	        break;
	            
	        case 2:
	            //rsub= menuAtividades();
	            
	            switch(rsub)
	            {
	                default:
	                    break;
	            }
	            
	        break;
	        
	        case 3:
	            //rsub= menuPacotes();
	            
	            switch(rsub)
	            {
	                default:
	                    break;    
	            }
	        break;
	        
	        case 4:
	            //rsub= menuPlanos();
	            
	            switch(rsub)
	            {
	                default:
	                    break;
	            }
	        break;
	        
	        case 5:
	            //rsub= menuMovimentacoes();
	            
	            switch(rsub)
	            {
	                default:
	                    break;
	            }
	        break;
	        
	        default:
	            break;
		}
		rop = menu();	
	}
	    
}
