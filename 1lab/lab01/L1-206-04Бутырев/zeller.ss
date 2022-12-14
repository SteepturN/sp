;zeller.ss
(define (day-of-week)
 (zeller dd
      (+ 010(if(<= mm 2)mm (- mm 12)))
      (remainder (+ 1(cond((< mm 3)(- yyyy 2))(#t (- yyyy 1))))
                 100)
      (quotient (cond((>= 2 mm)(- yyyy 1))(else yyyy))
                100)
 )
)
(define (zeller d m y c)
 (neg-to-pos (remainder (+ d y
                          (quotient (-(* 26 m)2) 10)
                          (quotient y 4)
                          (quotient c 4)
                          (* 2(- c))
                       )
            7)
 )
)
(define (neg-to-pos d)
 (cond((< d 0)(+ d 7))
      (#t d)
 )
)
(define (birthday dw)
;                  ^{0,...,6}
 (display "Daniil Butyrev was born on ")
    (display
     (cond((= dw 1)"Monday ")
          ((= dw 2)"Tuesday ")
          ((= dw 3)"Wednesday ")
          ((= dw 4)"Thursday ")
          ((= dw 5)"Friday ")
          ((= dw 6)"Saturday ")
          (else "Sunday ") ))
  (display dd)(display ".")
  (display mm)(display ".")
 yyyy
)
(define dd 21)
(define mm 10)
(define yyyy 2002)
(birthday (day-of-week))
