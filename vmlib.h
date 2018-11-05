int readFile(char * fileName, unsigned char bytes[]); // Used to read in a file, returns the number of bytes read.
//void fetch(unsigned char * bytes, int * pc, int * flag);
void fetch(unsigned char * bytes, int * pc, int * flag, unsigned char * buffer);
void dispatch(unsigned char * buffer, int * OP1, int * OP2, int * REGISTERS);
void execute(unsigned char * buffer, int * OP1, int * OP2, int * RESULT, int * REGISTERS);
void store(unsigned char * buffer, int * RESULT, int * REGISTERS);
