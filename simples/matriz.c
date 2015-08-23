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

         tpNoMatriz * pCelCorr ;
               /* Ponteiro para o nó corrente da mariz */

         unsigned int LinhaCorr ;
               /* Índice da linha de pCelCorr */

         unsigned int ColCorr ;
               /* Índice da coluna de pCelCorr */

   } tpMatriz ;



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar mariz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpMatriz * pMatriz )
   {

      *pMatriz = malloc( sizeof( tpMatriz )) ;
      if ( *pMatriz == NULL )
      {
         return MAT_CondRetFaltouMemoria ;
      } /* if */

      memset( *pMatriz, 0, sizeof( tpMatriz ) ) ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Criar mariz */

/***************************************************************************
*
*  Função: MAT Destruir mariz
*  ****/

   void MAT_DestruirMatriz( MAT_tpMatriz Matriz )
   {

      tpMatriz * pMatriz = ( tpMatriz * ) Matriz;
      tpCelulaMatriz * pCel ;

      if ( pMatriz != NULL )
      {
         if ( pMatriz->pCelRaiz != NULL )
         {
            pCel = pMatriz->pCelRaiz;
            while ( pCel != NULL )
            {
               // 
            DestroiMatriz( pMatriz->pNoRaiz ) ;
         } /* if */
         free( pMatriz ) ;
         pMatriz = NULL ;
      } /* if */

   } /* Fim função: MAT Destruir mariz */

/***************************************************************************
*
*  Função: MAT Adicionar filho à esquerda
*  ****/

   MAT_tpCondRet MAT_InserirEsquerda( MAT_tpMatriz Matriz, char ValorParm )
   {

      MAT_tpCondRet CondRet ;

      tpNoMatriz * pCorr ;
      tpNoMatriz * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != MAT_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pMatriz->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pMatriz->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: MAT Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: MAT Adicionar filho à direita
*  ****/

   MAT_tpCondRet MAT_InserirDireita( MAT_tpMatriz Matriz, char ValorParm )
   {

      MAT_tpCondRet CondRet ;

      tpNoMatriz * pCorr ;
      tpNoMatriz * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != MAT_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pMatriz->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pMatriz->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: MAT Adicionar filho à direita */

/***************************************************************************
*
*  Função: MAT Ir para nó pai
*  ****/

   MAT_tpCondRet MAT_IrPai( MAT_tpMatriz Matriz )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoPai != NULL )
      {
         pMatriz->pNoCorr = pMatriz->pNoCorr->pNoPai ;
         return MAT_CondRetOK ;
      } else {
         return MAT_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: MAT Ir para nó pai */

/***************************************************************************
*
*  Função: MAT Ir para nó à esquerda
*  ****/

   MAT_tpCondRet MAT_IrNoEsquerda( MAT_tpMatriz Matriz )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoEsq == NULL )
      {
         return MAT_CondRetNaoPossuiFilho ;
      } /* if */

      pMatriz->pNoCorr = pMatriz->pNoCorr->pNoEsq ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ir para nó à esquerda */

/***************************************************************************
*
*  Função: MAT Ir para nó à direita
*  ****/

   MAT_tpCondRet MAT_IrNoDireita( MAT_tpMatriz Matriz )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoDir == NULL )
      {
         return MAT_CondRetNaoPossuiFilho ;
      } /* if */

      pMatriz->pNoCorr = pMatriz->pNoCorr->pNoDir ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ir para nó à direita */

/***************************************************************************
*
*  Função: MAT Obter valor corrente
*  ****/

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpMatriz Matriz, char * ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */
      * ValorParm = pMatriz->pNoCorr->Valor ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MAT Criar nó da mariz
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros da célula criada estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoMatriz * CriarNo( MAT_tpMatriz Matriz, char ValorParm )
   {

      tpNoMatriz * pNo ;

      pNo = ( tpNoMatriz * ) malloc( sizeof( tpNoMatriz )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: MAT Criar nó da mariz */


/***********************************************************************
*
*  $FC Função: MAT Criar nó raiz da mariz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoCriouRaiz
*
***********************************************************************/

   MAT_tpCondRet CriarNoRaiz( MAT_tpMatriz Matriz, char ValorParm )
   {

      MAT_tpCondRet CondRet ;
      tpNoMatriz * pNo ;

      if ( pMatriz == NULL )
      {
         CondRet = MAT_CriarMatriz( ) ;

         if ( CondRet != MAT_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pMatriz->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */
         pMatriz->pNoRaiz = pNo ;
         pMatriz->pNoCorr = pNo ;

         return MAT_CondRetOK ;
      } /* if */

      return MAT_CondRetNaoCriouRaiz ;

   } /* Fim função: MAT Criar nó raiz da mariz */


/***********************************************************************
*
*  $FC Função: MAT Destruir a estrutura da mariz
*
*  $EAE Assertivas de entradas esperadas
*     pNoMatriz != NULL
*
***********************************************************************/

   void DestroiMatriz( MAT_tpMatriz Matriz, tpNoMatriz * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiMatriz( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiMatriz( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: MAT Destruir a estrutura da mariz */

/********** Fim do módulo de implementação: Módulo mariz **********/

