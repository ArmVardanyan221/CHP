#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

void runLengthEncode(const char* input, char* encoded) {
    int length = strlen(input);
    int index = 0;
    unsigned char count = 1; 

    for (int i = 1; i <= length; ++i) {
        if (i < length && input[i] == input[i - 1]) {
            count++;
        } else {
            encoded[index++] = input[i - 1];   
            encoded[index++] = count;          
            count = 1;
        }
    }
    encoded[index] = '\0'; 
}

void runLengthDecode(const char* encoded, char* decoded) {
    int index = 0;
    int decodedIndex = 0;

    while (encoded[index] != '\0') {
        char currentChar = encoded[index++];
        unsigned char count = encoded[index++]; 

        for (int i = 0; i < count; ++i) {
            decoded[decodedIndex++] = currentChar;
        }
    }
    decoded[decodedIndex] = '\0';
}

int main() {
    const int MAX_SIZE = 100; 
    char input[MAX_SIZE];
    char encoded[MAX_SIZE * 2]; 
    char decoded[MAX_SIZE];

    cout << "Enter a string to encode: ";
    cin >> input;

    runLengthEncode(input, encoded);
    cout << "Encoded: ";
    for (int i = 0; encoded[i] != '\0'; i += 2) {
        cout << encoded[i] << (encoded[i + 1]); 
    }
    cout << endl;

    runLengthDecode(encoded, decoded);
    cout << "Decoded: " << decoded << endl;

    return 0;
}
