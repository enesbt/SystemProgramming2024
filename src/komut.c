#include "komut.h"

void yaz(int fd ,char* c,int count)
{   
    int i;
    if(strcmp(c,"\n"))
    {
        for(i = 0; i<count; i++)
            write(fd,"\n", strlen("\n"));
    }
        
    // else if(c == "\b")
    //     for(i = 0; i<count; i++)
    //         write(fd,"\b", strlen("\b"));
    else
        for(i = 0; i<count; i++)
            write(fd,c, strlen(c));

}