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
#include   "tabuleiro.h"
#include   "dado_pontos.h"
#include   "dado.h"
#include   "peca.h"
#include   "cores.h"

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

   static int Menu( tpOpcaoMenu * pOpcoes ) ;

   static int InserirPecas( unsigned int qtd , unsigned int pos , int cor ) ;

   static void CriarEstruturas( void ) ;

   static void DestruirEstruturas( void ) ;

   static void Sair( void ) ;

   static void MenuNovaPartida( void ) ;

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
   // static PFN_tppFinalizadas Final[ 2 ] ;

   /* Peças na barra dos jogadores */
   // static BAR_tppBarra Bar[ 2 ] ;

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

      int dado1 , dado2 , entrada ;
      char jogInic ;
      printf( "Jogadores , para rolarem dois dados para decidirem o jogador inicial digitem 1.\n" ) ;
      scanf( "%d" , &entrada ) ;
      if ( entrada == 1 )
      {
         DAD_JogarDados( &dado1 , &dado2 ) ;
         printf( "O dado rolado pelo jogador 1 deu: %d\n" , dado1 ) ;
         printf( "O dado rolado pelo jogador 2 deu: %d\n" , dado2 ) ;

         if ( dado1 == dado2 )
         {
            printf( "Rerrolagem de dados é necessária já que os valores foram iguais" ) ;
            JogadorInicial( ) ;
         }
         else
         {
            vez = dado1 > dado2 ? DPO_Jogador1 : DPO_Jogador2 ;
            jogInic = dado1 > dado2 ? 1 : 2 ;
            printf( "\n" COR_MENSAGEM "O jogador inicial é %d" COR_PADRAO "\n" , jogInic ) ;
         } /* if */
      }
      else
      {
         JogadorInicial( ) ;
      } /* if */

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
      int pos , cor , fundo ;
      unsigned int qtd ;
      char linha[ LARGURA + 1 ] ;
      char * cor_fundo[ 2 ] = { COR_BG1 , COR_BG2 } ;

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
         memset( linha , CharPeca[ cor ] , qtd ) ;
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
         memset( linha , CharPeca[ cor ] , qtd ) ;
         linha[ qtd ] = '\0' ;

         fundo = ! fundo ;
         printf( cor_fundo[ fundo ] ) ;
         printf( "<%s%s" COR_PADRAO , &StrFundo[ qtd ] , linha ) ;
         printf( "  " COR_LETRA_POS "%c" COR_PADRAO "\n" , 'X' - pos ) ;
      } /* for */

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
      JogadorInicial ( ) ;

      while ( ! FimPartida )
      {
         MenuNovaPartida( ) ;
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

      /* TODO Grava a quantidade de peças finalizadas de cada jogador */
      fprintf( f , "0 0\n" ) ; /* dummy */

      /* TODO Grava a quantidade de peças na barra de cada jogador */
      fprintf( f , "0 0\n" ) ; /* dummy */

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

      int i , p ;
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

      /* TODO Preencher peças finalizadas e na barra */

      DPO_DefinirPontosVez( pontos , podeDobrar ) ;

      if ( ( idVez != (int) DPO_Jogador1 )
        && ( idVez != (int) DPO_Jogador2 ) )
      {
         printf( "Jogador inválido no arquivo.\n" ) ;
         Sair( ) ;
      } /* if */

      vez = idVez ;

      ImprimirTabuleiro( ) ;

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

      /* Jogador 1 se move de A -> X ( 0 -> 23 )
       * Jogador 2 se move de X -> A ( 23 -> 0 ) */

      // TODO tratar BAR

      int temBar = 0 ; /* Inidica que o jogador tem peças na barra */
      int podeFinalizar = 1 ; /* Indica que todas as peças estão no
                                 campo do jogador e o jogador pode mover
                                 peças para a área de peças finalizadas. */

      /* No máximo haverá peças de um jogador em 23 posições do tabuleiro */
      tpOpcaoMenu opcoes[ 24 ] ;
      char txtOps[ 2 ][ 23 ] ;

      /* Determina podeFinalizar */
      int i , cor ;
      unsigned int qtd ;

      /* Guarda as combinações possíveis de movimento baseado nos dados.
       * Existem, no máximo, 4 movimentos possíveis */
      int movimentos[ 5 ] ;

      /* Indica quais posições têm peças que podem ser movidas */
      char podeMover[ TAB_QUANTIDADE_POS ] ;


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

      while ( d1Disponivel || d2Disponivel )
      {
         CombinacoesDados( movimentos ) ;

         /* Determina quais posições têm peças que podem ser movidas com
          * o resultado dos dados */
         int opcao = 0 ; /* índice da próxima opção do menu */
         int cor_dest ; /* Cor das peças na potencial posição de destino */
         int qtd_dest ; /* Quantidade de peças na potencial posição de destino */
         memset( podeMover , 0 , TAB_QUANTIDADE_POS ) ;
         for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
         {
            /* Sabemos que a posição é válida, não é preciso testar
             * o retorno */
            TAB_ContarPecas( tabuleiro , i , &qtd , &cor ) ;
            if ( ( qtd > 0 ) && ( cor == vez ) ) /* posição tem peças desse jogador? */
            {
               if ( ( d1Disponivel != 0 )
                 && ( i + Dado1 < TAB_QUANTIDADE_POS ) ) /* Garante que a posição é válida */
               {
                  TAB_ContarPecas( tabuleiro , i + Dado1 , &qtd_dest , &cor_dest ) ;
                  if ( ( qtd_dest == 0 ) || ( cor_dest == vez ) )
                  {
                     podeMover[ i ] = 1 ;
                  } /* if */
               } /* if */

               if ( ( d2Disponivel != 0 )
                 && ( i + Dado2 < TAB_QUANTIDADE_POS ) /* Garante que a posição é válida */
                 && ( podeMover[ i ] == 0 ) ) /* e não sabemos se pode ser movida */
               {
                  TAB_ContarPecas( tabuleiro , i + Dado2 , &qtd_dest , &cor_dest ) ;
                  if ( ( qtd_dest == 0 ) || ( cor_dest == vez ) )
                  {
                     podeMover[ i ] = 1 ;
                  } /* if */
               } /* if */

               if ( ( d1Disponivel != 0 ) && ( d2Disponivel != 0 )
                 && ( i + Dado1 + Dado2 < TAB_QUANTIDADE_POS ) /* Garante que a posição é válida */
                 && ( podeMover[ i ] == 0 ) ) /* e não sabemos se pode ser movida */
               {
                  TAB_ContarPecas( tabuleiro , i + Dado1 + Dado2 , &qtd_dest , &cor_dest ) ;
                  if ( ( qtd_dest == 0 ) || ( cor_dest == vez ) )
                  {
                     podeMover[ i ] = 1 ;
                  } /* if */
               } /* if */
            }
         }
      }

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
*     pOpcoes - Vetor de opções do menu.
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

   static int Menu( tpOpcaoMenu * pOpcoes )
   {

      assert( pOpcoes != NULL ) ;

      printf( "\n" ) ;
      tpOpcaoMenu * pOp = pOpcoes ;
      while ( pOp->texto != NULL )
      {
         printf( "%c - %s\n" , pOp->tecla , pOp->texto ) ;
         pOp ++ ;
      } /* while */

      /* Garante que o usuário escolha uma opção válida */
      while ( 1 )
      {
         char t = 0 ;
         int indice = 0 ;

         printf( "Escolha uma opção: " ) ;
         scanf( "%c" , &t ) ;

         pOp = pOpcoes ;
         while ( pOp->texto != NULL )
         {
            if ( pOp->tecla == t )
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

   static void MenuNovaPartida( void )
   {
      static const tpOpcaoMenu opcoes[] = {
                  { "Jogar dados"      , JogarDados      , 'j' } ,
                  { "Carregar partida" , CarregarPartida , 'c' } ,
                  { "Sair"             , Sair            , 's' } ,
                  { NULL               , NULL            , 0   } } ;

      Menu( (tpOpcaoMenu *)opcoes ) ;

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

#if 0
      if ( BAR_Criar( &Bar[ DPO_Jogador1 ] ) != BAR_CondRetOK )
      {
         printf( "Erro ao criar a barra\n" ) ;
         Bar[ DPO_Jogador1 ] = NULL ;
         Sair( ) ;
      } /* if */

      if ( BAR_Criar( &Bar[ DPO_Jogador2 ] ) != BAR_CondRetOK )
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
#endif

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

#if 0
      if ( Bar[ DPO_Jogador1 ] != NULL )
      {
          BAR_Destruir( Bar[ DPO_Jogador1 ] ) ;
          Bar[ DPO_Jogador1 ] = NULL ;
      } /* if */

      if ( Bar[ DPO_Jogador2 ] != NULL )
      {
          BAR_Destruir( Bar[ DPO_Jogador2 ] ) ;
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
#endif

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

//      if ( TAB_Criar( &tabuleiro ) != TAB_CondRetOK )
//      {
//         printf( "Erro ao criar o tabuleiro\n" ) ;
//         return 1 ;
//      } /* if */

      NovaPartida( ) ;
//      SalvarPartida( ) ;
//      CarregarPartida( ) ;

      return 0 ;

   } /* Fim função: Main */


/********** Fim do módulo de implementação: Módulo jogo **********/

