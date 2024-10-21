#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Proceso/Proceso.h"
#include "Pila/NodoPila.h"
#include "Pila/Pila.h"
#include "Cola/Cola.h"
#include "Cola/NodoCola.h"

class Scheduler{
    private:
        Pila procesos;
        Cola colaEspera;

        Proceso core_1;
        Proceso core_2;
        Proceso core_3;

    public:
        Scheduler();
        ~Scheduler();
        
        void addProcessToQueue();
        void addProcessToCore();
        void freeCore(int core);
};

#endif