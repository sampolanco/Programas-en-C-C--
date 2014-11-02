//Ejecutar con N productores, M consumidores
#include <pthread.h>//Libreria para hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define TRUE 1
#define FALSE 0
#define cantidad 5 //cantidad de productores y consumidores
#define largo 10 //Tamaño del buffer

int buffer[largo];
int imprimir=0;//Hasta donde se va a imprimir

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condProd=PTHREAD_COND_INITIALIZER;
pthread_cond_t condCons=PTHREAD_COND_INITIALIZER;

void *codigo_productor(void *_id); 
void *codigo_consumidor(void *_id);

void imprimir_vector();
void producir(int);
void consumir(int);

//--------------------------------------------------------------------------------main
int main(){
  int i;
  pthread_t hilo_productor[cantidad];//Procesos Productores
  pthread_t hilo_consumidor[cantidad];//Procesos Consumidores
 
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
		pthread_mutex_lock(&mutex);
		while(imprimir==largo){pthread_cond_wait(&condProd,&mutex);}//Se duerme hasta que liberan
		
		producir(id);
		pthread_cond_signal(&condCons);
		pthread_mutex_unlock(&mutex);
		//sleep(1);
	}//while	
	pthread_exit(&id);
}
//----------------------------------------------------------------------------------consumidor
void *codigo_consumidor(void *_id){ 
	int id = *(int *)_id;       usleep(1000-100*id);
	while(1){
		pthread_mutex_lock(&mutex);
		while(imprimir==0){pthread_cond_wait(&condCons,&mutex);}//Se duerme hasta que liberan

		consumir(id);
		pthread_cond_signal(&condProd);
		pthread_mutex_unlock(&mutex);
		//sleep(1);	
		}
	pthread_exit(&id);
}
//--------------------------------------------------------------------------------------producir
void producir(int id){
	printf("Productor con id: %d\n",id);
	buffer[imprimir]=id;
	imprimir++;
	imprimir_vector();
			}
//--------------------------------------------------------------------------------------consumir
void consumir(int id){
	printf("Consumidor con id %d\n consumio: %d",id,buffer[imprimir]);
	buffer[imprimir]=0;
	imprimir--;
	imprimir_vector();
			}

