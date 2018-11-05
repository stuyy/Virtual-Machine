all:
	gcc siavm.c -o siavm.o

assembler:
	gcc ~/Desktop/C-Assembler/assembler.c -o ~/Desktop/C-Assembler/assembler.o && ~/Desktop/C-Assembler/assembler.o ~/Desktop/C-Assembler/assembly.txt ~/Desktop/C-Assembler/out

assemble:
	~/Desktop/C-Assembler/assembler.o ~/Desktop/C-Assembler/assembly.txt ~/Desktop/C-Assembler/out

vm:
	gcc siavm.c -o siavm.o && ./siavm.o ~/Desktop/C-Assembler/out
