# lisp

A Lisp interperter with reference counting garbage collection.

Implemented in pure SysY.

## Usage

Put your Lisp program in file `input.lisp`, and run:

```sh
./list < input.lisp
```

For example, after interpreting the following program:

```lisp
(define null?
  (lambda (l) (eq? l '())))

(define map
  (lambda (f l)
    (cond ((null? l) '())
          ('t (cons (f (car l)) (map f (cdr l)))))))

(define fib
  (lambda (n)
    (cond ((< n 2) 1)
          ('t (+ (fib (- n 1)) (fib (- n 2)))))))

(define range
  (lambda (a b)
    (cond ((< a b) (cons a (range (+ a 1) b)))
          ('t '()))))

(map fib (range 0 20))
```

You will get:

```
(1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765)
```

## References

* [(How to Write a (Lisp) Interpreter (in Python))](http://norvig.com/lispy.html).
* [The Roots of Lisp](http://languagelog.ldc.upenn.edu/myl/llog/jmc.pdf).
* [The Racket Reference](https://docs.racket-lang.org/reference/index.html).
