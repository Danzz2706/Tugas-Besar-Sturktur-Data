#ifndef HEWAN_H_INCLUDED
#define HEWAN_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/* =====================================================
   ================ STRUKTUR DATA ======================
   ===================================================== */

// -------- DATA --------
struct Owner {
    string id;
    string nama;
};

struct Pet {
    string id;
    string nama;
    string jenis;
};

// -------- POINTER TYPE --------
typedef struct elmOwner* adrOwner;
typedef struct elmPet* adrPet;
typedef struct elmRelation* adrRelation;

// -------- ELEMEN LIST --------

// Parent List (Double Linked List)
struct elmOwner {
    Owner info;
    adrOwner next;
    adrOwner prev;
};

// Child List (Single Linked List)
struct elmPet {
    Pet info;
    adrPet next;
};

// Relation List (Single Linked List)
struct elmRelation {
    adrOwner ownerPtr;
    adrPet petPtr;
    adrRelation next;
};

// -------- LIST --------
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

/* =====================================================
   ================ PRIMITIF DASAR =====================
   ===================================================== */

void createListOwner(ListOwner &L);
void createListPet(ListPet &L);
void createListRelation(ListRelation &L);

adrOwner alokasiOwner(string id, string nama);
adrPet alokasiPet(string id, string nama, string jenis);
adrRelation alokasiRelation(adrOwner O, adrPet P);

/* =====================================================
   ================ INSERT ==============================
   ===================================================== */

void insertOwner(ListOwner &L, adrOwner O);
void insertPet(ListPet &L, adrPet P);
void connect(ListRelation &LR, ListOwner LO, ListPet LP, string idOwner, string idPet);

/* =====================================================
   ================ DELETE ==============================
   ===================================================== */

void deleteOwner(ListOwner &LO, ListRelation &LR, string idOwner);
void deletePet(ListPet &LP, ListRelation &LR, string idPet);
void disconnect(ListRelation &LR, string idOwner, string idPet);

/* =====================================================
   ================ SEARCH ==============================
   ===================================================== */

adrOwner findOwner(ListOwner L, string id);
adrPet findPet(ListPet L, string id);
adrRelation findRelation(ListRelation L, string idOwner, string idPet);

/* =====================================================
   ================ DISPLAY (LOGIC) =====================
   ===================================================== */

void printOwners(ListOwner L);
void printPets(ListPet L);
void printPetsByOwner(ListRelation LR, string idOwner);
void printOwnersByPet(ListRelation LR, string idPet);
void printAllOwnersWithPets(ListOwner LO, ListRelation LR);
void printAllPetsWithOwners(ListPet LP, ListRelation LR);

/* =====================================================
   ================ DISPLAY (UI TABLE) ==================
   ===================================================== */

void printOwnersTable(ListOwner LO);
void printPetsTable(ListPet LP);
void printOwnersWithPetsTable(ListOwner LO, ListRelation LR);
void printPetsWithOwnersTable(ListPet LP, ListRelation LR);

/* =====================================================
   ================ COUNT / STAT ========================
   ===================================================== */

int countPetsOfOwner(ListRelation LR, string idOwner);
int countOwnersOfPet(ListRelation LR, string idPet);
int countOrphanPets(ListPet LP, ListRelation LR);
int countChildlessOwners(ListOwner LO, ListRelation LR);

/* =====================================================
   ================ EDIT / UPDATE =======================
   ===================================================== */

void editRelation(
    ListRelation &LR,
    ListOwner LO,
    ListPet LP,
    string oldOwnerID,
    string oldPetID,
    string newOwnerID,
    string newPetID
);

void updateOwner(ListOwner &L, string id, string newNama);
void updatePet(ListPet &L, string id, string newNama, string newJenis);

/* =====================================================
   ================ SORT ================================
   ===================================================== */

void sortOwnersByNama(ListOwner &L);

#endif // HEWAN_H_INCLUDED

