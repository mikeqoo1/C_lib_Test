#include "sheet.h"

newsheet SetNumero(newsheet bhno, int Startrange, int Endrange)
{
    bhno.start = Startrange;
    bhno.end = Endrange;
    bhno.numero = Startrange;
    bhno.index = 0;
    return bhno;
}

newsheet SetTerm(newsheet bhno)
{
    bhno.term[0] = 'B';
    bhno.term[1] = 'F';
    bhno.term[2] = 'B';
    bhno.term[3] = 'F';
    return bhno;
}

newsheet Next(newsheet bhno)
{
    bhno.numero = bhno.numero + 1;
    if (bhno.numero > bhno.end) {
        bhno.index = bhno.index + 1;
        bhno.numero = bhno.start;
    }
    return bhno;
}