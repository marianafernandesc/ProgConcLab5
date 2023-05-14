# ProgConcLab5

Algumas melhorias foram feitas após a análise da primeira versão da atividade 4 do Laboratório 5,
que era o programa Lab5.c. Para começar, acrescentei if nas funções printOiJose e printOiMaria,
que testam se a variável estado é igual a 2 para então liberar a thread printSenta, que só
executa quando x = 2. Na primeira versão, não havia essa avaliação de condição e era simplesmente
feito o pthread_cond_broadcast mesmo sem estar com x = 2. O programa funcionava porque tem um while 
que avalia novamente a condição após a thread que executa printSenta desbloquear, bloqueando de novo 
se x fosse menor que 2, mas é um processamento a mais desnecessário.

Outra mudança foi retirar o pthread_cond_broadcast nas funções printAteJose e printAteMaria, que
simplesmente não tem finalidade alguma, já que não há mais nenhuma thread que dependa da variável
estado neste ponto do código a partir do momento em que a função printSenta incrementa e libera
as threads que executam printAteMaria e printAteJose.

Além disso, mudei a ordem das instruções pthread_cond_broadcast e pthread_mutex_unlock. Na primeira
versão, primeiramente se executava o unlock e depois o broadcast e na nova versão foi feita uma 
inversão dessa ordem. Não testei para ver qual tipo de erro a primeira versão geraria, mas como 
x_cond é uma variável global e compartilhada entre as threads, imagino que poderia gerar algum erro.

Na versão 3 (Lab5-v3.c), retirei o pthread_exit(NULL) no final e adicionei a função join na 
main, para fazer a main esperar as threads executarem, além de usar pthread_mutex_destroy e 
pthread_cond_destroy para destruir as variáveis de lock e condição. O tid, que eu percebi que 
usei com 0 em todas as threads no pthread_create, foi consertado. Por fim, em vez de usar a 
variável estado, optei por usar duas variáveis de condição, uma que avalia quando os prints 
"Oi Maria" e "Oi Jose" foram feitos, que são condição lógica para a função printSenta executar, 
e outra que avalia se o print "Sente-se por favor" foi feito, que é condição lógica para as 
funções printAteMaria e printAteJose executarem.
