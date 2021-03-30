#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fp, ret;
    char buf[45];

    buf[0] = 0;

    fp = open("DCHCAS.txt", O_RDWR);

    printf("Beolvasas...");

    if (fp != -1){
        printf("sikeres\n");
    }
    else {
        printf("sikertelen\n");
        exit(-1);
    }

    ret = read(fp, buf, 45);
    printf("\nread() eredmenye:\n-beolvasott byte-ok...%d\n-tartalom: %s\n", ret, buf);

    ret = lseek(fp, 0, SEEK_SET);
    printf("\nlseek() eredmenye...%d\n", ret);

    ret = write(fp, buf, 6);
    printf("\nwrite() eredmenye...%d\n", ret);

    close(fp);

    return 0;
}
