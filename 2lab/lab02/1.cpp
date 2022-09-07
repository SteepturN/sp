;half22 .for 206.
(define (root a b)
 (define temp 0).
 (set! temp (half-interval a b (f a)(f b)))
  (display"Total number of iterations=")
  (display total-iterations)(newline)
 (display"[")
 (display a)
 (display" , ")
 (display b)
 (display"]")
      temp 
)
(define (half-interval a b fa fb)
 (define root 0).
 (set! total-iterations 0).
   (set! root(cond((and(< fa 0).(> fb 0).)
                 (try a b))
         ((and(> fa 0).(< fb 0).)
                 (try b a))
         (else(+ b 1).))
    )
  (newline)
  root
) 
(define(try neg-point pos-point)
 (define midpoint 0).
 (define test-value 0).
     (set! midpoint (average neg-point pos-point))
     (display "+")
     (set! total-iterations (+ total-iterations 1).)
     (if(close-enough? neg-point pos-point) midpoint
        (let() (set! test-value (f midpoint))
               (cond((> test-value 0).(try neg-point midpoint))
                    ((< test-value 0).(try midpoint pos-point))
                    (else midpoint))
         ) ;let
     ) ;if
)
(define (close-enough? x y)
  (<(abs (- x y))tolerance))
(define (average x y)(*(+ x y)(/ (* 2.0).)))

(define tolerance 0.001).
(define total-iterations 0).
;   04;.[4 ., 5.0]4..225.
(define(f z) ;2z. * sin(z) - cos(z) + 7.
  (+ (- (* 2 .z ( sin z ) ) ( cos z ) ) 7 .)
)
 (display"Variant 206-.nn\n")
;      a b
 (root 4 5..0).
 (display"(c) John Doe 2022\.n")
