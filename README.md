# oclPGE test
Some fiddling around and learing of the Pixel Game Engine made by One Lone Coder.  
https://github.com/OneLoneCoder/olcPixelGameEngine

This spesific olcPGE project is a simple CAD program that can make:
- Lines
- Boxes
- Circles
- Splines (Bezier Curve)

So far you can't save things, but I might add that at a later point.

---

This is CAD program is inspired/based on [javidx9's (One Lone Coder) video on Polymorphism](https://youtu.be/kxKKHKSMGIg).

---

Note:  
this uses Version 2.20 of olcPGE
[link to release](https://github.com/OneLoneCoder/olcPixelGameEngine/releases/tag/v2.20)

---

## Quickstart

### Compile/Build
compiles/builds the C++ code in `src/impl/`   
and headers in `src/incl/`   
to `build/debug/`  
```sh
make build_debug
```
or
```sh
make
```

compiles/builds the C++ code in `src/impl/`   
and headers in `src/incl/`   
to `build/release/`  
```sh
make build_release
```

### Run
runs the compiled binary in `build/debug/`
```sh
make run
```

runs the compiled binary in `build/release/`
```sh
make run_release
```

### Clean
removes the `build/` folder
```sh
make clean
```

### Multiple at once
You can run multiple ones at once, for example:
```sh
make build run
```
or:
```sh
make clean build
```
etc...
