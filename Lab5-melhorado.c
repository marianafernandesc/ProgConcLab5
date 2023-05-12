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

int estado=0;

//variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_estado;

void *printOiMaria (void *arg) {
    int *id = (int *) arg;
    pthread_mutex_lock(&mutex);
   //printf("Thread %d executando\n", *id);
   //if(estado <= 2) { // notei que o if nao e necessario nas funcoes printOiMaria e printOiJose
    estado++;
    printf("Oi Maria!\n");
    if (estado == 2) {
        pthread_cond_broadcast(&cond_estado);
    }
    pthread_mutex_unlock(&mutex);
}

void *printOiJose (void *arg) {
    int *id = (int *) arg;
    pthread_mutex_lock(&mutex);
   //printf("Thread %d executando\n", *id);
   //if(estado <= 2) {
    estado++;
    printf("Oi Jose!\n");
    if (estado == 2) {
        pthread_cond_broadcast(&cond_estado);
    }
    pthread_mutex_unlock(&mutex);
}

void *printSenta (void *arg) {
   int *id = (int *) arg;
// printf("Thread %d executando\n", *id);
   pthread_mutex_lock(&mutex);
   while(estado < 2) {
// printf("Thread %d bloqueou\n", *id);
     pthread_cond_wait(&cond_estado, &mutex);
// printf("Thread %d desbloqueou\n", *id);
   }
   printf("Sente-se por favor.\n");
   estado++;
   pthread_cond_broadcast(&cond_estado);
   pthread_mutex_unlock(&mutex);
}

void *printOAteJose (void *arg) {
   int *id = (int *) arg;
   pthread_mutex_lock(&mutex);
// printf("Thread %d executando\n", *id);
   while(estado <= 2) {
// printf("Thread %d bloqueou\n", *id);
     pthread_cond_wait(&cond_estado, &mutex);
// printf("Thread %d desbloqueou\n", *id);
   }
   printf("Ate mais Jose!\n");
   pthread_mutex_unlock(&mutex);
}

void *printAteMaria (void *arg) {
   int *id = (int *) arg;
   pthread_mutex_lock(&mutex);
// printf("Thread %d executando\n", *id);
   while(estado <= 2) {
// printf("Thread %d bloqueou\n", *id);
     pthread_cond_wait(&cond_estado, &mutex);
// printf("Thread %d desbloqueou\n", *id);
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
  pthread_cond_init(&cond_estado, NULL);

  //cria as threads
  pthread_create(&tid[0], NULL, printOiMaria, (void *) id[0]);
  pthread_create(&tid[0], NULL, printOiJose, (void *) id[1]);
  pthread_create(&tid[0], NULL, printSenta, (void *) id[2]);
  pthread_create(&tid[0], NULL, printAteMaria, (void *) id[3]);
  pthread_create(&tid[0], NULL, printOAteJose, (void *) id[4]);


  pthread_exit(NULL);
  return 1;
}