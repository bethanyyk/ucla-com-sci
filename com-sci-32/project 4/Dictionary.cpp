#include "Dictionary.h"
#include <string>
#include <vector>
#include <cctype>
#include <utility>  // for swap
#include <algorithm> // for sort
using namespace std;

const int DEFAULT_MAX = 50000;
void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets)
        :m_maxBuckets(maxBuckets)
    {

    }
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    vector<string> m_words[DEFAULT_MAX];
    int m_maxBuckets;
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);

    string temp = word;
    sort(temp.begin(), temp.end());

    hash<string> hash;
    size_t hashValue = hash(temp) % m_maxBuckets;
    m_words[hashValue].push_back(word);
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    sort(letters.begin(), letters.end());
    int total = 0;
    for (int j = 0; j < letters.size(); j++)
    {
        total += letters.at(j);
    }
    hash<string> hash;
    size_t hashValue = hash(letters) % m_maxBuckets;

    for (int i = 0; i < m_words[hashValue].size(); i++)
    {
        if (m_words[hashValue].at(i).size() == letters.size())
        {
            int temp = 0;

            for (int j = 0; j < letters.size(); j++)
            {
                temp += m_words[hashValue].at(i).at(j);
            }

            if (temp == total)
            {
                string temp = m_words[hashValue].at(i);
                sort(temp.begin(), temp.end());
                sort(letters.begin(), letters.end());
                
                if (temp == letters)
                {
                    callback(m_words[hashValue].at(i));
                }
            }
        }
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
