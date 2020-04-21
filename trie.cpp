#include <iostream>
#include <unordered_map>

class Trie {
private:
    std::unordered_map<char, Trie*> next_symbols;
    bool is_word;

public:
    /* Initialize data structure here. */
    Trie() {
        is_word = false;
    }
    
    /* Inserts a word into the trie. */
    void insert(string word) {
        Trie* smb = this;
        for (const char c : word) {
            if (smb->next_symbols.find(c) == smb->next_symbols.end())
                smb->next_symbols[c] = new Trie();
            smb = smb->next_symbols[c];
        }
        smb->is_word = true;
    }
    
    /* Returns whether the word is in the trie. */
    bool search(string word) {
        Trie* smb = this;
        for (const char c : word) {
            if (smb->next_symbols.find(c) == smb->next_symbols.end())
                return false;
            smb = smb->next_symbols[c];
        }
        return smb->is_word;
    }
    
    /* Returns whether there is any word in the trie that starts with the given prefix. */
    bool has_prefix(string prefix) {
        Trie* smb = this;
        for (const char c : prefix) {
            if (smb->next_symbols.find(c) == smb->next_symbols.end())
                return false;
            smb = smb->next_symbols[c];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->has_prefix(prefix);
 */
 
