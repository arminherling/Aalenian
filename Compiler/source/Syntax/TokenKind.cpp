#include <Syntax/TokenKind.h>

QString Stringify(TokenKind kind)
{
	switch (kind)
	{
		case TokenKind::Plus:
			return QString("Plus");
		case TokenKind::Minus:
			return QString("Minus");
		case TokenKind::Star:
			return QString("Star");
		case TokenKind::Slash:
			return QString("Slash");
		case TokenKind::Dot:
			return QString("Dot");
		case TokenKind::Comma:
			return QString("Comma");
		case TokenKind::Equal:
			return QString("Equal");
		case TokenKind::OpenParenthesis:
			return QString("OpenParenthesis");
		case TokenKind::CloseParenthesis:
			return QString("CloseParenthesis");
		case TokenKind::OpenBracket:
			return QString("OpenBracket");
		case TokenKind::CloseBracket:
			return QString("CloseBracket");
		case TokenKind::Identifier:
			return QString("Identifier");
		case TokenKind::Number:
			return QString("Number");
		case TokenKind::String:
			return QString("String");
		case TokenKind::Error:
			return QString("Error");
		case TokenKind::Unknown:
			return QString("Unknown");
		case TokenKind::EndOfFile:
			return QString("EndOfFile");
		default:
			assert(!"String for TokenKind value was not defined yet");
			return QString();
	}
}

int COMPILER_API UnaryOperatorPrecedence(TokenKind kind)
{
	if (kind == TokenKind::Minus)
		return 4;

	return 0;
}

int COMPILER_API BinaryOperatorPrecedence(TokenKind kind)
{
	switch (kind)
	{
		case TokenKind::Dot:
		case TokenKind::DoubleColon:
			return 3;
		case TokenKind::Star:
		case TokenKind::Slash:
			return 2;
		case TokenKind::Plus:
		case TokenKind::Minus:
			return 1;
	}

	return 0;
}
