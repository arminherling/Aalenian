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
