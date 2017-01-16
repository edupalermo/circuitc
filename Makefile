circuit : main.o util.o trainingset.o linkedlist.o evaluation.o cstream.o circuit.o arraylist.o crandom.o error.o
	gcc -o circuit main.o util.o trainingset.o linkedlist.o evaluation.o cstream.o circuit.o arraylist.o crandom.o error.o

main.o : main.c main.h general.h
	gcc -g -c main.c -o main.o

util.o : util.c util.h general.h
	gcc -g -c util.c -o util.o

trainingset.o : trainingset.c trainingset.h general.h
	gcc -g -c trainingset.c -o trainingset.o

linkedlist.o : linkedlist.c linkedlist.h general.h
	gcc -g -c linkedlist.c -o linkedlist.o

evaluation.o : evaluation.c evaluation.h general.h
	gcc -g -c evaluation.c -o evaluation.o

cstream.o : cstream.c cstream.h general.h
	gcc -g -c cstream.c -o cstream.o

circuit.o : circuit.c circuit.h general.h
	gcc -g -c circuit.c -o circuit.o

arraylist.o : arraylist.c arraylist.h general.h
	gcc -g -c arraylist.c -o arraylist.o

crandom.o : crandom.c crandom.h general.h
	gcc -g -c crandom.c -o crandom.o

error.o : error.c error.h general.h
	gcc -g -c error.c -o error.o

clean:
	rm -fr *.o circuit


