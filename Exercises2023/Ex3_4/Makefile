CC=g++ #Name of compiler
FLAGS=-std=c++20 -w #Compiler flags (the s makes it silent)
TARGET=Test #Executable name
OBJECTS=Test.o FiniteFunctions2.o
LIBS=-I ../../GNUplot/ -lboost_iostreams

#First target in Makefile is default
${TARGET}:${OBJECTS} #Make target from objects
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}
	@make clean

Test.o : Test.cxx FiniteFunctions2.h
	${CC} ${FLAGS} ${LIBS} -c Test.cxx

FiniteFunctions2.o : FiniteFunctions2.cxx FiniteFunctions2.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions2.cxx

clean: #No targets just run shell command to rm object files and emacs backups
	@rm -f *.o *~

cleantarget: #Delete the exectuable
	@rm -f ${TARGET}
