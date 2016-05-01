; depends on cons, car, cdr, null?, if, empty?
; supports length, 
; first..fourth, rest
; caar...cddr,
; reverse

#lang racket

(define (_length l)
  (if (empty? l)
    0
    (length-compute l 0)))

(define (length-compute l base)
  (if (null? (cdr l))
    (+ base 1)
    (length-compute (cdr l) (+ base 1))))

(define (_first l) (car l))
(define (_rest l) (cdr l))

(define (_second l) (car (cdr l)))
(define (_third l) (car (cdr (cdr l))))
(define (_fourth l) (car (cdr (cdr (cdr l)))))

(define (_caar l) (car (car l)))
(define (_cadr l) (car (cdr l)))
(define (_cdar l) (cdr (car l)))
(define (_cddr l) (cdr (cdr l)))

(define (_reverse l)
  (reverse-compute l '()))

(define (reverse-compute remaining emitted)
  (if (empty? remaining)
    emitted
    (reverse-compute (rest remaining) (cons (first remaining) emitted))))

(_reverse (list 1 2 3 4))
