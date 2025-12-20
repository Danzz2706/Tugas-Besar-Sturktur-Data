#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "hewan.h"

using namespace std;

/* ================= UTIL UI ================= */

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore();
    cin.get();
}

void printLine(int len = 70) {
    for (int i = 0; i < len; i++) cout << "=";
    cout << endl;
}

/* ================= VALIDATION ================= */

bool isInteger(string s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string getValidOwnerID(ListOwner L) {
    string id;
    while (true) {
        cout << "ID Owner (Angka) : ";
        cin >> id;
        if (!isInteger(id)) {
            cout << "Error: ID harus berupa angka!\n";
        } else if (findOwner(L, id) != NULL) {
            cout << "Error: ID sudah digunakan!\n";
        } else {
            return id;
        }
    }
}

bool isOwnerNameExists(ListOwner L, string nama) {
    adrOwner P = L.first;
    while (P != NULL) {
        if (P->info.nama == nama) {
            return true;
        }
        P = P->next;
    }
    return false;
}

string getValidOwnerName(ListOwner L) {
    string nama;
    while (true) {
        cout << "Nama Owner : ";
        cin >> nama;
        if (isOwnerNameExists(L, nama)) {
            cout << "Error: Nama Owner sudah ada!\n";
        } else {
            return nama;
        }
    }
}

string getValidPetID(ListPet L) {
    string id;
    while (true) {
        cout << "ID Pet (Angka)   : ";
        cin >> id;
        if (!isInteger(id)) {
            cout << "Error: ID harus berupa angka!\n";
        } else if (findPet(L, id) != NULL) {
            cout << "Error: ID sudah digunakan!\n";
        } else {
            return id;
        }
    }
}

/* ================= MENU ================= */

void showMenu() {
    printLine();
    cout << "   APLIKASI MANAJEMEN HEWAN & PEMILIK (MULTI LINKED LIST)\n";
    printLine();
    cout << "|  1 | Insert Owner (Parent)                           |\n";
    cout << "|  2 | Insert Pet (Child)                              |\n";
    cout << "|  3 | Connect Owner & Pet                             |\n";
    cout << "|  4 | Show All Owners                                 |\n";
    cout << "|  5 | Show All Pets                                   |\n";
    cout << "|  6 | Show Owners beserta Hewannya                    |\n";
    cout << "|  7 | Show Pets beserta Pemiliknya                    |\n";
    cout << "|  8 | Cari Hewan milik Owner                          |\n";
    cout << "|  9 | Cari Pemilik dari Hewan                         |\n";
    cout << "| 10 | Delete Relation                                 |\n";
    cout << "| 11 | Delete Owner (Cascade Delete)                   |\n";
    cout << "| 12 | Delete Pet (Cascade Delete)                     |\n";
    cout << "| 13 | Statistik                                       |\n";
    cout << "| 14 | Edit Relation (Pindah Tangan)                   |\n";
    cout << "| 15 | Edit Data Owner                                 |\n";
    cout << "| 16 | Edit Data Pet                                   |\n";
    cout << "| 17 | Sort Owner by Name (Ascending)                  |\n";
    cout << "|  0 | Exit                                            |\n";
    printLine();
    cout << "Pilihan : ";
}

/* ================= MAIN ================= */

int main() {
    ListOwner LO;
    ListPet LP;
    ListRelation LR;

    createListOwner(LO);
    createListPet(LP);
    createListRelation(LR);

    /* ================= DATA DUMMY ================= */

    // OWNER
    insertOwner(LO, alokasiOwner("1", "Budi"));
    insertOwner(LO, alokasiOwner("2", "Siti"));
    insertOwner(LO, alokasiOwner("3", "Andi"));

    // PET
    insertPet(LP, alokasiPet("1", "Molly", "Kucing"));
    insertPet(LP, alokasiPet("2", "Bruno", "Anjing"));
    insertPet(LP, alokasiPet("3", "Tweety", "Burung"));
    insertPet(LP, alokasiPet("4", "Nemo", "Ikan"));

    // RELATION
    connect(LR, LO, LP, "1", "1"); // Budi - Molly
    connect(LR, LO, LP, "1", "2"); // Budi - Bruno
    connect(LR, LO, LP, "2", "1"); // Siti - Molly (shared)
    connect(LR, LO, LP, "3", "4"); // Andi - Nemo


    int choice;
    string choiceStr;
    string id1, id2, id3, id4, nama, jenis;

    do {
        clearScreen();
        showMenu();
        cin >> choiceStr;
        cin.ignore();

        if (isInteger(choiceStr)) {
            choice = atoi(choiceStr.c_str());
        } else {
            choice = -1;
        }

        clearScreen();

        switch (choice) {

        case 1:
            cout << "--- INSERT OWNER ---\n";
            // cout << "ID Owner   : "; cin >> id1;
            id1 = getValidOwnerID(LO);
            // cout << "Nama Owner : "; cin >> nama;
            nama = getValidOwnerName(LO);
            insertOwner(LO, alokasiOwner(id1, nama));
            pauseScreen();
            break;

        case 2:
            cout << "--- INSERT PET ---\n";
            // cout << "ID Pet : "; cin >> id1;
            id1 = getValidPetID(LP);
            cout << "Nama   : "; cin >> nama;
            cout << "Jenis  : "; cin >> jenis;
            insertPet(LP, alokasiPet(id1, nama, jenis));
            pauseScreen();
            break;

        case 3:
            cout << "--- CONNECT OWNER & PET ---\n";
            cout << "ID Owner : "; cin >> id1;
            cout << "ID Pet   : "; cin >> id2;
            connect(LR, LO, LP, id1, id2);
            pauseScreen();
            break;

        case 4:
            printOwnersTable(LO);
            pauseScreen();
            break;

        case 5:
            printPetsTable(LP);
            pauseScreen();
            break;

        case 6:
            printOwnersWithPetsTable(LO, LR);
            pauseScreen();
            break;

        case 7:
            printPetsWithOwnersTable(LP, LR);
            pauseScreen();
            break;

        case 8:
            cout << "--- CARI HEWAN MILIK OWNER ---\n";
            cout << "ID Owner: "; cin >> id1;
            printPetsByOwner(LR, id1);
            pauseScreen();
            break;

        case 9:
            cout << "--- CARI PEMILIK DARI HEWAN ---\n";
            cout << "ID Pet: "; cin >> id1;
            printOwnersByPet(LR, id1);
            pauseScreen();
            break;

        case 10:
            cout << "--- DELETE RELATION ---\n";
            cout << "ID Owner : "; cin >> id1;
            cout << "ID Pet   : "; cin >> id2;
            disconnect(LR, id1, id2);
            pauseScreen();
            break;

        case 11:
            cout << "--- DELETE OWNER ---\n";
            cout << "ID Owner: "; cin >> id1;
            deleteOwner(LO, LR, id1);
            pauseScreen();
            break;

        case 12:
            cout << "--- DELETE PET ---\n";
            cout << "ID Pet: "; cin >> id1;
            deletePet(LP, LR, id1);
            pauseScreen();
            break;

        case 13:
            cout << "--- STATISTIK ---\n";
            cout << "Hewan tak bertuan : " << countOrphanPets(LP, LR) << endl;
            cout << "Owner tanpa hewan : " << countChildlessOwners(LO, LR) << endl;
            pauseScreen();
            break;

        case 14:
            cout << "--- EDIT RELATION ---\n";
            cout << "Old Owner ID : "; cin >> id1;
            cout << "Old Pet ID   : "; cin >> id2;
            cout << "New Owner ID : "; cin >> id3;
            cout << "New Pet ID   : "; cin >> id4;
            editRelation(LR, LO, LP, id1, id2, id3, id4);
            pauseScreen();
            break;

        case 15:
            cout << "--- EDIT DATA OWNER ---\n";
            cout << "ID Owner : "; cin >> id1;
            cout << "Nama Baru: "; cin >> nama;
            updateOwner(LO, id1, nama);
            pauseScreen();
            break;

        case 16:
            cout << "--- EDIT DATA PET ---\n";
            cout << "ID Pet    : "; cin >> id1;
            cout << "Nama Baru : "; cin >> nama;
            cout << "Jenis Baru: "; cin >> jenis;
            updatePet(LP, id1, nama, jenis);
            pauseScreen();
            break;

        case 17:
            sortOwnersByNama(LO);
            cout << "Owner berhasil diurutkan (A-Z).\n";
            pauseScreen();
            break;

        case 0:
            cout << "Keluar dari program...\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
            pauseScreen();
        }

    } while (choice != 0);

    return 0;
}

