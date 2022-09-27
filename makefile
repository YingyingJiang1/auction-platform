cc = g++
objs = main.cc administrator.o user.o runtimeFile.o  interface.o  mainIntfFunc.o strOperation.o
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
interface.o: mainIntfFunc.h menuNumber.h
	$(cc) -c -g interface.cc
mainIntfFunc.o: administrator.h user.h
	$(cc) -c -g mainIntfFunc.cc
strOperation.o:
	$(cc) -c -g strOperation.cc
.PHONY:clean
clean:
	-rm *.o 

