CC=gcc
OPT=3
CC_FLAGS=-Wall -std=c11 -O$(OPT)
BUILDDIR=./build
OUTDIR=./bin

UNAME        := $(shell uname -s)
INSTALL_USER := $(or $(SUDO_USER),$(USER))

ifeq ($(UNAME),Darwin)
USER_SHELL := $(shell dscl . -read /Users/$(INSTALL_USER) UserShell | awk '{print $$2}')
else
USER_SHELL := $(shell getent passwd $(INSTALL_USER) | cut -d: -f7)
endif

SHELLTYPE := $(if $(filter zsh,$(notdir $(USER_SHELL))),zsh,other)

all: $(OUTDIR)/prevwd $(OUTDIR)/here

install: all
	mkdir -p /usr/share/cdpd
	cp $(OUTDIR)/prevwd /usr/bin/prevwd
	cp $(OUTDIR)/here /usr/bin/here
	cp ./cdpd_$(SHELLTYPE).sh /usr/share/cdpd/cdpd.sh

$(OUTDIR)/prevwd: $(BUILDDIR)/prevwd.o $(BUILDDIR)/cdpd.o
	mkdir -p $(OUTDIR)
	$(CC) -o $(OUTDIR)/prevwd $(BUILDDIR)/prevwd.o $(BUILDDIR)/cdpd.o

$(OUTDIR)/here: $(BUILDDIR)/here.o $(BUILDDIR)/cdpd.o
	mkdir -p $(OUTDIR)
	$(CC) -o $(OUTDIR)/here $(BUILDDIR)/here.o $(BUILDDIR)/cdpd.o

$(BUILDDIR)/here.o: here.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CC_FLAGS) here.c -o $(BUILDDIR)/here.o -c

$(BUILDDIR)/prevwd.o: prevwd.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CC_FLAGS) prevwd.c -o $(BUILDDIR)/prevwd.o -c


$(BUILDDIR)/cdpd.o: cdpd.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CC_FLAGS) cdpd.c -o $(BUILDDIR)/cdpd.o -c

clean:
	rm -rf $(BUILDDIR)
	rm -rf $(OUTDIR)
	rm -f ./prevwd
	rm -f ./here
