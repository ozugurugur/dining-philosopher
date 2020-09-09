#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>         											//to use exit(1)
#include <unistd.h>														//to sleep threads

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define THINKING 1
#define EATING 2

#define LEFTFORK i
#define RIGHTFORK (i+1) % 5
//#define LEFT (i-1) % 5
//#define RIGHT (i+1) % 5

int state[5];															//philospher state
pthread_mutex_t forks[5];

																		
void *runner(void *param);												//threads call this function


void printError(int i){
	printf("Error creating thread%d",i);
	exit(1);
}




void think(int i){
	state[i]=THINKING;
	sleep((rand()%3)+1);

}



void pick_up(int i){
	pthread_mutex_lock(&forks[i]);										//locks the chosen fork so other threads have to wait

	
}

void eat(int i){
	state[i]=EATING;
	printf("Philosopher%d is eating rn\n",i);
	sleep((rand()%3)+1);
	printf("Philosopher%d finished his meal and starts thinking again\n",i);
	
	
	
		
}

void put_down(int i){

	pthread_mutex_unlock(&forks[i]);
	
	
}

void philosopher(int i){
	
																
	while(1){
		think(i);
		pick_up(MIN(LEFTFORK,RIGHTFORK));
		pick_up(MAX(LEFTFORK,RIGHTFORK));														
		eat(i);
		put_down(LEFTFORK);
		put_down(RIGHTFORK);
	}																	
		
}

int main(){
	int phil=0;
	int phil1=1;
	int phil2=2;
	int phil3=3;
	int phil4=4;
	int i;
	for (i = 0; i < 5; i++)
    pthread_mutex_init (&forks[i], NULL);
	
	pthread_t t;
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;

	if(pthread_create( &t , NULL, runner,  &phil)!=0)
		printError(0);
	
	if(pthread_create( &t1, NULL, runner, &phil1)!=0)
		printError(1);
	
	if(pthread_create( &t2, NULL, runner, &phil2)!=0)
		printError(2);
	
	if(pthread_create( &t3, NULL, runner, &phil3)!=0)
		printError(3);
	
	if(pthread_create( &t4, NULL, runner, &phil4)!=0)
		printError(4);
	
	pthread_join(t, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	return 0;
}

void *runner(void *param){												//threads execute this function
	int *x_ptr= (int *)param;
	
	printf("Philosopher%d joined the table\n",*x_ptr);
	
	
	philosopher(*x_ptr);
	
	
	
	pthread_exit(0);
}
