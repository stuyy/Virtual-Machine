// Fetch is responsible for "fetching" an instruction, and storing the bytes inside the internal buffer array.
void fetch(unsigned char * bytes, int * pCounter, int * flag, unsigned char * buffer, int * iterater)
{
  int instruction = bytes[*pCounter] >> 4;
  switch(instruction)
  {
    case 0: // HALT
      buffer[0] = bytes[*pCounter]; // Store the first byte into buffer[0] by referencing the bytes array.
      buffer[1] = bytes[++(*pCounter)]; // Store the second byte into buffer[1], increment the pointer counter by 1.
      (*pCounter)++; // Increment the program counter by 1.
      (*iterater) += 2;
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
      (*iterater) += 4;
      break;
    default: // Default Case will handle all of the 2 byte instructions.
      buffer[0] = bytes[*pCounter];
      buffer[1] = bytes[++(*pCounter)];
      (*pCounter)++; // Go to the next byte.
      (*iterater) += 2;
      break;
  }
}