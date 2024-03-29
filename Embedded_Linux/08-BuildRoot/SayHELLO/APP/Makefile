# Just a simple package


CC := $(TARGET_CC)
CFLAGS := -I.

all: SayHelloAPP.c
	@$(CC)  -g -Wall $(CFLAGS) $(LDFLAGS) $< -o SayHelloAPP

clean:
	@rm -f SayHelloAPP
