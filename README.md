# Project2

Done
1) Professor said postfix not needed
2) 1+3 > 2 works now according to the project spec (thanks Chen for catching the error)
(So the + and the > have the same priority?)

Errors
1) 2*-3 throws error in input inspect, (treats negative as subtraction) but it will work in infix_eval if allowed through
(Fixed it, but you must input the 2*(-3). Because the 2--2 and the 2---2 will confused us)
(But now the infix_Eval will report an error will 2*(-3))
2) 1>(3-2)&&2 fails in input inspect
(Fixed)

