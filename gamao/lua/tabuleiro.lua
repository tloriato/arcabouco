m=require("modulo")

-- Códigos de retorno possíveis para o arcabouço
--ret= {{"Nome", 'Descrição'}}
ret = {{"OK", "Rodou sem erros"},
       {"PosInvalida", "Não existe a posição solicitada"},
       {"PosVazia", "Não é possível mover uma peça de uma posição vazia"},
       {"FaltaMemoria", "Erro ao alocar memória"}
      }

-- param = {"Nome", "Tipo", "Descrição", Oculto do teste (default false)}
pTab = {"tabuleiro", "TAB_tppTabuleiro", "Tabuleiro a ser operado", true}

pCriar = {{"pTabuleiro", "TAB_tppTabuleiro *", "Parâmetro de retorno do tabuleiro criado.\nEsse parâmetro é passado por referência", true}}

pDestruir = {{"tabuleiro", "TAB_tppTabuleiro", "Tabuleiro a ser destruído", true}}

pIncPeca = {pTab,
            {"posicao", "unsigned int", "Posição do tabuleiro aonde será incluída a peça"},
            {"peca", "PEC_tppPeca", "Peça a ser incluída"}
           }

pMoverPeca = {pTab,
              {"de", "unsigned int", "Posição de origem da peça"},
              {"para", "unsigned int", "Posição de destino da peça"}
             }

pRemPeca = {pTab,
               {"posicao", "unsigned int", "Posição da peça"},
               {"peca", "PEC_tppPeca *",  "Parâmetro para retorno da peça removida\nEsse parâmetro é passado por referência"}
              }


--func {'Nome da função',    'Descrição',               Retornos,     Parâmetros, Nome Teste}
fCriar = {"Criar", "Cria um tabuleiro vazio", {"OK", "FaltaMemoria"}, pCriar,     "criar"}

fDestruir = {"Destruir", "Destroi o tabuleiro e as peças nele contidas", {"OK"}, pDestruir, "destruir"}

fIncPeca = {"Incluir peça", "Inclui uma peça na posição desejada", {"OK", "PosInvalida"}, pIncPeca, "incluir"}

fMoverPeca = {"Mover peça", "Move uma peça de uma posição para outra", {"OK", "PosInvalida", "PosVazia"}, pMoverPeca, "mover"}

fRemoverPeca = {"Remover peça", "Remove uma peça da posição indicada e a retorna no parâmetro peça.", {"OK", "PosInvalida", "PosVazia"}, pRemPeca, "remover"}


funcs = {fCriar, fDestruir, fIncPeca, fMoverPeca, fRemoverPeca}

autores = {"Gabriel Barbosa de Oliveira", "Guilherme de Azevedo Pereira Marques", "Thiago Duarte Naves"}

--criar_modulo(nome,        id,    testes, mult_instâncias, cond_ret, funcoes, autores, arq_code,        arq_head,        arq_test,          arq_script)
m.criar_modulo("tabuleiro", "TAB", true,   true,            ret,      funcs,   autores, "tabuleiro.c",   "tabuleiro.h",   "testtabuleiro.c", "TesteTabuleiro.script")

