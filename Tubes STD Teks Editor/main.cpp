#include <iostream>
#include <conio.h>
#include "teksEditor.h"

using namespace std;

int main() {
    List teks;
    Stack undoStack, redoStack;
    createList(teks);
    createStack(undoStack);
    createStack(redoStack);

    cout << " ------------------> Notepad Setengah mateng <-------------------" << endl;
    cout << "| 1. Input karakter untuk menambah teks.                         |" << endl;
    cout << "| 2. Gunakan Panah Kiri dan Panah Kanan untuk memindahkan cursor.|" << endl;
    cout << "| 3. Tekan Backspace untuk menghapus karakter.                   |" << endl;
    cout << "| 4. Tekan CTRL+Z untuk Undo dan CTRL+Y untuk Redo.              |" << endl;
    cout << "| 5. Tekan ESC untuk keluar.                                     |" << endl;
    cout << " ----------------------------------------------------------------" << endl;

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
        cout << " ------------------> Notepad Setengah mateng <-------------------" << endl;
        cout << "| 1. Input karakter untuk menambah teks.                         |" << endl;
        cout << "| 2. Gunakan Panah Kiri dan Panah Kanan untuk memindahkan cursor.|" << endl;
        cout << "| 3. Tekan Backspace untuk menghapus karakter.                   |" << endl;
        cout << "| 4. Tekan CTRL+Z untuk Undo dan CTRL+Y untuk Redo.              |" << endl;
        cout << "| 5. Tekan ESC untuk keluar.                                     |" << endl;
        cout << " ----------------------------------------------------------------" << endl;
        showTeks(teks);

        // Tampilkan posisi cursor
        cout << "\nPosisi cursor saat ini: ";
        if (teks.cursor != nullptr) {
            cout << "[" << teks.cursor->info << "]" << endl;
        } else {
            cout << "null" << endl;
        }
    }

    cout << "\nTerima kasih telah menggunakan Notepad Setengah Mateng. Have a wonderful day!" << endl;
    return 0;
}
