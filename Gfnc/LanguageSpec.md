

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
       | IdentifierOrKeyword
       | StringLiteralToken
       | OperatorToken

IntegerLiteralToken := DecimalDigit+
DecimalDigit := '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

IdentifierOrKeyword := (IdentifierStartChar | '@' IdentifierChar) IdentifierChar*
IdentifierStartChar := (Any character between 'a' and 'z', or between 'A' and 'Z', or '_')
IdentifierChar := (Any IdentifierStartChar, or any character between '0' and '9')

StringLiteralToken := '"' StringLiteralCharacter* '"'
StringLiteralCharacter := (Any character except '"', '\', '\r', or '\n')
                        | StringLiteralEscapeSequence
StringLiteralEscapeSequence := '\' ('"' | '\' | '\r' | '\n' | '\t')

OperatorToken := '+' | '-' | '*' | '/' | '%' | '(' | ')' | ';'
               | '!' | '!=' | '==' | '&&' | '||' | '<' | '>' | '<=' | '>='
```

## Parsing Exceptions

### `IntegerLiteralToken`

An IntegerLiteralToken is ill-formed if it is more than one character long and starts with a '0'.
A few examples:

- "0" is parsed as the IntegerLiteralToken (0)
- "1" is parsed as the IntegerLiteralToken (1)
- "01" results in a compilation error, rather than being parsed as the IntegerLiteralToken (1)
- "10" is parsed as the IntegerLiteralToken (10)

Additionally, an IntegerLiteralToken is ill-formed if the next character after the integer literal
is a character that matches the "IdentifierStartChar" production. For example, "2b" is not parsed
as an integer literal token followed by an identifier token; instead, it is reported as a compilation
error.

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

### `IdentifierOrKeyword`

An IdentifierOrKeyword is parsed as a KeywordToken if it matches one
of the following keywords. Otherwise, it is parsed as an IdentifierToken.

```
if else puts print true false
```

Some keywords are parsed as a subclass of KeywordToken. Specifically:

- `true` and `false` are parsed as a BooleanLiteralToken

An IdentifierOrKeyword is always interpreted as an identifier if it starts with '@',
even if it would otherwise be considered a keyword. The '@' symbol is not a part of
the identifier.

# Syntax:

This context-free grammar can be used to describe a program that is syntactically valid.
Further steps are necessary to ensure that the program can actually be compiled, but at the very least
if a compilation unit can be correctly tokenized and parsed unambiguously using the
"CompilationUnit" rule of this syntax then the compiler can move on to the type-checking phase.

In this CFG, the terminal symbols are the tokens outputted by the "tokenizer" phase of compilation.

```cfg
CompilationUnit := Statement* (EndOfFileToken)

Statement := PrintStatement
           | IfStatement
           | ExpressionStatement

PrintStatement := ('print' | 'puts') Expression ';'

IfStatement := 'if' '(' Expression ')' Statement ['else' Statement]

ExpressionStatement := Expression ';'

Expression := ConditionalOrExpression

ConditionalOrExpression := [ConditionalOrExpression '||'] ConditionalAndExpression

ConditionalAndExpression := [ConditionalAndExpression '&&'] EqualityExpression

EqualityExpression := [EqualityExpression EqualityOp] RelationalExpression
EqualityOp := '==' | '!='

RelationalExpression := [RelationalExpression RelationalOp] AdditiveExpression
RelationalOp := '<' | '>' | '<=' | '>='

AdditiveExpression := [AdditiveExpression AdditiveOp] MultiplicativeExpression
AdditiveOp := '+' | '-'

MultiplicativeExpression := [MultiplicativeExpression MultiplicativeOp] UnaryExpression
MultiplicativeOp := '*' | '/' | '%'

UnaryExpression := UnaryOp UnaryExpression
                 | PrimaryExpression
UnaryOp := '+' | '-' | '!'

PrimaryExpression := (IntegerLiteralToken)
                   | (BooleanLiteralToken)
                   | (StringLiteralToken)
                   | '(' Expression ')'
```
