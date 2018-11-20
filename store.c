void store(unsigned char * buffer, unsigned char * bytes, int * RESULT, int * REGISTERS, int * pc, int * iter, int *OP1, int * OP2)
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
                printf("%d\n", offset); // If the offset is negative.
                if(*RESULT)
                    *pc += offset;
            }
            else { // If it's positive, subtract 4
                *pc += (offset-4);
            }
            printf("Program Counter is now: %d\n", *pc);
            exit(0);
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
                *pc += (offset-4);
            }
            printf("Program Counter is now: %d\n", *pc);
            break;
        case 12:
            *pc = *RESULT; // Set the program counter to where we are jumping.
            //printf("Program Counter is now %d\n", *pc);
            buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
            break;
        case 13: // ITERATEOVER
            printf("\n\n\n\n");
            temp = buffer[0] & 0xF;

            printf("%02x %02x %02x %02x\n", bytes[*RESULT], bytes[*RESULT+1], bytes[*RESULT+2], bytes[*RESULT+3]);

            offset = ((bytes[*RESULT] << 8) | bytes[*RESULT+1]) << 16 | ((bytes[*RESULT+2] << 8) | bytes[*RESULT+3]);
            
            printf("Offset: %d\n", offset);
            
            if(offset != 0)
            {
                printf("Hello?");
                //REGISTERS[temp] = bytes[*RESULT];
                REGISTERS[temp] += (*OP1);
                printf("Jumping back %d instructions\n", *OP2);
                printf("The program counter is currently %d\n", *pc);
                *pc = (*pc - 4) - *OP2;
                printf("program counter is %d\n", *pc);
            }
            break;
        case 14: // LOAD
            temp = buffer[0] & 0xF; // This is the register number we will load the value into.
            REGISTERS[temp] = (((bytes[*RESULT] << 8 | bytes[*RESULT+1])) << 16) | ((bytes[*RESULT+2] << 8) | bytes[*RESULT+3]);
            break;  
        case 15: // STORE
            temp = buffer[0] & 0xF;
            bytes[*RESULT] = (REGISTERS[temp] >> 24) & 0xFF;
            bytes[*RESULT+1] = (REGISTERS[temp] >> 16) & 0xFF;
            bytes[*RESULT+2] = (REGISTERS[temp] >> 8) & 0xFF;
            bytes[*RESULT+3] = REGISTERS[temp] & 0xFF;
            // At 1276, we want to store 1524
            break;
    
    }
    
}