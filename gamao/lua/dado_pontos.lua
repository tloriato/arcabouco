m=require("modulo")

-- Códigos de retorno possíveis para o arcabouço
--ret= {{"Nome", 'Descrição'}}
ret = {{"OK", "Rodou sem erros"},
       {"MaxPontos", "Valor da partida já atingiu o máximo"}}


-- param = {"Nome", "Tipo", "Descrição", Oculto do teste (default false)}
pDobrar = {{"jogador", "DPO_tpJogador", "Jogador"},
           {"res", "int *", "Resposta: 1 se o jogador pode dobrar. 0 caso contrário\nEsse parâmetro é passado por referência"}}

pObterPontos = {{"pontos", "int *", "Retorno do valor da partida\nEsse parâmetro é passado por referência"}}

--func {'Nome da função',   'Descrição',                Retornos,      Parâmetros, Nome Teste}
fDobrar = {"Dobrar pontos", "Dobra o valor da partida", {"OK", "MaxPontos"}, {}, "dobrar"}

fPodeDobrar = {"Pode dobrar", "Verifica se o jogador pode dobrar a pontuação da partida", {"OK"}, pDobrar, "podedobrar"}

fObterPontos = {"Obter pontos", "Obtém o valor atual da partida", {"OK"}, pObterPontos, "obterpontos"}

funcs = {fDobrar, fPodeDobrar, fObterPontos}

autores = {"Gabriel Barbosa de Oliveira", "Guilherme de Azevedo Pereira Marques", "Thiago Duarte Naves"}

--criar_modulo(nome,          id,    testes, mult_instâncias, cond_ret, funcoes,  autores, arq_code,          arq_head,          arq_test,            arq_script)
m.criar_modulo("dado pontos", "DPO", true,   false,           ret,      funcs,    autores, "dado_pontos.c",   "dado_pontos.h",   "testdado_pontos.c", "TesteDadoPontos.script")
