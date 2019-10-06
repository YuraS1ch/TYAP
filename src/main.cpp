#include "defs.h"
#include "Scaner.h"

int main(int argc, const char * argv[])
{
        TScaner * sc;
        int type; TypeLex l;// локальные переменные типа и изображения лексемы
        if (argc<=1) sc = new TScaner("input.txt"); // файл по умолчанию
        else sc = new TScaner(argv[1]); // заданный файл
        do {
                type=sc->Scaner(l);
                if (type != TErr)
                        printf("%s - тип %d \n",l, type);
        } while(type!=TEnd);
        return 0;
}
