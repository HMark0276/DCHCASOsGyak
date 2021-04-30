#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

struct msqid_ds ds, *buf;

int main()
{
	int msgid;
	key_t key;
	int msgflg;
	int rtn;
    int msgsz;

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);

 	if ( msgid == -1) 
    {
        perror("msgget rendszerhívás sikertelen\n");
         exit(-1);
    }


	msgp = &sndbuf;
	msgp->mtype = 1;
 	strcpy(msgp->mtext,"Hengsperger Mark, DCHCAS");
	msgsz = strlen(msgp->mtext) + 1;
    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

    if (msgp->mtext == "exit")
    {
        exit(0);
    }


	key_t kulcs;
	int tipus;
	int meret;

	kulcs = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);
 	if ( msgid == -1)
    {
        perror("msgget rendszerhivas sikertelen\n");
         exit(-1);
    }

	printf("uzenet ID... %d\n",msgid);

	msgp = &sndbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);

	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	rtn = msgctl(msgid,IPC_STAT,buf);

    do{
        printf("valasszon a menusorbol\n");
        printf("(0) uzenetek szama\n");
        printf("(1) elso uzenet kiolvasasa\n");
        printf("(2) uzenetsor megszuntetese\n");
        printf("(3) kilepes\n");
        scanf("%d", &msgid);
    }while(msgid < 0 || msgid > 3);

  switch(msgid)
  {
    case 0:
        printf("uzenetek szama... %ld\n",buf->msg_qnum);
        break;

    case 1:
        printf("uzenet... %s\n", msgp->mtext);
        break;

    case 2:
        rtn = msgctl(msgid, IPC_RMID, NULL);
        printf("kilepes... \n");
        break;

    case 3:
        exit(0);
  }
}