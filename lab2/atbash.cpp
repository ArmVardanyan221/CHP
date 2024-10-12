#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Crypto
{
    public:
    virtual char* encrypt(const string &realtext) = 0;
    virtual char* decrypt(const string &ciphertext) = 0;
    
    virtual ~Crypto() = 0;
};
Crypto::~Crypto() {}

class TemplateMethodDecrypter : public Crypto
{
    private:
    int len = 256;
    char* arr1;
    char* arr2; 
    
    int findIndex(char sym)
    {
        int i = 0;
        while(arr2[i] != sym) i++;
        return i;
    }
    
    public:
    TemplateMethodDecrypter()
    {
        arr1 = new char[len];
        arr2 = new char[len];
        
        for(int i = 0; i < len; i++)
        {
            arr1[i] = (char)i;
            arr2[i] = (char)(len - i);
        }
    }
    
    virtual char* encrypt(const string &realtext) override {
        char* newtext = new char[realtext.length()];
        
        for(int i = 0; i < realtext.length(); i++)
        {
            *(newtext + i) = arr2[(int)realtext[i]];
        }
    
        return newtext;
    }
    
    virtual char* decrypt(const string &ciphertext) override {
        char* newtext = new char[ciphertext.length()];
        
        for(int i = 0; i < ciphertext.length(); i++)
        {
            *(newtext + i) = arr1[findIndex(ciphertext[i])];
        }
    
        return newtext;
    }
    
    ~TemplateMethodDecrypter() override
    {
        delete[] arr1;
        delete[] arr2;
    }
};

int main() {
    Crypto& crypto = *new TemplateMethodDecrypter();
    
    string realtext;
    cout << "Enter the text: ";
    cin >> realtext;
    
    string ciphertext = crypto.encrypt(realtext);
    cout << "Ciphertext: " << ciphertext << endl;

    string decryptedText = crypto.decrypt(ciphertext);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
