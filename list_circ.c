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
int count = 0;
int val = 5;
struct nodo* insert(struct nodo*, void*, struct nodo**);
struct nodo* view(struct nodo*, void**);
int indexer = 0;
bool check = false;
int main(int argc, char **argv)
{
	struct nodo** array = (struct nodo**)malloc(sizeof(struct nodo)*5);
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
				testa = insert(testa,cont,array);
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
struct nodo* insert(struct nodo* testa, void* counter, struct nodo** array)
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
	}
	else
	{
		if(indexer==4)
			indexer = 0;
		if((check==true)&&(contatore!=6))
		{
			printf("Array_link[%d] = %p - Dereferenziato = %d \n",indexer, array[indexer], *(int*)array[indexer]); //li mantiene salvati, ok
			app->next = nuovo_nodo;
			nuovo_nodo->next = array[indexer];
			array[indexer] = app->next;
			app = nuovo_nodo;
			indexer = indexer + 1;
		}
		if(contatore==6)
		{
			check = true;
			testa = nuovo_nodo;
			app->next = nuovo_nodo;
			array[indexer+4] = app->next;
			app = testa;
			app->next = array[indexer];
			printf("Array_link[%d] = %p - Dereferenziato = %d \n",indexer+4, array[indexer+4], *(int*)array[indexer+4]); //li mantiene salvati, ok
			count = 1;
			indexer = indexer + 1;
		}
		else if(check==false)
		{
			app->next = nuovo_nodo;
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