# LIBS directory

In this directory, you are required to place all the external libraries your
project depends on. Although, in principle, you can use git submodules (and
place them under this directory), for the sake of easily compiling your
application, placing the source code of the open source libraries is also fine.
However, this approach is not applicable to large dependencies, such as QT.

# List of External Libs

1. [SFML](https://github.com/SFML/SFML.git)

Linux users need to install SFML's dependencies using their system package
manager. On Ubuntu and other Debian-based distributions the following commands
can be used:

```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

2. [Box2D](https://github.com/erincatto/box2d.git)

3. [Box2CPP](https://github.com/HolyBlackCat/box2cpp.git)

> If you are using already compiled library, place it in this folder, and set
> the linker options appropriately. The inlcude files of the dependent library
> should also be placed in this folder.
