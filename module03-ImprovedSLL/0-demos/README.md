# CMP 246 Data Structues & Algorithms
## Module 3 introductory demos

This directory contains seven progressive demonstrations that illustrate the need for / usefulness of operator overloads and copy constructors in C++ data structues. In an on-ground course, students will be asked to create a simple templated class representing a vector in two-dimensional space, and the instructor will guide them through a series of steps to illustrate these concepts before we look at them in the `SLL` data structure context.

The directories and the steps in the process are:

- vec1: simple templated `Vector2D<T>` class with accessor, mutator methods and a print method.

- vec2: add an addition operator to `Vector2D<T>.

- vec3: add stream insertion operator to `Vector2D<T>`.

- vec4: what happens when we do assignment between two `Vector2D<T>` objects?

- vec5: now make the fields of `Vector2D<T>` dynamic. What happens with assignment now?

- vec6: add assignment operator to dynamic `Vector2D<T>`.

- vec7: add copy constructors to dynamic `Vector2D<T>`.