// ipc.h
// various primatives to faciliate inter-process communication

/************* SPSC_FIFO *************/
// lock free fifo suitable for single-producer single-consumer
struct FIFO {
  int head;
  int tail;
  int size;
  int data[];
};
typedef struct FIFO FIFO;

FIFO *SPSC_Fifo_Init(int size);
void SPSC_Fifo_Put(FIFO *fifo, int data);
int SPSC_Fifo_Get(FIFO *fifo);
int SPSC_Fifo_Size(FIFO *fifo);
