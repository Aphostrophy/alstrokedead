#include "queue.h"
#include "../mesinkata/mesinkar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

boolean IsEmpty_Queue (Queue Q){
    return (Q.TAIL==nil);
}

boolean IsFull_Queue (Queue Q){
    return (Q.TAIL==4);
}

int NBElmt_Queue (Queue Q){
    return (Q.TAIL+1);
}

void MakeEmpty_Queue (Queue * Q, int Max){
    (*Q).P = (pengunjung*) malloc ((Max) * sizeof(pengunjung));
    if ((*Q).P != NULL){
        MaxEl(*Q)=Max;
    }
    else{
        MaxEl(*Q)=0;
    }
    Tail(*Q)=nil;
}

void Dealokasi_Queue (Queue *Q){
    MaxEl(*Q) = 0;
    free((*Q).P); 
}


boolean IsDouble(char W, char L[3]){
    int count=0;
    for(int i=0;i<3;i++){
        if (L[i]==W){
            return true;
        }
    }
    return false;
}


//inisialisasi antrean pada program utama
void GenerateQueue (Queue * Q, Wahana LW){
    srand(time(0));
    int i,j;
    int idx=0;
    char wahana_queue[9];
    for(int i=0;i<9;i++){
        wahana_queue[i]='-';
    }
    
    for(int i=0;i<8;i++){
        if (LW.TI[i].status=='G'){
            wahana_queue[idx]=LW.TI[i].id.TabKata[0];
            idx=idx+1;
        }
    }

    idx = idx-1;
    MakeEmpty_Queue(Q,10);
    if (idx !=-1){ 
        for (i=0;i<5;i++){
            for (j=0;j<3;j++){
                if (j==0){
                    (*Q).P[i].L[j]=wahana_queue[rand() % (idx + 1 - 0) + 0];
                }
                else{
                    char W = wahana_queue[rand() % ((idx+1) + 1 - 0) + 0];
                    if(IsDouble(W,(*Q).P[i].L)){
                        (*Q).P[i].L[j]= '-';
                    }
                    else{
                        (*Q).P[i].L[j]= W;
                    }                
                }
            }

            if ((*Q).P[i].L[1]=='-'){
                (*Q).P[i].L[2]='-';
            }
            (*Q).P[i].S = 5;
            (*Q).P[i].X = (i+1);
            (*Q).P[i].T = 0;
            (*Q).P[i].ID = (i+1); 
            (*Q).P[i].W = '-';
            Tail(*Q)=Tail(*Q)+1;
        }
    }
    else{
        printf("Belum ada wahana yang dibangun\n");
    }
}


//Generate pengunjung baru yang bisa masuk ke queue di tengah permainan
void GeneratePengunjung(pengunjung *P,int ID,int prio, Wahana LW){
    Queue Q;
    GenerateQueue(&Q,LW);
    *P = Q.P[0];
    (*P).ID=ID;
    (*P).S=5;
    (*P).X=prio;
}


//'Melepas' head Queue dari Queue
void Dequeue (Queue * Q, pengunjung * X){
    if (!IsEmpty_Queue(*Q)){
        int i;
        *X = (*Q).P[0];
        for (i=1;i<=Tail(*Q);i++){
            (*Q).P[i-1]=(*Q).P[i];
        }
        (*Q).TAIL=(*Q).TAIL-1;
    }
}

//print queue
void PrintQueue (Queue Q, int n){
    int j=0;
    if(n==1){
        printf("[%d/5]\n",(Q.TAIL+1));
    }
    while (j<=Q.TAIL){
        int i=0;
        int count=0;
        printf("(");
        while (Q.P[j].L[i] != '-' && i<3){
            count=count+1;
            i=i+1;
        }
        i=0;
        while (Q.P[j].L[i] != '-' && i<3){
            switch (Q.P[j].L[i]){
                case 'S':
                    printf("SkyCoaster");
                    break;
                case 'P':
                    printf("PirateShip");
                    break;
                case 'T':
                    printf("Tornado");
                    break;
                case 'C':
                    printf("Carousel");
                    break;
                case 'H':
                    printf("HauntedHouse");
                    break;
                case 'F':
                    printf("FerrisWheel");
                    break;
                case 'B':
                    printf("BumperCars");
                    break;
                case 'G':
                    printf("GyroDrop");
                    break;
                default:
                    printf("ya gamungkin sih");  
            }

            if (i!=(count-1)){
                printf(",");
            }
            i=i+1;
        }
        printf(")");
        printf(", ");
        if (n==1){
            printf("kesabaran : %d , prio : %d //customer %d\n", Q.P[j].S, Q.P[j].X, Q.P[j].ID);
        }
        else if (n==2){
            printf("Kesabaran : %d , Prio : %d , ID wahana yang sedang dinaiki : %c , Waktu bermain tersisa : %d  //customer %d\n", Q.P[j].S,Q.P[j].X,  Q.P[j].W, Q.P[j].T, Q.P[j].ID);
        }
        
        j=j+1;
    }
}

//cek apakah list wahana kosong
boolean isListWahanaEmpty(char L[3]){
    return L[0]=='-';
}

//dequeue wahana dari list wahana pengunjung
void DequeueWahana(pengunjung *X,char W){
    int i,idx;
    boolean found=false;

    if(!isListWahanaEmpty((*X).L)){
        for(i=0;i<3;i++){
            if ((*X).L[i]==W){
                (*X).W=W;
                found=true;
                (*X).L[i]='-';
                idx=i;
            }
        }
        if(found){
            if(idx!=3){
                for(i=idx+1;i<3;i++){
                    (*X).L[i-1]=(*X).L[i];
                }
            }
            (*X).L[2]='-';
        }
    }
}

//mengosongkan queue yang terisi
void EmptyQueue(Queue *Q){
    pengunjung P;
    while(!IsEmpty_Queue(*Q)){
        Dequeue(Q,&P);
    }
    Dealokasi_Queue(Q);
}


//Memasukan pengunjung ke Queue
void Enqueue(Queue *Q, pengunjung P){
    boolean found=false;
    int i=0;

    if (IsEmpty_Queue(*Q)){
        (*Q).P[0]=P;
    }
    else{
        for (i=(*Q).TAIL;i>=0;i--){
            if ((*Q).P[i].X <= P.X){ //ver 1 pake < bukan <=
                found=true;
                for (int j=(*Q).TAIL;j>=(i+1);j--){
                    (*Q).P[j+1]=(*Q).P[j];
                }
            }
            if (found){
                break;
            }
        }
        if (found){
            (*Q).P[i+1]=P;
        }
        else if(found==false){
            for (int j=(*Q).TAIL;j>=0;j--){
                (*Q).P[j+1]=(*Q).P[j];
            }
            (*Q).P[0]=P;            
        }
    }
    (*Q).TAIL=(*Q).TAIL+1;
}

//Mengurangi kesabaran untuk seluruh pengunjung pada queue
void ReduceKesabaran(Queue *Q){
    if(!IsEmpty_Queue(*Q)){
        for(int i=0;i<=(*Q).TAIL;i++){
            (*Q).P[i].S--;
            (*Q).P[i].X--;
        }
    }
}

//Mengurangi durasi bermain untuk seluruh pengunjung pada queue bermain
void ReduceTime(Queue *Q,int Time,Wahana LW){
    if(!IsEmpty_Queue(*Q)){
        for(int i=0;i<=(*Q).TAIL;i++){
            InfoWahana WahanaQ = getWahanabyID(&LW,(*Q).P[i].W);
            if (WahanaQ.status == 'G'){
                (*Q).P[i].T = (*Q).P[i].T - Time;
            }   
        }
    }  
}

//Prosedur untuk mengeluarkan pengunjung yang sudah habis sisa waktu bermainnya dari queue bermain
//Apabila pengunjung masih memiliki wahana yang ingin dinaiki maka pengunjung akan dikembalikan ke queue utama
void LeaveQueueT(Queue *M, Queue *Q, Wahana *LW){
    int idx[5];
    int lastidx=0;
    for (int i=0;i<=(*M).TAIL;i++){
        if ((*M).P[i].T <= 0){
            idx[lastidx]=i;
            lastidx++;
        }
    }
    lastidx=lastidx-1;
    for(int i=0;i<=lastidx;i++){
        pengunjung X;
        X = (*M).P[idx[i]];

        int idxW = GetIndex(LW,X.W);
        (*LW).TI[idxW].inside--;

        if(isListWahanaEmpty(X.L)==false){
            X.X=X.X-1; //masukin ke queue main
            Enqueue(Q,X);
        }
        for(int j=idx[i];j<=(*M).TAIL;j++){
            (*M).P[j]=(*M).P[j+1];
        }
        for(int k=i;k<=lastidx;k++){
            idx[k]=idx[k]-1;
        }
        (*M).TAIL=(*M).TAIL-1;
    }
}

//Mendapatkan indeks terakhir dari list wahana yang ingin dinaiki pengunjung
int getLastIdxListW(char L[3]){
    int idx=-1;
    for(int i=0;i<3;i++){
        if (L[i] != '-'){
            idx = i;
            break;
        }
    }
    return idx;
}


//Prosedur untuk memaksa keluar pengunjung yang tengah menaiki wahana rusak, pengunjung akan dikembalikan ke queue utama
void LeaveWahanaBroke(Queue *M, Queue *Q, Wahana *W){
    int idx[5];
    int lastidx=0;
    for (int i=0;i<=(*M).TAIL;i++){
        InfoWahana NaikWahana = getWahanabyID(W,(*M).P[i].W);
        if (NaikWahana.status=='B'){
            idx[lastidx]=i;
            lastidx++;
        }
    }
    lastidx=lastidx-1;
    for(int i=0;i<=lastidx;i++){
        pengunjung X;
        X = (*M).P[idx[i]];

        int idxW = GetIndex(W,X.W);
        (*W).TI[idxW].inside--;

        int idxL = getLastIdxListW(X.L);
        X.L[idxL+1] = X.W;
        X.X=X.X-1; //masukin ke queue utama
        if(!IsFull_Queue(*Q)){
            Enqueue(Q,X);
        }
        for(int j=idx[i];j<=(*M).TAIL;j++){
            (*M).P[j]=(*M).P[j+1];
        }
        for(int k=i;k<=lastidx;k++){
            idx[k]=idx[k]-1;
        }
        (*M).TAIL=(*M).TAIL-1;
    }
}

//mengecek queue lalu me-remove pengunjung pada queue yang sudah memiliki kesabaran negatif
void LeaveQueueS(Queue *Q){
    int idx[5];
    int lastidx=0;

    for (int i=0;i<=(*Q).TAIL;i++){
        if ((*Q).P[i].S <= 0){
            idx[lastidx]=i;
            lastidx++;
        }
    }
    lastidx=lastidx-1;
    for(int i=0;i<=lastidx;i++){
        for(int j=idx[i];j<=(*Q).TAIL;j++){
            (*Q).P[j]=(*Q).P[j+1];
        }
        for(int k=i;k<=lastidx;k++){
            idx[k]=idx[k]-1;
        }
        (*Q).TAIL=(*Q).TAIL-1;
    }
}

//Mengecek apakah suatu ID wahana ada pada list wahana pengunjung
boolean IsWahanaInList(char W, Queue Q){
    boolean isTrue=false;
    int i=0;
    while (isTrue==false && i<3){
        if(W==Q.P[0].L[i]){
            isTrue=true;
        }
        else{
            i=i+1;
        }
    }
    return isTrue;
}

//Prosedur melakukan serve
void Serve(Queue *Q, Queue *M, char W, Wahana *LW, int *pmoney){

    InfoWahana Swahana=getWahanabyID(LW,W);
    if (Swahana.status=='G' && (Swahana.inside < Swahana.kapasitas)){
        if (IsWahanaInList(W,*Q)){
            pengunjung X;
            
            // //Dequeue
            Dequeue(Q,&X);
            DequeueWahana(&X,W);

            X.W=W;
            //set durasi bermain pengunjung
            X.T=getDurasi(LW,W);

            //masukin pengunjung ke array bermain global
            Enqueue(M,X);
        
            //increment inside wahana
            int N= GetIndex(LW,W);
            LW->TI[N].inside++;
            LW->TI[N].total_pengunjung++;
            LW->TI[N].total_penghasilan=LW->TI[N].total_penghasilan+LW->TI[N].harga;
            LW->TI[N].penghasilan=LW->TI[N].penghasilan+LW->TI[N].harga;
            LW->TI[N].pengunjung++;

            //kurangi kesabaran & naikin prioritas orang di antrian
            ReduceKesabaran(Q);

            //tambah duit
            *pmoney=*pmoney+getHarga(LW,W);
        }
        else{
            printf("Masukan wahana salah! Tekan apapun untuk melanjutkan\n");
            getchar();	
        }
    }
    else{
        printf("Wahana sedang rusak atau telah memenuhi kapasitas, tekan apapun untuk melanjutkan");
        ReduceKesabaran(Q);
        getchar();
    }
}

void ManageTime(int time, Queue *Q, Queue *M,Wahana LW){
    ReduceTime(M,time,LW);
    LeaveQueueS(Q);
    LeaveQueueT(M,Q,&LW);
}
