/* File : stack.h */
/* Stack of Items */
/* Deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include "stack.h"
/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty_Stack (Stack *S){
	/* I.S. sembarang; */
	/* F.S. Membuat sebuah stack S yang kosong berkapasitas MAX_ELMT_STACK_STR */
	/* jadi indeksnya antara 1.. MAX_ELMT_STACK_STR+1 karena 0 tidak dipakai */
	/* Ciri stack kosong : TOP bernilai NULL_STACK_STR */
	Top(*S) = NULL_STACK_STR;	
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty_Stack (Stack S){
	/* Mengirim true jika Stack kosong: lihat definisi di atas */
	return (Top(S) == NULL_STACK_STR);
}

boolean IsFull_Stack (Stack S){
	/* Mengirim true jika tabel penampung nilai elemen stack penuh */
	return (Top(S) == MAX_ELMT_STACK_STR);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push_Stack (Stack * S, string str){
	/* Menambahkan str sebagai infotype_food baru pada Stack S. */
	/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
	/* F.S. str menjadi name TOP yang baru, ready bernilai false, TOP bertambah 1 */
	if(IsEmpty(*S))Top(*S) = 1;
	else Top(*S)++;
	InfoTop(*S) = X;	
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop_Stack (Stack * S, infotype_food * X){
	/* Menghapus X dari Stack S. */
	/* I.S. S  tidak mungkin kosong */
	/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
	*X = InfoTop(*S);
	Top(*S)--;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void Input_Stack (Stack * S, file * fptr){
	/* Membaca Stack S dari file teks eksternal. */
	/* I.S. S sembarang */
	/* F.S. Save file fptr masuk ke Stack S */	
}

void Save_Stack (Stack * S, file * fptr){
	/* Menyimpan Stack S ke file teks eksternal. */
	/* I.S. S terdefinisi */
	/* F.S. Stack S terdefinisi ke file fptr */	

}

void PrintData_Stack (Stack S){
	/* Proses : Menuliskan data dari file eksternal yang terkait dengan isi stack */
	/* I.S. S boleh kosong */
	/* F.S. Jika S tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
	/*      Jika S kosong : Hanya menulis "/Array name/ is empty." */
	/* Contoh: Jika isi Stack: [1, 20, 30, 50]
	   Maka tercetak di layar:
	   [1]Spaghetti
	   [2}Sosis
	   [3]Piring
	   [4]Garpu
	*/	
	int i;
	if(IsEmpty(S)){
		printf("Stack is empty");
	} else {
		for(i = 1; i <= Top(S); i++){
			printf("[%d]%s\n", i, S.T[i].name);
		}
	}
}