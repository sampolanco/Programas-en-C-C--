//Ejecutar con N productores, M consumidores
#include <pthread.h>//Libreria para hilos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int n=10;//productores
int m=10;//consumidores
int buffer[3][3];
int bandera=1,banderaprod=1,banderacons=1;

void *codigo_productor(void *_id); 
void *codigo_consumidor(void *_id); 
int aleatorio();
void llenar_buffer(int);
void imprimir_matriz(int [3][3]);

int main(){

  pthread_t hilo_productor[n];
  pthread_t hilo_consumidor[m];
  int idp[10]={1,2,3,4,5,6,7,8,9,10};
  int idc[10]={1,2,3,4,5,6,7,8,9,10};
  int error;
  int *salida;
  int i;
  llenar_buffer(0);
                           printf("Programa de productor-consumidor\n");

		//creando productor 1,2,3
		for(i=0;i<n;i++){
		error = pthread_create(&hilo_productor[i],NULL,codigo_productor,&idp[i]);//crear productor
		if(error){
		  fprintf(stderr,"Error %d: %s\n",error, strerror(error));
		  exit(-1);
		        }
				}//fin del for
		
		//creando consumidor 1,2,3
		for(i=0;i<m;i++){
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
//--------------------------------------------------------------------------------funcionesint aleatorio(){
int generar_aleatorio(){
int numero=rand()%10+1;
return numero;
		}
//--------------------------------------------------------------------------------Imp buffer
void imprimir_matriz(int matriz[3][3]){
int i,j;
printf("\n");
for(i=0;i<3;i++){
	for(j=0;j<3;j++){
	printf("%d->",matriz[i][j]);
			}
printf("\n");
		}
printf("\n\n");
			}
//--------------------------------------------------------------------------------llenar matriz
void llenar_buffer(int numero){
int i,j;
for(i=0;i<3;i++){
	for(j=0;j<3;j++){
	buffer[i][j]=numero;
			}
		}
			}
//-------------------------------------------------------------------------------productor
void *codigo_productor(void *_id){
	int e;
	int id = *(int *)_id;
	int aleatorio;
	usleep(1000-100*id);
	while(1){
	if(!bandera)banderaprod=id;
	if(bandera){
	if(id==banderaprod){
	printf("Productor %d Produciendo\n",id);
	llenar_buffer(id);
	printf("Buffer multiplicado por el id:\n");
	imprimir_matriz(buffer);
	aleatorio=generar_aleatorio();
	printf("Numero aleatorio:%d\n Buffer multiplicado por el aleatorio:\n",aleatorio);
	llenar_buffer(id*aleatorio);
	imprimir_matriz(buffer);
         bandera=0;
		   }
		    }//bandera
usleep(1000);
		}//while
	pthread_exit(&id);
}
//----------------------------------------------------------------------------------consumidor
void *codigo_consumidor(void *_id){
	int e,i,j;
	int id = *(int *)_id;
	int tmp[3][3];
	usleep(1000-100*id);
	while(1){
	if(bandera)banderacons=id;
	if(!bandera){
	if(id==banderacons){
	printf("Consumidor %d Consumiendo\n",id);
for(i=0;i<3;i++){
	for(j=0;j<3;j++){
		tmp[i][j]=buffer[i][j];
		}	}
		printf("Matriz temporal:\n");
		imprimir_matriz(tmp);
		llenar_buffer(0);
		printf("Buffer con ceros:\n");
		imprimir_matriz(buffer);
bandera=1;
		   }
		    }//bandera
usleep(1000);
		}//while
	pthread_exit(&id);
}
