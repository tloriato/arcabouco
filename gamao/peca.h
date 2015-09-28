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
*     Versão  Autor             Data       Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Esse módulo é uma peça que pode ser usada em um tabuleiro.
*     Cada peça tem apenas uma cor imutável e definida na sua criação.
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

      PEC_CondRetFaltouMemoria = 1
         /* Faltou memória ao alocar dados */

   } PEC_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: Tipo abstrato de dados Peça
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
*   Assertiva de Entrada:
*      - O ponteiro passado como parâmetro não aponte para NULL
*
*   Assertiva de saída:
*      - pPeca ocupe o espaço do tipo definido para peça no .c e
*        tenha a cor passada como parâmetro.
*
***********************************************************************/

   PEC_tpCondRet PEC_Criar( PEC_tppPeca * pPeca , int cor ) ;

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
*   Assertiva de Entrada:
*      - Não há necessidade de assertivas de entrada.
*
*   Assertiva de saída:
*      - O espaço ocupado pelo parâmetro passado esteja livre.
*
*
***********************************************************************/

   PEC_tpCondRet PEC_Destruir( PEC_tppPeca pPeca ) ;

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
*   Assertiva de Entrada:
*      - O ponteiro passado não aponte para NULL
*
*   Assertiva de saída:
*      - pCor guarde a cor guardada por pPeca.
*
*
***********************************************************************/

   PEC_tpCondRet PEC_ObterCor( PEC_tppPeca pPeca , int * pCor ) ;


/********** Fim do módulo de definição: Módulo Peça **********/

#else
#endif
