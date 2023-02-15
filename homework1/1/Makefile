CC= mpic++
CFLAGS=
LDFLAGS=
SOURCES= 1.cc 
EXECUTABLE= tests

all: $(SOURCES) $(EXECUTABLE)
	mpiexec -n 4 ./tests
	
$(EXECUTABLE): $(SOURCES) 
	$(CC) $(LDFLAGS) $(SOURCES) -o $@
