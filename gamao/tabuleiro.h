#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/**********************************************************************
*
*  $MCD Módulo de definição: Módulo tabuleiro
*
*  Arquivo gerado:              tabuleiro.h
*  Letras identificadoras:      TAB
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
*     Descrição...
*
***********************************************************************/

#include "peca.h"

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
***********************************************************************/

   typedef enum {

      TAB_CondRetOK = 0 ,
          /* Rodou sem erros */

      TAB_CondRetPosInvalida = 1 ,
          /* Não existe a posição solicitada */

      TAB_CondRetPosVazia = 2 ,
          /* Não é possível mover uma peça de uma posição vazia */

      TAB_CondRetMemoria = 3
          /* Erro ao alocar memória */

   } TAB_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Tipo abstrato tabuleiro
*
*
***********************************************************************/

typedef struct tpTabuleiro * TAB_tppTabuleiro ;

/***********************************************************************
*
*  $FC Função: TAB Criar
*
*  $ED Descrição da função
*     Cria um tabuleiro vazio
*
*  $EP Parâmetros
*     $P pTabuleiro - Parâmetro de retorno do tabuleiro criado.
*                     Esse parâmetro é passado por referência
*
*  $EAE Assertivas de entradas esperadas
*     pTabuleiro != NULL
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMemoria
*
***********************************************************************/

   TAB_tpCondRet TAB_Criar( TAB_tppTabuleiro * pTabuleiro ) ;

/***********************************************************************
*
*  $FC Função: TAB Destruir
*
*  $ED Descrição da função
*     Destroi o tabuleiro e as peças nele contidas
*
*  $EP Parâmetros
*     $P tabuleiro - Tabuleiro a ser destruído
*
*  $EAE Assertivas de entradas esperadas
*     tabuleiro != NULL
*
*  $FV Valor retornado
*     TAB_CondRetOK
*
***********************************************************************/

   TAB_tpCondRet TAB_Destruir( TAB_tppTabuleiro tabuleiro ) ;

/***********************************************************************
*
*  $FC Função: TAB Incluir peça
*
*  $ED Descrição da função
*     Inclui uma peça na posição desejada
*
*  $EP Parâmetros
*     $P tabuleiro - Tabuleiro a ser operado
*     $P posicao   - Posição do tabuleiro aonde será incluída a peça
*     $P peca     - Peça a ser incluída
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosInvalida
*
***********************************************************************/

   TAB_tpCondRet TAB_IncluirPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca peca ) ;

/***********************************************************************
*
*  $FC Função: TAB Mover peça
*
*  $ED Descrição da função
*     Move uma peça de uma posição para outra
*
*  $EP Parâmetros
*     $P tabuleiro - Tabuleiro a ser operado
*     $P de        - Posição de origem da peça
*     $P para      - Posição de destino da peça
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosInvalida
*     TAB_CondRetPosVazia
*
***********************************************************************/

   TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int de , unsigned int para ) ;

/***********************************************************************
*
*  $FC Função: TAB Remover peça
*
*  $ED Descrição da função
*     Remove uma peça da posição indicada e a retorna no parâmetro
*     peça.
*
*  $EP Parâmetros
*     $P tabuleiro - Tabuleiro a ser operado
*     $P posicao   - Posição da peça
*     $P peca      - Parâmetro para retorno da peça removida
*                    Esse parâmetro é passado por referência
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosInvalida
*     TAB_CondRetPosVazia
*
***********************************************************************/

   TAB_tpCondRet TAB_RemoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca * peca ) ;


#undef TABULEIRO_

/********** Fim do módulo de definição: Módulo tabuleiro **********/

#else
#endif
