#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "komut.h"
// dosya isimlerini argv al
// satir satir oku
// komuta göre sonuc dosyasına yaz


int main(int argc, char **argv)
{

  IS is;
  int i;
  int fd;

  
  // if(argc  !=  2 ){
  //   fprintf(stderr, "Eksik girildi, varsayilan dosyalar kullaniliyor.");
  //   is = new_inputstruct("giris.dat");
  //   fd = open("cikis.dat",O_RDWR|O_CREAT|O_TRUNC);
  // }else{
  //   is  = new_inputstruct(argv[1]);
  //   fd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC);
  // }
  is = new_inputstruct("data.txt");
  fd = open("cikis.txt", O_RDWR | O_CREAT | O_TRUNC);

  /* Open the file as an inputstruct.  Error check. */

  // is = new_inputstruct(argv[1]);
  //  if (is == NULL) {
  //    perror(argv[1]);
  //    exit(1);
  //  }


  int adet = 0;
  char *karakter;
  char *karakter2;
  while (get_line(is) >= 0)
  {
    if (strcmp(is->fields[0], "yaz:") == 0) //yaz komutu
    {
      for (i = 1; i < is->NF; i++)
      {
        adet = atoi(is->fields[i]);
        karakter = is->fields[++i];
        yaz(fd,karakter,adet);
      }
    }
    else if(strcmp(is->fields[0],"sil:")==0) //sil komutu
    {
      for (i = 1; i < is->NF; i++)
      {
        adet = atoi(is->fields[i]);
        karakter = is->fields[++i];
        sil(fd,karakter,adet);
      }
    }
    else if(strcmp(is->fields[0],"sonagit:")==0) //sonagit komutu
    {
        sonagit(fd);
    }
    else if(strcmp(is->fields[0],"dur:")==0) //dur komutu
    {
      jettison_inputstruct(is);
      close(fd);
      break;
    }
   
  }


  

  return 0;
}