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
    std::string buffer;
    // 初始类型假定为 INT
    TokenType type = TokenType::INT;

    // 1. 解析所有数字的共同前缀（整数部分）
    buffer += FIND_DIGITS();

    // 2. 预读（Lookahead）来判断是否为 REAL
    // 检查当前是否是 '.' 并且 '.' 后面紧跟着一个数字
    if (peek == '.' && pos + 1 < input.length() && std::isdigit(input[pos + 1]))
    {
        type = TokenType::REAL; // 一旦满足条件，类型就升级为 REAL
        buffer += static_cast<char>(peek);
        advance(); // 确认安全后，消耗 '.'
        buffer += FIND_DIGITS(); // 消耗小数部分
    }

    // 3. 预读来判断是否为 SCI
    if (peek == 'e' || peek == 'E')
    {
        // 检查 'E' 后面是否跟着一个合法的指数部分
        size_t lookahead_pos = pos + 1;
        if (lookahead_pos < input.length() && (input[lookahead_pos] == '+' || input[lookahead_pos] == '-')) {
            lookahead_pos++; // 跳过符号
        }

        // 如果符号后面（或E后面）是数字，则这是一个合法的科学记数法
        if (lookahead_pos < input.length() && std::isdigit(input[lookahead_pos]))
        {
            type = TokenType::SCI; // 类型升级为 SCI
            buffer += static_cast<char>(peek);
            advance(); // 消耗 'E' 或 'e'

            if (peek == '+' || peek == '-')
            {
                buffer += static_cast<char>(peek);
                advance(); // 消耗 '+' 或 '-'
            }
            buffer += FIND_DIGITS(); // 消耗指数部分的数字
        }
    }

    return Token(type, buffer, line);
}

std::string DragonLexer::FIND_DIGITS()
{
  std::string digits;
  if (!std::isdigit(peek))
  {
    return ""; 
  }

  digits += static_cast<char>(peek);
  advance();

  while (true)
  {
    if (peek == '\'')
    {

      if (std::isdigit(input[pos + 1]))
      {

        digits += '\'';
        advance();
        digits += static_cast<char>(peek);
        advance();

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