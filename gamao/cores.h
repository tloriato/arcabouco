#if ! defined( CORES_ )
#define CORES_
/**********************************************************************
*
*  $MCD Módulo de definição: Módulo cores
*
*  Arquivo gerado:              cores.h
*  Letras identificadoras:      COR
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data       Observações
*       1.00  gbo, gapm, pa, tdn  26/10/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*       Módulo de definição das sequências de caracteres ANSI para trocar
*       a cor do texto no terminal.
*       Esse módulo não tem .c
*
***********************************************************************/

/* Comente essa definição para usar um terminal monocromático */
//#define USAR_CORES

#define FG_PRETO    "30"
#define FG_VERMELHO "31"
#define FG_VERDE    "32"
#define FG_AMARELO  "33"
#define FG_AZUL     "34"
#define FG_MAGENTA  "35"
#define FG_CIANO    "36"
#define FG_BRANCO   "37"

#define BG_PRETO    "40"
#define BG_VERMELHO "41"
#define BG_VERDE    "42"
#define BG_AMARELO  "43"
#define BG_AZUL     "44"
#define BG_MAGENTA  "45"
#define BG_CIANO    "46"
#define BG_BRANCO   "47"

#define ESC( x )    "\x1b[" x "m"

#ifdef USAR_CORES
   #define COR_BG1 ESC( BG_PRETO )
   #define COR_BG2 ESC( BG_VERMELHO )
   #define COR_LETRA_POS ESC( FG_VERDE )
   #define COR_MENSAGEM ESC( FG_VERDE )
   #define COR_PADRAO ESC( BG_PRETO ) ESC( FG_BRANCO )
#else
   #define COR_BG1 ""
   #define COR_BG2 ""
   #define COR_LETRA_POS ""
   #define COR_MENSAGEM ""
   #define COR_PADRAO ""
#endif

#else
#endif
