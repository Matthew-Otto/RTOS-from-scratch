// ipc.c
// various primatives to faciliate inter-process communication

#include <stdio.h>
#include <stdlib.h>
#include "ipc.h"

/************* SPSC_FIFO *************/
// lock free fifo suitable for single-producer single-consumer

FIFO *SPSC_Fifo_Init(int size) {
  size_t fifo_size = sizeof(FIFO) + size * sizeof(int);
  FIFO *fifo = (FIFO *)malloc(fifo_size);
  if (fifo == NULL) {
    return -1;
  }
  fifo->head = 0;
  fifo->tail = 0;
  fifo->size = size;
  return fifo;
}

void SPSC_Fifo_Put(FIFO *fifo, int data) {
  if ((fifo->tail + 1) % fifo->size == fifo->head) {
    return 0; // FIFO full
  }
  fifo->data[fifo->tail] = data;
  fifo->tail = (fifo->tail + 1) % fifo->size;
}

int SPSC_Fifo_Get(FIFO *fifo) {
  while (fifo->head == fifo->tail) {
    OS_Suspend(); // wait until not empty
  }
  int data = fifo->data[fifo->head];
  fifo->head = (fifo->head + 1) % fifo->size;
}

int SPSC_Fifo_Size(FIFO *fifo) {
  if (fifo->tail >= fifo->head)
    return fifo->tail - fifo->head;
  else
    return fifo->size - (fifo->head - fifo->tail);
}
