#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct nodo
{
	int val;
	struct nodo* next;
};
struct nodo* testa = NULL;
struct nodo* app = NULL;
struct nodo* temp = NULL;
int count = 0;
int val = 5;
struct nodo* insert(struct nodo*, void*, struct nodo**, struct nodo**);
struct nodo* view(struct nodo*, void**);
int indexer = 0;
bool check = false;
bool flag = false;
int main(int argc, char **argv)
{
	struct nodo** array = (struct nodo**)malloc(sizeof(struct nodo)*5);
	struct nodo** free_memory = (struct nodo**)malloc(sizeof(struct nodo*)*5);
	void** ptr = (void**)malloc(sizeof(void*)*2);
	ptr[0] = &val;
	ptr[1] = &indexer;				

	bool fine = false;
	void* cont = &count;
	int scelta;
	do{
		puts(" ");
		printf("1. Insert in list circular [*] \n");
		printf("2. View list circular [*] \n");
		printf("9. Aborted [*] \n");
		scanf("%d",&scelta);
		switch(scelta)
		{
		case 1:
			{
				count = count + 1;
				testa = insert(testa,cont,array,free_memory);
			}break;
		case 2:
			{
				testa = view(testa,ptr);
			}break;
		default	:
			{
				fine = true;
			}
		}
	}while(fine != true);
	return 0;
}
struct nodo* insert(struct nodo* testa, void* counter, struct nodo** array, struct nodo** free_memory)
{
	int valore;
	int contatore_interno = 0;
	int contatore = *(int*)counter;
	printf("Insert value: ");
	scanf("%d", &valore);
	struct nodo* nuovo_nodo = malloc(sizeof(struct nodo));
	nuovo_nodo->val = valore;
	if(testa == NULL)
	{
		testa = nuovo_nodo;
		app = testa;
		free_memory[contatore-1] = testa;
		printf("Address in free _memory[%d] = %p - Dereferenziato = %d  \n",contatore-1, free_memory[contatore-1], *(int*)free_memory[contatore-1]);
	}
	else
	{
		if(indexer==4)
		{
			printf("- free_memory[%d] - \n", indexer);
			free(free_memory[indexer]);
			free_memory[indexer] = nuovo_nodo;
			flag = true;
			indexer = 0;
		}
		if((check==true)&&(contatore!=6))
		{
			printf("Array_link[%d] = %p - Dereferenziato = %d \n",indexer, array[indexer], *(int*)array[indexer]); //li mantiene salvati, ok
			app->next = nuovo_nodo;
			nuovo_nodo->next = array[indexer];
			array[indexer-1] = app->next;
			app = nuovo_nodo;
			if(flag==false)
			{
				printf("- free_memory[%d] - \n", indexer);
				free(free_memory[indexer]);
				free_memory[indexer] = nuovo_nodo;
			}
			indexer = indexer + 1;
			flag = false;
		}
		if(contatore==6)
		{
			indexer = 0;
			check = true;
			testa = nuovo_nodo;
			temp = app->next;
			app->next = nuovo_nodo;
			app = testa;
			app->next = array[indexer];
			array[indexer] = temp;
			printf("- free_memory[%d] - \n", contatore-6);
			free(free_memory[contatore-6]);
			free_memory[contatore-6] = nuovo_nodo;
			count = 1;
			indexer = indexer + 1;
		}
		else if(check==false)
		{
			app->next = nuovo_nodo;
			free_memory[contatore-1] = nuovo_nodo;
			printf("Node address free_memory[%d] = %p - Dereferenziato = %d \n", contatore-1, free_memory[contatore-1], *(int*)free_memory[contatore-1]);
			array[contatore-2] = app->next; //save link
			printf("Array_link[%d] = %p - Dereferenziato = %d \n", contatore-2, array[contatore-2], *(int*)array[contatore-2]); //li mantiene salvati, ok
			app = nuovo_nodo;	
		}
	}
	return testa;
}
struct nodo* view(struct nodo* testa, void** ptr)
{
	int tot = *(int*)ptr[0]; // tot = 5
	puts(" ");
	struct nodo* appo = testa;
	while((appo!=NULL)&&(tot-->0))
	{
		printf(" - [%d] ", appo->val );
		appo = appo->next;
	}
	puts(" ");
	return testa;
}