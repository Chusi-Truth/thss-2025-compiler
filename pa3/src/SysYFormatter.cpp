#include "SysYFormatter.h"
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

/*
note:需要讨论的问题
换行：
1.有分号必换行
2.有大代码块必换行

缩进：\n 后必加上缩进

*/






std::any SysYFormatter::visitCompUnit(SysYParser::CompUnitContext *ctx)
{
    string out;
    for(auto obj : ctx->children)
    {

    }
    
}
std::any SysYFormatter::visitDecl(SysYParser::DeclContext *ctx) {return ctx->getText();};
std::any SysYFormatter::visitConstDecl(SysYParser::ConstDeclContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitBType(SysYParser::BTypeContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitConstDef(SysYParser::ConstDefContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitConstInitVal(SysYParser::ConstInitValContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitVarDecl(SysYParser::VarDeclContext *ctx) {return ctx->getText();};
std::any SysYFormatter::visitVarDef(SysYParser::VarDefContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitInitVal(SysYParser::InitValContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitFuncDef(SysYParser::FuncDefContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitFuncType(SysYParser::FuncTypeContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitFuncFParams(SysYParser::FuncFParamsContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitFuncFParam(SysYParser::FuncFParamContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitBlock(SysYParser::BlockContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitBlockItem(SysYParser::BlockItemContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitStmt(SysYParser::StmtContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitExp(SysYParser::ExpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitCond(SysYParser::CondContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitLVal(SysYParser::LValContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitPrimaryExp(SysYParser::PrimaryExpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitNumber(SysYParser::NumberContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitUnaryExp(SysYParser::UnaryExpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitUnaryOp(SysYParser::UnaryOpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitFuncRParams(SysYParser::FuncRParamsContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitMulExp(SysYParser::MulExpContext *ctx){return ctx->getText();};

std::any SysYFormatter::visitAddExp(SysYParser::AddExpContext *ctx){return ctx->getText();};

std::any SysYFormatter::visitRelExp(SysYParser::RelExpContext *ctx){return ctx->getText();};

std::any SysYFormatter::visitEqExp(SysYParser::EqExpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitLAndExp(SysYParser::LAndExpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitLOrExp(SysYParser::LOrExpContext *ctx) {return ctx->getText();};

std::any SysYFormatter::visitConstExp(SysYParser::ConstExpContext *ctx) {return ctx->getText();};