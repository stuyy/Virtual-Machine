void execute(unsigned char * buffer, int * OP1, int * OP2, int * RESULT, int * REGISTERS)
{
    int instruction = buffer[0] >> 4;
    int r;
    int temp;
    int bit;
    switch(instruction)
    {
        case 1: // adding
            *RESULT = *OP1 + *OP2;
            break;
        case 2:
            *RESULT = *OP1 & *OP2;
            break;
        case 3:
            *RESULT = *OP1/(*OP2);
            break;
        case 4:
            *RESULT = (*OP1)*(*OP2);
            break;
        case 5:
            *RESULT = (*OP1)-(*OP2);
            break;
        case 6:
            *RESULT = (*OP1) | (*OP2);
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
            *RESULT = *OP1 + *OP2;
            break;
        case 10:
        case 11:
            // Calculate the offset here?
            bit = (buffer[1] & 0x0F) >> 3;
            
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            printf("Loading..\n");
            *RESULT = *OP2;
            printf("RESULT %d\n", *RESULT);
            break;
        case 15:
            break;
    }
}