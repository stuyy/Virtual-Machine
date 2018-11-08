all:
	gcc siavm.c -o siavm.o

assembler:
	gcc ~/Documents/C-Assembler/assembler.c -o ~/Documents/C-Assembler/assembler.o && ~/Documents/C-Assembler/assembler.o ~/Documents/C-Assembler/assembly.txt ~/Documents/C-Assembler/out

assemble:
	~/Documents/C-Assembler/assembler.o ~/Documents/C-Assembler/assembly.txt ~/Documents/C-Assembler/out

vm:
	gcc siavm.c -o siavm.o && ./siavm.o ~/Documents/C-Assembler/out
