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
; emits (list ir identifier (hash base locals globals closures)

(define (expression-to-ir code ctx)
  (cond
    [(list? code)
     (case (first code) [(lambda) (lambda-to-ir code ctx)]
                        [(define) (define-to-ir code ctx)]
                        [else (call-to-ir code ctx)])]
    [(number? code)
     (list '() (list "imm" code) ctx)]
    [(member code (first ctx))
     (list '() (list "local" code) ctx)]
    [(member code (second ctx))
     (list '() (list "global" code) ctx)]))

(define (define-to-ir code ctx)
  (list '() #f (hash-set ctx
                         'globals
                         (hash-set (hash-ref ctx 'globals)
                                   (second code)
                                   (second (expression-to-ir (third code) ctx))))))

(define (lambda-to-ir code base ctx)
  (match-let ([(list ir identifier nctx)
               (expression-to-ir (third code)
                                 (hash-set ctx 'locals (append (second code)
                                                               (hash-ref ctx 'locals))))])
             (list '()
                   ("lambda" (length (hash-ref nctx 'lambdas))) 
                   (hash-set ctx 'globals (cons ir (hash-ref ctx 'globals))))))

(define (call-to-ir code ctx)
  (let* ([ir (arguments-to-ir (rest code) '() '() ctx)])
    (list (cons (list "=" 
                      (hash-ref ctx 'base)
                      (append (list "call" (first code) (reverse (third ir)))
                              (second ir)))
                (hash-set ctx 'base (+ (hash-ref ctx 'base) 1))))))

(define (arguments-to-ir code emission identifiers ctx)
  (if (empty? code)
    (list '() emission identifiers ctx)
    (match-let ([(list ir nctx) (expression-to-ir (first code) ctx)])
      (arguments-to-ir
        (rest code) 
        (append ir emission)
        (cons (- (hash-ref nctx 'base) 1) identifiers)
        nctx))))

(expression-to-ir (resolve (vector-ref (current-command-line-arguments) 0))
                  (hash 'locals '() 'globals (hash) 'base 0 'lambdas '()))
