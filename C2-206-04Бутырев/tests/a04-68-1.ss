   ;; HPRED -> PDPAR )
(define (proc a b)( cond ( (predicate? 1 2 3 #t ) a )(#t b) ) )
(define (predicate? a b)( = a b ))
