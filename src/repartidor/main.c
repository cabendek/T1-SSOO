#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../file_manager/manager.h"

int semaforo_cruzado = 0;
int contador_tiempos[4] = {0, 0, 0, 0};
int tiempo = 0;
int posicion_actual = 0;

void luz_semaforo(int sig, siginfo_t *siginfo, void *context){
  int number_received = siginfo->si_value.sival_int;
  if (number_received == 1) {// En verde
    posicion_actual += 1;
    contador_tiempos[semaforo_cruzado] = tiempo;
    semaforo_cruzado += 1;
  }
};

int main(int argc, char const *argv[]){

  printf("I'm the REPARTIDOR process and my PID is: %i ---------------------------------------\n", getpid());

  int distancia_semaforo1 = atoi(argv[0]);
  int distancia_semaforo2 = atoi(argv[1]);
  int distancia_semaforo3 = atoi(argv[2]);
  int distancia_bodega = atoi(argv[3]);

  // Validando valores de variables
  // printf("distancia_semaforo1: %d\n", distancia_semaforo1);
  // printf("distancia_semaforo2: %d\n", distancia_semaforo2);
  // printf("distancia_semaforo3: %d\n", distancia_semaforo3);
  // printf("distancia_bodega:    %d\n", distancia_bodega);

  // Creamos el camino (array) a recorrer por el repartidor
  int* camino = calloc(distancia_bodega, sizeof(int));
  for (int i = 0; i <= distancia_bodega; i++){
    if ((i == distancia_semaforo1) || (i == distancia_semaforo2) || (i == distancia_semaforo3)) {
      camino[i] = 1;
    } else if (i == distancia_bodega){
      camino[i] = 2;
    } else {
      camino[i] = 0;
    };
  };
  
  // printeamos el camino
  
  // for(int loop = 0; loop < distancia_bodega+1; loop++){
  //   printf("%d-", camino[loop]);
  // };
  while (1) {
    printf("REPARTIDOR %d_____Estoy en la posicion => %d \n", getpid(), posicion_actual);
    sleep(10);
    tiempo += 1;
    
    // hay semaforo en siguiente posicion
    if (camino[posicion_actual + 1] == 1) {
      printf("Hay un semaforo \n");
      int pid_personal = getpid();
      int pid_parent = getppid();
      int solicitud_envio = pid_personal * 100 + 20 + semaforo_cruzado;
      posicion_actual +=1; 
      // preguntar estado de la luz
      // send_signal_with_int(pid_parent, solicitud_envio);
      // recibir estado de la luz
      //wait señal****
      // connect_sigaction(SIGUSR1, luz_semaforo);
    
    // no hay semaforo ni bodega
    } else if (camino[posicion_actual + 1] == 0){ 
      printf("Esta vacio...\n");
      posicion_actual +=1; 

    // hay bodega
    } else if (camino[posicion_actual + 1] == 2){
      printf("LLEGUE A LA BODEGAAA!!!\n");
      posicion_actual += 1;
      sleep(1);
      tiempo += 1;
      contador_tiempos[3] = tiempo;
      break;
      
    } else {
      printf("Esto no deberia pasar en repartidor");
    }
  };

  // Generar archivo
  // Avisar a fábrica el término --> kill(PID,señal)
  free(camino);
  exit (0);
  return 0;
}
