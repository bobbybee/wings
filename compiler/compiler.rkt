; WINGS compiler
; currently implemented using the shared subset of WINGS and Racket,
; to enable sane bootstrapping
; Copyright (C) Alyssa Rosenzweig 2016
; ALL RIGHTS RESERVED

#lang racket

(require racket)

; in the future, this is a lower-level call to resolve a URL
; but for now, this is just a thin wrapper around the Racket API

(define (resolve url)
  (let* ([handle (open-input-file url)]
         [content (read handle)])
    (close-input-port handle)
    content))

; compile s-expressions to IR
; emits (list ir identifier)

(define (expression-to-ir code base)
  (cond
    [(list? code) (case (first code) [("lambda") (lambda-to-ir code base)]
                                     [else (call-to-ir code base)])]
    [(number? code) (list (list (list "=" base code)) (+ base 1))]))

(define (lambda-to-ir code base)
  (display "Lambda: ")
  (display code)
  (display "\n")
  (list '() base))

(define (call-to-ir code base)
  (let* ([ir (arguments-to-ir (rest code) base '() '())]
         [nbase (second ir)])
    (list (cons (append (list "call" (first code))
                        (reverse (last ir)))
                (third ir))
          (+ nbase 1))))

(define (arguments-to-ir code base emission identifiers)
  (if (empty? code)
    (list '() base emission identifiers)
    (match-let ([(list ir newbase) (expression-to-ir (first code) base)])
      (arguments-to-ir
        (rest code) 
        newbase
        (append ir emission)
        (cons (- newbase 1) identifiers)))))

(expression-to-ir (resolve (vector-ref (current-command-line-arguments) 0)) 0)
