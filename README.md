# BowlingScoreboard

**BowlingScoreboard** is a Qt6-based bowling score display application. The project includes:
- A QML-based user interface for a bowling scoreboard.
- A core scoring library for bowling game logic.
- A network module that receives UDP data.
- GoogleTest-based unit tests for core and network components.

## Dependencies

Required:
- CMake 3.21 or newer
- C++20 compiler (GCC, Clang, etc.)
- Qt 6 with modules:
  - Core
  - Gui
  - Qml
  - Quick
  - QuickControls2
  - Network
- GoogleTest

Optional for static analysis:
- clang-tidy
- cppcheck
- cppcheck-htmlreport (for HTML reports)

## Connect to Dev Container

This project supports a Dev Container-based toolchain setup. On the host machine, install Docker and grant the container permission to access the local X11 display:

```bash
xhost +local:docker
```

### Connect via VS Code

Press **Ctrl+Shift+P** and select **Dev Containers: Reopen in Container**.

### Connect via Terminal:

Start container and enter source directory: 
```bash
cd ./.devcontainer
docker compose up -d
docker compose exec qt_dev /bin/bash
cd workspaces/BowlingScoreBoard/
```

## Configure and Build
In container shell, configure the project with CMake:

```bash
cmake -S . -B ./build
```

Build the project:

```bash
cmake --build ./build
```

The generated executable is `BowlingScoreboard` in the `./build` directory.

## Run the Application

### Run scoreboard UI

From the repository root:

```bash
./build/BowlingScoreboard
```

The application opens a bowling scoreboard window and listens for UDP score data.

### Test UDP input with `nc`

In **host** terminal, send test UDP payloads to the local receiver on port `45454`:

```bash
printf '5' | nc -u -w1 localhost 45454
```

Or send a `ROLL` command:

```bash
printf 'ROLL 7' | nc -u -w1 localhost 45454
```

Valid payloads are either a number from `0` to `10`, or a string of the form `ROLL <n>`.

## Run Unit Tests

After building, run tests using CTest from source directory:

```bash
cmake --build ./build --target test
```

## Run cppcheck

From the source directory, run:

```bash
cmake --build ./build --target cppcheck
```

If `cppcheck-htmlreport` is installed, generate an HTML report with:

```bash
cmake --build ./build --target cppcheck-html
```

The report is written to `build/cppcheck-report` when available.

## Run clang-tidy

From the source directory:

```bash
cmake --build ./build --target clang-tidy
```

## Project Structure

- `CMakeLists.txt`: main build file
- `src/main.cpp`: application entry point
- `src/core`: bowling scoring library and unit tests
- `src/network`: UDP network module and tests
- `src/viewmodel`: QML view model integration
- `src/ui`: QML user interface files
- `docs/`: generated documentation output
- `build/`: out-of-source build directory
- `.vscode`: vscode related settings
- `.devcontainer`: Docker container related files
