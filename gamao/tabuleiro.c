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
*     Versão  Autor                Data     Observações
*       1.00  gbdo, gdapm, tdn   19/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Descrição...
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
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

typedef struct
{
   LIS_tppLista posicoes ;
      /* Lista de posições do tabuleiro.
       * Cada posição dessa lista contém uma lista com as peças
       * presentes da respectiva posição
       */
} tpTabuleiro ;


/*****  Prorótipos das funções internas ao módulo  *****/

static void liberar_posicao( void * pValor ) ;
static void liberar_peca( void * pValor ) ;


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: TAB Criar
*  ****/

   TAB_tpCondRet TAB_Criar( TAB_tppTabuleiro * pTabuleiro )
   {

      int i;
      LIS_tppLista lis = NULL ;

      tpTabuleiro * tab = ( tpTabuleiro *) malloc( sizeof( tpTabuleiro )) ;
      if ( tab == NULL )
         return TAB_CondRetMemoria ;

      /* Cria a lista principal */
      if ( LIS_CriarLista( &tab->posicoes, liberar_posicao ) != LIS_CondRetOK )
      {
         return TAB_CondRetMemoria ;
      }

      for ( i = 0 ; i < QUANTIDADE_POS ; i ++ )
      {
         if ( LIS_CriarLista( &lis, liberar_peca ) != LIS_CondRetOK )
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

   TAB_tpCondRet TAB_IncluirPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca pPeca )
   {
      LIS_tppLista pos ;
      assert( tabuleiro != NULL ) ;

   } /* Fim função: TAB Incluir peça */


/***************************************************************************
*
*  Função: TAB Mover peça
*  ****/

   TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int de , unsigned int para )
   {

   } /* Fim função: TAB Mover peça */


/***************************************************************************
*
*  Função: TAB Remover peça
*  ****/

   TAB_tpCondRet TAB_RemoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca * peca )
   {

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

static void liberar_posicao( void * pValor )
{
   LIS_DestruirLista( ( LIS_tppLista ) pValor ) ;
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

static void liberar_peca( void * pValor )
{

   PEC_Destruir( ( PEC_tppPeca ) pValor ) ;

}


/********** Fim do módulo de implementação: Módulo tabuleiro **********/

