#include <Debug/TypedTreePrinter.h>

TypedTreePrinter::TypedTreePrinter(/*TypedTree& typedTree,*/ i32 indentation)
    : BasePrinter(indentation)
    //, m_typedTree{ typedTree }
{
}

QString TypedTreePrinter::PrettyPrint()
{
    //for (const auto& globalStatement : m_typedTree.GlobalStatements())
    //{
    //    PrettyPrintNode(globalStatement);
    //}

    return toUtf8();
}

//QString TypedTreePrinter::PrettyPrintNode(TypedNode* node)
//{
//    switch (node->kind())
//    {
//        default:
//            stream() << Indentation() << QString("Missing NodeKind!!") << NewLine();
//            break;
//    }
//}
