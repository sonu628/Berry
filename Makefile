CFLAGS = -std=c++17

all:
	clang++ $(CFLAGS) ArgParser.cpp -c
	clang++ $(CFLAGS) AST.cpp -c
	clang++ $(CFLAGS) Bind.cpp -c
	clang++ $(CFLAGS) Console.cpp -c
	clang++ $(CFLAGS) Error.cpp -c
	clang++ $(CFLAGS) Evaluator.cpp -c
	clang++ $(CFLAGS) Lexer.cpp -c
	clang++ $(CFLAGS) Main.cpp -c
	clang++ $(CFLAGS) Memory.cpp -c
	clang++ $(CFLAGS) Parse.cpp -c
	clang++ $(CFLAGS) SymbolTable.cpp -c
	clang++ $(CFLAGS) Token.cpp -c

	clang++ $(CFLAGS) ArgParser.o AST.o Bind.o Console.o Error.o Evaluator.o \
	Lexer.o Main.o Memory.o Parse.o SymbolTable.o Token.o -o Bin/Main

clean:
	rm *.o