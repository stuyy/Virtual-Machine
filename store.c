void store(unsigned char * buffer, int * RESULT, int * REGISTERS, int * reg, int * pc)
{
    int instruction = buffer[0] >> 4;
    int temp;
    printf("The instruction is: %d\n", instruction);
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
        case 10:
            break;
        case 11:
            break;
        case 12:
            *pc = *RESULT; // Set the program counter to where we are jumping.
            //printf("Program Counter is now %d\n", *pc);
            buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
            break;
        case 13:
            break;
        case 14:
            printf("Buffer: %02x %02x\n", buffer[0], buffer[1]);
            break;
        case 15:
            break;
    
    }
    
}