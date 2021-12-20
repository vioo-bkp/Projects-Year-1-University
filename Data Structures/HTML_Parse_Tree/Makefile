CC = gcc
CFLAG = -Wall -Wextra -g 
EXE = tema3
CODE = main.c interpret.c lista.c lib.c style.c getNodesByCriteria.c delNodesByCriteria.c

build: $(EXE)

$(EXE): $(CODE) 
	$(CC) $(CFLAG) $(CODE) -o $(EXE)

clean: $(EXE)
	rm -f $(EXE)
