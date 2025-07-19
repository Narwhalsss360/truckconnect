OUTPUT=a.gitignore.out

INCLUDES=-I truckconnect/include -I NStreamCom/include
SOURCES=testclient/*.cpp truckconnect/src/*.cpp NStreamCom/src/*.cpp

ifeq ($(OS),Windows_NT)
	LINK := -l ws2_32
else
	LINK :=
endif

build:
	g++ -std=c++17 $(INCLUDES) $(SOURCES) $(LINK) -g -o $(OUTPUT)

