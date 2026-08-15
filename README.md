# Idle Game

## Building

To build from source run the following two CMake commands.

```
cmake -B build -G Ninja .
cmake --build build
./build/idle
```

To build for web from source run the following commands.

```
# Install emsdk
git clone --depth=1 https://github.com/emscripten-core/emsdk.git
./emsdk/emsdk install latest
./emsdk/emsdk activate latest
# Do the build
source ./emsdk/emsdk_env.sh
emcmake cmake -S . -B embuild -G Ninja
cmake --build embuild
# Host the html file locally
python -m http.server -d embuild --bind 127.0.0.1
```

## Contributing

To enable clangd and clang-tidy we need to build a clang version.

```
cmake -B build-analyse -G Ninja . \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DLINT_ENGINE=ON
cmake --build build-analyse
```
