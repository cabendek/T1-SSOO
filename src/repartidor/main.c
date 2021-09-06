#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
  sleep(1);
  if (number_received == 1) {// En verde
    posicion_actual += 1;
    contador_tiempos[semaforo_cruzado] = tiempo;
    semaforo_cruzado += 1;
  }
};

int main(int argc, char const *argv[]){

  printf("I'm the REPARTIDOR process and my PID is: %i ----------------\n", getpid());

  int distancia_semaforo1 = atoi(argv[0]);
  int distancia_semaforo2 = atoi(argv[1]);
  int distancia_semaforo3 = atoi(argv[2]);
  int distancia_bodega = atoi(argv[3]);


  while(true) {
    sleep(1); //deberia ser 1
    tiempo += 1;
    printf("REPARTIDOR %d_____Estoy en la posicion => %d \n", getpid(), posicion_actual);
  
    // Semaforo 1
    if (posicion_actual + 1 == distancia_semaforo1) {
      printf("Encontre el semaforo 1 \n");
      int pid_personal = getpid();
      int pid_parent = getppid();
      int solicitud_envio = pid_personal * 100 + 20;
      send_signal_with_int(pid_parent, solicitud_envio);
      connect_sigaction(SIGUSR1, luz_semaforo);
      
    // Semaforo 2
    } else if (posicion_actual + 1 == distancia_semaforo2){ 
      printf("Encontre el semaforo 2 \n");
      int pid_personal = getpid();
      int pid_parent = getppid();
      int solicitud_envio = pid_personal * 100 + 21;
      send_signal_with_int(pid_parent, solicitud_envio);
      connect_sigaction(SIGUSR1, luz_semaforo);

    // Semaforo 3
    } else if (posicion_actual + 1 == distancia_semaforo3) { 
      printf("Encontre el semaforo 3 \n");
      int pid_personal = getpid();
      int pid_parent = getppid();
      int solicitud_envio = pid_personal * 100 + 22;
      send_signal_with_int(pid_parent, solicitud_envio);
      connect_sigaction(SIGUSR1, luz_semaforo);

    // bodega
    } else if (posicion_actual + 1 == distancia_bodega) {
      printf("LLEGUE A LA BODEGAAA!!!\n");
      posicion_actual += 1;
      sleep(1);
      tiempo += 1;
      contador_tiempos[3] = tiempo;
      exit(0);
      
    } else {
      sleep(1);
      printf("Camino vacio\n");
      posicion_actual += 1;
    }
};

  // Generar archivo
  // Avisar a fábrica el término --> kill(PID,señal)
  exit(0);
  return 0;
}
