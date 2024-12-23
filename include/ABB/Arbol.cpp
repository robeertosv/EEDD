#include "NodoArbol.h"
#include "Arbol.h"
#include "Lista/NodoListaProc.h"
#include "Lista/ListaProc.h"
#include <iostream>
using namespace std;

Arbol::Arbol()
{
    raiz = NULL;
    altura = 0;
    maxPN = 0;
    maxP = -1;
    minPN = 0;
    minP = -1;
}

Arbol::Arbol(Proceso p)
{
    raiz = new NodoArbol(p.priority, ListaProc(p));
    altura = 0;
    maxP = p.priority;
    maxPN = 1;
    minP = p.priority;
    minPN = 1;
}

Arbol::~Arbol() {
};

bool Arbol::isEmpty()
{
    return raiz == NULL;
}

int Arbol::getSize()
{
    return altura;
}

int Arbol::getMin()
{
    return minP;
}

int Arbol::getMax()
{
    return maxP;
}

parbol Arbol::izq()
{
    return raiz->izq;
}

parbol Arbol::dch()
{
    return raiz->dch;
}

bool Arbol::existsNode(parbol a, int p)
{
    if (a == NULL)
    {
        return false;
    }
    else
    {
        return a->prioridad == p || existsNode(a->izq, p) || existsNode(a->dch, p);
    }
}

void Arbol::addProccessToList(parbol a, Proceso p)
{
    if (existsNode(raiz, p.priority))
    {
        if (a->prioridad == p.priority)
        {
            a->procesos.append(p);
            if (a->procesos.length > maxPN)
            {
                maxP = p.priority;
                maxPN = a->procesos.length;
            }
            if (a->procesos.length < minPN)
            {
                minP = p.priority;
                minPN = a->procesos.length;
            }
        }
        else
        {
            if (a->prioridad < p.priority)
            {
                addProccessToList(a->dch, p);
            }
            else
            {
                addProccessToList(a->izq, p);
            }
        }
    }
}

void Arbol::append(Proceso p, parbol a)
{
    if (existsNode(raiz, p.priority))
    {
        // Buscar y append
        addProccessToList(raiz, p);
    }
    else
    {
        // Crear nodo con lista unitaria

        altura++;
        if (raiz == NULL)
        {
            raiz = new NodoArbol(p.priority, ListaProc(p));
            minP = p.priority;
            minPN = 1;
            maxP = p.priority;
            maxPN = 1;
            return;
        }

        if (a == NULL)
        {
            a = raiz;
        }
        if (p.priority < a->prioridad)
        {
            if (a->izq == NULL)
            {
                a->izq = new NodoArbol(p.priority, ListaProc(p));
            }
            else
            {
                append(p, a->izq);
            }
        }
        else
        {
            if (a->dch == NULL)
            {
                a->dch = new NodoArbol(p.priority, ListaProc(p));
            }
            else
            {
                append(p, a->dch);
            }
        }
    }
}

parbol Arbol::getRoot()
{
    return raiz;
}

ListaProc Arbol::getProcsByPriority(parbol a, int p)
{
    if (!existsNode(raiz, p))
    {
        return ListaProc();
    }
    else
    {
        if (a->prioridad == p)
        {
            return a->procesos;
        }
        else
        {
            if (a->prioridad > p)
            {
                return getProcsByPriority(a->izq, p);
            }
            else
            {
                return getProcsByPriority(a->dch, p);
            }
        }
    }
}

int Arbol::getNumProcsByPriority(parbol a, int p)
{
    if (!existsNode(raiz, p))
    {
        return -1;
    }
    else
    {
        if (a->prioridad == p)
        {
            return a->procesos.length;
        }
        else
        {
            if (a->prioridad > p)
            {
                return getNumProcsByPriority(a->izq, p);
            }
            else
            {
                return getNumProcsByPriority(a->dch, p);
            }
        }
    }
}

void Arbol::verInorden(parbol a)
{
    if (a == NULL)
    {
        return;
    }
    verInorden(a->izq);
    a->procesos.toString();
    cout << " ; ";
    verInorden(a->dch);
}

void Arbol::toString(parbol a)
{
    if (a && a != NULL)
    {
        cout << a->prioridad << endl;

        if (a->izq != NULL)
        {
            cout << a->prioridad << " tiene de hijo izquierdo a : ";
            toString(a->izq);
        }

        if (a->dch != NULL)
        {
            cout << "     ";
            cout << a->prioridad << " tiene de hijo derecho a : ";
            toString(a->dch);
        }
    }
}

void Arbol::toString2(parbol a)
{
    if (a != NULL)
    {
        a->procesos.toString();

        if (a->izq != NULL)
        {
            toString(a->izq);
        }

        if (a->dch != NULL)
        {
            cout << "     ";
            toString(a->dch);
        }
    }
}

void Arbol::showPriorities(parbol a)
{
    if (a == NULL)
        return;

    showPriorities(a->dch);
    if (a->procesos.length > 0)
    {
        cout << "Prioridad: " << a->prioridad << endl;
    }
    showPriorities(a->izq);
}

double Arbol::getAverageTimeByPriority(parbol a, int priority)
{
    if (a == NULL)
        return -1;

    if (a->prioridad == priority)
    {
        double totalTime = 0;
        int count = a->procesos.getLength();

        cout << "Hay esta cantidad de procesos: " << count << endl;
        a->procesos.toString();
        for (int i = 0; i < a->procesos.getLength(); i++)
        {
            cout << "Proceso: " << a->procesos.getIndex(i).PID << endl;
            totalTime += a->procesos.getIndex(i).getExecuteTime();
            cout << "Tiempo de ejecución hasta ahora: " << a->procesos.getIndex(i).getExecuteTime() << endl;
        }

        return count > 0 ? totalTime / count : -1;
    }
    else if (priority < a->prioridad)
    {
        return getAverageTimeByPriority(a->izq, priority);
    }
    else
    {
        return getAverageTimeByPriority(a->dch, priority);
    }
}

void Arbol::printAvgExecutionTimeAllPriorities(parbol a)
{
    if (a == NULL)
        return;

    cout << "Visitando nodo con prioridad: " << a->prioridad << endl;

    double totalTime = 0;
    int count = a->procesos.getLength();

    for (int i = 0; i < count; i++)
    {
        totalTime += a->procesos.getIndex(i).getExecuteTime();
    }

    if (count > 0)
    {
        cout << "Prioridad: " << a->prioridad << " - Tiempo promedio de ejecución: " << totalTime / count << " minutos." << endl;
    }

    printAvgExecutionTimeAllPriorities(a->izq);
    printAvgExecutionTimeAllPriorities(a->dch);
}