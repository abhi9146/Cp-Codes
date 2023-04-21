#include <iostream>
#include <string>
using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// Trie node
class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isLeaf;

    TrieNode() {
        isLeaf = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

// Trie data structure
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& key) {
        TrieNode* pCrawl = root;
        int n = key.length();
        for (int i = 0; i < n; i++) {
            int index = CHAR_TO_INDEX(key[i]);
            if (!pCrawl->children[index]) {
                pCrawl->children[index] = new TrieNode();
            }
            pCrawl = pCrawl->children[index];
        }
        pCrawl->isLeaf = true;
    }

    bool search(const string& key) {
        TrieNode* pCrawl = root;
        int n = key.length();
        for (int i = 0; i < n; i++) {
            int index = CHAR_TO_INDEX(key[i]);
            if (!pCrawl->children[index]) {
                return false;
            }
            pCrawl = pCrawl->children[index];
        }
        return (pCrawl != nullptr && pCrawl->isLeaf);
    }

    void remove(const string& key) {
        TrieNode* pCrawl = root;
        int n = key.length();
        for (int i = 0; i < n; i++) {
            int index = CHAR_TO_INDEX(key[i]);
            if (!pCrawl->children[index]) {
                return;
            }
            pCrawl = pCrawl->children[index];
        }
        pCrawl->isLeaf = false;
    }

private:
    TrieNode* root;
};

// Driver code
int main() {
    Trie trie;

    // Input keys (use only 'a' through 'z' and lower case)
    string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    int n = sizeof(keys)/sizeof(keys[0]);

    // Construct trie
    for (int i = 0; i < n; i++) {
        trie.insert(keys[i]);
    }

    // Test search
    cout << "the --- " << (trie.search("the") ? "Present in trie" : "Not present in trie") << endl;
    cout << "these --- " << (trie.search("these") ? "Present in trie" : "Not present in trie") << endl;

    // Test remove
    trie.remove("the");
    cout << "the --- " << (trie.search("the") ? "Present in trie" : "Not present in trie") << endl;
    cout << "thaw --- " << (trie.search("thaw") ? "Present in trie" : "Not present in trie") << endl;

    return 0;
}
