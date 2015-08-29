/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testmat.c
*  Letras identificadoras:      TMAT
*
*  Projeto: Disciplinas INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Peraira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*       1.00   gbo, gapm, tdn   28/08/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo matriz.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     =criar <int>  - chama a função MAT_CriarMatriz( mat )
*                     Obs. mat é a matriz identificada por <int>.
*                     <int> é o valor do parâmetro que se encontra
*                     no comando de teste.
*
*     =destruir <int>  - chama a função MAT_DestruirMatriz( mat )
*                        Obs. mat é a matriz identificada por <int>.
*                        <int> é o valor do parâmetro que se encontra
*                        no comando de teste.
*
*     =inscol <int>  - chama a função MAT_InserirColuna( mat )
*                    Obs. mat é a matriz identificada por <int>.
*                    <int> é o valor do parâmetro que se encontra
*                    no comando de teste.
*
*     =inslin <int>  - chama a função MAT_InserirLinha( mat )
*                    Obs. mat é a matriz identificada por <int>.
*                    <int> é o valor do parâmetro que se encontra
*                    no comando de teste.
*
*     =lercel <int, int, int>
*                    - chama a função MAT_LerCelula( mat, linha, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha e coluna são
*                    os dois parâmetros seguintes.
*
*     =esccel <int, int, int>
*                    - chama a função MAT_EscreverCelula( mat, linha, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha e coluna são
*                    os dois parâmetros seguintes.
*
*     =exccol <int, int>
*                    - chama a função MAT_ExcluirColuna( mat, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. coluna é o segundo
*                    parâmetro.
*
*     =exclin <int, int>
*                    - chama a função MAT_ExcluirLinha( mat, linha )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha é o segundo
*                    parâmetro.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "tst_espc.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define CMD_CRIAR           "=criar"
#define CMD_DESTRUIR        "=destruir"
#define CMD_INSERIR_COLUNA  "=inscol"
#define CMD_INSERIR_LINHA   "=inslin"
#define CMD_LER_CELULA      "=lercel"
#define CMD_ESCREVER_CELULA "=esccel"
#define CMD_EXCLUIR_COLUNA  "=exccol"
#define CMD_EXCLUIR_LINHA   "=exclin"


/* Quantidade máxima de matrizes que podem ser testadas simultaneamente */
#define QTD_MATRIZES 10

/* Quantidade máxima de parâmetros permitidos em um comando de teste */
#define MAX_PARAMS 3

/***** Tipos de dados utilizados neste módulo de teste *****/


/***********************************************************************
*
*  $TC Tipo de dados: cmdFunc
*
*  $ED Descrição do tipo
*     Ponteiro para uma função de tratamento que executa o comando
*     recebido do script.
*
***********************************************************************/

typedef MAT_tpCondRet ( * cmdFunc ) ( void ) ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da célula da mariz
*
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

typedef struct
{
   char * Comando;
      /* comando de teste lido do script */

   char * Params;
      /* lista de parâmetros que será passada para a função
       * LER_LerParametros */

   cmdFunc Funcao;
      /* função a ser executada para tratar o comando */

   char * MsgErro;
      /* mensagem de erro que será mostrada em caso de falha */

} tpComandoTeste;


/*****  Protóripos das funções *****/

static MAT_tpCondRet TMAT_CmdCriar( void ) ;
static MAT_tpCondRet TMAT_CmdDestruir( void ) ;
static MAT_tpCondRet TMAT_CmdInsCol( void ) ;
static MAT_tpCondRet TMAT_CmdInsLin( void ) ;
static MAT_tpCondRet TMAT_CmdLerCel( void ) ;
static MAT_tpCondRet TMAT_CmdEscCel( void ) ;
static MAT_tpCondRet TMAT_CmdExcCol( void ) ;
static MAT_tpCondRet TMAT_CmdExcLin( void ) ;


/*****  Variáveis globais à este módulo  *****/

/***************************************************************************
*
*  Vetor: Matrizes
*  Descrição: Lista de matrizes usadas nos testes
*
*  ****/

static MAT_tpMatriz Matrizes[ QTD_MATRIZES ] ;


/***************************************************************************
*
*  Vetor: Parametros
*  Descrição: Vetor que armazena os parâmetros lidos de um comando no script
*  de teste.
*
*  ****/

static int Parametros[ MAX_PARAMS ] ;


/***************************************************************************
*
*  Variável: Lista
*  Descrição: Simula a existência de uma lista do tipo LIS_tppLista
*             ( apenas provê um ponteiro válido: o endereço dessa variável ).
*             O conteúdo dessa variável não é usado.
*
*  ****/

static void * Lista = NULL ;


/***************************************************************************
*
*  Vetor: Comandos
*  Descrição: Vetor que associa os comandos de teste às funções de tratamento
*
*  ****/

static tpComandoTeste Comandos[] = {
/*   Comando           Parâmetros  Função             Mensagem de erro */
   { CMD_CRIAR ,           "i" ,   TMAT_CmdCriar ,    "Retorno errado ao criar a matriz."    } ,
   { CMD_DESTRUIR ,        "i" ,   TMAT_CmdDestruir , "Retorno errado ao destruir a matriz." } ,
   { CMD_INSERIR_COLUNA ,  "i" ,   TMAT_CmdInsCol ,   "Retorno errado ao inserir a coluna."  } ,
   { CMD_INSERIR_LINHA ,   "i" ,   TMAT_CmdInsLin ,   "Retorno errado ao inserir a linha."   } ,
   { CMD_LER_CELULA ,      "iii" , TMAT_CmdLerCel ,   "Retorno errado ao ler a célula."      } ,
   { CMD_ESCREVER_CELULA , "iii" , TMAT_CmdEscCel ,   "Retorno errado ao escrever a célula." } ,
   { CMD_EXCLUIR_COLUNA ,  "ii" ,  TMAT_CmdExcCol ,   "Retorno errado ao excluir a coluna."  } ,
   { CMD_EXCLUIR_LINHA ,   "ii" ,  TMAT_CmdExcLin ,   "Retorno errado ao excluir a linha."   }
} ;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para matriz
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     matriz sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      /* Obtém o número de elementos do vetor Comandos */
      static const int qtdComandos = sizeof( Comandos ) / sizeof( Comandos[0] ) ;
      int cmd;
      int qtdParams;

      MAT_tpCondRet CondRetEsperada;

      /* Encontra a função de tratamento do comando de teste */
      for ( cmd = 0 ; cmd < qtdComandos ; cmd ++ )
      {
         if ( strcmp( Comandos[ cmd ].Comando , ComandoTeste ) == 0 )
         {
            qtdParams = LER_LerParametros( Comandos[ cmd ].Params ,
                                           &Parametros[ 0 ] ,
                                           &Parametros[ 1 ] ,
                                           &Parametros[ 2 ] ,
                                           &CondRetEsperada ) ;

            if ( qtdParams != strlen( Comandos[ cmd ].Params ) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsperada , Comandos[ cmd ].Funcao() ,
                                    Comandos[ cmd ].MsgErro ) ;
         } /* if */
      } /* for */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT Efetuar operações de teste específicas para matriz */


/***********************************************************************
*
*  $FC Função: TMAT Comando Criar
*
*  $ED Descrição da função
*     Testa criação da matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdCriar( void )
   {

      return MAT_CriarMatriz( &Matrizes[ Parametros[ 0 ]] ) ;

   } /* Fim função: TMAT Comando Criar */

/***********************************************************************
*
*  $FC Função: TMAT Comando Destruir
*
*  $ED Descrição da função
*     Testa desalocação da matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdDestruir( void )
   {

      return MAT_DestruirMatriz( Matrizes[ Parametros[ 0 ]] ) ;

   } /* Fim função: TMAT Comando Destruir */

/***********************************************************************
*
*  $FC Função: TMAT Comando Inserir Coluna
*
*  $ED Descrição da função
*     Testa a inserção de uma coluna na matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdInsCol( void )
   {

      return MAT_InserirColuna( Matrizes[ Parametros[ 0 ]] ) ;

   } /* Fim função: TMAT Comando Inserir Coluna */

/***********************************************************************
*
*  $FC Função: TMAT Comando Inserir Linha
*
*  $ED Descrição da função
*     Testa a inserção de uma linha na matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdInsLin( void )
   {

      return MAT_InserirLinha( Matrizes[ Parametros[ 0 ]] ) ;

   } /* Fim função: TMAT Comando Inserir Linha */


/***********************************************************************
*
*  $FC Função: TMAT Comando Ler Célula
*
*  $ED Descrição da função
*     Testa recuperação de uma Lista de uma célula da matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdLerCel( void )
   {

      MAT_tpCondRet ret;
      LIS_tppLista lis;

      ret = MAT_LerCelula( Matrizes[ Parametros[ 0 ]],
                           Parametros[ 1 ],
                           Parametros[ 2 ],
                           &lis ) ;

      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      if ( ( void ** ) lis != &Lista )
      {
         TST_NotificarFalha( "Lista lida diferente do esperado." ) ;
      } /* if */

      return MAT_CondRetOK;

   } /* Fim função: TMAT Comando Ler Célula */


/***********************************************************************
*
*  $FC Função: TMAT Comando Escrever Célula
*
*  $ED Descrição da função
*     Testa inserção de uma Lista em uma célula da matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdEscCel( void )
   {

      return MAT_EscreverCelula( Matrizes[ Parametros[ 0 ]],
                                 Parametros[ 1 ],
                                 Parametros[ 2 ],
                                 ( LIS_tppLista ) &Lista ) ;

   } /* Fim função: TMAT Comando Escrever Célula */


/***********************************************************************
*
*  $FC Função: TMAT Comando Excluir Coluna
*
*  $ED Descrição da função
*     Testa a exclusão de colunas da matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdExcCol( void )
   {

      return MAT_ExcluirColuna( Matrizes[ Parametros[ 0 ]],
                                Parametros[ 1 ] ) ;

   } /* Fim função: TMAT Comando Excluir Coluna */


/***********************************************************************
*
*  $FC Função: TMAT Comando Excluir Linha
*
*  $ED Descrição da função
*     Testa a exclusão de linhas da matriz
*
***********************************************************************/

   static MAT_tpCondRet TMAT_CmdExcLin( void )
   {

      return MAT_ExcluirLinha( Matrizes[ Parametros[ 0 ]],
                               Parametros[ 1 ] ) ;

   } /* Fim função: TMAT Comando Excluir Linha */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
