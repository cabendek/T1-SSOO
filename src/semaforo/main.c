#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "../file_manager/manager.h"

int id_semaforo;
int funcionando = true;
int luz_semaforo = 1;
int contador_cambios = 0;

void cambio_luz (int pid_fabrica) {
  if ((luz_semaforo = 0)) {
    luz_semaforo = 1;
  } else if ((luz_semaforo = 1)) {
    luz_semaforo = 0;
  }
  contador_cambios += 1;
  int retorno = 10 + id_semaforo;
  send_signal_with_int(pid_fabrica, retorno);
}

void finalizar (int sig) {
  funcionando = false;
  // Generar archivo
  printf("Gracefully finishing SEMAFORO\n");

  // Abrimos un archivo en modo de lectura
  char name_file[30]; 
  sprintf(name_file,"semaforo_%d.txt", id_semaforo);

  FILE *output = fopen(name_file, "w");
  fprintf(output, "%i", contador_cambios);

  // Se cierra el archivo (si no hay leak)
  fclose(output);

  // Finalizar
  exit(0);
};

void handle_sigint(int sig){
}

int main(int argc, char const *argv[]) {
  
  int tiempo = atoi(argv[0]);
  int pid_fabrica = atoi(argv[1]);
  int id = atoi(argv[2]);
  id_semaforo = id;
  // printf("pid_padre: %d\n", getppid());
  // printf("tiempo:    %d\n", tiempo);
  // printf("id:        %d\n", id_semaforo);
  // printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());

  signal(SIGINT, handle_sigint);
  signal(SIGABRT,finalizar);

  while (funcionando) {
    sleep(tiempo);
    cambio_luz(pid_fabrica);
  } 
  return 0;
}
