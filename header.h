#ifndef DATA
#define DATA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#pragma region Structs

typedef struct operation {
    int id;
    int quantMachines;
    int *machineAndTime;
    struct operation *next;
}operation;

typedef struct job {
    operation *op;
}job;

#pragma endregion

#pragma region Signatures

job *inicializarJob();
operation *inicializarOperation();
void verificarDadosNoFicheiro(operation *op, int *idCont);
void guardarDadosNoFicheiro(operation *op);
void menu(int *opcao);
void inserirNovaOperacao(operation *op, int *idCont);
void listarOperacoes(operation *op);
void removerOperacao(job **jobList);
void editarOperacao(operation *op);
void determinarTempoMinimo(operation *op);
void determinarTempoMaximo(operation *op);

#pragma endregion

#endif