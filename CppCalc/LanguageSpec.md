

# Tokenizer:

Before the compiler attempts to interpret a compilation unit in any meaningful way,
it first attempts to group characters into more representative units called "tokens."

In this context-free grammar, the terminal symbols are the characters in the compilation unit. (Source file.)
The one exception to this rule is the "(EndOfFile)" terminal symbol, which is a virtual "character" representing
the end of the compilation unit, when there are no further characters.

Except where explicitly stated, all rules are greedy. That is, the two characters "12" would be interpreted
as a single IntegerLiteralToken (12) rather than two separate tokens (1 followed by 2).

There are further tokenization rules that cannot be adequately expressed in this context-free grammar.
Those are enumerated after the CFG definition.

```
CompilationUnit := (WhiteSpace* Token)* WhiteSpace* (EndOfFile)

WhiteSpace := ' ' | '\t' | '\r' | '\n'

Token := IntegerLiteralToken
       | OperatorToken

IntegerLiteralToken := DecimalDigit+
DecimalDigit := '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

OperatorToken := '+' | '-' | '*' | '/' | '%' | '(' | ')'
```

## Parsing Exceptions

### `IntegerLiteralToken`

An IntegerLiteralToken is ill-formed if it is more than one character long and starts with a '0'.
A few examples:

- "0" is parsed as the IntegerLiteralToken (0)
- "1" is parsed as the IntegerLiteralToken (1)
- "01" results in a compilation error, rather than being parsed as the IntegerLiteralToken (1)
- "10" is parsed as the IntegerLiteralToken (10)

The maximum value that can be represented by an IntegerLiteralToken is 2147483647.
An IntegerLiteralToken with a larger value is not permitted unless all of the following conditions are true:

1. The integer literal value is 2147483648
2. The integer literal is immediately preceded by an OperatorToken (-)
3. There are no characters between the '-' character of the OperatorToken and
   the first character in the IntegerLiteralToken
4. The OperatorToken and IntegerLiteralToken would be interpreted by the parser as an UnaryExpressionSyntax.

A few examples:

- "2147483647" is valid.
- "2147483648" is not valid. (Greater than the max value representable by an int32)
- "-2147483648" is valid.
- "- 2147483648" is not valid.
- "-(2147483648)" is not valid.
- "0-2147483648" is not valid.
  (The '-' character would be consumed by an AdditiveExpressionSyntax,
  rather than being part of an UnaryExpressionSyntax.)

An implementation is required to fail compilation if any of the invalid cases above are parsed,
even if the expression could potentially be interpreted in a sensible way.
However, an implementation can defer the error to a later stage in the compiler if necessary,
rather than failing compilation speculatively.

# Syntax:

This context-free grammar can be used to describe a program that is syntactically valid.
Further steps are necessary to ensure that the program can actually be compiled, but at the very least
if a compilation unit can be correctly tokenized and parsed unambiguously using the
"CompilationUnitExpressionSyntax" rule of this syntax then the compiler can move on to the type-checking phase.

In this CFG, the terminal symbols are the tokens outputted by the "tokenizer" phase of compilation.

Note that although an empty file can be correctly tokenized, there is no way to parse a
CompilationUnitExpressionSyntax from the single (EndOfFile) token produced by the tokenizer.
Therefore, an empty source string is not a valid compilation unit.

```cfg
CompilationUnitExpressionSyntax := ExpressionSyntax (EndOfFileToken)

ExpressionSyntax := AdditiveExpressionSyntax

AdditiveExpressionSyntax := [AdditiveExpressionSyntax AdditiveOp] MultiplicativeExpressionSyntax
AdditiveOp := '+' | '-'

MultiplicativeExpressionSyntax := [MultiplicativeExpressionSyntax MultiplicativeOp] UnaryExpressionSyntax
MultiplicativeOp := '*' | '/' | '%'

UnaryExpressionSyntax := UnaryOp UnaryExpressionSyntax
                       | PrimaryExpressionSyntax
UnaryOp := '+' | '-'

PrimaryExpressionSyntax := (IntegerLiteralToken)
                         | '(' ExpressionSyntax ')'
```
