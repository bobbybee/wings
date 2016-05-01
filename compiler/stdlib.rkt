; WINGS Operating System
; Copyright (C) 2016 Alyssa Rosenzweig
; 
; This file is part of WINGS.
; 
; WINGS is free software: you can redistribute it and/or modify
; it under the terms of the GNU Affero General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; WINGS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with WINGS.  If not, see <http://www.gnu.org/licenses/>.

; depends on cons, car, cdr, null?, if, empty?
; supports length, 
; first..fourth, rest
; caar...cddr,
; reverse
; append

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

(define (_append head tail)
  (append-compute (reverse head) tail))

(define (append-compute head tail)
  (if (empty? head)
    tail
    (append-compute (rest head) (cons (first head) tail))))

(define (_map f l)
  (reverse (map-compute f l '())))

(define (map-compute f l emitted)
  (if (empty? l)
    emitted
    (map-compute f (rest l) (cons (f (first l)) emitted))))

; hash maps are not actually implemented yet
; for now, use a list of key-value pairs.
; this is O(N) for all operations, which is bad.
; but it will work.

(define (hash-ref h k)
  (if (eq? (car (first h)) k)
    (cdr (first h))
    (hash-ref (rest h) k)))

(define (hash-set h k v)
  (if (empty? h)
    (list (cons k v))
    (if (eq? (car (first h)) k)
      (cons (cons k v) (rest h))
      (cons (first h) (hash-set (rest h) k v)))))

; S-expression reader
; still but a subset, unfortunately.

(define (_read str)
  (first (read-compute str 0)))

(define (read-compute str base)
  (case (string-ref str base)
    [(#\() (read-list str (+ base 1) #\) '())]
    [(#\[) (read-list str (+ base 1) #\] '())]
    [(#\") (read-sstring str (+ base 1) '())]
    [(#\') (read-quote str (+ base 1))]
    [(#\space #\tab #\newline) (read-compute str (+ base 1))]
    [(#\;) (read-comment str (+ base 1))]
    [else (read-symbol str base)]))

(define (read-list str base terminator emitted)
  (if (eq? (string-ref str base) terminator)
    (list (reverse emitted) (+ base 1))
    (match-let ([(list element nbase) (read-compute str base)])
      (read-list str nbase terminator (cons element emitted)))))

(define (read-symbol str base)
  (match-let* ([(list element nbase) (read-identifier str base '())]
               [relement (reverse element)])
    (cond
      [(andmap char-numeric? element)
       (list (string->number (list->string relement)) nbase)]
      [(eq? (first relement) #\#)
       (list (read-pound relement) nbase)]
      [else
       (list (string->symbol (list->string relement)) nbase)])))

(define (read-identifier str base emitted)
  (if (<= (string-length str) base)
    (list emitted base)
    (let ([c (string-ref str base)])
      (if (not (or
                 (eq? c #\))
                 (eq? c #\]) 
                 (char-whitespace? c)))
        (read-identifier str (+ base 1) (cons c emitted))
        (list emitted base)))))

(define (read-pound chars)
  (case (second chars)
    [(#\t #\T) #t]
    [(#\f #\F) #f]))

(define (read-sstring str base emitted)
  (if (eq? (string-ref str base) #\")
    (list (list->string (reverse emitted)) (+ base 1))
    (read-sstring str (+ base 1) (cons (string-ref str base) emitted))))

(define (read-quote str base)
  (let ([quoted (read-compute str base)])
    (list (list 'quote (first quoted)) (second quoted))))

(define (read-comment str base)
  (if (eq? (string-ref str base) #\newline)
    (read-compute str (+ base 1))
    (read-comment str (+ base 1))))

(let ([str (port->string (current-input-port))])
  (pretty-print (_read str))
  (pretty-print (read (open-input-string str))))
