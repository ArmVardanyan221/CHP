#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;


struct TreeNode {
    char ch;
    int freq;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    bool operator>(const TreeNode& other) const {
        return freq > other.freq;
    }
};


unordered_map<char, int> buildFrequency(const string& text) {
    unordered_map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    return freqMap;
}


TreeNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<TreeNode*, vector<TreeNode*>, greater<TreeNode*>> minHeap;

    
    for (const auto& entry : freqMap) {
        minHeap.push(new TreeNode(entry.first, entry.second));
    }

    
    while (minHeap.size() > 1) {
        TreeNode* left = minHeap.top(); minHeap.pop();
        TreeNode* right = minHeap.top(); minHeap.pop();
        TreeNode* merged = new TreeNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }

    return minHeap.top();  
}


void generateCodes(TreeNode* node, const string& prefix, unordered_map<char, string>& huffmanCodes) {
    if (!node) return;

    if (node->ch != '\0') {
        huffmanCodes[node->ch] = prefix;  
    }

    generateCodes(node->left, prefix + "0", huffmanCodes);
    generateCodes(node->right, prefix + "1", huffmanCodes);
}


string encodeText(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encoded;
    for (char c : text) {
        encoded += huffmanCodes.at(c);
    }
    return encoded;
}


string decodeText(const string& encoded, TreeNode* root) {
    string decoded;
    TreeNode* current = root;

    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;

        if (current->ch != '\0') {
            decoded += current->ch;
            current = root;  
        }
    }

    return decoded;
}

int main() {
    string inputText = "abcd";

    
    unordered_map<char, int> freqMap = buildFrequency(inputText);

    
    TreeNode* root = buildHuffmanTree(freqMap);

    
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    
    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    
    string encodedText = encodeText(inputText, huffmanCodes);
    cout << "\nEncoded Text: " << encodedText << endl;

    
    string decodedText = decodeText(encodedText, root);
    cout << "\nDecoded Text: " << decodedText << endl;

    return 0;
}
