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
*  $TC Tipo de dados: MAT Direções das células adjacetes
*
*
***********************************************************************/

   typedef enum {
      MAT_DirNorte = 0 ,
            /* Direção norte */

      MAT_DirSul = 1 ,
            /* Direção sul */

      MAT_DirLeste = 2 ,
            /* Direção leste */

      MAT_DirOeste = 3 ,
            /* Direção oeste */

      MAT_DirNordeste = 4 ,
            /* Direção nordeste */

      MAT_DirNoroeste = 5 ,
            /* Direção noroeste */

      MAT_DirSudeste = 6 ,
            /* Direção sudeste */

      MAT_DirSudoeste = 7 ,
            /* Direção sudoeste */

   } MAT_tgDir ;

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

         struct tgCelulaMatriz * pCelDir[ 8 ] ;
               /* Vetor com ponteiros para as 8 células adjacentes
                *
                *$EED Assertivas estruturais
                *   Cada ponteiro só é NULL se não existir uma célula
                *   na direção correspondente
                *   Se não for NULL, a célula apontada tem um ponteiro na
                *   direção oposta apontando para esta célula
                *   Norte <-> Sul
                *   Leste <-> Oeste
                *   Nordeste <-> Sudoeste
                *   Noroeste <-> Sudeste
                */

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

         int LinhaCorr ;
               /* Índice da linha de pCelCorr */

         int ColCorr ;
               /* Índice da coluna de pCelCorr */

         int QuantidadeLinhas ;
               /* Número de linhas da matriz */

         int QuantidadeColunas ;
               /* Número de colunas da matriz */

   } tpMatriz ;


/***** Protótipos das funções encapuladas no módulo *****/

   static tpCelulaMatriz * ObterCelulaNasCoordenadas( MAT_tpMatriz Matriz , int Coluna , Linha ) ;

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
            pCel = pMatriz->pCelRaiz ;
            while ( pCel != NULL )
            {
               pCel = pCel->pCelSul ;
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
      int linha ;
      tpCelulaMatriz * cel ,
                     * ultimaCriada ,
                     * novaCelula ;
      tpMatriz * pMatriz = ( tpMatriz * ) Matriz ;
      MAT_tpCondRet ret ;

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      /* Se a matriz estiver vazia, cria uma única célula */
      if ( ( pMatriz->QuantidadeColunas == 0 ) && ( pMatriz->QuantidadeLinhas == 0 ) )
      {
         pMatriz->QuantidadeLinhas = 1 ;
         pMatriz->QuantidadeColunas = 1 ;
         pMatriz->pCelRaiz = ( tpCelulaMatriz * ) calloc( sizeof( tpCelulaMatriz ) , 1 ) ;
         pMatriz->pCelCorr = pMatriz->pCelRaiz ;

         if ( pMatriz->pCelRaiz == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */

         return MAT_CondRetOK ;
      } /* if */

      ret = ObterCelulaNasCoordenadas( Matriz , pMatriz->QuantidadeColunas - 1 , 0, &cel );

      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      ultimaCriada = NULL;

      for ( linha = 0 ; linha < pMatriz->QuantidadeLinhas ; linha ++ )
      {
         if ( cel == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         novaCelula = ( tpCelulaMatriz * ) calloc( sizeof( tpCelulaMatriz ) , 1 ) ;

         if ( novaCelula == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */

         novaCelula->pCelDir[ MAT_DirOeste ] = cel ;
         novaCelula->pCelDir[ MAT_DirNorte ] = ultimaCriada ;
         novaCelula->pCelDir[ MAT_DirNoroeste ] = cel->pCelDir[ MAT_DirNorte ] ;
         novaCelula->pCelDir[ MAT_DirSudoeste ] = cel->pCelDir[ MAT_DirSul ] ;

         ultimaCriada->pCelDir[ MAT_DirSul ] = novaCelula ;
         ultimaCriada = novaCelula ;

         cel->pCelDir[ MAT_DirLeste ] = novaCelula ;
         cel = cel->pCelDir[ MAT_DirSul ] ;
      } /* for */

      pMatriz->QuantidadeColunas ++ ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Inserir coluna */

/***************************************************************************
*
*  Função: MAT Inserir linha
*  ****/

   MAT_tpCondRet MAT_InserirLinha( MAT_tpMatriz Matriz )
   {
      int coluna ;
      tpCelulaMatriz * cel ,
                     * ultimaCriada ,
                     * novaCelula ;
      tpMatriz * pMatriz = ( tpMatriz * ) Matriz ;
      MAT_tpCondRet ret ;

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      /* Se a matriz estiver vazia, cria uma única célula */
      if ( ( pMatriz->QuantidadeColunas == 0 ) && ( pMatriz->QuantidadeLinhas == 0 ) )
      {
         pMatriz->QuantidadeLinhas = 1 ;
         pMatriz->QuantidadeColunas = 1 ;
         pMatriz->pCelRaiz = ( tpCelulaMatriz * ) calloc( sizeof( tpCelulaMatriz ) , 1 ) ;
         pMatriz->pCelCorr = pMatriz->pCelRaiz ;

         if ( pMatriz->pCelRaiz == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */

         return MAT_CondRetOK ;
      } /* if */

      ret = ObterCelulaNasCoordenadas( Matriz , 0, pMatriz->QuantidadeLinhas - 1 , &cel );

      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      ultimaCriada = NULL;

      for ( coluna = 0 ; coluna < pMatriz->QuantidadeColunas ; coluna ++ )
      {
         if ( cel == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         novaCelula = ( tpCelulaMatriz * ) calloc( sizeof( tpCelulaMatriz ) , 1 ) ;

         if ( novaCelula == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */

         novaCelula->pCelDir[ MAT_DirNorte ] = cel ;
         novaCelula->pCelDir[ MAT_DirOeste ] = ultimaCriada ;
         novaCelula->pCelDir[ MAT_DirNoroeste ] = cel->pCelDir[ MAT_DirLeste ] ;
         novaCelula->pCelDir[ MAT_DirNordeste ] = cel->pCelDir[ MAT_DirOeste ] ;

         ultimaCriada->pCelDir[ MAT_DirLeste ] = novaCelula ;
         ultimaCriada = novaCelula ;

         cel->pCelDir[ MAT_DirSul ] = novaCelula ;
         cel = cel->pCelDir[ MAT_DirLeste ] ;
      } /* for */

      pMatriz->QuantidadeLinhas ++ ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Inserir linha */

/***************************************************************************
*
*  Função: MAT Ler célula
*  ****/

   MAT_tpCondRet MAT_LerCelula( MAT_tpMatriz Matriz , int Coluna , int Linha , LIS_tppLista * Lista )
   {

      if ( Lista == NULL )
      {
         return MAT_CondRetPonteiroRetornoNulo ;
      } /* if */

      tpCelulaMatriz * pCel ;
      MAT_tpCondRet ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      *Lista = pCel->Lista ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ler célula */

/***************************************************************************
*
*  Função: MAT Escrever célula
*  ****/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tpMatriz Matriz , int Coluna , int Linha , LIS_tppLista Lista )
   {

      tpCelulaMatriz * pCel ;
      MAT_tpCondRet ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      pCel->Lista = Lista ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Escrever célula */

/***************************************************************************
*
*  Função: MAT Excluir coluna
*  ****/

   MAT_tpCondRet MAT_ExcluirColuna( MAT_tpMatriz Matriz , int Coluna )
   {
   } /* Fim função: MAT Excluir coluna */

/***************************************************************************
*
*  Função: MAT Excluir linha
*  ****/

   MAT_tpCondRet MAT_ExcluirLinha( MAT_tpMatriz Matriz , int Linha )
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

   static MAT_tpCondRet ObterCelulaNasCoordenadas( MAT_tpMatriz Matriz , int Coluna , Linha , tpCelulaMatriz ** Celula )
   {

      int distDiagonal ,    /* Quantidade de passos na diagonal */
          distCol ,         /* Distância em colunas da célula atual para a desejada */
          distLin ,         /* Distância em linhas da célula atual para a desejada */
          distNaoDiagonal ; /* Quantidade de passos sem ser na diagonal */

      MAT_tgDir dirDiagonal , /* Em qual das diagonais andar */
                dirNaoDiagonal ; /* Direção na qual andar após ter andado na diagonal */

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

      if ( pMatriz->pCelCorr == NULL )
      {
         return MAT_CondRetErroEstrutura;
      } /* if */

      distCol = abs( pMatriz->ColCorr - Coluna ) ;
      distLin = abs( pMatriz->LinhaCorr - Linha ) ;

      /* Anda a maior distância possível na diagonal, sem ultrapassar a linha
       * nem a coluna desejadas */
      distDiagonal = distCol < distLin ? distCol : distLini ;

      /* Calcula a distância restante após andar na diagonal */
      distCol -= distDiagonal ;
      distLin -= distDiagonal ;

      if ( distCol != 0 )
      {
         /* Sobraram colunas para andar */
         distNaoDiagonal = distCol ;

         if ( pMatriz->ColCorr > Coluna )
         {
            dirNaoDiagonal = MAT_DirOeste ;
         } else
         {
            dirNaoDiagonal = MAT_DirLeste ;
         } /* if */
      } else
      {
         /* Sobraram linhas para andar */
         if ( pMatriz->LinhaCorr > Linha )
         {
            dirNaoDiagonal = MAT_DirNorte ;
         } else
         {
            dirNaoDiagonal = MAT_DirSul ;
         } /* if */
      }

      /* Determina a direção do movimento diagonal */
      if ( pMatriz->ColCorr > Coluna )
      {
         /* Sudoeste / Noroeste */
         if ( Matriz->LinhaCorr > Linha )
         {
            dirDiagonal = MAT_DirNoroeste ;
         } else
         {
            dirDiagonal = MAT_DirSudoeste ;
         } /* if */
      } else
      {
         /* Sudeste / Nordeste */
         if ( pMatriz->LinhaCorr > Linha )
         {
            dirDiagonal = MAT_DirNordeste ;
         } else
         {
            dirDiagonal = MAT_DirSudeste ;
         } /* if */
      } /* if */

      /* Anda na diagonal */
      while ( distDiagonal > 0 )
      {
         if ( pMatriz->pCelCorr->pCelDir[ dirDiagonal ] == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         pMatriz->pCelCorr = pMatriz->pCelCorr->pCelDir[ dirDiagonal ] ;
         distDiagonal -- ;
      } /* while */

      /* Anda nas células restantes */
      while ( distNaoDiagonal > 0 )
      {
         if ( pMatriz->pCelCorr->pCelDir[ dirNaoDiagonal ] == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         pMatriz->pCelCorr = pMatriz->pCelCorr->pCelDir[ dirNaoDiagonal ] ;
         distNaoDiagonal -- ;
      }

      /* Atualiza as coodenadas da nova célula corrente */
      pMatriz->ColCorr = Coluna ;
      pMatriz->LinhaCorr = Linha ;

      return MAT_CondRetOK ;
   }

