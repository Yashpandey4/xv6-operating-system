#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096
#define DEBUG 0

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int
main(int argc, char *argv[]){

	#if FIFO

	int i, j;
	char *arr[14];
	char input[10];

	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE);

	arr[12] = sbrk(PGSIZE);
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE) for the 13th time, a page fault should occur and one page in swap file.\nPress any key...\n");
	gets(input, 10);

	arr[13] = sbrk(PGSIZE);
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE) for the 14th time, a page fault should occur and two pages in swap file.\nPress any key...\n");
	gets(input, 10);

	for (i = 0; i < 5; i++) {
		for (j = 0; j < PGSIZE; j++)
			arr[i][j] = 'k';
	}
	printf(1, "5 page faults should have occurred.\nPress any key...\n");
	gets(input, 10);

	if (fork() == 0) {
		printf(1, "Child code running.\n");
		printf(1, "View statistics for pid %d, then press any key...\n", getpid());
		gets(input, 10);

		arr[5][0] = 't';
		printf(1, "A page fault should have occurred for page 8.\nPress any key to exit the child code.\n");
		gets(input, 10);

		exit();
	}
	else {
		wait();

		sbrk(-14 * PGSIZE);
		printf(1, "Deallocated all extra pages.\nPress any key to exit the father code.\n");
		gets(input, 10);
	}

#elif SCFIFO
	int i, j;
	char *arr[14];
	char input[10];

	printf(1, "myMemTest: testing SCFIFO... \n");

	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	printf(1, "Called sbrk(PGSIZE) 12 times - all physical pages taken.\nPress any key...\n");
	gets(input, 10);

	arr[12] = sbrk(PGSIZE);
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE) for the 13th time, no page fault should occur and one page in swap file.\nPress any key...\n");
	gets(input, 10);

	arr[13] = sbrk(PGSIZE);
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE) for the 14th time, no page fault should occur and two pages in swap file.\nPress any key...\n");
	gets(input, 10);

	for (i = 0; i < 5; i++) {
		for (j = 0; j < PGSIZE; j++)
			arr[i][j] = 'k';
	}
	printf(1, "5 page faults should have occurred.\nPress any key...\n");
	gets(input, 10);

	if(DEBUG){
		for (i = 0; i < 5; i++) {
			printf(1, "Writing to address 0x%x\n", arr[i]);
			arr[i][0] = 'k';
		}
		gets(input, 10);
	}

	if (fork() == 0) {
		printf(1, "Child code running.\n");
		printf(1, "View statistics for pid %d, then press any key...\n", getpid());
		gets(input, 10);

		arr[5][0] = 'k';
		printf(1, "A Page fault should have occurred in child proccess.\nPress any key to exit the child code.\n");
		gets(input, 10);

		exit();
	}
	else {
		wait();

		sbrk(-14 * PGSIZE);
		printf(1, "Deallocated all extra pages.\nPress any key to exit the father code.\n");
		gets(input, 10);
	}


	#elif NFU

	int i, j;
	char *arr[27];
	char input[10];

	// TODO delete
	printf(1, "myMemTest: testing NFU... \n");

	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	printf(1, "Called sbrk(PGSIZE) 12 times - all physical pages taken.\nPress any key...\n");
	gets(input, 10);

	arr[12] = sbrk(PGSIZE);
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE) for the 13th time, no page fault should occur and one page in swap file.\nPress any key...\n");
	gets(input, 10);

	arr[13] = sbrk(PGSIZE);
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE) for the 14th time, no page fault should occur and two pages in swap file.\nPress any key...\n");
	gets(input, 10);

	for (i = 0; i < 5; i++) {
		printf(1, "Writing to address 0x%x\n", arr[i]);
		for (j = 0; j < PGSIZE; j++){
			arr[i][j] = 'k';
		}
	}
	printf(1, "5 page faults should have occurred.\nPress any key...\n");
	gets(input, 10);

	if(DEBUG){
		for (i = 0; i < 5; i++){
			printf(1, "Writing to address 0x%x\n", arr[i]);
			arr[i][0] = 'k';
		}
		//printf(1, "No page faults should have occurred.\nPress any key...\n");
		gets(input, 10);
	}

	if (fork() == 0) {
		printf(1, "Child code running.\n");
		printf(1, "View statistics for pid %d, then press any key...\n", getpid());
		gets(input, 10);

		arr[5][0] = 'k';
		//arr[5][0] = 't';
		printf(1, "Page faults should have occurred in child proccess.\nPress any key to exit the child code.\n");
		gets(input, 10);

		exit();
	}
	else {
		wait();

		sbrk(-14 * PGSIZE);
		printf(1, "Deallocated all extra pages.\nPress any key to exit the father code.\n");
		gets(input, 10);
	}


	#else
	char* arr[50];
	int i = 50;
	printf(1, "Commencing user test for default paging policy.\nNo page faults should occur.\n");
	for (i = 0; i < 50; i++) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	#endif
	exit();
}
