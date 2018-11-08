void dispatch(unsigned char * buffer, int * OP1, int * OP2, int * REGISTERS, unsigned char * bytes)
{
    int instruction = buffer[0] >> 4;
    int offset;
    int bit;
    int temp;
    int tempTwo;
    switch(instruction)
    {
    case 0: // HALT
        break;
    case 7: // RIGHTSHIFT, LEFTSHIFT (SFT)
        temp = buffer[0] & 0x0F;
        *OP1 = REGISTERS[temp];
        *OP2 = buffer[1] & 0x1F;
        break;
    case 8: // INTERRUPT
        // Not sure what to do for Interrupt.
        break;
    case 9: // ADDIMMEDIATE
        *OP1 = REGISTERS[(0x0F) & buffer[0]]; // The value at the specified register.
        bit = (buffer[1] & 0xF0) >> 7;
        offset = buffer[1];
        if(bit) // if bit = 1
        {
            offset = (~(offset-1)) & ((1<<7)-1);
            offset -= (offset*2);
            *OP2 = offset;
        } 
        else
            *OP2 = offset;
        break;
    case 14: // LOAD
        printf("%02x %02x\n", buffer[0], buffer[1]);
        temp = (buffer[1] & 0xF0) >> 4; // Get the register number.
        tempTwo = REGISTERS[temp]; //get the value of the register.
        *OP1 = 0; // Not sure what OP1 or OP2 would be...
        *OP2 = tempTwo + (buffer[1] & 0x0F);
        break;
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
        printf("Jumping\n");
        break;
    case 13: // ITERATEOVER
        printf("Iterateover\n");
        break;
    default: // Handles OPCODES 1 to 6.
        *OP1 = REGISTERS[0x0F & buffer[0]];
        *OP2 = REGISTERS[(0xF0 & buffer[1]) >> 4];
        break;
    }
}