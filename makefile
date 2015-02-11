CC=cc
CFLAGS+=-g

src=$(wildcard *.c)
Target=$(basename $(firstword $(src) ) )

$(Target):$(src)
	$(CC) $(src) $(CFLAGS) -o $(Target)

.PHONY:test clean
test:
	@echo "Current Dir : " $(shell pwd)
	@echo "Src         : "$(src) 
	@echo "Target      : "$(Target)

clean:
	-rm  $(Target)

