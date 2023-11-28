#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <utility>
#include "Windows.h"

using namespace std;

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};


struct CompareHuffmanNodes {
    bool operator()(HuffmanNode *const &node1, HuffmanNode *const &node2) {
        return node1->frequency > node2->frequency;
    }
};

HuffmanNode *buildHuffmanTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareHuffmanNodes> &minHeap) {
    while (minHeap.size() > 1) {
        HuffmanNode *left = minHeap.top();
        minHeap.pop();

        HuffmanNode *right = minHeap.top();
        minHeap.pop();

        auto *newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

void buildHuffmanCodes(HuffmanNode *root, const string &code, unordered_map<char, string> &huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    buildHuffmanCodes(root->left, code + "0", huffmanCodes);
    buildHuffmanCodes(root->right, code + "1", huffmanCodes);
}

string encodeHuffman(const string &message, unordered_map<char, string> &huffmanCodes) {
    string encodedMessage;
    for (char c: message) {
        encodedMessage += huffmanCodes[c];
    }
    return encodedMessage;
}

string decodeHuffman(HuffmanNode *root, const string &encodedMessage) {
    string decodedMessage;
    HuffmanNode *current = root;
    for (char bit: encodedMessage) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (!current->left && !current->right) {
            decodedMessage += current->data;
            current = root;
        }
    }
    return decodedMessage;
}


struct ShannonFanoNode {
    char letter;
    string code;
    double probability;

    ShannonFanoNode(char letter, string code, double probability) : letter(letter), code(std::move(code)),
                                                                    probability(probability) {}
};

void shannonFano(int left, int right, vector<ShannonFanoNode *> &nodes) {
    if (left == right - 1) {
        return;
    }
    int currentSequenceStart = left;
    int currentSequenceEnd = right - 1;
    int sequenceLeftEnd = 0;
    int sequenceRightStart = 0;
    double leftSum = 0, rightSum = 0, sum = 0;
    for (int i = currentSequenceStart; i <= currentSequenceEnd; i++) {
        sum += nodes[i]->probability;
    }
    double minDiff = sum;
    for (int i = currentSequenceStart; i <= currentSequenceEnd; i++) {
        leftSum += nodes[i]->probability;
        rightSum = sum - leftSum;
        if (abs(leftSum - rightSum) < minDiff) {
            minDiff = abs(leftSum - rightSum);
        } else {
            sequenceRightStart = i;
            sequenceLeftEnd = i - 1;
            break;
        }
    }
    for (int i = currentSequenceStart; i <= sequenceLeftEnd; i++) {
        nodes[i]->code += "0";
    }
    for (int i = sequenceRightStart; i <= currentSequenceEnd; i++) {
        nodes[i]->code += "1";
    }
    shannonFano(currentSequenceStart, sequenceLeftEnd + 1, nodes);
    shannonFano(sequenceRightStart, currentSequenceEnd + 1, nodes);
}

struct comparatorShannonFano {
    bool operator()(ShannonFanoNode *lx, ShannonFanoNode *rx) const {
        return lx->probability > rx->probability;
    }
};

void sortShannonFano(vector<ShannonFanoNode *> &nodes) {
    sort(nodes.begin(), nodes.end(), comparatorShannonFano());
}

vector<ShannonFanoNode *> createLettersMapShannonFano(string &str) {
    unordered_map<char, double> lettersMap;
    for (char letter: str) {
        lettersMap[letter] = 0;
    }
    for (char letter: str) {
        lettersMap[letter] += 1;
    }
    vector<ShannonFanoNode *> nodes;
    int i = 0;
    for (const auto &[letter, count]: lettersMap) {
        nodes.emplace_back(new ShannonFanoNode(letter, "", count / str.length()));
        i++;
    }
    sortShannonFano(nodes);
    return nodes;
}

ShannonFanoNode *findByCodeShannonFano(const string &code, vector<ShannonFanoNode *> &nodes) {
    for (auto &cell: nodes) {
        if (cell->code == code)
            return cell;
    }
    return nullptr;
}

ShannonFanoNode *findBySymbolShannonFano(char symbol, vector<ShannonFanoNode *> &nodes) {
    for (auto cell: nodes) {
        if (cell->letter == symbol)
            return cell;
    }
}

string encodeShannonFano(string str, vector<ShannonFanoNode *> &nodes) {
    string encoded;
    for (char letter: str) {
        encoded += findBySymbolShannonFano(letter, nodes)->code;
    }
    return encoded;
}

string decodeShannonFano(string &str, vector<ShannonFanoNode *> &nodes) {
    string decoded;
    string currentSequence;
    for (char letter: str) {
        currentSequence += letter;
        ShannonFanoNode *crnt = findByCodeShannonFano(currentSequence, nodes);
        if (crnt != nullptr) {
            decoded += crnt->letter;
            currentSequence = "";
        }
    }
    return decoded;
}

struct Token {
    int offset;
    int length;
    char nextChar;

    Token(int o, int l, char c) : offset(o), length(l), nextChar(c) {}
};

vector<Token> compressLZ77(const string &input) {
    vector<Token> compressed;
    int inputSize = static_cast<int>(input.size());
    int currentPosition = 0;

    while (currentPosition < inputSize) {
        int maxMatchLength = 0;
        int bestMatchOffset = 0;

        for (int offset = 1; offset <= currentPosition; ++offset) {
            int matchLength = 0;

            while (currentPosition + matchLength < inputSize &&
                   input[currentPosition + matchLength] == input[currentPosition - offset + matchLength]) {
                ++matchLength;
            }

            if (matchLength > maxMatchLength) {
                maxMatchLength = matchLength;
                bestMatchOffset = offset;
            }
        }

        if (maxMatchLength > 0) {
            compressed.emplace_back(bestMatchOffset, maxMatchLength, input[currentPosition + maxMatchLength]);
            currentPosition += maxMatchLength + 1;
        } else {
            compressed.emplace_back(0, 0, input[currentPosition]);
            ++currentPosition;
        }
    }

    return compressed;
}

string decompressLZ77(const vector<Token> &compressed) {
    string decompressed;

    for (const Token &token: compressed) {
        if (token.length > 0) {
            int startPos = static_cast<int>(decompressed.size()) - token.offset;
            for (int i = 0; i < token.length; ++i) {
                decompressed.push_back(decompressed[startPos + i]);
            }
        }
        decompressed.push_back(token.nextChar);
    }

    return decompressed;
}


vector<pair<int, char>> compressLZ78(string data) {
    unordered_map<string, int> storage;
    vector<pair<int, char>> compressed_data;
    string current_symbol = "";
    int index = 1;
    int iter = 0;
    for (char character: data) {
        iter++;
        current_symbol += character;
        if (storage.find(current_symbol) == storage.end() || iter == data.size()) {
            storage[current_symbol] = index;
            compressed_data.push_back(make_pair(
                    storage[current_symbol.substr(0, current_symbol.length() - 1)], character
            ));
            index += 1;
            current_symbol = "";
        }
    }

    return compressed_data;
}

string decompressLZ78(vector<pair<int, char>> data) {
    unordered_map<int, string> storage;
    string decompressed_data = "";
    int index = 1;
    for (auto character: data) {
        storage[index] = storage[character.first] + character.second;
        decompressed_data += storage[index];
        index += 1;
    }

    return decompressed_data;
}


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout << "Choose task:\n"
            "1 - Huffmann\n"
            "2 - Shannon-Fano\n"
            "3 - LZ77\n"
            "4 - LZ78\n";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: {
            string message = "Komarnitskiy Egor Alexandrovich";
            unordered_map<char, int> frequencyMap;
            for (char c: message) {
                frequencyMap[c]++;
            }
            priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareHuffmanNodes> minHeap;
            for (auto &entry: frequencyMap) {
                minHeap.push(new HuffmanNode(entry.first, entry.second));
            }

            HuffmanNode *root = buildHuffmanTree(minHeap);

            unordered_map<char, string> huffmanCodes;
            buildHuffmanCodes(root, "", huffmanCodes);

            string encodedMessage = encodeHuffman(message, huffmanCodes);
            string decodedMessage = decodeHuffman(root, encodedMessage);

            cout << "Original Message: " << message << "\n";
            cout << "Huffman Codes: \n";
            for (const auto &[chr, code]: huffmanCodes) {
                cout << chr << "\t" + code + "\n";
            }
            cout << "Encoded Message: " << encodedMessage << "\n";
            cout << "Decoded Message: " << decodedMessage << "\n";
            double average_code_length = 0;
            double dispersion = 0;
            for (const auto &[chr, code]: huffmanCodes) {
                average_code_length += (double(frequencyMap[chr]) / double(message.length())) * double(code.length());
            }
            cout << "Average code length: " << average_code_length << "\n";
            for (const auto &[chr, code]: huffmanCodes) {
                dispersion += (double(frequencyMap[chr]) / double(message.length())) *
                              (double(code.length()) - average_code_length) *
                              (double(code.length()) - average_code_length);
            }
            cout << "Dispersion: " << dispersion << "\n";
            cout << "Compression ratio ASCII / Huffman: "
                 << (8. * double(message.length())) / double(encodedMessage.length()) << "\n";
            cout << "Compression ratio Uniform code / Huffman: "
                 << double(message.length()) * ceil(log2(huffmanCodes.size())) / double(encodedMessage.length())
                 << "\n";
            break;
        }
        case 2: {
            ifstream input_file("input.txt");
            if (!input_file.is_open()) {
                cerr << "Failed to open the file!" << endl;
                return 1;
            }
            string message;
            getline(input_file, message);
            input_file.close();

            vector<ShannonFanoNode *> nodes = createLettersMapShannonFano(message);
            shannonFano(0, nodes.size(), nodes);
            cout << "ShannonFano Codes: " << endl;
            for (ShannonFanoNode *i: nodes) {
                cout << i->letter << "\t" << i->code << "\n";
            }
            string encoded = encodeShannonFano(message, nodes);
            cout << "Encoded Message: " << encoded << endl;
            cout << "Decoded Message: " << decodeShannonFano(encoded, nodes) << endl;
            cout << "Compression percentage: " << double(encoded.length()) / (double(message.length()) * 8) * 100
                 << "%\n";
            break;

        }
        case 3: {
            string message = "0001010010101001101";

            vector<Token> compressedData = compressLZ77(message);
            cout << "Compressed Message:\n";
            for (const Token &token: compressedData) {
                cout << "(" << token.offset << ", " << token.length << ", " << token.nextChar << ") ";
            }
            cout << "\n";
            string decompressedString = decompressLZ77(compressedData);
            cout << "Decompressed Message: " << decompressedString << "\n";

            break;

        }
        case 4: {

            string message = "kukurkukurekureku";
            vector<pair<int, char>> compressed_message = compressLZ78(message);
            string decompressed_message = decompressLZ78(compressed_message);
            cout << "Compressed Message:\n";
            for (auto element: compressed_message) {
                cout << "(" << element.first << ", " << element.second << ") ";
            }
            cout << "\nDecompressed Message: " << decompressed_message << endl;
            break;
        }
        default:
            cerr << "No task selected!\n";
            return 1;
    }


}