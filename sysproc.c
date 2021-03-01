#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Custom  defined system commands implementation starts here
// importing utility for 2.2 from syscall.c
extern int count_command_calls[LEN_SYSCALL];

// importing utility for 2.4 from proc.c
extern void get_process_name(void);

// declaring utility for 2.2
char *name_system_call[] = {
        "sys_fork",
        "sys_exit",
        "sys_wait",
        "sys_pipe",
        "sys_read",
        "sys_kill",
        "sys_exec",
        "sys_fstat",
        "sys_chdir",
        "sys_dup",
        "sys_getpid",
        "sys_sbrk",
        "sys_sleep",
        "sys_uptime",
        "sys_open",
        "sys_write",
        "sys_mknod",
        "sys_unlink",
        "sys_link",
        "sys_mkdir",
        "sys_close",
        "sys_toggle",
        "sys_print_count",
        "sys_add",
        "sys_ps",
        "sys_send",
        "sys_recv",
};

// System Toggle Flag: Defined for 2.1 and 2.2. 1: TOGGLE ON, 2: TOGGLE OFF
int trace_mode = 0;

/**
 * This function is used to change the state of the toggle flag (TOGGLE ON -> OFF or vice versa)
 * @return Switch the state of the trace_mode toggle flag
 */
int
sys_toggle(void)
{
    if(trace_mode == 0) // TOGGLE OFF
    {
        // Before turning Toggle ON again, we reset the counts of commands from the previous time TOGGLE was ON (if any)
        for(int i=0; i<LEN_SYSCALL; i++)
            count_command_calls[i] = 0;
        // Switch TOGGLE state to ON
        trace_mode = 1;
    }
    else // Toggle ON
        // Switch TOGGLE state to OFF
        trace_mode = 0;
    return 0;
}

/**
 * This function will print the summary of usage of the commands and respective counts
 * since last TOGGLE was turned to the ON state
 * @return <command> <frequency> printed alphabetically in ascending order
 */
int
sys_print_count(void)
{
    for(int i=1; i<LEN_SYSCALL; i++)
    {
        if(count_command_calls[i]>0)
            cprintf("%s %d\n", name_system_call[i], count_command_calls[i]);
    }
    return 0;
}

/**
 * Function implementation for Part 2.3 of the assignment
 * @param a First number to be added
 * @param b Second number to be added
 * @return sum of the two: a + b
 */
int
sys_add(int a, int b)
{
    argint(0, &a);
    argint(1, &b);
    return a+b;
}

/**
 * Function implementation for Part 2.4 of the assignment
 * @return pid:<Process-Id> name:<Process Name> - a list of all the current running processes
 */
int
sys_ps(void)
{
    get_process_name();
    return 0;
}






//struct queue_node message_queue[100];
int queue_size = 0;
extern int mq1[1000];
extern int mq2[1000];
extern void* mq3[1000];
extern int mq4[1000];



/*
* Function Implementation for Part 3.1 of the assignement
* sys_send sends the message to the buffer
* sys_recv recvs it from there..
*/
int
sys_send(int sender_pid,int rec_pid,void* msg)
{
  argint(0,&sender_pid);
  argint(1,&rec_pid);
  mq1[queue_size] = sender_pid ;
  mq2[queue_size] = rec_pid;
  mq3[queue_size] = msg;
  mq4[queue_size] = 0;
  queue_size = queue_size + 1;
  //cprintf("\nPARENT EXITED!!");
  return 0;
}


int
sys_recv(void *msg)
{
  int mypid = sys_getpid();
  //cprintf("\nRecieved pid: %d",mypid);
  for ( int i = 0 ; i<queue_size ; i++){
        if(mq2[i]==mypid && mq4[i]==0){
                  msg = (char *)mq3[i];
                  mq4[i]=1;
                  return 0;
          }
  }
  return (-1);
}
