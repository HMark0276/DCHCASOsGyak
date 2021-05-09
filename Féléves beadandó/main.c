#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mesg_buffer {
    long mesg_type;
    double a;
    double b;
    double m;

} message;

int lnko(double x, double y);
void kuldes(double a,double b, double m);

int main(){

   double input[2]; // a, b
   int szamparok;

   FILE *fp = fopen("bemenet.txt","r");
   if (fp < 0){
        perror("Hiba üres a file");
        exit(-1);
   }
   fscanf(fp,"%d",&szamparok);
   printf("A fileban talalhato szamparok... %d \n",szamparok);
   for(int i = 0; i < szamparok; i++){
        for(int k = 0; k < 2; k++){
            fscanf(fp,"%lf",&input[k]);
        }

        double m = lnko(input[0], input[1]);
        kuldes(input[0], input[1], m);
        printf("%d. szampar: a = %.2lf, b=%.2lf, m=%.2lf \n",i + 1,input[0],input[1], m);
   }

   fclose(fp);

   return 0;
}

int lnko(double x, double y){


  if (x == 0) {
    return y;
  }

  while (y != 0) {
    if (x > y)
      x = x - y;
    else
      y = y - x;
  }

    return x;


}
void kuldes(double a, double b, double m){

	key_t key;
	key = ftok("progfile", 65);
	int msgid = msgget(key, 0666 | IPC_CREAT);
	printf("msgid: %d\n", msgid);
	message.mesg_type = 1;

	message.a = a;
	message.b = b;
	message.m = m;

    msgsnd(msgid, &message, sizeof(message), 0);
    printf("LNKO: a = %.2lf, b=%.2lf,  lnko=%.2lf\n",a,b,m);
}
