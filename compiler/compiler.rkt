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
    [(list? code) (let ([ir (arguments-to-ir (rest code) base '() '())])
                    (list (third ir) (second ir)))]
    [(number? code) (list (list (list "=" base code)) (+ base 1))]))

(define (arguments-to-ir code base emission identifiers)
  (if (empty? code)
    (list '() base emission identifiers)
    (match-let ([(list ir newbase) (expression-to-ir (first code) base)])
      (arguments-to-ir
        (rest code) 
        newbase
        (append ir emission)
        (cons newbase identifiers)))))

(expression-to-ir (resolve (vector-ref (current-command-line-arguments) 0)) 0)
