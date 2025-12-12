#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string &source) {
  auto raw_elements = find_all(source.begin(), source.end(),
                               [](unsigned char c) { return std::isspace(c); });

  Corpus tokens;
  auto out_iter = std::inserter(tokens, tokens.end());
  std::transform(raw_elements.begin(), raw_elements.end() - 1,
                 raw_elements.begin() + 1, out_iter,
                 [&source](auto begin, auto end) -> Token {
                   return Token(source, begin, end);
                 });

  std::erase_if(tokens,
                [](const Token &token) { return token.content.empty(); });
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus &source,
                                 const Dictionary &dictionary) {
  namespace rv = std::ranges::views;
  auto misspelled_view =
      source | rv::filter([&dictionary](const Token &token) {
        return !dictionary.contains(token.content);
      }) |
      rv::transform([&dictionary](const Token &token) -> Misspelling {
        auto suggestion_view =
            dictionary | rv::filter([&token](const std::string &word) {
              return levenshtein(token.content, word) == 1;
            });
        std::set<std::string> suggestions(suggestion_view.begin(),
                                          suggestion_view.end());
        return Misspelling{token, suggestions};
      }) |
      rv::filter([](const Misspelling &missepll) {
        return !missepll.suggestions.empty();
      });
  return std::set<Misspelling>{misspelled_view.begin(), misspelled_view.end()};
};

/* Helper methods */

#include "utils.cpp"
