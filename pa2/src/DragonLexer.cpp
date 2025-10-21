#include "DragonLexer.hpp"
#include "Token.hpp"
#include <cctype>
#include <string>
#include <iostream>

DragonLexer::DragonLexer(const std::string &input)
    : Lexer(input) {}

Token DragonLexer::nextToken()
{
  if (peek == EOF_CHAR)
  {
    return Token(TokenType::EOF_T, "EOF", line);
  }
  if (peek == '\n')
  {
    advance();
  }

  if (std::isspace(peek))
  {
    return WS();
  }

  // TODO: finish me. You need to consider when to call ID()

  if (std::isalpha(peek))
  {
    // note: need to see if it is "if" or "else", it is considered in ID()
    return ID();
  }

  if (std::isdigit(peek))
  {
    return NUMBER();
  }

  int cur = peek;
  switch (cur)
  {
  // TODO: finish me. You need to consider EQ, NE, LT, LE, GT, GE
  case '(':
    advance();
    return Token(TokenType::L_PAREN, "(", line);
  case ')':
    advance();
    return Token(TokenType::R_PAREN, ")", line);
  case '{':
    advance();
    return Token(TokenType::L_BRACE, "{", line);
  case '}':
    advance();
    return Token(TokenType::R_BRACE, "}", line);
  case '[':
    advance();
    return Token(TokenType::L_BRACKET, "[", line);
  case ']':
    advance();
    return Token(TokenType::R_BRACKET, "]", line);
  case ',':
    advance();
    return Token(TokenType::COMMA, ",", line);
  case ';':
    advance();
    return Token(TokenType::SEMI, ";", line);
  case '+':
    advance();
    return Token(TokenType::PLUS, "+", line);
  case '-':
    advance();
    return Token(TokenType::MINUS, "-", line);
  case '*':
    advance();
    return Token(TokenType::MUL, "*", line);
  case '/':
    advance();
    return Token(TokenType::DIV, "/", line);
  case '.':
    advance();
    return Token(TokenType::DOT, ".", line);
  case '=':
    advance();
    return Token(TokenType::EQ, "=", line);
  case '<':
    advance();
    if (peek == '=')
    {
      advance();
      return Token(TokenType::LE, "<=", line);
    }
    else if (peek == '>')
    {
      advance();
      return Token(TokenType::NE, "<>", line);
    }
    return Token(TokenType::LT, "<", line);
  case '>':
    advance();
    if (peek == '=')
    {
      advance();
      return Token(TokenType::GE, ">=", line);
    }
    return Token(TokenType::GT, ">", line);
  case '\'':
    advance();
    return Token(TokenType::SQUOTE, "'", line);
  case EOF_CHAR:
    return Token(TokenType::EOF_T, "EOF", line);
  default:
    char ch = static_cast<char>(peek);
    if (peek == EOF_CHAR)
      return Token(TokenType::EOF_T, "EOF", line);
    std::string s(1, ch);
    advance();

    return Token(TokenType::UNKNOWN, s, line);
  }
}

Token DragonLexer::WS()
{
  // TODO: finish me. The WS() method should consume all whitespace characters (spaces, tabs, newlines)
  int start_line = line;
  std::string ws;
  while (std::isspace(peek))
  {
    ws += static_cast<char>(peek);
    advance();
  }
  return Token(TokenType::WS, ws, start_line);
}

Token DragonLexer::ID()
{
  // TODO: finish me. The ID() method should consume an identifier or keyword.
  std::string id;
  // already know the first one is alpha
  while (std::isalpha(peek) || std::isdigit(peek))
  {
    id += static_cast<char>(peek);
    advance();
  }
  if (id == "if")
    return Token(TokenType::IF, "if", line);
  if (id == "else")
    return Token(TokenType::ELSE, "else", line);
  // not if or else
  return Token(TokenType::ID, id, line);
}

Token DragonLexer::NUMBER()
{
  // use pre-read instead of revert
  std::string buffer;

  TokenType type = TokenType::INT;

  buffer += FIND_DIGITS();
  //check if is real number
  if (peek == '.' && pos + 1 < input.length() && std::isdigit(input[pos + 1]))
  {
    type = TokenType::REAL;
    buffer += static_cast<char>(peek);
    advance();
    buffer += FIND_DIGITS();
  }

  // check if is sci number
  if (peek == 'e' || peek == 'E')
  {

    size_t lookahead_pos = pos + 1;
    if (lookahead_pos < input.length() && (input[lookahead_pos] == '+' || input[lookahead_pos] == '-'))
    {
      lookahead_pos++;
    }

    if (lookahead_pos < input.length() && std::isdigit(input[lookahead_pos]))
    {
      type = TokenType::SCI;
      buffer += static_cast<char>(peek);
      advance();

      if (peek == '+' || peek == '-')
      {
        buffer += static_cast<char>(peek);
        advance();
      }
      buffer += FIND_DIGITS();
    }
  }

  return Token(type, buffer, line);
}

std::string DragonLexer::FIND_DIGITS()
{
  std::string digits;
  // not start with a digit, return
  if (!std::isdigit(peek))
  {
    return "";
  }

  digits += static_cast<char>(peek);
  advance();

  while (true)
  {
    // check if a digit is after '
    if (peek == '\'')
    {

      if (std::isdigit(input[pos + 1]))
      {

        digits += '\'';
        advance();
        digits += static_cast<char>(peek);
        advance();
      }
      else
      {
        break;
      }
    }
    else if (std::isdigit(peek))
    {

      digits += static_cast<char>(peek);
      advance();
    }
    else
    {

      break;
    }
  }
  return digits;
}