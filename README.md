# Timey

**Timey** is a simple time library written in C. It comes with a timestamp and datetime struct, and some functions for obtaining times and dates,
as well as obtaining future times and dates.

> [!NOTE]
> Timey is not thread-safe.

## Clone the repository

```
git clone https://github.com/loganjellis/Timey.git
cd Timey
```

### Using Timey (in-directory, place header files in /include, .a files in /lib, and any .dll files next to any executables)

```
target_include_directories(app PRIVATE "path/to/include")
target_link_libararies(app PRIVATE "path/to/lib")
```

### Using Timey (subdirectory)

```
add_subdirectory(Timey)
target_link_libraries(app PRIVATE Timey::timey)
```

## Documenation

Please refer to the Timey docs <a href="docs/html" targets="_blank">here</a>
