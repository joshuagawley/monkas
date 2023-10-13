#include <fmt/core.h>

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <string_view>

#include "monkas/lexer.h"
#include "monkas/token.h"

using Token = monkas::Token;
using monkas::TokenType;

namespace monkas {
int Run(std::string_view input) {
  auto lexer = Lexer{input};

  for (auto token = lexer.NextToken(); !lexer.IsAtEnd();
       token = lexer.NextToken()) {
    fmt::println("{}", token);
    if (token.type() == monkas::TokenType::kIllegal) return EXIT_FAILURE;
    token = lexer.NextToken();
  }
  return EXIT_SUCCESS;
}
}  // namespace monkas

namespace {

auto ReadFile(std::string_view path) -> std::string {
  constexpr auto read_size = std::size_t{4096};
  auto stream = std::ifstream{path.data()};
  stream.exceptions(std::ios_base::badbit);

  if (!stream) throw std::ios_base::failure("File does not exist");

  auto output = std::string{};
  auto buffer = std::string(read_size, '\0');
  while (stream.read(&buffer[0], read_size)) {
    output.append(buffer, 0, stream.gcount());
  }
  output.append(buffer, 0, stream.gcount());
  return output;
}

int RunFile(std::string_view path) {
  auto input = ReadFile(path);
  return monkas::Run(input);
}

int Repl() {
  while (true) {
    auto input = std::string{};
    fmt::print("[monkas] >> ");
    std::getline(std::cin, input);

    auto result = monkas::Run(input);
  }
}
}  // namespace

int main(int argc, const char *argv[]) {
  if (argc == 1) return Repl();
  if (argc == 2) return RunFile(argv[1]);
}
