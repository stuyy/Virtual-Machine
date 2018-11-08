#include <stdio.h>
#include <stdlib.h>
#include "vmlib.h"

int main(int argc, char** argv)
{
  unsigned char bytes[10000]; // Allocate 10000 bytes to the unsigned char array.

  // CPU Infrastructure
  int REGISTERS[16] = {0}; // 16 Registers
  int programCounter = 0; // Program Counter
  int OP1, OP2;
  int RESULT;
  unsigned char buffer[4];

  if(argc != 2)
    printf("Invalid amount of arguments.");

  else {
    int byteCount = readFile(argv[1], bytes);
    //printf("The number of bytes read were: %d\n", byteCount);
    int flag = 1;
    while(flag)
    {
      fetch(bytes, &programCounter, &flag, buffer);
      printf("Current Instruction to Dispatch: %02x %02x\n", buffer[0], buffer[1]);
      dispatch(buffer, &OP1, &OP2, REGISTERS);
      execute(buffer, &OP1, &OP2, &RESULT, REGISTERS);
    }
  }
  return 0;
}

int readFile(char * fileName, unsigned char bytes[]) // This process is loading the memory.
{
  int i = 0;
  long fileLength;
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
// Fetch is responsible for "fetching" an instruction, and storing the bytes inside the internal buffer array.
void fetch(unsigned char * bytes, int * pCounter, int * flag, unsigned char * buffer)
{
  int instruction = bytes[*pCounter] >> 4;
  switch(instruction)
  {
    case 0: // HALT
      // Allocate 2 bytes for the buffer.
      buffer[0] = bytes[*pCounter]; // Store the first byte into buffer[0] by referencing the bytes array.
      buffer[1] = bytes[++(*pCounter)]; // Store the second byte into buffer[1], increment the pointer counter by 1.
      (*pCounter)++; // Increment the program counter by 1.
      (*flag)--; // Decrement flag, indicating to stop the program.
      break;
    case 10: // BRANCHIFEQUAL
    case 11: // BRANCHIFLESS
    case 12: // JUMP
    case 13: // ITERATEOVER
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      buffer[2] = bytes[++(*pCounter)];
      buffer[3] = bytes[++(*pCounter)];
      (*pCounter)++; // Go to the next byte.
      break;
    default: // Default Case will handle all of the 2 byte instructions.
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      (*pCounter)++; // Go to the next byte.
      break;
  }
}
// Dispatch is responsible for reading the bytes from the buffer array we created and allocated in Fetch
// Populate OP1 and OP2
void dispatch(unsigned char * buffer, int * OP1, int * OP2, int * REGISTERS)
{
  int instruction = buffer[0] >> 4;
  int offset;
  int bit;
  switch(instruction)
  {
    case 0: // HALT
      break;
    case 7: // RIGHTSHIFT, LEFTSHIFT (SFT)
    case 9: // ADDIMMEDIATE
      *OP1 = REGISTERS[(0x0F) & buffer[0]]; // The value at the specified register.
      bit = (buffer[1] & 0xF0) >> 7;
      printf("Bit: %d\n", bit);
      offset = buffer[1];
      if(bit) // if bit = 1
      {
        offset = (~(offset-1)) & ((1<<7)-1);
        offset -= (offset*2);
        *OP2 = offset;
      } else {
        *OP2 = offset;
      }
      
      printf("Offset: %d\n", offset);
      
      break;
    case 8: // INTERRUPT
      // Not sure what to do for Interrupt.
      break;
    case 14: // LOAD
    case 15: // STORE
      *OP1 = 0x0F & buffer[0]; // Get lower 4 bits by logical ANDing 0x0F with buffer[0]
      *OP2 = (0xF0 & buffer[1]) >> 4; // AND 0xF) with buffer[1] to get top 4 bits, and right shift by 4 to remove 0's.
      break;
    case 10: // Branchifless and Branchifequal
    case 11:
      *OP1 = REGISTERS[buffer[0] & (0x0F)];
      *OP2 = REGISTERS[(buffer[1] & 0xF0) >> 4];
      bit = (buffer[1] & 0x0F) >> 3;
      offset = ((((buffer[1] & 0x0F) << 8) | buffer[2]) << 8) | buffer[3];
      if(bit) // If bit is 1, then it's negative.
      {
        offset = (~(offset-1)) & ((1<<20)-1);
        offset -= (offset*2);
      }
      break;
    case 12: // JUMP
    case 13: // ITERATEOVER
      break;
    default: // Handles OPCODES 1 to 6.
      *OP1 = REGISTERS[0x0F & buffer[0]];
      *OP2 = REGISTERS[(0xF0 & buffer[1]) >> 4];
      printf("Register: %d has value %d\nRegister: %d has value %d\n", (0x0F & buffer[0]), *OP1, ((0xF0 & buffer[1]) >> 4 ), *OP2);
      break;
  }

}

void execute(unsigned char * buffer, int * OP1, int * OP2, int * RESULT, int * REGISTERS)
{
  int instruction = buffer[0] >> 4;
  int r;
  switch(instruction)
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      printf("OPCODE: %d OP1: %d OP2: %d\n", instruction, *OP1, *OP2);
      *RESULT = *OP1 + *OP2;
    break;
    case 9:
      printf("OP1: %d OP2: %d\n", *OP1, *OP2);
      *RESULT = *OP1 + *OP2;
      r = buffer[0] & 0x0F;
      REGISTERS[r] = *RESULT;
      printf("%d\n", REGISTERS[r]);
      break;
  }
}

void store(unsigned char * buffer, int * RESULT, int * REGISTERS)
{

}
