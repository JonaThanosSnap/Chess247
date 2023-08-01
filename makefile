CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -w -MMD -lX11

EXEC=chess
CCFILES=$(shell find . -name "*.cc")
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

clean:
	rm -rf ${OBJECTS} ${DEPENDS} ${EXEC}

-include ${DEPENDS}
