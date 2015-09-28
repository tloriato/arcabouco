/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testtabuleiro.c
*  Letras identificadoras:      TTAB
*
*  Projeto: Disciplina INF 1301
*  Autores: gbdo - Gabriel Barbosa de Oliveira
*           gdapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor              Data       Observações
*       1.00  gbdo, gdapm, tdn   19/09/2015 Início do desenvolvimento
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
*     =incluir <int, int, int> - chama a função TAB_IncluirPeca( )
*         Parâmetros:
*         1 - tabuleiro
*         2 - posicao: Posição do tabuleiro aonde será incluída a peça
*         3 - peca: Peça a ser incluída
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
*         3 - peca: Parâmetro para retorno da peça removida
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


/***** Definições utilizados neste módulo de teste *****/


/* Quantidade máxima de instâncias do módulo que podem ser testadas
 * simultaneamente */
#define QTD_INSTANCIAS 1

/* Quantidade máxima de parâmetros permitidos em um comando de teste,
 * mais 1 para o retorno esperado */
#define MAX_PARAMS 4

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

static TAB_tppTabuleiro Pecas[ MAX_PECAS ] = { NULL } ;


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
   { CMD_INCLUIR_PECA , "iiii" ,    TTAB_CmdIncluirPeca , "Retorno errado ao incluir a peça" } ,
   { CMD_MOVER_PECA ,   "iiii" ,    TTAB_CmdMoverPeca ,   "Retorno errado ao mover a peça" } ,
   { CMD_REMOVER_PECA , "iiii" ,    TTAB_CmdRemoverPeca , "Retorno errado ao remover a peça" }
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
                                                &Parametros[ 3 ] ) ;

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
      int ret , corObtida , corEsperada ;

      if ( ( Parametros[ 2 ] < 0 )
        || ( Parametros[ 2 ] >= MAX_PECAS ) )
      {
         TST_NotificarFalha( "Índice de peça inválido" ) ;
         return TAB_CondRetOK ;
      } /* if */

      ret = TAB_RemoverPeca( Instancias[ Parametros[ 0 ] ] , Parametros[ 1 ] , &peca ) ;

      if ( ret == TAB_CondRetOK )
      {
         if ( PEC_ObterCor( peca , &corObtida ) != PEC_CondRetOK )
         {
            TST_NotificarFalha( "Erro ao obter a cor da peça" ) ;
            return TAB_CondRetOK ;
         } /* if */

         if ( PEC_ObterCor( Pecas[ Parametros[ 2 ] ], &corEsperada ) != PEC_CondRetOK )
         {
            TST_NotificarFalha( "Erro ao obter a cor da peça" ) ;
            return TAB_CondRetOK ;
         } /* if */

         if ( corObtida != corEsperada )
         {
            TST_NotificarFalha( "Cor da peça diferente da esperada" ) ;
         } /* if */
      }

      return ret ;

   } /* Fim função: TTAB Comando Remover peça */


/********** Fim do módulo de implementação: Módulo de teste específico **********/
