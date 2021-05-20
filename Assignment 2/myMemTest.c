#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#define PGSIZE 4096
#define ARR_SIZE 55000

/**
 * 	Test used to check the swapping machanism in fork.
 *	Best tested when LIFO is used (for more swaps)
 */
void forkTest(){
    int i;
    char * arr;
    arr = malloc (50000);

    for (i = 0; i < 50; i++) {
        arr[49100+i] = 'A';
        arr[45200+i] = 'B';
    }
    arr[49100+i] = 0;
    arr[45200+i] = 0;

    if (fork() == 0){
        for (i = 40; i < 50; i++) {
            arr[49100+i] = 'C';
            arr[45200+i] = 'D';
        }
        printf(1, "SON: %s\n",&arr[49100]);
        printf(1, "SON: %s\n",&arr[45200]);
        printf(1,"\n");
        free(arr);
        exit();
    } else {
        wait();
        printf(1, "PARENT: %s\n",&arr[49100]);
        printf(1, "PARENT: %s\n",&arr[45200]);
        free(arr);
    }

}

/**
 * Generates Random Number
 */
static unsigned long int next = 1;
int getRandNum() {
    next = next * 1103515245 + 12341;
    return (unsigned int)(next/65536) % ARR_SIZE;
}

#define PAGE_NUM(addr) ((uint)(addr) & ~0xFFF)
#define TEST_POOL 500

/**
Global Test:
Allocates 17 pages (1 code, 1 space, 1 stack, 14 malloc)
Using pseudoRNG to access a single cell in the array and put a number in it.
 */
void globalTest(){
    char * arr;
    int i;
    int randNum;
    arr = malloc(ARR_SIZE);
    for (i = 0; i < TEST_POOL; i++) {
        randNum = getRandNum();
        while (PGSIZE*10-8 < randNum && randNum < PGSIZE*10+PGSIZE/2-8)
            randNum = getRandNum();

        arr[randNum] = 'X';
    }
    free(arr);
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
    globalTest();
    forkTest();
    exit();
}