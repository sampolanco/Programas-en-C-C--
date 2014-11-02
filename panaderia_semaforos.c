//Ejecutar con N productores, N consumidores
#include <pthread.h>//Libreria para hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>
#define TRUE 1
#define FALSE 0
#define cantidad 5 //cantidad de productores y consumidores
#define largo 10 //Tamaño del buffer

int buffer[largo];
int imprimir=0;//Hasta donde se va a imprimir
sem_t semaforo_prod,semaforo_cons,candado;

void *codigo_productor(void *_id); 
void *codigo_consumidor(void *_id);

void imprimir_vector();


//--------------------------------------------------------------------------------main
int main(){
  int i;
  pthread_t hilo_productor[cantidad];//Procesos Productores
  pthread_t hilo_consumidor[cantidad];//Procesos Consumidores
  sem_init(&semaforo_prod,0,largo);//Se puede producir de inmediato
  sem_init(&semaforo_cons,0,0);//No se puede consumir en un principio
  sem_init(&candado,0,1);//Candado para que solo un procesos se este ejecutando
  int idp[cantidad];
  int idc[cantidad];
  int error;
  int *salida;
		for(i=0;i<cantidad;i++){
			idp[i]=i;
			idc[i]=i+10;
					}

		//creando productor 1,2,3...cantidad
		for(i=0;i<cantidad;i++){
		error = pthread_create(&hilo_productor[i],NULL,codigo_productor,&idp[i]);//crear productor
		if(error){
		  fprintf(stderr,"Error %d: %s\n",error, strerror(error));
		  exit(-1);
		        }
				}//fin del for
		
		//creando consumidor 1,2,3..cantidad
		for(i=0;i<cantidad;i++){
		error = pthread_create(&hilo_consumidor[i],NULL,codigo_consumidor,&idc[i]);//crear consumidor
		if(error){
		  fprintf(stderr,"Error %d: %s\n",error, strerror(error));
		  exit(-1);
		        }
				}//fin del for

 	//esperar a hilo, no avanza de aqui hasta que termine el productor
    error = pthread_join(hilo_productor[1],(void **)&salida);
    if(error)
      fprintf(stderr,"Error %d: %s\n",error,strerror(error));
    else{
      printf("Hilo %d terminado,%d\n",*salida,idp[1-1]);
       }

	return 0;
}
//--------------------------------------------------------------------------------Imp buffer
void imprimir_vector(){
int i;
printf("\n");
for(i=0;i<imprimir;i++){printf("%d->",buffer[i]);}
printf("\n\n");
				   }
//-------------------------------------------------------------------------------productor
void *codigo_productor(void *_id){
	int id = *(int *)_id;
	usleep(1000-100*id);
while(1){
		sem_wait(&candado);
		if(sem_trywait(&semaforo_prod)!=0){sem_post(&candado);}
		else{
				sem_post(&semaforo_cons);
				printf("Productor con id: %d\n",id);
				buffer[imprimir]=id;
				imprimir++;
				imprimir_vector();
		sem_post(&candado);
		    }
	}//while	
	pthread_exit(&id);
}
//----------------------------------------------------------------------------------consumidor
void *codigo_consumidor(void *_id){ 
	int id = *(int *)_id;       usleep(1000-100*id);
	while(1){
		sem_wait(&candado);
		if(sem_trywait(&semaforo_cons)!=0){sem_post(&candado);}
		else{
				sem_post(&semaforo_prod);
				printf("Consumidor con id %d\n consumio: %d",id,buffer[imprimir]);
				buffer[imprimir]=0;
				imprimir--;
				imprimir_vector();
		sem_post(&candado);
		    }
		}
	pthread_exit(&id);
}

