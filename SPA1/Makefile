main : 	Processor.o	Task_Q.o SPA1.o
	gcc -o main Processor.o Task_Q.o SPA1.o -lm

Processor.o	: Processor.c
	gcc -c -o Processor.o Processor.c

Task_Q.o : Task_Q.c
	gcc -c -o Task_Q.o	Task_Q.c

main.o : SPA1.c
	gcc -c -o SPA1.o	SPA1.c 	
clean:
	rm *.o main