void dispatch(unsigned char * buffer, int * OP1, int * OP2, int * REGISTERS, unsigned char * bytes, int byteCount)
{
    int instruction = buffer[0] >> 4;
    int offset;
    int bit;
    int temp;
    int tempTwo;
    switch(instruction)
    {
        case 0: // HALT
            *OP1 = *OP2 = 0;
            break;
        case 7: // RIGHTSHIFT, LEFTSHIFT (SFT)
            temp = buffer[0] & 0x0F;
            *OP1 = REGISTERS[temp];
            *OP2 = buffer[1] & 0x1F;
            break;
        case 8: // INTERRUPT
            // Not sure what to do for Interrupt.
            //*OP1 = buffer[0] & 0xF;
            temp = 0;
            if(buffer[1] == 0)
                while(temp<16)
                {
                    printf("Register %d: %d\n", temp, REGISTERS[temp]);
                    temp++;
                }
            else if(buffer[1] == 1)
                while(temp<100)
                {
                    printf("%08x: %02x\n", temp, bytes[temp]);
                    temp++;
                }
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
        case 10: // Branchifless and Branchifequal
        case 11:
            *OP1 = REGISTERS[buffer[0] & (0x0F)]; // get the value of register 1
            *OP2 = REGISTERS[(buffer[1] & 0xF0) >> 4]; // get the value of register 2.
            break;
        case 12: // JUMP
            printf("Jumping\n");
            // If number is greater than 1<<28
            // 4 byte instruction.
            offset = ((((((buffer[0] & 0xF) << 8) | buffer[1]) << 8) | buffer[2]) << 8) | buffer[3];
            *OP1 = *OP2 = offset;
            break;
        case 13: // ITERATEOVER
            printf("Iterateover\n");
            printf("%02x %02x %02x %02x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            *OP1 = buffer[1]; // The amount of bytes to point to next.
            *OP2 = (buffer[2] << 8 | buffer[3]); // The amount of bytes to jump back in the Program Counter.
            printf("Next Offset: %d, Jumping back %d bytes.\n", *OP1, *OP2);
            break;
        case 14: // LOAD
            printf("LOADING:::::\n");
            bit = (buffer[1] & 0xF) >> 3;
            offset = buffer[1] & 0xF;

            if(bit)
            {
                offset = (~(offset-1)) & ((1<<3)-1);
                offset -= offset*2;
            }
            temp = (buffer[1] & 0xF0) >> 4;
            *OP1 = REGISTERS[temp]; // Get the value of the register.
            *OP2 = offset;
            printf("*OP1: %d *OP2: %d\n", *OP1, *OP2);
            break;
        case 15: // STORE
            bit = (buffer[1] & 0xF) >> 3;
            offset = buffer[1] & 0xF;
            if(bit)
            {
                offset = (~(offset-1)) & ((1<<3)-1);
                offset -= offset*2;
            }
            temp = (0xF0 & buffer[1]) >> 4; // Get the register number.
            *OP1 = REGISTERS[temp]; // Get the value of the 2nd register.
            *OP2 = offset;
            break;
        default: // Handles OPCODES 1 to 6.
            *OP1 = REGISTERS[0x0F & buffer[0]];
            *OP2 = REGISTERS[(0xF0 & buffer[1]) >> 4];
            break;
    }
}