; depends on cons, car, cdr, null?, if, empty?
; supports length

#lang racket

(define (_length l)
  (if (empty? l)
    0
    (length-compute l 0)))

(define (length-compute l base)
  (if (null? (cdr l))
    (+ base 1)
    (length-compute (cdr l) (+ base 1))))

