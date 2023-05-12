# ProgConcLab5

Algumas melhorias foram feitas após a análise da primeira versão da atividade 4 do Laboratório 5,
que era o programa Lab5.c. Para começar, acrescentei if nas funções printOiJose e printOiMaria,
que testavam se a variável estado era igual a 2 para então liberar a thread printSenta, que só
executa quando x = 2. Na primeira versão, não havia essa avaliação de condição e era simplesmente
feito o broadcast mesmo sem estar com x = 2. O programa funcionava porque tem um while que avalia
novamente a condição após a thread que executa printSenta desbloquear, bloqueando de novo se x fosse
menor que 2, mas é um processamento a mais desnecessário.

Outra mudança foi retirar o pthread_cond_broadcast nas funções printAteJose e printAteMaria, que
simplesmente não tem finalidade alguma, já que não há mais nenhuma thread que dependa da variável
estado neste ponto do código a partir do momento em que a função printSenta incrementa e libera
printAteMaria e printAteJose.
