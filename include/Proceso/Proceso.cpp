#include "Proceso.h"
#include <iostream>

using namespace std;

Proceso::Proceso() {
    PID = -1;
    PPID = -1;
    startTime = -1;
    ttl = -1;
    priority = -1;
    core = -1;
}

Proceso::Proceso(int pid, int START_TIME, int LIFE_TIME, int PRIORITY, int CORE, int ppid)
{
    PID = pid;
    PPID = ppid;
    startTime = START_TIME;
    ttl = LIFE_TIME;
    priority = PRIORITY;
    core = CORE;
}

Proceso::~Proceso()
{
}

void Proceso::decrementLifeTime(int quantity) {
    if (ttl > 0)
        ttl-=quantity;
}

int Proceso::getPriority() {
    return priority;
}

void Proceso::toString()
{
    cout << "PID: " << PID << endl;
    cout << "PPID: " << PPID << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "Lifetime: " << ttl << " minutos" << endl;
    cout << "Priority: " << priority << endl;
    cout << "Core: " << core << endl;
}

double Proceso::getExecuteTime() {
    return executeTime;
}

void Proceso::setExecuteTime(int tiempo) {
    executeTime = tiempo;
}
