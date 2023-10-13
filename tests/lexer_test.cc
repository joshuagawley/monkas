#include "../lexer.h"

#include <gtest/gtest.h>

#include <string_view>

using Token = monkas::Token;
using TokenType = monkas::TokenType;
using Lexer = monkas::Lexer;

TEST(Lexer, SingleCharTokens) {
  constexpr auto input = std::string_view{"=+(){}.;"};
  constexpr auto expected_tokens = std::array<monkas::Token, 9>{
      Token{TokenType::kEq,          "="},
      Token{TokenType::kAdd,         "+"},
      Token{TokenType::kOpenParen,   "("},
      Token{TokenType::kClosedParen, ")"},
      Token{TokenType::kOpenBrace,   "{"},
      Token{TokenType::kClosedBrace, "}"},
      Token{TokenType::kDot,         "."},
      Token{TokenType::kSemi,        ";"},
      Token{TokenType::kEof,         "" }
  };
  auto lexer = Lexer(input);
  auto token = lexer.NextToken();
  for (const auto &expected : expected_tokens) {
    ASSERT_EQ(token, expected);
    token = lexer.NextToken();
  }
}

TEST(Lexer, ActualSourceCode) {
  constexpr auto input = std::string_view{
      "let five = 5; \
  let ten = 10;                           \
                                          \
  let add = fn(x, y) {                    \
    x + y;                                \
  };                                      \
                                          \
  let result = add(five, ten);            \
  "};
  constexpr auto expected_tokens = std::array<monkas::Token, 37>{
      Token{TokenType::kLet,         "let"   },
      Token{TokenType::kIdent,       "five"  },
      Token{TokenType::kEq,          "="     },
      Token{TokenType::kInt,         "5"     },
      Token{TokenType::kSemi,        ";"     },
      Token{TokenType::kLet,         "let"   },
      Token{TokenType::kIdent,       "ten"   },
      Token{TokenType::kEq,          "="     },
      Token{TokenType::kInt,         "10"    },
      Token{TokenType::kSemi,        ";"     },
      Token{TokenType::kLet,         "let"   },
      Token{TokenType::kIdent,       "add"   },
      Token{TokenType::kEq,          "="     },
      Token{TokenType::kFunc,        "fn"    },
      Token{TokenType::kOpenParen,   "("     },
      Token{TokenType::kIdent,       "x"     },
      Token{TokenType::kComma,       ","     },
      Token{TokenType::kIdent,       "y"     },
      Token{TokenType::kClosedParen, ")"     },
      Token{TokenType::kOpenBrace,   "{"     },
      Token{TokenType::kIdent,       "x"     },
      Token{TokenType::kAdd,         "+"     },
      Token{TokenType::kIdent,       "y"     },
      Token{TokenType::kSemi,        ";"     },
      Token{TokenType::kClosedBrace, "}"     },
      Token{TokenType::kSemi,        ";"     },
      Token{TokenType::kLet,         "let"   },
      Token{TokenType::kIdent,       "result"},
      Token{TokenType::kEq,          "="     },
      Token{TokenType::kIdent,       "add"   },
      Token{TokenType::kOpenParen,   "("     },
      Token{TokenType::kIdent,       "five"  },
      Token{TokenType::kComma,       ","     },
      Token{TokenType::kIdent,       "ten"   },
      Token{TokenType::kClosedParen, ")"     },
      Token{TokenType::kSemi,        ";"     },
      Token{TokenType::kEof,         ""      }
  };
  auto lexer = Lexer(input);
  auto token = lexer.NextToken();
  for (const auto &expected : expected_tokens) {
    ASSERT_EQ(token, expected);
    token = lexer.NextToken();
  }
}

TEST(Lexer, LexingNonsense) {
  constexpr auto input = std::string_view{"!-/*5; 5 < 10 > 5"};
  constexpr auto expected_tokens = std::array<monkas::Token, 12>{
      Token{TokenType::kNot,   "!" },
      Token{TokenType::kMinus, "-" },
      Token{TokenType::kSlash, "/" },
      Token{TokenType::kStar,  "*" },
      Token{TokenType::kInt,   "5" },
      Token{TokenType::kSemi,  ";" },

      Token{TokenType::kInt,   "5" },
      Token{TokenType::kLt,    "<" },
      Token{TokenType::kInt,   "10"},
      Token{TokenType::kGt,    ">" },
      Token{TokenType::kInt,   "5" },
      Token{TokenType::kEof,   ""  },
  };
  auto lexer = Lexer(input);
  auto token = lexer.NextToken();
  for (const auto &expected : expected_tokens) {
    ASSERT_EQ(token, expected);
    token = lexer.NextToken();
  }
}

TEST(Lexer, MoreKeyWords) {
  constexpr auto input = std::string_view{
      "if (5 < 10) { \
return true;         \
} else {             \
return false;        \
}"};
  constexpr auto expected_tokens = std::array<monkas::Token, 17>{
      Token{TokenType::kIf,           "if"    },
      Token{TokenType::kOpenParen,    "("     },
      Token{TokenType::kInt,          "5"     },
      Token{TokenType::kLt,           "<"     },
      Token{TokenType::kInt,          "10"    },
      Token{TokenType::kClosedParen,  ")"     },
      Token{TokenType::kOpenBrace,    "{"     },
      Token{TokenType::kReturn,       "return"},
      Token{TokenType::kTrue,         "true"  },
      Token{monkas::TokenType::kSemi, ";"     },
      Token{TokenType::kClosedBrace,  "}"     },
      Token{TokenType::kElse,         "else"  },
      Token{TokenType::kOpenBrace,    "{"     },
      Token{TokenType::kReturn,       "return"},
      Token{TokenType::kFalse,        "false" },
      Token{monkas::TokenType::kSemi, ";"     },
      Token{TokenType::kClosedBrace,  "}"     },
  };
  auto lexer = Lexer(input);
  auto token = lexer.NextToken();
  for (const auto &expected : expected_tokens) {
    ASSERT_EQ(token, expected);
    token = lexer.NextToken();
  }
}

TEST(Lexer, ComparisonOps) {
  constexpr auto input = std::string_view{
      "10 == 10; \
     10 != 9;"};
  constexpr auto expected_tokens = std::array<monkas::Token, 9>{
      Token(TokenType::kInt, "10"), Token{TokenType::kEqEq,  "=="},
      Token(TokenType::kInt, "10"), Token{TokenType::kSemi,  ";" },
      Token(TokenType::kInt, "10"), Token{TokenType::kNotEq, "!="},
      Token(TokenType::kInt, "9"),  Token{TokenType::kSemi,  ";" },
      Token{TokenType::kEof,   ""  }
  };
  auto lexer = Lexer(input);
  auto token = lexer.NextToken();
  for (const auto &expected : expected_tokens) {
    ASSERT_EQ(token, expected);
    token = lexer.NextToken();
  }
}
