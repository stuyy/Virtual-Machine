#include <stdio.h>
#include "vmlib.h"

int main(int argc, char** argv)
{
  unsigned char bytes[10000];
  if(argc != 2)
    printf("Invalid amount of arguments.");

  else {
    int byteCount = readFile(argv[1], bytes);
    printf("The number of bytes read were: %d\n", byteCount);
  }
  return 0;
}

int readFile(char * fileName, unsigned char bytes[])
{
  int i = 0;
  FILE * file = fopen(fileName, "rb"); // Open the file and read it in in binary mode.
  if(file == NULL)
    printf("There was an error reading the file %s\n", fileName);
  else {
    int c;
    while((c = fgetc(file)) != EOF)
      bytes[i++] = (unsigned char)c;
  }
  return i;
}
