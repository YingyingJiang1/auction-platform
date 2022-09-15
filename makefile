cc = g++
objs = main.cc Administrator.o User.o RuntimeFile.o Prompt.o Interface.o
#VPATH = input:compiler:execute

main: $(objs)
	$(cc) -g -o  main $(objs);
	make clean

Administrator.o: Administrator.h
	$(cc) -c -g Administrator.cc
User.o: User.h
	$(cc) -c -g User.cc
RuntimeFile.o: RuntimeFile.h 
	$(cc) -c -g RuntimeFile.cc
Prompt.o: 
	$(cc) -c -g Prompt.cc
Interface.o: Administrator.h User.h Prompt.h
	$(cc) -c -g Interface.cc

.PHONY:clean
clean:
	-rm *.o 

