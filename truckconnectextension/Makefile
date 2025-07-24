ifeq ($(OS),Windows_NT)
	OUTPUT := truckconnectextension.gitignore.dll
	LINK := -l ws2_32
else
	OUTPUT := truckconnectextension.gitignore.a
	LINK :=
endif

DEBUG=1

ifeq ($(DEBUG),1)
	DEBUG_ARGS := -g -D_DEBUG
else
	DEBUG_ARGS :=
endif

INCLUDES=-I ../c++/truckconnect/include -I ../c++/NStreamCom/include
SOURCES=*.cpp ../c++/truckconnect/src/*.cpp ../c++/NStreamCom/src/*.cpp

build:
	g++ -std=c++17 -shared $(INCLUDES) $(SOURCES) $(LINK) $(DEBUG_ARGS) -o $(OUTPUT) -Wl,--out-implib,libmylibrary.a

