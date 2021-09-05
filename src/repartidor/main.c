#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// funcion para crear el array - camino
// int* crear_camino(int distancia_semaforo1, int distancia_semaforo2, int distancia_semaforo3, int distancia_bodega)
// {
//   int* camino = calloc(distancia_bodega, sizeof(int));
//   for (int i = 0, i <= distancia_bodega, i++)
//   {
//     if ((i = distancia_semaforo1) || (i = distancia_semaforo2) || (i = distancia_semaforo3)){
//       camino[i] = 1;
//     }
//     else if (i = distancia_bodega)
//     {
//     camino[i] = 2;
//     }
//   }
//   return camino;
// }

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

  // int distancia_semaforo1 = atoi(argv[0]);
  // int distancia_semaforo2 = atoi(argv[1]);
  // int distancia_semaforo3 = atoi(argv[2]);
  // int distancia_bodega = atoi(argv[3]);
  
  // Validando valores de variables
  // printf("distancia_semaforo1: %d\n", distancia_semaforo1);
  // printf("distancia_semaforo2: %d\n", distancia_semaforo2);
  // printf("distancia_semaforo3: %d\n", distancia_semaforo3);
  // printf("distancia_bodega:    %d\n", distancia_bodega);
  printf("I'm the REPARTIDOR process and my PID is: %i ---------------------------------------\n", getpid());

  // Creamos el camino (array) a recorrer por el repartidor
  

  //sleep(1);
  exit (0);
  return 0;
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
