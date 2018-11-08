void execute(unsigned char * buffer, int * OP1, int * OP2, int * RESULT, int * REGISTERS)
{
    int instruction = buffer[0] >> 4;
    int r;
    int temp;
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
    case 7: // SFT
        printf("OPCODE: %d OP1: %d OP2: %d\n", instruction, *OP1, *OP2);
        temp = (buffer[1] & 0xF0) >> 5; // Check the bit to see if it's a right or left shift.
        if(temp)
        *RESULT = (*OP1) >> (*OP2);
        else
        *RESULT = (*OP1) << (*OP2);
        printf("RESULT AFTER SHIFT IS %d\n", *RESULT);
        break;
    case 8: // interrupt
        break;
    case 9:
        printf("OP1: %d OP2: %d\n", *OP1, *OP2);
        *RESULT = *OP1 + *OP2;
        r = buffer[0] & 0x0F;
        REGISTERS[r] = *RESULT;
        printf("%d\n", REGISTERS[r]);
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    }
}