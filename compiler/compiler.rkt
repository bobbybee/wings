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

#lang racket

(require racket)

; in the future, this is a lower-level call to resolve a URL
; but for now, this is just a thin wrapper around the Racket API

(define (recursive-resolve handle data)
  (let ([datum (read handle)])
    (if (list? datum)
      (recursive-resolve handle (cons datum data))
      (reverse data))))

(define (resolve url)
  (let* ([handle (open-input-file url)]
         [content (recursive-resolve handle '())])
    (close-input-port handle)
    content))

; compile s-expressions to IR
; emits (list ir identifier (hash base locals globals closures)

(define (expression-to-ir code ctx)
  (cond
    [(list? code)
     (case (first code) [(lambda) (lambda-to-ir code ctx)]
                        [(define) (define-to-ir code ctx)]
                        [(quote) (quote-to-ir (second code) ctx)]
                        [(let) (let-to-ir code '() ctx)]
                        [else (call-to-ir code ctx)])]
    [(number? code)
     (list '() (list "imm" code) ctx)]
    [(string? code)
     (list '() (list "immstr" code) ctx)]
    [(hash-has-key? (hash-ref ctx 'locals) code)
     (list '() (list "local" code) ctx)]
    [(hash-has-key? (hash-ref ctx 'globals) code)
     (list '() (list "global" code) ctx)]))

(define (define-to-ir code ctx)
  (if (list? (second code))
    (define-to-ir 
      (list 'define
            (first (second code))
            (append (list 'lambda (rest (second code))) (cddr code)))
      ctx)
    (match-let ([(list ir identifier nctx) (expression-to-ir (third code) ctx)])
      (list '() #f (hash-set nctx 'globals (hash-set (hash-ref nctx 'globals)
                                                     (second code)
                                                     identifier))))))

(define (lambda-to-ir code ctx)
  (match-let ([(list ir identifier nctx)
               (expression-to-ir (third code)
                                 (hash-set ctx 'locals (append (second code)
                                                               (hash-ref ctx 'locals))))])
             (list '()
                   (list "lambda" (length (hash-ref ctx 'lambdas))) 
                   (hash-set nctx 'lambdas (cons ir (hash-ref nctx 'lambdas))))))

; May be unstable -- rewrite later
(define (quote-to-ir code ctx)
  (cond [(list? code) (expression-to-ir (cons 'list code) ctx)]))

(define (let-to-ir code ir ctx)
  (if (= (length (second code)) 0)
    (expression-to-ir (third code) ctx)
    (let ([value (expression-to-ir (second (first (second code))) ctx)])
      (let-to-ir (list "let" (rest (second code)) (third code))
                 (append (first value) ir)
                 (hash-set (third value)
                           'locals
                           (hash-set (hash-ref (third value) 'locals)
                                     (first (first (second code)))
                                     (second value)))))))

(define (call-to-ir code ctx)
  (match-let ([(list ir emission identifiers nctx)
               (arguments-to-ir (rest code) '() '() ctx)])
    (list (cons (list "=" 
                      (hash-ref nctx 'base)
                      (append (list "call" (first code)) (reverse identifiers)))
                emission)
          (hash-set nctx 'base (+ (hash-ref nctx 'base) 1)))))

(define (arguments-to-ir code emission identifiers ctx)
  (if (empty? code)
    (list '() emission identifiers ctx)
    (match-let ([(list ir id nctx) (expression-to-ir (first code) ctx)])
      (arguments-to-ir
        (rest code) 
        (append ir emission)
        (cons id identifiers)
        nctx))))

(define (program-to-ir sexpr ir globals lambdas)
    (if (empty? sexpr)
      (list (reverse ir))
      (let ([expression (expression-to-ir (first sexpr) (hash 'locals (hash)
                                                              'globals globals
                                                              'base 0
                                                              'lambdas lambdas))])
        (program-to-ir (rest sexpr)
                       (cons (first expression) ir) 
                       (hash-ref (second expression) 'globals)
                       (hash-ref (second expression) 'lambdas)))))

(program-to-ir (resolve (vector-ref (current-command-line-arguments) 0))
               '()
               (hash)
               '())
