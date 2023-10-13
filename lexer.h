#ifndef MONKAS__LEXER_H_
#define MONKAS__LEXER_H_

#include <string_view>

#include "token.h"

namespace monkas {

class Lexer {
 private:
  std::string_view input_;
  std::string_view::iterator current_char_;

  auto NCharToken(TokenType type, std::size_t n) -> Token;
  auto ReadIdentifier() -> Token;
  auto ReadNumber() -> Token;
  auto MaybeComp(TokenType one_char_type, TokenType two_char_type) -> Token;
  auto SkipWhitespace() -> void;

  constexpr auto GetSpan(std::size_t n) -> std::string_view {
    return {current_char_, current_char_ + n};
  }

 public:
  constexpr Lexer(std::string_view input)
      : input_(input), current_char_(input.cbegin()) {}

  constexpr auto IsAtEnd() -> bool { return current_char_ >= input_.cend(); }
  auto NextToken() -> Token;
};

}  // namespace monkas

#endif  // MONKAS__LEXER_H_
