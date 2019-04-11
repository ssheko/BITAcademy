/* Hash Table */
#ifndef HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

#define HASHSIZE 256
/* 원본 코드 */
//
//struct nlist {
//	struct nlist *next;
//	char *name;
//	char *phone;
//};
//
//
//static struct nlist *hashtab[HASHSIZE];
//
//
//unsigned hash(char *s)
//{
//	unsigned hashval = 7;
//
//
//
//	for (hashval = 0; *s != '\0'; s++)
//		hashval = *s + 31 * hashval;
//
//	return hashval % HASHSIZE;
//}
//
//
//struct nlist* lookup(char *s)
//{
//	struct nlist *np;
//
//	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
//		if (strcmp(s, np->name) == 0)
//			return np;
//	return NULL;
//}
//
//
//char *str_mcopy(char *s)
//{
//	char *p;
//	p = (char *)malloc(strlen(s) + 1);
//	if (p != NULL)
//		strcpy(p, s);
//	return p;
//}
//
//
//struct nlist* install(char *name, char *phone)
//{
//	struct nlist *np;
//	unsigned hashval;
//
//	if ((np = lookup(name)) == NULL) {
//		np = (struct nlist *) malloc(sizeof(*np));
//		if (np == NULL || (np->name = str_mcopy(name)) == NULL)
//			return NULL;
//		hashval = hash(name);
//		np->next = hashtab[hashval];
//		hashtab[hashval] = np;
//
//	}
//	else
//		free((void *)np->phone);
//
//	if ((np->phone = str_mcopy(phone)) == NULL)
//		return NULL;
//	return np;
//}
//
//int main()
//{
//
//	char *name[] = { "손나은","김태희","한지민",
//	   "문채원","전지현","문채원" };
//	char *phone[] = { "731-1234", "567-8976", "521-5030",
//	   "521-9600", "418-4165", "520-3307", "425-1024" };
//	int i, n = sizeof(name) / sizeof(name[0]);
//	struct nlist *head, *ptr;
//
//
//	for (i = 0; i < n; i++) {
//		printf("%d: %s\n", hash(name[i]), name[i]);
//
//		install(name[i], phone[i]);
//	}
//
//	printf("\nHash Table List \n");
//	for (i = 0; i < HASHSIZE; i++) {
//		head = hashtab[i];
//		for (ptr = head; ptr != NULL; ptr = ptr->next) {
//			printf("%d: %s, %s\n", i, ptr->name, ptr->phone);
//		}
//	}
//
//	printf("\nHash Table Search \n");
//	ptr = lookup("문채원");
//	printf("found: %s, %s\n", ptr->name, ptr->phone);
//
//	printf("\nPress any key to end...");
//	getchar();
//	return 0;
//}


/* 수정 코드 */
struct nlist {
	struct nlist *next;
	char *name;
	char *phone;
};


static struct nlist *hashtab[HASHSIZE];


unsigned hash(char *s)
{
	unsigned hashval = 7;



	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}


struct nlist* lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}


char *str_mcopy(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}


struct nlist* install(char *name, char *phone)
{
	//struct nlist *np, *newnp;
	struct nlist *np;
	unsigned hashval;

	// 핵심은 lookup을 쓰지 않는 것
	np = (struct nlist *) malloc(sizeof(*np)); 
	if (np == NULL || (np->name = str_mcopy(name)) == NULL)
		return NULL;
	hashval = hash(name);					  
	np->next = hashtab[hashval];
	hashtab[hashval] = np;

	if ((np->phone = str_mcopy(phone)) == NULL)
		return NULL;

	//if ((np = lookup(name)) == NULL) {
	//	np = (struct nlist *) malloc(sizeof(*np));
	//	if (np == NULL || (np->name = str_mcopy(name)) == NULL)
	//		return NULL;
	//	hashval = hash(name);
	//	np->next = hashtab[hashval];
	//	hashtab[hashval] = np;

	//	if ((np->phone = str_mcopy(phone)) == NULL)
	//		return NULL;
	//}
	//else {
	//	newnp = (struct nlist *) malloc(sizeof(*newnp));
	//	if (newnp == NULL || (newnp->name = str_mcopy(name)) == NULL)
	//		return NULL;
	//	hashval = hash(name);
	//	newnp->next = np;
	//	hashtab[hashval] = newnp;
	//	//newnp->next = np->next;
	//	//np->next = newnp;
	//	if ((newnp->phone = str_mcopy(phone)) == NULL)
	//		return NULL;
	//}
		//free((void *)np->phone);

	return np;
}

int main()
{

	char *name[] = { "손나은","김태희","한지민",
	   "문채원","전지현","문채원" };
	char *phone[] = { "731-1234", "567-8976", "521-5030",
	   "521-9600", "418-4165", "520-3307", "425-1024" };
	int i, n = sizeof(name) / sizeof(name[0]);
	struct nlist *head, *ptr;


	for (i = 0; i < n; i++) {
		printf("%d: %s\n", hash(name[i]), name[i]);

		install(name[i], phone[i]);
	}

	printf("\nHash Table List \n");
	for (i = 0; i < HASHSIZE; i++) {
		head = hashtab[i];
		for (ptr = head; ptr != NULL; ptr = ptr->next) {
			printf("%d: %s, %s\n", i, ptr->name, ptr->phone);
		}
	}

	printf("\nHash Table Search \n");
	ptr = lookup("문채원");
	//for(ptr; ptr != NULL; ptr = ptr->next){
	while(ptr != NULL){
		printf("found: %s, %s\n", ptr->name, ptr->phone);
		ptr = ptr->next;
	}

	printf("\nPress any key to end...");
	getchar();
	return 0;
}
