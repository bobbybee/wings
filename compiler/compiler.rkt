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
; emits (list ir identifier (list locals globals closures)

(define (expression-to-ir code base ctx)
  (cond
    [(list? code)
     (case (first code) [(lambda) (lambda-to-ir code base ctx)]
                        [(define) (define-to-ir code base ctx)]
                        [else (call-to-ir code base ctx)])]
    [(number? code)
     (list (list (list "=" base (list "imm" code))) (+ base 1) ctx)]
    [(member code (first ctx))
     (list (list (list "=" base (list "local" code))) (+ base 1) ctx)]
    [(member code (second ctx))
     (list (list (list "=" base (list "global" code))) (+ base 1) ctx)]))

(define (define-to-ir code base ctx)
  (list '() base (list (first ctx)
                       (hash-set (second ctx)
                                 (second code)
                                 (expression-to-ir (third code) base ctx))
                       (third ctx))))

(define (lambda-to-ir code base ctx)
  (match-let ([(list ir identifier nctx)
               (expression-to-ir (third code)
                                 base
                                 (list (append (second code) (first ctx))
                                       (third ctx)))])
      (list (list (list "=" base (list "lambda" (length (third ctx)))))
            (+ base 1)
            (list (first ctx) (cons ir (third nctx))))))

(define (call-to-ir code base ctx)
  (let* ([ir (arguments-to-ir (rest code) base '() '() ctx)]
         [nbase (second ir)])
    (list (cons (list "=" nbase (append (list "call" (first code))
                                        (reverse (fourth ir))))
                (third ir))
          (+ nbase 1)
          (last ir))))

(define (arguments-to-ir code base emission identifiers ctx)
  (if (empty? code)
    (list '() base emission identifiers ctx)
    (match-let ([(list ir newbase nctx) (expression-to-ir (first code) base ctx)])
      (arguments-to-ir
        (rest code) 
        newbase
        (append ir emission)
        (cons (- newbase 1) identifiers) nctx))))

(expression-to-ir (resolve (vector-ref (current-command-line-arguments) 0))
                  0 (list '() (hash) '()))
