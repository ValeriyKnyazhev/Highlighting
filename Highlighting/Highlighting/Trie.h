#pragma once

#include <vector>
#include <string>
#include <map>
#include <functional>


namespace Yapynb {

class CTrie {
public:
    using TPosition = size_t;
    using TChar = char;

    static const TPosition FromRoot;
    static const TPosition InvalidPosition;
    static const TPosition MaxCompletions;

    CTrie();

    TPosition Append(TChar by, TPosition from);

    template<class InputIt>
    TPosition AppendWord(
        InputIt begin, InputIt end,
        TPosition position = FromRoot,
        bool terminal = true
    ) {
        for (; IsValidPosition(position) && begin != end; ++begin) {
            position = Append(*begin, position);
        }
        if (terminal && IsValidPosition(position)) {
            EnsureTerminal(position);
        }
        return position;
    }

    template<class OutputIt>
    OutputIt FindCompletions(
        OutputIt out,
        TPosition commonRoot = FromRoot,
        size_t limit = MaxCompletions
    ) const;

    TPosition Root() const;
    bool IsValidPosition(TPosition pos) const;
    TPosition Go(TChar by, TPosition from = FromRoot) const;

    template<class InputIt>
    TPosition Go(InputIt begin, InputIt end, TPosition from = FromRoot) const {
        for (; IsValidPosition(from) && begin != end; ++begin) {
            from = Go(*begin, from);
        }
        return from;
    }

    bool IsTerminal(TPosition pos) const;
    void EnsureTerminal(TPosition pos);

private:
    using CTransitionMap = std::map<TChar, TPosition>;

    struct CNode {
        CTransitionMap Next;
        bool Terminal = false;
    };

    TPosition NewNode();

    std::vector<CNode> Nodes;
};

template<class OutputIt>
OutputIt CTrie::FindCompletions(OutputIt out, TPosition commonRoot, size_t limit) const {
    if (!IsValidPosition(commonRoot)) {
        return out;
    }

    std::string path;
    std::function<void(TPosition)> traverse = [&](TPosition pos) {
        if (Nodes[pos].Terminal && limit) {
            *out = path;
            ++out;
            --limit;
        }
        for (const auto& edge : Nodes[pos].Next) {
            if (!limit) {
                break;
            }
            path.push_back(edge.first);
            traverse(edge.second);
            path.pop_back();
        }
    };

    traverse(commonRoot);
    return out;
}

}
