circuit : main.o util.o trainingset.o linkedlist.o evaluation.o cstream.o circuit.o arraylist.o crandom.o error.o population.o receiver.o hive.o
	gcc -o circuit main.o util.o trainingset.o linkedlist.o evaluation.o cstream.o circuit.o arraylist.o crandom.o error.o population.o receiver.o hive.o -lpthread

main.o : main.c main.h global.h
	gcc -g -c main.c -o main.o

util.o : util.c util.h global.h
	gcc -g -c util.c -o util.o

trainingset.o : trainingset.c trainingset.h global.h
	gcc -g -c trainingset.c -o trainingset.o

linkedlist.o : linkedlist.c linkedlist.h global.h
	gcc -g -c linkedlist.c -o linkedlist.o

evaluation.o : evaluation.c evaluation.h global.h
	gcc -g -c evaluation.c -o evaluation.o

cstream.o : cstream.c cstream.h global.h
	gcc -g -c cstream.c -o cstream.o

circuit.o : circuit.c circuit.h global.h
	gcc -g -c circuit.c -o circuit.o

arraylist.o : arraylist.c arraylist.h global.h
	gcc -g -c arraylist.c -o arraylist.o

population.o: population.c population.h global.h
	gcc -g -c population.c -o population.o

crandom.o : crandom.c crandom.h global.h
	gcc -g -c crandom.c -o crandom.o

error.o : error.c error.h global.h
	gcc -g -c error.c -o error.o

receiver.o : receiver.c receiver.h global.h
	gcc -g -c receiver.c -o receiver.o

hive.o : hive.c hive.h global.h
	gcc -g -c hive.c -o hive.o

debug:
	rm -fr *.o circuit


