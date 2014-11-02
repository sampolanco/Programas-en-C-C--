//Ejecutar con N productores, M consumidores
#include <pthread.h>//Libreria para hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define TRUE 1
#define FALSE 0
#define cantidad 5 //cantidad de productores y consumidores
#define largo 10 

int buffer[largo];
int escogiendo[cantidad];
int numero[cantidad];
int bandera=1;

void *codigo_productor(void *_id); 
void *codigo_consumidor(void *_id);
int elegir_maximo();
void entrar_region(int);
void salir_region(int);
int verificar_id(int,int);
void llenar_buffer(int);
void imprimir();

//---------------------------------------
int main(){
  int i;
  pthread_t hilo_productor[cantidad];
  pthread_t hilo_consumidor[cantidad];
  int idp[cantidad];
  int idc[cantidad];
  int error;
  int *salida;
		for(i=0;i<cantidad;i++){
			idp[i]=i;
			idc[i]=i;
			escogiendo[i]=FALSE;
			numero[i]=0;
					}
  
  		llenar_buffer(0);
                           printf("Algoritmo de peterson para N procesos\n");

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
void imprimir(){
int i;
printf("\n");
for(i=0;i<largo;i++){printf("%d->",buffer[i]);}
printf("\n\n");
				   }
//--------------------------------------------------------------------------------llenar buffer
void llenar_buffer(int numero){
int i;
for(i=0;i<largo;i++){buffer[i]=numero;}
			      }
//-------------------------------------------------------------------------------productor
void *codigo_productor(void *_id){
	int id = *(int *)_id;
	usleep(1000-100*id);
while(1){
	
		entrar_region(id);
				printf("Productor %d esta poduciendo los datos\n",id);
				llenar_buffer(id);
				imprimir();
		salir_region(id);

usleep(10000);}
	}//while	
	pthread_exit(&id);
}
//----------------------------------------------------------------------------------consumidor
void *codigo_consumidor(void *_id){ 
	int id = *(int *)_id;     
        usleep(1000-100*id);
	while(1){

		entrar_region(id);
				  printf("Consumidor %d esta consumiendo los datos\n",id);
				  llenar_buffer(0);
				  imprimir();
		salir_region(id);
usleep(10000);
		}}
	pthread_exit(&id);
}
//---------------------------------------------------------------------------------peterson
void entrar_region(int id){
	int k=0;
	escogiendo[id]=TRUE;
	numero[id]=elegir_maximo();
	escogiendo[id]=FALSE;
	for(k=0;k<cantidad;k++){//El valor de k aumenta, por cada proceso;
		while(escogiendo[k]);//Se detiene si el proceso no ha tomado turno
		while(verificar_id(id,k));//Se detiene si el proceso tiene un tuno meno al procesok
			    }	
			}
//---------------------------------------------------------------------------------
void salir_region(int id){
	numero[id]=0;
				}
//-----------------------------------------------------------------------------------
int elegir_maximo(){
	int i,maximo=0;
	for(i=0;i<cantidad;i++){
		if(maximo<numero[i]){maximo=numero[i];}
			    }
	return maximo+1;
		  }
//------------------------------------------------------------------------------------
int verificar_id(int id, int k){
	if(numero[k]!=0){
		if(numero[k]<numero[id]){return 1;}
		if (numero[k]==numero[id] && k<id){return 1;}
			}
	return 0;
				}
//--------------------------------------------------------------------------------
