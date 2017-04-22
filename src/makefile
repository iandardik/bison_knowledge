
all: bison flex
	g++ parser.tab.c lex.yy.c -o parser

bison:
	bison -d parser.y

flex:
	flex tokens.l
