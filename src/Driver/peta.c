// ======================================Include Kebutuhan ADT============================================
#include "../Header/Input.h"
#include "../Header/matriks.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include "../Header/stackt.h"
#include "../Header/point.h"
#include "../Header/arrayPair.h"
#include "../Header/jam.h"
#include "../Header/wahana.h"
<<<<<<< HEAD
#include "../Header/graph.h"
=======
#include "../Header/bintree.h"
#include "../Header/arrayTriplet.h"
#include "../Header/list_linkedlist.h"
>>>>>>> fb6365646c423034f8bcc3ffd6b6d0c8ad558dd0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// =======================================================================================================

// ======================================Pendefinisian State di dalam Game================================
#define MAIN_MENU 0
#define NEW_GAME 1
#define LOAD_GAME 2
#define MAIN_DAY 3
#define PREPARATION_DAY 4
#define OFFICE 5
#define OFFICE_DETAIL 6
#define OFFICE_REPORT 7
#define DETAIL_WAHANA 8
#define INVENTORY 9
// =======================================================================================================

// =========================Pendefinisian global variabel yang akan dipakai===============================
int cmap;
int state;
MATRIKS map[5], mapRoom;
POINT playerpos ;
int pmoney;
Stack aksi;
int count_aksi, need_money, need_time;
TabInt Materials, Inventory, need_material, HargaBuild, MaterialBuild, ActionTime;
JAM time ;
Wahana wahana;
Kata CKata;
boolean EndKata;
ListNode *link[20] = { 0 }; // Inisialisasi semua linked list dengan null, untuk load game bisa dilakukan add upgrade manual
char ChoosenWahana;
Graph denah;

// Dan masih banyak variabel lain , sambil menunggu adt jadi
// =======================================================================================================

// ====================Pendefinisian kata supaya bisa di recognize mesinkar/kata==========================

// =======================================================================================================


void MaintoPrepDay(){
	// Prepare Everything
	for (int i = 0 ; i < 8 ; i++){
		if(wahana.TI[i].status == 'B') {
			wahana.TI[i].status = 'G';
		}
	}
	// Kosongkan Antrian , nunggu Hera
	// Kosongkan Array orang sedang naik Wahana
}
void PrepToMainDay(){
	infotype x;
	while(!IsEmptyStack(aksi)){
		Pop(&aksi,&x);
	}
	need_money = 0;
	need_time = 0;
	for (int i = ArrayPair_GetFirstIdx(Inventory) ; i <= ArrayPair_GetLastIdx(Inventory) ; i ++){ 
		Pair_Cost(need_material,i) = 0 ;
	} 
	count_aksi = 0 ;
}
// =========================================Fungsi MainDay================================================


void UpdateWaktu(int n){
	time = NextNMenit(time,n);
	if (state == MAIN_DAY) {
		if (JAMToMenit(time) >= 1260){
			state = PREPARATION_DAY;
			MaintoPrepDay();
		} else {
			int broke = rand() % 100;
			if(broke == 69 || broke == 12 || broke >= 80) {
				int machine = rand() % 8;
				if(wahana.TI[machine].status == 'G') {
					wahana.TI[machine].status = 'B';
					printf("OH NO!!! %s broke. Please repair it ASAP!!!\n", wahana.TI[machine].nama);
					printf("Tekan tombol enter untuk melanjutkan permainan!!\n");
					getchar();
				}
			}
		}
	}
	
	if (state == PREPARATION_DAY && JAMToMenit(time) >= 540 && JAMToMenit(time) <= 580){
		PrepToMainDay();
		state = MAIN_DAY;
	}
}

boolean IsBisaDilewati(char c){
	// Return true apabila c adalah karakter yang bisa ditindih player
	return (c=='^' || c=='>' || c=='<' || c=='V' || c=='-'|| c=='X' || c=='O');
}

char getBangunanSekitar(){
	if (Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos))!='*' && Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos))!='O' &&Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos))!='-'){
		return Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos));
	} else if (Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1)!='*' && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1)!='O' &&Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1)!='-'){
		return Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1);
	} else if (Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos))!='*' && Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos))!='O' &&Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos))!='-'){
		return Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos));
	} else if (Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1)!='*' && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1)!='O' &&Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1)!='-'){
		return Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1);
	} else {
		return '*';
	}
}

void RepairWahana(Wahana *W, char id) {
    char status = getStatus(W,id);
    if (status == 'B') {
        (*W).TI[GetIndex(W,id)].status = 'G';
    }
}

void InputMainDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	Kata W; W.TabKata[0] = 'w'; W.Length = 1;
	Kata A; A.TabKata[0] = 'a'; A.Length = 1;
	Kata S; S.TabKata[0] = 's'; S.Length = 1;
	Kata D; D.TabKata[0] = 'd'; D.Length = 1;
	Kata Detail; Detail.TabKata[0] = 'd'; Detail.TabKata[1] = 'e'; Detail.TabKata[2] = 't'; Detail.TabKata[3] = 'a'; Detail.TabKata[4] = 'i'; Detail.TabKata[5] = 'l'; Detail.Length = 6;
	Kata Repair; Repair.TabKata[0] = 'r'; Repair.TabKata[1] = 'e'; Repair.TabKata[2] = 'p'; Repair.TabKata[3] = 'a'; Repair.TabKata[4] = 'i'; Repair.TabKata[5] = 'r'; Repair.Length = 6;
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,W)));
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,A)));
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,S)));
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,D)));
	} else if (inpt == INPUT_i){
		state = PREPARATION_DAY;
		Hour(time) = 21 ;
		Minute(time) = 0;
		MaintoPrepDay();
	} else if (inpt == INPUT_1 && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)) == 'O') {
		state = OFFICE;
	} else if (inpt == INPUT_2 && getBangunanSekitar() != 'A' && getBangunanSekitar() != '*') {
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Detail)));
		ChoosenWahana = getBangunanSekitar();
		state = DETAIL_WAHANA;
	} else if ( inpt == INPUT_3){
		char id = getBangunanSekitar();
		RepairWahana(&wahana, id);
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Repair)));
	}
}

void PrintMainDay() {
	JAM tutup;
	Hour(tutup) = 21;
	Minute(tutup) = 0;
	// Menampilkan informasi pada bagian inti game saat mainday
	if (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '>' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '<' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '^' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == 'V' ) {
		infotypePeta CurrentPos;
		CurrentPos.map = cmap;
		Absis(CurrentPos.p) = Absis(playerpos);
		Ordinat(CurrentPos.p) = Ordinat(playerpos);
		adrPeta P = SearchPeta(denah,CurrentPos);
		adrTerowongan T = Trail(P);
		P = T->Succ;
		cmap = idPeta(P).map;
		Absis(playerpos) = Absis(idPeta(P).p);
		Ordinat(playerpos) = Ordinat(idPeta(P).p);
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,Absis(playerpos),Ordinat(playerpos));
	printf("%s\n","");
	printf("Nama : %s 	Uang: %d	Waktu tersisa: %d menit\n ", "stranger", pmoney, Durasi(time, tutup));
	printf("%s","Jam : ");
	TulisJAM(time);
	printf("\n");
	printBrokenWahana(&wahana);
	printf("%s\n","");
	// Masih harus ngeprint data data seperti queue , broken wahana dll
}

// =======================================================================================================

// ========================================Fungsi Preparation Day=========================================
void HandleBuy() {
	Kata Action, StackEl, Barang, Jumlah;
	int jumlah_int;

	printf("Selamat Datang ke Menu Pembelian\n");
	printf("Daftar Barang yang dapat dibeli: \n");
    ArrayPair_TulisIsiTabNumbering(Materials);printf("\n");
	printf("Masukkan Barang yang ingin dibeli: ");

   	int kata_ke = 1;
	Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.Length = 3;
    STARTBUY();
    while(!EOP && !EOL){
		int i = 0;
		CKata.Length=0;
        while(CC!=BLANK){
			if(CC=='\r'){
				CC ='\n';
			}
			if(CC=='\n'){
				break;
			}
			CKata.TabKata[i] = CC;
			i++;
			CKata.Length=i;
			// printf("%c",CC);
			ADV();
		}
		if(kata_ke==1){
			Action = CKata;
		} else if(kata_ke==2){
			Jumlah = CKata;
		} else if(kata_ke==3){
			Barang = CKata;
		}
		if(CC=='\n'){
			break;
		}
		kata_ke++;
		IgnoreBlank();
    }
	jumlah_int = atoi(Jumlah.TabKata);
	int materialIndex = ArrayPair_SearchByItem(Materials,Barang);
	if(IsKataSama(Action,BUY) && materialIndex != IdxUndef){
		if(pmoney>=jumlah_int*Pair_Cost(Materials,materialIndex)+need_money){
			need_money = need_money + jumlah_int*Pair_Cost(Materials,materialIndex);
			StackEl.Length=0; strcpy(StackEl.TabKata,"");StackEl = KataConcat(StackEl,Action);strcat(StackEl.TabKata," ");StackEl.Length++;StackEl = KataConcat(StackEl,Jumlah);strcat(StackEl.TabKata," ");StackEl.Length++;StackEl = KataConcat(StackEl,Barang);
			// printf("%d",Jumlah.Length); printf("%s",Action.TabKata); printf("%s",Barang.TabKata); 
			Push(&aksi,StackEl.TabKata);
			count_aksi = count_aksi + 1;
			need_time = need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUY));
			Pair_Cost(Inventory,materialIndex) += jumlah_int;
			
		} else{ // Uang tidak cukup
			printf("Uang tidak cukup! Tekan apapun untuk melanjutkan\n");
			getchar();
		}
	} else{
		printf("Command salah! Tekan apapun untuk melanjutkan\n");
		getchar();
	}
	// End of Parser

	// Validasi apakah yang diketik benar benar "buy"
	// Validasi apakah uang masih cukup dan validasi apakah waktu cukup , kalau ada validasi lain jg sabi
	// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, kalo tidak keluarkan pesan error
}

void HandleBuild(){
	char SbuildX[100]; char SbuildY[100]; char SbuildMap[100];
	int PbuildX = 0; int PbuildY = 0; int PbuildMap = cmap;  //Membangun di koordinat (PbuildX,Pbuildy) di peta PbuildMap
	printf("Selamat Datang ke Menu Pembangunan\n");
	printf("Ingin membangun diposisi mana (w/a/s/d): \n");
	Kata Choice,BUILD,StackEl;
   	int kata_ke = 1;
    BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d';
    BUILD.Length = 5;
	STARTBUY();
	while(!EOP && !EOL){
		int i = 0;
		CKata.Length=0;
		while(CC!=BLANK){
			if(CC=='\r'){
				CC ='\n';
			}
			if(CC=='\n'){
				break;
			}
			CKata.TabKata[i] = CC;
			i++;
			CKata.Length=i;
			ADV();
		}
		if(kata_ke==1){
			Choice = CKata;
		}
		if(CC=='\n'){
			break;
		}
		kata_ke++;
		IgnoreBlank();
	}
	// Mendapatkan lokasi mau dibangun dimana
	if(Choice.TabKata[0]=='w' || Choice.TabKata[0]=='a' || Choice.TabKata[0]=='s' || Choice.TabKata[0]=='d'){
		if (Choice.TabKata[0] == 'w') { PbuildX = Absis(playerpos) -1 ; PbuildY = Ordinat(playerpos) ;} 
		else if (Choice.TabKata[0] == 'a' ){ PbuildX = Absis(playerpos) ; PbuildY = Ordinat(playerpos)-1 ;} 
		else if (Choice.TabKata[0] == 's' ){ PbuildX = Absis(playerpos) +1 ; PbuildY = Ordinat(playerpos) ;} 
		else if (Choice.TabKata[0] == 'd' ){ PbuildX = Absis(playerpos)  ; PbuildY = Ordinat(playerpos) + 1 ;}
		if (IsBisaDilewati(Elmt(mapRoom,PbuildX,PbuildY))){
			printf("Daftar Bangunan yang dapat dibangun: \n");
			printNotBuilded(&wahana);
			printf("Masukkan Bangunan yang ingin dibangun: ");
			Kata Method, Bangunan;
			STARTBUY();
			while(!EOP && !EOL){
				int i = 0;
				CKata.Length=0;
				if(kata_ke==1){
					while(CC!=BLANK){
						if(CC=='\r'){
							CC ='\n';
						}
						if(CC=='\n'){
							break;
						}
						CKata.TabKata[i] = CC;
						i++;
						CKata.Length=i;
						ADV();
					}
					Method = CKata;
				} else if(kata_ke==2){
					while(true){
						if(CC=='\r'){
							CC ='\n';
						}
						if(CC=='\n'){
							break;
						}
						CKata.TabKata[i] = CC;
						i++;
						CKata.Length=i;
						ADV();
					}
					Bangunan = CKata;
				}
				if(CC=='\n'){
					break;
				}
				kata_ke++;
				IgnoreBlank();
			}
			if(IsKataSama(Method,BUILD)){
				int bangunanIndex = ArrayPair_SearchByItem(HargaBuild,Bangunan);
				Kata AMBER;
				AMBER.TabKata[0] = 'A'; AMBER.TabKata[1] = 'm'; AMBER.TabKata[2] = 'b'; AMBER.TabKata[3] = 'e'; AMBER.TabKata[4] = 'r';
				AMBER.Length = 5;
				int materialIndex = ArrayPair_SearchByItem(Materials,AMBER);
				int banyakAmberdibutuhkan = Pair_Cost(MaterialBuild,ArrayPair_SearchByItem(MaterialBuild,Bangunan));
				if (pmoney < Pair_Cost(HargaBuild,bangunanIndex)+need_money){
					printf("Uang Tidak Mencukupi!");getchar();
				} else if (Pair_Cost(Inventory,materialIndex) < banyakAmberdibutuhkan){
					printf("Bahan Bangunan Tidak Mencukupi!");getchar();
				} else {
					Pair_Cost(need_material,materialIndex) = Pair_Cost(need_material,materialIndex) + banyakAmberdibutuhkan ;
					need_money = need_money + Pair_Cost(HargaBuild,bangunanIndex);
					Elmt(map[PbuildMap],PbuildX,PbuildY) = Bangunan.TabKata[0];
					sprintf(SbuildX, "%d", PbuildX); sprintf(SbuildY, "%d", PbuildY); sprintf(SbuildMap, "%d", PbuildMap); sprintf(SbuildY, "%d", PbuildY);
					strcpy(StackEl.TabKata,""); StackEl = KataConcat(StackEl,Method); strcat(StackEl.TabKata," "); StackEl.Length++; StackEl = KataConcat(StackEl,Bangunan); strcat(StackEl.TabKata," ");StackEl.Length++; strcat(StackEl.TabKata,SbuildX);strcat(StackEl.TabKata," "); strcat(StackEl.TabKata,SbuildY);strcat(StackEl.TabKata," "); strcat(StackEl.TabKata,SbuildMap);
					Push(&aksi,StackEl.TabKata);
					count_aksi = count_aksi + 1;
					(wahana).TI[GetIndex(&wahana, Bangunan.TabKata[0])].status ='O';
					need_time = need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUILD));
					// Validasi apakah waktu cukup 
					// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, tambah bahan bangunan yang dibutuhkan, kalo tidak keluarkan pesan error
				}
			} else{
				printf("Invalid Command!");getchar();
			}	
		} else {
			printf("Tidak Bisa Membangun disitu");getchar();
		}
	} else{
		printf("Invalid location!");getchar();
		
	}

}

void HandleUpgrade(){
	// char action[100] ; char method[100] ; char upgrade[100]; 
	Kata Action, Nama_Wahana, StackEl;
	char bangunan = getBangunanSekitar();
	if (bangunan != '*'){
		printf("Selamat Datang ke Menu Upgrade\n");
		printf("Daftar Upgrade: \n");
<<<<<<< HEAD
=======
		PrintAvailableUpgrade(bangunan);
>>>>>>> fb6365646c423034f8bcc3ffd6b6d0c8ad558dd0
		// Ambil upgrade dari si bangunan dengan state sekarang
		printf("Masukkan Upgrade yang ingin dilakukan: ");
		Kata UPGRADE;
		int kata_ke = 1;
		UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e';
		UPGRADE.Length = 7;
		STARTBUY();
		while(!EOP){
			int i = 0;
			CKata.Length=0;
			while(CC!=BLANK){
				CKata.TabKata[i] = CC;
				if(CC=='\n'){
					break;
				}
				i++;
				CKata.Length=i;
				ADV();
			}
			if(kata_ke==1){
				Action = CKata;
			} else if(kata_ke==2){
				Nama_Wahana = CKata;
			}
			if(CC=='\n'){
				break;
			}
			kata_ke++;
			IgnoreBlank();
		}
		if(IsKataSama(Action, UPGRADE)){
			//Validasi di sini, tapi belum ,soalnya g tau dmn :v
			strcpy(StackEl.TabKata,"");StackEl = KataConcat(StackEl,Action); strcat(StackEl.TabKata," "); StackEl.Length++; StackEl = KataConcat(StackEl,Nama_Wahana);
			Push(&aksi,StackEl.TabKata);
		} else{
			printf("Command salah! Tekan apapun untuk melanjutkan\n");
			getchar();
		}
		// Validasi apakah yang diketik benar benar "upgrade"
		// Validasi apakah uang masih cukup dan validasi apakah waktu cukup , validasi apakah bahan bangunan cukup untuk upgrade
		// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, tambah bahan bangunan yang dibutuhkan, kalo tidak keluarkan pesan error
	} else{
		printf("Tidak ada wahana di sekitar Anda");
		getchar();
	}

}

void HandleUndo(){
	Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.Length = 3;
	Kata BUILD; BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d'; BUILD.Length = 5;
	Kata UPGRADE; UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e'; UPGRADE.Length = 7;
	if(!IsEmptyStack(aksi)){
		infotype x ;
		Pop(&aksi,&x);
		if (x[0] == 'b' && x[2] == 'y'){
			char benda[100]; int n; Kata Benda;
			AkuisisiBuy(x,&n,benda);
			strcpy(Benda.TabKata, benda);  Benda.Length = strlen(benda);
			int materialIndex = ArrayPair_SearchByItem(Materials,Benda);
			need_money = need_money - n*Pair_Cost(Materials,materialIndex);
			count_aksi = count_aksi - 1;
			need_time = need_time - Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUY));
			Pair_Cost(Inventory,materialIndex) -= n;
			// printf("%c %d", benda[0] , n); getchar(); // Ini gw tes dengan ngeprint wkwk
			// Kurangi waktu yang dibutuhkan dari buy
		} else if (x[0] == 'b' && x[2] == 'i') {
			int PbuildX; int PbuildY; int PbuildMap; char bangunan[100]; Kata Bangunan;
			AkuisisiBuild(x,&PbuildX,&PbuildY,&PbuildMap,bangunan);
			strcpy(Bangunan.TabKata, bangunan);  Bangunan.Length = strlen(bangunan);
			// printf("%d %d %d %c", PbuildX,PbuildY,PbuildMap,bangunan[0]); getchar(); // Ini gw tes dengan ngeprint wkwk
			// Kurangi waktu yang dibutuhkan dari buy
			Kata AMBER;
			AMBER.TabKata[0] = 'A'; AMBER.TabKata[1] = 'm'; AMBER.TabKata[2] = 'b'; AMBER.TabKata[3] = 'e'; AMBER.TabKata[4] = 'r';
			AMBER.Length = 5;
			int materialIndex = ArrayPair_SearchByItem(Materials,AMBER);
			int n = Pair_Cost(MaterialBuild,ArrayPair_SearchByItem(MaterialBuild,Bangunan)); 
			int bangunanIndex = ArrayPair_SearchByItem(HargaBuild,Bangunan);
			need_money = need_money - Pair_Cost(HargaBuild,bangunanIndex); // Kurangi uang yang dibutuhkan dari membangun bangunan
			Pair_Cost(need_material,materialIndex)= Pair_Cost(need_material,materialIndex) - n;
			count_aksi = count_aksi - 1;
			(wahana).TI[GetIndex(&wahana, bangunan[0])].status ='N';
			Elmt(map[PbuildMap],PbuildX,PbuildY) = '-';
			need_time = need_time - Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUILD));
			
		} else if (x[0] == 'u'){
			printf("upgrade"); getchar();
		}
	}
}

void HandleExecution(){
	infotype x;
	count_aksi = 0 ;
	UpdateWaktu(need_time);
	need_time = 0;
	pmoney = pmoney - need_money; // Kurangi uang dengan uang yang dibutuhkan
	need_money = 0 ;
	for (int i = ArrayPair_GetFirstIdx(Inventory) ; i <= ArrayPair_GetLastIdx(Inventory) ; i ++){ 
		Pair_Cost(Inventory,i) = Pair_Cost(Inventory,i) - Pair_Cost(need_material,i); // Kurangi material dengan semua material dibutuhkan
		Pair_Cost(need_material,i) = 0 ;
	} 
	Reverse(&aksi);
	while(!IsEmptyStack(aksi)){
		Pop(&aksi,&x);
		if (x[0] == 'b' && x[2] == 'y'){
			char benda[100]; int n; Kata Benda;
			AkuisisiBuy(x,&n,benda);
			strcpy(Benda.TabKata, benda);  Benda.Length = strlen(benda);
			// printf("%c %d", benda[0] , n); getchar(); // Ini gw tes dengan ngeprint wkwk
			int materialIndex = ArrayPair_SearchByItem(Materials,Benda);
			// Pair_Cost(Inventory,materialIndex) += n; // Menambah jumlah barang di inventory
		} else if (x[0] == 'b' && x[2] == 'i') {
			int PbuildX; int PbuildY; int PbuildMap; char bangunan[100];
			AkuisisiBuild(x,&PbuildX,&PbuildY,&PbuildMap,bangunan);
			Elmt(map[PbuildMap],PbuildX,PbuildY) = bangunan[0];
			(wahana).TI[GetIndex(&wahana, bangunan[0])].status ='G';
		} else if (x[0] == 'u'){
			printf("upgrade"); getchar();
		}
	}
}

void InputPreparationDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	JAM buka; Hour(buka) = 9; Minute(buka) = 0;
	Kata W; W.TabKata[0] = 'w'; W.Length = 1;
	Kata A; A.TabKata[0] = 'a'; A.Length = 1;
	Kata S; S.TabKata[0] = 's'; S.Length = 1;
	Kata D; D.TabKata[0] = 'd'; D.Length = 1;
	Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.Length = 3;
	Kata BUILD; BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d'; BUILD.Length = 5;
	Kata UPGRADE; UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e'; UPGRADE.Length = 7;
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,W)));
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,A)));
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,S)));
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,D)));
	} else if (inpt == INPUT_i){
		state = MAIN_DAY;
		Hour(time) = 9 ;
		Minute(time) = 0;
		PrepToMainDay();
	} else if (inpt == INPUT_b){
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUY))){
			HandleBuy();
		} else {
			printf("Waktu tidak mencukupi untuk buy!"); getchar();
		}
	} else if (inpt == INPUT_1){
		state = INVENTORY;
	} else if (inpt == INPUT_l) {
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUILD))){
			HandleBuild();
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
	} else if(inpt == INPUT_k) { 
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,UPGRADE))){
			HandleUpgrade();
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
	} else if (inpt == INPUT_j){
		HandleUndo();
	} else if (inpt == INPUT_2){
		HandleExecution();
	}
}


void PrintPreparationDay() {
	// Menampilkan informasi pada bagian inti game saat preparation day
	JAM buka;
	Hour(buka) = 9;
	Minute(buka) = 0;
	if (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '>' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '<' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '^' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == 'V' ) {
		infotypePeta CurrentPos;
		CurrentPos.map = cmap;
		Absis(CurrentPos.p) = Absis(playerpos);
		Ordinat(CurrentPos.p) = Ordinat(playerpos);
		adrPeta P = SearchPeta(denah,CurrentPos);
		adrTerowongan T = Trail(P);
		P = T->Succ;
		cmap = idPeta(P).map;
		Absis(playerpos) = Absis(idPeta(P).p);
		Ordinat(playerpos) = Ordinat(idPeta(P).p);
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,Absis(playerpos),Ordinat(playerpos));
	printf("%s\n","");

	printf("Nama : %s		Uang: %d		Waktu sebelum buka: %d menit\n", "stranger", pmoney, Durasi(time, buka));
	printf("Material yang dibutuhkan: ");ArrayPair_TulisIsiTab(need_material);printf("\n");
	printf("Aksi yang akan dilakukan : %d		Uang yang dibutuhkan: %d		Waktu yang dibutuhkan: %d\n", count_aksi, need_money, need_time);
	printf("%s","Jam : ");
	TulisJAM(time);
	printf("%s\n","");
	printf("%s\n","==================================================================");
	printf("%s\n","Stack of Your Action");
	PrintStack(aksi);
	printf("%s\n","==================================================================");
}

void InputOffice() {
	char input[100];
	Kata Office; Office.TabKata[0] = 'o'; Office.TabKata[1] = 'f'; Office.TabKata[2] = 'f'; Office.TabKata[3] = 'i'; Office.TabKata[4] = 'c'; Office.TabKata[5] = 'e'; Office.Length = 6;
	scanf("%s", &input);
	getchar();
	if(strcmp(input, "Details") == 0) {
		printf("Daftar Wahana :\n");
		printListWahana(&wahana);
		printf("\n");

		printf("Masukkan ID Wahana yang ingin dilihat detailnya : ");
		scanf("%c", &ChoosenWahana); getchar();
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Office)));
		state = OFFICE_DETAIL;
	} else if (strcmp(input, "Report") == 0) {
		printf("Daftar Wahana :\n");
		printListWahana(&wahana);
		printf("\n");

		printf("Masukkan ID Wahana yang ingin dilihat reportnya : ");
		scanf("%c", &ChoosenWahana); getchar();
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Office)));
		state = OFFICE_REPORT;
	} else if (strcmp(input, "Exit") == 0) {
		state = MAIN_DAY;
	}
}

// =======================================================================================================


// =========================================Fungsi Umum===================================================
void GameSetup (){
	// Setup awal untuk memulai game
	cmap = 0;
	ArrayPair_MakeEmpty(&Materials);
	ArrayPair_MakeEmpty(&Inventory);
	ArrayPair_MakeEmpty(&need_material);
	ArrayPair_MakeEmpty(&HargaBuild);
	ArrayPair_MakeEmpty(&MaterialBuild);
	ArrayPair_MakeEmpty(&ActionTime);
	BacaMATRIKS(&map[1], "../file/1.txt");
	BacaMATRIKS(&map[0], "../file/0.txt");
	BacaMATRIKS(&map[2], "../file/2.txt");
	BacaMATRIKS(&map[3], "../file/3.txt");
	ArrayPair_BacaIsi(&Materials, "../Saves/Materials.txt");
	ArrayPair_BacaIsi(&Inventory, "../Saves/Inventory.txt");
	ArrayPair_BacaIsi(&need_material, "../Saves/Inventory.txt");
	ArrayPair_BacaIsi(&HargaBuild, "../Saves/HargaBuild.txt");
	ArrayPair_BacaIsi(&MaterialBuild, "../Saves/MaterialBuild.txt");
	ArrayPair_BacaIsi(&ActionTime, "../Saves/ActionPrice.txt");
	Absis(playerpos) = 1;
	Ordinat(playerpos)= 1;
	BacaGraph(&denah,"../file/graph.txt");
	state = MAIN_DAY;
	CopyMATRIKS(map[cmap], &mapRoom);
	CreateEmpty(&aksi);
	count_aksi = 0 ;
	need_money = 0 ;
	pmoney = 10000 ;
	Hour(time) = 9 ;
	Minute(time) = 0 ;
	bacaWahana(&wahana, "../file/wahana.txt");
}

void PrintJudul (){
	// printf("%s\n","==================================================================");
	// printf("%s\n","==================================================================");  
	// printf("%s\n","*     __    __ _ _ _         __    __                  _          ");
	// printf("%s\n","*    / / /\ \ (_| | |_   _  / / /\ \ \__ _ _ __   __ _| | ___   _ ");   
	// printf("%s\n","*    \ \/  \/ | | | | | | | \ \/  \/ / _` | '_ \ / _` | |/ | | | |");   
	// printf("%s\n","*     \  /\  /| | | | |_| |  \  /\  | (_| | | | | (_| |   <| |_| |");   
	// printf("%s\n","*      \/  \/ |_|_|_|\__, |   \/  \/ \__,_|_| |_|\__, |_|\_\\__, |");   
	// printf("%s\n","*               __   |___/         _     _       |___/      |___/ ");   
	// printf("%s\n","*              / / /\ \ \___  _ __| | __| |                       ");   
	// printf("%s\n","*              \ \/  \/ / _ \| '__| |/ _` |                       ");   
	// printf("%s\n","*               \  /\  | (_) | |  | | (_| |                       ");   
	// printf("%s\n","*                \/  \/ \___/|_|  |_|\__,_|                       ");   
	// printf("%s\n","*                                                                 ");
	printf("%s\n","==================================================================");
	printf("%s\n","			Willy Wangky World						 ");
	printf("%s\n","==================================================================");                                 
}

void PrintMain(){
	switch (state) {
	case MAIN_MENU:
		// Kebutuhan menu
		break;
	case NEW_GAME:
		// Kebutuhan newgame
		break;
	case LOAD_GAME:
		// Kebutuhan load game
		break;
	case MAIN_DAY:
		PrintMainDay();
		break;
	case PREPARATION_DAY:
		PrintPreparationDay();
		break;
	case OFFICE:
		// List menu office diprint dan dipilih
		printf("\nSELAMAT DATANG DI OFFICE WILLY WANGKY'S WORLD!!!\n\n");
		break;
	case OFFICE_DETAIL:
		printDetailWahana(&wahana, ChoosenWahana);
		break;
	case OFFICE_REPORT:
		printReportWahana(&wahana, ChoosenWahana);
		break;
	case DETAIL_WAHANA:
		printDetailWahana(&wahana, ChoosenWahana);	
		break;
	case INVENTORY:
		printf("Inventory Anda\n");
		ArrayPair_TulisIsiTab(Inventory);printf("\n");
		break;
	default:
	printf("%s","Bukan state game");
		break;
	}
}


void BacaInput(){
	int inpt;
	switch (state) {
	case MAIN_MENU:
		// Input yang ada di main menu
		break;
	case NEW_GAME:
		// Input saat player mau new game
		break;
	case LOAD_GAME:
		// Input saat player mau load game
		break;
	case MAIN_DAY:
		inpt = GetInput();
		InputMainDay(inpt);
		break;
	case PREPARATION_DAY:
		inpt = GetInput();
		InputPreparationDay(inpt);
		break; 
	case OFFICE:
		InputOffice();
		break;
	case OFFICE_DETAIL:
		getchar();
		state = OFFICE;
		break;
	case OFFICE_REPORT:
		getchar();
		state = OFFICE;
		break;
	case DETAIL_WAHANA:
		getchar();
		state = MAIN_DAY;
		break;
	case INVENTORY: 
		getchar();
		state = PREPARATION_DAY;
		break ;
	default:
		printf("%s","Input tidak valid");
		break;
	}
}

void PrintFooter(){
	switch (state) {
	case MAIN_MENU:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","w : atas  s : bawah	 enter : pilih menu");
		break;
	case MAIN_DAY:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Main Day");
		printf("%s\n","	w : Atas   a : kiri   s : bawah   d: kanan   i: masuk ke preparation day");
		printf("%s\n","	1 : Enter Office  2: Lihat Detail Wahana  3: Repair Wahana");
		break;
	case PREPARATION_DAY:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Preparation Day");
		printf("%s\n","	w : atas a : kiri  s : bawah  d: kanan i: masuk ke main day");
		printf("%s\n"," b: buy l : build k : upgrade j : undo 2 : execute 1 : inventory" ); 
		break;
	case INVENTORY:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Inventory ");
		printf("%s\n","	Tekan apapun untuk kembali ke Preparation Phase");
		break;
	case DETAIL_WAHANA:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Detail Wahana");
		printf("%s\n","	Tekan apapun untuk kembali ke Main Phase");
		break;
	case NEW_GAME:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","					       Masukkan Nama 						 ");
		printf("%s\n","		   ketik enter untuk next, ketik lainnya untuk back	     ");
		break;
	case OFFICE:
		printf("%s\n","		           Tombol aksi				 ");
		printf("%s\n","	Menu Office");
		printf("\n%s\n","Details : Lihat Detail Wahana, Report : Melihat Report Wahana, \nExit : Keluar dari Office");
		break;
	case OFFICE_REPORT:
		printf("%s\n","		           Tombol aksi				 ");
		printf("%s\n","	Report Office");
		printf("%s\n","	Tekan apapun untuk kembali ke Menu Office");
		break;
	case OFFICE_DETAIL:
		printf("%s\n","		           Tombol aksi				 ");
		printf("%s\n","	Detail Office");
		printf("%s\n","	Tekan apapun untuk kembali ke Menu Office");
		break;
	default:
		printf("\n");
		break;
	}
}
void UserInterface(){
	clrscr();
	PrintJudul();
	printf("%s\n","		Have fun working with this!!				");
	PrintMain();
	printf("%s\n","==================================================================");
	PrintFooter();
	printf("%s\n","=================================================================="); 
	BacaInput();
	UserInterface();
}
// =======================================================================================================

int main(){
	GameSetup();
	UserInterface();
}