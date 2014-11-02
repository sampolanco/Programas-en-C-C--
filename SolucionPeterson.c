#include <pthread.h>//Libreria para hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define TRUE 1
#define FALSE 0
#define N 2

int P = 5;
int contador=0;
int buffer[5]={0,0,0,0,0};
int bandera=1;

void *codigo_productor(void *_id); 
void *codigo_consumidor(void *_id); 
int aleatorio();
int turno;
int interesado[N];

void entrar_region(int);
void salir_region(int);

int main(){
  int h;
  pthread_t hilo[2];
  pthread_t th;
  int id[2]={1,2};
  int error;
  int *salida;
  int i;
                           printf("Programa de productor-consumidor\n");

		//creando productor
		error = pthread_create(&hilo[1],NULL,codigo_productor,&id[0]);//crear productor
		if(error){
		  fprintf(stderr,"Error %d: %s\n",error, strerror(error));
		  exit(-1);
		        }
		//creando consumidor
		error = pthread_create(&hilo[2],NULL,codigo_consumidor,&id[1]);//crear consumidor
		if(error){
		  fprintf(stderr,"Error %d: %s\n",error, strerror(error));
		  exit(-1);
		        }

 //esperar a hilo, no avanza de aqui hasta que termine el productor
    error = pthread_join(hilo[1],(void **)&salida);
    if(error)
      fprintf(stderr,"Error %d: %s\n",error,strerror(error));
    else{
      printf("Hilo %d terminado,%d\n",*salida,id[1-1]);
       }

	return 0;
}
//--------------------------------------------------------------------------------funciones
int aleatorio(){
int numero=rand(),10+1;
return numero;
		}
//-------------------------------------------------------------------------------productor
void *codigo_productor(void *_id){
	int e;
	int id = *(int *)_id;
	while(1){

		entrar_region(id);
		if(contador<5){
				e=aleatorio();
				buffer[contador]=e;
				printf("Se producio el dato,%d\n",e);
				contador++;
				}//contador
		salir_region(id);
		}//while
	pthread_exit(&id);
}
//----------------------------------------------------------------------------------consumidor
void *codigo_consumidor(void *_id){
	int e;
	int id = *(int *)_id;
	while(1){
		entrar_region(id);
		if(contador>0){
				e=buffer[contador-1];
				contador--;
				  printf("Se consumio el dato,%d\n",e);
				}//contador
		salir_region(id);
		}
	pthread_exit(&id);}
//----------------------------------------------------------------------------------------------
void entrar_region(int proceso){
	int otro;
	otro=1-proceso;
	interesado[proceso]=TRUE;
	turno=proceso;
	while(turno==proceso && interesado[otro]==TRUE){}
				}

void salir_region(int proceso){
	interesado[proceso]=FALSE;
				}

