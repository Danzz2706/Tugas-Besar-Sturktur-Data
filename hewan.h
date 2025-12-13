#ifndef HEWAN_H_INCLUDED
#define HEWAN_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

// --- Definisi Data ---
struct Owner {
    string id;
    string nama;
    // Tambahkan data lain jika perlu
};

struct Pet {
    string id;
    string nama;
    string jenis; // misal: Kucing, Anjing
};

// --- Definisi Pointer ---
typedef struct elmOwner* adrOwner;
typedef struct elmPet* adrPet;
typedef struct elmRelation* adrRelation;

// --- Definisi Element List ---

// List Parent (Double Linked List sesuai diagram)
struct elmOwner {
    Owner info;
    adrOwner next;
    adrOwner prev;
};

// List Child (Single Linked List)
struct elmPet {
    Pet info;
    adrPet next;
};

// List Relasi (Single Linked List)
// Menyimpan pointer ke Parent dan pointer ke Child
struct elmRelation {
    adrOwner ownerPtr; // Pointer ke elemen Parent
    adrPet petPtr;     // Pointer ke elemen Child
    adrRelation next;
};

// --- Definisi List ---
struct ListOwner {
    adrOwner first;
    adrOwner last;
};

struct ListPet {
    adrPet first;
};

struct ListRelation {
    adrRelation first;
};

// --- Primitif Dasar ---
void createListOwner(ListOwner &L);
void createListPet(ListPet &L);
void createListRelation(ListRelation &L);

adrOwner alokasiOwner(string id, string nama);
adrPet alokasiPet(string id, string nama, string jenis);
adrRelation alokasiRelation(adrOwner P, adrPet C);

// --- a. Insert Element Parent ---
void insertOwner(ListOwner &L, adrOwner P);

// --- b. Insert Element Child ---
void insertPet(ListPet &L, adrPet C);

// --- c. Insert Element Relation ---
// Menghubungkan Parent dan Child berdasarkan ID mereka
void connect(ListRelation &LR, ListOwner LP, ListPet LC, string idOwner, string idPet);

// --- d. Delete Element Parent ---
// Hapus parent dan semua relasinya
void deleteOwner(ListOwner &LP, ListRelation &LR, string idOwner);

// --- e. Delete Element Child ---
// Hapus child dan semua relasinya
void deletePet(ListPet &LC, ListRelation &LR, string idPet);

// --- f. Delete Element Relation ---
// Putus hubungan tertentu antara Owner dan Pet
void disconnect(ListRelation &LR, string idOwner, string idPet);

// --- g. Find Element Parent ---
adrOwner findOwner(ListOwner L, string id);

// --- h. Find Element Child ---
adrPet findPet(ListPet L, string id);

// --- i. Find Relasi ---
// Cek apakah Owner X punya Hewan Y
adrRelation findRelation(ListRelation L, string idOwner, string idPet);

// --- j. Show All Parent ---
void printOwners(ListOwner L);

// --- k. Show All Child ---
void printPets(ListPet L);

// --- l. Show Data Child dari Parent Tertentu ---
// Menampilkan semua hewan milik Owner X
void printPetsByOwner(ListRelation LR, string idOwner);

// --- m. Show Data Parent dari Child Tertentu ---
// Menampilkan siapa saja pemilik Hewan Y
void printOwnersByPet(ListRelation LR, string idPet);

// --- n. Show Setiap Parent beserta Child-nya ---
void printAllOwnersWithPets(ListOwner LP, ListRelation LR);

// --- o. Show Setiap Child beserta Parent-nya ---
void printAllPetsWithOwners(ListPet LC, ListRelation LR);

// --- p. Count Child dari Parent Tertentu ---
int countPetsOfOwner(ListRelation LR, string idOwner);

// --- q. Count Parent dari Child Tertentu ---
int countOwnersOfPet(ListRelation LR, string idPet);

// --- r. Count Child yang tidak punya Parent (Liar/Belum diadopsi) ---
int countOrphanPets(ListPet LC, ListRelation LR);

// --- s. Count Parent yang tidak punya Child ---
int countChildlessOwners(ListOwner LP, ListRelation LR);

// --- t. Edit Relasi ---
// Mengganti kepemilikan atau mengganti hewan
void editRelation(ListRelation &LR, ListOwner LP, ListPet LC, string oldOwnerID, string oldPetID, string newOwnerID, string newPetID);

// --- u. Update Data Owner ---
void updateOwner(ListOwner &L, string id, string newNama);

// --- v. Update Data Pet ---
void updatePet(ListPet &L, string id, string newNama, string newJenis);

// --- w. Sort Owner by Name (Ascending) ---
void sortOwnersByNama(ListOwner &L);

#endif // HEWAN_H_INCLUDED
