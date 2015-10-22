m=require("modulo")

-- param = {"Nome", "Tipo", "Descrição", Oculto do teste (default false)}

--func {'Nome da função',      'Descrição',                                                Retornos,  Parâmetros, Nome Teste}
func = {{"Imprimir tabuleiro", "Imprime o estado atual do tabuleiro em ASCII na tela."                     },
        {"Nova partida",       "Inicia uma nova partida de jogo."                                          },
        {"Salvar partida",     "Salva a partida atual em um arquivo."                                      },
        {"Carregar partida",   "Carrega a partida salva de um arquivo."                                    },
        {"Jogar dados",        "Joga os dados para determinar o número de movimentos do jogador"           },
        {"Mover peça",         "Move uma peça do jogador atual."                                           },
        {"Menu",               "Imprime o menu, aguarda a escolha da opção e chama a função correspondente"},
        {"Main",               "Ponto de entrada do programa."                                             }}

autores = {"Gabriel Barbosa de Oliveira",
           "Guilherme de Azevedo Pereira Marques",
           "Pedro Alvarez",
           "Thiago Duarte Naves"}

--criar_modulo(nome,   id,    testes, mult_instâncias, cond_ret, funcoes, autores, arq_code, arq_head, arq_test, arq_script)
m.criar_modulo("jogo", "JOG", false,  false,           nil,      func,    autores, "jogo.c", nil,      nil,      nil)
