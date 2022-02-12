# mandelbrot

A mandelbrot plotting program implemented in extended SysY.

## Requirements

Your SysY compiler must support the following "function declaration" syntax:

```ebnf
FuncDef ::= FuncType IDENT "(" [FuncFParams] ")" Block;
FuncDecl ::= FuncType IDENT "(" [FuncFParams] ")";
```

To get an executable, you should link the SysY compiler-generated file with `libsysy` and `fp-math.c`.

## Usage

```sh
echo 1049275610 1049280643 999820068 1000185140 500 1024 | ./mandelbrot > pic.ppm
```

The generated mandelbrot set image looks like:

![Mandelbrot](mandelbrot.png)
