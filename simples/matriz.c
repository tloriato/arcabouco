/***************************************************************************
*  $MCI Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              matriz.c
*  Letras identificadoras:      MAT
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Autores: tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   tdn   21/08/2015 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   "matriz.h"

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da célula da mariz
*
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct tgCelulaMatriz {

         struct tgCelulaMatriz * pCelNorte ;
               /* Ponteiro para a célula acima
               *
               *$EED Assertivas estruturais
               *   É NULL só se a célula estiver na primeira linha
               *   Se não for NULL, pCelSul de pCelNorte aponta para esta célula */

         struct tgCelulaMatriz * pCelNordeste ;
               /* Ponteiro para a célula acima à direita
                *
                *$EED Assertivas estruturais
                *   É NULL só se a célula estiver na primeira linha ou na última coluna
                *   Se não for NULL, pCelSudoeste de pCelNordeste aponta para esta célula */

         struct tgCelulaMatriz * pCelNoroeste ;
               /* Ponteiro para a célula acima à esquerda
                *
                *$EED Assertivas estruturais
                *   É NULL só se a célula estiver na primeira linha ou na primeira coluna
                *   Se não for NULL, pCelSudeste de pCelNoroeste aponta para esta célula */

         struct tgCelulaMatriz * pCelSul ;
               /* Ponteiro para a célula abaixo
                *
                *$EED Assertivas estruturais
                *   É NULL só se a célula estiver na última linha
                *   Se não for NULL, pCelNorte de pCelSul aponta para esta célula */

         struct tgCelulaMatriz * pCelSudeste ;
               /* Ponteiro para a célula abaixo à direita
                *
                *$EED Assertivas estruturais
                *   É NULL só se a célula estiver na última linha ou na última coluna
                *   Se não for NULL, pCelNoroeste de pCelSudeste aponta para esta célula */

         struct tgCelulaMatriz * pCelSudoeste ;
               /* Ponteiro para a célula abaixo à esquerda
                *
                *$EED Assertivas estruturais
                *   É NULL só se a célula estiver na última linha ou na primeira coluna
                *   Se não for NULL, pCelNordeste de pCelSudoeste aponta para esta célula */

         LIS_tppLista Lista ;
               /* Estrutura de lista contida na célula */

   } tpCelulaMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma mariz
*
*
*  $ED Descrição do tipo
*     A cabeça da mariz é o ponto de acesso para uma determinada mariz.
*     Por intermédio da referência para célula corrente e dos ponteiros
*     para as células vizinhas pode-se navegar a mariz sem necessitar
*     de uma pilha.
*     Pode-se, inclusive, operar com a mariz em forma de co-rotina.
*     Os índices LinhaCorr e ColCorr permitem calcular a posição
*     relativa entre a célula corrente e a desejada pelo usuário.
*     LinhasTot e ColsTot permitem determinar se a célula desejada
*     existe sem a necessidade de navegar na matriz.
*
***********************************************************************/

   typedef struct tgMatriz {

         tpCelulaMatriz * pCelRaiz ;
               /* Ponteiro para a raiz da mariz: Célula superior esquerda,
                * Coluna 0, Linha 0 */

         tpCelualaMatriz * pCelCorr ;
               /* Ponteiro para o nó corrente da mariz */

         unsigned int LinhaCorr ;
               /* Índice da linha de pCelCorr */

         unsigned int ColCorr ;
               /* Índice da coluna de pCelCorr */

         unsigned int QuantidadeLinhas ;
               /* Número de linhas da matriz */

         unsigned int QuantidadeColunas ;
               /* Número de colunas da matriz */

   } tpMatriz ;


/***** Protótipos das funções encapuladas no módulo *****/

   static tpCelulaMatriz * ObterCelulaNasCoordenadas( MAT_tpMatriz Matriz , unsigned int Coluna , unsigned Linha );
   static MAT_tpCondRet ValidarCelula( MAT_tpMatriz Matriz , unsigned int Coluna , unsigned Linha ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar mariz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpMatriz * pMatriz )
   {

      *pMatriz = calloc( sizeof( tpMatriz ) , 1 ) ;
      if ( *pMatriz == NULL )
      {
         return MAT_CondRetFaltouMemoria ;
      } /* if */

      return MAT_CondRetOK ;

   } /* Fim função: MAT Criar mariz */

/***************************************************************************
*
*  Função: MAT Destruir mariz
*  ****/

   void MAT_DestruirMatriz( MAT_tpMatriz Matriz )
   {

      tpMatriz * pMatriz = ( tpMatriz * ) Matriz ;
      tpCelulaMatriz * pCel ;

      if ( pMatriz != NULL )
      {
         if ( pMatriz->pCelRaiz != NULL )
         {
            pCel = pMatriz->pCelRaiz;
            while ( pCel != NULL )
            {
               pCel = pCel->pCelSul;
               MAT_ExcluirLinha( Matriz , 0 ) ;
            } /* while */
         } /* if */

         free( pMatriz ) ;
         pMatriz = NULL ;
      } /* if */

   } /* Fim função: MAT Destruir mariz */

/***************************************************************************
*
*  Função: MAT Inserir coluna
*  ****/

   MAT_tpCondRet MAT_InserirColuna( MAT_tpMatriz Matriz )
   {
   } /* Fim função: MAT Inserir coluna */

/***************************************************************************
*
*  Função: MAT Inserir linha
*  ****/

   MAT_tpCondRet MAT_InserirLinha( MAT_tpMatriz Matriz )
   {
   } /* Fim função: MAT Inserir linha */

/***************************************************************************
*
*  Função: MAT Ler célula
*  ****/

   MAT_tpCondRet MAT_LerCelula( MAT_tpMatriz Matriz , unsigned int Coluna , unsigned int Linha , LIS_tppLista * Lista )
   {

      if ( Lista == NULL )
      {
         return MAT_CondRetPonteiroRetornoNulo ;
      } /* if */

      tpCelulaMatriz * pCel;
      MAT_tpCondRet ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret;
      } /* if */

      *Lista = pCel->Lista ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ler célula */

/***************************************************************************
*
*  Função: MAT Escrever célula
*  ****/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tpMatriz Matriz , unsigned int Coluna , unsigned int Linha , LIS_tppLista Lista )
   {
   } /* Fim função: MAT Escrever célula */

/***************************************************************************
*
*  Função: MAT Excluir coluna
*  ****/

   MAT_tpCondRet MAT_ExcluirColuna( MAT_tpMatriz Matriz , unsigned int Coluna )
   {
   } /* Fim função: MAT Excluir coluna */

/***************************************************************************
*
*  Função: MAT Excluir linha
*  ****/

   MAT_tpCondRet MAT_ExcluirLinha( MAT_tpMatriz Matriz , unsigned int Linha )
   {
   } /* Fim função: MAT Excluir linha */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: MAT Obter célula nas coordenadas
*
*  $ED Descrição da função
*     Essa função retorna um ponteiro para a célula da matriz nas coordenadas
*     (Coluna, Linha). Essa função tem o efeito colateral de atualizar o
*     ponteiro para a célula atual na estrutura da matriz.
*
*  $EP Parâmetros
*     $P Matriz - matriz que contém a célula desejada
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Celula - parâmetro para retorno do ponteiro para a célula desejada
*                 este parâmetro é passado por referência
*
*  $EAE Assertivas de entradas esperadas
*     Matriz != NULL
*
*  $FV Valor retornado
*     MAT_CondRetOK    - obteve a célula sem problemas
*     MAT_CondRetMatrizNaoExiste - o parâmetro Matriz é NULO
*     MAT_CondRetNaoPossuiCelula - coordenadas da célula estão fora da matriz
*     MAT_CondRetErroEstrutura - estrutura da matriz está corrompida
*
***********************************************************************/

   static MAT_tpCondRet ObterCelulaNasCoordenadas( MAT_tpMatriz Matriz , unsigned int Coluna , unsigned Linha , tpCelulaMatriz ** Celula )
   {

      if ( Matriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      tpMatriz * pMatriz = ( tpMatriz * ) Matriz ;

      if ( ( Coluna >= pMatriz->QuantidadeColunas )
        || ( Linha >= pMatriz->QuantidadeLinhas ))
      {
         return MAT_CondRetNaoPossuiCelula ;
      } /* if */

   }


/***********************************************************************
*
*  $FC Função: MAT Validar célula
*
*  $ED Descrição da função
*     Essa função retorna um ponteiro para a célula da matriz nas coordenadas
*     (Coluna, Linha). Essa função tem o efeito colateral de atualizar o
*     ponteiro para a célula atual na estrutura da matriz.
*
*  $EP Parâmetros
*     $P Matriz - matriz que contém a célula desejada
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0

*  $EAE Assertivas de entradas esperadas
*     Matriz != NULL
*
***********************************************************************/

   static MAT_tpCondRet ValidarCelula( MAT_tpMatriz Matriz , unsigned int Coluna , unsigned Linha )
   {

   }

/********** Fim do módulo de implementação: Módulo mariz **********/

