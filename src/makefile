
src_files=main.cpp database.cpp noun.cpp recipe.cpp helpers.cpp
gen_files=parser.tab.c lex.yy.c

all: bison flex compile

compile:
	g++ -std=c++11 -g -o parser ${src_files} ${gen_files}

bison:
	bison -d parser.y

flex:
	flex tokens.l

clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h parser
