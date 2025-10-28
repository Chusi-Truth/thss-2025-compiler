#include "SysYFormatter.h"
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

#define toString(x) std::any_cast<std::string>(x)

/*
note:需要讨论的问题
换行：
1.有分号必换行
2.有大代码块必换行

缩进：\n 后必加上缩进

*/

std::string SysYFormatter::indentStr() const
{
    return std::string(indent * 2, ' '); // 每层缩进两个空格
}

std::any SysYFormatter::visitCompUnit(SysYParser::CompUnitContext *ctx)
{
    string out;
    for (auto obj : ctx->children)
    {
        out += any_cast<string>(visit(obj));
    }
    //这个是为了方便给函数声明添加空行用的，如果输出开头是空行，那么直接删除。空行信息在token的时候就会删掉，因此不影响。
    if (!out.empty() && out[0] == '\n')
    {
        out.erase(0, 1); // 删除开头的换行
    }
    return out;
}
std::any SysYFormatter::visitDecl(SysYParser::DeclContext *ctx)
{
    if (ctx->constDecl())
        return visit(ctx->constDecl());
    return visit(ctx->varDecl());
}
std::any SysYFormatter::visitConstDecl(SysYParser::ConstDeclContext *ctx)
{
    // 这个是正好一行，最开始进行缩进，最后进行换行
    string out;
    out += indentStr();
    out += "const ";
    out += (toString(ctx->bType()->getText()) + " ");
    for (size_t i = 0; i < ctx->constDef().size(); ++i)
    {
        out += toString(visit(ctx->constDef(i)));
        if (i != ctx->constDef().size() - 1)
            out += ", ";
    }
    out += ";\n";
    return out;
}

// 可以直接跳过了
std::any SysYFormatter::visitBType(SysYParser::BTypeContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitConstDef(SysYParser::ConstDefContext *ctx)
{
    // constDef 一定不需要处理缩进,因为不会出现在一行的最前面，同理也不需要处理结尾
    string out;
    out += toString(ctx->IDENT()->getText());
    for (auto obj : ctx->constExp())
    {
        out += ("[" + toString(visit(obj)) + "]");
    }
    out += " = ";
    out += toString(visit(ctx->constInitVal()));
    return out;
}

std::any SysYFormatter::visitConstInitVal(SysYParser::ConstInitValContext *ctx)
{
    // 同样不需要考虑缩进与换行
    if (ctx->constExp())
        return toString(visit(ctx->constExp()));
    string out;
    out += "{";
    for (size_t i = 0; i < ctx->constInitVal().size(); ++i)
    {
        out += toString(visit(ctx->constInitVal(i)));
        if (i != ctx->constInitVal().size() - 1)
            out += ", ";
    }
    out += "}";
    return out;
}

std::any SysYFormatter::visitVarDecl(SysYParser::VarDeclContext *ctx)
{
    // 需要考虑缩进和换行
    string out;
    out += indentStr();
    out += (toString(ctx->bType()->getText()) + " ");
    for (size_t i = 0; i < ctx->varDef().size(); ++i)
    {
        out += toString(visit(ctx->varDef(i)));
        if (i != ctx->varDef().size() - 1)  out += ", ";
    }
    out += ";\n";
    return out;
}
std::any SysYFormatter::visitVarDef(SysYParser::VarDefContext *ctx)
{
    // constDef 一定不需要处理缩进,因为不会出现在一行的最前面，同理也不需要处理结尾
    string out;
    out += toString(ctx->IDENT()->getText());
    for (auto obj : ctx->constExp())
    {
        out += ("[" + toString(visit(obj)) + "]");
    }
    if (ctx->ASSIGN())
    {
        out += " = ";
        out += toString(visit(ctx->initVal()));
    }
    return out;
}

std::any SysYFormatter::visitInitVal(SysYParser::InitValContext *ctx)
{
    // 不需要考虑缩进与换行
    if (ctx->exp())
        return toString(visit(ctx->exp()));
    string out;
    out += "{";
    for (size_t i = 0; i < ctx->initVal().size(); ++i)
    {
        out += toString(visit(ctx->initVal(i)));
        if (i != ctx->initVal().size() - 1) out += ", ";
    }
    out += "}";
    return out;
}

std::any SysYFormatter::visitFuncDef(SysYParser::FuncDefContext *ctx) 
{
    //需要考虑缩进，但是不需要考虑换行，换行在 block部分考虑
    string out;
    out+="\n";
    out+=indentStr();
    out+=(toString(visit(ctx->funcType()))+" ");
    out+=(toString(ctx->IDENT()->getText()));
    out+="(";
    if(ctx->funcFParams())  out+=toString(visit(ctx->funcFParams()));
    out+=") ";
    //TODO: 这里存在一个问题，block需要进行分类讨论
    //直接使用一个记号，告诉处理函数是否需要换行即可
    follow=true;
    out+=toString(visit(ctx->block()));
    return out;

}

//这个也不用管
std::any SysYFormatter::visitFuncType(SysYParser::FuncTypeContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitFuncFParams(SysYParser::FuncFParamsContext *ctx)
{
    //这个不需要考虑缩进或者换行
    string out;
    for(size_t i=0; i<ctx->funcFParam().size();i++)
    {
        out+=toString(visit(ctx->funcFParam(i)));
        if(i!=ctx->funcFParam().size()-1)   out+=", ";
    }
    return out;
}

std::any SysYFormatter::visitFuncFParam(SysYParser::FuncFParamContext *ctx)
{
    //这个也不需要考虑，因为是上面的组成部分
    string out;
    out+=(toString(visit(ctx->bType()))+" ");
    out+=(toString(ctx->IDENT()->getText()));
    if(ctx->L_BRACKT().size()>0)
    {
        out+="[]";
        for(size_t i=1;i<ctx->L_BRACKT().size();i++)
        {
            out+=("["+toString(visit(ctx->exp(i)))+"]");
        }
    }
    return out;

}

std::any SysYFormatter::visitBlock(SysYParser::BlockContext *ctx)
{
    //note：这个要比较麻烦一些，要判断两个东西：如果是函数体，那么开始不缩进，结束缩进。反之则都需要缩进。
    string out;
    if(follow)
    {
        follow=false;
        //是一个函数体，{ 不需要缩进
        out+="{\n";
        //剩下的部分需要缩进，这里面会自动处理缩进
        indent++;
        for(auto obj : ctx->blockItem())   out+=toString(visit(obj));
        indent--;
        //最后一个缩进和函数名称是同级别的
        out+=(indentStr()+"}\n");
        return out;
    }
    else
    {
    //正常的代码块形式
    out+=(indentStr()+"{\n");
    indent++;
    for(auto obj : ctx->blockItem())   out+=toString(visit(obj));
    indent--;
    out+=(indentStr()+"}\n");
    return out;
    }
}

std::any SysYFormatter::visitBlockItem(SysYParser::BlockItemContext *ctx)
{
    //内部处理缩进和换行
    if(ctx->decl()) return toString(visit(ctx->decl()));
    return toString(visit(ctx->stmt()));
}

std::any SysYFormatter::visitStmt(SysYParser::StmtContext *ctx)
{
    //TODO: 目前的问题：面对 if else 语句的时候，如何提前知道，下面的语句是不是代码块
    //TODO: 一个可行的策略是预读？
    //return ctx->getText();
    //缩进和换行
    string out;
    if(ctx->lVal()) return (indentStr()+toString(visit(ctx->lVal()))+" = "+toString(ctx->exp())+";\n");
    else if(ctx->SEMICOLON())
    {
        if(ctx->exp())  return (indentStr()+toString(visit(ctx->exp()))+";\n");
        return indentStr()+";\n";
    }
    else if(ctx->block()) return toString(visit(ctx->block()));
    else if(ctx->IF())
    {
        out+=(indentStr()+"if("+toString(visit(ctx->cond()))+") ");
    }


    return out;
    

}

std::any SysYFormatter::visitExp(SysYParser::ExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitCond(SysYParser::CondContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitLVal(SysYParser::LValContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitPrimaryExp(SysYParser::PrimaryExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitNumber(SysYParser::NumberContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitUnaryExp(SysYParser::UnaryExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitUnaryOp(SysYParser::UnaryOpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitFuncRParams(SysYParser::FuncRParamsContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitMulExp(SysYParser::MulExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitAddExp(SysYParser::AddExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitRelExp(SysYParser::RelExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitEqExp(SysYParser::EqExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitLAndExp(SysYParser::LAndExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitLOrExp(SysYParser::LOrExpContext *ctx) { return ctx->getText(); };

std::any SysYFormatter::visitConstExp(SysYParser::ConstExpContext *ctx) { return ctx->getText(); };