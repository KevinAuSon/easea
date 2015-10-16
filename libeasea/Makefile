UNAME = $(shell uname)
ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifeq ($(shell uname -o 2>/dev/null),Cygwin)
	OS := CYGWIN
endif

CXXFLAGS = -g -O1 -fopenmp -Wall -fmessage-length=0 -I/usr/local/cuda/include -I../boost/

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

ifneq ("$(OS)","")
OBJS += inet_pton.o
endif

#ifeq ($(EZ_CUDA),1)
#OBJS += CCuda.o
#endif

ifneq ("$(OS)","")
LIBS = -L"C:\MinGW\lib" -lws2_32 -lwinmm
CXXFLAGS += -I"C:\MinGW\include"
endif

TARGET = libeasea.a
#ifneq ("$(OS)","")
#	CPPFLAGS=-I..\boost\ #-pg
#else
#	CPPFLAGS=-I../boost/ #-pg
#endif

$(TARGET): $(OBJS)
	ar rcs $@ $^ 

%.o:%.cpp
	$(CXX) $(LIBS) -c $(CXXFLAGS) $(CPPFLAGS) $^ 

all:	$(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
