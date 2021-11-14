CXXFLAGS        = -g -Wall -std=c++14 -g3 -O0
LDLIBS  = -lglfw -lGLEW -lGL -lXrandr -lXinerama -lXcursor -lXi \
				-lXxf86vm -lX11 -lpthread -lrt -lm -ldl
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET  = sample

.PHONY: clean
 
$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@
 
clean:
	-$(RM) $(TARGET) $(OBJECTS) *~ .*~ core
