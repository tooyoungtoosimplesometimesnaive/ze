# The code/package manager for everyone!

Using github as the remote server.

## To be a ze project, you have to include a ze.project file in your root directory.

The `ze.project` file is a file that indicating the structure of the project.

Sample ze.project:
```
lang: c++
src-dir: src
src-files: sample.hpp, sample.cpp

```

## Down load using `ze install <project_name>`

Then will download the files defined in the `src-files` in `ze.project` to `./lib/<project_name>`.

## Create a ze project using `ze init`

Will create a ze.project in your root directory and bootstrap the project.
