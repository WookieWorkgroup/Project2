# Project2

Done
Update the inputinspect and it can inspect most of errors now.
(The index position for the error report is the position after removed spaces.)

Errors
1) 4++ still report an error because the requirements for our project told us that the ++ is prefix increment, if we need make it can work with post increment, I'll fix it.
2)1+2*3 cannot calculator corretly.
3)Divide by zero not caught(now Josh's detector can report like 1/0, but can't detect devide 0 like this 1/(6-6), so I think it should be detected when it do the divide calculate but not when the expression input.
