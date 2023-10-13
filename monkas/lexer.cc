#include "lexer.h"

#include <cctype>
#include <string_view>

#include "token.h"

namespace {
using monkas::TokenType;

constexpr auto CheckKeyword(std::string_view ident) -> TokenType {
  if (ident == "fn") return TokenType::kFunc;
  if (ident == "let") return TokenType::kLet;
  if (ident == "if") return TokenType::kIf;
  if (ident == "else") return TokenType::kElse;
  if (ident == "true") return TokenType::kTrue;
  if (ident == "false") return TokenType::kFalse;
  if (ident == "return") return TokenType::kReturn;

  return TokenType::kIdent;
}
}  // namespace

namespace monkas {

auto Lexer::SkipWhitespace() -> void {
  while (std::isspace(*current_char_)) {
    ++(this->current_char_);
  }
}

auto Lexer::MaybeComp(TokenType one_char_type, TokenType two_char_type)
    -> Token {
  if (*(current_char_ + 1) == '=') {
    return NCharToken(two_char_type, 2);
  }
  return NCharToken(one_char_type, 1);
}

auto Lexer::NCharToken(TokenType type, std::size_t n) -> Token {
  auto token = Token{type, GetSpan(n)};
  current_char_ += n;
  return token;
}

auto Lexer::ReadIdentifier() -> Token {
  auto start = current_char_;
  while (std::isalpha(static_cast<unsigned char>(*current_char_))) {
    ++current_char_;
  }

  auto ident = std::string_view{start, current_char_};

  return {CheckKeyword(ident), ident};
}

auto Lexer::ReadNumber() -> Token {
  auto start = current_char_;
  while (std::isdigit(static_cast<unsigned char>(*current_char_))) {
    ++current_char_;
  }

  return {
      TokenType::kInt, {start, current_char_}
  };
}

auto Lexer::NextToken() -> Token {
  SkipWhitespace();
  if (current_char_ >= input_.cend()) return {TokenType::kEof, ""};
  switch (*current_char_) {
    case '=':
      return MaybeComp(TokenType::kEq, TokenType::kEqEq);
    case ';':
      return NCharToken(TokenType::kSemi, 1);
    case '(':
      return NCharToken(TokenType::kOpenParen, 1);
    case ')':
      return NCharToken(TokenType::kClosedParen, 1);
    case '{':
      return NCharToken(TokenType::kOpenBrace, 1);
    case '}':
      return NCharToken(TokenType::kClosedBrace, 1);
    case ',':
      return NCharToken(TokenType::kComma, 1);
    case '+':
      return NCharToken(TokenType::kAdd, 1);
    case '-':
      return NCharToken(TokenType::kMinus, 1);
    case '*':
      return NCharToken(TokenType::kStar, 1);
    case '/':
      return NCharToken(TokenType::kSlash, 1);
    case '.':
      return NCharToken(TokenType::kDot, 1);
    case '!':
      return MaybeComp(TokenType::kNot, TokenType::kNotEq);
    case '<':
      return NCharToken(TokenType::kLt, 1);
    case '>':
      return NCharToken(TokenType::kGt, 1);
    default: {
      if (std::isalpha(static_cast<unsigned char>(*current_char_))) {
        return ReadIdentifier();
      }
      if (std::isdigit(static_cast<unsigned char>(*current_char_))) {
        return ReadNumber();
      }
      return NCharToken(TokenType::kIllegal, 1);
    }
  }
}

}  // namespace monkas