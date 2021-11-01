<!--
    README.md : important information regarding this project.

    See `LICENSE' for full license.
-->

<!--
    Copyright (C) 2021 Kevin Matthes

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
-->

<!----------------------------------------------------------------------------->

# mkcws

## Summary

A simple command line application in order to create new Code workspaces.



## License

This project's license is **GPL 2**.  The whole license text can be found in
`LICENSE` in the main directory of this repository.  The brief version of the
license is as follows:

> Copyright (C) 2021 Kevin Matthes
>
> This program is free software; you can redistribute it and/or modify
> it under the terms of the GNU General Public License as published by
> the Free Software Foundation; either version 2 of the License, or
> (at your option) any later version.
>
> This program is distributed in the hope that it will be useful,
> but WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
> GNU General Public License for more details.
>
> You should have received a copy of the GNU General Public License along
> with this program; if not, write to the Free Software Foundation, Inc.,
> 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.



## Introduction

Many IDEs (*I*ntegrated *D*evelopment *E*nvironments) offer the possibility to
create projects in order to group project related files.  The same goes for
compilations of the VS Code source code, such as VS Code and VSCodium, for
instance, which will be named "VSC-like IDEs" in the following.  But often,
the way of how a project is defined as one differs from IDE to IDE.  Hence,
people who are new to a certain IDE might wonder how this is processed in the
concerning IDE.

For VSC-like IDEs, there are the `*.code-workspace` files which define a
certain directory on the machine's file system to be a workspace for the IDE.
This specification is made by using a JSON-like syntax.  Hence, workspaces can
not only be created from within the IDE during a session, but also before the
first session in this workspace since the used format can be edited by hand and
any arbitrary editor due to the fact that is just plain text.

This application, `mkcws`, is one possible solution in order to automate the
process of workspace creation.  It is designed to be a simple command line
application which creates the workspace according to different given parameters
which are as follows:

* the used coding language
* the intended project name
* the path of the directory with all related project files

The name `mkcws` is an abbreviation of "**m**a**k**e a new **C**ode
**w**ork**s**pace" and is inspired by the UNIX commands for creation, such as
the one for directories: `mkdir`.



## Build process

Building this project is very simple since it does not depend on anything
except the C standard library.  This project can be build by executing the
following command in a terminal:

```
make
```

Other compilers than `gcc` are possible, as well, if desired.  Therefore, the
variable `CC` in `makefile` should be adjusted.

The command above will build the application and test it with `valgrind` right
after the compilation finished.  In order to ensure this test to succeed, users
should make sure that they have a valid `valgrind` installation.  In general,
users should take a look at the variable settings of the build routine before
building the application in order to avoid unnecessary errors due to incorrect
settings regarding their system configuration.

To build without any tests, run:

```
make mkcws
```



## Usage

### Options

`mkcws` uses options in order to determine the mode to use.  In the following,
a table will explain all options, what has be passed with them and how high
their priority is.  Priority is counted in the UNIX style, i. e. the lower the
integer number is, the higher is the associated priority.  Hence, priority `0`
is the highest possible one.

Option              | Prio. | Category  | Meaning               | Requirement(s)
:-------------------|:-----:|:----------|:----------------------|:--------------
`-L`                | 0     | state     | show the license      | none
`-c`                | 0     | state     | show the license      | none
`--copyright`       | 0     | state     | show the license      | none
`-l`                | 2     | content   | main coding language  | `-n`, `-p`
`--language=`       | 2     | content   | main coding language  | `-n`, `-p`
`--license`         | 0     | state     | show the license      | none
`-n`                | 1     | content   | project name          | `-p`
`-p`                | 1     | content   | path to the project   | `-n`
`--path=`           | 1     | content   | path to the project   | `-n`
`--project-name=`   | 1     | content   | project name          | `-p`
`-s`                | 0     | state     | show the license      | none
`--show-copyright`  | 0     | state     | show the license      | none
