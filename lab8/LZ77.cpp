#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;


class LZ77 {
public:

    LZ77(int window_size = 256, int lookahead_size = 15)
        : window_size(window_size), lookahead_size(lookahead_size) {}


    vector<tuple<int, int, char>> compress(const string &input) {
        vector<tuple<int, int, char>> compressed_data;
        int n = input.size();
        int pos = 0;

        while (pos < n) {
            pair<int, int> match = findLongestMatch(input, pos);

            int len = match.first;
            int dist = match.second;

            if (len == 0) {
                compressed_data.push_back(make_tuple(0, 0, input[pos]));
                pos++;
            } else {
                compressed_data.push_back(make_tuple(len, dist, input[pos + len]));
                pos += len + 1;
            }
        }

        return compressed_data;
    }

    string decompress(const vector<tuple<int, int, char>> &compressed_data) {
        string decompressed_data = "";

        for (const auto &entry : compressed_data) {
            int len, dist;
            char next_char;
            tie(len, dist, next_char) = entry;

            if (len == 0) {
                decompressed_data += next_char;
            } else {
                int start = decompressed_data.size() - dist;
                for (int i = 0; i < len; ++i) {
                    decompressed_data += decompressed_data[start + i];
                }
                decompressed_data += next_char;
            }
        }

        return decompressed_data;
    }

    static void printCompressedData(const vector<tuple<int, int, char>> &compressed_data) {
        for (const auto &entry : compressed_data) {
            int len, dist;
            char next_char;
            tie(len, dist, next_char) = entry;

            if (len == 0) {
                cout << "(0, 0, '" << next_char << "') ";
            } else {
                cout << "(" << len << ", " << dist << ", '" << next_char << "') ";
            }
        }
        cout << endl;
    }

private:
    int window_size;     
    int lookahead_size;   


    pair<int, int> findLongestMatch(const string &input, int position) {
        int max_len = 0;
        int max_dist = 0;

        int start = max(0, position - window_size);
        int end = position + lookahead_size;

        for (int i = start; i < position; ++i) {
            int match_len = 0;

            while (position + match_len < end && input[i + match_len] == input[position + match_len]) {
                ++match_len;
            }

            if (match_len > max_len) {
                max_len = match_len;
                max_dist = position - i;
            }
        }

        return make_pair(max_len, max_dist);
    }
};

int main() {
    string input;
    cout << "Enter the string to be compressed: ";
    getline(cin, input);
    cout << "Original data: " << input << endl;

    LZ77 lz77;

    auto compressed = lz77.compress(input);
    cout << "Compressed data: ";
    LZ77::printCompressedData(compressed);

    string decompressed = lz77.decompress(compressed);
    cout << "Decompressed data: " << decompressed << endl;

    return 0;
}
