#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	if(argc< 2){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename=argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;	

	int size=1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]=c-'0';
		read(fd, &c, 1);
	}	
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);
  
  	//----FILL THE CODE HERE for unicast sum
  	
  	
  	
  	
  	
  	
  	
  	
  	
  	
  	
 /* 	

	int master = getpid();
	int slave[8];
	for(int i=0; i<NUM_PROCS; ++i)
	{
	slave[i] = fork();
	if(slave[i] == 0)
	{
	    int sum = 0;
	    int start = size/NUM_PROCS * i;
	    int end = i == NUM_PROCS - 1 ? size : size/NUM_PROCS * (i+1);
	    for(int j = start; j < end; j++)
	    {
		sum += arr[j];
	    }
	    char *message = encode_message(sum);
	    send(getpid(), master, message);
	    exit();
	}
	}
	for(int i=0; i<NUM_PROCS; ++i)
	{
	char *message = (char *)malloc(8);
	recv(message);
	int sum = 0;
	sum = extract(message);
	tot_sum += sum;
	}



*/





  	//------------------

  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}
	exit();
}


/**
 * This function extracts the integer value of the message recieved in the string form
 * @param message - string representation of the message
 * @return Integer value
 */
int extract(char *message) {
    int res = 0;
    int idx = -1;
    char *msg = (char *)message;
    while(*(msg + idx) != '\0')
        idx += 1;
    while(idx >= 0)
    {
        res *= 10;
        res += (*(msg + idx) - '0');
        idx -= 1;
    }
    return res;
}

/**
 * This function takes in the sum and converts it to a string to be sent as a message
 * @param sum - integer value of the message
 * @return String representation of the message
 */
char *encode_message(int sum)
{
    int t = sum;
    int idx = 0;
    char *msg = (char *)malloc(8);
    while(t>0)
    {
        *(msg + idx) = '0' + (t%10);
        t /= 10;
        idx += 1;
    }
    *(msg + idx) = '\0';
    return msg;
}
