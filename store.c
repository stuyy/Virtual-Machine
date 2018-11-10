void store(unsigned char * buffer, int * RESULT, int * REGISTERS, int * reg)
{
    int instruction = buffer[0] >> 4;
    int temp;
    switch(instruction)
    {
        // Get the register, and store the result into it.
        case 1: // add
        case 2: // and
        case 3: // 
        case 4: // 
        case 5: 
        case 6:
            temp = buffer[1] & 0x0F;
            REGISTERS[temp] = *RESULT;
            break;
        case 9:
            temp = buffer[0] & 0x0F;
            REGISTERS[temp] = *RESULT;
            printf("%d\n", REGISTERS[temp]);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            printf("Loading %d into Register %d\n", *RESULT, *reg);
            REGISTERS[*reg] = *RESULT;
            break;
        case 15:
            break;
    
    }
}