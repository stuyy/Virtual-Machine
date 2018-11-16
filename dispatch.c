void dispatch(unsigned char * buffer, int * OP1, int * OP2, int * REGISTERS, unsigned char * bytes, int * reg, int byteCount)
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
                while(temp<300)
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
            break;
        case 14: // LOAD
            temp = (buffer[1] & 0xF0) >> 4; // Get the register number.
            tempTwo = REGISTERS[temp]; //get the value of the register.
            *OP1 = 0; // Not sure what OP1 or OP2 would be...

            offset = buffer[1] & 0x0F;
            bit = (buffer[1] & 0x0F) >> 3;
            
            if(bit)
            {
                offset = (~(offset-1)) & ((1<<3)-1);
                offset -= offset*2;
            }
            *OP2 = tempTwo + offset;
            *reg = buffer[0] & 0x0F;
            // I think I have it, I'm just not sure what the OPERANDS will be for LOAD.
            break;
        case 15: // STORE
            
            temp = (0xF0 & buffer[1]) >> 4; // Get the register number.

            *OP1 = REGISTERS[temp]; // Get the value of the register that we are going to add the offset to.
            *OP2 = 0xF & buffer[1];
            printf("Value: %d Offset: %d\n", *OP1, *OP2);
            // We need the value of the 2nd register.
            //*OP2 = REGISTERS[tempTwo];
            break;
        default: // Handles OPCODES 1 to 6.
            *OP1 = REGISTERS[0x0F & buffer[0]];
            *OP2 = REGISTERS[(0xF0 & buffer[1]) >> 4];
            break;
    }
}