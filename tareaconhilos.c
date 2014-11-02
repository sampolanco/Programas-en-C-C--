#include <pthread.h>//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int contador = 1;

void *codigo_hilo(void *_id); 
void *codigo_hilo3(void *_id);
void *codigo_hilo4(void *_id);
void *codigo_hilo6(void *_id);
void *codigo_hilo8(void *_id);
void *codigo_hilo9(void *_id);

int main(){
  int h;
  pthread_t hilo[5];
  pthread_t th;
	int id[5]={1,2,3,4,5,6,7,8,9};
  int error;
  int *salida;
	int i;

		//creando hilo 3
		error = pthread_create(&hilo[3],NULL,codigo_hilo3,&id[3]);
		if(error){
		  fprintf(stderr,"Error %d: %s\n",error, strerror(error));
		  exit(-1);
		}
	


	for(i=1;i<=9;i++){
    error = pthread_join(hilo[i],(void **)&salida);
    if(error)
      fprintf(stderr,"Error %d: %s\n",error,strerror(error));
    else
      printf("Hilo %d terminado\n",*salida);
	}
	
	
	
	return 0;
}




void *codigo_hilo(void *_id){
	int i;
	int id = *(int *)_id;
	for(i=1;i<=100;i++){
		printf("Hilo %d  contador: %d  i:%d\n",id,contador,i);
		contador++;
	}
	pthread_exit(&id);
}

void *codigo_hilo3(void *_id){
	int i;
	int id = *(int *)_id;
	for(i=1;i<=100;i++){
		printf("Hilo %d  contador: %d  i:%d\n",id,contador,i);
		contador++;
	}
	pthread_exit(&id);
}

void *codigo_hilo4(void *_id){
	int i;
	int id = *(int *)_id;
	for(i=1;i<=100;i++){
		printf("Hilo %d  contador: %d  i:%d\n",id,contador,i);
		contador++;
	}
	pthread_exit(&id);
}

void *codigo_hilo6(void *_id){
	int i;
	int id = *(int *)_id;
	for(i=1;i<=100;i++){
		printf("Hilo %d  contador: %d  i:%d\n",id,contador,i);
		contador++;
	}
	pthread_exit(&id);
}

void *codigo_hilo8(void *_id){
	int i;
	int id = *(int *)_id;
	for(i=1;i<=100;i++){
		printf("Hilo %d  contador: %d  i:%d\n",id,contador,i);
		contador++;
	}
	pthread_exit(&id);
}

void *codigo_hilo9(void *_id){
	int i;
	int id = *(int *)_id;
	for(i=1;i<=100;i++){
		printf("Hilo %d  contador: %d  i:%d\n",id,contador,i);
		contador++;
	}
	pthread_exit(&id);
}

