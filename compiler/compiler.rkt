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
; emits (list ir identifier (list variables lambdas)

(define (expression-to-ir code base ctx)
  (display code)
  (display (first ctx))
  (display "\n")

  (cond
    [(list? code) (case (first code) [(lambda) (lambda-to-ir code base ctx)]
                                     [else (call-to-ir code base ctx)])]
    [(number? code) (list (list (list "=" base code)) (+ base 1) ctx)]
    [(member code (first ctx)) code]))

(define (lambda-to-ir code base ctx)
  (display "Lambda: ")
  (display code)
  (display "\n")

  (list '()
        base
        (list (first ctx)
              (cons (expression-to-ir (third code)
                                      base
                                      (list (append (second code) (first ctx))
                                            (second ctx))) (second ctx)))))

(define (call-to-ir code base ctx)
  (let* ([ir (arguments-to-ir (rest code) base '() '() ctx)]
         [nbase (second ir)])
    (list (cons (append (list "call" (first code))
                        (reverse (last ir)))
                (third ir))
          (+ nbase 1)
          ctx)))

(define (arguments-to-ir code base emission identifiers ctx)
  (if (empty? code)
    (list '() base emission identifiers)
    (match-let ([(list ir newbase nctx) (expression-to-ir (first code) base ctx)])
      (arguments-to-ir
        (rest code) 
        newbase
        (append ir emission)
        (cons (- newbase 1) identifiers) nctx))))

(expression-to-ir (resolve (vector-ref (current-command-line-arguments) 0))
                  0 (list '() '()))
