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

TEST(Tokenizer_tokenize, IsolatedOperator) {
    TOKENIZE_SOURCE("*"s);

    EXPECT_OPERATOR("*"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
}

TEST(Tokenizer_tokenize, IsolatedModulusOperator) {
    TOKENIZE_SOURCE("%"s);

    EXPECT_OPERATOR("%"s);

    EXPECT_END_OF_FILE();
    EXPECT_NO_MORE_TOKENS();
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
