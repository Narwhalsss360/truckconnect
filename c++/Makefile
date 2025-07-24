ifeq ($(OS),Windows_NT)
	OUTPUT := a.gitignore.exe
	LINK := -l ws2_32
else
	OUTPUT := a.gitignore.out
	LINK :=
endif

DEBUG=1

ifeq ($(DEBUG),1)
	DEBUG_ARGS := -g -D_DEBUG
else
	DEBUG_ARGS :=
endif

INCLUDES=-I truckconnect/include -I NStreamCom/include
SOURCES=testclient/*.cpp truckconnect/src/*.cpp NStreamCom/src/*.cpp

build:
	g++ -std=c++17 $(INCLUDES) $(SOURCES) $(LINK) $(DEBUG_ARGS) -o $(OUTPUT)

