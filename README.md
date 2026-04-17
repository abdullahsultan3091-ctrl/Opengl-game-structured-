# OpenGL Breakout

A Breakout clone built with OpenGL, GLFW, GLAD, and GLM.
Uses a modular CMake architecture.

## Project Structure

    breakout-opengl/
    ??? CMakeLists.txt
    ??? apps/
    ?   ??? CMakeLists.txt
    ?   ??? main.cpp
    ??? libs/
        ??? CMakeLists.txt
        ??? external_libs/
        ?   ??? glad/
        ?   ??? glfw-3.4/
        ?   ??? glm/
        ??? internal_libs/
            ??? game_object/
            ??? collision/
            ??? shader/
            ??? renderer/

## Controls

| Key | Action |
|-----|--------|
| A / Left Arrow | Move paddle left |
| D / Right Arrow | Move paddle right |
| Space | Launch ball |
| Escape | Quit |

---

## Windows 11

### Prerequisites

- [Git](https://git-scm.com/download/win)
- [CMake 3.16+](https://cmake.org/download/) — during install select "Add CMake to system PATH"
- [Visual Studio 2022](https://visualstudio.microsoft.com/) — needed for the compiler even if you use VS Code or CLion

During Visual Studio install select:
- Desktop development with C++
- Make sure C++ CMake tools for Windows is checked

### Clone the repo

    git clone https://github.com/abdullahsultan3091-ctrl/Opengl-game-structured-.git
    cd Opengl-game-structured-

---

### Windows 11 — VS Code

1. Install [VS Code](https://code.visualstudio.com/)

2. Install these extensions inside VS Code:
   - C/C++ (Microsoft)
   - CMake Tools (Microsoft)

3. Open the project — File ? Open Folder ? select the project folder

4. VS Code will ask "Would you like to configure this project?" — click Yes

5. Select your kit when prompted — choose Visual Studio Community 2022 Release - amd64

6. At the bottom toolbar click Build or press F7

7. At the bottom toolbar click the play button next to RainbowBreakout

---

### Windows 11 — CLion

1. Install [CLion](https://www.jetbrains.com/clion/)

2. Open CLion ? Open ? select the project folder
   CLion auto-detects CMakeLists.txt and configures everything

3. In the top right dropdown select RainbowBreakout as the target

4. Click the green Run button or press Shift+F10

If CLion cannot find the compiler go to:
- File ? Settings ? Build, Execution, Deployment ? Toolchains
- Add Visual Studio toolchain and point it to your VS 2022 install

---

## Ubuntu

### Prerequisites

Open a terminal and run:

    sudo apt update
    sudo apt install -y git cmake build-essential libgl1-mesa-dev libglu1-mesa-dev

### Clone the repo

    git clone https://github.com/abdullahsultan3091-ctrl/Opengl-game-structured-.git
    cd Opengl-game-structured-

---

### Ubuntu — Terminal

    mkdir build
    cd build
    cmake ..
    cmake --build .
    ./apps/RainbowBreakout

---

### Ubuntu — VS Code

1. Install VS Code:

       sudo snap install code --classic

2. Install these extensions inside VS Code:
   - C/C++ (Microsoft)
   - CMake Tools (Microsoft)

3. Open the project:

       code .

4. VS Code will ask "Would you like to configure this project?" — click Yes

5. Select your kit when prompted — choose GCC

6. At the bottom toolbar click Build or press F7

7. At the bottom toolbar click the play button next to RainbowBreakout

---

### Ubuntu — CLion

1. Install CLion:

       sudo snap install clion --classic

2. Open CLion ? Open ? select the project folder
   CLion auto-detects CMakeLists.txt and configures everything

3. In the top right dropdown select RainbowBreakout as the target

4. Click the green Run button or press Shift+F10

If CLion cannot find CMake go to:
- File ? Settings ? Build, Execution, Deployment ? Toolchains
- Make sure GCC is listed. If not install it:

      sudo apt install gcc g++

---

## Dependencies

| Library | Version | Purpose |
|---------|---------|---------|
| GLFW | 3.4 | Window creation and input |
| GLAD | - | OpenGL function loader |
| GLM | - | Math library |
| OpenGL | 3.3 Core | Rendering |