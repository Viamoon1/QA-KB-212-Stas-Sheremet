#include <iostream>
#include <string>
#include <locale>

using namespace std;
static const int alfavitLenght(33);
static wstring alfavitUP = L"АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
static wstring alfavitLOW = L"абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
// Функція для знаходження оберненої величини (модульної оберненої)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

int charNumber(char32_t c, wstring alfavit) {
    int i = 0;
    for (char32_t c1 : alfavit) {
        if (c == c1) {
            return i;
        }
        i++;
    }
    return 0;
}

// Функція для шифрування повідомлення
wstring encrypt(wstring message, int key1, int key2) {
    wstring encryptedMessage = L"";
    for (char32_t c : message) {
        if (iswalpha(c)) {
            // Зміщення символів
            if (iswlower(c)) {
                char32_t cCrypt = alfavitLOW[(charNumber(c, alfavitLOW) * key1 + key2) % alfavitLenght];
                encryptedMessage += cCrypt;
            }
            else { 
                char32_t cCrypt = alfavitUP[(charNumber(c, alfavitUP) * key1 + key2) % alfavitLenght];
                encryptedMessage += cCrypt;
            }
        }
        else {
            encryptedMessage += c;
        }
    }
    return encryptedMessage;
}

// Функція для дешифрування повідомлення
wstring decrypt(wstring message, int key1, int key2) {
    wstring decryptedMessage = L"";
    int invKey1 = modInverse(key1, alfavitLenght);
    for (char32_t c : message) {
        if (iswalpha(c)) {
            if (iswlower(c)) {
                decryptedMessage += alfavitLOW[((charNumber(c, alfavitLOW) - key2) * invKey1) % alfavitLenght];
            }
            else {
                decryptedMessage += alfavitUP[((charNumber(c, alfavitLOW) - key2) * invKey1) % alfavitLenght];
            }  
        }
        else {
            decryptedMessage += c;
        }
    }
    return decryptedMessage;
}

int main() {
    locale::global(locale(""));

    bool endProg = false;
    while (!endProg) {
        wstring message;
        cout << "Введіть повідомлення для обробки: ";
        wcin >> message;
        cout << "Що ви хочете зробити?" << endl << endl;
        cout << "Зашифрувати повідомлення?(1)" << endl;
        cout << "Розшифрувати повідомлення?(2)" << endl;
        cout << "Завершити програму(Будь-який символ)" << endl;
        int cr;
        cin >> cr;
        cout << endl;
        if (cr == 1) {
            int key1;
            cout << "Введіть перший ключ (ціле число, взаємно просте з 33): ";
            cin >> key1;
            int key2;
            cout << "Введіть другий ключ (ціле число): ";
            cin >> key2;
            // Шифрування
            wstring encryptedMessage = encrypt(message, key1, key2);
            wcout << L"Зашифроване повідомлення: " << encryptedMessage << endl << endl;
        }
        else if (cr == 2) {
            int key1;
            cout << "Введіть перший ключ (ціле число, взаємно просте з 33): ";
            cin >> key1;
            int key2;
            cout << "Введіть другий ключ (ціле число): ";
            cin >> key2;
            // Дешифрування
            wstring decryptedMessage = decrypt(message, key1, key2);
            wcout << L"Розшифроване повідомлення: " << decryptedMessage << endl << endl;
        }
        else {
            cout << "Програму завершено" << endl;
            break;
        }
    }
    cout << "Hello GitHub";
    return 0;
}