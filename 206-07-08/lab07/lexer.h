//                 lexer.h 2020
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
class tLexer:public tBaseLexer{
public:
//конструктор
 tLexer():tBaseLexer(){
//создать автоматы:

//________________________________________

// вещественное
    addrange(Adec,0,'0','9',1);
    addstr  (Adec,1,".",   2);
    addrange(Adec,2,'0','9',2);
  Adec.final(2);
//________________________________________

// идентификатор
    addrange(Aid,0,'a','z',1);
    addrange(Aid,1,'a','z',1);
    addstr  (Aid,1,"!",   1);
    addstr  (Aid,0,"G",   1);
  Aid.final(1);
//________________________________________

// идентификатор предиката
    addstr  (Aidq,0,"?",   1);
    addstr  (Aidq,0,"pxy",   2);
    addstr  (Aidq,2,"?",   1);
  Aidq.final(1);
}
};
#endif

