#
# Chemin vers le repertoire d'installation des sources du noyau
#
KERN_PATH = /lib/modules/$(shell uname -r)/build

KERN_INCDIR = $(KERN_PATH)/include

CFLAGS = -Wall -I$(KERN_INCDIR) -D__KERNEL__

MODULES = hello1.o hello2.o

all: $(MODULES)

clean:
	$(RM) $(MODULES) *~
