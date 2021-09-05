#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../file_manager/manager.h"

int estado_semaforos[3] = {1,1,1};


int cambio_semaforo (int semaforo){
  if (estado_semaforos[semaforo] == 0){
    estado_semaforos[semaforo] = 1;
  } else if (estado_semaforos[semaforo] == 1){
    estado_semaforos[semaforo] = 0;
  } else{
    printf("Esto no deberia pasar");
  }

  return 0;
};

void print(int sig, siginfo_t *siginfo, void *context) {
  int number_received = siginfo->si_value.sival_int;
  printf("\n\t -----> CTMMMM LLEGO Y RECIBI EL SEMAFORO: %i\n", number_received);
}

/*
void consultar_semaforo (int semaforo, int PID){
  int estado_semaforo = estado_semaforos[semaforo];
  // enviar señal estado_semaforo con send_signal_with_int(PID, estado_semaforo)
};

void signal_reception (int sig, siginfo_t *siginfo, void *context)
{
  int number_received = siginfo->si_value.sival_int;

  //Hacer la conversion del int
  //cambio_semaforo(id_semaforo);

  //consultar_semaforo(id_semaforo,PID)

};*/

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  // Guardamos las variables
  int linea_1[4];
  int linea_2[5];
  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
    linea_1[i] = atoi(data_in->lines[0][i]);
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
    linea_2[i] = atoi(data_in->lines[1][i]);
  }
  printf("\n");
  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
  
  int distancia_semaforo1 = linea_1[0];
  int distancia_semaforo2 = linea_1[1];
  int distancia_semaforo3 = linea_1[2];
  int distancia_bodega = linea_1[3];

  int tiempo_de_creacion = linea_2[0];
  int envios_necesarios = linea_2[1];
  int tiempo_1 = linea_2[2];
  int tiempo_2 = linea_2[3];
  int tiempo_3 = linea_2[4];

  // Printeamos variables (para verificarlas)
  // printf("%d, %d, %d, %d\n",distancia_semaforo1, distancia_semaforo2, distancia_semaforo3, distancia_bodega);
  // printf("%d, %d, %d, %d, %d\n",tiempo_de_creacion, envios_necesarios, tiempo_1, tiempo_2, tiempo_3);

  
  // Proceso Principal crea a Fabrica:
  /* FABRICA */

  int fabrica = fork();
  
  if (!fabrica) {
    //connect_sigaction (SIGUSR1, interpretar_señal); //recibe del semáforo o del repartidor
    printf("FABRICA: Hola soy la Fabrica! con PID: %d\n",getpid());

    //Creamos el camino
    

    // Fabrica crea a repartidores cada tiempo_de_creacion segundos:
    /* REPARTIDORES */

    connect_sigaction(SIGUSR1,print);

    for (int i = 0; i < envios_necesarios; i++) { 
      
      sleep(tiempo_de_creacion);

      printf("**TIEMPO DE ESPERA: %d SEG\n",tiempo_de_creacion);
      int repartidor = fork();

      if (!repartidor){
  
        printf("---ENTREE AQUI----\n");
        // transformamos a char* cada valor bajo el supuesto de que no habran numeros con mas de 30 digitos
        
        // Semaforo 1
        char d_semaforo1_s[30];
        sprintf(d_semaforo1_s, "%d", distancia_semaforo1);
        // Semaforo 2
        char d_semaforo2_s[30];
        sprintf(d_semaforo2_s, "%d", distancia_semaforo2);
        // Semaforo 3
        char d_semaforo3_s[30];
        sprintf(d_semaforo3_s, "%d", distancia_semaforo3);
        // Bodega
        char d_bodega_s[30];
        sprintf(d_bodega_s, "%d", distancia_bodega);
        
        char* args[] = {d_semaforo1_s, d_semaforo2_s, d_semaforo3_s, d_bodega_s, NULL};

        if(execv("repartidor", args) == -1) {
          printf("\nfailed connection\n");
        }
      }
    };
    while(true);
    printf("\n\tEsto NO se deberia imprimir\n");
    wait(NULL); //Manejo de finalizacion

  } else {

    char fabrica_s[10];
    sprintf(fabrica_s,"%d",fabrica);
    
    int semaforo1 = fork();
    if (!semaforo1) {

      char tiempo_1_s[30];
      sprintf(tiempo_1_s,"%d", tiempo_1);
      
      char* argf[] = {tiempo_1_s,fabrica_s,NULL};
      if(execv("semaforo", argf) == -1){
        printf("\nFallo la conexion del 1er semaforo\n");
      };
    } else {
      int semaforo2 = fork();
      if (!semaforo2) {
        // printf("\nSEMAFORO 2\n");
        char tiempo_2_s[30];
        sprintf(tiempo_2_s,"%d", tiempo_2);

        char* argf[] = {tiempo_2_s,fabrica_s,NULL};
        if(execv("semaforo", argf) == -1){
          printf("\nFallo la conexion del 2do semaforo\n");
        };
      } else {
          int semaforo3 = fork();
          if (!semaforo3) {
            // printf("\nSEMAFORO 3\n");
            char tiempo_3_s[30];
            sprintf(tiempo_3_s,"%d", tiempo_3);

            char* argf[] = {tiempo_3_s,fabrica_s,NULL};
            if(execv("semaforo", argf) == -1){
              printf("\nFallo la conexion del 3er semaforo\n");
            };
          } 
      }
    }

    wait(NULL);
      
  }

  return 0;

}
