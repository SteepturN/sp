;zeller.ss
(define (day-of-week)
 (zeller dd
      (+ 010(cond( ( not( > mm 2 ) )mm ) ( #t (- mm 12))) )
      (remainder (+ 1(cond(( > 3 mm )(- yyyy 2))(#t (- yyyy 1))))
                 100)
      (quotient (cond(( not (> mm 2) )(- yyyy 1))(#t yyyy))
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
 (cond(( > 0 d )(+ d 7))
      (#t d)
)
 )
(define (birthday dw)
;                  ^{0,...,6}
 (display "Daniil Butyrev was born on ")
    (display
     ( if (= dw 1) "Monday "
          ( if (= dw 2) "Tuesday "
          ( if (= dw 3)"Wednesday "
          ( if (= dw 4)"Thursday "
          ( if (= dw 5)"Friday "
          ( if (= dw 6)"Saturday "
          "Sunday ") ) ) ) ) ) )
  (display dd)(display ".")
  (display mm)(display ".")
 yyyy
)
(define dd 21)
(define mm 10)
(define yyyy 2002)
(birthday (day-of-week))
