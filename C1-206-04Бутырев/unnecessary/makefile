##
# Project Title
#
# @file
# @version 0.1

run: ML
	echo "a04 -> try"
	./ML
ML: Mlispgen.cpp base-compiler.cpp base-compiler.h basegramma.cpp basegramma.h baselexer.cpp baselexer.h code-gen.cpp code-gen.h fsm.h kngramma.cpp kngramma.h lexer.h mlisp.h slr.cpp slr.h
	g++ -o ML -Wall -pedantic Mlispgen.cpp
try: try.cpp
	g++ -o try -Wall -pedantic try.cpp
clean:
	rm ML try

# end
