#include <fmt/core.h>

#include "monkas/lexer.h"
#include "monkas/token.h"

using Token = monkas::Token;
using monkas::TokenType;

int main() {
  auto input = std::string{"!-/*5 5 < 10 > 5"};
  constexpr auto expected_tokens = std::array<monkas::Token, 10>{
      Token{TokenType::kNot,   "!" },
      Token{TokenType::kMinus, "-" },
      Token{TokenType::kSlash, "/" },
      Token{TokenType::kStar,  "*" },
      Token{TokenType::kInt,   "5" },
      Token{TokenType::kLt,    "<" },
      Token{TokenType::kInt,   "10"},
      Token{TokenType::kGt,    ">" },
      Token{TokenType::kInt,   "5" },
      Token{TokenType::kEof,   ""  }
  };
  auto lexer = monkas::Lexer(input);
  auto token = lexer.NextToken();
  while (!lexer.IsAtEnd()) {
    fmt::println("{}", token);
    token = lexer.NextToken();
  }
}
