void store(unsigned char * buffer, unsigned char * bytes, int * RESULT, int * REGISTERS, int * reg, int * pc, int * iter)
{
    int instruction = buffer[0] >> 4;
    int temp;
    int bit;
    int offset;
    switch(instruction)
    {
        // Get the register, and store the result into it.
        case 0:
            break;
        case 1: // add
        case 2: // and
        case 3: // 
        case 4: // 
        case 5: 
        case 6:
            temp = buffer[1] & 0x0F;
            REGISTERS[temp] = *RESULT;
            break;
        case 7:
            temp = buffer[0] & 0xF; // Get the register.
            REGISTERS[temp] = *RESULT;
            break;
        case 9:
            temp = buffer[0] & 0x0F;
            REGISTERS[temp] = *RESULT;
            //printf("%d\n", REGISTERS[temp]);
            break;
        case 10: // BRANCHIFEQUAL
            bit = (buffer[1] & 0x0F) >> 3;
            offset = ((((buffer[1] & 0x0F) << 8) | buffer[2]) << 8) | buffer[3];
            printf("Program Counter is currently: %d\n", *pc);
            if(bit) // If bit is 1, then it's negative.
            {
                offset = (~(offset-1)) & ((1<<20)-1);
                offset -= (offset*2);
                if(*RESULT)
                    *pc += offset;
            }
            else {
                *pc += offset;
            }
            printf("Program Counter is now: %d\n", *pc);
            break;
        case 11: // BRANCHIFLESS
            bit = (buffer[1] & 0x0F) >> 3;
            offset = ((((buffer[1] & 0x0F) << 8) | buffer[2]) << 8) | buffer[3];
            printf("Program Counter is currently: %d\n", *pc);
            if(bit) // If bit is 1, then it's negative.
            {
                offset = (~(offset-1)) & ((1<<20)-1);
                offset -= (offset*2);
                if(*RESULT)
                    *pc += offset;
            }
            else {
                *pc += offset;
            }
            printf("Program Counter is now: %d\n", *pc);
            break;
        case 12:
            *pc = *RESULT; // Set the program counter to where we are jumping.
            //printf("Program Counter is now %d\n", *pc);
            buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
            break;
        case 13: // ITERATEOVER
            printf("Iterator: %d\n Program Counter: %d\n", *iter, *pc);
            break;
        case 14:
            printf("Buffer: %02x %02x\n", buffer[0], buffer[1]);
            break;
        case 15: // STORE
            temp = buffer[0] & 0xF;
            printf("Register %d Value %d\n", temp, REGISTERS[temp]);
            printf("MEMORY ADDRESS: %d\n", *RESULT);
            bytes[*RESULT] = REGISTERS[temp];
            break;
    
    }
    
}