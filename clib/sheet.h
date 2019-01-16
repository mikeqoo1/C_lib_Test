#ifndef SHEET_H
#define SHEET_H
typedef struct Sheet {
    char term[4];
    int start;
    int end;
    int numero;
    int index;
} newsheet;

newsheet SetNumero(newsheet bhno, int Startrange, int Endrange);

newsheet SetTerm(newsheet bhno);

newsheet Next(newsheet bhno);

#endif /* SHEET_H */