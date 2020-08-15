CC=g++
CFLAGS=-I.
DFLAGS=-Wall -std=c++11 -g 
BUILDDIR=build
BINDIR=bin
TARGET=queue
LIBS=-pthread

SRC_DIR=.
SRC_FILES=$(wildcard ./*.cpp)
SRC_OBJS=$(patsubst ./%.cpp, $(BUILDDIR)/%.o, $(SRC_FILES))

WORKERDIR=Workers
WORKER_SRC=$(wildcard $(WORKERDIR)/*.cpp)
WORKER_OBJS=$(patsubst $(WORKERDIR)/%.cpp, $(BUILDDIR)/%.o, $(WORKER_SRC))

OBJS=$(SRC_OBJS) $(WORKER_OBJS)

$(TARGET):$(OBJS)
	@mkdir -p $(BINDIR)
	@echo "Linking $(TARGET)"
	$(CC) $(OBJS) -o $(BINDIR)/$(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(DFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(WORKERDIR)/%.cpp 
	@mkdir -p $(BUILDDIR)
	$(CC) $(DFLAGS) -c -o $@ $<

clean:
	\rm -rf $(BINDIR) $(BUILDDIR) *.o $(TARGET)
