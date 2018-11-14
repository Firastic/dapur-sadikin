/* File : file-handler.c */
/* Dapur SADIKIN Game External All File Handler */

#include "file-handler.h"
#include <string.h>


/* Semuanya masih bisa diubah sesuai kebutuhan */
void LoadRoom (Matrix *M, int TableNum1 , int TableNum2 , int TableNum3, int TableNum4 ) {
  Kata Kata1, Kata2, Kata3, Kata4;
  int i = MIN_ROW_MAP;
  int j;
  IntToKata(TableNum1,&Kata1);
  IntToKata(TableNum2,&Kata2);
  IntToKata(TableNum3,&Kata3);
  IntToKata(TableNum4,&Kata4);

    while (CC != BARRIER) {
      ADV();
      ADVKATA();
      j = MIN_COL_MAP;
      while ((CC != BREAKLINE) && (CC != BARRIER)) {
          if (IsKataSama(CKata,Kata1)) {
            ElmtMx(*M,i,j).tag = TABLE;
            TableNumber(ElmtMx(*M,i,j)) = TableNum1;
            CapacityOf(ElmtMx(*M,i,j)) = 4;
            //MakeEmpty_Table (M1,i,j);
          } else if (IsKataSama(CKata,Kata2)) {
            ElmtMx(*M,i,j).tag = TABLE;
            ElmtMx(*M,i,j).data.table.num = TableNum2;
            ElmtMx(*M,i,j).data.table.size = 2;
            //MakeEmpty_Table (M1,i,j);
          } else if (IsKataSama(CKata,Kata3)) {
            ElmtMx(*M,i,j).tag = TABLE;
            ElmtMx(*M,i,j).data.table.num = TableNum3;
            ElmtMx(*M,i,j).data.table.size = 4;
            //MakeEmpty_Table (M1,i,j);
          } else if (IsKataSama(CKata,Kata4)) {
            ElmtMx(*M,i,j).tag = TABLE;
            ElmtMx(*M,i,j).data.table.num = TableNum4;
            ElmtMx(*M,i,j).data.table.size = 2;
            //MakeEmpty_Table (M1,i,j);
          } else {
            /* Tidak melakukan apa apa di M1 */
          }
        //printf("Elemen ke %d, %d\n",i,j);
      ADVKATA();
      ++j;
    }
    ++i;
   }

}

void LoadKitchen (Matrix *M) {
  Kata Kata1, Kata2;
  int i = MIN_ROW_MAP;
  int j;

  Kata1.TabKata[1] = 'M'; //KOMPOR
  Kata1.Length = 1;
  Kata2.TabKata[1] = 'T';
  Kata2.Length = 1;

  while (CC != BARRIER) {
    ADV();
    ADVKATA();
    j = MIN_COL_MAP;
    while ((CC != BREAKLINE) && (CC != BARRIER)) {
        if (IsKataSama(CKata,Kata1)) {
          ElmtMx(*M,i,j).tag = STOVE;
          ElmtMx(*M,i,j).data.stove.itemID = 0;
          //MakeEmpty_Table (M1,i,j);
        } else if (IsKataSama(CKata,Kata2)) {
          ElmtMx(*M,i,j).tag = TRAY;
          //printf("Elemen ke %d, %d adalah TRAY\n",i,j);
          //MakeEmpty_Table (M1,i,j);
        } else {

          /* Tidak melakukan apa apa di M1 */
        }
        //printf("Elemen ke %d, %d\n",i,j);
    ADVKATA();
    ++j;
  }
  ++i;
 }
}

void LoadMap(Matrix *M1, Matrix *M2, Matrix *M3, Matrix *M4)
/*
    Prosedur ini akan melakukan load dari file eksternal yang berisi objek-objek dan koordinatnya.
    Parameter masih belum jelas. */
{
    Kata Kata1, Kata2, Kata3, Kata4;
    MakeEmpty_Map(8,8,M1);
    MakeEmpty_Map(8,8,M2);
    MakeEmpty_Map(8,8,M3);
    MakeEmpty_Map(8,8,M4);

    STARTKATA();

    Kata1.TabKata[1] = 'M';
    Kata1.TabKata[2] = 'a';
    Kata1.TabKata[3] = 'p';
    Kata1.Length = 3;

      if (IsKataSama(CKata,Kata1)) {
    	  ADV();
        ADVKATA();

        Kata1.TabKata[1] = '1';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
            LoadRoom(M1,1,2,3,4);
        }
        ADV();
        ADVKATA();

        Kata1.TabKata[1] = '2';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
          LoadRoom(M2,5,6,7,8);
        }
        ADV();
        ADVKATA();

        Kata1.TabKata[1] = '3';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
          LoadRoom(M3,9,10,11,12);
        }
        ADV();
        ADVKATA();

        Kata1.TabKata[1] = '4';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
          LoadKitchen(M4);
        }
        ADV();
      }
  }


void LoadGameStatus() {}

void LoadMapStatus() {}

void LoadMapSave() {}

void Save() {}
