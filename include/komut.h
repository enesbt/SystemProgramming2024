#ifndef KOMUT_H
#define KOMUT_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


void yaz(int fd ,char* c,int count);
void sil(int fd,char* c,int count);
void sonagit(int fd);
void tersine_cevir(char *karakter_dizisi);

#endif