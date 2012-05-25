
restore_defaults: restore_defaults.o
	gcc -o restore_defaults restore_defaults.o

restore_defaults.o: restore_defaults.c restore_defaults.h
	gcc -c restore_defaults.c restore_defaults.h

clean:
	rm -rf *.o *.gch restore_defaults
					
