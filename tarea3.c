#include <stdio.h>
#include <stdlib.h>
void imprimir(int pid, int id){
	printf("Proceso numero:%d, Padre:%d, identificador:%d \n",getpid(),getppid(),id);
				}

int main(){
	//proceso 1
	int pid=getpid(),pid2=getpid();
	imprimir(pid,1);//Proceso numero 1

	if(pid2>0){//Si es 1
	pid2=fork();//crear a 3
		//proceso3
		if(pid2==0){//Si es 3
		imprimir(pid2,3);
		sleep(1);//dormir a 3
		                            //----Reanudacion despues de terminar a 2---//
		
		pid2=fork();//Crear a 6
			if(pid2==0){
			imprimir(pid2,6);
			sleep(7);//Dormir a 6
//--
pid2=fork();//Crear a 8
			if(pid2==0){//Si es 8
			imprimir(pid2,8);
			pid2=fork();//Crear a 9
				if(pid2==0){//Si es 9
				imprimir(pid2,9);
				exit(0);//Salir de 9
			                   }
			sleep(1);
			exit(0);//Salir de 8
				  }
 			sleep(1);//Dormir a 6
			exit(0);//Salir de 6
//--
				  }
		sleep(3);//Dormir a 3
		//exit(0);//Salir de 3
	
		pid2=fork();//Crear 5
			//proceso5
			if(pid2==0){//Si es 5
			imprimir(pid2,5);
			exit(0);//Salir de 5
				  }
		sleep(6);//Dormir a 3 en lo que pasan los demas
		exit(0);//Salir de 3
			 }//fin de si es 3
	
	sleep(1);//dormir a 1

	pid2=fork();//crear a 2
		if(pid2==0){//Si es 2
		imprimir(pid2,2);
		exit(0); //Salir de 2
			  }//fin de si es 2
	sleep(2);//Dormir a 1


	pid2=fork();//crear a 4
		if(pid2==0){//Si es 4
		imprimir(pid2,4);
		sleep(1);
		if(pid2==0){//Si es 4
		
		pid2=fork();//Crear a 7
		sleep(2);
			if(pid2==0){//Si es 7
			imprimir(pid2,7);
			exit(0);//Salir de 7
				   }
			  }
		exit(0);//Salir de 4
			  }//fin de si es 4
	sleep(5);
	exit(0);
		 }//fin de si es 1
	  }//fin del main
		


