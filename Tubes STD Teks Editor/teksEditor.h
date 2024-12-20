#ifndef TEKSEDITOR_H_INCLUDED
#define TEKSEDITOR_H_INCLUDED
#define MAX 1000
#include <iostream>

using namespace std;

typedef char infotype;
typedef struct elmList *adr;

struct elmList {
    infotype info;
    adr prev;
    adr next;
};

struct List {
    adr first;
    adr last;
    adr cursor;
};

struct infotypeStack {
    string action;         // Jenis operasi: "insert" atau "delete"
    adr target;            // Pointer ke elemen yang dihapus/dimasukkan
    adr cursorBefore;      // Posisi cursor sebelum operasi
    string position;       // Posisi elemen
};

struct Stack {
    infotypeStack info[MAX];
    int top;
};

void createList(List &L);
adr createNewElemen(infotype data);
bool isEmpty(List L);
void insertFirst(List &L, adr ptr);
void insertLast(List &L, adr ptr);
void insertAfter(List &L, adr pred, adr ptr);
void deleteFirst(List &L, adr &ptr);
void deleteLast(List &L, adr &ptr);
void deleteAfter(List &L, adr pred, adr &ptr);

Stack createStack(Stack &S);
bool isEmptyStack(Stack S);
bool isFullStack(Stack S);
void push(Stack &S, infotypeStack data);
void pop(Stack &S, infotypeStack &data);

void tambahTeks(List &L, adr &cursor, adr ptr);
void tambahTeksByIndex(List &L, int posisi, adr ptr);
void deletechar(List &L, adr &cursor, adr &ptr);
void showTeks(List L);
void undo(Stack &history, Stack &redoStack, List &L, adr &cursor);
void redo(Stack &redoStack, Stack &history, List &L, adr &cursor);


#endif // TEKSEDITOR_H_INCLUDED
