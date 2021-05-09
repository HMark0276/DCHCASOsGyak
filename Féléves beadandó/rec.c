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

void file(double a, double b, double m);

int main()
{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("msgid: %d\n", msgid);
    if(msgid == -1){
        perror("msget");
        exit(1);
    for(;;){

        if(msgrcv(msgid, &message, sizeof(message), 1, 0) == -1){
            perror("msgrcv");
            exit(1);
        }

        file(message.a,message.b,message.m);
        printf("File-ba irt szoveg: \n");
        printf("LNKO: a = %.2lf, b=%.2lf,  lnko=%.2lf\n",message.a,message.b,message.m);


    }
    msgctl(msgid, IPC_RMID, NULL);
    printf("Vege\n");

    return 0;
}

void file(double a, double b, double m){

    FILE *file_to_write = fopen("vege.txt","a");

    if (file_to_write < 0){
        perror("Hiba, ures a file");
        exit(-1);
    }

    printf("Sikeres file kiiras\n");

    fprintf(file_to_write,"LNKO: a = %.2lf, b=%.2lf,  lnko=%.2lf\n",message.a,message.b,message.m);

    fclose(file_to_write);
}
