Tiny RayTracer
==============

Tiny RayTracer aim to be easy to hack, portable, modular and fast.

Compiling
--------------

Tiny RayTracer doesn't rely on any external libs/framework (qt/cmake)
So the 

```sh
gcc main.c
./a.out 192 108 output
```

Dependency
--------------
libc (open/read/write)


DONE
----
  - geometry intersection
  - output stream API (see output.bmp.c)
  - scene and camera API
  - almost every basic class (vector,color ...)

ALMOST DONE
-----------
  - materials

TODO
----
  - light
  - BSDF
  - more geometry

TODO (optional)
---------------
  - LISP scene scripting
