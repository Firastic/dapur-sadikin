/* File : selectors.h */
/* Manajemen selektor ADT */

#ifndef SELECTOR_H
#define SELECTOR_H

/* ********** GLOBAL ********** */
#define Neff(X)     (X).Neff
#define Array(X)    (X).T
#define Elmt(X,i)   (X).T[(i)]

/* *** Point *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** Matrix *** */
#define NRowEff(M)      (M).NRowEff
#define NColEff(M)      (M).NColEff
#define ElmtMx(M,i,j)  (M).Mem[(i)][(j)]

/* *** String Stack *** */
#define Top(S)      (S).TOP
#define InfoTop(S)  (S).T[(S).TOP]

#endif