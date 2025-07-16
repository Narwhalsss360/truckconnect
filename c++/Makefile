OUTPUT=a.gitignore.out

INCLUDES=-I truckconnect/include -I NStreamCom/include
SOURCES=testclient/*.cpp truckconnect/src/*.cpp NStreamCom/src/*.cpp

build:
	g++ -std=c++17 $(INCLUDES) $(SOURCES) -g -o $(OUTPUT)

