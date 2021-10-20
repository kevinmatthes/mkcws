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
