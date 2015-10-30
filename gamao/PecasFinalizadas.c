/**********************************************************************
*
*  $MCD Módulo de definição: Módulo peças finalizadas
*
*  Arquivo gerado:              pecasfinalizadas.c
*  Letras identificadoras:      PFN
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data        Observações
*       1.00  gbo, gapm, tdn, pa  23/10/2015  Início do desenvolvimento
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
#include "PecasFinalizadas.h"


/***********************************************************************
*
*  $TC Tipo de dados: PFN Estrutura finalizadas
*
*
***********************************************************************/

struct tpFinalizadas
{
   LIS_tppLista finalizadas ;
   /* Lista com os peças finalizdas
    * de cada jogador
    */
};

/*****  Prorótipos das funções internas ao módulo  *****/

   static void LiberarPeca( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: PFN Criar Lista
*
***************************************************************************/

   PFN_tpCondRet PFN_Criar ( PFN_tppFinalizadas * pFinalizadas )
   {
      *pFinalizadas = ( PFN_tppFinalizadas ) malloc ( sizeof ( PFN_tppFinalizadas ) ) ;

      if ( pFinalizadas == NULL ) 
      {
         return PFN_CondRetMemoria ;
      } /* if */

      if ( LIS_CriarLista ( &(*pFinalizadas)->finalizadas , LiberarPeca ) != LIS_CondRetOK  )
      {
         return PFN_CondRetMemoria ;
      } /* if */

      return PFN_CondRetOK ;

   } /* Fim função: PFN Criar Lista */

/***************************************************************************
*
*  Função: PFN Destruir Lista
*
***************************************************************************/

   PFN_tpCondRet PFN_Destruir ( PFN_tppFinalizadas pFinalizadas )
   {
      if ( pFinalizadas == NULL )
      {
         return PFN_CondRetOK ;
      } /* if */

      LIS_DestruirLista ( pFinalizadas->finalizadas ) ;

      return PFN_CondRetOK ;

   } /* Fim função: PFN Destruir Lista */

/***************************************************************************
*
*  Função: PFN Inserir Peça
*
***************************************************************************/

   PFN_tpCondRet PFN_InserirPeca ( PFN_tppFinalizadas pFinalizadas , PEC_tppPeca peca )
   {
      assert ( pFinalizadas != NULL ) ;

      if ( LIS_InserirElementoApos ( pFinalizadas->finalizadas , ( void * ) peca ) != LIS_CondRetOK ) 
      {
         return PFN_CondRetMemoria ;
      } /* if */

      return PFN_CondRetOK ;

   } /* FIm função: PFN Inserir Peça */

/***************************************************************************
*
*  Função: PFN Conta Pecas
*
***************************************************************************/

   PFN_tpCondRet PFN_ContaPecas ( PFN_tppFinalizadas pFinalizadas , int * qtd_pecas )
   {

      PEC_tppPeca peca = NULL ;
      LIS_tppLista lis = pFinalizadas->finalizadas ;

      assert ( pFinalizadas != NULL ) ;
      assert ( qtd_pecas != NULL ) ;

      LIS_IrInicioLista(lis) ;

      if ( LIS_ObterValor ( lis , (void ** ) &peca ) != LIS_CondRetOK )
      {
         *qtd_pecas = 0 ;
         return PFN_CondRetOK ;
      } /* if */

      *qtd_pecas = 1 ;

      while ( LIS_AvancarElementoCorrente ( lis , 1 ) != LIS_CondRetFimLista )
      {
         ( *qtd_pecas ) ++ ;
      } /* while */

      return PFN_CondRetOK ;

   } /* Fim função: PFN Contar Pecças */


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

   } /* Fim função Liberar peça */
