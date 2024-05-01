#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "komut.h"
//dosya isimlerini argv al
//satir satir oku
//komuta göre sonuc dosyasına yaz

int main(int argc, char **argv)
{
  test();
  printf("test bitt\n");
  IS is;
  int i;

  //if (argc != 2) { fprintf(stderr, "usage: printwords filename\n"); exit(1); }
 
  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

  /* Read each line with get_line().  Print out each word. */

  while(get_line(is) >= 0) {
    for (i = 0; i < is->NF; i++) {
      printf("%d: %s\n", is->line, is->fields[i]);
    }
  }

  /* Free up the memory allocated with new_inputstruct, and
     close the open file.  This is not necessary in this program, 
     since we are exiting anyway, but I just want to show how you free it up. */

  jettison_inputstruct(is);
  // int fd;

  int fd,sz;
  fd = open("./sonuc.txt",O_RDWR|O_CREAT|O_TRUNC);
  
  sz = write(fd, "aaaabbbcckc ss kkk", strlen("aaaabbbkcckc ss kkk"));



  //son konum
  lseek(fd,0,SEEK_END);
  char* c;

  c = (char *) malloc(2 * sizeof(char));
  int hh = 0;
  
  //bir bayt geri git sonra oku
  while (lseek(fd, -1, SEEK_CUR) != -1)
  {
    sz = read(fd, c, 1);
    c[sz] = '\0';
    off_t currentPosition = lseek(fd, -1, SEEK_CUR);
    //0kez silincekse girme

    if(c[0]=='a')
    {
      
          hh++;
          // eslesen karakter konum 
          
          // 'b' karakterinin sonrasından itibaren dosyayı okuyup b'nin üzerine yazalım
          off_t fileSize = lseek(fd, 0, SEEK_END); // Dosyanın boyutunu al
          off_t remainingSize = fileSize - currentPosition - 1; // karakterinin sonrasından itibaren dosyanın geri kalan boyutu
          char *buffer = (char *)malloc(remainingSize); // Dosyanın geri kalanını okumak için bellek ayır

          // 'b' karakterinin sonrasından itibaren dosyanın geri kalanını oku
          if (lseek(fd, currentPosition + 1, SEEK_SET) == -1) { // 'b' karakterinin sonrasına git
              perror("lseek");
              exit(1);
          }

          sz = read(fd, buffer, remainingSize);
          if (sz == -1) {
              perror("read");
              exit(1);
          }
          

          // 'b' karakterinin üstüne dosyanın geri kalanını yaz
          if (lseek(fd, currentPosition, SEEK_SET) == -1) { // 'b' karakterinin olduğu yere git
              perror("lseek");
              exit(1);
          }

          sz = write(fd, buffer, remainingSize); // 'b' karakterinin sonrasından itibaren dosyanın geri kalanını yaz
          if (sz == -1) {
              perror("write");
              exit(1);
          }

          // // Dosyanın sonundaki fazla veriyi sil
          if (ftruncate(fd, lseek(fd, 0, SEEK_CUR)) == -1) { // Dosyanın boyutunu güncelle
              perror("ftruncate");
              exit(1);
          }
          printf("buffer:%s \n",buffer);
          free(buffer); // Belleği serbest bırak
          lseek(fd, currentPosition, SEEK_CUR);
          
    }
    //lseek(fd,0,SEEK_CUR);
    if(hh==2) //kaç tane silinecek
    {
      //lseek(fd,0,SEEK_CUR)
      //kaldigi yere al
      lseek(fd,currentPosition,SEEK_SET);
      break;
    }
    printf("Those bytes are as follows: %s\n", c);
  }

   char *y;
   y= (char*)malloc(20*sizeof(char));
  // sz = write(fd,"xxxx",4);

  //basa al
  lseek(fd,0,SEEK_SET);
  sz = read(fd,y,20);

  printf("son hali: %s\n",y);
  //printf("called read(%d, c, 1).  returned that %d bytes  were read.\n", fd, sz);

  //c[sz] = '\0';
  //printf("Those bytes are as follows: %s\n", c);





  //SEEK_SET BAŞTAN 
  //SEEK_CUR şuandan
  //SEEK_END dosya sonundan
  //lseek(fd,100,SEEK_SET);
  // const char* data = "hello world !";
  // sz = write(fd,data,strlen(data));



  
  return 0;
}