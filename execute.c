void execute(unsigned char * buffer, int * OP1, int * OP2, int * RESULT, int * REGISTERS, int * flag)
{
    int instruction = buffer[0] >> 4;
    int r;
    int temp;
    int bit;
    int offset;
    switch(instruction)
    {
        case 0:
            (*flag)--;
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
        case 13: // Iterateover
            // What should result be? We need the memory address that we are iterating over... So get the memory address of r2 = 1E0.
            temp = buffer[0] & 0xF;
            *RESULT = REGISTERS[temp] + (*OP1); // RESULT should be the memory address, plus the bytes we're going to jump next.
            break;
        case 14: // LOAD
            //printf("Loading..\n");
            *RESULT = *OP1 + (*OP2);
            break;
        case 15: // STORE
            *RESULT = *OP1 + *OP2; // Add the offset to the value of 2nd register. We will treat this as a memory address. This is where we will store the value of r1.
            break;
    }
}