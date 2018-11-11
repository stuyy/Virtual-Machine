void execute(unsigned char * buffer, int * OP1, int * OP2, int * RESULT, int * REGISTERS, int * flag)
{
    int instruction = buffer[0] >> 4;
    int r;
    int temp;
    int bit;
    int offset;
    printf("The instruction is: %d\n", instruction);
    switch(instruction)
    {
        case 0:
            (*flag)--;
            printf("Now exiting program.\n");
            break;
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
            temp = (buffer[1] & 0xF0) >> 5; // Check the bit to see if it's a right or left shift.
            if(temp)
                *RESULT = (*OP1) >> (*OP2);
            else
                *RESULT = (*OP1) << (*OP2);
            break;  
        case 8: // interrupt
            break;
        case 9: 
            *RESULT = *OP1 + *OP2;
            break;
        case 10: // BRANCHIFEQUAL
            if(*OP1 == *OP2)
                *RESULT = 1;
            else
                *RESULT = 0;
            break;
        case 11: // BRANCHIFLESS
            // Calculate the offset here?
            if(*OP1 < *OP2)
                *RESULT = 1;
            else
                *RESULT = 0;
            break;
        case 12:
            *RESULT = *OP1;
            break;
        case 13:
            break;
        case 14:
            //printf("Loading..\n");
            *RESULT = *OP2;
           // printf("RESULT %d\n", *RESULT);
            break;
        case 15:
            break;
    }
}