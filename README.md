# cLDtk
C99 loader for the LDtk map editor

built using parson: https://github.com/kgabis/parson

LDtk map editor: https://ldtk.io/


How to compile for GCC

```sh
gcc -c cLDtk.c parson.c -std=c99
```
```sh
ar rvs libcLDtk.a cLDtk.o parson.o
```
```sh
gcc example.c -o example.exe libcLDtk.a -std=c99
```
How to compile for DJGPP(MS-DOS)

```sh
gcc -c cLDtk.c parson.c -std=c99
```
```sh
ar rvs libcLDtk.a cLDtk.o parson.o
```
```sh
gcc example.c -o example.exe libcLDtk.a -std=c99 -lalleg
```

The person I forked it from said to compile it into a static library but I don't see any need to. You can it you want i guess.
