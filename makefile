CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -MMD

EXEC=chessnut
CCFILES=$(wildcard ./**/*.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

clean:
	rm -rf ./**/*.o ./**/*.d ${EXEC}

-include ${DEPENDS}
