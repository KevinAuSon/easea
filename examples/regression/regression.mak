

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

regressionLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =   -fopenmp -O2 -g -Wall -fmessage-length=0 -I$(regressionLIB_PATH)include -I$(EZ_PATH)boost

OBJS = regression.o regressionIndividual.o 

LIBS = -lpthread -fopenmp 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :
 

CXXFLAGS+=-I/usr/local/cuda/common/inc/ -I/usr/local/cuda/include/
LDFLAGS+=

#END OF USER MAKEFILE OPTIONS

TARGET =	regression

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(regressionLIB_PATH)/libeasea.a $(EZ_PATH)boost/program_options.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp regression.png regression.dat regression.prm regression.mak Makefile regression.vcproj regression.csv regression.r regression.plot regression.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp regression.png regression.dat regression.prm regression.mak Makefile regression.vcproj regression.csv regression.r regression.plot regression.pop
endif

