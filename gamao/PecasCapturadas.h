#if ! defined( CAPTURADAS_ )
#define CAPTURADAS_
/**********************************************************************
*
*  $MCD Módulo de definição: Módulo peças capturadas
*
*  Arquivo gerado:              pecascapturadas.h
*  Letras identificadoras:      PCA
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data       Observações
*       1.00  gbo, gapm, tdn, pa  26/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Tipo abstrato de dados que encapsula uma lista de estruturas Peça
*     capturadas de cada jogador
*
***********************************************************************/

#include "peca.h"

/***********************************************************************
*
*  $TC Tipo de dados: PCA Condições de retorno
*
*
***********************************************************************/

   typedef enum {

      PCA_CondRetOK = 0 ,
          /* Rodou sem erros */

      PCA_CondRetMemoria = 1
          /* Erro ao alocar memória */

   } PCA_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: PCA Tipo abstrato peças capturadas
*
*
***********************************************************************/

typedef struct tpCapturadas * PCA_tppCapturadas ;

/***********************************************************************
*
*  $FC Função: PCA Criar
*
*  $ED Descrição da função
*     Cria uma lista de peças capturadas vazia
*
*  $EP Parâmetros:
*     $P pCapturadas   - Parâmetro de retorno do lista de pças
*                        capturadas criada.
*                        Esse parâmetro é passado por referência
*
*  Assertivas de entrada:
*     - O ponteiro passado como parametro deve ser válido.
*
*  Assertivas de saída:
*     - *pCapturadas deve conter a lista de peças capturadas criada.
*
*  $FV Valor retornado:
*     PCA_CondRetOK
*     PCA_CondRetMemoria
*
***********************************************************************/

   PCA_tpCondRet PCA_Criar( PCA_tppCapturadas * pCapturadas ) ;

/***********************************************************************
*
*  $FC Função: PCA Destruir
*
*  $ED Descrição da função:
*     Destroi a lista e as peças nela contidas
*
*  $EP Parâmetros:
*     $P pCapturadas - Lista de peças capturadas a ser destruída
*
*  Assertivas de entrada:
*     - pCapturadas deve ser uma instância válida de lista de peças capturadas.
*
*  Assertivas de saída:
*     - A memória ocupada pela lista passada por parâmetro deve
*       ser desalocada.
*
*  $FV Valor retornado:
*     PCA_tpCondRetOK
*
***********************************************************************/

   PCA_tpCondRet PCA_Destruir( PCA_tppCapturadas pCapturadas ) ;

/***********************************************************************
*
*  $FC Função: PCA Incluir Peça
*
*  $ED Descrição da função:
*     Inclui uma peça na lista de peças capturadas
*
*  $EP Parâmetros:
*     $P pCapturadas - Lista de peças a ser operado
*     $P peca        - Peça a ser incluída
*
*  Assertivas de entrada:
*     - pCapturadas deve ser uma instância válida de lista de peças capturadas.
*     - peca deve ser uma instância válida de peça.
*
*  Assertivas de saída:
*     - A peça passada no parâmetro peca será incluída na lista passada.
*
*  $FV Valor retornado
*     PCA_CondRetOK
*
***********************************************************************/

   PCA_tpCondRet PCA_InserirPeca ( PCA_tppCapturadas pCapturadas , PEC_tppPeca peca ) ;

 /***********************************************************************
*
*  $FC Função: PCA Contar Peças
*
*  $ED Descrição da função:
*     Conta as peças da lista de peças capturadas.
*
*  $EP Parâmetros:
*     $P pCapturadas - Lista de peças a ser operado.
*     $P qtd_pecas   - Ponteiro para a quantidade de peças a ser contada
*
*  Assertivas de entrada:
*     - pCapturadas deve ser uma instância válida de lista de peças capturadas.
*     - qtd_pecas deve ser um ponteiro válido
*
*  Assertivas de saída:
*     - qtd_pecas tem o tamnaho da lista.
*
*  $FV Valor retornado:
*     PCA_CondRetOK
*
***********************************************************************/

   PCA_tpCondRet PCA_ContaPecas ( PCA_tppCapturadas pCapturadas , int * qtd_pecas , int pCor ) ;

/********** Fim do módulo de definição: Módulo tabuleiro **********/


#else
#endif
