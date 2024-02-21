#
# DANTE :: System Automatycznych Testów Jednostkowych oraz Akceptacyjnych
# Tomasz Jaworski, 2018-2020
#
# Plik wygenerowany automatycznie
# Znacznik czasowy: 2024-02-20 18:18:57.763137
#

cmake_minimum_required(VERSION 3.17)
project(project1 C)

# Przyjmij standard C11
set(CMAKE_C_STANDARD 11)

# Ustaw opcje kompilatora (z raportu Dante)
add_compile_options(
      "-Wno-error=unused-parameter"
      "-D_ANSI_OUTPUT"
      "-fdiagnostics-color"
      "-Wall"
      "-Wno-error=implicit-fallthrough"
      "-Wno-parentheses"
      "-std=c11"
      "-Wno-error=parentheses"
      "-DINSIDE_DANTE"
      "-xc"
      "-pedantic"
      "-ggdb3"
      "-Werror"
      "-Werror=vla"
      "-D_GNU_SOURCE"
      "-fmax-errors=5"
      "-Wextra"

)

# Ustaw opcje konsolidatora (z raportu Dante)
add_link_options(
        "-Wl,-Map=main.map"
        "-Wl,-wrap,main"
        "-ggdb3"
        "-Wl,-cref"
)

# Utwórz target 'project1' i dodaj do niego pliki źródlowe:
add_executable(project1
        "defs.c"
        "main.c"
        "unit_helper_v2.c"
        "unit_test_v2.c"
        "rdebug.c"
)

# Dołącz niezbędne biblioteki
target_link_libraries(project1
        "m"
)