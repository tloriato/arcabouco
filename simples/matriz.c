/***************************************************************************
*  $MCI Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              matriz.c
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
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define MATRIZ_OWN
#include "matriz.h"
#undef MATRIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da célula da mariz
*
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct tgNoMatriz {

         struct tgNoMatriz * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai da célula
               *   corrente apontam para o nó corrente */

         struct tgNoMatriz * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq da célula X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoMatriz * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir da célula X != NULL então pNoPai de pNoDir aponta para o nó X */

         char Valor ;
               /* Valor da célula */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma mariz
*
*
*  $ED Descrição do tipo
*     A cabeça da mariz é o ponto de acesso para uma determinada mariz.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a mariz sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a mariz em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgMatriz {

         tpNoMatriz * pNoRaiz ;
               /* Ponteiro para a raiz da mariz */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da mariz */

   } tpMatriz ;

/*****  Dados encapsulados no módulo  *****/

      static tpMatriz * pMatriz = NULL ;
            /* Ponteiro para a cabea da mariz */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoMatriz * CriarNo( char ValorParm ) ;

   static MAT_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiMatriz( tpNoMatriz * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar mariz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpHandle * Handle )
   {

      if ( pMatriz != NULL )
      {
         MAT_DestruirMatriz( ) ;
      } /* if */

      pMatriz = ( tpMatriz * ) malloc( sizeof( tpMatriz )) ;
      if ( pMatriz == NULL )
      {
         return MAT_CondRetFaltouMemoria ;
      } /* if */

      pMatriz->pNoRaiz = NULL ;
      pMatriz->pNoCorr = NULL ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Criar mariz */

/***************************************************************************
*
*  Função: MAT Destruir mariz
*  ****/

   void MAT_DestruirMatriz( MAT_tpHandle Handle )
   {

      if ( pMatriz != NULL )
      {
         if ( pMatriz->pNoRaiz != NULL )
         {
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

   MAT_tpCondRet MAT_InserirEsquerda( MAT_tpHandle Handle, char ValorParm )
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

   MAT_tpCondRet MAT_InserirDireita( MAT_tpHandle Handle, char ValorParm )
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

   MAT_tpCondRet MAT_IrPai( MAT_tpHandle Handle )
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

   MAT_tpCondRet MAT_IrNoEsquerda( MAT_tpHandle Handle )
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

   MAT_tpCondRet MAT_IrNoDireita( MAT_tpHandle Handle )
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

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpHandle Handle, char * ValorParm )
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

   tpNoMatriz * CriarNo( MAT_tpHandle Handle, char ValorParm )
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

   MAT_tpCondRet CriarNoRaiz( MAT_tpHandle Handle, char ValorParm )
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

   void DestroiMatriz( MAT_tpHandle Handle, tpNoMatriz * pNo )
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

