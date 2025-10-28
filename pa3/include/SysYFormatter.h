#pragma once
#include <any>
#include <string>
#include "./SysYParserBaseVisitor.h"
// TODO: Implement SysYFormatter

class SysYFormatter : public SysYParserBaseVisitor
{
public:
    virtual std::any visitCompUnit(SysYParser::CompUnitContext *ctx) override;

    virtual std::any visitDecl(SysYParser::DeclContext *ctx) override;
    virtual std::any visitConstDecl(SysYParser::ConstDeclContext *ctx) override;

    virtual std::any visitBType(SysYParser::BTypeContext *ctx) override;

    virtual std::any visitConstDef(SysYParser::ConstDefContext *ctx) override;

    virtual std::any visitConstInitVal(SysYParser::ConstInitValContext *ctx) override;

    virtual std::any visitVarDecl(SysYParser::VarDeclContext *ctx) override;
    virtual std::any visitVarDef(SysYParser::VarDefContext *ctx) override;

    virtual std::any visitInitVal(SysYParser::InitValContext *ctx) override;

    virtual std::any visitFuncDef(SysYParser::FuncDefContext *ctx) override;

    virtual std::any visitFuncType(SysYParser::FuncTypeContext *ctx) override;

    virtual std::any visitFuncFParams(SysYParser::FuncFParamsContext *ctx) override;

    virtual std::any visitFuncFParam(SysYParser::FuncFParamContext *ctx) override
    ;

    virtual std::any visitBlock(SysYParser::BlockContext *ctx) override;

    virtual std::any visitBlockItem(SysYParser::BlockItemContext *ctx) override;

    virtual std::any visitStmt(SysYParser::StmtContext *ctx) override;

    virtual std::any visitExp(SysYParser::ExpContext *ctx) override;

    virtual std::any visitCond(SysYParser::CondContext *ctx) override;

    virtual std::any visitLVal(SysYParser::LValContext *ctx) override;

    virtual std::any visitPrimaryExp(SysYParser::PrimaryExpContext *ctx) override;

    virtual std::any visitNumber(SysYParser::NumberContext *ctx) override;

    virtual std::any visitUnaryExp(SysYParser::UnaryExpContext *ctx) override;

    virtual std::any visitUnaryOp(SysYParser::UnaryOpContext *ctx) override;

    virtual std::any visitFuncRParams(SysYParser::FuncRParamsContext *ctx) override;

    virtual std::any visitMulExp(SysYParser::MulExpContext *ctx);

    virtual std::any visitAddExp(SysYParser::AddExpContext *ctx);

    virtual std::any visitRelExp(SysYParser::RelExpContext *ctx);

    virtual std::any visitEqExp(SysYParser::EqExpContext *ctx) override;

    virtual std::any visitLAndExp(SysYParser::LAndExpContext *ctx) override;

    virtual std::any visitLOrExp(SysYParser::LOrExpContext *ctx) override;

    virtual std::any visitConstExp(SysYParser::ConstExpContext *ctx) override;

    // 当前缩进层级（
    int indent = 0;
    // 是否已输出过第一个函数，用于在函数之间插入空行
    bool firstFunctionSeen = false;

    //帮助判断KR风格
    bool follow=false;


    // 返回当前缩进字符串
    std::string indentStr() const;
    // 去掉字符串行尾多余空格
    std::string trimTrailing(const std::string &s) const;
};