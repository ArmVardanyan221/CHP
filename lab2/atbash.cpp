#include <iostream>
#include <string>
using namespace std;
class Cipher {
public:
    void toLowerCase(string &str) {
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
        }
    }

    void toUpperCase(string &str) {
        for (char &c : str) {
            if (c >= 'a' && c <= 'z') {
                c -= 32;
            }
        }
    }

    void atbashEncrypt(string &str) {
        int mask = (str[0] <= 'Z') ? ('A' + 'Z') : ('a' + 'z');
        for (char &c : str) {
            if (isalpha(c)) {
                c = mask - c;
            }
        }
    }

    void atbashDecrypt(string &str) {
        atbashEncrypt(str);
    }

    void caesarEncrypt(string &str, int key) {
        key %= 26;
        for (char &c : str) {
            if (c == ' ') continue;
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + key) % 26 + base;
            }
        }
    }

    void caesarDecrypt(string &str, int key) {
        key %= 26;
        for (char &c : str) {
            if (c == ' ') continue;
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base - key + 26) % 26 + base;
            }
        }
    }
};

int main() {
    Cipher cipher;
    string inputString;
    int alg, type, alpha, key = 4;

    cout << "Which algorithm do you want to use: \n1. Atbash\n2. Caesar\n";
    cin >> alg;
    cout << "Do you want to \n1. Encrypt \nor\n2. Decrypt\n";
    cin >> type;
    cout << "Do you want an Upper case or Lower case?\nPress 1 for Upper case:\nPress 2 for Lower case: ";
    cin >> alpha;
    cin.ignore();
    cout << "Print your sentence: ";
    getline(cin, inputString);

    if (alpha == 1) {
        cipher.toUpperCase(inputString);
    } else if (alpha == 2) {
        cipher.toLowerCase(inputString);
    }

    string originalString = inputString;

    if (alg == 2) {
        cout << "Print key: ";
        cin >> key;
        if (type == 1) {
            cipher.caesarEncrypt(inputString, key);
            cout << "Caesar Encrypting: " << inputString << endl;
        } else if (type == 2) {
            cipher.caesarDecrypt(inputString, key);
            cout << "Caesar Decrypting: " << inputString << endl;
        }
    } else if (alg == 1) {
        if (type == 1) {
            cipher.atbashEncrypt(inputString);
            cout << "Atbash Encrypting: " << inputString << endl;
        } else if (type == 2) {
            cipher.atbashDecrypt(inputString);
            cout << "Atbash Decrypting: " << inputString << endl;
        }
    }

    // cipher.atbashDecrypt(inputString);
    cout << "After Atbash Decrypting: " << inputString << endl;
    if (originalString == inputString) {
        cout << "Same word" << endl;
    } else {
        cout << "Not same word" << endl;
    }

    return 0;
}
