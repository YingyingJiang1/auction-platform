cc = g++
objs = main.cc administrator.o user.o runtimeFile.o prompt.o interface.o baseUser.o logAndSign.o
#VPATH = input:compiler:execute

main: $(objs)
	$(cc) -g -o  main $(objs);
	make clean
administrator.o: administrator.h
	$(cc) -c -g administrator.cc
user.o: user.h
	$(cc) -c -g user.cc
runtimeFile.o: runtimeFile.h 
	$(cc) -c -g runtimeFile.cc
prompt.o: 
	$(cc) -c -g prompt.cc
interface.o: interface.h
	$(cc) -c -g interface.cc
baseUser.o: baseUser.h
	$(cc) -c -g baseUser.cc
logAndSign.o: administrator.h user.h
	$(cc) -c -g logAndSign.cc

.PHONY:clean
clean:
	-rm *.o 

