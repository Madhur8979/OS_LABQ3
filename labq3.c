#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void *function1() ; 
void *function2() ; 
void *function3() ; 
pthread_mutex_t mutex1 ;  
pthread_mutex_t mutex2 ; 
pthread_mutex_t mutex3 ;  

int main()
{
pthread_mutex_init ( &mutex1  , NULL  ) ; 
pthread_mutex_init ( &mutex2  ,NULL  ) ; 
pthread_mutex_init ( &mutex3  , NULL  ) ;  
pthread_t one, two, three ; 
pthread_create (&one,   NULL, function1, NULL) ; 
pthread_create (&two,   NULL, function2, NULL) ; 
pthread_create (&three, NULL, function3, NULL) ; 
printf("							   DEADLOCK CREATION\n");
pthread_join (one ,  NULL) ;
	pthread_join (two ,  NULL) ;
	pthread_join (three ,NULL) ;

	printf("Thread joined\n");
}

void *function1() 
{
pthread_mutex_lock(&mutex1);
printf("							Thread 1 acquired mutex1\n");
pthread_mutex_lock(&mutex2); 
printf("							Thread 1 acquired mutex2\n");
sleep(1);
pthread_mutex_lock(&mutex3); 
printf("							Thread 1 acquired mutex3\n");
pthread_mutex_unlock(&mutex3); 
printf("							Thread 1 released mutex3\n");
pthread_mutex_unlock(&mutex2); 
printf("							Thread 1 released mutex2\n");
pthread_mutex_unlock(&mutex1); 
printf("							Thread 1 released mutex1\n");
		
}

void *function2() 
{
pthread_mutex_lock(&mutex2);
printf("							Thread 2 acquired mutex2\n");
pthread_mutex_lock(&mutex3);
printf("							Thread 2 acquired mutex3\n"); 
sleep(1);
pthread_mutex_lock(&mutex1);
printf("							Thread 2 acquired mutex1\n"); 
pthread_mutex_unlock(&mutex1); 
printf("							Thread 2 released mutex1\n");
pthread_mutex_unlock(&mutex3);
printf("							Thread 2 acquired mutex3\n"); 
pthread_mutex_unlock(&mutex2); 
printf("							Thread 2 released mutex2\n");
}

void *function3() 
{
pthread_mutex_lock (&mutex3);
printf("							Thread 3 acquired mutex3\n");
pthread_mutex_lock (&mutex1);
printf("							Thread 3 acquired mutex1\n"); 
sleep(1);
pthread_mutex_lock (&mutex2);
printf("							Thread 3 acquired mutex2\n"); 
pthread_mutex_unlock(&mutex2); 
printf("							Thread 3 released second_mutex\n");
pthread_mutex_unlock(&mutex1); 
printf("							Thread 3 released mutex1\n");
pthread_mutex_unlock(&mutex3); 
printf("							Thread 3 released mutex3\n");


}
