#include "hewan.h"
void createListOwner(ListOwner &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void createListPet(ListPet &L) {
    L.first = nullptr;
}

void createListRelation(ListRelation &L) {
    L.first = nullptr;
}

adrOwner alokasiOwner(string id, string nama) {
    adrOwner P = new elmOwner;
    P->info.id = id;
    P->info.nama = nama;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

adrPet alokasiPet(string id, string nama, string jenis) {
    adrPet P = new elmPet;
    P->info.id = id;
    P->info.nama = nama;
    P->info.jenis = jenis;
    P->next = nullptr;
    return P;
}

adrRelation alokasiRelation(adrOwner P, adrPet C) {
    adrRelation R = new elmRelation;
    R->ownerPtr = P;
    R->petPtr = C;
    R->next = NULL;
    return R;
}

// ---------------- INSERT (A, B) ----------------
void insertOwner(ListOwner &L, adrOwner P) {
    // Insert Last (Double Linked List)
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void insertPet(ListPet &L, adrPet C) {
    // Insert Last (Single Linked List)
    if (L.first == nullptr) {
        L.first = C;
    } else {
        adrPet Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
    }
}

// ---------------- FIND (G, H) ----------------
adrOwner findOwner(ListOwner L, string id) {
    adrOwner P = L.first;
    while (P != nullptr) {
        if (P->info.id == id) return P;
        P = P->next;
    }
    return nullptr;
}

adrPet findPet(ListPet L, string id) {
    adrPet P = L.first;
    while (P != nullptr) {
        if (P->info.id == id) return P;
        P = P->next;
    }
    return nullptr;
}

adrRelation findRelation(ListRelation L, string idOwner, string idPet) {
    adrRelation R = L.first;
    while (R != nullptr) {
        if (R->ownerPtr->info.id == idOwner && R->petPtr->info.id == idPet) {
            return R;
        }
        R = R->next;
    }
    return nullptr;
}

// ---------------- CONNECT / INSERT RELASI (C) ----------------
void connect(ListRelation &LR, ListOwner LP, ListPet LC, string idOwner, string idPet) {
    adrOwner O = findOwner(LP, idOwner);
    adrPet P = findPet(LC, idPet);

    if (O != NULL && P != nullptr) {
        // Cek apakah sudah ada relasi
        if (findRelation(LR, idOwner, idPet) == nullptr) {
            adrRelation R = alokasiRelation(O, P);
            // Insert First pada Relasi (biar cepat)
            R->next = LR.first;
            LR.first = R;
            cout << "Berhasil menghubungkan " << O->info.nama << " dengan " << P->info.nama << endl;
        } else {
            cout << "Relasi sudah ada." << endl;
        }
    } else {
        cout << "Owner atau Pet tidak ditemukan." << endl;
    }
}

// ---------------- DELETE (D, E, F) ----------------
void disconnect(ListRelation &LR, string idOwner, string idPet) {
    // Menghapus node relasi tertentu
    adrRelation P = LR.first;
    adrRelation Prev = nullptr;
    bool found = false;

    while (P != nullptr && !found) {
        if (P->ownerPtr->info.id == idOwner && P->petPtr->info.id == idPet) {
            found = true;
        } else {
            Prev = P;
            P = P->next;
        }
    }

    if (found) {
        if (Prev == nullptr) { // Hapus elemen pertama
            LR.first = P->next;
        } else {
            Prev->next = P->next;
        }
        delete P;
        cout << "Relasi dihapus." << endl;
    } else {
        cout << "Relasi tidak ditemukan." << endl;
    }
}

void deleteOwner(ListOwner &LP, ListRelation &LR, string idOwner) {
    // 1. Hapus semua relasi yang melibatkan owner ini dulu
    adrRelation R = LR.first;
    while (R != nullptr) {
        adrRelation nextR = R->next;
        if (R->ownerPtr->info.id == idOwner) {
            disconnect(LR, idOwner, R->petPtr->info.id);
        }
        R = R ->next;
    }

    // 2. Hapus Owner dari List Parent
    adrOwner P = findOwner(LP, idOwner);
    if (P != nullptr) {
        if (P == LP.first) { // Hapus awal
            LP.first = P->next;
            if (LP.first != nullptr){
                LP.first->prev = nullptr;
            } else {
                LP.last = nullptr;
            }
        } else if (P == LP.last) { // Hapus akhir
            LP.last = P->prev;
            LP.last->next = nullptr;
        } else { // Hapus tengah
            P->prev->next = P->next;
            P->next->prev = P->prev;
        }
        delete P;
        cout << "Owner berhasil dihapus." << endl;
    } else {
        cout << "Owner tidak ditemukan." << endl;
    }
}

void deletePet(ListPet &LC, ListRelation &LR, string idPet) {
    // 1. Hapus semua relasi yang melibatkan pet ini
    adrRelation R = LR.first;
    while (R != nullptr) {
        adrRelation nextR = R->next;
        if (R->petPtr->info.id == idPet) {
            disconnect(LR, R->ownerPtr->info.id, idPet);
        }
        R = R ->next;
    }

    // 2. Hapus Pet dari List Child
    adrPet P = findPet(LC, idPet);
    if (P != nullptr) {
        if (P == LC.first) {
            LC.first = P->next;
        } else {
            adrPet Q = LC.first;
            while (Q->next != P) {
                Q = Q->next;
            }
            Q->next = P->next;
        }
        delete P;
        cout << "Pet berhasil dihapus." << endl;
    } else {
        cout << "Pet tidak ditemukan." << endl;
    }
}

// ---------------- SHOW (J, K, L, M, N, O) ----------------
void printOwners(ListOwner L) {
    adrOwner P = L.first;
    cout << "=== List Owner ===" << endl;
    while (P != nullptr) {
        cout << "ID: " << P->info.id << " | Nama: " << P->info.nama << endl;
        P = P->next;
    }
    cout << endl;
}

void printPets(ListPet L) {
    adrPet P = L.first;
    cout << "=== List Hewan ===" << endl;
    while (P != nullptr) {
        cout << "ID: " << P->info.id << " | Nama: " << P->info.nama << " (" << P->info.jenis << ")" << endl;
        P = P->next;
    }
    cout << endl;
}

void printPetsByOwner(ListRelation LR, string idOwner) {
    adrRelation R = LR.first;
    bool found = false;
    cout << "Hewan milik Owner ID " << idOwner << ":" << endl;
    while (R != nullptr) {
        if (R->ownerPtr->info.id == idOwner) {
            cout << "- " << R->petPtr->info.nama << " (" << R->petPtr->info.jenis << ")" << endl;
            found = true;
        }
        R = R->next;
    }
    if (!found) cout << "(Tidak ada hewan)" << endl;
}

void printOwnersByPet(ListRelation LR, string idPet) {
    adrRelation R = LR.first;
    bool found = false;
    cout << "Pemilik dari Hewan ID " << idPet << ":" << endl;
    while (R != nullptr) {
        if (R->petPtr->info.id == idPet) {
            cout << "- " << R->ownerPtr->info.nama << endl;
            found = true;
        }
        R = R->next;
    }
    if (!found) cout << "(Tidak ada pemilik)" << endl;
}

void printAllOwnersWithPets(ListOwner LP, ListRelation LR) {
    adrOwner P = LP.first;
    while (P != nullptr) {
        cout << "Owner: " << P->info.nama << endl;
        printPetsByOwner(LR, P->info.id);
        cout << "-----------------" << endl;
        P = P->next;
    }
}

void printAllPetsWithOwners(ListPet LC, ListRelation LR) {
    adrPet P = LC.first;
    while (P != nullptr) {
        cout << "Hewan: " << P->info.nama << endl;
        printOwnersByPet(LR, P->info.id);
        cout << "-----------------" << endl;
        P = P->next;
    }
}

// ---------------- COUNT (P, Q, R, S) ----------------
int countPetsOfOwner(ListRelation LR, string idOwner) {
    int count = 0;
    adrRelation R = LR.first;
    while (R != nullptr) {
        if (R->ownerPtr->info.id == idOwner) count++;
        R = R->next;
    }
    return count;
}

int countOwnersOfPet(ListRelation LR, string idPet) {
    int count = 0;
    adrRelation R = LR.first;
    while (R != nullptr) {
        if (R->petPtr->info.id == idPet) count++;
        R = R->next;
    }
    return count;
}

int countOrphanPets(ListPet LC, ListRelation LR) {
    int count = 0;
    adrPet P = LC.first;
    while (P != nullptr) {
        if (countOwnersOfPet(LR, P->info.id) == 0) {
            count++;
        }
        P = P->next;
    }
    return count;
}

int countChildlessOwners(ListOwner LP, ListRelation LR) {
    int count = 0;
    adrOwner P = LP.first;
    while (P != nullptr) {
        if (countPetsOfOwner(LR, P->info.id) == 0) {
            count++;
        }
        P = P->next;
    }
    return count;
}

// ---------------- EDIT (T) ----------------
void editRelation(ListRelation &LR, ListOwner LP, ListPet LC, string oldOwnerID, string oldPetID, string newOwnerID, string newPetID) {
    // Cari relasi lama
    adrRelation R = findRelation(LR, oldOwnerID, oldPetID);
    if (R == nullptr) {
        cout << "Relasi lama tidak ditemukan!" << endl;
        return;
    }

    // Cari Owner dan Pet baru
    adrOwner newOwner = findOwner(LP, newOwnerID);
    adrPet newPet = findPet(LC, newPetID);

    if (newOwner != nullptr && newPet != nullptr) {
        // Cek apakah relasi baru sudah ada
        if (findRelation(LR, newOwnerID, newPetID) == nullptr) {
            R->ownerPtr = newOwner;
            R->petPtr = newPet;
            cout << "Relasi berhasil diubah." << endl;
        } else {
            cout << "Relasi tujuan sudah ada, edit dibatalkan." << endl;
        }
    } else {
        cout << "Data Owner baru atau Pet baru tidak valid." << endl;
    }
}

// ---------------- UPDATE DATA (U, V) ----------------
void updateOwner(ListOwner &L, string id, string newNama) {
    adrOwner P = findOwner(L, id);
    if (P != nullptr) {
        P->info.nama = newNama;
        cout << "Data Owner berhasil diupdate." << endl;
    } else {
        cout << "Owner tidak ditemukan." << endl;
    }
}

void updatePet(ListPet &L, string id, string newNama, string newJenis) {
    adrPet P = findPet(L, id);
    if (P != nullptr) {
        P->info.nama = newNama;
        P->info.jenis = newJenis;
        cout << "Data Pet berhasil diupdate." << endl;
    } else {
        cout << "Pet tidak ditemukan." << endl;
    }
}

// ---------------- SORTING (W) ----------------
void sortOwnersByNama(ListOwner &L) {
    // Bubble Sort pada Double Linked List (Swap Info)
    if (L.first == nullptr || L.first->next == nullptr) {
            return; // 0 or 1 element
    }

    bool swapped;
    adrOwner P;
    adrOwner LastPtr = nullptr;

    do {
        swapped = false;
        P = L.first;

        while (P->next != LastPtr) {
            if (P->info.nama > P->next->info.nama) {
                // Swap Data
                Owner temp = P->info;
                P->info = P->next->info;
                P->next->info = temp;
                swapped = true;
            }
            P = P->next;
        }
        LastPtr = P;
    } while (swapped);
    cout << "List Owner berhasil diurutkan berdasarkan Nama (A-Z)." << endl;
}
