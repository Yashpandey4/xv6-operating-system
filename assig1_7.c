#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
	printf(1,"%s\n","IPC Test case");
	
	int MSGSIZE = 8;
	
	int cid = fork();
	if(cid==0){
		// This is child
		char *msg = (char *)malloc(MSGSIZE);
		int stat=-1;
		while(stat==-1){
			stat = recv(msg);
		}
		printf(1,"2 CHILD: msg recv is: %s \n", msg );
		exit();
		
	}else{
		// This is parent
		char *msg_child = (char *)malloc(MSGSIZE);
//		char s = 'S';
		msg_child = "P";
//		printf(1,msg_child);
//		printf(1,s);
		printf(1,"1 PARENT: msg sent is: %s \n", msg_child );
		send(getpid(),cid,msg_child);
		wait();
		
		free(msg_child);
	}
	
	exit();
}
