# SCOP
In this repogitory, we try to display 3D object from object file like Blender. We implemented following functions.
Let's enjoy GPU rendering.


- Read and parse object file
- Project object as 3D object
- Rotate object
- Walk around 3D space
- Switch object color

You can try this program by running following command.

```bash
export LD_LIBRARY_PATH=LD_LIBRARY_PATH:glfw/build/src
export LIBGL_ALWAYS_INDIRECT=0
cd srcs
make re
./scop 42.obj
```

<img src="images/42.gif" width='700'>

<br></br>

## Controls
- Move forward: w
- Move backward: s
- Move left: a
- Move right: d
- Switch object color to red: r
- Switch object color to green: g
- Switch object color to blue: b

<br></br>

## Referrence
- [Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion](https://learnopengl.com/book/book_pdf.pdf)
