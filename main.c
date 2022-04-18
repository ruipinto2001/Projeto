#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include "header.h"

int main(int argc, char const *argv[]) {
    job *jobList;
    int opcao, idCont = 0;
    
    jobList = inicializarJob();
	verificarDadosNoFicheiro(jobList->op,&idCont);

    do {
        menu(&opcao);

        switch(opcao) {
            case 1: inserirNovaOperacao(jobList->op,&idCont); 
					break;
            case 2: listarOperacoes(jobList->op); 
					break;
            case 3: removerOperacao(&jobList);
					break;
            case 4: editarOperacao(jobList->op);
					break;
            case 5: determinarTempoMinimo(jobList->op);
					break;
            case 6: determinarTempoMaximo(jobList->op);
					break;
            case 7: printf("Fim do programa!!\n\n");
            		break;
        }
    }while(opcao != 7);

    guardarDadosNoFicheiro(jobList->op);

    return 0;
}