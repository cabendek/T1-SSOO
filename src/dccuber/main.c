#include <stdio.h>
#include <stdlib.h>
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

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
  }
  printf("\n");

  
  //-- AQUI EMPIEZA --
 
  char* distancia_semaforo1_s = data_in->lines[0][0];
  char* distancia_semaforo2_s = data_in->lines[0][1];
  char* distancia_semaforo3_s = data_in->lines[0][2];
  char* distancia_bodega_s = data_in->lines[0][3];

  char* tiempo_de_creacion_s = data_in->lines[1][0];
  char* envios_necesarios_s = data_in->lines[1][1];
  char* tiempo_1_s = data_in->lines[1][2];
  char* tiempo_2_s = data_in->lines[1][3];
  char* tiempo_3_s = data_in->lines[1][4];
  
  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
  
  int distancia_semaforo1 = atoi(distancia_semaforo1_s);
  int distancia_semaforo2 = atoi(distancia_semaforo2_s);
  int distancia_semaforo3 = atoi(distancia_semaforo3_s);
  int distancia_bodega = atoi(distancia_bodega_s);

  int tiempo_de_creacion = atoi(tiempo_de_creacion_s);
  int envios_necesarios = atoi(envios_necesarios_s);
  int tiempo_1 = atoi(tiempo_1_s);
  int tiempo_2 = atoi(tiempo_2_s);
  int tiempo_3 = atoi(tiempo_3_s);

  printf("%i, %i, %i, %i\n",distancia_semaforo1, distancia_semaforo2, distancia_semaforo3, distancia_bodega);
  printf("%i, %i, %i, %i, %i\n",tiempo_de_creacion, envios_necesarios, tiempo_1, tiempo_2, tiempo_3);



  int fabrica = fork();
  
  if (!fabrica){
    //connect_sigaction (SIGUSR1, interpretar_señal); //recibe del semáforo o del repartidor
    printf("FABRICA: Hola soy la Fabrica!\n");
    
    for (int i = 0; i < 1; i++){ //DUDA:: Se hacen esa cantidad de repartidores o se siguen haciendo y cuando finaliza la cantidad de envios necesarios se corta???
      int repartidor = fork();

      if (!repartidor){
        printf("REPARTIDOR: Hola soy un repartidor!\n");
        
        char* args[] = {"2", "1", NULL };
        
        if(execv("repartidor", args) == -1) {
            printf("\nfailed connection\n");}
        
        printf("ESTA WEA NO SE IMPRIME");
      }

    };

    wait(NULL); //Manejo de finalizacion
    printf("Ahora si me duermo");

  } else {
    /*
    int semaforo1 = fork();
    int semaforo2 = fork();
    int semaforo3 = fork();

    if (!semaforo1){
        //execute() semaforo 1
      }
    else if (!semaforo2) {
        //execute() semaforo 2
      }
    else if (!semaforo3) {
        //execute() semaforo 3
      };
      */
  }

  return 0;

}
