CXX=g++

CXXFLAGS = -std=c++11  -Wall -g -Wreturn-type

BINARIES= executeit

all: ${BINARIES}

executeit: main.o Node.o Trie.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o