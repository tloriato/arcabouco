/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testtabuleiro.c
*  Letras identificadoras:      TTAB
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor            Data       Observações
*       1.00  gbo, gapm, tdn   19/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo tabuleiro.
*
*  $EIU Interface com o usuário
*     Comandos de teste específicos para testar o módulo tabuleiro:
*
*     =criar <int> - chama a função TAB_Criar( )
*         Parâmetros:
*         1 - tabuleiro
*
*     =destruir <int> - chama a função TAB_Destruir( )
*         Parâmetros:
*         1 - tabuleiro
*
*     =incluir <int, int, int, int> - cria uma peça da cor especificada e
*                                     chama a função TAB_IncluirPeca( )
*         Parâmetros:
*         1 - tabuleiro
*         2 - posicao: Posição do tabuleiro aonde será incluída a peça
*         3 - peca: ID da peça a ser incluída
*         4 - cor da peça
*
*     =mover <int, int, int> - chama a função TAB_MoverPeca( )
*         Parâmetros:
*         1 - tabuleiro
*         2 - de: Posição de origem da peça
*         3 - para: Posição de destino da peça
*
*     =remover <int, int, int> - chama a função TAB_RemoverPeca( )
*         Parâmetros:
*         1 - tabuleiro
*         2 - posicao: Posição da peça
*         3 - cor da peca: Cor esperada da peça removida
*
*     =contar <int, int, int, int> - chama a função TAB_ContarPecas( )
*        Parâmetros:
*        1 - tabuleiro
*        2 - posição
*        3 - quantidade esperada
*        4 - cor esperada
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tst_espc.h"
#include "generico.h"
#include "lerparm.h"
#include "tabuleiro.h"
#include "peca.h"

/* Nomes dos comandos de teste específicos */
const char CMD_CRIAR        [] = "=criar" ;
const char CMD_DESTRUIR     [] = "=destruir" ;
const char CMD_INCLUIR_PECA [] = "=incluir" ;
const char CMD_MOVER_PECA   [] = "=mover" ;
const char CMD_REMOVER_PECA [] = "=remover" ;
const char CMD_CONTAR       [] = "=contar" ;


/***** Definições utilizados neste módulo de teste *****/


/* Quantidade máxima de instâncias do módulo que podem ser testadas
 * simultaneamente */
#define QTD_INSTANCIAS 1

/* Quantidade máxima de parâmetros permitidos em um comando de teste,
 * mais 1 para o retorno esperado */
#define MAX_PARAMS 5

/* Quantidade máxima de peças que podem ser utilizadas simultaneamente
 * no teste do tabuleiro */
#define MAX_PECAS 4

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
*  $TC Tipo de dados: TTAB Descritor do comando de teste
*
*  $ED Descrição do tipo
*     Descreve a associação do comando de teste com a função de
*     tratamento e os parâmetros esperados
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

   char * MsgErro;
      /* mensagem de erro que será mostrada em caso de falha */

} tpComandoTeste;


/*****  Protóripos das funções *****/

static int TTAB_CmdCriar( void ) ;
static int TTAB_CmdDestruir( void ) ;
static int TTAB_CmdIncluirPeca( void ) ;
static int TTAB_CmdMoverPeca( void ) ;
static int TTAB_CmdRemoverPeca( void ) ;
static int TTAB_CmdContar( void ) ;


/*****  Variáveis globais à este módulo  *****/

/***************************************************************************
*
*  Vetor: Instâncias
*  Descrição: Lista de instâncias do módulo usadas nos testes
*
*  ****/

static TAB_tppTabuleiro Instancias[ QTD_INSTANCIAS ] = { NULL } ;


/***************************************************************************
*
*  Vetor: Peças
*  Descrição: Lista de peças que podem ser incluídas no tabuleiro
*
*  ****/

static PEC_tppPeca Pecas[ MAX_PECAS ] = { NULL } ;


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
*  Vetor: Comandos
*  Descrição: Vetor que associa os comandos de teste às funções de tratamento
*  Obs.: Incluir um 'i' no final dos parâmetros para o retorno esperado
*
*  ****/

static tpComandoTeste Comandos[] = {
/*   Comando            Parâmetros  Função                Mensagem de erro */
   { CMD_CRIAR ,        "ii" ,      TTAB_CmdCriar ,       "Retorno errado ao criar o tabuleiro" } ,
   { CMD_DESTRUIR ,     "ii" ,      TTAB_CmdDestruir ,    "Retorno errado ao destruir o tabuleiro" } ,
   { CMD_INCLUIR_PECA , "iiiii" ,   TTAB_CmdIncluirPeca , "Retorno errado ao incluir a peça" } ,
   { CMD_MOVER_PECA ,   "iiii" ,    TTAB_CmdMoverPeca ,   "Retorno errado ao mover a peça" } ,
   { CMD_REMOVER_PECA , "iiii" ,    TTAB_CmdRemoverPeca , "Retorno errado ao remover a peça" } ,
   { CMD_CONTAR,        "iiiii" ,   TTAB_CmdContar ,      "Retorno errado ao contar as peças" }
} ;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB Efetuar operações de teste específicas
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     sendo testado.
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

            /* Parametros[ 0 ] é o número da instância do módulo */
            if ( ( qtdParamsLidos != qtdParamsEsperados )
              || ( Parametros[ 0 ] < 0 )
              || ( Parametros[ 0 ] >= QTD_INSTANCIAS ) )
            {
               return TST_CondRetParm ;
            } /* if */

            /* O Retorno esperado é lido como o último parâmetro */
            return TST_CompararInt( Parametros[ qtdParamsLidos - 1 ] , Comandos[ cmd ].Funcao() ,
                                    Comandos[ cmd ].MsgErro ) ;
         } /* if */
      } /* for */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TTAB Efetuar operações de teste específicas */


/*****  Código das funções internas ao módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB Comando Criar
*
*  $ED Descrição da função
*     Testa criação do tabuleiro
*
***********************************************************************/

   static int TTAB_CmdCriar( void )
   {

      return TAB_Criar( &Instancias[ Parametros[ 0 ] ] ) ;

   } /* Fim função: TTAB Comando Criar */


/***********************************************************************
*
*  $FC Função: TTAB Comando Destruir
*
*  $ED Descrição da função
*     Testa a desalocação do tabuleiro
*
***********************************************************************/

   static int TTAB_CmdDestruir( void )
   {

      int ret = TAB_Destruir( Instancias[ Parametros[ 0 ] ] ) ;
      Instancias[ Parametros[ 0 ] ] = NULL ;
      return ret ;

   } /* Fim função: TTAB Comando Destruir */


/***********************************************************************
*
*  $FC Função: TTAB Comando Incluir peça
*
*  $ED Descrição da função
*     Testa a inclusão de peças
*
***********************************************************************/

   static int TTAB_CmdIncluirPeca( void )
   {

      if ( ( Parametros[ 2 ] < 0 )
        || ( Parametros[ 2 ] >= MAX_PECAS ) )
      {
         TST_NotificarFalha( "Índice de peça inválido" ) ;
         return TAB_CondRetOK ;
      } /* if */

      PEC_Criar( &Pecas[ Parametros[ 2 ] ] , Parametros[ 3 ] ) ;
      return TAB_IncluirPeca( Instancias[ Parametros[ 0 ] ] , Parametros[ 1 ] , Pecas[ Parametros[ 2 ] ] ) ;

   } /* Fim função: TTAB Comando Incluir peça */


/***********************************************************************
*
*  $FC Função: TTAB Comando Mover peça
*
*  $ED Descrição da função
*     Testa a movimentação de peças
*
***********************************************************************/

   static int TTAB_CmdMoverPeca( void )
   {

      return TAB_MoverPeca( Instancias[ Parametros[ 0 ] ] , Parametros[ 1 ] , Parametros[ 2 ] ) ;

   } /* Fim função: TTAB Comando Mover peça */


/***********************************************************************
*
*  $FC Função: TTAB Comando Remover peça
*
*  $ED Descrição da função
*     Testa a remoção de peças
*
***********************************************************************/

   static int TTAB_CmdRemoverPeca( void )
   {

      PEC_tppPeca peca ;
      TAB_tpCondRet ret ;
      int  corObtida ;

      ret = TAB_RemoverPeca( Instancias[ Parametros[ 0 ] ] , Parametros[ 1 ] , &peca ) ;

      if ( ret == TAB_CondRetOK )
      {
         if ( PEC_ObterCor( peca , &corObtida ) != PEC_CondRetOK )
         {
            TST_NotificarFalha( "Erro ao obter a cor da peça" ) ;
            return TAB_CondRetOK ;
         } /* if */

         if ( corObtida != Parametros[ 2 ] )
         {
            TST_NotificarFalha( "Cor da peça diferente da esperada" ) ;
         } /* if */

         PEC_Destruir( peca ) ;
      }

      return ret ;

   } /* Fim função: TTAB Comando Remover peça */


/***********************************************************************
*
*  $FC Função: TTAB Comando Contar
*
*  $ED Descrição da função
*     Testa a contagem de peças em uma posição do tabuleiro
*
***********************************************************************/

   static int TTAB_CmdContar( void )
   {

      unsigned int quantidade ;
      int cor ;
      TAB_tpCondRet ret ;

      ret = TAB_ContarPecas( Instancias[ Parametros [ 0 ] ] , Parametros[ 1 ] , &quantidade , &cor ) ;
      if ( ret == TAB_CondRetOK )
      {
         if ( ( int )quantidade != Parametros[ 2 ] )
         {
            TST_NotificarFalha( "Quantidade diferente da esperada." ) ;
            return ret ;
         } /* if */

         if ( ( cor != Parametros[ 3 ] ) && ( quantidade > 0 ) )
         {
            TST_NotificarFalha( "Cor diferente da esperada." ) ;
            return ret ;
         } /* if */
      } /* if */

      return ret ;

   } /* Fim função: TTAB Comando Contar */


/********** Fim do módulo de implementação: Módulo de teste específico **********/
