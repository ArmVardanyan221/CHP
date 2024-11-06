#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Zip {
public:
    virtual string zip(const string& plainText) = 0;
    virtual string unzip(const string& zipText) = 0;

    virtual ~Zip() = 0;
};
Zip::~Zip() {}

class RLE : public Zip {
public:
    RLE() {}
    ~RLE() override {}

    string zip(const string& plainText) override {
        string zipped = "";
        int len = plainText.length();

        for (int i = 0; i < len; ++i) {
            char currentChar = plainText[i];
            int count = 1;

            while (i + 1 < len && plainText[i] == plainText[i + 1]) {
                count++;
                i++;
            }

            while (count > 255) {
                zipped += currentChar;
                zipped += (char)255;
                count -= 255;
            }

            zipped += currentChar;
            zipped += (char)count;
        }

        return zipped;
    }

    string unzip(const string& zipText) override {
        string unzipped = "";
        int len = zipText.length();

        for (int i = 0; i < len; i += 2) {
            char currentChar = zipText[i];
            int count = (unsigned char)zipText[i + 1];

            unzipped.append(count, currentChar);
        }

        return unzipped;
    }
};

class CaesarCipher {
public:
    CaesarCipher(int shift) : shift(shift) {}

    string encrypt(const string& text) {
        string encrypted = text;
        for (char& c : encrypted) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
        }
        return encrypted;
    }

    string decrypt(const string& text) {
        string decrypted = text;
        for (char& c : decrypted) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base - shift + 26) % 26 + base;
            }
        }
        return decrypted;
    }

private:
    int shift;
};

class MixCipher {
public:
    MixCipher(int caesarShift) : caesar(caesarShift), rle() {}

    string encrypt(const string& text) {
       
        string caesarEncrypted = caesar.encrypt(text);
       
        return rle.zip(caesarEncrypted);
    }

    string decrypt(const string& text) {
       
        string rleDecompressed = rle.unzip(text);

        return caesar.decrypt(rleDecompressed);
    }

private:
    CaesarCipher caesar;
    RLE rle;
};

int main() {
    string inputText;
    cout << "Enter the text to be encrypted: ";
    getline(cin, inputText);

    MixCipher mixCipher(3);


    string encryptedText = mixCipher.encrypt(inputText);
    cout << "Encrypted (MixCipher): " << encryptedText << endl;


    string decryptedText = mixCipher.decrypt(encryptedText);
    cout << "Decrypted (MixCipher): " << decryptedText << endl;

    if (decryptedText == inputText) {
        cout << "The original text and the final decrypted text match!" << endl;
    } else {
        cout << "There is a mismatch between the original and decrypted text." << endl;
    }

    return 0;
}
