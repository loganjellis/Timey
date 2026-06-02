# Timey

**Timey** is a simple time library written in C. It comes with a timestamp and datetime struct, and some functions for obtaining times and dates,
    as well as obtaining future times and dates.

> [!NOTE]
> Timey is not thread-safe as of right now.

## Clone the repository

```
git clone https://github.com/loganjellis/Timey.git
cd Timey
```

## Building (and optionally installing)

```
cmake -S . -B build
cmake --build build
(only include this line if you want to install Timey) cmake --install build --prefix ./install
```

> [!NOTE]
> Note that ./install is a placeholder install location for the library. Omitting the install location results in the library being installed in the operating system's default path.

### Using Timey (installed package)

```
list(APPEND CMAKE_PREFIX_PATH "/path/to/timey/install")
find_package(Timey REQUIRED)
target_link_libraries(app PRIVATE Timey::timey)
```

### Using Timey (subdirectory)

```
add_subdirectory(Timey)
target_link_libraries(app PRIVATE Timey::timey)
```

## Documenation

Please refer to the Timey docs <a href="docs/html" targets="_blank">here</a>
