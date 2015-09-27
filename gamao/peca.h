#if ! defined( PECA_ )
#define PECA_
/**********************************************************************
*
*  $MCD Módulo de definição: Módulo Peça
*
*  Arquivo gerado:              peca.h
*  Letras identificadoras:      PEC
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
*     Módulo que representa uma peça em para ser usada em um tabuleiro.
*     Cada peça tem uma cor imutável definida em sua criação.
*
***********************************************************************/


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
***********************************************************************/

   typedef enum {

      PEC_CondRetOK = 0,
          /* Rodou sem erros */

	  PEC_CondRetPonteiroRetornoNulo = 1,
		  /* Ponteiro passado por parâmetro para retorno é NULL */

	  PEC_CondRetFaltouMemoria = 2
	      /* Faltou memória ao alocar dados */

   } PEC_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: Tipo abstrato de dados peça
*
***********************************************************************/
   
typedef void * PEC_tppPeca;

/***********************************************************************
*
*  $FC Função: PEC Criar
*
*  $ED Descrição da função
*     Cria uma peça da cor indicada
*
*  $EP Parâmetros
*     $P pPeca - Parâmetro para retorno da peça criada
*                Esse parâmetro é passado por referência
*     $P cor   - Cor da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*
***********************************************************************/

   PEC_tpCondRet Criar( PEC_tppPeca * pPeca , int cor ) ;

/***********************************************************************
*
*  $FC Função: PEC Destruir
*
*  $ED Descrição da função
*     Libera a memória ocupada pela peça
*
*  $EP Parâmetros
*     $P pPeca - Peça a ser destruída
*
*  $FV Valor retornado
*     PEC_CondRetOK
*
***********************************************************************/

   PEC_tpCondRet Destruir( PEC_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Função: PEC Obter cor
*
*  $ED Descrição da função
*     Obtém a cor da peça
*
*  $EP Parâmetros
*     $P pPeca - Peça
*     $P pCor  - Parâmetro para retorno da cor da peça
*                Esse parâmetro é passado por referência
*
*  $FV Valor retornado
*     PEC_CondRetOK
*
***********************************************************************/

   PEC_tpCondRet ObterCor( PEC_tppPeca pPeca , int * pCor ) ;


#undef PECA_

/********** Fim do módulo de definição: Módulo Peça **********/

#else
#endif
