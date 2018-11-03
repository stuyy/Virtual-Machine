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
      // Call Fetch, pass in the byte array, the address of the program counter, and the address of the flag.
      fetch(bytes, &programCounter, &flag, buffer);
      // Call Dispatch. Dispatch will execute the instruction that was previously fetched from "fetch".
      dispatch(buffer, &OP1, &OP2, REGISTERS);
      execute(buffer, &OP1, &OP2, &RESULT, REGISTERS);

      // Call Execute.
      // Call Store.
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
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      (*pCounter)++; // Go to the next byte.
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
  }
}
// Dispatch is responsible for reading the bytes from the buffer array we created and allocated in Fetch
// Populate OP1 and OP2
void dispatch(unsigned char * buffer, int * OP1, int * OP2, int * REGISTERS)
{
  int tempOne, tempTwo;
  int instruction = buffer[0] >> 4;
  switch(instruction)
  {
    case 1: // ADD
    case 2: // AND
    case 3: // DIVIDE
    case 4: // MULTIPLY
    case 5: // SUBTRACT
    case 6: // OR
      //*OP1 = 0x0F & buffer[0]; // Get the register number.
      // We want to get the register number, and get the value of that register.
      tempOne = 0x0F & buffer[0]; // Get the register number.
      tempTwo = (0xF0 & buffer[1]) >> 4; // Get the second register number.
      printf("REG: %x %x\n", tempOne, tempTwo);
      *OP1 = REGISTERS[tempOne];
      *OP2 = REGISTERS[tempTwo];
      break;
    case 7: // RIGHTSHIFT, LEFTSHIFT (SFT)
    case 8: // INTERRUPT
    case 9: // ADDIMMEDIATE
      tempOne = (0x0F) & buffer[0];
      *OP1 = REGISTERS[tempOne]; // The value at the specified register.
      *OP2 = buffer[1]; // The value to add.
    break;
    case 14: // LOAD
    case 15: // STORE
      *OP1 = 0x0F & buffer[0]; // Get lower 4 bits by logical ANDing 0x0F with buffer[0]
      *OP2 = (0xF0 & buffer[1]) >> 4; // AND 0xF) with buffer[1] to get top 4 bits, and right shift by 4 to remove 0's.
    break;
    case 10:
    case 11:
    case 12:
    case 13:

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
