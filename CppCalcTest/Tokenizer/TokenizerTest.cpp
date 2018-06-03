#include "pch.h"
#include "TokenizerMacros.h"

TEST(Tokenizer_tokenize, EmptyString) {
    TOKENIZE_SOURCE(""s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIntegerLiteral) {
    TOKENIZE_SOURCE("42"s);

    EXPECT_INTEGER_LITERAL(42UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIntegerLiteral_0) {
    TOKENIZE_SOURCE("0"s);

    EXPECT_INTEGER_LITERAL(0UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, InvalidIntegerLiteral) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("01"), std::logic_error);
}

TEST(Tokenizer_tokenize, MildlyInvalidIntegerLiteralUpperBound) {
    TOKENIZE_SOURCE("2147483648"s);

    EXPECT_INTEGER_LITERAL(2147483648UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, WildlyInvalidIntegerLiteralUpperBound) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("9999999999999999"), std::logic_error);
}

TEST(Tokenizer_tokenize, EmptyStringLiteral) {
    TOKENIZE_SOURCE("\"\""s);

    EXPECT_STRING_LITERAL(""s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, SimpleStringLiteral) {
    TOKENIZE_SOURCE("\"Hello, World!\""s);

    EXPECT_STRING_LITERAL("Hello, World!"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, StringLiteral_EscapedBackslash) {
    TOKENIZE_SOURCE("\"\\\\\""s);

    EXPECT_STRING_LITERAL("\\"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, StringLiteral_EscapedDoubleQuote) {
    TOKENIZE_SOURCE("\"\\\"\""s);

    EXPECT_STRING_LITERAL("\""s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, StringLiteral_EscapedNewline) {
    TOKENIZE_SOURCE("\"\\r\\n\""s);

    EXPECT_STRING_LITERAL("\r\n"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, InvalidStringLiteral_Nonterminated) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("\"Hi!"), std::logic_error);
}

TEST(Tokenizer_tokenize, InvalidStringLiteral_DanglingEscapeSequence) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("\"\\\""), std::logic_error);
}

TEST(Tokenizer_tokenize, InvalidStringLiteral_NewlineCharacter) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("\"\r\n\""), std::logic_error);
}

TEST(Tokenizer_tokenize, IsolatedBooleanLiteral_True) {
    TOKENIZE_SOURCE("true"s);

    EXPECT_BOOLEAN_LITERAL(true);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedBooleanLiteral_False) {
    TOKENIZE_SOURCE("false"s);

    EXPECT_BOOLEAN_LITERAL(false);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedPlusOperator) {
    TOKENIZE_SOURCE("+"s);

    EXPECT_OPERATOR("+"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedMinusOperator) {
    TOKENIZE_SOURCE("-"s);

    EXPECT_OPERATOR("-"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedTimesOperator) {
    TOKENIZE_SOURCE("*"s);

    EXPECT_OPERATOR("*"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedDivideOperator) {
    TOKENIZE_SOURCE("/"s);

    EXPECT_OPERATOR("/"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedModulusOperator) {
    TOKENIZE_SOURCE("%"s);

    EXPECT_OPERATOR("%"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, ParenthesesOperators) {
    TOKENIZE_SOURCE("()"s);

    EXPECT_OPERATOR("("s);
    EXPECT_OPERATOR(")"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, NotOperators) {
    TOKENIZE_SOURCE("! !="s);

    EXPECT_OPERATOR("!"s);
    EXPECT_OPERATOR("!="s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, LessThanOperators) {
    TOKENIZE_SOURCE("< <="s);

    EXPECT_OPERATOR("<"s);
    EXPECT_OPERATOR("<="s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, GreaterThanOperators) {
    TOKENIZE_SOURCE("> >="s);

    EXPECT_OPERATOR(">"s);
    EXPECT_OPERATOR(">="s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedLogicalAndOperator) {
    TOKENIZE_SOURCE("&&"s);

    EXPECT_OPERATOR("&&"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedLogicalOrOperator) {
    TOKENIZE_SOURCE("||"s);

    EXPECT_OPERATOR("||"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, InvalidSingleEquals) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("="), std::logic_error);
}

TEST(Tokenizer_tokenize, InvalidAmpersand) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("&"), std::logic_error);
}

TEST(Tokenizer_tokenize, InvalidPipe) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("|"), std::logic_error);
}

TEST(Tokenizer_tokenize, NegativeIntegerLiteral) {
    TOKENIZE_SOURCE("-42"s);

    EXPECT_OPERATOR("-"s);
    EXPECT_INTEGER_LITERAL(42UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, WhitespaceIntegerLiteral) {
    TOKENIZE_SOURCE("   42   "s);

    EXPECT_INTEGER_LITERAL(42UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, BinaryExpression) {
    TOKENIZE_SOURCE("1 + 2"s);

    EXPECT_INTEGER_LITERAL(1UL);
    EXPECT_OPERATOR("+"s);
    EXPECT_INTEGER_LITERAL(2UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, ComplexExpression) {
    TOKENIZE_SOURCE("(1 + 2) * 3"s);

    EXPECT_OPERATOR("("s);
    EXPECT_INTEGER_LITERAL(1UL);
    EXPECT_OPERATOR("+"s);
    EXPECT_INTEGER_LITERAL(2UL);
    EXPECT_OPERATOR(")"s);
    EXPECT_OPERATOR("*"s);
    EXPECT_INTEGER_LITERAL(3UL);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, ComplexRelationalEqualityExpression) {
    TOKENIZE_SOURCE("2 < 5 && true"s);

    EXPECT_INTEGER_LITERAL(2UL);
    EXPECT_OPERATOR("<"s);
    EXPECT_INTEGER_LITERAL(5UL);
    EXPECT_OPERATOR("&&"s);
    EXPECT_BOOLEAN_LITERAL(true);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, ComplexCompactRelationalEqualityExpression) {
    TOKENIZE_SOURCE("2<5&&true"s);

    EXPECT_INTEGER_LITERAL(2UL);
    EXPECT_OPERATOR("<"s);
    EXPECT_INTEGER_LITERAL(5UL);
    EXPECT_OPERATOR("&&"s);
    EXPECT_BOOLEAN_LITERAL(true);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, MultipleBooleanLiterals) {
    TOKENIZE_SOURCE("true false true false"s);

    EXPECT_BOOLEAN_LITERAL(true);
    EXPECT_BOOLEAN_LITERAL(false);
    EXPECT_BOOLEAN_LITERAL(true);
    EXPECT_BOOLEAN_LITERAL(false);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedKeyword) {
    TOKENIZE_SOURCE("puts"s);

    EXPECT_KEYWORD("puts"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, SimpleIfStatement) {
    TOKENIZE_SOURCE("if (true) print \"It's true!\";"s);

    EXPECT_KEYWORD("if"s);
    EXPECT_OPERATOR("("s);
    EXPECT_BOOLEAN_LITERAL(true);
    EXPECT_OPERATOR(")"s);
    EXPECT_KEYWORD("print"s);
    EXPECT_STRING_LITERAL("It's true!"s);
    EXPECT_OPERATOR(";"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIdentifier) {
    TOKENIZE_SOURCE("fish"s);

    EXPECT_IDENTIFIER("fish"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIdentifier_Underscore) {
    TOKENIZE_SOURCE("_seahorse"s);

    EXPECT_IDENTIFIER("_seahorse"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIdentifier_ToggleCase) {
    TOKENIZE_SOURCE("ApPlEs2ApPlEs"s);

    EXPECT_IDENTIFIER("ApPlEs2ApPlEs"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIdentifier_OnlyUnderscores) {
    TOKENIZE_SOURCE("___"s);

    EXPECT_IDENTIFIER("___"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedIdentifier_Verbatim) {
    TOKENIZE_SOURCE("@if"s);

    EXPECT_IDENTIFIER("if"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, InvalidIdentifier_VerbatimNoCharacters) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("@"), std::logic_error);
}

TEST(Tokenizer_tokenize, InvalidIdentifier_NumericStartChar) {
    Tokenizer tokenizer;
    EXPECT_THROW(tokenizer.tokenize("2b"), std::logic_error);
}

TEST(Tokenizer_tokenize, Identifier_VerbatimNumericStartChar) {
    TOKENIZE_SOURCE("@2b"s);

    EXPECT_IDENTIFIER("2b"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, ShakespeareanQuestion) {
    TOKENIZE_SOURCE("@2b || !@2b"s);

    EXPECT_IDENTIFIER("2b"s);
    EXPECT_OPERATOR("||"s);
    EXPECT_OPERATOR("!"s);
    EXPECT_IDENTIFIER("2b"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}
