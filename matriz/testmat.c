/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testmat.c
*  Letras identificadoras:      TMAT
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
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
*     =lercel <int, int, int, int>
*                    - chama a função MAT_LerCelula( mat, linha, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha e coluna são
*                    os dois parâmetros seguintes.
*                    O quarto parâmetro indica com qual lista devemos
*                    comparar o ponteiro lido.
*                    Caso especial: Se linha ou coluna < 0, é passado
*                    NULL no ponteiro de retorno da lista.
*
*     =esccel <int, int, int, int>
*                    - chama a função MAT_EscreverCelula( mat, linha, coluna )
*                    Obs. mat é a matriz identificada pelo primeiro
*                    parâmetro do comando de teste. linha e coluna são
*                    os dois parâmetros seguintes. O quarto parâmetro
*                    indica qual lista devemos colocar na célula.
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
*     ------------------ Funções de manipulação de listas ----------------
*
*     =criarlis <int>
*                    - cria uma lista com <int> como identificador.
*
*     =destruirlis <int>
*                    - destroi a lista identificada por <int>
*
*     =esvaziarlis <int>
*                    - remove todos os elementos da lista identificada
*                    por <int>.
*
*     =inserirlis <int, char>
*                    - insere um elemento contendo <char> após o elemento
*                    atual na lista identificada por <int>.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <assert.h>
#include    <stdlib.h>

#include    "tst_espc.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"
#include    "lista.h"

/* Tabela dos nomes dos comandos de teste específicos */

const char CMD_CRIAR           [] = "=criar" ;
const char CMD_DESTRUIR        [] = "=destruir" ;
const char CMD_INSERIR_COLUNA  [] = "=inscol" ;
const char CMD_INSERIR_LINHA   [] = "=inslin" ;
const char CMD_LER_CELULA      [] = "=lercel" ;
const char CMD_ESCREVER_CELULA [] = "=esccel" ;
const char CMD_EXCLUIR_COLUNA  [] = "=exccol" ;
const char CMD_EXCLUIR_LINHA   [] = "=exclin" ;
const char CMD_CRIAR_LIS       [] = "=criarlis" ;
const char CMD_DESTRUIR_LIS    [] = "=destruirlis" ;
const char CMD_ESVAZIAR_LIS    [] = "=esvaziarlis" ;
const char CMD_INSERIR_LIS     [] = "=inserirlis" ;


/* Quantidade máxima de matrizes que podem ser testadas simultaneamente */
#define QTD_MATRIZES 11

/* Quantidade máxima de listas que podem ser usadas simultaneamente */
#define QTD_LISTAS 10

/* Quantidade máxima de parâmetros permitidos em um comando de teste,
 * mais 1 para o retorno esperado */
#define MAX_PARAMS 5

/* Essa macro converte um parâmetro de int para char (evita possíveis
 * problemas de endianness.
 * p é o índice do vetor Parametros*/
#define PARAM_CHAR( p ) ( *( char * ) &Parametros[ ( p ) ] )

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

typedef int ( * cmdFunc ) ( void ) ;


/***********************************************************************
*
*  $TC Tipo de dados: valFunc
*
*  $ED Descrição do tipo
*     Ponteiro para uma função de validação de parâmetros.
*     Retorna 1 se os parâmetros forem válidos, 0 caso contrário.
*
*  #EP Parâmetros
*     cmd - String do comando de teste a ser validado.
*
***********************************************************************/

typedef int ( * valFunc ) ( const char * cmd ) ;


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
   const char * Comando;
      /* comando de teste lido do script */

   char * Params;
      /* lista de parâmetros que será passada para a função
       * LER_LerParametros */

   cmdFunc Funcao;
      /* função a ser executada para tratar o comando */

   valFunc Validar;
      /* Função para validar os parâmetros recebidos */

   char * MsgErro;
      /* mensagem de erro que será mostrada em caso de falha */

} tpComandoTeste;


/*****  Protóripos das funções *****/

static int TMAT_CmdCriar( void ) ;
static int TMAT_CmdDestruir( void ) ;
static int TMAT_CmdInsCol( void ) ;
static int TMAT_CmdInsLin( void ) ;
static int TMAT_CmdLerCel( void ) ;
static int TMAT_CmdEscCel( void ) ;
static int TMAT_CmdExcCol( void ) ;
static int TMAT_CmdExcLin( void ) ;
static int TMAT_CmdCriarLis( void ) ;
static int TMAT_CmdDestruirLis( void ) ;
static int TMAT_CmdEsvaziarLis( void ) ;
static int TMAT_CmdInserirLis( void ) ;
static int TMAT_ValMat( const char * cmd ) ;
static int TMAT_ValLis( const char * cmd ) ;


/*****  Variáveis globais à este módulo  *****/

/***************************************************************************
*
*  Vetor: Matrizes
*  Descrição: Lista de matrizes usadas nos testes
*
*  ****/

static MAT_tppMatriz Matrizes[ QTD_MATRIZES ] = { NULL } ;


/***************************************************************************
*
*  Vetor: Parametros
*  Descrição: Vetor que armazena os parâmetros lidos de um comando no script
*  de teste, juntamente com o retorno esperado.
*
*  ****/

static int Parametros[ MAX_PARAMS ] ;


/***************************************************************************
*
*  Vetor: Listas
*  Descrição: Vetor que armazena as listas criadas no script de testes.
*
*  ****/

static LIS_tppLista Listas[ QTD_LISTAS ] ;


/***************************************************************************
*
*  Vetor: Comandos
*  Descrição: Vetor que associa os comandos de teste às funções de tratamento
*  Obs.: Incluir um 'i' no final dos parâmetros para o retorno esperado
*
*  ****/

static tpComandoTeste Comandos[] = {
/*   Comando             Parâmetros  Função               Validar params Mensagem de erro */
   { CMD_CRIAR ,           "ii" ,    TMAT_CmdCriar ,       TMAT_ValMat , "Retorno errado ao criar a matriz."    } ,
   { CMD_DESTRUIR ,        "ii" ,    TMAT_CmdDestruir ,    TMAT_ValMat , "Retorno errado ao destruir a matriz." } ,
   { CMD_INSERIR_COLUNA ,  "ii" ,    TMAT_CmdInsCol ,      TMAT_ValMat , "Retorno errado ao inserir a coluna."  } ,
   { CMD_INSERIR_LINHA ,   "ii" ,    TMAT_CmdInsLin ,      TMAT_ValMat , "Retorno errado ao inserir a linha."   } ,
   { CMD_LER_CELULA ,      "iiiii" , TMAT_CmdLerCel ,      TMAT_ValMat , "Retorno errado ao ler a célula."      } ,
   { CMD_ESCREVER_CELULA , "iiiii" , TMAT_CmdEscCel ,      TMAT_ValMat , "Retorno errado ao escrever a célula." } ,
   { CMD_EXCLUIR_COLUNA ,  "iii" ,   TMAT_CmdExcCol ,      TMAT_ValMat , "Retorno errado ao excluir a coluna."  } ,
   { CMD_EXCLUIR_LINHA ,   "iii" ,   TMAT_CmdExcLin ,      TMAT_ValMat , "Retorno errado ao excluir a linha."   } ,
   { CMD_CRIAR_LIS ,       "ii" ,    TMAT_CmdCriarLis ,    TMAT_ValLis , "Retorno errado ao criar a lista."     } ,
   { CMD_DESTRUIR_LIS ,    "ii" ,    TMAT_CmdDestruirLis , TMAT_ValLis , "Retorno errado ao destruir a lista."  } ,
   { CMD_ESVAZIAR_LIS ,    "ii" ,    TMAT_CmdEsvaziarLis , TMAT_ValLis , "Retorno errado ao esvaziar a lista."  } ,
   { CMD_INSERIR_LIS ,     "ici" ,   TMAT_CmdInserirLis ,  TMAT_ValLis , "Retorno errado ao inserir na lista."  }
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
      int cmd ;
      int qtdParamsLidos ,
          qtdParamsEsperados ;

      /* Encontra a função de tratamento do comando de teste */
      for ( cmd = 0 ; cmd < qtdComandos ; cmd ++ )
      {
         if ( strcmp( Comandos[ cmd ].Comando , ComandoTeste ) == 0 )
         {
            qtdParamsEsperados = strlen( Comandos[ cmd ].Params ) ;
            assert( qtdParamsEsperados <= MAX_PARAMS ) ;

            qtdParamsLidos = LER_LerParametros( Comandos[ cmd ].Params ,
                                                &Parametros[ 0 ] ,
                                                &Parametros[ 1 ] ,
                                                &Parametros[ 2 ] ,
                                                &Parametros[ 3 ] ,
                                                &Parametros[ 4 ] ) ;

            if ( ( qtdParamsLidos != qtdParamsEsperados )
              || ( Comandos[ cmd ].Validar( ComandoTeste ) == 0 ))
            {
               return TST_CondRetParm ;
            } /* if */

            /* O Retorno esperado é lido como o último parâmetro */
            return TST_CompararInt( Parametros[ qtdParamsLidos - 1 ] , Comandos[ cmd ].Funcao() ,
                                    Comandos[ cmd ].MsgErro ) ;
         } /* if */
      } /* for */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT Efetuar operações de teste específicas para matriz */


/*****  Código das funções internas ao módulo  *****/

/***********************************************************************
*
*  $FC Função: TMAT Validar Matriz
*
*  $ED Descrição da função
*     Valida os parâmetros recebidos em comandos de matriz
*
*  #EP Parâmetros
*     cmd - String do comando de teste a ser validado.
*
***********************************************************************/

   static int TMAT_ValMat( const char * cmd )
   {

      if ( ( strcmp( cmd , CMD_ESCREVER_CELULA ) == 0 )
        || ( strcmp( cmd , CMD_LER_CELULA ) == 0 ))
      {
         /* Valida índice da lista: Quarto parâmetro de ambas as funções */
         if ( ( Parametros[ 3 ] >= QTD_LISTAS )
           || ( Parametros[ 3 ] < 0 ))
         {
            return 0 ;
         } /* if */
      }  /* if */

      return ( Parametros[ 0 ] >= 0 ) && ( Parametros[ 0 ] <= QTD_MATRIZES ) ;

   } /* Fim função: TMAT Validar Matriz */


/***********************************************************************
*
*  $FC Função: TMAT Validar Lista
*
*  $ED Descrição da função
*     Valida os parâmetros recebidos em comandos de lista
*
*  #EP Parâmetros
*     cmd - String do comando de teste a ser validado.
*
***********************************************************************/

   static int TMAT_ValLis( const char * cmd )
   {

      return ( Parametros[ 0 ] >= 0 ) && ( Parametros[ 0 ] < QTD_LISTAS ) ;

   } /* Fim função TMAT Validar Lista */


/***********************************************************************
*
*  $FC Função: TMAT Comando Criar
*
*  $ED Descrição da função
*     Testa criação da matriz
*
***********************************************************************/

   static int TMAT_CmdCriar( void )
   {
      struct mat
      {
         void * a;
         void * b;
         int c ,
             d ,
             e ,
             f ;
      } ;

      if ( Parametros[ 0 ] == QTD_MATRIZES )
      {
         return MAT_CriarMatriz( NULL ) ;
      } /* if */

      /* Caso especial: cria uma matriz corrompida */
      if ( Parametros[ 0 ] == QTD_MATRIZES - 1 )
      {
         Matrizes[ Parametros[ 0 ]] = ( MAT_tppMatriz ) calloc( 100 , 1 ) ;
         if ( Matrizes[ Parametros[ 0 ]] == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */

         struct mat tmp ;
         memset( &tmp , 0 , sizeof( tmp ) ) ;
         tmp.c = 10 ;
         tmp.d = 10 ;
         tmp.e = 10 ;
         tmp.f = 10 ;

         memcpy( Matrizes[ Parametros[ 0 ]] , &tmp , sizeof( tmp )) ;
         return MAT_CondRetOK ;
      } /* if */

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

   static int TMAT_CmdDestruir( void )
   {

      /* Caso especial: destruir a matriz corrompida */
      if ( Parametros[ 0 ] == QTD_MATRIZES - 1 )
      {
         free( Matrizes[ Parametros[ 0 ]] ) ;
         return MAT_CondRetOK ;
      } /* if */

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

   static int TMAT_CmdInsCol( void )
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

   static int TMAT_CmdInsLin( void )
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

   static int TMAT_CmdLerCel( void )
   {

      MAT_tpCondRet ret ;
      LIS_tppLista lis ;

      /* Caso especial: param de retorno nulo */
      if ( ( Parametros[ 1 ] < 0 )
        || ( Parametros[ 2 ] < 0 ))
      {
         ret = MAT_LerCelula( Matrizes[ Parametros[ 0 ]] ,
                              Parametros[ 1 ] ,
                              Parametros[ 2 ] ,
                              NULL ) ;
      } else
      {
         ret = MAT_LerCelula( Matrizes[ Parametros[ 0 ]] ,
                              Parametros[ 1 ] ,
                              Parametros[ 2 ] ,
                              &lis ) ;
      } /* if */

      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      if ( lis != Listas[ Parametros[ 3 ]] )
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

   static int TMAT_CmdEscCel( void )
   {

      return MAT_EscreverCelula( Matrizes[ Parametros[ 0 ]],
                                 Parametros[ 1 ],
                                 Parametros[ 2 ],
                                 Listas[ Parametros[ 3 ]] ) ;

   } /* Fim função: TMAT Comando Escrever Célula */


/***********************************************************************
*
*  $FC Função: TMAT Comando Excluir Coluna
*
*  $ED Descrição da função
*     Testa a exclusão de colunas da matriz
*
***********************************************************************/

   static int TMAT_CmdExcCol( void )
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

   static int TMAT_CmdExcLin( void )
   {

      return MAT_ExcluirLinha( Matrizes[ Parametros[ 0 ]],
                               Parametros[ 1 ] ) ;

   } /* Fim função: TMAT Comando Excluir Linha */


/***********************************************************************
*
*  $FC Função: TMAT Comando Criar lista
*
*  $ED Descrição da função
*     Cria uma lista no índice passado como o primeiro parâmetro de
*     teste
*
***********************************************************************/

   static int TMAT_CmdCriarLis( void )
   {

      return LIS_CriarLista( &Listas[ Parametros[ 0 ]] ) ;

   } /* Fim função: Comando Criar lista */

/***********************************************************************
*
*  $FC Função: TMAT Comando Destruir lista
*
*  $ED Descrição da função
*     Destroi a lista no índice passado como o primeiro parâmetro de
*     teste
*
***********************************************************************/

   static int TMAT_CmdDestruirLis( void )
   {

      return LIS_DestruirLista( Listas[ Parametros[ 0 ]] ) ;
      Listas[ Parametros[ 0 ]] = NULL ;

   } /* Fim função: Comando Destruir lista */

/***********************************************************************
*
*  $FC Função: TMAT Comando Esvaziar lista
*
*  $ED Descrição da função
*     Remove todos os elementos da lista no índice passado como o
*     primeiro parâmetro de teste
*
***********************************************************************/

   static int TMAT_CmdEsvaziarLis( void )
   {

      return LIS_EsvaziarLista( Listas[ Parametros[ 0 ]] ) ;

   } /* Fim função: Comando Esvaziar lista */

/***********************************************************************
*
*  $FC Função: TMAT Comando Inserir na lista
*
*  $ED Descrição da função
*     Insere o caracter passado como o segundo parâmetro no comando de
*     teste na lista no índice passado como o primeiro parâmetro
*
***********************************************************************/

   static int TMAT_CmdInserirLis( void )
   {

      return LIS_InserirElementoApos( Listas[ Parametros[ 0 ]] , PARAM_CHAR( 1 )) ;

   } /* Fim função: Comando Inserir na lista */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
