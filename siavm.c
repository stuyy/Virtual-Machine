#include <stdio.h>
#include <stdlib.h>
#include "vmlib.h"

int main(int argc, char** argv)
{
  unsigned char bytes[10000]; // Allocate 10000 bytes to the unsigned char array.

  // Create 16 registers.
  int registers[16];
  int programCounter = 0;
  int OPERANDS[3]; // OP1, OP2, and RESULT in respective order.

  if(argc != 2)
    printf("Invalid amount of arguments.");

  else {
    int byteCount = readFile(argv[1], bytes);
    printf("The number of bytes read were: %d\n", byteCount);
    int flag = 1;
    while(flag)
    {
      // Call Fetch, pass in the byte array, the address of the program counter, and the address of the flag.
      unsigned char * buffer = fetch(bytes, &programCounter, &flag);
      // Call Dispatch. Dispatch will execute the instruction that was previously fetched from "fetch".
      dispatch(buffer, OPERANDS);
      printf("OP1 = %x OP2 = %x and RESULT = %x\n", OPERANDS[0], OPERANDS[1], OPERANDS[2]);
      // Call Execute.
      // Call Store.
    }
  }
  return 0;
}

int readFile(char * fileName, unsigned char bytes[]) // This process is loading the memory.
{
  int i = 0;
  FILE * file = fopen(fileName, "rb"); // Open the file and read it in in binary mode.
  if(file == NULL)
    printf("There was an error reading the file %s\n", fileName);
  else {
    int c;
    while((c = fgetc(file)) != EOF)
      bytes[i++] = (unsigned char)c; // Populate the array.
  }
  return i; // Return the total number of bytes read.
}

unsigned char * fetch(unsigned char * bytes, int * pCounter, int * flag)
{
  unsigned char * buffer;
  int instruction = bytes[*pCounter] >> 4;
  switch(instruction)
  {
    case 0: // HALT
      buffer = malloc(2);
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      (*pCounter)++;
      (*flag)--;
      return buffer;
    case 1: // ADD
    case 2: // AND
    case 3: // DIVIDE
    case 4: // MULTIPLY
    case 5: // SUBTRACT
    case 6: // OR
    case 7: // RIGHTSHIFT, LEFTSHIFT (SFT)
    case 8: // INTERRUPT
    case 9: // If the instruction is ADDIMMEDIATE, read 2 bytes.
    case 14: // LOAD
    case 15: // STORE
      buffer = malloc(2);
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      (*pCounter)++; // Go to the next byte.
      return buffer;
    case 10: // BRANCHIFEQUAL
    case 11: // BRANCHIFLESS
    case 12: // JUMP
    case 13: // ITERATEOVER
      buffer = malloc(4);
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      buffer[2] = bytes[++(*pCounter)];
      buffer[3] = bytes[++(*pCounter)];
      (*pCounter)++; // Go to the next byte.
      return buffer;
  }
  return NULL;
}

void dispatch(unsigned char * buffer, int OPERANDS[])
{
  int instruction = buffer[0] >> 4;
  switch(instruction)
  {
    case 1: // ADD
    case 2: // AND
    case 3: // DIVIDE
    case 4: // MULTIPLY
    case 5: // SUBTRACT
    case 6: // OR
    case 7: // RIGHTSHIFT, LEFTSHIFT (SFT)
    case 8: // INTERRUPT
    case 9: // If the instruction is ADDIMMEDIATE, read 2 bytes.
    case 14: // LOAD
    case 15: // STORE
      printf("Buffer: %x\n", buffer[0]);
      OPERANDS[0] = 0x0F & buffer[0]; // Get lower 4 bits by logical ANDing 0x0F with buffer[0]
      OPERANDS[1] = (0xF0 & buffer[1]) >> 4; // AND 0xF) with buffer[1] to get top 4 bits, and right shift by 4 to remove 0's.
      OPERANDS[2] = 0x0F & buffer[1]; // Get lower 4 bits of buffer[1] by ANDing 0x0F.
    break;
    case 10:
    case 11:
    case 12:
    case 13:

      break;
  }

  if(buffer[0] != 0x00 && buffer[1] != 0x00 && buffer[3] == 0x00 && buffer[4] == 0x00)
    printf("%02x %02x %02x %02x\n", 0x00, 0x00, buffer[0], buffer[1]);
  else
    printf("%02x %02x %02x %02x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
}
