#include <iostream>
#include "teksEditor.h"

using namespace std;


void createList(List &L){
    L.first = nullptr;
    L.last = nullptr;
    L.cursor = nullptr;
}

adr createNewElemen(infotype data){
    adr ptr = new elmList;

    ptr->info = data;
    ptr->prev = nullptr;
    ptr->next = nullptr;
    return ptr;
}

bool isEmpty(List L){
    return L.first == nullptr && L.last == nullptr;
}

void insertFirst(List &L, adr ptr){
    if (isEmpty(L)) {
        L.first = ptr;
        L.last = ptr;
        L.cursor = ptr;
    } else {
        ptr->next = L.first;
        (L.first)->prev = ptr;
        L.first = ptr;
        L.cursor = ptr;
    }
}

void insertLast(List &L, adr ptr){
    if (isEmpty(L)) {
        L.first = ptr;
        L.last = ptr;
        L.cursor = ptr;
    } else {
        ptr->prev = L.last;
        (L.last)->next = ptr;
        L.last = ptr;
        L.cursor = ptr;
    }
}

void insertAfter(List &L, adr pred, adr ptr){
    ptr->next = pred->next;
    ptr->prev = pred;
    if (pred->next != nullptr) {
        pred->next->prev = ptr;
    } else {
        L.last = ptr;
    }
    pred->next = ptr;
    L.cursor = ptr;
}

void deleteFirst(List &L, adr &ptr){
    ptr = L.first;
    if (L.cursor == L.first) {
        L.cursor = L.cursor->next;
    }

    if (L.first == L.last){
        L.first = nullptr;
        L.last = nullptr;
    } else {
        L.first = ptr->next;
        ptr->next = nullptr;
        (L.first)->prev = nullptr;
    }
}

void deleteLast(List &L, adr &ptr){
    ptr = L.last;
    if (L.cursor == L.first) {
        L.cursor = L.cursor->prev;
    }

    if (L.first == L.last){
        L.first = nullptr;
        L.last = nullptr;
    } else {
        L.last = (L.last)->prev;
        ptr->prev = nullptr;
        (L.last)->next = nullptr;
    }
}

void deleteAfter(List &L, adr pred, adr &ptr) {
    if (pred != nullptr && pred->next != nullptr) {
        ptr = pred->next;
        if (L.cursor == ptr) {
            L.cursor = L.cursor->prev->prev;
        }
        pred->next = ptr->next;

        if (ptr->next != nullptr) {
            ptr->next->prev = pred;
        }
        ptr->prev = nullptr;
        ptr->next = nullptr;
    }
}

Stack createStack(Stack &S) {
    S.top = 0;
    return S;
}

bool isEmptyStack(Stack S) {
    return S.top == 0;
}

bool isFullStack(Stack S) {
    return S.top == MAX;
}

void push(Stack &S, infotypeStack data) {
    if (!isFullStack(S)) {
        S.top++;
        S.info[S.top] = data;
    }
}

void pop(Stack &S, infotypeStack &data) {
    if (!isEmptyStack(S)) {
        data = S.info[S.top];
        S.top--;
    }
}

void tambahTeks(List &L, adr &cursor, adr ptr) {
    /* I.S. terdefinisi sebuah list L yang mungkin kosong, sebuah pointer cursor yang menunjuk ke salah satu elemen dalam L, dan pointer ptr yang menunjuk ke elemen berisi teks yang ingin dimasukkan ke dalam list.
    F.S. karakter yang ditunjuk ptr menjadi etemen list L yang berada di posisi setetoh cursor dan posisi cursor beruban menunjuk ke elemen tersebut. */

    cursor = L.cursor;
    if (isEmpty(L)) {
        insertFirst(L, ptr);
    } else {
        if (cursor == L.first){
            insertFirst(L, ptr);
        } else if (cursor == L.last) {
            insertLast(L, ptr);
        } else {
            insertAfter(L, cursor, ptr);
        }
    }
    cursor = ptr; // Perbarui posisi kursor
    L.cursor = cursor;
}

void deletechar(List &L, adr &cursor, adr &ptr) {
    /* I.S. terdefinisi sebuah list L yang mungkin kosong, sebuah pointer cursor yang menunjuk ke salah satu elemen L, dan sebuah pointer ptr.
    F.S. elemen yang ditunjuk cursor keluar dari list dia dan ditunjuk oleh ptr. Posisi cursor berubah menunjuk ke elemen sesudahnya atau Null. Posisi cursor bernilai Null. apabila menghapus (1) elemen satu-satunya dalam list, atau (2) elemen terakhir dalam list. */

    if (cursor != nullptr) {
        ptr = cursor;
        if (cursor == L.first) {
            deleteFirst(L, ptr);
            L.cursor = L.first;
        } else if (cursor == L.last) {
            deleteLast(L, ptr);
            L.cursor = L.last;
        } else {
            deleteAfter(L, cursor->prev, ptr);
            L.cursor = cursor->next;
        }
    } else {
        L.cursor = nullptr; // Jika elemen kosong
    }
 }

void showTeks(List L) {
    if (isEmpty(L)) {
        cout << "Notepad kosong. Mulai menulis..." << endl;
    } else {
        adr current = L.first;
        while (current != nullptr) {
            cout << current->info;
            current = current->next;
        }
        cout << endl;
    }
}

void undo(Stack &history, Stack &redoStack, List &L, adr &cursor) {
    if (!isEmptyStack(history)) {
        infotypeStack action;
        pop(history, action);
        push(redoStack, action);

        if (action.action == "insert") {
            adr deletedNode = action.target;
            deletechar(L, deletedNode, cursor);
        } else if (action.action == "delete") {
            tambahTeks(L, cursor, action.target);
        }

        L.cursor = cursor; // Perbarui posisi kursor
    }
}


void redo(Stack &history, Stack &redoStack, List &L, adr &cursor) {
    if (!isEmptyStack(redoStack)) {
        infotypeStack action;
        pop(redoStack, action);
        push(history, action);

        if (action.action == "insert") {
            tambahTeks(L, cursor, action.target);
        } else if (action.action == "delete") {
            adr deletedNode = action.target;
            deletechar(L, cursor, deletedNode);
        }

        L.cursor = cursor; // Perbarui posisi kursor
    }
}
