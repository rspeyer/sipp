SIPp - a SIP protocol test tool
Copyright (C) 2003-2014 - The Authors

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see [http://www.gnu.org/licenses/](http://www.gnu.org/licenses/).

# Building

This is the SIPp package. Please refer to the [webpage](http://sipp.sourceforge.net/) for details and documentation.

Normally, you should be able to build SIPp by just typing "./configure
--with-pcap --with-sctp; make" in the current directory. Then "sipp
-h" will give you access to the online help.

Some users have experienced problems with the pre-built autoconf-generated 'configure' file. There are two solutions:

* If you checked out the source through Git, you may need to `touch configure.ac aclocal.m4 configure Makefile.am Makefile.in` to correct the timestamps before running configure and make.
* You can also rebuild the 'configure' file from scratch by running `autoreconf -ivf`. You will need `autoconf` and `autoconf-archive` installed to make this work.

# Support

I try and be responsive to issues raised on Github, and there's [a reasonably active mailing list](https://lists.sourceforge.net/lists/listinfo/sipp-users).

# Contributing

SIPp is free software, under the terms of the GPL licence (see the LICENCE.txt file for details). You can contribute to the development of SIPp and use the standard Github fork/pull request method to integrate your changes integrate your changes. If you make changes in SIPp, *PLEASE* follow a few coding rules:

  - Please stay conformant with the current indentation style (2 spaces
    indent, standard Emacs-like indentation). Examples:

```
if (condition) {
  f();
} else {
  g();
}
```

  - Use "{" in if conditions even if there is only one instruction
    (see example above).

  - If possible, check your changes can be compiled on:
      - Linux,
      - Cygwin,
      - Mac OS X,
      - FreeBSD.

Thanks,

  Rob Day <rkd@rkd.me.uk>
