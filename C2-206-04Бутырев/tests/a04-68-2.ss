   ;; HPRED -> PDPAR )
(define (proc a b)( cond ( (predicate? 1 2 #t 4 #f a b ) a )(#t b) ) )
(define (predicate? a b c d e f? g)( = a b ))
