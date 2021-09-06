#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "../file_manager/manager.h"

int id_semaforo;

typedef struct semaforo {
  int luz_semaforo;
  int contador_cambios;
} Semaforo;
 
Semaforo* semaforo_init () {
  Semaforo* semaforo = malloc(sizeof(Semaforo));
  *semaforo = (Semaforo) {
    .luz_semaforo = 1,
    .contador_cambios = 0
  };
  return semaforo;
}

void cambio_luz (Semaforo* semaforo, int pid_fabrica) {
  if ((semaforo->luz_semaforo = 0)) {
    semaforo->luz_semaforo = 1;
  } else if ((semaforo->luz_semaforo = 1)) {
    semaforo->luz_semaforo = 0;
  }
  semaforo->contador_cambios += 1;
  // printf("Accedi a la funcion para mandar señal al PID: %d\n", pid_fabrica);
  int retorno = 10 + id_semaforo;
  send_signal_with_int(pid_fabrica, retorno);
}

int finalizar (int funcionando) {
  funcionando = false;
  return funcionando;
};


int main(int argc, char const *argv[]) {
  
  int tiempo = atoi(argv[0]);
  int pid_fabrica = atoi(argv[1]);
  int id = atoi(argv[2]);
  id_semaforo = id;
  // printf("pid_padre: %d\n", getppid());
  // printf("tiempo:    %d\n", tiempo);
  // printf("id:        %d\n", id_semaforo);
  // printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  
  // instanciar semáforo
  Semaforo* semaforo = semaforo_init();

  // comenzar a iterarlo
  int funcionando = true;

  for (int i = 0; i<10; i++) {
    sleep(tiempo);
    cambio_luz(semaforo, pid_fabrica);
    // receptor de señal: SIGNAL (alarma, finalizar(funcionando))
  }; 
  
  // while (funcionando) {
  //   sleep(tiempo);
  //   cambio_luz(semaforo, pid_fabrica);
  //   // receptor de señal: SIGNAL (alarma, finalizar(funcionando))
  // } 

  // escribir archivo output
  //fwrite semaforo.contador_cambios;

  // finalizar
  free(semaforo);
  exit(0);
  return 0;
}
