#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} rcvbuf, *msgp;

struct msqid_ds ds, *buf;

int main()
{
	int msgid;
	key_t key;
	int mtype, msgflg;
	int rtn, msgsz;
	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(key, msgflg);    
 	if (msgid == -1) 
        {
            perror(" msgget hivas nem sikerult.\n");
            exit(-1);
        }

	printf(" msgid... %d\n", msgid);

	msgp = &rcvbuf;
	buf = &ds;
	msgsz = 20;
	mtype = 0;
	rtn = msgctl(msgid, IPC_STAT, buf);

	printf(" Uzenetek szama... %d\n", buf->msg_qnum);
	
	while (buf->msg_qnum) 
        {
            rtn = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
            printf(" rtn... %d, vett uzenet... %s\n", rtn, msgp->mtext);
            rtn = msgctl(msgid,IPC_STAT,buf);
        }
	exit (0);
}