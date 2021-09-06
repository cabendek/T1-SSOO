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
int id_repartidor;

void luz_semaforo(int sig, siginfo_t *siginfo, void *context){
  int number_received = siginfo->si_value.sival_int;
  sleep(1);
  if (number_received == 1) {// En verde
    posicion_actual += 1;
    contador_tiempos[semaforo_cruzado] = tiempo;
    semaforo_cruzado += 1;
  }
};

void finalizar(int sig){

  // Generar archivo
  printf("Gracefully finishing\n");

  // Abrimos un archivo en modo de lectura
  char name_file[30]; 
  sprintf(name_file,"repartidor_%d.txt",id_repartidor);

  FILE *output = fopen(name_file, "w");
  for (int i = 0; i < 4; i++) {
    fprintf(output, "%i", contador_tiempos[i]);
    // No agregamos el separador al último número
    if (i + 1 != 4)
      fprintf(output, ", ");
  }

  // Se cierra el archivo (si no hay leak)
  fclose(output);

  // Avisar a fábrica el término --> kill(PID,señal)
  
  // Terminamos el programa con exit code 0
  exit(0);
}

int main(int argc, char const *argv[]){

  printf("I'm the REPARTIDOR process and my PID is: %i ----------------\n", getpid());

  int distancia_semaforo1 = atoi(argv[0]);
  int distancia_semaforo2 = atoi(argv[1]);
  int distancia_semaforo3 = atoi(argv[2]);
  int distancia_bodega = atoi(argv[3]);
  id_repartidor = atoi(argv[4]) - 1;


  while(true) {
    sleep(1);
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

    // Bodega
    } else if (posicion_actual + 1 == distancia_bodega) {
      printf("LLEGUE A LA BODEGAAA!!!\n");
      posicion_actual += 1;
      sleep(1);
      tiempo += 1;
      contador_tiempos[3] = tiempo;
      break;
      
    } else {
      sleep(1);
      printf("Camino vacio\n");
      posicion_actual += 1;
    }
  };

  signal(SIGABRT,finalizar);
  while(true);
  return 0;

}
