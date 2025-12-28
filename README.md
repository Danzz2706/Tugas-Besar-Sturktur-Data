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

## 📝 Catatan
Program ini dibuat untuk memenuhi Tugas Besar mata kuliah Struktur Data Semester 3.
