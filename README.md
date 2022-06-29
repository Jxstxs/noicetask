# NoiceTask - a simple Cli Todo Management Tool

This Project is about a simple extendable Todo Management Tool written in C and using a sqlite3 Database as storage.

## Features

nt (noicetask) lets you create Todos, modify, delete, list or mark them as done.
It also let you create multiple Databases, to manage Todos in diffrent Projects or other Stuff.
To learn more about the Implemented Feature have a look at the [Implemented](./docs/IMPLEMENTED.md) Page.

## Current Status of the Project

This project is currently under active development in an very early state, so dont expect too much (I'm also new to this whole Stuff :) ).

## Installation

You need a Unix Based system with the base-devel package(name in arch).
To Compile it, simply run `make` in your Terminal and run it with `./bin/nt <..args..>`.
When you want to install it, run `sudo make install` and `make clean` to keep the Sourcetree pretty (or combined `sudo make install clean`).
This will copy `nt` into `/usr/bin` (or the Directory specified within the [Makefile](./Makefile) with `INST_DEST`).

### Dependencies

This project only relies on the sqlite3 C libary and other standard C libaries. So you dont need to install any other extra Packages.

## Roadmap

To have a look at what Features you could expect, have a look at the [Ideas](./docs/IDEAS.md) Page, where all the comming features are written down.

## Contribution

Feel free to contribute to this project, the guidelines for this could be find [here](./docs/CONTRIBUTING.md).
I would apreceate any Contribution to learn more about working with others and to improve this project.

## License

I didnt thought about that by now.
