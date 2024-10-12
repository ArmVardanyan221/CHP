#include <iostream>
#include <string>
using namespace std;

class RunLengthEncoding {
public:
    string encode(const string& input) {
        string encoded = "";
        int length = input.length();
        unsigned char count = 1;

        for (int i = 1; i <= length; ++i) {
            if (i < length && input[i] == input[i - 1]) {
                count++;
            } else {
                encoded += input[i - 1];
                encoded += static_cast<char>(count);
                count = 1;
            }
        }
        return encoded;
    }

    string decode(const string& encoded) {
        string decoded = "";
        int index = 0;

        while (index < encoded.length()) {
            char currentChar = encoded[index++];
            unsigned char count = static_cast<unsigned char>(encoded[index++]);

            decoded.append(count, currentChar);
        }
        return decoded;
    }
};

int main() {
    RunLengthEncoding rle;
    string input;

    cout << "Enter a string to encode: ";
    cin >> input;

    string encoded = rle.encode(input);
    cout << "Encoded: ";
    for (size_t i = 0; i < encoded.length(); i += 2) {
        cout << encoded[i] << (static_cast<unsigned char>(encoded[i + 1]));
    }
    cout << endl;

    string decoded = rle.decode(encoded);
    cout << "Decoded: " << decoded << endl;

    return 0;
}
