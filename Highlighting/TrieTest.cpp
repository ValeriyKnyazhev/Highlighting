#include "TrieTest.h"
#include "Trie.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

#include <cassert>
#include <cstdlib>

namespace Yapynb {

namespace {


class TrieTestFixture {
public:
    void DoTest() {
        static const std::string text =
            "abadd"
            " aba abacaba a abacabadabacaba"
            " begin end"
            " beginning"
        ;

        SplitAndAdd(text);

        CheckCompletions("a", 0, {});
        CheckCompletions("a", 10, {"", "ba", "bacaba", "bacabadabacaba", "badd"});
        CheckCompletions("a", 3, {"", "ba", "bacaba"});
        CheckCompletions("b", 1, {"egin"});
        CheckCompletions("b", 2, {"egin", "eginning"});
        CheckCompletions("g", 5, {});
        CheckCompletions("abaq", 5, {});
    }

    void CheckCompletions(
        const std::string& prefix,
        size_t limit,
        const std::vector<std::string>& expected
    ) {
        auto pos = trie.Go(prefix.begin(), prefix.end());
        std::vector<std::string> actual;
        trie.FindCompletions(std::back_inserter(actual), pos, limit);
        if (expected != actual) {
            std::cerr << "expected: [\n";
            for (const auto& s : expected) {
                std::cerr << "\t\"" << s << "\",\n";
            }
            std::cerr << "]\nactual: [\n";
            for (const auto& s : actual) {
                std::cerr << "\t\"" << s << "\",\n";
            }
            std::cerr << "]\n";
            exit(1);
        }
    }

    void SplitAndAdd(const std::string text) {
        std::istringstream iss(text);

        std::string word;
        while (std::getline(iss, word, ' ')) {
            trie.AppendWord(word.begin(), word.end());
        }
    }

private:
    CTrie trie;
};

}

void TrieTest() {
    TrieTestFixture f;
    f.DoTest();
}

}  // Yapynb
