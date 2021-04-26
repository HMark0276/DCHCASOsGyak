#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#define MSGKEY 654321L 

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

int main()
{
	int msgid;
	key_t key;
	int msgflg;
	int rtn, msgsz;

	key=MSGKEY;
	msgflg=msgget(key,msgflg);

	if(msgid==-1)
	{
		perror("msgget hivas nem sikerult.\n ");
		exit(-1);
	}
	printf("msgid...%d, %x : \n ",msgid,msgid);

	msgp=&sndbuf;
	msgp->mtype=1;
	strcpy(msgp->mtext, "Nev: Hengsperger Mark\n ");
	msgsz=strlen(msgp->mtext)+1;
	rtn=msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("Elso msgsnd visszaadott...%d-t\n ", rtn);
	printf("Uzenet... %s\n ",msgp->mtext);
	strcpy(msgp->mtext, "NEPTUN kod: DCHCAS\n ");
	msgsz=strlen(msgp->mtext)+1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("Masodik  msgsnd visszaadott...%d-t\n ", rtn);
	printf("Uzenet... %s\n ", msgp->mtext);
	exit (0);
}





