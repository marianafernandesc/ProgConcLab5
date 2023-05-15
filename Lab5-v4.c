/*
Disciplina Programacao Concorrente
Professora: Silvana Rossetto
Estudante: Mariana Fernandes Cabral
DRE: 121060838
Laboratorio 5: Atividade 4
*/


#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define NTHREADS 5

int senta=0;
int ate=0;

//variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_senta;
pthread_cond_t cond_ate;


void *printOiMaria (void *arg) {
    int *id = (int *) arg;
    printf("Oi Maria!\n");
    // como a thread não precisa satisfazer nenhuma ordem de execução e nem faz acesso a nenhuma
    // variável global/compartilhada, não há necessidade do print ser executado dentro de um lock
    pthread_mutex_lock(&mutex);
   //printf("Thread %d executando\n", *id);
    senta++;
   // printf("Oi Maria!\n");
    if (senta == 2) {
   //pthread_cond_broadcast(&cond_senta); 
   //como só tem uma thread esperando pela condição da variável senta, basta signal
        pthread_cond_signal(&cond_senta);
    }
    pthread_mutex_unlock(&mutex);
}

void *printOiJose (void *arg) {
    int *id = (int *) arg;
    printf("Oi Jose!\n"); 
    // como a thread não precisa satisfazer nenhuma ordem de execução e nem faz acesso a nenhuma
    // variável global/compartilhada, não há necessidade do print ser executado dentro de um lock
    pthread_mutex_lock(&mutex);
//printf("Thread %d executando\n", *id);
    senta++;
// printf("Oi Jose!\n");
    if (senta == 2) {
        pthread_cond_broadcast(&cond_senta);
    }
    pthread_mutex_unlock(&mutex);
}

void *printSenta (void *arg) {
   int *id = (int *) arg;
//printf("Thread %d executando\n", *id);
   pthread_mutex_lock(&mutex);
   if(senta < 2) {
// printf("Thread %d bloqueou\n", *id);
     pthread_cond_wait(&cond_senta, &mutex);
// printf("Thread %d desbloqueou\n", *id);
   }
   printf("Sente-se por favor.\n");
   ate++;
   pthread_cond_broadcast(&cond_ate);
   pthread_mutex_unlock(&mutex);
}

void *printOAteJose (void *arg) {
   int *id = (int *) arg;
   pthread_mutex_lock(&mutex);
//printf("Thread %d executando\n", *id);
//while(ate == 0) {
   if(ate == 0) {
// uma vez que a condição se torna válida, ela será válida pelo resto do programa neste caso, então pode usar if

//printf("Thread %d bloqueou\n", *id);
     pthread_cond_wait(&cond_ate, &mutex);
//printf("Thread %d desbloqueou\n", *id);
   }
   printf("Ate mais Jose!\n");
   pthread_mutex_unlock(&mutex);
}

void *printAteMaria (void *arg) {
   int *id = (int *) arg;
   pthread_mutex_lock(&mutex);
//printf("Thread %d executando\n", *id);
//while(ate == 0) {
   if(ate == 0) { 
// uma vez que a condição se torna válida, ela será válida pelo resto do programa neste caso, então pode usar if
//printf("Thread %d bloqueou\n", *id);
     pthread_cond_wait(&cond_ate, &mutex);
//printf("Thread %d desbloqueou\n", *id);
   }
   printf("Ate mais Maria!\n");
   pthread_mutex_unlock(&mutex);
}

//funcao principal
int main(void) {
  //variaveis auxiliares
  int i;
 
  //identificadores das threads
  pthread_t tid[NTHREADS];
  int *id[NTHREADS];

  //aloca espaco para os IDs das threads
  for(i=0; i<NTHREADS;i++) {
    id[i] = malloc(sizeof(int));
    if(id[i] == NULL) exit(-1);
    *id[i] = i+1;
  }

  //inicializa as variaveis de sincronizacao
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_senta, NULL);
  pthread_cond_init(&cond_ate, NULL);

  //cria as threads
  pthread_create(&tid[0], NULL, printOiMaria, (void *) id[0]);
  pthread_create(&tid[1], NULL, printOiJose, (void *) id[1]);
  pthread_create(&tid[2], NULL, printSenta, (void *) id[2]);
  pthread_create(&tid[3], NULL, printAteMaria, (void *) id[3]);
  pthread_create(&tid[4], NULL, printOAteJose, (void *) id[4]);

  for (i = 0; i < NTHREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond_ate);
  pthread_cond_destroy(&cond_senta);

  return 1;
}