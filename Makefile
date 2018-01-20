PROGRAMS := str2 str1

CXXFLAGS += -std=c++11

.PHONY : all clean
all : ${PROGRAMS}

str1 : str1.o strproc.o
	${CXX} ${CXXFLAGS} -pthread -o $@ $^

str2 : str2.o strproc.o
	${CXX} ${CXXFLAGS} -o $@ $^

str1.o : str1.cpp  strproc.h
str2.o : str2.cpp  strproc.h
strproc.o : strproc.cpp strproc.h

clean :
	${RM} *.o ${PROGRAMS}

