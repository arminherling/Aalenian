#pragma once

#include <Debug/BasePrinter.h>
#include <Defines.h>
//#include <Syntax/TypedNode.h>

class COMPILER_API TypedTreePrinter : public BasePrinter
{
public:
    TypedTreePrinter(/*TypedTree& typedTree, */i32 indentation = 4);

    QString PrettyPrint();

//private:
//    void PrettyPrintNode(TypedNode* node);

    //TypedTree& m_typedTree;
};
