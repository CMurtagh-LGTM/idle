# Idle Game

## Building

To build from source run the following two CMake commands.

```
cmake -B build -G Ninja .
cmake --build build
./build/idle
```

## Contributing

To enable clangd and clang-tidy we need to build a clang version.

```
cmake -B build-analyse -G Ninja . \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DLINT_ENGINE=ON
cmake --build build-analyse
```
