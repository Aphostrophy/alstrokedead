#include <stdio.h>
#include "../boolean.h"
#include "wahana.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"
#include "../linkedlist/list_linkedlist.h"

void bacaWahana(Wahana *W, char* namaFile) {
    /* I.S. List Wahana valid dan namafile valid
	/* F.S. W terdefinisi nilai */
	/* Proses: membaca nilai per baris */
    
    Kata id, nama, deskripsi, bil1, bil2, bil3;
    int harga, durasi, kapasitas;
	int infoKe = 0;
    int kataKe = 1;
    
	START(namaFile);
    
	while (!EOP){
        int i = 0;
        CKata.Length = 0;
        while(CC != BLANK){
            if(CC == '\n') {
                ADV();
                break;
            }
            if(CC == '.') {
                break;
            }
            
            CKata.TabKata[i] = CC;
            i++;
            CKata.Length = i;
            // printf("%s %d\n", CKata.TabKata, CKata.Length);
            ADV();
        }
        switch(kataKe) {
            case 1:
                id = copyKata(CKata);
                break;
            case 2:
                nama = copyKata(CKata);
                break;
            case 3:
                bil1 = copyKata(CKata);
                harga = KataToInt(bil1);
                break;
            case 4:
                bil2 = copyKata(CKata);
                durasi = KataToInt(bil2);
                break;
            case 5:
                bil3 = copyKata(CKata);
                kapasitas = KataToInt(bil3);
                break;
            case 6:
                deskripsi = copyKata(CKata);

                // inisiasi list
                (*W).TI[infoKe].id = copyKata(id);
                (*W).TI[infoKe].nama = copyKata(nama);
                (*W).TI[infoKe].harga = harga;
                (*W).TI[infoKe].durasi = durasi;
                (*W).TI[infoKe].kapasitas = kapasitas;
                (*W).TI[infoKe].status = 'N'; //inisiasi dengan not build
                (*W).TI[infoKe].deskripsi = copyKata(deskripsi);

                //inisiasi jumlah pengunjung dan penghasilan dengan 0
                (*W).TI[infoKe].inside = 0;
                (*W).TI[infoKe].pengunjung = 0;
                (*W).TI[infoKe].total_pengunjung = 0;
                (*W).TI[infoKe].penghasilan = 0;
                (*W).TI[infoKe].total_penghasilan = 0;
                (*W).TI[infoKe].panjang = 0;
                (*W).TI[infoKe].lebar = 0;
                kataKe = 0;
                infoKe++;
                break;
            default:
                break;
        }        
        kataKe++;
        IgnoreBlank();

        if(CC == '.') {
            break;
        }
	}
}

/* Selektor - Selektor Penting */
/* Selektor properti wahana, representatif sesuai namanya */
Kata getNama(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].nama;
        }
    }
}

int getHarga(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].harga;
        }
    }
}

int getDurasi(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].durasi;
        }
    }
}

int getKapasitas(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].kapasitas;
        }
    }
}

char getStatus(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].status;
        }
    }
}

Kata getDeskripsi(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].deskripsi;
        }
    }
}

int getInside(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].inside;
        }
    }
}

InfoWahana getWahanabyID(Wahana *W,char id){
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i];
            break;
        }
    }
}

int getPengunjung(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].pengunjung;
        }
    }
}

int getPenghasilan(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].penghasilan;
        }
    }
}

int getTotalPengunjung(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].total_pengunjung;
        }
    }
}

int getTotalPenghasilan(Wahana *W, char id) {
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return (*W).TI[i].total_penghasilan;
        }
    }
}


/* Primitif - Primitif Penting */
void printDetailWahana(Wahana *W, char id, ListNode **head) 
/* Prosedur untuk mencetak detail wahana berdasarkan char id nya, 
   menggunakan linked list untuk mencetak history upgradenya */
{
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            printKata((*W).TI[i].id); printf("\n");
            printKata((*W).TI[i].nama); printf("\n");
            printf("Harga Tiket Wahana : %d\n", (*W).TI[i].harga);
            printf("Durasi Wahana : %d\n", (*W).TI[i].durasi);
            printf("Kapasitas Wahana : %d\n", (*W).TI[i].kapasitas);
            printf("Status Wahana : %c\n", (*W).TI[i].status);
            printf("Ukuran Wahana : ( %d x %d ) \n", (*W).TI[i].lebar,(*W).TI[i].panjang);
            printf("Deskripsi : ");printKata((*W).TI[i].deskripsi); printf("\n");
            printf("Upgrade : ");printUpgrades(head);printf("\n");
            break;
        }
    }
}

void printReportWahana(Wahana *W, char id) 
/* Prosedur untuk mencetak laporan wahana berupa pengunjung dan penghasilan wahana hari ini,
   serta total pengunjung dan penghasilan wahana selama bermain */
{
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            printf("Jumlah Pengunjung Wahana hari ini : %d\n", (*W).TI[i].pengunjung);
            printf("Jumlah Penghasilan Wahana hari ini : %d\n", (*W).TI[i].penghasilan);
            printf("Jumlah Total Pengunjung Wahana : %d\n", (*W).TI[i].total_pengunjung);
            printf("Jumlah Total Penghasilan Wahana : %d\n", (*W).TI[i].total_penghasilan);
            break;
        }
    }
}

void printListWahana(Wahana *W) 
/* Prosedur untuk mencetak list wahana beserta id nya */
{
    for(int i = 0; i < 8; i++) {
        printKata((*W).TI[i].nama); printf(" ");
        printKata((*W).TI[i].id); printf("\n");
    }
}

int countBrokenWahana(Wahana *W) 
/* Fungsi yang mengembalikan jumlah wahana yang sedang rusak */
{
    int res = 0;
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'B') {
            res++;
        }
    }
    return res;
}

void SetZero(Wahana *W)
/* Prosedur untuk mengubah jumlah penghasilan dan pengunjung tiap wahana menjadi 0 setiap hari baru
   I.S setiap jumlah pengunjung, penghasilan, dan inside harian wahana bebas, bisa 0 atau sembarang int 
   F.S setiap jumlah pengunjung, penghasilan, dan inside harian wahana menjadi 0 */
{
    for(int i=0;i<8;i++){
        (*W).TI[i].inside=0;
        (*W).TI[i].pengunjung=0;
        (*W).TI[i].penghasilan=0;
    }
}

void printBrokenWahana(Wahana *W) 
/* Prosedur untuk menetak list wahana yang sedang rusak */
{
    if(countBrokenWahana(W) == 0) {
        printf("Tidak ada wahana yang sedang rusak.\n");
    } else {
        printf("Wahana yang sedang rusak :\n");
        int count = 1;
        for(int i = 0; i < 8; i++) {
            if((*W).TI[i].status == 'B') {
                printf("%d. ", count); printKata((*W).TI[i].nama); printf("\n");
                count++;
            }
        }
    }
}

boolean IsAdaWahanaGood(Wahana W)
/* Fungsi yang mengembalikan true jika W berada dalam kondisi baik dan tidak rusak */
{
    for(int i=0;i<8;i++){
       if (W.TI[i].status=='G'){
           return true;
       }
    }
    return false;
}

void printNotBuilded(Wahana *W)
/* Prosedur untuk mencetak list wahana yang belum dibangun */
{
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].status == 'N'){
            printKata((*W).TI[i].nama); printf("\n");
        }
    }
}

int GetIndex(Wahana *W, char id )
/* Fungsi yang mengembalikan indeks dari wahana dengan char id */
{
    for(int i = 0; i < 8; i++) {
        if((*W).TI[i].id.TabKata[0] == id) {
            return i;
        }
    }
}

boolean IsWahanaBenar(Kata W, Wahana LW)
/* Fungsi yang mengembalikan true jika W terdapat dalam list wahana LW */
{
    boolean benar = false;
    int i=0;
    while (benar==false && i<8){
        if (IsKataSama(W,LW.TI[i].nama)){
            benar = true;
        }
        else{
            i=i+1;
        }
    }
    return benar;
}