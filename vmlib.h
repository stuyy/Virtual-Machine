int readFile(char * fileName, unsigned char bytes[]); // Used to read in a file, returns the number of bytes read.
//void fetch(unsigned char * bytes, int * pc, int * flag);
unsigned char * fetch(unsigned char * bytes, int * pc, int * flag);
void dispatch(unsigned char * buffer, int OPERANDS[]);
