#include "DragonLexer.hpp"
#include "Token.hpp"
#include <cctype>
#include <string>

DragonLexer::DragonLexer(const std::string &input)
    : Lexer(input) {}

Token DragonLexer::nextToken()
{
  if (peek == EOF_CHAR)
  {
    return Token(TokenType::EOF_T, "EOF", line);
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
  default:
    char ch = static_cast<char>(peek);
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
    if (id == "if")
      return Token(TokenType::IF, "if", line);
    if (id == "else")
      return Token(TokenType::ELSE, "else", line);
  }
  //not if or else
  return Token(TokenType::ID,id,line);
}

Token DragonLexer::NUMBER()
{
  // TODO: finish me. The NUMBER() method should consume an integer, real number, or scientific notation number.

}

std::string DragonLexer::FIND_DIGITS()
{
  std::string digits;
  int accept_squote=2;
  //note: 2 means ' is acceptable, 1 means ' is not acceptable 0 means illgal
  while((std::isdigit(peek)||static_cast<char>(peek)=='\'')&&accept_squote)
  {
    char digit=static_cast<char>(peek);
    digits+=digit;
    if(digit=='\'') accept_squote--;
    else{
      accept_squote=std::min(2,accept_squote+1);
    }
    advance();
  }
  //calculate offset: digits must not end with '
  int offset =0;
  //actually, offset = 2-accept_squote
  while(!digits.empty()&&digits.back()=='\'') 
  {
    digits.pop_back();
    offset++;
  }
  if(offset>0)  resetPos(pos-offset);
  return digits;
  //set new position
}