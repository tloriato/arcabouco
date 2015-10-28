#if ! defined( DADO_PONTOS_ )
#define DADO_PONTOS_
/**********************************************************************
*
*  $MCD Módulo de definição: Módulo dado pontos
*
*  Arquivo gerado:              dado_pontos.h
*  Letras identificadoras:      DPO
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data       Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Encapsula uma estrutura DadoPontos, armazena qual jogador pode
*     dobrar o valor da partida e informa o valor atual da partida.
*
***********************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: DPO Condições de retorno
*
*
***********************************************************************/

   typedef enum {

      DPO_CondRetOK = 0 ,
          /* Rodou sem erros */

      DPO_CondRetMaxPontos = 1 ,
          /* Valor da partida já atingiu o máximo */

      DPO_JogadorNaoPodeDobrar = 2
         /* Não é permitido que o jogador passado
            por parâmetro dobre a partida */

   } DPO_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: DPO Jogadores
*
*
***********************************************************************/

   typedef enum {

      DPO_Jogador1 = 0 ,
         /* Jogador 1 */

      DPO_Jogador2 = 1
         /* Jogador 2 */

   } DPO_tpJogador ;


/*****  Funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: DPO Dobrar pontos
*
*  $ED Descrição da função
*     Dobra o valor da partida
*
*  $EP Parâmetros
*     $P jogador - Jogador que irá dobrar o valor da partida
*
*  $FV Valor retornado
*     DPO_CondRetOK
*     DPO_CondRetMaxPontos
*
*  Assertivas de Entrada:
*    - Jogador exista (DPO_Jogador1 ou DPO_Jogador2).
*
*  Assertivas de Saída:
*    - Valor da partida tenha sido atualizado no estrutura
*      encapsulada no módulo.
*
***********************************************************************/

   DPO_tpCondRet DPO_DobrarPontos( DPO_tpJogador jogador ) ;

/***********************************************************************
*
*  $FC Função: DPO Pode dobrar
*
*  $ED Descrição da função
*     Verifica se o jogador pode dobrar a pontuação da partida
*
*  $EP Parâmetros
*     $P jogador - Jogador
*     $P res     - Resposta: 1 se o jogador pode dobrar. 0 caso contrário
*                  Esse parâmetro é passado por referência
*
*  $FV Valor retornado
*     DPO_CondRetOK
*
*  Assertivas de Entrada:
*    - Jogador exista (DPO_Jogador1 ou DPO_Jogador2).
*    - res seja um ponteiro válido.
*
*  Assertivas de Saída:
*    - *res = 1 se o jogador pode dobrar e 0 caso contrário.
*
***********************************************************************/

   DPO_tpCondRet DPO_PodeDobrar( DPO_tpJogador jogador , int * res ) ;

/***********************************************************************
*
*  $FC Função: DPO Obter pontos
*
*  $ED Descrição da função
*     Obtém o valor atual da partida.
*
*  $EP Parâmetros
*     $P pontos - Retorno do valor da partida.
*                 Esse parâmetro é passado por referência.
*
*  $FV Valor retornado
*     DPO_CondRetOK
*
*  Assertivas de Entrada:
*      - pontos seja um ponteiro válido.
*
*  Assertivas de Saída:
*     - *pontos seja igual a uma potência de 2 entre 1 e 64, inclusive.
*
***********************************************************************/

   DPO_tpCondRet DPO_ObterPontos( int * pontos ) ;


/***********************************************************************
*
*  $FC Função: DPO Definir Pontos e Vez
*
*  $ED Descrição da função
*     Define o valor da partida e o próximo jogador a dobrar.
*     Caso o valor da partida seja 1, ambos os jogadores podem dobrar.
*     Caso o valor da partida seja 64, nenhum jogador pode dobrar.
*
*  $EP Parâmetros
*     $P pontos  - Novo valor da partida.
*     $P jogador - Jogador que pode dobrar o valor da partida.
*
*  $FV Valor retornado
*     DPO_CondRetOK
*
*  Assertivas de Entrada:
*      - Jogador exista (DPO_Jogador1 ou DPO_Jogador2).
*      - pontos deve ser uma potência de 2 entre 1 e 64, inclusive.
*
*  Assertivas de Saída:
*      - valor da partida passa a ser o definido pelo parâmetro pontos.
*      - vez de dobrar passa a ser do jogador passado por parâmetro.
*
***********************************************************************/

   DPO_tpCondRet DPO_DefinirPontosVez( int pontos , DPO_tpJogador jogador ) ;



/********** Fim do módulo de definição: Módulo dado pontos **********/

#else
#endif
