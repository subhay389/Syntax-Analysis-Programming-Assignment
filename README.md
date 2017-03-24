github url: https://github.com/subhay389/Syntax-Analysis-Programming-Assignment

to compile use: gcc front.c -o parser

to run the file please type ./parser <filename>

PS: in my case the filename is front.in so just run: ./parser front.in

if any confusion or problem in running the code,  please email at subhay.manandhar@bison.howard.edu

some restrictions:
do not put space after expression 
do not leave a line with only a space 

commits:

1.
https://github.com/subhay389/Syntax-Analysis-Programming-Assignment/commit/a5a9cc20110135f7fe47ade5a1de9ee6376f5028
March 23 2017, 2:30 AM
Finished copying all the Codes from the book

2.
https://github.com/subhay389/Syntax-Analysis-Programming-Assignment/commit/93b116df8ece1305e604b11c10f40b36641482ac
March 23 2017, 12:21 PM
Handled the case where the front.in file may contain more than 1 expression.

3.
https://github.com/subhay389/Syntax-Analysis-Programming-Assignment/commit/cfb6266d59eb10a545e22552fd42ca53eca9d7ca
March 23 2017, 12:44 PM
Taking input for the name of the file from the command line

4.
https://github.com/subhay389/Syntax-Analysis-Programming-Assignment/commit/5574180d9c908f3c54b6b4e8cf17a99196983a41
March 23 2017, 6:17 PM
Printing the error lexeme as well as the expression until error occurred

5.
https://github.com/subhay389/Syntax-Analysis-Programming-Assignment/commit/e684bf76d76a739ad3e08161d71888f3116c22d6
March 23 2017, 3:02 PM
Complete error function which handles the case where the error occurs in the last lexeme of the expression. (Printing the actual error lexeme instead of EOF)
