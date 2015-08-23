#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              matriz.h
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Autores: tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   tdn   21/08/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     manipular matrizes.
*
*     TODO: Trocar descrição !
*     A mariz possui uma cabeça que contém uma referência para a raíz da
*     mariz e outra para um nó corrente da mariz.
*     A cada momento o módulo admite no máximo uma única mariz.
*     Ao iniciar a execução do programa não existe mariz.
*     A mariz poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a mariz estiver vazia.
*
***************************************************************************/

/***********************************************************************
*
*  Módulo de lista duplamente encadeada
*
*
***********************************************************************/

#include "lista.h"


/***********************************************************************
*
*  $TC Tipo de dados: MAT Matriz da matriz visto pelo usuário
*
*
***********************************************************************/

typedef void * MAT_tpMatriz;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetNaoCriouMatriz = 1 ,
               /* Não criou o handle */

         MAT_CondRetErroEstrutura = 2 ,
               /* Estrutura da mariz está errada */

         MAT_CondRetMatrizNaoExiste = 3 ,
               /* Mariz não existe */

         MAT_CondRetMatrizVazia = 4 ,
               /* Mariz está vazia */

         MAT_CondRetNaoPossuiCelula = 5 ,
               /* Matriz não possui a célula desejada */

         MAT_CondRetNaoPossuiColuna = 6 ,
               /* Matriz não possui a coluna desejada */

         MAT_CondRetNaoPossuiLinha = 7 ,
               /* Matriz não possui a linha desejada */

         MAT_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar mariz
*
*  $ED Descrição da função
*     Cria uma nova mariz vazia
*     Se não for possível criar a matriz, Matriz será NULL
*
*  $EP Parâmetros
*     $P Matriz - parâmetro para retorno do matriz
*                 Este parâmetro é passado por referência
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetNaoCriouMatriz
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir mariz
*
*  $ED Descrição da função
*     Destrói o corpo e o handle da mariz, anulando a mariz passada
*     Essa função se encarrega de destruir as listas contidas na matriz
*     Faz nada caso a mariz passada não exista
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser destruída
*
***********************************************************************/

   void MAT_DestruirMatriz( MAT_tpMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir coluna
*
*  $ED Descrição da função
*     Adiciona uma coluna vazia à direita da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser estendida
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirColuna( MAT_tpMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir linha
*
*  $ED Descrição da função
*     Adiciona uma linha vazia abaixo da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser estendida
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirLinha( MAT_tpMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ler célula
*
*  $ED Descrição da função
*     Obtém a lista contida em uma célula da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser lida
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Lista  - retorno da lista armazenada na célula
*                 Este parâmetro é passado por referência
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiCelula
*
***********************************************************************/

   MAT_tpCondRet MAT_LerCelula( MAT_tpMatriz Matriz, unsigned int Coluna, unsigned int Linha, LIS_tppLista * Lista ) ;


/***********************************************************************
*
*  $FC Função: MAT Escrever célula
*
*  $ED Descrição da função
*     Adiciona uma lista a uma célula da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Lista  - lista a armazenar na célula
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiCelula
*
***********************************************************************/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tpMatriz Matriz, unsigned int Coluna, unsigned int Linha, LIS_tppLista Lista ) ;


/***********************************************************************
*
*  $FC Função: MAT Excluir coluna
*
*  $ED Descrição da função
*     Exclui a coluna especificada da matriz
*     Essa função se encarrega de destruir as listas contidas na coluna excluida
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Coluna - coluna que se deseja excluir
*                 a coluna mais à esquerda tem índice 0
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiColuna
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirColuna( MAT_tpMatriz Matriz, unsigned int Coluna ) ;


/***********************************************************************
*
*  $FC Função: MAT Excluir linha
*
*  $ED Descrição da função
*     Exclui a linha especificada da matriz
*     Essa função se encarrega de destruir as listas contidas na linha excluida
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Linha  - linha que se deseja excluir
*                 a linha mais à esquerda tem índice 0
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiLinha
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirLinha( MAT_tpMatriz Matriz, unsigned int Linha ) ;


/********** Fim do módulo de definição: Módulo mariz **********/

#endif
