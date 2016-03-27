# Project2

Done
1) Update the inputinspect and it can inspect most of errors now.
(The index position for the error report is the position after removed spaces.)
2) 4++ still report an error because the requirements for our project told us that the ++ is prefix increment, if we need make it can work with post increment, I'll fix it. (assuming we dont have to do this)
3)1+2*3 cannot calculator corretly. (fixed, had one too many pops, or sodas)
4)Divide by zero not caught(now Josh's detector can report like 1/0, but can't detect devide 0 like this 1/(6-6), so I think it should be detected when it do the divide calculate but not when the expression input. (fixed, parens and ^ were calling solve top too early)

Errors
1) Comparison operator has higher precedence than addition (but project specs say should be lower). 
2) 2+2∧2×3 is 66 (error in precedence)
