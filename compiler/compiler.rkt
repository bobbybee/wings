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

(define (wings-to-ir code base)
  (foldl (lambda (element emission)
           (list
             (append (first element) (first emission))
             (+ (second emission) (second element))))
         (map (lambda (arg) (argument-ir arg base)) (rest code))
         (list '() base)))

(define (argument-ir code sbase)
  (if (list? code)
      (foldl (lambda (element emission)
               (match-let
                 ([(list code base) (wings-to-ir code (second emission))])
                 (list 
                   (append code (first emission))
                   base)))
             (list '() sbase)
             code)
      (wings-to-ir code sbase)))
     
(wings-to-ir (resolve (vector-ref (current-command-line-arguments) 0)) 0)
