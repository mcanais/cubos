# Getting started {#getting-started}

@brief How to download, build and run the engine and where to go from there.

## Building the engine from source

@note This guide assumes you're familiar with the basics of git.

### Getting the code

The **Cubos** source code is [hosted on GitHub](https://github.com/GameDevTecnico/cubos),
so the easiest and only way to get the code right now is to clone the
repository with git.

### Dependencies

All required dependencies are fetched by CMake through `FetchContent` commands.
It first looks for them, and if it can't find an existing installation, it installs them locally.
You can see a list of those dependencies in the `CMakeLists.txt` configuration of each target.
For example, to see the dependencies of the `cubos-core` library, take a look at `core/CMakeLists.txt`.

### Formatting

To contribute you must ensure your code is correctly formatted. Install
`clang-format` and run the following command to enable a pre-commit hook
which formats your changes automatically:

```bash
git config --local include.path ../.gitconfig
```

### Compiling

The easiest way to compile **Cubos** is by opening its directory in an IDE with CMake support. We recommend using [Visual Studio Code](https://code.visualstudio.com/) with the CMake and C++ extensions installed, as it is cross-platform, and most of the team is using it.

The IDE you choose most probably provides a way to set CMake options through the UI.
In *Visual Studio Code*, you can do this by pressing `Ctrl + Shift + P` and choosing `CMake: Edit CMake Cache (UI)`.
Alternatively, you can change options directly through the `CMakeCache.txt` on the directory you chose to build the project in (usually `build/`).

*Visual Studio Code*'s CMake extension allows you to set a *build* target. You can set this target, for example, to `cubos-core`, in order to compile only the `core`. To compile it, just press the build button.

You can see a list of all the options available to configure the engine through CMake, or through the `CMakeLists.txt` files themselves.
We've put some of the most used options in the table below:

| Name                    | Description                          |
| ----------------------- | ------------------------------------ |
| `CUBOS_CORE_SAMPLES`    | Build core samples?                  |
| `CUBOS_CORE_TESTS`      | Build core tests?                    |
| `CUBOS_ENGINE_SAMPLES`  | Build engine samples?                |
| `CUBOS_ENGINE_TESTS`    | Build engine tests?                  |
| `CUBOS_DOCUMENTATION`   | Build the documentation?             |
| `TESSERATOS_DISTRIBUTE` | Build the editor for distribution?   |

After you change an option's value, make sure to reconfigure CMake! In *Visual Studio Code*, you can do this by pressing `Ctrl + Shift + P` and choosing `CMake: Configure`.

## Running the examples and tests

In *Visual Studio Code*, the CMake extension allows you to set the *debug* targets. That target can then by launched/debugged by pressing the launch/debug button.

### Examples

Both `core` and `engine` contain examples which you can run to check if
things are running correctly. To build them, you must enable the
`CUBOS_CORE_SAMPLES` and/or `CUBOS_ENGINE_SAMPLES` options.
This will show new multiple targets, one for each example.

### Testing

**Cubos** uses *doctest* for unit testing the engine. To build them, you must
enable the `CUBOS_CORE_TESTS` and/or `CUBOS_ENGINE_TESTS` options. You can run the tests through the targets `cubos-core-tests` and `cubos-engine-tests`.

## Whats next?

We recommend you start by reading the @ref features "feature guide", which
introduces you to important concepts and features of the engine, such as what
is an ECS and how it is used in **Cubos**.

The @ref examples "examples page" is also a good place to go if you want to
see how specific parts of the engine are used in practice.
