
;; ( let() 1 2 3 +4.12e-1 )
;; ( f 5 )
;; ( cond( abc? 5 )( #f 6 ) )


;; AREX
( * a )
( - a )
( + a )
( / a )
( + a b )
( - a b )
( / a b )
( * a b )
( + a b c d )
( - a b c d )
( * a b c d )
( / a b c d )

(- (+ a b))
(/ (* a b))
(/(/ a))


;;STR
;;( if abc? "aaaaaa" ( if abc? "aaaaaaa" "no" ) )

;;BOOL
;; ( cond( #f 1 )( abc? 3 )( ( > a b ) 4 )( ( not #t ) 2 )( ( or a? b? c? ) 5 )( ( or d? ) 6 ) )

;;CPRED
;; ( cond( ( a? 1 2 ) 2 ) ( ( a? ) 4 ) )

;; DISPSET
;; ( display 1 )
;; ( newline )
;; ( display #t )
;; ( newline )
;; ( display "abc" )
;; ( newline )


;; PRED
;; ( define ( abc? a b? c? )#t )
;; ( define ( abc? a? )( or a? b? ) )


;; SET
;; ( set! a 5 )


;; PROC
;; ( define a 4 )
;; ( define ( a a b c )
;;   ( define b 4 )
;;   ( define c 4 )
;;   ( + b c )
;; )
;; ( define b 7 )
;; a
