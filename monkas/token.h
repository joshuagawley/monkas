#ifndef MONKAS_TOKEN_H_
#define MONKAS_TOKEN_H_

#include <fmt/ostream.h>

#include <ostream>
#include <string_view>

namespace monkas {

enum class TokenType {
  kIllegal,
  kEof,

  kIdent,
  kInt,

  kEq,
  kLt,
  kGt,
  kAdd,
  kMinus,
  kSlash,
  kStar,
  kNot,

  kEqEq,
  kNotEq,

  kComma,
  kSemi,
  kDot,

  kOpenParen,
  kClosedParen,
  kOpenBrace,
  kClosedBrace,

  kFunc,
  kLet,
  kTrue,
  kFalse,
  kIf,
  kElse,
  kReturn
};

inline std::ostream &operator<<(std::ostream &os, TokenType type) {
  switch (type) {
    case TokenType::kIllegal:
      return os << "ILLEGAL";
    case TokenType::kEof:
      return os << "EOF";
    case TokenType::kNot:
      return os << "NOT";
    case TokenType::kAdd:
      return os << "ADD";
    case TokenType::kMinus:
      return os << "MINUS";
    case TokenType::kSlash:
      return os << "SLASH";
    case TokenType::kStar:
      return os << "STAR";
    case TokenType::kGt:
      return os << "GT";
    case TokenType::kLt:
      return os << "LT";
    case TokenType::kComma:
      return os << "COMMA";
    case TokenType::kIdent:
      return os << "IDENT";
    case TokenType::kInt:
      return os << "INT";
    case TokenType::kEq:
      return os << "EQ";
    case TokenType::kEqEq:
      return os << "EQ_EQ";
    case TokenType::kNotEq:
      return os << "NOT_EQ";
    case TokenType::kSemi:
      return os << "SEMI";
    case TokenType::kDot:
      return os << "DOT";
    case TokenType::kOpenParen:
      return os << "OPEN_PAREN";
    case TokenType::kClosedParen:
      return os << "CLOSED_PAREN";
    case TokenType::kOpenBrace:
      return os << "OPEN_BRACE";
    case TokenType::kClosedBrace:
      return os << "CLOSED_BRACE";
    case TokenType::kFunc:
      return os << "FUNC";
    case TokenType::kLet:
      return os << "LET";
    case TokenType::kTrue:
      return os << "TRUE";
    case TokenType::kFalse:
      return os << "FALSE";
    case TokenType::kIf:
      return os << "IF";
    case TokenType::kElse:
      return os << "ELSE";
    case TokenType::kReturn:
      return os << "RETURN";
    default:
      return os << "";
  }
}

class Token {
 private:
  TokenType type_;
  std::string_view literal_;

 public:
  constexpr Token(TokenType type, std::string_view literal)
      : type_(type), literal_(literal) {}

  constexpr friend bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.type_ == rhs.type_ && lhs.literal_ == rhs.literal_;
  }

  friend std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << token.type_;
    if (token.literal_.length() > 1 || token.type_ == TokenType::kInt) {
      os << "(" << token.literal_ << ")";
    }
    return os;
  }

  auto type() -> TokenType { return type_; }
  auto literal() -> std::string_view { return literal_; }
};

}  // namespace monkas

namespace fmt {

using TokenType = monkas::TokenType;
using Token = monkas::Token;

template <>
struct formatter<TokenType> : ostream_formatter {};

template <>
struct formatter<Token> : ostream_formatter {};

}  // namespace fmt

#endif  // MONKAS_TOKEN_H_
