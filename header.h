/**
 * @file Header.h
 * @author Rui Pinto (a18450@alunos.ipca.pt)
 * @brief 
 * @version 1.1
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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

/**
* @brief Struct Operacao
*/
typedef struct operacao {
    int id;                 // Codigo da operacao
    int quantMaquinas;      // Quantidade de maquinas na operacao
    int *maquinaTempo;      // Maquina e o seu respetivo tempo
    struct operacao *seg;   // Operacao seguinte
}operacao;

/**
* @brief Struct Job
*/
typedef struct job {
    int id;             // Codigo do Job
    int numOperacoes;   // Numero de operacoes
    operacao *op;       // Apontador da operacao
    struct job *seg;    // Job seguinte
}job;

#pragma endregion

#pragma region Assinaturas Operacao
    
    operacao *inicializarOperacao();
    operacao *novoNoOperacao();
    void inserirNovaOperacao(operacao *op, int *idCont);
    void listaOperacao(operacao *op, int numOperacoes);
    void editaOperacao(operacao *op);
    void determinaTempoCurto(operacao *op);
    void determinaTempoLongo(operacao *op);

    void listarNoOperacao(operacao *op);
    void leOperacao(operacao *op);
    void removeOperacao(operacao *op, int *numOperacoes);
    void insereNoOperacao(operacao *op, int *numOperacoes);

#pragma endregion

#pragma region Assinaturas Job

    job *inicializarJob();
    job *novoNoJob(int key);

    void criaOperacaoApartirFich(operacao *op, int idOp, int cont, int arrM[], int arrT[]);

    void inserirJob(job *jb, int *idContJob);
    void removeJob(job *jb); 

    void listarNoJob(operacao *auxOp, job *jb);
    void listarJobEmListaOrdenada(job *j);

    job *descobreJobLista(job *root, int key) ;
    job *descobreJob(job *auxjb);

#pragma endregion

#pragma region Assinaturas Ficheiro


    void verificarDadosNoFicheiro(operacao *op, int *idCont, int *numOperacoes);
    void criaOperacaoApartirFich(operacao *op, int idOp, int cont, int arrM[], int arrT[]);
    void escreveNoFich(operacao *op, int id, FILE *f_JOB);
    void guardaDadosFile(job *jb, char *nomeFich);
    job *verificaDadosNoFich(job *jb, int *idContJob);

#pragma endregion

#pragma region Outras Assinaturas
    
    void menu(int *opcao);
    int procuraMaquinaIgual(operacao *maq, int procElem, int posAtual);
    int simNao();

#pragma endregion Outras Assinaturas

#endif