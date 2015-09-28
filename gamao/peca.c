/**********************************************************************
*
*  $MCD Módulo de definição: Módulo Peça
*
*  Arquivo gerado:              peca.c
*  Letras identificadoras:      PEC
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data       Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Esse módulo é uma peça que pode ser usada em um tabuleiro.
*     Cada peça tem apenas uma cor imutável e definida na sua criação.
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <assert.h>
#include   "peca.h"

typedef struct peca
{
   int cor ; /* Cor da peça */
} tpPeca ;


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: PEC Criar
*  ****/

   PEC_tpCondRet PEC_Criar( PEC_tppPeca * pPeca , int cor )
   {
      tpPeca * peca;

      assert( pPeca != NULL ) ;

      *pPeca = ( tpPeca * ) malloc( sizeof( tpPeca ) ) ;

      if ( *pPeca == NULL )
      {
         return PEC_CondRetFaltouMemoria ;
      } /* if */

      peca = ( tpPeca *) *pPeca ;
      peca->cor = cor;

      return PEC_CondRetOK ;

   } /* Fim função: PEC Criar */


/***************************************************************************
*
*  Função: PEC Destruir
*  ****/

   PEC_tpCondRet PEC_Destruir( PEC_tppPeca pPeca )
   {
      tpPeca * peca = ( tpPeca * ) pPeca ;

      free( peca );

      return PEC_CondRetOK ;

   } /* Fim função: PEC Destruir */


/***************************************************************************
*
*  Função: PEC Obter cor
*  ****/

   PEC_tpCondRet PEC_ObterCor( PEC_tppPeca pPeca , int * pCor )
   {

      assert( pPeca != NULL ) ;
      assert( pCor != NULL ) ;

      tpPeca * peca = ( tpPeca * ) pPeca ;
      *pCor = peca->cor ;

      return PEC_CondRetOK ;

   } /* Fim função: PEC Obter cor */


/*****  Código das funções encapsuladas pelo módulo  *****/


/********** Fim do módulo de implementação: Módulo Peça **********/

