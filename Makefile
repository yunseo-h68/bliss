CXX               = g++
LIB_TARGET        = libbliss
LIB_VERSION       = 0.0.0
LIB_VERSION_MAJOR = 0
LIB_DIR           = lib
SRC_DIR           = src
OBJS              = *.o
SRCS              = $(OBJS:.o=.cpp)
LINK_LIBS         = -lm
EXAMPLE_TARGET    = bin/example
EXAMPLE_DIR       = example

$(LIB_TARGET):$(SRC_DIR)/$(SRCS) $(SRC_DIR)/*/$(SRCS)
	$(CXX) -fPIC -c $^ $(LINK_LIBS)
	$(CXX) -shared -Wl,-soname,$(LIB_DIR)/$(LIB_TARGET).so.$(LIB_VERSION_MAJOR) -o $(LIB_DIR)/$(LIB_TARGET).so.$(LIB_VERSION) $(OBJS)

ifeq (exist, $(shell [ ! -d ./bin ] && echo exist))
	mkdir lib
endif

ifneq ("$(wildcard $(LIB_DIR)/$(LIB_TARGET).so)", "")
	rm $(LIB_DIR)/$(LIB_TARGET).so
endif
	ln -s $(LIB_TARGET).so.$(LIB_VERSION) $(LIB_DIR)/$(LIB_TARGET).so

ifneq ("$(wildcard $(LIB_DIR)/$(LIB_TARGET).so.$(LIB_VERSION_MAJOR))", "")
	rm $(LIB_DIR)/$(LIB_TARGET).so.$(LIB_VERSION_MAJOR)
endif
	ln -s $(LIB_TARGET).so.$(LIB_VERSION) $(LIB_DIR)/$(LIB_TARGET).so.$(LIB_VERSION_MAJOR)

	rm *.o

example: $(EXAMPLE_TARGET)

$(EXAMPLE_TARGET): $(LIB_TARGET)
ifeq (exist, $(shell [ ! -d ./bin ] && echo exist))
	mkdir bin
endif
	$(CXX) -o $@ $(EXAMPLE_DIR)/$(SRCS) -I. ./$(LIB_DIR)/$(LIB_TARGET).so.$(LIB_VERSION) $(LINK_LIBS)

clean:
	rm -f *.o $(LIB_DIR)/$(LIB_TARGET).* bin/*
