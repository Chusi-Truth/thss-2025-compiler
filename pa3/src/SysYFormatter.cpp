#include "SysYFormatter.h"
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

std::any SysYFormatter::visitCompUnit(SysYParser::CompUnitContext *ctx)
{
    return string("111");
}
std::any SysYFormatter::visitDecl(SysYParser::DeclContext *ctx) {};
std::any SysYFormatter::visitConstDecl(SysYParser::ConstDeclContext *ctx) {};

std::any SysYFormatter::visitBType(SysYParser::BTypeContext *ctx) {};

std::any SysYFormatter::visitConstDef(SysYParser::ConstDefContext *ctx) {};

std::any SysYFormatter::visitConstInitVal(SysYParser::ConstInitValContext *ctx) {};

std::any SysYFormatter::visitVarDecl(SysYParser::VarDeclContext *ctx) {};
std::any SysYFormatter::visitVarDef(SysYParser::VarDefContext *ctx) {};

std::any SysYFormatter::visitInitVal(SysYParser::InitValContext *ctx) {};

std::any SysYFormatter::visitFuncDef(SysYParser::FuncDefContext *ctx) {};

std::any SysYFormatter::visitFuncType(SysYParser::FuncTypeContext *ctx) {};

std::any SysYFormatter::visitFuncFParams(SysYParser::FuncFParamsContext *ctx) {};

std::any SysYFormatter::visitFuncFParam(SysYParser::FuncFParamContext *ctx) {};

std::any SysYFormatter::visitBlock(SysYParser::BlockContext *ctx) {};

std::any SysYFormatter::visitBlockItem(SysYParser::BlockItemContext *ctx) {};

std::any SysYFormatter::visitStmt(SysYParser::StmtContext *ctx) {};

std::any SysYFormatter::visitExp(SysYParser::ExpContext *ctx) {};

std::any SysYFormatter::visitCond(SysYParser::CondContext *ctx) {};

std::any SysYFormatter::visitLVal(SysYParser::LValContext *ctx) {};

std::any SysYFormatter::visitPrimaryExp(SysYParser::PrimaryExpContext *ctx) {};

std::any SysYFormatter::visitNumber(SysYParser::NumberContext *ctx) {};

std::any SysYFormatter::visitUnaryExp(SysYParser::UnaryExpContext *ctx) {};

std::any SysYFormatter::visitUnaryOp(SysYParser::UnaryOpContext *ctx) {};

std::any SysYFormatter::visitFuncRParams(SysYParser::FuncRParamsContext *ctx) {};

std::any SysYFormatter::visitMulExp(SysYParser::MulExpContext *ctx){};

std::any SysYFormatter::visitAddExp(SysYParser::AddExpContext *ctx){};

std::any SysYFormatter::visitRelExp(SysYParser::RelExpContext *ctx){};

std::any SysYFormatter::visitEqExp(SysYParser::EqExpContext *ctx) {};

std::any SysYFormatter::visitLAndExp(SysYParser::LAndExpContext *ctx) {};

std::any SysYFormatter::visitLOrExp(SysYParser::LOrExpContext *ctx) {};

std::any SysYFormatter::visitConstExp(SysYParser::ConstExpContext *ctx) {};