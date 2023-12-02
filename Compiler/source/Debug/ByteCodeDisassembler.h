#pragma once

#include <Defines.h>
#include <VirtualMachine/ByteCode.h>

#include <qtextstream.h>

class COMPILER_API ByteCodeDisassembler
{
public:
    ByteCodeDisassembler(ByteCode& byteCode);

    QString PrettyPrint();

private:
    void PrettyPrintOp();

    void PrettyPrintLoadBool();
    void PrettyPrintNotBool();
    void PrettyPrintEqualBool();
    void PrettyPrintNotEqualBool();
    void PrettyPrintLoadInt32();
    void PrettyPrintAddInt32();
    void PrettyPrintSubtractInt32();
    void PrettyPrintMultiplyInt32();
    void PrettyPrintDivideInt32();
    void PrettyPrintNegateInt32();
    void PrettyPrintEqualInt32();
    void PrettyPrintNotEqualInt32();
    void PrettyPrintGreaterInt32();
    void PrettyPrintGreaterOrEqualInt32();
    void PrettyPrintLessInt32();
    void PrettyPrintLessOrEqualInt32();
    void PrettyPrintJump();
    void PrettyPrintJumpIfFalse();
    void PrettyPrintMove();
    void PrettyPrintPrintBool();
    void PrettyPrintPrintInt32();
    void PrettyPrintPrintNewLine();
    void PrettyPrintHalt();

    QTextStream& stream() { return m_stream; }
    QByteArray toUtf8() { return m_output.toUtf8(); }
    QString NewLine() { return QString("\n"); }

    ByteCode& m_byteCode;
    u16 m_ip;
    QString m_output;
    QTextStream m_stream;
};
