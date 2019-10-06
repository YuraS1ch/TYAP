#include "defs.h"
#include "Scaner.h"

static TypeLex Keyword[MAX_KEYW] = { "int", "unsigned", "while", "main", "return"};
static int IndexKeyword[MAX_KEYW]= {TInt, TUnsigned, TWhile, TMain, TReturn};
using namespace std;

TScaner:: TScaner(const char * FileName) {
        GetData(FileName);
        PutUK(0);
}

void TScaner::PutUK(int i){
        uk=i;
}                                 //восстановить указатель

int TScaner::GetUK(void){
        return uk;
}                                    // запомнить указатель

void TScaner::PrintError(const char * err, char * a) {
        // выдать сообщение об ошибке
        if (a==nullptr)
                printf("Ошибка : %s %s\n",err,a);
        else
                printf("Ошибка : %s. Неверный символ %s\n",err,a);
        return;
}

int TScaner::Scaner(TypeLex l) // программа сканера
{
        int i; // текущая длина лексемы
        for (i=0; i<MAX_LEX; i++) l[i]=0; //очистили поле лексемы
        i=0; // лексема заполняется с позиции i
start:
        while((t[uk]==' ' ) || (t[uk]=='\n') || (t[uk]=='\t')) uk++; // пропуск незначащих элементов
        if ( (t[uk]=='/') && (t[uk+1]=='/') )
        { // начался комментарий, надо пропустить текст до ’\n’
                uk=uk+2;
                while ( (t[uk]!='\n')&&(t[uk]!='#')) uk++;
                goto start;
        }
        if (t[uk]=='\0') {l[0]='#'; return TEnd;}

        if (t[uk]<='9'&&t[uk]>='0') {
                if(t[uk] == '0') {
                        if(t[uk+1] == 'x') {
                                uk+=2;
                                while (( (t[uk]<='9')&&(t[uk]>='0'))|| ( (t[uk]<='F')&&(t[uk]>='A')))
                                        if (i<MAX_LEX-1) l[i++]=t[uk++]; else uk++;
                                return TConstInt_16;
                        }
                        else {
                                uk++;
                                while (( (t[uk]<='7')&&(t[uk]>='0')))
                                        if (i<MAX_LEX-1) l[i++]=t[uk++]; else uk++;
                                return TConstInt_8;
                        }

                }
                else {
                        while (( (t[uk]<='9')&&(t[uk]>='0')))
                                if (i<MAX_LEX-1) l[i++]=t[uk++]; else uk++;
                        return TConstInt_10;
                }
        }
        else if ( ((t[uk]>='a')&&(t[uk]<='z')) ||
                  ((t[uk]>='A')&&(t[uk]<='Z')) ) {
                // начинается идентификатор
                l[i++]=t[uk++];
                while ( ((t[uk]<='9')&&(t[uk]>='0')) ||
                        ((t[uk]>='a')&&(t[uk]<='z')) ||
                        ((t[uk]>='A')&&(t[uk]<='Z')) || t[uk] == '_')
                        if (i<MAX_LEX-1) l[i++]=t[uk++]; else uk++;
                // длинный идентификатор обрезали
                int j; // проверка на ключевое слово:
                for (j=0; j<MAX_KEYW; j++)
                        if (strcmp(l, Keyword[j]) == 0) return IndexKeyword[j];
                return TIdent;
        }
        else if (t[uk]=='\'')
        {
                uk++;
                while ((t[uk] != '\'') && (t[uk] != '\n') && (t[uk] != '#')) {
                        if(i<MAX_LEX) l[i++]=t[uk++]; else uk++;
                }
                if (t[uk] != '\'') {
                        PrintError("Неверная символьная константа", l);
                        return TErr;
                }
                uk++;
                return TConstChar;
        }
        else if (t[uk]=='*')
        { l[i++]=t[uk++]; return TStar; }
        else if (t[uk]=='\\')
        { l[i++]=t[uk++]; return TSlash; }
        else if (t[uk]=='%')
        { l[i++]=t[uk++]; return TPercent; }
        else if (t[uk]=='+')
        { l[i++]=t[uk++]; return TPlus; }
        else if (t[uk]=='-')
        { l[i++]=t[uk++]; return TMinus; }
        else if (t[uk]==';')
        { l[i++]=t[uk++]; return TSemicolon; }
        else if (t[uk]=='(')
        { l[i++]=t[uk++]; return TParent_O; }
        else if (t[uk]==')')
        { l[i++]=t[uk++]; return TParent_C; }
        else if (t[uk]=='{')
        { l[i++]=t[uk++]; return TBrace_O; }
        else if (t[uk]=='}')
        { l[i++]=t[uk++]; return TBrace_C; }
        else if (t[uk]==',')
        { l[i++]=t[uk++]; return TComma; }



        else if (t[uk]=='<') {
                l[i++]=t[uk++];
                if (t[uk]=='=') {
                        l[i++]=t[uk++];
                        return TLess_EQ;
                }
                else if (t[uk]=='<') {
                        l[i++]=t[uk++];
                        return TShift_L;
                }
                return TLess;
        }

        else if (t[uk]=='>') {
                l[i++]=t[uk++];
                if (t[uk]=='=') {
                        l[i++]=t[uk++];
                        return TGreat_EQ;
                }
                else if (t[uk]=='>') {
                        l[i++]=t[uk++];
                        return TShift_R;
                }
                return TGreat;
        }

        else if (t[uk]=='=') {
                l[i++]=t[uk++];
                if (t[uk]=='=') {
                        l[i++]=t[uk++];
                        return TEQ;
                }
                return TAssign;
        }

        else if (t[uk]=='!') {
                l[i++]=t[uk++];
                if (t[uk]=='=') {
                        l[i++]=t[uk++];
                        return TNot_EQ;
                }
                PrintError("Неверный символ",l);
                return TErr;
        }
        else{
                l[i++]=t[uk++];
                PrintError("Неверный символ",l); // ошибка
                return TErr;
        }




}

// ввод файла с исходным модулем
void TScaner::GetData(const char * FileName)
{
        char aa;
        string FilePath = "../scaner/";
        FilePath += FileName;
        FILE * in = fopen(FilePath.c_str(),"r");
        if (!in) {
                PrintError("Отсутствует входной файл",nullptr); exit(1);
        }
        int i=0;
        while(!feof(in)) {
                fscanf(in,"%c",&aa);
                if (!feof(in)) t[i++]=aa;
                if (i>=MAX_TEXT-1) {
                        PrintError("Слишком большой размер исходного модуля",nullptr);
                        break;
                }
        } t[i]='\0'; // приписываем знак ’\0’ в конец текста
        fclose(in);
}     // конец GetData()
