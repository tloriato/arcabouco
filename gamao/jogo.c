/**********************************************************************
*
*  $MCD Módulo de definição: Módulo jogo
*
*  Arquivo gerado:              jogo.c
*  Letras identificadoras:      JOG
*
*  Projeto: Disciplina INF 1301
*  Autores: gbdo - Gabriel Barbosa de Oliveira
*           gdapm - Guilherme de Azevedo Pereira Marques
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor                  Data       Observações
*       1.00  gbdo, gdapm, pa, tdn   22/10/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo é responsável por interagir com o usuário e garantir
*     que as regras do gamão sejam seguidas.
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <assert.h>
#include   <time.h>
#include   "tabuleiro.h"
#include   "dado_pontos.h"
#include   "dado.h"
#include   "peca.h"
#include   "cores.h"
#include   "PecasCapturadas.h"
#include   "PecasFinalizadas.h"


/***********************************************************************
*
*  $TC Tipo de dados: JOG Opção de menu
*
*
***********************************************************************/

   typedef struct {

         char * texto ;
            /* Texto correspondente a esta opção que será impresso */

         void ( * funcao )( void ) ;
            /* Função que será chamada se o usuário escolher essa
             * opção */

         char tecla ;
            /* Tecla que será usada pelo usuário para selecionar
             * essa opção */

   } tpOpcaoMenu ;


/***** Protótipos das funções encapuladas no módulo *****/

   static void ImprimirTabuleiro( void ) ;

   static void NovaPartida( void ) ;

   static void SalvarPartida( void ) ;

   static void CarregarPartida( void ) ;

   static void JogarDados( void ) ;

   static void MoverPeca( void ) ;

   static int Menu( tpOpcaoMenu * pOpcoes , int ocultarTexto ) ;

   static int InserirPecas( unsigned int qtd , unsigned int pos , int cor ) ;

   static void CriarEstruturas( void ) ;

   static void DestruirEstruturas( void ) ;

   static void Sair( void ) ;

   static void MenuJogada( void ) ;

   static void JogadorInicial( void ) ;

   static void CombinacoesDados( int * movimentos ) ;


/*****  Variáveis globais ao módulo  *****/

   static TAB_tppTabuleiro tabuleiro = NULL ; /* Tabuleiro do jogo */
   static DPO_tpJogador vez = DPO_Jogador1 ;  /* Indica de qual jogador é
                                               * a vez de jogar */
   static int Dado1 , Dado2 ;                 /* Resultado da última jogada
                                                 de dados */
   static int FimPartida ;                    /* Se 1, indica que a partida
                                                 terminou */

/*****  Constantes globais ao módulo  *****/

   /* Caracteres que representam as peças de cada jogador */
   static const char CharPeca[ 2 ]  = { 'O' , '@' } ;

   /* Fundo de uma posição do tabuleiro */
   static const char StrFundo[] = "------------------" ;

   /* Arrumação das peças no início de uma partida */
   static const struct
   {
      unsigned int pos;
      unsigned int qtd;
      int cor;
   } ArrumacaoInicial[] = {
        { 0  , 2 , DPO_Jogador1 } , { 5  , 5 , DPO_Jogador2 } ,
        { 11 , 5 , DPO_Jogador1 } , { 12 , 5 , DPO_Jogador2 } ,
        { 18 , 5 , DPO_Jogador1 } , { 23 , 2 , DPO_Jogador2 } ,
        { 16 , 3 , DPO_Jogador1 } , { 7  , 3 , DPO_Jogador2 } } ;

   /* Indicam se quantas vezes ainda podemos usar cada dado.
    * No caso de dados iguais cada um pode ser usado duas vezes */
   static int d1Disponivel = 0 ;
   static int d2Disponivel = 0 ;

   /* Peças finalizadas dos jogadores */
   static PFN_tppFinalizadas Final[ 2 ] ;

   /* Peças na barra dos jogadores */
   static PCA_tppCapturadas Bar[ 2 ] ;

/*****  Código das funções encapsuladas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: JOG Jogador Inicial
*
*  $ED Descrição da função
*     Decide o jogador que irá fazer a primeira jogada.
*
***********************************************************************/

   static void JogadorInicial( void )
   {

      int dado1 = 0 , dado2 = 0 ;

      while ( dado1 == dado2 )
      {
         DAD_JogarDados( &dado1 , &dado2 ) ;
      } /* while */

      printf( "O dado rolado pelo jogador %c deu: %d\n" , CharPeca[ DPO_Jogador1 ] , dado1 ) ;
      printf( "O dado rolado pelo jogador %c deu: %d\n" , CharPeca[ DPO_Jogador2 ] , dado2 ) ;

      vez = dado1 > dado2 ? DPO_Jogador1 : DPO_Jogador2 ;
      printf( "\n" COR_MENSAGEM "O jogador inicial é %c" COR_PADRAO "\n\n" , CharPeca[ vez ] ) ;

   } /* Fim função: JOG Jogador Inicial */


/***********************************************************************
*
*  $FC Função: JOG Imprimir tabuleiro
*
*  $ED Descrição da função
*     Imprime o estado atual do tabuleiro em ASCII na tela.
*
***********************************************************************/

   static void ImprimirTabuleiro( void )
   {

      #define LARGURA 18  /* 15 peças + 3 traços '-' */
      int pos , cor , fundo , qtd_bar , qtd_fin ;
      unsigned int qtd ;
      char linha[ LARGURA + 1 ] ;
      char * cor_fundo[ 2 ] = { COR_BG1 , COR_BG2 } ;
      int valor ;

      /* Imprime as peças na barra e finalizadas */
      PCA_ContaPecas( Bar[ DPO_Jogador1 ] , &qtd_bar ) ;
      PFN_ContaPecas( Final[ DPO_Jogador1 ] , &qtd_fin ) ;

      DPO_ObterPontos( &valor ) ;
      printf( "\nValor da partida: %d\n\n" , valor ) ;
      printf( "   Peças capturadas  |     Peças Finalizadas\n" ) ;

      /* Barra 1 */
      memset( linha , CharPeca[ DPO_Jogador1 ] , qtd_bar ) ;
      linha[ qtd_bar ] = '\0' ;
      printf( "   %s%s   |   " , linha , &StrFundo[ qtd_bar + 3 ] ) ;

      /* Finalizadas 1 */
      memset( linha , CharPeca[ DPO_Jogador1 ] , qtd_fin ) ;
      linha[ qtd_fin ] = '\0' ;
      printf( "   %s%s\n" , linha , &StrFundo[ qtd_fin + 3] ) ;

      PCA_ContaPecas( Bar[ DPO_Jogador2 ] , &qtd_bar ) ;
      PFN_ContaPecas( Final[ DPO_Jogador2 ] , &qtd_fin ) ;

      /* Barra 2 */
      memset( linha , CharPeca[ DPO_Jogador2 ] , qtd_bar ) ;
      linha[ qtd_bar ] = '\0' ;
      printf( "   %s%s   |   " , linha , &StrFundo[ qtd_bar + 3 ] ) ;

      /* Finalizadas 2 */
      memset( linha , CharPeca[ DPO_Jogador2 ] , qtd_fin ) ;
      linha[ qtd_fin ] = '\0' ;
      printf( "   %s%s\n\n" , linha , &StrFundo[ qtd_fin + 3 ] ) ;

      /* Imprime o tabuleiro */
      fundo = 0 ;
      for ( pos = 0 ; pos < TAB_QUANTIDADE_POS / 2 ; pos ++ )
      {
         /* Insere uma linha em branco dividindo o tabuleiro ao meio */
         if ( pos == TAB_QUANTIDADE_POS / 4 )
         {
            printf( "\n" ) ;
         } /* if */

         if ( TAB_ContarPecas( tabuleiro , pos , &qtd , &cor ) != TAB_CondRetOK )
         {
            printf( "\nPosição inválida ao imprimir o tabuleiro\n" ) ;
            return ;
         } /* if */

         /* Exemplo: A  @@@@@@------------> */
         if ( qtd )
         {
            memset( linha , CharPeca[ cor ] , qtd ) ;
         } /* if */
         linha[ qtd ] = '\0' ;

         printf( COR_LETRA_POS "%c  " COR_PADRAO , 'A' + pos ) ;
         printf( cor_fundo[ fundo ] ) ;
         printf( "%s%s>" COR_PADRAO "     " , linha , &StrFundo[ qtd ] ) ;

         if ( TAB_ContarPecas( tabuleiro , TAB_QUANTIDADE_POS - pos - 1 , &qtd , &cor ) != TAB_CondRetOK )
         {
            printf( "\nPosição inválida ao imprimir o tabuleiro\n" ) ;
            return ;
         } /* if */

         /* Exemplo: <--------------OOOO  X */
         if ( qtd )
         {
            memset( linha , CharPeca[ cor ] , qtd ) ;
         } /* if */
         linha[ qtd ] = '\0' ;

         fundo = ! fundo ;
         printf( cor_fundo[ fundo ] ) ;
         printf( "<%s%s" COR_PADRAO , &StrFundo[ qtd ] , linha ) ;
         printf( "  " COR_LETRA_POS "%c" COR_PADRAO "\n" , 'X' - pos ) ;
      } /* for */

      printf( "\n" ) ;

   } /* Fim função: JOG Imprimir tabuleiro */


/***********************************************************************
*
*  $FC Função: JOG Nova partida
*
*  $ED Descrição da função
*     Inicia uma nova partida de jogo.
*
***********************************************************************/

   static void NovaPartida( void )
   {

      int i , qtd ;

      if ( tabuleiro != NULL )
      {
         DestruirEstruturas( ) ;
      } /* if */

      CriarEstruturas( ) ;
      FimPartida = 0 ;

      /* Arrumação inicial do tabuleiro */
      qtd = sizeof( ArrumacaoInicial ) / sizeof( ArrumacaoInicial[0] ) ;

      for ( i = 0 ; i < qtd ; i ++ )
      {
         if ( ! InserirPecas( ArrumacaoInicial[ i ].qtd ,
                              ArrumacaoInicial[ i ].pos ,
                              ArrumacaoInicial[ i ].cor ) )
         {
            printf( "Erro ao inserir as peças no tabuleiro\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      ImprimirTabuleiro( ) ;
      JogadorInicial( ) ;
      MenuJogada( ) ;

      while ( ! FimPartida )
      {
         MenuJogada( ) ;
      } /* while */

   } /* Fim função: JOG Nova partida */


/***********************************************************************
*
*  $FC Função: JOG Salvar partida
*
*  $ED Descrição da função
*     Salva a partida atual em um arquivo.
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - essa função só pode ser chamada entre as jogadas de um jogador
*       e outro, nunca durante uma jogada.
*
*  Assertivas de saída:
*     - estado atual do jogo salvo no arquivo.
*
***********************************************************************/

   static void SalvarPartida( void )
   {

      int i ;
      int pontos ;
      int podeDobrar ; /* Jogador 1 pode dobrar se 64 > pontos > 1 */
      int qtd1 , qtd2 ;
      FILE * f = fopen( "partida.txt" , "w" ) ;

      if ( f == NULL )
      {
         printf( "Não foi possível criar o arquivo!\n" ) ;
         return ;
      } /* if */

      /* Grava tabuleiro */
      for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
      {
         unsigned int quantidade ;
         int cor ;
         TAB_ContarPecas( tabuleiro, i , &quantidade , &cor ) ;
         fprintf( f , "%d %X\n" , cor , quantidade ) ;
      } /* for */

      /* Grava a quantidade de peças finalizadas de cada jogador */
      PFN_ContaPecas( Final[ DPO_Jogador1 ] , &qtd1 ) ;
      PFN_ContaPecas( Final[ DPO_Jogador2 ] , &qtd2 ) ;
      fprintf( f , "%d %d\n" , qtd1 , qtd2 ) ;

      /* Grava a quantidade de peças na barra de cada jogador */
      PCA_ContaPecas( Bar[ DPO_Jogador1 ] , &qtd1 ) ;
      PCA_ContaPecas( Bar[ DPO_Jogador2 ] , &qtd2 ) ;
      fprintf( f , "%d %d\n" , qtd1 , qtd2 ) ;

      /* Grava valor da partida (dado pontos) */
      DPO_ObterPontos( &pontos ) ;
      DPO_PodeDobrar( DPO_Jogador1 , &podeDobrar ) ;
      fprintf( f, "%d %d\n" , pontos , podeDobrar ) ;

      /* Grava de qual jogador é a vez */
      fprintf( f , "%d\n" , vez == DPO_Jogador1 ) ;

      fclose( f ) ;

   } /* Fim função: JOG Salvar partida */


/***********************************************************************
*
*  $FC Função: JOG Carregar partida
*
*  $ED Descrição da função
*     Carrega a partida salva de um arquivo.
*
***********************************************************************/

   static void CarregarPartida( void )
   {

      int i ;
      int pontos , idVez ;
      int podeDobrar ; /* Jogador 1 pode dobrar se 64 > pontos > 1 */
      unsigned int qtd[ TAB_QUANTIDADE_POS ] ;
      int cor[ TAB_QUANTIDADE_POS ] ;
      unsigned int bar1 , bar2, fin1 , fin2 ;
      FILE * f = fopen( "partida.txt" , "r" ) ;

      if ( f == NULL )
      {
         printf( "Não foi possível abrir o arquivo!\n" ) ;
         return ;
      } /* if */

      /* Lê a quantidade de peças e a cor de cada posição do tabuleiro */
      for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
      {
         if ( fscanf( f , "%u %x\n" , &cor[ i ] , &qtd[ i ] ) != 2 )
         {
            printf( "Erro ao ler o arquivo\n" ) ;
            fclose( f ) ;
            return ;
         } /* if */
      } /* for */

      if ( fscanf( f , "%u %u\n" , &fin1 , &fin2 ) != 2 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      if ( fscanf( f , "%u %u\n" , &bar1 , &bar2 ) != 2 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      if ( fscanf( f , "%d %d\n" , &pontos , &podeDobrar ) != 2 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      if ( fscanf( f , "%d\n" , &idVez ) != 1 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      /* Todos os dados foram lidos sem erro, altera os parâmetros do
       * jogo */

      /* Cria um novo jogo */
      DestruirEstruturas( ) ;
      CriarEstruturas( ) ; /* Aborta o programa em caso de falha */

      /* Adiciona as peças */
      for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
      {
         if ( ! InserirPecas( qtd[ i ] , i , cor[ i ] ) )
         {
            printf( "Erro ao criar a peça\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      /* Preenche peças finalizadas e na barra */
      for ( i = 0 ; i < bar1 ; i ++ )
      {
         PEC_tppPeca peca ;
         if ( PEC_Criar( &peca , DPO_Jogador1 ) != PEC_CondRetOK )
         {
            printf( "Erro ao criar a peça\n" ) ;
            Sair( ) ;
         } /* if */

         if ( PCA_InserirPeca( Bar[ DPO_Jogador1 ] , peca ) != PCA_CondRetOK )
         {
            printf( "Erro ao inserir a peça.\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      for ( i = 0 ; i < bar2 ; i ++ )
      {
         PEC_tppPeca peca ;
         if ( PEC_Criar( &peca , DPO_Jogador2 ) != PEC_CondRetOK )
         {
            printf( "Erro ao criar a peça\n" ) ;
            Sair( ) ;
         } /* if */

         if ( PCA_InserirPeca( Bar[ DPO_Jogador2 ] , peca ) != PCA_CondRetOK )
         {
            printf( "Erro ao inserir a peça.\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      for ( i = 0 ; i < fin1 ; i ++ )
      {
         PEC_tppPeca peca ;
         if ( PEC_Criar( &peca , DPO_Jogador1 ) != PEC_CondRetOK )
         {
            printf( "Erro ao criar a peça\n" ) ;
            Sair( ) ;
         } /* if */

         if ( PFN_InserirPeca( Final[ DPO_Jogador1 ] , peca ) != PFN_CondRetOK )
         {
            printf( "Erro ao inserir a peça.\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      for ( i = 0 ; i < fin2 ; i ++ )
      {
         PEC_tppPeca peca ;
         if ( PEC_Criar( &peca , DPO_Jogador2 ) != PEC_CondRetOK )
         {
            printf( "Erro ao criar a peça\n" ) ;
            Sair( ) ;
         } /* if */

         if ( PFN_InserirPeca( Final[ DPO_Jogador2 ] , peca ) != PFN_CondRetOK )
         {
            printf( "Erro ao inserir a peça.\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      DPO_DefinirPontosVez( pontos , podeDobrar ) ;

      if ( ( idVez != (int) DPO_Jogador1 )
        && ( idVez != (int) DPO_Jogador2 ) )
      {
         printf( "Jogador inválido no arquivo.\n" ) ;
         Sair( ) ;
      } /* if */

      vez = idVez ;

      ImprimirTabuleiro( ) ;

      printf( COR_MENSAGEM "Vez: %c" COR_PADRAO "\n\n" , CharPeca[ vez ] ) ;

   } /* Fim função: JOG Carregar partida */


/***********************************************************************
*
*  $FC Função: JOG Jogar dados
*
*  $ED Descrição da função
*     Joga os dados para determinar o número de movimentos do jogador e
*     inicia a próxima jogada.
*
***********************************************************************/

   static void JogarDados( void )
   {

      DAD_JogarDados( &Dado1 , &Dado2 ) ;
      if ( Dado1 == Dado2 )
      {
         d1Disponivel = 2 ;
         d2Disponivel = 2 ;
      }
      else
      {
         d1Disponivel = 1 ;
         d2Disponivel = 1 ;
      } /* if */

      printf( "\n" COR_MENSAGEM "Dados: %d  %d" COR_PADRAO "\n\n" , Dado1 , Dado2 ) ;

      MoverPeca( ) ;

   } /* Fim função: JOG Jogar dados */


/***********************************************************************
*
*  $FC Função: JOG Combinações de Dados
*
*  $ED Descrição da função
*     Calcula as possíveis combinações de dados
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - movimentos deve ser um vetor válido com pelo menos 5 posições
*
*  Assertivas de saída:
*     - Combinações dos dados escritas no vetor.
*     - Último elemento do vetor igual a 0.
*
***********************************************************************/

   static void CombinacoesDados( int * movimentos )
   {

      int i ;
      if ( Dado1 != Dado2 )
      {
         i = 0 ;
         if ( d1Disponivel != 0 )
         {
            movimentos[ i ] = Dado1 ;
            i ++ ;
         } /* if */

         if ( d2Disponivel != 0 )
         {
            movimentos[ i ] = Dado2 ;
            i ++ ;
         } /* if */

         if ( ( d1Disponivel != 0 ) && ( d2Disponivel != 0 ) )
         {
            movimentos[ i ] = Dado1 + Dado2 ;
            i ++ ;
         } /* if */
      }
      else
      {
         for ( i = 0 ; i < ( d1Disponivel + d2Disponivel ) ; i ++ )
         {
            movimentos[ i ] = ( i + 1 ) * Dado1 ;
         } /* for */
      } /* if */

      movimentos[ i ] = 0 ;

   } /* Fim função: JOG Combinações de Dados */


/***********************************************************************
*
*  $FC Função: JOG Mover peça
*
*  $ED Descrição da função
*     Move uma peça do jogador atual.
*
***********************************************************************/

   static void MoverPeca( void )
   {

      /* Jogador 1 se move de A -> X ( 0 -> 23 ) => direcao = 1
       * Jogador 2 se move de X -> A ( 23 -> 0 ) => direcao = -1 */
      int direcao = vez == DPO_Jogador1 ? 1 : -1 ;

      int temBar = 0 ; /* Inidica que o jogador tem peças na barra */
      int podeFinalizar = 1 ; /* Indica que todas as peças estão no
                                 campo do jogador e o jogador pode mover
                                 peças para a área de peças finalizadas. */

      /* No máximo haverá peças de um jogador em todas menos uma posições
       * do tabuleiro */
      tpOpcaoMenu opcoes[ TAB_QUANTIDADE_POS ] ;
      int opcao = 0 ; /* índice da próxima opção do menu */

      /* Determina podeFinalizar */
      int i , cor ;
      unsigned int qtd ;

      /* Guarda as combinações possíveis de movimento baseado nos dados.
       * Existem, no máximo, 4 movimentos possíveis */
      int movimentos[ 5 ] ;

      /* Indica quais posições têm peças que podem ser movidas.
       * O valor de podeMover[ pos ] é uma máscara de bits que indica
       * quais elementos do vetor movimentos são movimentos válidos para
       * essa peça. */
      char podeMover[ TAB_QUANTIDADE_POS ] ;

      /* Guarda o jogador adversário do atual (vez) */
      DPO_tpJogador adversario = vez == DPO_Jogador1 ? DPO_Jogador2 : DPO_Jogador1 ;

      /* Verifica se o jogador tem peças na barra */
      int qtd_pca ;
      PCA_ContaPecas( Bar[ vez ] , &qtd_pca ) ;
      temBar = qtd_pca != 0 ;

      /* Determina se o jogador já pode finalizar peças */
      if ( ! temBar )
      {
         if ( vez == DPO_Jogador1 )
         {
            /* Testa as 18 posições que não são as últimas 6 */
            for ( i = 0 ; i < TAB_QUANTIDADE_POS - 6 ; i ++ )
            {
               /* Sabemos que a posição é válida, não é preciso testar
                * o retorno */
               TAB_ContarPecas( tabuleiro , i , &qtd , &cor ) ;
               if ( ( qtd > 0 ) && ( cor == DPO_Jogador1 ) )
               {
                  podeFinalizar = 0 ;
                  break ;
               } /* if */
            } /* for */
         }
         else
         {
            /* Testa as 18 posições que não são as primeiras 6 */
            for ( i = 6 ; i < TAB_QUANTIDADE_POS ; i ++ )
            {
               /* Sabemos que a posição é válida, não é preciso testar
                * o retorno */
               TAB_ContarPecas( tabuleiro , i , &qtd , &cor ) ;
               if ( ( qtd > 0 ) && ( cor == DPO_Jogador2 ) )
               {
                  podeFinalizar = 0 ;
                  break ;
               } /* if */
            } /* for */
         } /* if */
      } /* if */

      /* Se houver peças na barra, o jogador deve primeiro coloca-las em jogo */
      int d1Disp = d1Disponivel , d2Disp = d2Disponivel ;
      while ( temBar && ( d1Disp || d2Disp ) )
      {
         int posPara ;
         printf( "Jogador %c deve retornar a(s) peça(s) da barra ao jogo.\n" , CharPeca[ vez ] ) ;
         if ( vez == DPO_Jogador1 )
         {
            TAB_ContarPecas( tabuleiro , Dado1 - 1 , &qtd , &cor ) ;
            if ( ( qtd == 0 ) || ( cor == vez )
              || ( ( qtd == 1 ) && ( cor == adversario ) ) )
            {
               printf( "%c, " , 'A' + Dado1 - 1 ) ;
               opcoes[ opcao ].texto = "" ;
               opcoes[ opcao ].tecla = 'A' + Dado1 - 1 ;
               opcoes[ opcao ].funcao = NULL ;
               opcao ++ ;
            }
            else
            {
               d1Disp = 0 ;
            } /* if */

            if ( Dado1 != Dado2 )
            {
               TAB_ContarPecas( tabuleiro , Dado2 - 1 , &qtd , &cor ) ;
               if ( ( qtd == 0 ) || ( cor == vez )
                 || ( ( qtd == 1 ) && ( cor == adversario ) ) )
               {
                  printf( "%c, " , 'A' + Dado2 - 1 ) ;
                  opcoes[ opcao ].texto = "" ;
                  opcoes[ opcao ].tecla = 'A' + Dado2 - 1 ;
                  opcoes[ opcao ].funcao = NULL ;
                  opcao ++ ;
               }
               else
               {
                  d2Disp = 0 ;
               } /* if */
            } /* if */
         }
         else /* Vez = DPO_Jogador2 */
         {
            TAB_ContarPecas( tabuleiro , TAB_QUANTIDADE_POS - Dado1 , &qtd , &cor ) ;
            if ( ( qtd == 0 ) || ( cor == vez )
              || ( ( qtd == 1 ) && ( cor == adversario ) ) )
            {
               printf( "%c, " , 'X' - Dado1 + 1 ) ;
               opcoes[ opcao ].texto = "" ;
               opcoes[ opcao ].tecla = 'X' - Dado1 + 1 ;
               opcoes[ opcao ].funcao = NULL ;
               opcao ++ ;
            }
            else
            {
               d1Disp = 0 ;
            } /* if */

            if ( Dado1 != Dado2 )
            {
               TAB_ContarPecas( tabuleiro , TAB_QUANTIDADE_POS - Dado2 , &qtd , &cor ) ;
               if ( ( qtd == 0 ) || ( cor == vez )
                 || ( ( qtd == 1 ) && ( cor == adversario ) ) )
               {
                  printf( "%c, " , 'X' - Dado2 + 1 ) ;
                  opcoes[ opcao ].texto = "" ;
                  opcoes[ opcao ].tecla = 'X' - Dado2 + 1 ;
                  opcoes[ opcao ].funcao = NULL ;
                  opcao ++ ;
               }
               else
               {
                  d2Disp = 0 ;
               } /* if */
            } /* if */
         } /* if */

         if ( opcao == 0 )
         {
            printf( COR_MENSAGEM "Não há jogadas possíveis. Passando a vez..." COR_PADRAO "\n" ) ;
            d1Disponivel = 0 ;
            d2Disponivel = 0 ;
            break ;
         } /* if */

         printf( "\n" ) ;
         opcoes[ opcao ].texto  = NULL ;
         opcoes[ opcao ].tecla  = '\0' ;
         opcoes[ opcao ].funcao = NULL ;

         posPara = Menu( opcoes , 1 ) ;

         /* Converte posPara para uma posição do tabulero */
         posPara = opcoes[ posPara ].tecla - 'A' ;

         PEC_tppPeca peca ;
         TAB_ContarPecas( tabuleiro , posPara , &qtd , &cor ) ;
         if ( ( qtd == 1 ) && ( cor == adversario ) )
         {
            /* Captura a peça adversária */
            TAB_RemoverPeca( tabuleiro , posPara , &peca ) ;
            PCA_InserirPeca( Bar[ adversario ] , peca ) ;
         } /* if */

         PCA_RemoverPeca( Bar[ vez ] , &peca ) ;

         if ( vez == DPO_Jogador1 )
         {
            if ( ( posPara + 1 == Dado1 ) && d1Disponivel )
            {
               d1Disponivel = 0 ;
               d1Disp = 0 ;
            }
            else
            {
               d2Disponivel = 0 ;
               d2Disp = 0 ;
            } /* if */

           if ( TAB_IncluirPeca( tabuleiro , posPara , peca ) != TAB_CondRetOK )
           {
              printf( "Erro ao inserir a peça no tabuleiro.\n" ) ;
              Sair( ) ;
           } /* if */
         }
         else
         {
            if ( ( posPara == TAB_QUANTIDADE_POS - Dado1 ) && d1Disponivel )
            {
               d1Disponivel = 0 ;
            }
            else
            {
               d2Disponivel = 0 ;
            } /* if */

           if ( TAB_IncluirPeca( tabuleiro , posPara , peca ) != TAB_CondRetOK )
           {
              printf( "Erro ao inserir a peça no tabuleiro.\n" ) ;
              Sair( ) ;
           } /* if */
         } /* if */

         /* Verifica se o jogador tem peças na barra */
         PCA_ContaPecas( Bar[ vez ] , &qtd_pca ) ;
         temBar = qtd_pca != 0 ;

         ImprimirTabuleiro( ) ;

      } /* while */



      /* Deixa o jogador continuar jogando enquanto houver pontos nos dados */
      while ( ( d1Disponivel || d2Disponivel ) && ( ! temBar ) )
      {
         CombinacoesDados( movimentos ) ;

         /* Determina quais posições têm peças que podem ser movidas com
          * o resultado dos dados */
         int d ;         /* Combinação de dados */
         int cor_dest ;  /* Cor das peças na potencial posição de destino */
         unsigned int qtd_dest ;  /* Quantidade de peças na potencial posição de destino */
         memset( podeMover , 0 , TAB_QUANTIDADE_POS ) ;
         for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
         {
            /* Sabemos que a posição é válida, não é preciso testar
             * o retorno */
            TAB_ContarPecas( tabuleiro , i , &qtd , &cor ) ;
            if ( ( qtd > 0 ) && ( cor == vez ) ) /* posição tem peças desse jogador? */
            {
               /* Itera nos possíveis movimentos das peças nessa posição */
               for ( d = 0 ; ( d < 4 ) && ( movimentos[ d ] != 0 ) ; d ++ )
               {
                  /* Como o parâmetro posicao é unsigned, se i + direcao * movimentos[ d ]
                   * for negativo, TAB_ContarPecas verá um valor gigante (underflow) e portanto
                   * a lógica funciona igual ao caso de posicao >= TAB_QUANTIDADE_POS */
                  if ( TAB_ContarPecas( tabuleiro , i + direcao * movimentos[ d ] ,
                           &qtd_dest , &cor_dest ) == TAB_CondRetOK )
                  {
                     /* Posição de destino pode ter peças nossas, nenuma ou apenas 1 do adversário */
                     if ( ( qtd_dest == 0 ) || ( cor_dest == vez )
                           || ( ( qtd_dest == 1 ) && ( cor_dest == adversario ) ) )
                     {
                        podeMover[ i ] |= ( 1 << d ) ;
                     } /* if */
                  }
                  else
                  {
                     /* Se a posição de destino >= TAB_QUANTIDADE_POS ( ou < 0 ), o
                      * jogador estaria finalizando a peça */
                     if ( podeFinalizar )
                     {
                        podeMover[ i ] |= ( 1 << d ) ;
                     } /* if */
                  } /* if */
               } /* for */
            } /* if */
         } /* for */

         /* Adiciona as opções ao menu */
         printf( "Escolha uma peça para mover:\n" ) ;
         for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
         {
            if ( podeMover[ i ] )
            {
               printf( "%c, " , 'A' + (char) i ) ;
               opcoes[ opcao ].texto = "" ;
               opcoes[ opcao ].tecla = 'A' + (char) i ;
               opcoes[ opcao ].funcao = NULL ;
               opcao ++ ;
            } /* if */
         } /* for */

         printf( "\n" ) ;
         opcoes[ opcao ].texto  = NULL ;
         opcoes[ opcao ].tecla  = '\0' ;
         opcoes[ opcao ].funcao = NULL ;

         /* Testa se há alguma jogada possível */
         if ( opcao == 0 )
         {
            printf( COR_MENSAGEM "Não há jogadas possíveis. Passando a vez..." COR_PADRAO "\n" ) ;
            break ;
         } /* if */

         /* Mostra menu */
         int posDe , posPara ; /* Opções de origem e destino da peça
                                  (posição) escolhidas pelo jogador */
         int podeFinalizarPeca = 0 ; /* Se 1, mostra a opção de finalizar
                                        a peça escolhida */
         posDe = Menu( opcoes , 1 ) ;

         /* Converte do índice do menu para uma posição no tabuleiro */
         posDe = opcoes[ posDe ].tecla - 'A' ;

         /* Monta um novo menu com as posições de destino válidas para a
          * peça escolhida */
         opcao = 0 ;
         printf( "Escolha a posição de destino:\n" ) ;
         for ( d = 0 ; ( d < 4 ) && ( movimentos[ d ] != 0 ) ; d ++ )
         {
            if ( podeMover[ posDe ] & ( 1 << d ) )
            {
               if ( ( posDe + direcao * movimentos[ d ] >= TAB_QUANTIDADE_POS )
                     || ( posDe + direcao * movimentos[ d ] < 0 ) )
               {
                  podeFinalizarPeca = 1 ;
               }
               else
               {
                  printf( "%c, " , 'A' + ( posDe + direcao * movimentos[ d ] ) ) ;
                  opcoes[ opcao ].texto = "" ; /* Não será mostrado */
                  opcoes[ opcao ].tecla = 'A' + ( posDe + direcao * movimentos[ d ] ) ;
                  opcoes[ opcao ].funcao = NULL ;
                  opcao ++ ;
               } /* if */
            } /* if */
         } /* for */

         printf( "\n" ) ;

         if ( podeFinalizarPeca )
         {
            printf( "Z -> Finalizar peça\n" ) ;
            opcoes[ opcao ].texto = "" ;
            opcoes[ opcao ].tecla = 'Z' ;
            opcoes[ opcao ].funcao = NULL ;
            opcao ++ ;
         } /* if */

         opcoes[ opcao ].texto  = NULL ;
         opcoes[ opcao ].tecla  = '\0' ;
         opcoes[ opcao ].funcao = NULL ;

         posPara = Menu( opcoes , 1 ) ;
         if ( opcoes[ posPara ].tecla == 'Z' )
         {
            /* Finaliza peça */
            PEC_tppPeca peca ;

            /* Sabemos que a posição é válida. Não é preciso testar o retorno */
            TAB_RemoverPeca( tabuleiro , posDe , &peca ) ;
            PFN_InserirPeca( Final[ vez ] , peca ) ;

            /* Calcula os pontos restantes nos dados */
            posPara = TAB_QUANTIDADE_POS ;
            int dp = direcao * ( posPara - posDe ) ; /* Número de posições
                                                        andadas */
            if ( Dado1 == Dado2 )
            {
               d1Disponivel += d2Disponivel ;
               d2Disponivel = 0 ;

               d1Disponivel -= dp / Dado1 ;
               if ( dp % Dado1 )
               {
                  d1Disponivel -- ;
               } /* if */
            }
            else
            {
               /* Se só tiver 1 dado disponível, usa esse */
               if ( d1Disponivel + d2Disponivel == 1 )
               {
                  d1Disponivel = 0 ;
                  d2Disponivel = 0 ;
               }
               else
               {
                  /* Tenta usar o dado menor primeiro */
                  if ( Dado1 < Dado2 )
                  {
                     if ( dp <= Dado1 )
                     {
                        d1Disponivel = 0 ;
                     }
                     else
                     {
                        if ( dp <= Dado2 )
                        {
                           d2Disponivel = 0 ;
                        }
                        else
                        {
                           d1Disponivel = 0 ;
                           d2Disponivel = 0 ;
                        }  /* if */
                     } /* if */
                  }
                  else /* Dado1 > Dado 2 */
                  {
                     if ( dp <= Dado2 )
                     {
                        d1Disponivel = 0 ;
                     }
                     else
                     {
                        if ( dp <= Dado1 )
                        {
                           d2Disponivel = 0 ;
                        }
                        else
                        {
                           d1Disponivel = 0 ;
                           d2Disponivel = 0 ;
                        }  /* if */
                     } /* if */
                  } /* if */
               } /* if */
            } /* if */
         }
         else
         {
            /* Converte a opção lida para uma posição no tabuleiro */
            posPara = opcoes[ posPara ].tecla - 'A' ;

            /* É uma captura de peça? */
            int cor_dest ;  /* Cor das peças na potencial posição de destino */
            unsigned int qtd_dest ;  /* Quantidade de peças na potencial posição de destino */

            TAB_ContarPecas( tabuleiro , posPara , &qtd_dest , &cor_dest ) ;
            if ( ( qtd_dest == 1 ) && ( cor_dest == adversario ) )
            {
               /* Primeiro move a peça adversária para a barra */
               PEC_tppPeca peca ;
               if ( TAB_RemoverPeca( tabuleiro , posPara , &peca ) != TAB_CondRetOK )
               {
                  printf( "Erro ao remover a peça adversária.\n" ) ;
                  break ;
               } /* if */

               if ( PCA_InserirPeca( Bar[ adversario ] , peca ) != PCA_CondRetOK )
               {
                  printf( "Erro ao mover a peça adversária para a barra.\n" ) ;
                  Sair( ) ;
               } /* if */
            } /* if */

            if ( TAB_MoverPeca( tabuleiro , posDe , posPara ) != TAB_CondRetOK )
            {
               /* Nunca deveria chegar aqui */
               printf( "Erro ao mover a peça\n" ) ;
               continue ;
            } /* if */

            /* Determina qual combinação de dados foi usada e 
             * disconta as posições andadas dos pontos disponíveis */
            int dp = direcao * ( posPara - posDe ) ; /* Número de posições
                                                        andadas */
            if ( Dado1 == Dado2 )
            {
               /* Dados iguais -> Considera como 4 jogadas do Dado1 */
               d1Disponivel = d1Disponivel + d2Disponivel ;
               d2Disponivel = 0 ;
               d1Disponivel -= dp / Dado1 ;
            }
            else
            {
               if ( dp == Dado1 )
               {
                  d1Disponivel = 0 ;
               }
               else
               {
                  if ( dp == Dado2 )
                  {
                     d2Disponivel = 0 ;
                  }
                  else
                  {
                     /* dp = Dado1 + Dado2 */
                     d1Disponivel = 0 ;
                     d2Disponivel = 0 ;
                  } /* if */
               } /* if */
            } /* if */
         } /* if */

         ImprimirTabuleiro( ) ;

      } /* while */

      /* Testa se o jogador ganhou a partida */
      int qtd_fin ;
      PFN_ContaPecas( Final[ vez ] , &qtd_fin ) ;
      if ( qtd_fin == 15 )
      {
         FimPartida = 1 ;
         printf( COR_MENSAGEM "Jogador %c venceu !" COR_PADRAO "\n" , CharPeca[ vez ] ) ;
      }
      else
      {
         /* Fim da vez. Muda para o próximo jogador */
         if ( vez == DPO_Jogador1 )
         {
            vez = DPO_Jogador2 ;
         }
         else
         {
            vez = DPO_Jogador1 ;
         } /* if */

         printf( COR_MENSAGEM "Vez do Jogador %c" COR_PADRAO "\n\n" , CharPeca[ vez ] ) ;
      } /* if */

   } /* Fim função: JOG Mover peça */


/***********************************************************************
*
*  $FC Função: JOG Menu
*
*  $ED Descrição da função
*     Imprime o menu, aguarda a escolha da opção e chama a função
*     correspondente
*
*  $EP Parâmetros
*     pOpcoes      - Vetor de opções do menu.
*     ocultarTexto - Se 1, apenas aguarda e valida as teclas, sem
*                    escrever as opções.
*
*  Assertivas de entrada:
*     - Vetor pOpcoes deve existir.
*     - A última posição do vetor deve conter NULL no campo texto.
*
*  Assertivas de saída:
*     - Menu impresso e função correspondente à opção escolhida pelo
*       usuário chamada (se existir).
*     - Índice da opção escolhida retornado.
*
*  $FV Valor retornado
*     Índice da opção escolhida.
*
***********************************************************************/

   static int Menu( tpOpcaoMenu * pOpcoes , int ocultarTexto )
   {

      assert( pOpcoes != NULL ) ;

      tpOpcaoMenu * pOp = pOpcoes ;
      if ( ! ocultarTexto )
      {
         while ( pOp->texto != NULL )
         {
            printf( "%c - %s\n" , pOp->tecla , pOp->texto ) ;
            pOp ++ ;
         } /* while */
      } /* if */

      /* Garante que o usuário escolha uma opção válida */
      while ( 1 )
      {
         char t = 0 ;
         int indice = 0 ;

         printf( "Escolha uma opção: " ) ;
         scanf( " %c" , &t ) ;

         pOp = pOpcoes ;
         while ( pOp->texto != NULL )
         {
            /* Não diferenciar entre maiúsculas e minúsculas */
            if ( ( pOp->tecla | ( 1 << 5 ) ) == ( t | ( 1<< 5 ) ) )
            {
               if ( pOp->funcao )
               {
                  pOp->funcao( ) ;
               } /* if */

               return indice ;
            } /* if */

            indice ++ ;
            pOp ++ ;
         } /* while */

         printf( "Opção inválida: %c\n" , t ) ;
      } /* while */

   } /* Fim função: JOG Menu */


/***********************************************************************
*
*  $FC Função: JOG Inserir Peças
*
*  $ED Descrição da função
*     Cria qtd peças na posição pos do tabuleiro
*
*  $EP Parâmetros
*     qtd - Quantidade de peças a adicionar
*     pos - Posição na qual adicionar as peças
*     cor - Cor das peças a adicionar
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro
*     - pos dever ser uma posição válida de tabuleiro
*
*  Assertivas de saída:
*     - qtd peças inseridas na posição pos do tabuleiro e retorno 1 ou
*       retorno 0 em caso de falha.
*
*  $FV Valor retornado
*     1 se as peças foram inseridas corretamente, 0 caso contrário.
*
***********************************************************************/

   static int InserirPecas( unsigned int qtd , unsigned int pos , int cor )
   {

      unsigned int i ;
      PEC_tppPeca peca ;

      for ( i = 0 ; i < qtd ; i ++ )
      {
         if ( PEC_Criar( &peca , cor ) != PEC_CondRetOK )
         {
            return 0 ;
         } /* if */

         if ( TAB_IncluirPeca( tabuleiro , pos , peca ) != TAB_CondRetOK )
         {
            PEC_Destruir( peca ) ;
            return 0 ;
         } /* if */
      } /* for */

      return 1 ;

   } /* Fim função: JOG Inserir Peças */


/***********************************************************************
*
*  $FC Função: JOG Menu Nova Partida
*
*  $ED Descrição da função
*     Mostra o menu no início de uma nova partida
*
*  Assertivas de saída:
*     - Dados jogados ou partida salva carregada ou jogo finalizado,
*       de acordo com a opção escolhida pelo usuário.
*
***********************************************************************/

   static void MenuJogada( void )
   {
      static const tpOpcaoMenu opcoes[] = {
                  { "Jogar dados"      , JogarDados      , 'J' } ,
                  { "Salvar Partida"   , SalvarPartida   , 'S' } ,
                  { "Carregar partida" , CarregarPartida , 'C' } ,
                  { "Sair"             , Sair            , 'X' } ,
                  { NULL               , NULL            , 0   } } ;

      Menu( (tpOpcaoMenu *)opcoes , 0 ) ;

   } /* Fim função: JOG Menu Nova Partida */


/***********************************************************************
*
*  $FC Função: JOG Criar Estruturas
*
*  $ED Descrição da função
*     Aloca as instâncias das estruturas de dados utilizadas:
*     tabuleiro, Bar[ DPO_Jogador1 ], Bar[ DPO_Jogador2 ],
*     Final[ DPO_Jogador1 ] e Final[ DPO_Jogador2 ].
*
*  Assertivas de entrada:
*     - tabuleiro, Bar[ DPO_Jogador1 ], Bar[ DPO_Jogador2 ],
*       Final[ DPO_Jogador1 ] e Final[ DPO_Jogador2 ] não devem apontar
*       para memória ainda alocada.
*
*  Assertivas de saída:
*     Estruturas citadas acima criadas
*
***********************************************************************/

   static void CriarEstruturas( void )
   {

      if ( TAB_Criar( &tabuleiro ) != TAB_CondRetOK )
      {
         printf( "Erro ao criar o tabuleiro\n" ) ;
         tabuleiro = NULL ;
         Sair( ) ;
      } /* if */

      if ( PCA_Criar( &Bar[ DPO_Jogador1 ] ) != PCA_CondRetOK )
      {
         printf( "Erro ao criar a barra\n" ) ;
         Bar[ DPO_Jogador1 ] = NULL ;
         Sair( ) ;
      } /* if */

      if ( PCA_Criar( &Bar[ DPO_Jogador2 ] ) != PCA_CondRetOK )
      {
         printf( "Erro ao criar a barra\n" ) ;
         Bar[ DPO_Jogador2 ] = NULL ;
         Sair( ) ;
      } /* if */

      if ( PFN_Criar( &Final[ DPO_Jogador1 ] ) != PFN_CondRetOK )
      {
         printf( "Erro ao criar peças finalizadas\n" ) ;
         Final[ DPO_Jogador1 ] = NULL ;
         Sair( ) ;
      } /* if */

      if ( PFN_Criar( &Final[ DPO_Jogador2 ] ) != PFN_CondRetOK )
      {
         printf( "Erro ao criar peças finalizadas\n" ) ;
         Final[ DPO_Jogador2 ] = NULL ;
         Sair( ) ;
      } /* if */

   } /* Fim Função: JOG Criar Estruturas */


/***********************************************************************
*
*  $FC Função: JOG Destruir Estruturas
*
*  $ED Descrição da função
*     Libera a memória alocada pelas estruturas de dados utilizadas
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro
*       ou NULL
*     - Bar[ DPO_Jogador1 ] e Bar[ DPO_Jogador2 ] devem ser instâncias
*       válidas de PecasCapturadas ou NULL
*     - Final[ DPO_Jogador1 ] e Final[ DPO_Jogador2 ] devem ser
*       instâncias válidas de PecasFinalizadas ou NULL
*
*  Assertivas de saída:
*     - Memória alocada dinâmicamente pelas estruturas de dados liberada
*     - Ponteiros para as estruturas apontam para NULL
*
***********************************************************************/

   static void DestruirEstruturas( void )
   {

      if ( tabuleiro != NULL )
      {
         TAB_Destruir( tabuleiro ) ;
         tabuleiro = NULL ;
      } /* if */

      if ( Bar[ DPO_Jogador1 ] != NULL )
      {
          PCA_Destruir( Bar[ DPO_Jogador1 ] ) ;
          Bar[ DPO_Jogador1 ] = NULL ;
      } /* if */

      if ( Bar[ DPO_Jogador2 ] != NULL )
      {
          PCA_Destruir( Bar[ DPO_Jogador2 ] ) ;
          Bar[ DPO_Jogador2 ] = NULL ;
      } /* if */

      if ( Final[ DPO_Jogador1 ] != NULL )
      {
          PFN_Destruir( Final[ DPO_Jogador1 ] ) ;
          Final[ DPO_Jogador1 ] = NULL ;
      } /* if */

      if ( Final[ DPO_Jogador2 ] != NULL )
      {
          PFN_Destruir( Final[ DPO_Jogador2 ] ) ;
          Final[ DPO_Jogador2 ] = NULL ;
      } /* if */

   } /* Fim Função: JOG Destruir Estruturas */


/***********************************************************************
*
*  $FC Função: JOG Sair
*
*  $ED Descrição da função
*     Libera a memória alocada pelos módulos do programa e termina
*     imediatamente a execução.
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro
*     - Bar[ DPO_Jogador1 ] e Bar[ DPO_Jogador2 ] devem ser instâncias
*       válidas de PeçasCapturadas
*     - Final[ DPO_Jogador1 ] e Final[ DPO_Jogador2 ] devem ser 
*       instâncias válidas de PeçasFinalizadas
*
*  Assertivas de saída:
*     Memória alocada dinâmicamente pela aplicação liberada e execução
*     finalizada.
*
***********************************************************************/

   static void Sair( void )
   {

      DestruirEstruturas( ) ;
      exit( 0 ) ;

   } /* Fim Função: JOG Sair */


/***********************************************************************
*
*  $FC Função: Main
*
*  $ED Descrição da função
*     Ponto de entrada do programa.
*
***********************************************************************/

   int main( void )
   {
      /* Inicializa o rand */
      srand( time( NULL ) ) ;

      while ( 1 )
      {
         NovaPartida( ) ;
      } /* while */

      return 0 ;

   } /* Fim função: Main */


/********** Fim do módulo de implementação: Módulo jogo **********/

