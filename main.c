#include <stdio.h>
#include <stdlib.h>

#include "lib/data_structure/data_type.h"
#include "lib/data_structure/gdt/game_data_type.h"
#include "lib/handler/handler_include.h"

#define initialX 4
#define initialY 4


GameState gameState;
Player player;
Queue CustomerQueue;

Object *ArrayOfMeja[13];

Matrix Map1, Map2, Map3, Kitchen;

void PrintAllOrder(){
    for (int i = 1; i <= 12; i++){
        if (IsOccupied(*(ArrayOfMeja[i]))){
            printf("Meja No.%d memesan OrderID %d.\n", i, OrdersAt(*(ArrayOfMeja[i])));
        }else {
            printf("Meja No.%d kosong.\n", i);
        }
    }
}

void PrintAllMemory(Matrix M){
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            printf("ALAMAT MEMORY M KE %d-%d adalah %p.\n", i, j, &(M.Mem[i][j]));
        }
    }
}

void Dealokasi_All_Meja(){
    for (int i = 1; i <= 12; i++){
        if (IsOccupied(*(ArrayOfMeja[i]))){
            Dealokasi_Customer((*(ArrayOfMeja[i])).data.table.customer_here);
            printf("Meja nomor %d terisi dan sudah di dealokasi.\n", TableNumber(*(ArrayOfMeja[i])));
        }
    }
}

void Init(){
    Create_New_Player(&player);
    LoadMap(&Map1, &Map2, &Map3, &Kitchen);

    printf("Init\n");
    PrintAllMemory(Map1);

    /*
        Melakukan inisialisasi dari array of pointer ArrayOfMeja.
        ArrayOfMeja akan berisi pointer menuju semua objek meja sesuai nomornya.
        Sebagai contoh, ketika diakses *(ArrayOfMeja[3]) maka akan diakses
        memori yang menyimpan objek yang merupakan meja dengan nomor meja 3.
    */
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                ArrayOfMeja[ElmtMx(Map1, i, j).data.table.num] = &(ElmtMx(Map1, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                ArrayOfMeja[ElmtMx(Map2, i, j).data.table.num] = &(ElmtMx(Map2, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                ArrayOfMeja[ElmtMx(Map3, i, j).data.table.num] = &(ElmtMx(Map3, i, j));
            }
        }
    }

    player.currentMap = &Map1;

    Absis(player.pos) = initialX;
    Ordinat(player.pos) = initialY;

    SetTag_Matrix(player.currentMap, initialX, initialY, PLAYER_POS);
}

void CustomerGenerator(){
    if (!IsFull_Queue(CustomerQueue)){
        Customer *newCustomer;
        newCustomer = GenerateCustomer();

        printf("New Customer\n");
        printCustomer(*newCustomer);

        Add_Queue(&CustomerQueue, newCustomer);
    }
}

void InputProcessor(char input[], int input_length){
    Kata processedInput;
    isiKata(&processedInput, input, input_length);
    
    Kata quitInput;
    isiKata(&quitInput, "quit", 4);

    Kata statusInput;
    isiKata(&statusInput, "status", 6);

    Kata moveInputUp;
    isiKata(&moveInputUp, "GU", 2);

    Kata moveInputDown;
    isiKata(&moveInputDown, "GD", 2);

    Kata moveInputLeft;
    isiKata(&moveInputLeft, "GL", 2);

    Kata moveInputRight;
    isiKata(&moveInputRight, "GR", 2);

    Kata queueInput;
    isiKata(&queueInput, "queue", 5);

    Kata allOrderInput;
    isiKata(&allOrderInput, "allOrder", 8);

    Kata placeInput;
    isiKata(&placeInput, "place", 5);

    Kata checkInput;
    isiKata(&checkInput, "check", 5);

    Kata memoryInput;
    isiKata(&memoryInput, "memcheck", 8);

    Kata helpInput;
    isiKata(&helpInput, "help", 4);

    if (IsKataSama(processedInput, quitInput)){
        gameState = CREDITS;
    }else if (IsKataSama(processedInput, statusInput)){
        Print_Player(player);
    }else if (IsKataSama(processedInput, moveInputUp)){
        Move_Player_Direction(player.currentMap, &player, UP);
        CustomerGenerator(&CustomerQueue);
    }else if (IsKataSama(processedInput, moveInputDown)){
        Move_Player_Direction(player.currentMap, &player, DOWN);
        CustomerGenerator(&CustomerQueue);
    }else if (IsKataSama(processedInput, moveInputLeft)){
        Move_Player_Direction(player.currentMap, &player, LEFT);
        CustomerGenerator(&CustomerQueue);
    }else if (IsKataSama(processedInput, moveInputRight)){
        Move_Player_Direction(player.currentMap, &player, RIGHT);
        CustomerGenerator(&CustomerQueue);
    }else if (IsKataSama(processedInput, queueInput)){
        Print_Queue(CustomerQueue);
    }else if (IsKataSama(processedInput, allOrderInput)){
        PrintAllOrder();
    }else if (IsKataSama(processedInput, checkInput)){
        Object * ClosestTable = Closest_Empty_Table(player, (player.currentMap));
    }else if (IsKataSama(processedInput, memoryInput)){
        PrintAllMemory(Map1);
    }else if (IsKataSama(processedInput, placeInput)){
        Object * ClosestTable = Closest_Empty_Table(player, (player.currentMap));
        if (ClosestTable != NULL){
            printf("Meja dengan nomor %d kosong.\n", (*ClosestTable).data.table.num);
            if (!IsEmpty_Queue(CustomerQueue)){
                Customer * CustomerToPlace = InfoHead(CustomerQueue);
                boolean successfulPlace = PlaceCustomerToTable(ClosestTable, (*CustomerToPlace));
                if (successfulPlace){
                    Del_Queue(&CustomerQueue, &CustomerToPlace);
                }
                if (IsOccupied(*ClosestTable)){
                    printf("Sekarang meja nomor %d sudah diduduki.\n", TableNumber(*ClosestTable));
                }
                if (IsOccupied(*(ArrayOfMeja[(*ClosestTable).data.table.num]))){
                    printf("VERSI2 Sekarang meja nomor %d sudah diduduki.\n", TableNumber(*ClosestTable));
                }
            }
        }else {
            printf("Tidak ada meja kosong disekitarmu!\n");
        }
    } else if(IsKataSama(processedInput, helpInput)){
        printf("Ketik help untuk melihat daftar command.\n");
        printf("Ketik GU untuk memindahkan player ke atas.\n");
        printf("Ketik GD untuk memindahkan player ke bawah.\n");
        printf("Ketik GL untuk memindahkan player ke kiri.\n");
        printf("Ketik GR untuk memindahkan player ke kanan.\n");
        printf("Ketik allOrder untuk melihat order untuk setiap meja.\n");
        printf("Ketik queue untuk melihat antrian saat ini\n");
        printf("Ketik status untuk melihat status pemain\n");
        printf("Ketik place untuk mengecek petak sekitar");
        printf("Ketik quit untuk keluar dari permainan.\n");
    }
}

void MainScreen(){
    printf("Main Screen\n");
    char rawInput[10] = "";
    while (gameState == MAIN_MENU){
        Create_New_Player(&player);
        printf("Welcome to Dapur Sadikin!\n");
        printf("What is your name?\n");
        printf("Name : ");
        scanf("%s", &rawInput);
        Set_Player_Name(&player, rawInput, 10);
        printf("Selamat datang, ");
        printKata(player.name);
        printf(".\n");
        gameState = IN_GAME;
    }
}

void MainGame(){
    printf("Main Game\n");
    PrintAllMemory(Map1);

    char rawInput[10] = "";

    CreateEmpty_Queue(&CustomerQueue, 5);

    while (gameState == IN_GAME){
        /*
        printf("Map 1\n");
        Print_Room(Map1);
        printf("Map 2\n");
        Print_Room(Map2);
        printf("Map 3\n");
        Print_Room(Map3);
        printf("Dapur\n");
        Print_Kitchen(Kitchen);
        */
        printf("Input : ");
        scanf("%s", &rawInput);
        InputProcessor(rawInput, 10);
        Print_Room(*(player.currentMap));
    }
    DeAlokasi_Queue(&CustomerQueue);
    Dealokasi_All_Meja();
}

int main(){
    Init();
    printf("After init\n");
    PrintAllMemory(Map1);
    printf("After init2\n");
    PrintAllMemory(Map1);

    gameState = MAIN_MENU;
    printf("%d\n", gameState);

    MainScreen();
    printf("After mainscreen\n");
    PrintAllMemory(Map1);
    printf("After mainscreen2\n");
    PrintAllMemory(Map1);

    MainGame();

    gameState = CREDITS;
    printf("%d\n", gameState);

    printf("Before quit\n");
    PrintAllMemory(Map1);
    printf("Before quit2\n");
    PrintAllMemory(Map1);
}