/**********************************************************************
*
*  $MCD Módulo de definição: Módulo peças finalizadas.
*
*  Arquivo gerado:              pecascapturadas.c
*  Letras identificadoras:      PCA
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data           Observações
*       1.00  gbo, gapm, tdn, pa  27/10/2015   Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Tipo abstrato de dados que encapsula uma lista de estruturas Peça
*     capturadas de cada jogador
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"
#include "peca.h"
#include "PecasCapturadas.h"


/***********************************************************************
*
*  $TC Tipo de dados: PCA Estrutura capturadas
*
*
***********************************************************************/

struct tpCapturadas 
{
   LIS_tppLista capturadas ;
   /* Lista com os peças capturadas
    * de cada jogador
    */
};

/*****  Prorótipos das funções internas ao módulo  *****/

static void LiberarPeca( void * pValor ) ;


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: PCA Criar Lista
*
***************************************************************************/

   PCA_tpCondRet PCA_Criar ( PCA_tppCapturadas * pCapturadas )
   {
      *pCapturadas  = ( PCA_tppCapturadas ) malloc ( sizeof ( PCA_tppCapturadas ) ) ;

      if ( pCapturadas == NULL ) 
      {
         return PCA_CondRetMemoria ;
      } /* if */

      if ( LIS_CriarLista ( &(*pCapturadas)->capturadas , LiberarPeca ) != LIS_CondRetOK  )
      {
         free( pCapturadas ) ;
         return PCA_CondRetMemoria ;
      } /* if */

      return PCA_CondRetOK ;

   } /* Fim função: PCA Criar Lista */

/***************************************************************************
*
*  Função: PCA Destruir
*
***************************************************************************/

   PCA_tpCondRet PCA_Destruir ( PCA_tppCapturadas pCapturadas )
   {
      if ( pCapturadas == NULL )
      {
         return PCA_CondRetOK ;
      } /* if */

      LIS_DestruirLista ( pCapturadas->capturadas ) ;

      return PCA_CondRetOK ;

   } /* Fim função: PCA Destruir */

/***************************************************************************
*
*  Função: PCA Inserir Peça
*
***************************************************************************/

   PCA_tpCondRet PCA_InserirPeca ( PCA_tppCapturadas pCapturadas , PEC_tppPeca peca )
   {
      assert ( pCapturadas != NULL ) ;

      if ( LIS_InserirElementoApos ( pCapturadas->capturadas , ( void * ) peca ) != LIS_CondRetOK )
      {
         return PCA_CondRetMemoria ;
      } /* if */

      return PCA_CondRetOK ;

   } /* FIm função: PCA Inserir Peça */

/***************************************************************************
*
*  Função: PCA Conta Pecas
*
***************************************************************************/

   PCA_tpCondRet PCA_ContaPecas ( PCA_tppCapturadas pCapturadas , int * qtd_pecas , int pCor )
   {
      PEC_tppPeca peca = NULL ;
      struct tpCapturadas * lis = pCapturadas ;

      assert ( pCapturadas != NULL ) ;
      assert ( qtd_pecas != NULL ) ;


      LIS_IrInicioLista( lis->capturadas ) ;

      if ( LIS_ObterValor ( lis->capturadas , (void ** ) &peca ) != LIS_CondRetOK )
      {
         *qtd_pecas = 0 ;
         return PCA_CondRetOK ;
      } /* if */


      PEC_ObterCor( peca , &pCor ) ;
      *qtd_pecas = 1 ;

      while ( LIS_AvancarElementoCorrente ( lis->capturadas , 1 ) != LIS_CondRetFimLista )
      {
         ( *qtd_pecas ) ++ ;
      } /* while */

      return PCA_CondRetOK ;

   } /* Fim função: PCA Conta Peças */

/*****  Código das funções encapsuladas pelo módulo  *****/

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

   } /* Fim função: Liberar peça */
