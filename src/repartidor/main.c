#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//Recibe: distancia_semaforo1, distancia_semaforo2, distancia_semaforo3, distancia_bodega
// hacer función para recibir

//Crear array:
/*
int* camino = calloc(distancia_bodega, sizeof(int));
for (int i = 0, i <= distancia_bodega, i++){
  if ((i = distancia_semaforo1) || (i = distancia_semaforo2) || (i = distancia_semaforo3)){
    camino[i] = 1;
  };
  else if (i = distancia_bodega){
    camino[i] = 2;
  };
};

int luz_semaforo(int sig, siginfo_t *siginfo, void *context){
  int number_received = siginfo->si_value.sival_int;
  return number_received;
};

*/
int main(int argc, char const *argv[]){
  printf("Primer argumento, %s\n", argv[0]);
  printf("Segundo argumento, %s\n", argv[1]);

  int first_value = atoi(argv[0]);
  int second_value = atoi(argv[1]);
  int result = first_value+second_value;
  printf("\tEl resultado es =>[%i]\n",result);

  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  sleep(1);
  return(0);
/*
  int posicion_actual = 0;
  int semaforo_cruzado = 0;
  int contador_tiempos[4] = {0, 0, 0, 0}
  int tiempo = 0

  while (true){
    sleep(1);
    tiempo += 1;
    // hay semaforo en siguiente posicion
    if (camino[posicion_actual + 1] = 1){
      //enviar señal a fábrica consultando estado send_signal_with_int (PID + 20 + semaforo_cruzado);
      //wait señal
      //cruzar = recibir señal de fábrica connect_sigaction(SIGUSR1, luz_semaforo);
      if (cruzar){
        posicion_actual +=1;
        semaforo_cruzado +=1;
        contador_tiempos[semaforo_cruzado] = tiempo;
      };
    };

    // no hay semaforo ni bodega
    else if (camino[posicion_actual + 1] = 0){
      posicion_actual +=1;
    }

    // hay bodega
    else if (camino[posicion_actual + 1] = 2){
      posicion_actual += 1;
      sleep(1);
      tiempo += 1;
      contador_tiempos[3] = tiempo;
      break;
    };
  };

  // Generar archivo
  // Avisar a fábrica el término --> exit(0)

  //LIBERAR CAMINO (FREE)
  
*/
}
