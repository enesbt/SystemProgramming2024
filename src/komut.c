#include "komut.h"

void tersine_cevir(char *karakter_dizisi) 
{
    char temp = karakter_dizisi[0];
    karakter_dizisi[0] = karakter_dizisi[1];
    karakter_dizisi[1] = '/';
}

void sonagit(int fd)
{
    lseek(fd,0,SEEK_END);
}


void yaz(int fd ,char* c,int count)
{   
    char* c2;
    if(strlen(c)==2)
    {
        c2  = c;
        tersine_cevir(c2);         
    }

    int j;
         
       
    if (strcmp(c, "n/") == 0) 
    {
        for (j = 0; j < count; j++)
        {
            write(fd, "\n", strlen("\n"));

        }
        
    }   
    else if(strcmp(c,"b/")==0)
    {
        for (j = 0; j < count; j++)
        {
            write(fd, "\b", strlen("\b"));

        }
    }
        else{
        for (j = 0; j < count; j++)
        {
            write(fd, c, strlen(c));

        }
    
    }
   

}


void sil(int fd,char* c,int count)
{
    char* c2;
    c2 = (char *) malloc(2 * sizeof(char));
    int hh = 0;
    int sz;
    //bir bayt geri git sonra oku
    while (lseek(fd, -1, SEEK_CUR) != -1)
    {
        sz = read(fd, c2, 1);
        c2[sz] = '\0';
        off_t currentPosition = lseek(fd, -1, SEEK_CUR);

        if(strcmp(c2,c)==0)
        {

            hh++;
            // eslesen karakter konum

            // secilen karakterden sonrasını okuyup silecenk uzerine yazilir
            off_t fileSize = lseek(fd, 0, SEEK_END); // Dosyanın boyutunu al
            off_t remainingSize = fileSize - currentPosition - 1; // karakterinin sonrasından itibaren dosyanın geri kalan boyutu
            char *buffer = (char *)malloc(remainingSize); // Dosyanın geri kalanını okumak için bellek ayır

            // karakter sonrasından itibaren dosyanın geri kalanını oku
            if (lseek(fd, currentPosition + 1, SEEK_SET) == -1) { 
                perror("lseek");
                exit(1);
            }

            sz = read(fd, buffer, remainingSize);
            if (sz == -1) {
                perror("read");
                exit(1);
            }

            
            if (lseek(fd, currentPosition, SEEK_SET) == -1) {
                perror("lseek");
                exit(1);
            }

            sz = write(fd, buffer, remainingSize); // seçilen karakterden sonrasından itibaren dosyanın geri kalanını yaz
            if (sz == -1) {
                perror("write");
                exit(1);
            }

            // // Dosyanın sonundaki fazla veriyi sil
            if (ftruncate(fd, lseek(fd, 0, SEEK_CUR)) == -1) { // Dosyanın boyutunu güncelle
                perror("ftruncate");
                exit(1);
            }
            //printf("buffer:%s \n",buffer);
            free(buffer); // Belleği serbest bırak
            lseek(fd, currentPosition, SEEK_CUR);

        }
        //lseek(fd,0,SEEK_CUR);
        if(hh==count) //kaç tane silinecek
        {
            //kaldigi yere al
            lseek(fd,currentPosition,SEEK_SET);
            break;
        }
        //printf("Those bytes are as follows: %s\n", c);
    }
}
