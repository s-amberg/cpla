# No new exercises

Time for Questions!


# WebAssembly Lecture Steps

## Setup

You can install the necessary tooling in the devcontainer if you don't want to add clutter to your machine natively. In the terminal install

- nodejs: `pacman -S nodejs`
- npm: `pacman -S npm`
- libicu: `pacman -S icu`
- wat-wasm: `npm install -g wat-wasm`

Check the following command works: `wat2wasm`

Install `emcripten` by following the installation instructions [here](https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install).

- Navigate to the top-level directory of the devcontainer
- Clone the repository: `git clone https://github.com/emscripten-core/emsdk.git`
- Enter the directory: `cd emsdk`
- Update the repsitory: `git pull`
- Download the latest SDK tools: `./emsdk install latest`
- Activate the latest SDK tools: `./emsdk activate latest`
- Activate the environment: `source ./emsdk_env.sh`
- Check the installation: `emcc -v`


## Hello World (WAT)

Run the following commands in the directory `lecture_examples/01_wasm_hello_world`:
- Compile WAT to WASM: `wat2wasm helloworld.wat` -> This should create `helloworld.wasm`
- Run the corresponding javascript: `node helloworld.js` -> You should see `Hello world!` in the console.

## Hello World (Emscripten)

Run the following commands in the directory `lecture_examples/02_emscripten_hello_world`:
- Compile WASM and generate Javascript file: `emcc hello_world.cpp` -> this should create `a.out.js` and `a.out.wasm`
- Run generated Javascript file: `node a.out.js`


## Hello World with HTML (Emscripten)

Run the following commands in the directory `lecture_examples/02_emscripten_hello_world`:
- Compile WASM, generate Javascript and HTML files: `emcc hello_world.cpp -o hello.html` -> this should create `hello.js`, `hello.wasm` and `hello.html`
- Start a python http.server: `python -m http.server` -> From the devcontainer you should automatically get the option to open the browser at the selected port. There you should be able to navigate to `hello.html` and see a console-like window. Using a web server is typically required to avoid XHR (XMLHttpRequest) to other local files, which might be prevented by the browser.


## SDL Example (Emscripten)

Run the following commands in the directory `lecture_examples/03_emscripten_sdl`:
- Compile WASM, generate Javascript and HTML files: `emcc sdl_example.cpp -o sdl.html` -> this should create `sdl.js`, `sdl.wasm` and `sdl.html`
- Start a python http.server: `python -m http.server` -> From the devcontainer you should automatically get the option to open the browser at the selected port. There you should be able to navigate to `hello.html` and see a console-like window. Using a web server is typically required to avoid XHR (XMLHttpRequest) to other local files, which might be prevented by the browser.