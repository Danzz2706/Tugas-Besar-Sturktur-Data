# Tugas Besar Struktur Data - Hewan & Pemilik System

Program ini adalah aplikasi konsol C++ untuk mengelola data Pemilik (Owner) dan Hewan Peliharaan (Pet) serta relasi kepemilikan di antara keduanya.

## 👥 Dibuat Oleh
- **Muhammad Cheng Ho**
- **Zaidan Kamil**

## 📚 Deskripsi
Aplikasi ini menggunakan struktur data Linked List untuk menyimpan data:
- **List Owner**: Double Linked List
- **List Pet**: Single Linked List
- **List Relation**: Single Linked List (menghubungkan Owner dan Pet)

## 🚀 Fitur
Program memiliki berbagai fitur CRUD dan operasi data lainnya:

### 1. Input Data
- **Insert Owner**: Menambahkan data pemilik baru.
- **Insert Pet**: Menambahkan data hewan peliharaan baru.
- **Connect**: Menghubungkan Owner dengan Pet (membuat relasi).

### 2. Show & Search (Menampilkan & Mencari)
- **Show All Owners**: Menampilkan tabel semua pemilik.
- **Show All Pets**: Menampilkan tabel semua hewan.
- **Show Owners + Hewan**: Menampilkan daftar Owner beserta hewan yang dimilikinya.
- **Show Pets + Owner**: Menampilkan daftar Pet beserta pemiliknya.
- **Find Hewan by Owner**: Mencari hewan spesifik milik owner tertentu berdasarkan ID.
- **Find Owner by Hewan**: Mencari pemilik dari hewan tertentu berdasarkan ID.

### 3. Delete (Menghapus)
- **Delete Relation**: Menghapus hubungan kepemilikan saja (data Owner dan Pet tetap ada).
- **Delete Owner (Cascade)**: Menghapus data Owner, otomatis menghapus relasi terkait.
- **Delete Pet (Cascade)**: Menghapus data Pet, otomatis menghapus relasi terkait.

### 4. Edit & Tools
- **Statistik**: Melihat jumlah hewan tak bertuan dan Owner tanpa hewan.
- **Edit Relation**: Mengubah data relasi (misal: memindahkan hewan ke owner lain).
- **Edit Owner**: Mengubah nama Owner.
- **Edit Pet**: Mengubah nama atau jenis Pet.
- **Sort Owner**: Mengurutkan daftar Owner berdasarkan nama (A-Z) menggunakan manipulasi pointer.

## 🛠️ Cara Menjalankan
Pastikan Anda memiliki compiler C++ (seperti G++).

1. Compile semua file `.cpp` dan `.h`:
   ```bash
   g++ main.cpp hewan.cpp -o tubes_std
   ```
2. Jalankan program:
   - Windows:
     ```bash
     .\tubes_std.exe
     ```
   - Linux/Mac:
     ```bash
     ./tubes_std
     ```

## 📂 Struktur Data (Source Code)
Berikut adalah representasi struktur data yang digunakan dalam `hewan.h` dan `hewan.cpp`:

### 1. Element Owner (`elmOwner`)
Node untuk Double Linked List Owner.
- `info`: Struct `Owner` (menyimpan `id`, `nama`).
- `next`: Pointer ke elemen owner selanjutnya.
- `prev`: Pointer ke elemen owner sebelumnya.

### 2. Element Pet (`elmPet`)
Node untuk Single Linked List Pet.
- `info`: Struct `Pet` (menyimpan `id`, `nama`, `jenis`).
- `next`: Pointer ke elemen pet selanjutnya.

### 3. Element Relation (`elmRelation`)
Node untuk menghubungkan Owner dan Pet (Single Linked List).
- `ownerPtr`: Pointer yang menunjuk ke address Owner di List Owner.
- `petPtr`: Pointer yang menunjuk ke address Pet di List Pet.
- `next`: Pointer ke elemen relasi selanjutnya.

## ⚙️ Metode & Implementasi
Setiap fitur diimplementasikan dengan algoritma spesifik sebagai berikut:

### 1. Insert Data
- **Insert Owner**: Menggunakan metode **Insert Last**.
  - Data baru selalu ditambahkan di akhir list owner.
  - *Logic*: `L.last->next = O; O->prev = L.last; L.last = O;`
- **Insert Pet**: Menggunakan metode **Insert Last**.
  - Data baru loop sampai elemen terakhir, lalu disambung.
- **Connect (Relasi)**:
  - Menggunakan metode **Insert First** pada List Relation.
  - Relasi baru ditambahkan di awal list agar operasi lebih cepat (O(1)).

### 2. Search Data
- **Find Owner / Pet**: Menggunakan **Sequential Search (Linear Search)**.
  - Menelusuri list dari `first` sampai `last` untuk mencocokkan ID.

### 3. Delete Data
- **Delete Relation**:
  - Mencari relasi berdasarkan ID Owner dan ID Pet, lalu menghapus node tersebut dari List Relation.
- **Delete Owner (Cascade)**:
  - Langkah 1: Mencari semua relasi yang terhubung dengan Owner tersebut, lalu menghapusnya (**Disconnect**).
  - Langkah 2: Menghapus node Owner dari List Owner (memutus pointer `prev` dan `next`).
- **Delete Pet (Cascade)**:
  - Serupa dengan Owner, relasi dihapus terlebih dahulu sebelum menghapus data Pet.

### 4. Edit & Sorting
- **Edit**: Mencari elemen menggunakan fungsi *Find*, lalu mengubah nilai `info`-nya secara langsung melalui pointer.
- **Sort Owner**:
  - Menggunakan algoritma **Bubble Sort**.
  - Yang ditukar bukan hanya datanya, tetapi **pointer node-nya** (`next` dan `prev` di-swap secara fisik dalam memori).

## 📝 Catatan
Program ini dibuat untuk memenuhi Tugas Besar mata kuliah Struktur Data Semester 3.
