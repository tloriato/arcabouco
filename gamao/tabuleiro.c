/**********************************************************************
*
*  $MCD Módulo de definição: Módulo tabuleiro
*
*  Arquivo gerado:              tabuleiro.c
*  Letras identificadoras:      TAB
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
*     Descrição...
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <stdbool.h>
#include   <assert.h>
#include   "tabuleiro.h"
#include   "lista.h"


/***********************************************************************
*
*  Definição: MAT Quantidade de posições no tabuleiro
*
***********************************************************************/

#define QUANTIDADE_POS 24


/***********************************************************************
*
*  $TC Tipo de dados: TAB Estrutura tabuleiro
*
*
***********************************************************************/

struct tpTabuleiro
{
   LIS_tppLista posicoes ;
      /* Lista de posições do tabuleiro.
       * Cada posição dessa lista contém uma lista com as peças
       * presentes da respectiva posição
       */
} ;


/*****  Prorótipos das funções internas ao módulo  *****/

static void LiberarPosicao( void * pValor ) ;
static void LiberarPeca( void * pValor ) ;
static LIS_tppLista ObterListaPosicao( TAB_tppTabuleiro tabuleiro,
                                       unsigned int posicao ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: TAB Criar
*  ****/

   TAB_tpCondRet TAB_Criar( TAB_tppTabuleiro * pTabuleiro )
   {

      int i;
      LIS_tppLista lis = NULL ;

      struct tpTabuleiro * tab = ( struct tpTabuleiro *) malloc( sizeof( struct tpTabuleiro )) ;
      if ( tab == NULL )
         return TAB_CondRetMemoria ;

      /* Cria a lista principal */
      if ( LIS_CriarLista( &tab->posicoes, LiberarPosicao ) != LIS_CondRetOK )
      {
         return TAB_CondRetMemoria ;
      }

      for ( i = 0 ; i < QUANTIDADE_POS ; i ++ )
      {
         if ( LIS_CriarLista( &lis, LiberarPeca ) != LIS_CondRetOK )
         {
            /* Se tivemos problema com a lista, desfaz tudo
             * (evita vazamento de memória) */
            TAB_Destruir( *pTabuleiro ) ;
            return TAB_CondRetMemoria ;
         }

         if ( LIS_InserirElementoApos( tab->posicoes, ( void * ) lis ) != LIS_CondRetOK )
         {
            /* Se tivemos problema com a lista, desfaz tudo
             * (evita vazamento de memória) */
            LIS_DestruirLista( lis ) ;
            TAB_Destruir( *pTabuleiro ) ;
            return TAB_CondRetMemoria ;
         }
      }

      return TAB_CondRetOK ;

   } /* Fim função: TAB Criar */


/***************************************************************************
*
*  Função: TAB Destruir
*  ****/

   TAB_tpCondRet TAB_Destruir( TAB_tppTabuleiro tabuleiro )
   {

      if ( tabuleiro == NULL )
      {
         return TAB_CondRetOK ;
      }

      LIS_DestruirLista( tabuleiro->posicoes ) ;

      return TAB_CondRetOK ;

   } /* Fim função: TAB Destruir */


/***************************************************************************
*
*  Função: TAB Incluir peça
*  ****/

   TAB_tpCondRet TAB_IncluirPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca peca )
   {

      LIS_tppLista pos ;
      assert( tabuleiro != NULL ) ;

      if ( posicao >= QUANTIDADE_POS )
      {
         return TAB_CondRetPosInvalida ;
      }

      pos = ObterListaPosicao( tabuleiro , posicao ) ;
      assert( pos != NULL ) ;

      if ( LIS_InserirElementoApos( pos, ( void * ) peca ) != LIS_CondRetOK )
      {
         return TAB_CondRetMemoria ;
      }

   } /* Fim função: TAB Incluir peça */


/***************************************************************************
*
*  Função: TAB Mover peça
*  ****/

   TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int de , unsigned int para )
   {

      assert( tabuleiro != NULL ) ;

      LIS_tppLista lDe , lPara ;
      PEC_tppPeca pec ;

      if (( de >= QUANTIDADE_POS ) || ( para >= QUANTIDADE_POS ))
      {
         return TAB_CondRetPosInvalida ;
      }

      if ( de == para )
      {
         return TAB_CondRetOK ;
      }

      lDe = ObterListaPosicao( tabuleiro , de ) ;
      lPara = ObterListaPosicao( tabuleiro , para ) ;

      assert( lDe != NULL ) ;
      assert( lPara != NULL ) ;

      if ( LIS_ObterValor( lDe , ( void ** ) &pec ) != LIS_CondRetOK )
      {
         return TAB_CondRetPosVazia ;
      }

      if ( LIS_InserirElementoAntes( lPara, ( void * ) pec ) != LIS_CondRetOK )
      {
         return TAB_CondRetMemoria ;
      }

      /* Impede que a peça seja desalocada */
      LIS_DefinirFuncaoExcluir( lDe, NULL ) ;

      /* Já sabemos que a peça existe. Não é preciso testar o retorno */
      LIS_ExcluirElemento( lDe ) ;

      return TAB_CondRetOK ;

   } /* Fim função: TAB Mover peça */


/***************************************************************************
*
*  Função: TAB Remover peça
*  ****/

   TAB_tpCondRet TAB_RemoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca * peca )
   {

      assert( tabuleiro != NULL ) ;
      assert( peca != NULL ) ;

      LIS_tppLista pos = NULL ;

      if ( posicao >= QUANTIDADE_POS )
      {
         return TAB_CondRetPosInvalida ;
      }

      pos = ObterListaPosicao( tabuleiro, posicao ) ;

      if ( LIS_IrInicioLista( pos ) != LIS_CondRetOK )
      {
         return TAB_CondRetPosVazia ;
      }

      /* Já sabemos que a peça existe. Não é preciso testar a condição
       * de retorno novamente */
      LIS_ObterValor( pos , ( void ** ) peca ) ;
      LIS_DefinirFuncaoExcluir( pos , NULL ) ; /* Evita desalocação da peça */
      LIS_ExcluirElemento( pos ) ;

      return TAB_CondRetOK ;

   } /* Fim função: TAB Remover peça */


/*****  Código das funções encapsuladas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: Liberar Posição
*
*  $ED Descrição da função
*     Destroi a lista e as peças de uma posição do tabuleiro
*
*  $EP Parâmetros
*     $P pValor - Lista a ser destruída
*
***********************************************************************/

static void LiberarPosicao( void * pValor )
{

   LIS_tppLista lis = ( LIS_tppLista ) pValor ;

   LIS_DefinirFuncaoExcluir( lis , LiberarPeca ) ;
   LIS_DestruirLista( lis ) ;

}


/***********************************************************************
*
*  $FC Função: Liberar Peça
*
*  $ED Descrição da função
*     Destroi a peça indicada
*
*  $EP Parâmetros
*     $P pValor - Peça a ser destruída
*
***********************************************************************/

static void LiberarPeca( void * pValor )
{

   PEC_Destruir( ( PEC_tppPeca ) pValor ) ;

}


/***********************************************************************
*
*  $FC Função: Obter Lista Posição
*
*  $ED Descrição da função
*     Obtém a lista de peças correspondente a posição desejada
*
*  $EP Parâmetros
*     $P tabuleiro  -  Tabuleiro a ser indexado
*     $P posicao    -  Posição desejada dentro do tabuleiro
*
*  $EAE Assertivas de entradas esperadas
*     tabuleiro != NULL
*     posicao < QUANTIDADE_POS
*
*  $FV Valor retornado
*     Lista correspondente a linha desejada
*
*
***********************************************************************/

static LIS_tppLista ObterListaPosicao( TAB_tppTabuleiro tabuleiro,
                                       unsigned int posicao )
{

   assert( tabuleiro != NULL ) ;
   assert( posicao < QUANTIDADE_POS ) ;

   LIS_tppLista ret = NULL ;

   if ( LIS_IrInicioLista( tabuleiro->posicoes ) != LIS_CondRetOK )
   {
      return NULL ;
   }

   if ( LIS_AvancarElementoCorrente( tabuleiro->posicoes , posicao ) != LIS_CondRetOK )
   {
      return NULL ;
   }

   if ( LIS_ObterValor( tabuleiro->posicoes , ( void ** ) &ret ) != LIS_CondRetOK )
   {
      return NULL ;
   }

   return ret ;

} /* Fim função Obter Lista Posição */


/********** Fim do módulo de implementação: Módulo tabuleiro **********/
