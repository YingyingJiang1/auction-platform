cc = g++
objs = main.cc administrator.o user.o runtimeFile.o prompt.o interface.o baseUser.o
#VPATH = input:compiler:execute

main: $(objs)
	$(cc) -g -o  main $(objs);

administrator.o: administrator.h
	$(cc) -c -g administrator.cc
user.o: user.h
	$(cc) -c -g user.cc
runtimeFile.o: runtimeFile.h 
	$(cc) -c -g runtimeFile.cc
prompt.o: 
	$(cc) -c -g prompt.cc
interface.o: administrator.h user.h prompt.h
	$(cc) -c -g interface.cc
baseUser.o: baseUser.h
	$(cc) -c -g baseUser.cc

.PHONY:clean
clean:
	-rm *.o 

