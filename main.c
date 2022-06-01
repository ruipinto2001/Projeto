/**
 * @file Main.c
 * @author Rui Pinto (a18450@alunos.ipca.pt)
 * @brief 
 * @version 1.1
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include "header.h"
#include "functions.c"

int main() {

	job *jb = NULL, *procuraJob = NULL;
	int opcao, idContJob = 1, idCont = 0;

	system("cls");
    jb = novoNoJob(idContJob);
    verificaDadosNoFich(jb,&idContJob);


	job *listaJob;	
    operacao *listaOperacao;	

    listaJob = inicializarJob();
	verificarDadosNoFicheiro(listaJob->op,&idCont,&(listaJob->numOperacoes));


    do {
        menu(&opcao);

        switch(opcao) {
            case 1: inserirNovaOperacao(listaJob->op, &idCont); 
					system("pause");
					break;
            case 2: listarOperacao(listaJob->op, listaJob->numOperacoes); 
					system("pause");
					break;
            case 3: procuraJob = descobreJob(jb);
                    removeOperacao(procuraJob->op,&(procuraJob->numOperacoes));
					system("pause");
        			break;
            case 4: procuraJob = descobreJob(jb);
                    editaOperacao(procuraJob->op);
					system("pause");
					break;
            case 5: determinaTempoCurto(listaJob->op);
					system("pause");
					break;
            case 6: determinaTempoLongo(listaJob->op);
					system("pause");
					break;
            case 7: system("cls");
					listarJobEmListaOrdenada(jb);
					system("pause");
					break;
            case 8: inserirJob(jb,&idContJob);
					system("pause");
					break;
            case 9: removeJob(jb);
					system("pause");
					break;
            case 10:procuraJob = descobreJob(jb);
                    insereNoOperacao(procuraJob->op,&(procuraJob->numOperacoes)); 
					system("pause");
					break;
            case 11:procuraJob = descobreJob(jb);
                    removeOperacao(procuraJob->op,&(procuraJob->numOperacoes));
					system("pause");
					break;
            case 12:procuraJob = descobreJob(jb);
                    editaOperacao(procuraJob->op);
					system("pause");
					break;
            case 13:printf("Ate a proxima!\n\n"); 
					break;
        }
    }while(opcao != 0);
    
    guardaDadosFile(jb,"dados.txt");

    return 0;
}