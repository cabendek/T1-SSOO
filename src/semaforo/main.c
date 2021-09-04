#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
/*
typedef struct semaforo
{
 int luz_semaforo;
 int contador_cambios;
}Semaforo;

Semaforo* semaforo_init ()
{
 Semaforo* semaforo = malloc(sizeof(Semaforo));
 *semaforo = (Semaforo) {
  .luz = 1,
  .contador_cambios = 0
 };
}

void cambio_luz (Semaforo* semaforo)
{
 if (semaforo.luz = 0)
 {
  semaforo.luz = 1;
 };
 else if (semaforo.luz = 1)
 {
   semaforo.luz = 0;
 };
 semaforo.contador_cambios += 1
 // enviar señal de cambio a fabrica, indicado id semáforo
}

int finalizar (int funcionando)
{
 funcionando = false;
 return funcionando;
};
*/
int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  return 0;
}
  /*
  //LOGRAR RECIBIR LA VARIABLE tiempo_semaforo y pid_fabrica

  // instanciar semáforo
  Semaforo* semaforo = semaforo_init();

  // comenzar a iterarlo
  int funcionando = true
  while (funcionando):
   sleep(tiempo_semaforo);
   cambio_luz(semaforo);
   // receptor de señal: SIGNAL (alarma, finalizar(funcionando))

  // escribir archivo output
  //fwrite semaforo.contador_cambios;

  // finalizar
  exit(0);
}*/
