
src_files=main.cpp database.cpp
gen_files=parser.tab.c lex.yy.c

all: bison flex
	g++ -g -o parser ${src_files} ${gen_files}

bison:
	bison -d parser.y

flex:
	flex tokens.l
