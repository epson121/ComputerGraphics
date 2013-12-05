# Hip, 2013-11-18

LIBS = -lm -lGL -lGLU -lglut

CFILES := $(wildcard *.c)
CPPFILES := $(wildcard *.cpp)
XFILES := $(CFILES:%.c=%.x)
XPPFILES := $(CPPFILES:%.cpp=%.x)

%.x : %.c
	gcc $^ $(LIBS) -o $@

%.x : %.cpp
	g++ $^ $(LIBS) -o $@

# kao prvo u nizu izvodi se kad se napise samo: make
all: $(XFILES) $(XPPFILES)

# poziva se sa: make test
test:
	@echo "CFILES=${CFILES}"
	@echo "CPPFILES=${CPPFILES}"
	@echo "XFILES=${XFILES}"
	@echo "XPPFILES=${XPPFILES}"

# poziva se sa: make clean
clean:
	rm -f $(XFILES) $(XPPFILES)

