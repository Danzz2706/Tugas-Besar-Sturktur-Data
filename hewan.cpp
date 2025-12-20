#include "hewan.h"

/* =====================================================
   ================ CREATE LIST =========================
   ===================================================== */

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

/* =====================================================
   ================ ALOKASI =============================
   ===================================================== */

adrOwner alokasiOwner(string id, string nama) {
    adrOwner O = new elmOwner;
    O->info.id = id;
    O->info.nama = nama;
    O->next = nullptr;
    O->prev = nullptr;
    return O;
}

adrPet alokasiPet(string id, string nama, string jenis) {
    adrPet P = new elmPet;
    P->info.id = id;
    P->info.nama = nama;
    P->info.jenis = jenis;
    P->next = nullptr;
    return P;
}

adrRelation alokasiRelation(adrOwner O, adrPet P) {
    adrRelation R = new elmRelation;
    R->ownerPtr = O;
    R->petPtr = P;
    R->next = nullptr;
    return R;
}

/* =====================================================
   ================ INSERT ==============================
   ===================================================== */

void insertOwner(ListOwner &L, adrOwner O) {
    if (L.first == nullptr) {
        L.first = O;
        L.last = O;
    } else {
        L.last->next = O;
        O->prev = L.last;
        L.last = O;
    }
}

void insertPet(ListPet &L, adrPet P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        adrPet Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void connect(ListRelation &LR, ListOwner LO, ListPet LP, string idOwner, string idPet) {
    adrOwner O = findOwner(LO, idOwner);
    adrPet P = findPet(LP, idPet);

    if (O && P) {
        if (findRelation(LR, idOwner, idPet) == nullptr) {
            adrRelation R = alokasiRelation(O, P);
            R->next = LR.first;
            LR.first = R;
            cout << "Relasi berhasil ditambahkan.\n";
        } else {
            cout << "Relasi sudah ada.\n";
        }
    } else {
        cout << "Owner atau Pet tidak ditemukan.\n";
    }
}

/* =====================================================
   ================ SEARCH ==============================
   ===================================================== */

adrOwner findOwner(ListOwner L, string id) {
    adrOwner P = L.first;
    while (P) {
        if (P->info.id == id) return P;
        P = P->next;
    }
    return nullptr;
}

adrPet findPet(ListPet L, string id) {
    adrPet P = L.first;
    while (P) {
        if (P->info.id == id) return P;
        P = P->next;
    }
    return nullptr;
}

adrRelation findRelation(ListRelation L, string idOwner, string idPet) {
    adrRelation R = L.first;
    while (R) {
        if (R->ownerPtr->info.id == idOwner &&
            R->petPtr->info.id == idPet)
            return R;
        R = R->next;
    }
    return nullptr;
}

/* =====================================================
   ================ DELETE ==============================
   ===================================================== */

void disconnect(ListRelation &LR, string idOwner, string idPet) {
    adrRelation P = LR.first, prev = nullptr;

    while (P) {
        if (P->ownerPtr->info.id == idOwner &&
            P->petPtr->info.id == idPet) {

            if (prev == nullptr)
                LR.first = P->next;
            else
                prev->next = P->next;

            delete P;
            cout << "Relasi berhasil dihapus.\n";
            return;
        }
        prev = P;
        P = P->next;
    }
    cout << "Relasi tidak ditemukan.\n";
}

void deleteOwner(ListOwner &LO, ListRelation &LR, string idOwner) {
    // hapus relasi
    adrRelation R = LR.first;
    while (R) {
        adrRelation nextR = R->next;
        if (R->ownerPtr->info.id == idOwner)
            disconnect(LR, idOwner, R->petPtr->info.id);
        R = nextR;
    }

    adrOwner O = findOwner(LO, idOwner);
    if (!O) {
        cout << "Owner tidak ditemukan.\n";
        return;
    }

    if (O == LO.first) {
        LO.first = O->next;
        if (LO.first) LO.first->prev = nullptr;
        else LO.last = nullptr;
    } else if (O == LO.last) {
        LO.last = O->prev;
        LO.last->next = nullptr;
    } else {
        O->prev->next = O->next;
        O->next->prev = O->prev;
    }

    delete O;
    cout << "Owner berhasil dihapus.\n";
}

void deletePet(ListPet &LP, ListRelation &LR, string idPet) {
    adrRelation R = LR.first;
    while (R) {
        adrRelation nextR = R->next;
        if (R->petPtr->info.id == idPet)
            disconnect(LR, R->ownerPtr->info.id, idPet);
        R = nextR;
    }

    adrPet P = findPet(LP, idPet);
    if (!P) {
        cout << "Pet tidak ditemukan.\n";
        return;
    }

    if (P == LP.first) {
        LP.first = P->next;
    } else {
        adrPet Q = LP.first;
        while (Q->next != P) Q = Q->next;
        Q->next = P->next;
    }

    delete P;
    cout << "Pet berhasil dihapus.\n";
}

/* =====================================================
   ================ DISPLAY (LOGIC) =====================
   ===================================================== */

void printOwners(ListOwner L) {
    adrOwner P = L.first;
    while (P) {
        cout << P->info.id << " - " << P->info.nama << endl;
        P = P->next;
    }
}

void printPets(ListPet L) {
    adrPet P = L.first;
    while (P) {
        cout << P->info.id << " - " << P->info.nama
             << " (" << P->info.jenis << ")\n";
        P = P->next;
    }
}

/* =====================================================
   ================ DISPLAY (UI TABLE) ==================
   ===================================================== */

void printOwnersTable(ListOwner LO) {
    cout << left << setw(10) << "ID" << setw(20) << "NAMA OWNER" << endl;
    cout << string(30, '-') << endl;

    adrOwner P = LO.first;
    while (P) {
        cout << left << setw(10) << P->info.id
             << setw(20) << P->info.nama << endl;
        P = P->next;
    }
}

void printPetsTable(ListPet LP) {
    cout << left << setw(10) << "ID"
         << setw(15) << "NAMA"
         << setw(15) << "JENIS" << endl;
    cout << string(40, '-') << endl;

    adrPet P = LP.first;
    while (P) {
        cout << left << setw(10) << P->info.id
             << setw(15) << P->info.nama
             << setw(15) << P->info.jenis << endl;
        P = P->next;
    }
}

void printOwnersWithPetsTable(ListOwner LO, ListRelation LR) {
    adrOwner O = LO.first;
    while (O) {
        cout << "\nOwner: " << O->info.nama << " (" << O->info.id << ")\n";
        cout << left << setw(10) << "PET ID"
             << setw(15) << "NAMA"
             << setw(15) << "JENIS" << endl;
        cout << string(40, '-') << endl;

        bool ada = false;
        adrRelation R = LR.first;
        while (R) {
            if (R->ownerPtr == O) {
                adrPet P = R->petPtr;
                cout << left << setw(10) << P->info.id
                     << setw(15) << P->info.nama
                     << setw(15) << P->info.jenis << endl;
                ada = true;
            }
            R = R->next;
        }
        if (!ada) cout << "(Tidak punya hewan)\n";
        O = O->next;
    }
}

void printPetsWithOwnersTable(ListPet LP, ListRelation LR) {
    adrPet P = LP.first;
    while (P) {
        cout << "\nPet: " << P->info.nama
             << " (" << P->info.jenis << ")\n";
        cout << left << setw(10) << "OWNER ID"
             << setw(20) << "NAMA OWNER" << endl;
        cout << string(30, '-') << endl;

        bool ada = false;
        adrRelation R = LR.first;
        while (R) {
            if (R->petPtr == P) {
                adrOwner O = R->ownerPtr;
                cout << left << setw(10) << O->info.id
                     << setw(20) << O->info.nama << endl;
                ada = true;
            }
            R = R->next;
        }
        if (!ada) cout << "(Tidak punya pemilik)\n";
        P = P->next;
    }
}

/* =====================================================
   ================ COUNT / UPDATE / SORT ===============
   ===================================================== */

int countPetsOfOwner(ListRelation LR, string idOwner) {
    int count = 0;
    adrRelation R = LR.first;
    while (R) {
        if (R->ownerPtr->info.id == idOwner) count++;
        R = R->next;
    }
    return count;
}

int countOwnersOfPet(ListRelation LR, string idPet) {
    int count = 0;
    adrRelation R = LR.first;
    while (R) {
        if (R->petPtr->info.id == idPet) count++;
        R = R->next;
    }
    return count;
}

int countOrphanPets(ListPet LP, ListRelation LR) {
    int count = 0;
    adrPet P = LP.first;
    while (P) {
        if (countOwnersOfPet(LR, P->info.id) == 0)
            count++;
        P = P->next;
    }
    return count;
}

int countChildlessOwners(ListOwner LO, ListRelation LR) {
    int count = 0;
    adrOwner O = LO.first;
    while (O) {
        if (countPetsOfOwner(LR, O->info.id) == 0)
            count++;
        O = O->next;
    }
    return count;
}

void updateOwner(ListOwner &L, string id, string newNama) {
    adrOwner O = findOwner(L, id);
    if (O) O->info.nama = newNama;
}

void updatePet(ListPet &L, string id, string newNama, string newJenis) {
    adrPet P = findPet(L, id);
    if (P) {
        P->info.nama = newNama;
        P->info.jenis = newJenis;
    }
}

void sortOwnersByNama(ListOwner &L) {
    if (!L.first) return;
    bool swapped;
    do {
        swapped = false;
        adrOwner P = L.first;
        while (P->next) {
            if (P->info.nama > P->next->info.nama) {
                swap(P->info, P->next->info);
                swapped = true;
            }
            P = P->next;
        }
    } while (swapped);
}

void printPetsByOwner(ListRelation LR, string idOwner) {
    adrRelation R = LR.first;
    bool ada = false;

    cout << "Hewan milik Owner ID " << idOwner << ":\n";
    while (R != nullptr) {
        if (R->ownerPtr->info.id == idOwner) {
            cout << "- "
                 << R->petPtr->info.nama
                 << " (" << R->petPtr->info.jenis << ")\n";
            ada = true;
        }
        R = R->next;
    }

    if (!ada) {
        cout << "(Tidak ada hewan)\n";
    }
}

void printOwnersByPet(ListRelation LR, string idPet) {
    adrRelation R = LR.first;
    bool ada = false;

    cout << "Pemilik dari Hewan ID " << idPet << ":\n";
    while (R != nullptr) {
        if (R->petPtr->info.id == idPet) {
            cout << "- " << R->ownerPtr->info.nama << endl;
            ada = true;
        }
        R = R->next;
    }

    if (!ada) {
        cout << "(Tidak ada pemilik)\n";
    }
}

void editRelation(
    ListRelation &LR,
    ListOwner LO,
    ListPet LP,
    string oldOwnerID,
    string oldPetID,
    string newOwnerID,
    string newPetID
) {
    adrRelation R = findRelation(LR, oldOwnerID, oldPetID);
    if (R == nullptr) {
        cout << "Relasi lama tidak ditemukan.\n";
        return;
    }

    adrOwner newOwner = findOwner(LO, newOwnerID);
    adrPet newPet = findPet(LP, newPetID);

    if (newOwner == nullptr || newPet == nullptr) {
        cout << "Owner atau Pet baru tidak valid.\n";
        return;
    }

    if (findRelation(LR, newOwnerID, newPetID) != nullptr) {
        cout << "Relasi baru sudah ada. Edit dibatalkan.\n";
        return;
    }

    R->ownerPtr = newOwner;
    R->petPtr = newPet;
    cout << "Relasi berhasil diubah.\n";
}

