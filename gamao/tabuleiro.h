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
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data       Observações
*       1.00  gbo, gapm, pa, tdn  19/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Módulo para movimentação de peças em um tabuleiro de jogo
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
*  Definição: MAT Quantidade de posições no tabuleiro
*
***********************************************************************/

#define TAB_QUANTIDADE_POS 24


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
*  Assertivas de entrada:
*     - O ponteiro passado como parametro deve ser válido.
*
*  Assertivas de saída:
*     - *pTabuleiro deve conter a instância de tabuleiro criada.
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
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*
*  Assertivas de saída:
*     - A memória ocupada pelo tabuleiro passado por parâmetro deve
*       ser desalocada.
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
*     $P peca      - Peça a ser incluída
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - posicao deve ser um inteiro entre 0 e 23, inclusive.
*     - peca deve ser uma instância válida de peça.
*
*  Assertivas de saída:
*     - A peça passada no parâmetro peca será incluída na posição indicada
*       do tabuleiro passado.
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
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - de deve ser um inteiro entre 0 e 23, inclusive.
*     - para deve ser um inteiro entre 0 e 23, inclusive.
*     - a posição 'de' deve conter ao menos uma peça.
*
*  Assertivas de saída:
*     - Uma das peças do tabuleiro contidas na posição 'de' será movida
*       para a posição 'para'. Assume-se que todas as peças em uma mesma
*       posição do tabuleiro são equivalentes e qualquer uma pode ser
*       movida com o mesmo efeito.
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
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - posicao deve ser um inteiro entre 0 e 23, inclusive.
*     - peca deve ser um ponteiro válido.
*     - A posição 'posicao' deve conter ao menos uma peça.
*
*  Assertivas de saída:
*     - Uma das peças do tabuleiro contidas na posição 'posicao' será
*       removida. Assume-se que todas as peças em uma mesma posição do
*       tabuleiro são equivalentes e qualquer uma pode ser removida
*       com o mesmo efeito.
*     - A peça removida será retornada através do parâmetro peca.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosInvalida
*     TAB_CondRetPosVazia
*
***********************************************************************/

   TAB_tpCondRet TAB_RemoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca * peca ) ;

/***********************************************************************
*
*  $FC Função: TAB Contar Peças
*
*  $ED Descrição da função
*     Conta quantas peças há na posição passada por parâmetro e
*     retorna a cor das mesmas.
*     Assume-se que todas as peças em uma mesma posição do
*     tabuleiro são equivalentes e de mesma cor.
*
*  $EP Parâmetros
*     $P tabuleiro  - Tabuleiro a ser operado
*     $P posicao    - Posição da peça
*     $P pQuanidade - Parâmetro para retorno da quantidade de peças
*                     Esse parâmetro é passado por referência
*     $P pCor       - Parâmetro para retorno da cor das peças
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - posicao deve ser um inteiro entre 0 e 23, inclusive.
*     - pQuantidade deve ser um ponteiro válido.
*     - pCor deve ser um ponteiro válido.
*
*  Assertivas de saída:
*     - A quantidade de peças presentes na posição indicada
*       será retornada através do parâmetro pQuantidade e a cor
*       dessas peças será retornada através do parâmetro pCor.
*     - As variáveis apontadas por pQuantidade e pCor não serão
*       alteradas em caso de falha.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosInvalida
*
***********************************************************************/

   TAB_tpCondRet TAB_ContarPecas( TAB_tppTabuleiro tabuleiro , unsigned int posicao , unsigned int * pQuantidade , int * pCor ) ;


/********** Fim do módulo de definição: Módulo tabuleiro **********/

#else
#endif
