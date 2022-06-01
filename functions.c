/**
 * @file Functions.c
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

#pragma region Operacao 

/**
* @brief Inicia a lista das operações
*/
operacao *inicializarOperacao() {
	operacao *op;
	op = (operacao*) malloc(sizeof(operacao));
	
	if(op==NULL){
		system("cls");
		printf("Nao foi possivel criar a lista.\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*op).id=0;
		(*op).seg=NULL;
		return(op);
	}
}

/**
* @brief Inicializa o Job na lista
*/
operacao *novoNoOperacao() {
	operacao *p = (operacao*) malloc(sizeof(operacao));
	
	if(p == NULL) {
		system("cls");
		printf("Nao foi possivel criar a lista.""\n\n");
		system("pause");
		return NULL;
	}
	else {
		p->id = 0;
        p->quantMaquinas = 0;
        p->maquinaTempo = NULL;
		p->seg = NULL;
		return p;
	}
}

/**
* @brief Verificação de dados no ficheiro
*/
void verificarDadosNoFicheiro(operacao *op, int *idCont, int *numOperacoes){
	operacao *opP, *auxOp;
	FILE *f_JOB = fopen("dados.txt","r");
	char symb ;
    unsigned char symbI;
	int i = 0, cont = 0, success = 0, arrayM[100], arrayT[100];

    if(f_JOB != NULL) {
		do {
			if((symb = getc(f_JOB)) != EOF) {
				i = cont = 0;
				while ((symb=getc(f_JOB))!='\n') {
					symbI = (int) symb;
					if(symbI >= '0' && symbI <='9') {
						arrayM[i] = symbI - '0';
						cont++;
						i++;
					}
				}
				i=0;
				while ((symb=getc(f_JOB))!='\n') {
					symbI = (int) symb;
					if(symbI >= '0' && symbI <='9') {
						arrayT[i] = symbI - '0';
						i++;
					}
				}

				opP=(operacao *)malloc(sizeof(operacao));
				(*opP).seg=NULL;

				while((*op).seg != NULL) {
					op = (*op).seg;
				}

				(*numOperacoes)++;

				(*idCont)++;
				(*op).id = (*idCont);
				(*op).quantMaquinas = cont;
				(*op).maquinaTempo = (int *)malloc(sizeof(int[2][cont]));
				for(i=0; i < cont; i++) {
					(*op).maquinaTempo[0*cont + i] = arrayM[i];
					(*op).maquinaTempo[1*cont + i] = arrayT[i];
				}
				(*op).seg = opP;
				success = 0;
			}
			else{
				success = 1;
			}
		}while(success == 0);
	}

    fclose(f_JOB);
}

/**
* @brief Insere uma nova operação na lista
*/
void inserirNovaOperacao(operacao *op, int *idCont) {
    char *input;
    int i, j;
	operacao *auxOp;

	auxOp = (operacao*)malloc(sizeof(operacao));
	
	system("cls");
	if(auxOp==NULL) { 
		printf("Nao existe espaco na memoria!\n\n");
		system("pause");
	}
	else {
		system("cls");
        (*auxOp).seg=NULL;
		while(((*op).seg) != NULL) {
			op = (*op).seg;
		}

		(*idCont)++;
		(*op).id = (*idCont);

		printf("Quantas maquinas ira usar a operacao: ");
		fgets(input, sizeof(input), stdin);
		(*op).quantMaquinas = strtol(input, NULL, 0);
		(*op).maquinaTempo = (int *)malloc(sizeof(int[2][(*op).quantMaquinas]));
		for (i = 0; i < 2; ++i) {
			for (j = 0; j < (*op).quantMaquinas; ++j) {
				if(i==0) {
					printf("Id da Maquina %d: ", j+1);
					fgets(input, sizeof(input), stdin);
					(*op).maquinaTempo[i*(*op).quantMaquinas + j] = strtol(input, NULL, 10);
				}
				else {
					printf("Tempo da Maquina %d: ", (*op).maquinaTempo[0*(*op).quantMaquinas + j]);
					fgets(input, sizeof(input), stdin);
					(*op).maquinaTempo[i*(*op).quantMaquinas + j] = strtol(input, NULL, 10);
				}
			}
		}
		(*op).seg = auxOp;
	}
}

/**
* @brief Lista todas as operacoes
*/
void listarOperacao(operacao *op, int numOperacoes) {
	int i = 0, j = 0;	

	system("cls");
	if((*op).seg==NULL)	{
		puts("Nenhum");
	}
	else {
		//printf("Este job contem %d Operacoes.\n\n", numOperacoes);
		while((*op).seg != NULL) {
			printf("Id - (%d)\n",(*op).id);
			printf("Maquina - (");
			for (j = 0; j < (*op).quantMaquinas; ++j) {
				if(((*op).quantMaquinas - j) == 1)
					printf("%d",(*op).maquinaTempo[0*(*op).quantMaquinas + j]);
				else
					printf("%d,",(*op).maquinaTempo[0*(*op).quantMaquinas + j]);
			}
			printf(")");
			printf("\nTempo - [");
			for (j = 0; j < (*op).quantMaquinas; ++j) {
				if(((*op).quantMaquinas - j) == 1)
					printf("%d",(*op).maquinaTempo[1*(*op).quantMaquinas + j]);
				else
					printf("%d,",(*op).maquinaTempo[1*(*op).quantMaquinas + j]);	
			}
			printf("]\n\n");
			op=(*op).seg;
		}
	}
	printf("\n\n");
	system("pause");
}

/**
* @brief Edita uma operação
*/
void editaOperacao(operacao *op) {
	int ElemEditar;

	system("cls");
	
	if((op->seg) == NULL) { 
		printf("Nao existe operacoes na lista.\n"); 
	}
	else {
		printf("Qual e o codigo da operacao que deseja editar?\n");
		scanf("%d",&ElemEditar);

		if(ElemEditar == op->id) {
			system ("cls");
			printf("O elemento esta a ser editado.\n");
			listarNoOperacao(op);
			leOperacao(op);
		}
		else {
			while((ElemEditar != op->id) && (op->seg != NULL)) {
				op = op->seg;
			}
			
			if(ElemEditar == op->id) {
				system ("cls");
				printf("O elemento esta a ser editado.\n");
				listarNoOperacao(op);
				leOperacao(op);
			}
			else {
				system("cls");
				printf("O elemento com id %d não existe na lista", ElemEditar);
			}
		}
	}
}

/**
* @brief Remove uma operação
*/
void removeOperacao(operacao *op, int *numOperacoes) {
	operacao *j, *atras, *frente, *auxOp;
	int ElemRetirar;

	system("cls");
	j = op;
	
	if((j->seg)==NULL) { 
		printf("Não existe operações na lista.\n"); 
	}
	else {
		printf("Qual é o código cuja operação pretende remover?\n");
		scanf("%d",&ElemRetirar);

		if(ElemRetirar == op->id) {
			system ("cls");
			
			(*numOperacoes)--;
			printf("O elemento foi removido\n");
			listarNoOperacao(op);
			op = op->seg;
			free(j);
		}
		else {
			auxOp = op;
			while((ElemRetirar != auxOp->id) && (auxOp->seg != NULL)) {
				atras = auxOp;
				auxOp = auxOp->seg;
				frente = auxOp->seg;
			}
			
			if(ElemRetirar == auxOp->id) {
				atras->seg = frente;
				system ("cls");
				
				(*numOperacoes)--;
				printf("O elemento foi removido!\n");
				listarNoOperacao(auxOp);
				free(auxOp);
			}
			else {
				system("cls");
				printf("O elemento com código %d não existe na lista.", ElemRetirar);
			}
		}
	}
}

/**
* @brief Remove uma operação de um job
*/
void removeOperacaoNumJob(operacao *op, int *numOperacoes) {
	operacao *j, *atras, *frente, *auxOp;
	int ElemRetirar;

	system("cls");
	j = op;
	
	if((j->seg)==NULL) { 
		printf("Não existe operações na lista.\n"); 
	}
	else {
		printf("Qual é o código cuja operação pretende remover?\n");
		scanf("%d",&ElemRetirar);

		if(ElemRetirar == op->id) {
			system ("cls");
			
			(*numOperacoes)--;
			printf("O elemento foi removido\n");
			listarNoOperacao(op);
			op = op->seg;
			free(j);
		}
		else {
			auxOp = op;
			while((ElemRetirar != auxOp->id) && (auxOp->seg != NULL)) {
				atras = auxOp;
				auxOp = auxOp->seg;
				frente = auxOp->seg;
			}
			
			if(ElemRetirar == auxOp->id) {
				atras->seg = frente;
				system ("cls");
				
				(*numOperacoes)--;
				printf("O elemento foi removido!\n");
				listarNoOperacao(auxOp);
				free(auxOp);
			}
			else {
				system("cls");
				printf("O elemento com código %d não existe na lista.", ElemRetirar);
			}
		}
	}
}

/**
* @brief  Determina o tempo maximo necessario para completar o job e listagem das respetivas operações
*/
void determinaTempoLongo(operacao *op) {
	int i = 0, k = 0, soma = 0, maximo, mach;

	system("cls");
	if((*op).seg==NULL) {
		puts("Nenhum dado");
	}
	else {
		printf("Necessita de uma quantidade minima de tempo para finalizar o Job:\n");
		while((*op).seg != NULL) { 
			maximo = 0;
			for (k = 0; k < (*op).quantMaquinas; ++k) {
				if((*op).maquinaTempo[1*(*op).quantMaquinas + k] > maximo) {
					maximo = (*op).maquinaTempo[1*(*op).quantMaquinas + k];
					mach = (*op).maquinaTempo[0*(*op).quantMaquinas + k];
				}
			}
			printf("%d", mach);
			if((*(*op).seg).seg != NULL)
				printf(",");

			soma = soma + maximo;
			op=(*op).seg;
		}
		printf("\nO tempo mais longo e: %d", soma);
	}
	printf("\n\n");
	system("pause");
}

/**
* @brief Determina o tempo minimo necessario para completar o job e listagem das respetivas operações
*/
void determinaTempoCurto(operacao *op) {
	int i = 0, k = 0, soma = 0, minimo, mach;

	system("cls");
	if((*op).seg==NULL) {
		puts("Nao existe dados!");
	}
	else {
		printf("Necessita de uma quantidade maxima de tempo para finalizar o Job:\n");
		while((*op).seg != NULL) { 
			minimo = 99999;
			for (k = 0; k < (*op).quantMaquinas; ++k) {
				if((*op).maquinaTempo[1*(*op).quantMaquinas + k] < minimo) {
					minimo = (*op).maquinaTempo[1*(*op).quantMaquinas + k];
					mach = (*op).maquinaTempo[0*(*op).quantMaquinas + k];
				}
			}
			printf("%d", mach);
			if((*(*op).seg).seg != NULL)
				printf(",");

			soma = soma + minimo;
			op=(*op).seg;
		}
		printf("\nO tempo mais curto e: %d", soma);
	}
	printf("\n\n");
	system("pause");
}

/**
* @brief Listar a operação selecionada
*/
void listarNoOperacao(operacao *op) {
	int j = 0;

	printf("Id - (%d)\n",op->id);
	printf("Maquina - (");
	for (j = 0; j < op->quantMaquinas; ++j) {
		if((op->quantMaquinas - j) == 1)
			printf("%d",op->maquinaTempo[0*op->quantMaquinas + j]);
		else
			printf("%d,",op->maquinaTempo[0*op->quantMaquinas + j]);
	}
	printf(")\nTempo - [");
	for (j = 0; j < op->quantMaquinas; ++j) {
		if((op->quantMaquinas - j) == 1)
			printf("%d",op->maquinaTempo[1*op->quantMaquinas + j]);
		else
			printf("%d,",op->maquinaTempo[1*op->quantMaquinas + j]);
	}
	printf("]\n\n");

}

/**
* @brief Criar uma operação dentro do ficheiro
*/
void criaOperacaoApartirFich(operacao *op, int idOp, int numMaquinas, int arrM[], int arrT[]) {
	operacao *pOp;
	int i = 0;

	pOp = novoNoOperacao();

	while(op->seg != NULL) {
		op = op->seg;
	}

	op->id = idOp;
	op->quantMaquinas = numMaquinas;
	op->maquinaTempo = (int *)malloc(sizeof(int[2][op->quantMaquinas]));
	for(i=0; i < op->quantMaquinas; i++) {
		op->maquinaTempo[0*op->quantMaquinas + i] = arrM[i];
		op->maquinaTempo[1*op->quantMaquinas + i] = arrT[i];
	}
	op->seg = pOp;
}

/**
* @brief Recolha de informação de uma operação
*/
void leOperacao(operacao *op) {
	int i, j, verificar;

	printf("Quantas máquinas podem ser utilizadas para esta operação: ");
	scanf("%d",&op->quantMaquinas);

	op->maquinaTempo = (int *)malloc(sizeof(int[2][op->quantMaquinas]));
	for (i = 0; i < 2; i++) {
		for (j = 0; j < op->quantMaquinas; j++) {
			if(i == 0) {
				do {
					if( j > 0) {
						verificar = 0;
						printf("Qual é o id da máquina que pretende utilizar: ");
						scanf("%d",&op->maquinaTempo[i*op->quantMaquinas + j]);

						verificar = procuraMaquinaIgual(op,op->maquinaTempo[i*op->quantMaquinas + j],j);
						if(verificar == 0) {
							printf("\nA maquina %d ja esta em uso. Escolha outra maquina\n\n", op->maquinaTempo[i*op->quantMaquinas + j]);
						}
					}
					else {
						verificar = 1;
						printf("Qual é o id da máquina que pretende utilizar: ");
						scanf("%d",&op->maquinaTempo[i*op->quantMaquinas + j]);
					}
				}while(verificar == 0);
			}
			else {
				printf("Quanto tempo demorará a maquina %d: ", op->maquinaTempo[0*op->quantMaquinas + j]);
				scanf("%d",&op->maquinaTempo[i*op->quantMaquinas + j]);
			}
		}
	}
}

/**
* @brief Inserir uma seguinte operação
*/
void insereNoOperacao(operacao *op, int *numOperacoes) {
	operacao *auxOp;
	int id = 1;

	auxOp = novoNoOperacao();
	system("cls");

	if(auxOp==NULL) { 
		printf("Não há mais espaço de memória. É impossível inserir na operacao.\n\n");
		system("pause");
	}
	else {
		while((op->seg) != NULL) {
			id = op->id + 1;
			op = op->seg;
		}

		(*numOperacoes)++;
		op->id = id;
		leOperacao(op);
		op->seg = auxOp;
	}
}

#pragma endregion Operacao



#pragma region Job

/**
* @brief Inicia a lista dos jobs
*/
job *inicializarJob() {
	job *p;
	p = (job *) malloc( sizeof(job));
	
	if(p==NULL) {
		system("cls");
		printf("E impossivel criar a estrutura\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*p).numOperacoes = 0;
		(*p).op = inicializarOperacao();
		return(p);
	}
}

/**
* @brief criação de um job na lista
*/
job *novoNoJob(int key) {
	job *no = (job *) malloc(sizeof(job));

	if(no == NULL) {
		system("cls");
		printf("Nao foi possivel criar a arvore\n\n");
		system("pause");
		return NULL;
	}
	else {
        no->id = key;
        no->numOperacoes = 0;
		no->op = novoNoOperacao();
		no->seg = NULL;
		return no;
	}
}

/**
* @brief Inserir um novo job
*/
void inserirJob(job *jb, int *idContJob) {
	job *auxjb = NULL, *atravesLista = NULL;
	int SN;

	system("cls");
	(*idContJob)++;
	auxjb = novoNoJob((*idContJob));
	atravesLista = jb;
	while (atravesLista->seg != NULL) {
		atravesLista = atravesLista->seg;
	}
	atravesLista->seg = auxjb;

	printf("Quer adicionar operacoes ao novo job?\n");
	while (SN = simNao(), SN == 1) {
		insereNoOperacao(atravesLista->op,&(atravesLista->numOperacoes));
	}
}

/**
* @brief Remocao de um job
*/
void removeJob(job *jb) {
	job *j, *atras, *frente, *auxOp;
	int ElemRetirar;

	system("cls");
	j = jb;
	
	if((j->seg)==NULL) { 
		printf("Nao tem operacoes na lista\n"); 
	}
	else {
		printf("Qual é o codigo do Job que deseja remover\n");
		scanf("%d",&ElemRetirar);

		if(ElemRetirar == jb->id) {
			system ("cls");
			printf("O job foi removido\n");
			listarNoJob(jb->op,jb);
			jb = jb->seg;
			free(j);
		}
		else {
			auxOp = jb;
			while((ElemRetirar != auxOp->id) && (auxOp->seg != NULL)) {
				atras = auxOp;
				auxOp = auxOp->seg;
				frente = auxOp->seg;
			}
			
			if(ElemRetirar == auxOp->id) {
				atras->seg = frente;
				system ("cls");
				printf("O job foi removido\n");
				listarNoJob(jb->op,jb);
				free(auxOp);
			}
			else {
				system("cls");
				printf("O job com o numero %d nao existe na lista", ElemRetirar);
			}
		}
	}
}

/**
* @brief Insere um novo job na lista
*/
void listarNoJob(operacao *auxOp, job *jb) {
	int i = 0;

	for(i = 0; i < 25; i++) printf("%c",205);
	printf("\nJOB N%c %d\n",167,jb->id);

	if(jb->numOperacoes > 0) {
		printf("Contagem de operacoes: %d\n",jb->numOperacoes);
		while(auxOp->seg != NULL) {
            listarNoOperacao(auxOp);
            auxOp = auxOp->seg;
        }
	}
	else {
		printf("O job nao tem operacoes\n\n");
	}
}

/**
* @brief Listagem dos jobs ordenados
*/
void listarJobEmListaOrdenada(job *j) {
    while(j->seg != NULL) {
		listarNoJob(j->op,j);
		j = j->seg;
	}
}

/**
* @brief Procurar o Job pelo codigo
*/
job *descobreJobLista(job *no, int j) {
	while(no->seg != NULL) {
		if (no->id == j) {
			listarNoJob(no->op,no);
			return no;
		} 
		no = no->seg;
	}
	return NULL;
}

/**
* @brief Procura o job que precisa
*/
job *descobreJob(job *auxjb) {
	job *jobADescobrir;
	int ElemDescobrir;

	system("cls");
	
	if(auxjb == NULL) { 
		printf("Não há jobs na lista\n");
		system("cls");
		return NULL;
	}
	else {
		printf("Qual é o id que pretende encontrar?\n");
		scanf("%d",&ElemDescobrir);

		jobADescobrir = descobreJobLista(auxjb,ElemDescobrir);
		if(jobADescobrir != NULL)
			return jobADescobrir;
		
		printf("O Job com o codigo %d não existe!\n", ElemDescobrir);
		return NULL;
	}
}

#pragma endregion Job



#pragma region Outros

/**
* @brief Procura os dados no ficheiro
*/
job *verificaDadosNoFich(job *jb, int *idContJob) {
	job *atravesLista, *auxjb = NULL;
	FILE *f_JOB = fopen("dados.txt","r");
	int i = 0, cont = 0, arrayM[100], arrayT[100], contdigitos = 0, iochar;
	char simpleBuffer[12];

	if(f_JOB != NULL) {
		do {
			i = cont = 0;
			while (iochar = getc(f_JOB), iochar != '\n' && iochar != EOF) {
				if(iochar == '#'){
					do {
						iochar = getc(f_JOB); 
					}while( iochar != '\n' && iochar != EOF);

					(*idContJob)++;
					auxjb = novoNoJob((*idContJob));
					atravesLista = jb;
					while (atravesLista->seg != NULL) {
						atravesLista = atravesLista->seg;
					}
					atravesLista->seg = auxjb;
				}
				if(iochar != '(' && iochar != ')' && iochar != ',' && iochar != ' ' && iochar != '\n') {
					simpleBuffer[contdigitos++] = (char) iochar;
				}
				else if(contdigitos > 0){
					simpleBuffer[contdigitos] = 0; //Anexar caracter nulo ao formato de string final
					arrayM[i] = strtol(simpleBuffer, NULL, 0);
					cont++;
					i++;
					contdigitos = 0;  //Fazer reset ao buffer para ler novo número
				}
			}
			i = 0;
			while (iochar = getc(f_JOB), iochar != '\n' && iochar != EOF) {
				if(iochar != '[' && iochar != ']' && iochar != ',' && iochar != ' ' && iochar != '\n') {
					simpleBuffer[contdigitos++] = (char) iochar;
				}
				else if(contdigitos > 0){
					simpleBuffer[contdigitos] = 0; //Anexar caracter nulo ao formato de string final
					arrayT[i] = strtol(simpleBuffer, NULL, 0);
					i++;
					contdigitos = 0;  //Fazer reset ao buffer para ler novo número
				}
			}

			if(i > 0){
				atravesLista->numOperacoes++;
				criaOperacaoApartirFich(atravesLista->op,atravesLista->numOperacoes,cont,arrayM,arrayT);
			}
			
		}while(iochar != EOF);
	}
	fclose(f_JOB);

	return jb;
}

/**
* @brief Funcao para reconhecer o sim e o nao
*/
int simNao() {
	char buf[1024];

	fflush(stdin);

	while(TRUE) {
		printf("Sim ou Nao: ");

		if(!fgets(buf, sizeof(buf), stdin)) {
			printf("Algo correu mal tente de novo\n\n");
			printf("Erro: %d\n", errno);
			system("pause");
		}
		errno = 0;
		buf[strcspn(buf, "\n")] = 0;
		strlwr(buf);

		if(errno == EINVAL) {
			printf("Ocorreu um erro de conversão: %d""\n", errno);
			exit(0);
		}
		if(errno == ERANGE) {
			printf("A opção introduzida ou é demasiado grande ou demasiado pequena.""\n\n");
		}
		else if((strcmp(buf,"sim") != 0) && (strcmp(buf,"nao") != 0)) {
			printf("Por favor, introduza um Sim ou Não.\n\n");
		}
		else if(strcmp(buf,"sim") == 0) {
			return 1;
		}
		else if(strcmp(buf,"nao") == 0) {
			return 0;
		}
	}
}

/**
* @brief Procura uma maquina igual
*/
int procuraMaquinaIgual(operacao *maq, int procElem, int posAtual) {
	for(int i = posAtual - 1; i >= 0; i--) {
		if(maq->maquinaTempo[i] == maq->maquinaTempo[posAtual])
			return 0;
	}
	return 1;
}

/**
* @brief Escrever no ficheiro de texto
*/
void escreveNoFich(operacao *op, int id, FILE *f_JOB) {
	int i;

	fprintf(f_JOB,"#%d\n", id);
	while(op->seg != NULL) {
		if(op->quantMaquinas == 1) {
			fprintf(f_JOB,"(%d)\n", op->maquinaTempo[1*op->quantMaquinas + 0]);
			fprintf(f_JOB,"[%d]\n", op->maquinaTempo[0*op->quantMaquinas + 0]);
		}
		else {
			for(i = 0; i < op->quantMaquinas; ++i) {
				if( i == 0)
					fprintf(f_JOB,"(%d,", op->maquinaTempo[1*op->quantMaquinas + i]);
				else if((op->quantMaquinas - i) != 1)
					fprintf(f_JOB,"%d,", op->maquinaTempo[1*op->quantMaquinas + i]);
				else
					fprintf(f_JOB,"%d)\n", op->maquinaTempo[1*op->quantMaquinas + i]);
			}
			for(i = 0; i < op->quantMaquinas; ++i) {
				if( i == 0)
					fprintf(f_JOB,"[%d,", op->maquinaTempo[0*op->quantMaquinas + i]);
				else if((op->quantMaquinas - i) != 1)
					fprintf(f_JOB,"%d,", op->maquinaTempo[0*op->quantMaquinas + i]);
				else
					fprintf(f_JOB,"%d]\n", op->maquinaTempo[0*op->quantMaquinas + i]);
			}
		}
		op = op->seg;
	}
}

/**
* @brief Guardar os dados no ficheiro
*/
void guardaDadosFile(job *jb, char *nomeFich) {
	FILE *f_JOB = fopen(nomeFich,"w");

	if(f_JOB != NULL) {
		while(jb->seg != NULL) {
			escreveNoFich(jb->op,jb->id,f_JOB);
			jb = jb->seg;
		}
	}
	fclose(f_JOB);
}


#pragma endregion Outros



#pragma region Menu 

/**
* @brief Menu inicial para escolher as operações a realizar
*/
void menu(int *opcao) {
    int i, continuar;
	char *endptr, buf[1024];
	
	do {
		system("cls");

		printf("|-------------------- MENU --------------------|\n");
		printf("|----------------------------------------------|\n");
		printf("|INSERIR OPERACAO-----------------------------1|\n");
		printf("|LISTAR OPERACOES-----------------------------2|\n");
		printf("|REMOVER OPERACAO-----------------------------3|\n");
		printf("|EDITAR OPERACAO------------------------------4|\n");
		printf("|DETERMINAR O TEMPO MINIMO--------------------5|\n");
		printf("|DETERMINAR O TEMPO MAXIMO--------------------6|\n");
		printf("|----------------------------------------------|\n");
		printf("|LISTAR JOBS----------------------------------7|\n");
		printf("|INSERIR JOB----------------------------------8|\n");
		printf("|REMOVER JOB----------------------------------9|\n");
		printf("|INSERIR UMA OPERACAO NUM JOB----------------10|\n");
		printf("|REMOVER UMA OPERACAO NUM JOB----------------11|\n");
		printf("|EDITAR OPERACAO NUM JOB---------------------12|\n");
		printf("|SAIR----------------------------------------13|\n");
		printf("|----------------------------------------------|\n");
		printf("| OPCAO: ");

		if (!fgets(buf, sizeof(buf), stdin)) {
			continuar = 0;
		}
		errno = 0; // Vai redefenir o erro do numero
		(*opcao) = strtol(buf, &endptr, 10);
		
		if (((*opcao) > 13) || ((*opcao) < 1)) {
			printf("Por favor insira um numero entre 1 e 13.\n\n");
			system("pause");
			continuar = 0;
		}	else if ((*endptr) && (*endptr != '\n')) {
			// *endptr não é o fim da string nem na nova linha, logo entao nao convertemos o input todo
			continuar = 0;
		}	else if (endptr == buf)	{
			// Não foi lido nenhum caractere
			continuar = 0;
		}	else {
			continuar = 1;
		}
	}while(!continuar);
}

#pragma endregion Menu