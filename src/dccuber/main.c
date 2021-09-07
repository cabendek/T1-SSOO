#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../file_manager/manager.h"

int estado_semaforos[3] = {1,1,1};
int pid_semaforos[3];
int tiempo_repartidores;
int cant_repartidores;
int contador = 1;
int distancia_semaforo1;
int distancia_semaforo2;
int distancia_semaforo3;
int distancia_bodega;
int repartidor;
int fabrica;
int* pid_repartidores;
int repartidores_finalizados = 0;

void handle_sigalrm(int sig) {
  // Vamos a enviarle todos los números al hijo

  repartidor = fork();

  if (!repartidor){
    
    char distancia_1_s[10];
    char distancia_2_s[10];
    char distancia_3_s[10];
    char distancia_4_s[10];
    char indice_repartidor[10];
    sprintf(distancia_1_s,"%d", distancia_semaforo1);
    sprintf(distancia_2_s,"%d", distancia_semaforo2);
    sprintf(distancia_3_s,"%d", distancia_semaforo3);
    sprintf(distancia_4_s,"%d", distancia_bodega);
    sprintf(indice_repartidor,"%d", contador);

    char* args[] = {distancia_1_s,distancia_2_s,distancia_3_s,distancia_4_s,indice_repartidor,NULL};
    printf("Cree un repartidor\n");
    if(execv("repartidor", args) == -1) {
      printf("\nfailed connection\n");
    }
  } else {
    pid_repartidores[contador] = repartidor;
  }
  if (contador < cant_repartidores) {
    alarm(tiempo_repartidores);
    contador += 1;
  }
};

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

// MANEJO DE 2 RECEPCIONES DE SEÑAL
void handle_siguser1(int sig, siginfo_t *siginfo, void *context) {
  int number_received = siginfo->si_value.sival_int;
  printf("> > > > Mensaje recibido: %d\n",number_received );
  int from = (number_received/10%10);
  int id_semaforo = (number_received%10);
  
  if (from == 1) { //SEMAFORO
    if (estado_semaforos[id_semaforo] == 0) {
      estado_semaforos[id_semaforo] = 1;
    } else {
      estado_semaforos[id_semaforo] = 0;
    }
  } else if (from == 2) { //REPARTIDOR
    int PID_repartidor = (number_received/100);
    send_signal_with_int(PID_repartidor, estado_semaforos[id_semaforo]);
  } else {
    printf("Esto NO se deberia imprimir");
  }
};

void handle_siguser2(int sig, siginfo_t *siginfo, void *context){
  repartidores_finalizados += 1;
  if (repartidores_finalizados == cant_repartidores){
    kill(getppid(),SIGINT);
  }
}

void handle_sigint(int sig){
  printf("PRINCIPAL: Le digo a FABRICA que termine al PID: %d \n",fabrica);
  kill(fabrica, SIGABRT); // Mandarle a fabrica la señal SIGABRT

  waitpid(fabrica, NULL, 0); //Hacer un wait a que fabrica termine
  
  printf("PRINCIPAL: Le digo a los SEMAFOROS que terminen \n");
  kill(pid_semaforos[0],SIGABRT);
  kill(pid_semaforos[1],SIGABRT);
  kill(pid_semaforos[2],SIGABRT);
  waitpid(pid_semaforos[0], NULL, 0);
  waitpid(pid_semaforos[1], NULL, 0);
  waitpid(pid_semaforos[2], NULL, 0);

  exit(0);
};

void handle_sigabrt(int sig){
  printf("FABRICA: Le digo a los repartidores que terminen...\n");
  
  for (int i=0 ; i<cant_repartidores;i++) {
    kill(pid_repartidores[i], SIGABRT); // ACA DEBERIA MANDAR SIGABRT A LOS PROCESOS REPARTIDORES
  }
  for (int i=0 ; i<cant_repartidores;i++) {
    waitpid(pid_repartidores[i], NULL, 0); // Esperar a los repartidores
  }
  printf("FABRICA: mori XP\n");
  exit(0);
};

void handle_sigint_fab(int sig) {
};


int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %d \n", getpid());

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
  
  distancia_semaforo1 = linea_1[0];
  distancia_semaforo2 = linea_1[1];
  distancia_semaforo3 = linea_1[2];
  distancia_bodega = linea_1[3];

  int tiempo_de_creacion = linea_2[0];
  int envios_necesarios = linea_2[1];
  int tiempo_1 = linea_2[2];
  int tiempo_2 = linea_2[3];
  int tiempo_3 = linea_2[4];

  tiempo_repartidores = tiempo_de_creacion;
  cant_repartidores = envios_necesarios;
  pid_repartidores = calloc(cant_repartidores, sizeof(int));

  // Printeamos variables (para verificarlas)
  // printf("%d, %d, %d, %d\n",distancia_semaforo1, distancia_semaforo2, distancia_semaforo3, distancia_bodega);
  // printf("%d, %d, %d, %d, %d\n",tiempo_de_creacion, envios_necesarios, tiempo_1, tiempo_2, tiempo_3);

  
  // Proceso Principal crea a Fabrica:
  /* FABRICA */

  fabrica = fork();
  
  if (!fabrica) {
    //connect_sigaction (SIGUSR1, interpretar_señal); //recibe del semáforo o del repartidor
    printf("FABRICA: Hola soy la Fabrica! con PID: %d \n", getpid());

    /* REPARTIDORES */

    signal(SIGINT, handle_sigint_fab);
    signal(SIGABRT, handle_sigabrt);
    connect_sigaction(SIGUSR1, handle_siguser1);
    connect_sigaction(SIGUSR2, handle_siguser2);
    signal(SIGALRM, handle_sigalrm);

    alarm(tiempo_de_creacion);

    //wait(NULL); //Manejo de finalizacion
    while(true);
    // int returnStatus;
    // waitpid(repartidor, &returnStatus, 0);

  } else { // ---------------------------------------------- SEMAFORO -------------------------------

    char fabrica_s[10];
    sprintf(fabrica_s,"%d",fabrica);
    
    int semaforo1 = fork();
    if (!semaforo1) {

      char tiempo_1_s[30];
      sprintf(tiempo_1_s,"%d", tiempo_1);
      
      char* argf[] = {tiempo_1_s,fabrica_s,"0",NULL};
      if(execv("semaforo", argf) == -1){
        printf("\nFallo la conexion del 1er semaforo\n");
      };
    } else {
      pid_semaforos[0]= semaforo1;
      int semaforo2 = fork();
      if (!semaforo2) {
        // printf("\nSEMAFORO 2\n");
        char tiempo_2_s[30];
        sprintf(tiempo_2_s,"%d", tiempo_2);

        char* argf[] = {tiempo_2_s,fabrica_s,"1",NULL};
        if(execv("semaforo", argf) == -1){
          printf("\nFallo la conexion del 2do semaforo\n");
        };
      } else {
        pid_semaforos[1]= semaforo2;
        int semaforo3 = fork();
        if (!semaforo3) {
          // printf("\nSEMAFORO 3\n");
          char tiempo_3_s[30];
          sprintf(tiempo_3_s,"%d", tiempo_3);

          char* argf[] = {tiempo_3_s,fabrica_s,"2",NULL};
          if(execv("semaforo", argf) == -1){
            printf("\nFallo la conexion del 3er semaforo\n");
          };
        } else {
          pid_semaforos[2]= semaforo3;
        }
      }
    }

    signal(SIGINT, handle_sigint);
    free(pid_repartidores);
    while(true);
  }

  return 0;

}
