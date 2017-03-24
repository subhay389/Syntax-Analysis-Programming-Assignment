#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char previouslexeme [100];
char errorstring[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();
char * expression = NULL;
size_t len = 0;
ssize_t read;
int current;
int temp;

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void factor();
void term();
void error();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) {
  /* Open the input data file and process its contents */
  // If the arguments in command prompt is invalid
  if (argc == 2){
    if ((in_fp = fopen(argv[1], "r")) == NULL)
      printf("ERROR - cannot open front.in \n");
    else {
      while ((read = getline(&expression, &len, in_fp)) != -1) {
        printf("\nRetrieved line of length %zu :\n", read-1);
        //storing the line retrived from the file in variable expression
        if(read-1 != 0){
          printf("Analysis for the expression: %s", expression);
          //setting the string errorstring to null
          memset(errorstring,0,sizeof(errorstring));
          current = 0;
          getChar();
          if (expression != NULL){
            do {
              lex();
              expr();
            } while (nextToken != EOF);
          }
        }else{
          printf("This was a blank line\n");
        }
      }
      // getChar();
      // do {
      //   lex();
      //   expr();
      // } while (nextToken != EOF);
    }
  }
  else{
    printf("error in reading filename\n");
  }
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
  switch (ch) {

    case '(':
      addChar();
      nextToken = LEFT_PAREN;
      break;

    case ')':
      addChar();
      nextToken = RIGHT_PAREN;
      break;

    case '+':
      addChar();
      nextToken = ADD_OP;
      break;

    case '-':
      addChar();
      nextToken = SUB_OP;
      break;

    case '*':
      addChar();
      nextToken = MULT_OP;
      break;

    case '/':
      addChar();
      nextToken = DIV_OP;
      break;

    default:
      addChar();
      nextToken = EOF;
      break;
    }
    return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  }
  else
  printf("Error - lexeme is too long \n");
}


/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getCharOld() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
    charClass = LETTER;
    else if (isdigit(
      nextChar))
      charClass = DIGIT;
      else charClass = UNKNOWN;
    }
    else
    charClass = EOF;
}


/******************************************************/
//modified get char
//this function gets char from the string expression which is storing the current line read from the file
void getChar() {
  if (expression[current] != '\n' && expression[current] != EOF) {
    nextChar = expression[current];
    errorstring[current] = nextChar;
    temp = current;
    current++;

    if (isalpha(nextChar))
    charClass = LETTER;
    else if (isdigit(
      nextChar))
      charClass = DIGIT;
      else charClass = UNKNOWN;
    }
    else
    charClass = EOF;
}




/*****************************************************/
/* getNonBlank - a function to call getChar until it
returns a non-
whitespace
character */
void getNonBlank() {
  while (isspace(nextChar))
  getChar();
}


/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
  lexLen = 0;
  getNonBlank();
  strcpy(previouslexeme, lexeme);
  switch (charClass) {

  /* Parse identifiers */
    case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT) {
      addChar();
      getChar();
    }
    nextToken = IDENT;
    break;

    /* Parse integer literals */
    case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT) {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;
    /* Parentheses and operators */
    case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;
    /* EOF */
    case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  } /* End of switch */
  printf("Next token is: %d, Next lexeme is %s\n",
  nextToken, lexeme);
  return nextToken;
} /* End of function lex */




/* expr
Parses strings in the language generated by the rule:
<expr> -> <term> {(+ | -) <term>}
*/
void expr() {
  printf("  Enter <expr>\n");
  /* Parse the first term */
  term();
  /* As long as the next token is + or -, get
  the next token and parse the next term */
  while (nextToken == ADD_OP || nextToken == SUB_OP) {
    lex();
    term();
  }
  printf("  Exit <expr>\n");
} /* End of function expr */

/* term
Parses strings in the language generated by the rule:
<term> -> <factor> {(* | /) <factor>)
*/
void term() {
  printf("  Enter <term>\n");
  /* Parse the first factor */
  factor();
  /* As long as the next token is * or /, get the
  next token and parse the next factor */
  while (nextToken == MULT_OP || nextToken == DIV_OP) {
    lex();
    factor();
  }
  printf("  Exit <term>\n");
} /* End of function term */



/* factor
Parses strings in the language generated by the rule:
<factor> -> id | int_constant | ( <expr )
*/
void factor() {
  printf("  Enter <factor>\n");
  /* Determine which RHS */
  if (nextToken == IDENT || nextToken == INT_LIT)
  /* Get the next token */
  lex();
  /* If the RHS is ( <expr>), call lex to pass over the
  left parenthesis, call expr, and check for the right
  parenthesis */
  else {
    if (nextToken == LEFT_PAREN) {
      lex();
      expr();
      if (nextToken == RIGHT_PAREN)
      lex();
      else
      error();
    } /* End of if (nextToken == ... */
      /* It was not an id, an integer literal, or a left
      parenthesis */
      else
      error();
    } /* End of else */
    printf("  Exit <factor>\n");;
} /* End of function factor */


void error(){
  //if the error is in the end then printing the lexeme in which there is error intead of printing EOF
  if (strcmp(lexeme, "EOF") == 0){
    printf("    Error function called\n");
    printf("    Error expression %s\n", errorstring);
    //printf("Error in: %s\n", lexeme);
    //printf("Error in: %c\n", errorstring[temp]);
    printf("    Error in: %s\n", previouslexeme);
  }
  else{
    printf("    Error function called\n");
    printf("    Error expression %s\n", errorstring);
    printf("    Error in: %s\n", lexeme);
  }
}
