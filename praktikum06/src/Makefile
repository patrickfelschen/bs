BIN_SIMPLE = simple_bot
INCDIR     = ./include
LIBDIR     = ./include
SRCDIR     = ./
CFLAGS     = -Wall -Werror -Wpedantic -g -I$(INCDIR)
CPPFLAGS   = $(CFLAGS) -std=c++11
LDFLAGS    = -lm -lssl -lcrypto -pthread /usr/lib/x86_64-linux-gnu/libcurl.so.4 #-lcurl
OUTDIR	   = ./output

# executables
all: $(OBJFILES) | $(BIN_SIMPLE)

$(BIN_SIMPLE): $(SRCDIR)/Bot.o $(SRCDIR)/main.o $(SRCDIR)/Queue.o $(LIBDIR)/web_request.o
	g++ -o $@ $^ $(LDFLAGS)

# object files
%.o: %.c
	gcc -c -o $@ $(CFLAGS) $^

%.o: %.cpp
	g++ -c -o $@ $(CPPFLAGS) $^

.PHONY: clean
clean:
	$(RM) $(BIN_SIMPLE)
	$(RM) $(wildcard $(SRCDIR)*.o)
	$(RM) $(wildcard $(LIBDIR)/*.o)
	$(RM) $(OUTDIR)/*.html
