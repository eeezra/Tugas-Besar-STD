#include <iostream>
#include <conio.h>
#include "teksEditor.h"

using namespace std;

int main() {
    /* List teks;
    Stack undoStack, redoStack;
    createList(teks);
    createStack(undoStack);
    createStack(redoStack);

    cout << "Selamat datang di Notepad\n";
    cout << "1. Jika ingin menghapus, klik Backspace.\n";
    cout << "2. Jika ingin Undo, klik CTRL+Z.\n";
    cout << "3. Jika ingin Redo, klik CTRL+Y.\n";
    cout << "4. Tekan ESC untuk keluar.\n\n";

    char input;
    while (true) {
        input = _getch(); // Tangkap input karakter tanpa perlu menekan Enter

        if (input == 27) { // ESC untuk keluar
            break;
        } else if (input == 8) { // Backspace
            adr deletedChar = nullptr;
            deletechar(teks, teks.cursor, deletedChar);
            if (deletedChar != nullptr) {
                infotypeStack action = {"delete", deletedChar, teks.cursor, ""};
                push(undoStack, action);

                // Hapus redoStack setiap kali ada perubahan
                redoStack.top = 0;
            }
        } else if (input == 26) { // CTRL+Z (Undo)
            undo(undoStack, redoStack, teks, teks.cursor);
        } else if (input == 25) { // CTRL+Y (Redo)
            redo(undoStack, redoStack, teks, teks.cursor);
        } else if (input >= 32 && input <= 126) { // Input karakter (spasi hingga karakter ASCII ~)
            adr newChar = createNewElemen(input);
            tambahTeks(teks, teks.cursor, newChar);

            // Push operasi ke undoStack
            infotypeStack action;
            action.action = "insert";
            action.target = newChar;
            action.cursorBefore = teks.cursor;
            push(undoStack, action);

            // Hapus redoStack setiap kali ada perubahan
            redoStack.top = 0;
        }

        // Menampilkan teks setelah setiap operasi
        system("cls"); // Membersihkan layar (opsional, tergantung terminal yang digunakan)
        cout << "Selamat datang di Notepad\n";
        cout << "1. Jika ingin menghapus, klik Backspace.\n";
        cout << "2. Jika ingin Undo, klik CTRL+Z.\n";
        cout << "3. Jika ingin Redo, klik CTRL+Y.\n";
        cout << "4. Tekan ESC untuk keluar.\n\n";
        showTeks(teks);
    }

    cout << "\nTerima kasih telah menggunakan Notepad sederhana ini!" << endl; */

    // --------------
    List teks;
    Stack undoStack, redoStack;
    createList(teks);
    createStack(undoStack);
    createStack(redoStack);

    cout << "Selamat datang di Notepad Sederhana\n";
    cout << "1. Input karakter untuk menambah teks.\n";
    cout << "2. Gunakan Panah Kiri (<-) dan Panah Kanan (->) untuk memindahkan cursor.\n";
    cout << "3. Tekan Backspace untuk menghapus karakter.\n";
    cout << "4. Tekan CTRL+Z untuk Undo dan CTRL+Y untuk Redo.\n";
    cout << "5. Tekan ESC untuk keluar.\n\n";

    char input;
    while (true) {
        input = _getch(); // Tangkap input pertama

        if (input == 27) { // ESC untuk keluar
            break;
        } else if (input == -32) { // Tombol Arrow Key ditekan
            input = _getch(); // Tangkap input kedua
            if (input == 75) { // Panah Kiri (←)
                if (teks.cursor != nullptr && teks.cursor->prev != nullptr) {
                    teks.cursor = teks.cursor->prev; // Geser kursor ke kiri
                }
            } else if (input == 77) { // Panah Kanan (→)
                if (teks.cursor != nullptr && teks.cursor->next != nullptr) {
                    teks.cursor = teks.cursor->next; // Geser kursor ke kanan
                }
            }
        } else if (input == 8) { // Backspace
            if (teks.cursor != nullptr) {
                adr deletedChar = nullptr;
                deletechar(teks, teks.cursor, deletedChar);

                // Simpan aksi ke undoStack
                infotypeStack action = {"delete", deletedChar, teks.cursor, ""};
                push(undoStack, action);
                redoStack.top = 0; // Reset redoStack
            }
        } else if (input == 26) { // CTRL+Z (Undo)
            undo(undoStack, redoStack, teks, teks.cursor);
        } else if (input == 25) { // CTRL+Y (Redo)
            redo(undoStack, redoStack, teks, teks.cursor);
        } else if (input >= 32 && input <= 126) { // Input karakter ASCII
            adr newChar = createNewElemen(input);

            // Tambahkan karakter di posisi kursor
            if (teks.cursor == nullptr) { // Jika list kosong
                insertFirst(teks, newChar);
            } else if (teks.cursor == teks.last) { // Jika kursor di akhir
                insertLast(teks, newChar);
            } else if (teks.cursor == teks.first){ // Kursor di depan
                insertFirst(teks, newChar);
            } else { // Jika kursor di tengah
                insertAfter(teks, teks.cursor, newChar);
            }
            teks.cursor = newChar; // Pindahkan cursor ke elemen baru

            // Simpan aksi ke undoStack
            infotypeStack action = {"insert", newChar, teks.cursor, ""};
            push(undoStack, action);
            redoStack.top = 0; // Reset redoStack
        }

        // Tampilkan teks dan posisi cursor
        system("cls");
        cout << "-> Notepad Setengah Mateng <-" << endl;
        cout << "-----------------------------" << endl;
        showTeks(teks);

        // Tampilkan posisi cursor
        cout << "\nPosisi cursor saat ini: ";
        if (teks.cursor != nullptr) {
            cout << "[" << teks.cursor->info << "]" << endl;
        } else {
            cout << "null" << endl;
        }
    }

    cout << "\nTerima kasih telah menggunakan Notepad Sederhana. Have a wonderful day!" << endl;
    return 0;
}
