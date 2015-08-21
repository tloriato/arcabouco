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
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: MAT Handle da matriz visto pelo usuário
*
*
***********************************************************************/
typedef void * MAT_tpHandle;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetNaoCriouHandle = 1 ,
               /* Não criou o handle */

         MAT_CondRetErroEstrutura = 2 ,
               /* Estrutura da mariz está errada */

         MAT_CondRetMatrizNaoExiste = 3 ,
               /* mariz não existe */

         MAT_CondRetMatrizVazia = 4 ,
               /* mariz está vazia */

         MAT_CondRetNaoPossuiCelula = 5 ,
               /* Nó corrente não possui a célula desejada */

         MAT_CondRetFaltouMemoria = 6
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar mariz
*
*  $ED Descrição da função
*     Cria uma nova mariz vazia.
*
*  $EP Parâmetros
*     $P Handle - ponteiro para retorno do handle da matriz
*                 Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpHandle * Handle ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir mariz
*
*  $EP Parâmetros
*     $P Handle - handle da matriz a ser destruída
*
*  $ED Descrição da função
*     Destrói o corpo e o handle da mariz, anulando a mariz passada.
*     Faz nada caso a mariz passada não exista.
*
***********************************************************************/

   void MAT_DestruirMatriz( MAT_tpHandle Handle ) ;


/***********************************************************************
*
*  $FC Função: MAT Adicionar filho à esquerda
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoEhFolha     - caso não seja folha para a esquerda
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirEsquerda( MAT_tpHandle Handle, char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: MAT Adicionar filho à direita
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoEhFolha     - caso não seja folha para a direita
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirDireita( MAT_tpHandle Handle, char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó pai
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEhRaiz
*
***********************************************************************/

   MAT_tpCondRet MAT_IrPai( MAT_tpHandle Handle, void ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó à esquerda
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNoEsquerda( MAT_tpHandle Handle, void ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó à direita
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNoDireita( MAT_tpHandle Handle, void ) ;


/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpHandle Handle, char * ValorParm ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo mariz **********/

#else
#endif
