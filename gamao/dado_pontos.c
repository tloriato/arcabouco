/**********************************************************************
*
*  $MCD Módulo de definição: Módulo dado pontos
*
*  Arquivo gerado:              dado_pontos.c
*  Letras identificadoras:      DPO
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data     Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Encapsula uma estrutura DadoPontos, armazena qual jogador pode 
*     dobrar o valor da partida e informa o valor atual da partida.
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   "dado_pontos.h"
#include   <assert.h>

#define PODE 1
#define NAO_PODE 0


typedef struct dadopontos {
	int ValorPartida;
		/* Valor da partida no momento */

	DPO_tpJogador JogadorPodeDobrar;
		/* Qual jogador que pode dobrar o valor da partida */

	int PontosJogador1;
		/* Pontuação do jogador 1 */

	int PontosJogador2;
		/* Pontuação do jogador 2 */
} DadoPontos ;

 static DadoPontos Pontos = {1 , ( DPO_tpJogador ) 0 , 0 , 0 } ;

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: DPO Dobrar pontos
*  ****/

   DPO_tpCondRet DPO_DobrarPontos( DPO_tpJogador jogador )
   {
	   if ( Pontos.ValorPartida == 64 )
	   {
		   return DPO_CondRetMaxPontos;
	   } /* if */

	   Pontos.ValorPartida *= 2;

	   if ( jogador == DPO_Jogador1 )
	   {
		   Pontos.JogadorPodeDobrar = DPO_Jogador2 ;
	   } /* if */

	   else
	   {
		   Pontos.JogadorPodeDobrar = DPO_Jogador1 ;
	   }

	   return DPO_CondRetOK ;

   } /* Fim função: DPO Dobrar pontos */


/***************************************************************************
*
*  Função: DPO Pode dobrar
*  ****/

   DPO_tpCondRet DPO_PodeDobrar( DPO_tpJogador jogador , int * res )
   {

	   assert ( res != NULL ) ;

	   if ( Pontos.JogadorPodeDobrar == 0 )
	   {
		   *res = PODE ;
	   } /* if */

	   else if ( jogador == Pontos.JogadorPodeDobrar )
	   {
		   *res = PODE ;
	   } /* if */

	   else
	   {
		   *res = NAO_PODE ;
		   return DPO_JogadorNaoPodeDobrar ;
	   }

	   return DPO_CondRetOK ;

   } /* Fim função: DPO Pode dobrar */


/***************************************************************************
*
*  Função: DPO Obter pontos
*  ****/

   DPO_tpCondRet DPO_ObterPontos( int * pontos )
   {

	   assert ( pontos != NULL ) ;

	   *pontos = Pontos.ValorPartida;

	   return DPO_CondRetOK ;

   } /* Fim função: DPO Obter pontos */


/*****  Código das funções encapsuladas pelo módulo  *****/


/********** Fim do módulo de implementação: Módulo dado pontos **********/

