## A simple Software Renderer

This was primarily made as an exercise to try to learn and understand how graphics rendering works. A GPU usually abstracts away a lot of the details regarding how pixels are rendered into complex shapes and effects, and the math behind it. Being interested in this aspect of rendering, I decided to make a rasterizer based software renderer.

Reminicient of the early days of gaming, this program could theoretically be used to make stylized games like [Starfox](https://en.wikipedia.org/wiki/Star_Fox_%281993_video_game%29), [Doom](https://en.wikipedia.org/wiki/Doom_(1993_video_game)), etc.

## Building and Running

This program uses the SDL2 library to draw to the screen, handle windows, etc. To run the program, you'll need to download [SDL2 from its github page](https://github.com/libsdl-org/SDL/releases/) and place the `SDL2.dll` file (found in the `bin` folder inside the zip file) either on your OS's PATH, or adjacent to the compiled executable.

To build this library from source, create a folder called `lib` in the main folder, and extract the contents of the 64-bit version of SDL2 into the folder. It should look something like this:
```
software-renderer
|- lib
    |- SDL
        |- bin
        |- include
        |- lib
        |- share
|- src 
    |- ...
|- .gitignore
|- Makefile
```

Then, just run the make file with `make init`, which creates a new `bin` folder and copies the SDL.dll into it. Running `make` after should build and run the project.
