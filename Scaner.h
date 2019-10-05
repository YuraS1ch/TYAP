#ifndef SCANER_H
#include "defs.h"

class TScaner{
    private:
        TypeMod t; // исходный текст
        int uk; // указатель текущей позиции в исходном тексте
    public:
        void PutUK (int i);
        int GetUK (void);
        void PrintError(const char *, char *);
        int Scaner (TypeLex l);
        void GetData(const char *);
        TScaner(const char *);
        ~TScaner() {}
};

#endif // SCANER_H
