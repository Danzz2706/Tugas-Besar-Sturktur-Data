#include <iostream>
#include "hewan.h"
using namespace std;

void showMenu() {
    cout << "\n=== APLIKASI MANAJEMEN HEWAN & PEMILIK ===" << endl;
    cout << "1. Insert Owner (Parent)" << endl;
    cout << "2. Insert Pet (Child)" << endl;
    cout << "3. Connect (Hubungkan Owner & Pet)" << endl;
    cout << "4. Show All Owners" << endl;
    cout << "5. Show All Pets" << endl;
    cout << "6. Show All Owners beserta Hewannya" << endl;
    cout << "7. Show All Pets beserta Pemiliknya" << endl;
    cout << "8. Cari Hewan milik Owner tertentu" << endl;
    cout << "9. Cari Pemilik dari Hewan tertentu" << endl;
    cout << "10. Delete Relation (Putus Hubungan)" << endl;
    cout << "11. Delete Owner (Cascade Delete)" << endl;
    cout << "12. Delete Pet (Cascade Delete)" << endl;
    cout << "13. Statistik (Count)" << endl;
    cout << "14. Edit Relation (Pindah Tangan)" << endl;
    cout << "15. Edit Data Owner" << endl;
    cout << "16. Edit Data Pet" << endl;
    cout << "17. Sort Owner by Name (Ascending)" << endl;
    cout << "0. Exit" << endl;
    cout << "Pilihan: ";
}

int main() {
    ListOwner LO;
    ListPet LP;
    ListRelation LR;

    createListOwner(LO);
    createListPet(LP);
    createListRelation(LR);

    // Data Dummy untuk tes cepat
    insertOwner(LO, alokasiOwner("O1", "Budi"));
    insertOwner(LO, alokasiOwner("O2", "Siti"));
    insertPet(LP, alokasiPet("P1", "Molly", "Kucing"));
    insertPet(LP, alokasiPet("P2", "Bruno", "Anjing"));
    insertPet(LP, alokasiPet("P3", "Tweety", "Burung"));

    // Connect
    connect(LR, LO, LP, "O1", "P1"); // Budi punya Molly
    connect(LR, LO, LP, "O1", "P2"); // Budi punya Bruno
    connect(LR, LO, LP, "O2", "P1"); // Siti juga punya Molly (Shared ownership)

    // Helper lambda for numeric validation
    auto isNumeric = [](const string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!isdigit(c)) return false;
        }
        return true;
    };

    // Helper lambda to get valid numeric ID
    auto getValidID = [&](string prompt) -> string {
        string input;
        while (true) {
            cout << prompt;
            cin >> input;
            if (isNumeric(input)) {
                return input;
            }
            cout << "Error: ID harus berupa angka! Silakan coba lagi." << endl;
        }
    };

    int choice;
    string id1, id2, id3, id4, nama, jenis;

    do {
        showMenu();
        if (!(cin >> choice)) {
            cout << "Input tidak valid! Harap masukkan angka." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1; // Set invalid choice to continue loop
        }
        cout << endl;

        if (choice == 1) {
            id1 = getValidID("Masukkan ID Owner: ");
            if (findOwner(LO, id1) != NULL) {
                cout << "Error: ID Owner sudah ada!" << endl;
            } else {
                cout << "Masukkan Nama Owner: "; cin >> nama;
                insertOwner(LO, alokasiOwner(id1, nama));
            }
        } else if (choice == 2) {
            id1 = getValidID("Masukkan ID Pet: ");
            if (findPet(LP, id1) != NULL) {
                cout << "Error: ID Pet sudah ada!" << endl;
            } else {
                cout << "Masukkan Nama Pet: "; cin >> nama;
                cout << "Masukkan Jenis Pet: "; cin >> jenis;
                insertPet(LP, alokasiPet(id1, nama, jenis));
            }
        } else if (choice == 3) {
            id1 = getValidID("ID Owner: ");
            id2 = getValidID("ID Pet: ");
            connect(LR, LO, LP, id1, id2);
        } else if (choice == 4) {
            printOwners(LO);
        } else if (choice == 5) {
            printPets(LP);
        } else if (choice == 6) {
            printAllOwnersWithPets(LO, LR);
        } else if (choice == 7) {
            printAllPetsWithOwners(LP, LR);
        } else if (choice == 8) {
            id1 = getValidID("ID Owner: ");
            printPetsByOwner(LR, id1);
        } else if (choice == 9) {
            id1 = getValidID("ID Pet: ");
            printOwnersByPet(LR, id1);
        } else if (choice == 10) {
            id1 = getValidID("ID Owner: ");
            id2 = getValidID("ID Pet: ");
            disconnect(LR, id1, id2);
        } else if (choice == 11) {
            id1 = getValidID("ID Owner yang akan dihapus: ");
            deleteOwner(LO, LR, id1);
        } else if (choice == 12) {
            id1 = getValidID("ID Pet yang akan dihapus: ");
            deletePet(LP, LR, id1);
        } else if (choice == 13) {
            cout << "--- STATISTIK ---" << endl;
            cout << "Jumlah  Hewan tak bertuan: " << countOrphanPets(LP, LR) << endl;
            cout << "Jumlah Owner tanpa hewan: " << countChildlessOwners(LO, LR) << endl;
        } else if (choice == 14) {
            cout << "--- Edit Relation ---" << endl;
            id1 = getValidID("ID Owner Lama: ");
            id2 = getValidID("ID Pet Lama: ");
            id3 = getValidID("ID Owner Baru: ");
            id4 = getValidID("ID Pet Baru: ");
            editRelation(LR, LO, LP, id1, id2, id3, id4);
        } else if (choice == 15) {
            cout << "--- Edit Owner ---" << endl;
            id1 = getValidID("ID Owner: ");
            cout << "Nama Baru: "; cin >> nama;
            updateOwner(LO, id1, nama);
        } else if (choice == 16) {
            cout << "--- Edit Pet ---" << endl;
            id1 = getValidID("ID Pet: ");
            cout << "Nama Baru: "; cin >> nama;
            cout << "Jenis Baru: "; cin >> jenis;
            updatePet(LP, id1, nama, jenis);
        } else if (choice == 17) {
            sortOwnersByNama(LO);
        } else if (choice == 0) {
            cout << "Keluar..." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 0);

    return 0;
}
