# OpenVC Hero

## Installing OpenCV
------

### From Homebrew

```
brew remove opencv3
brew cleanup
brew install homebrew/science/opencv3
brew ln opencv3 --force
```

### From source
If you are on mac just follow [these instructions] (http://blogs.wcode.org/2014/10/howto-install-build-and-use-opencv-macosx-10-10/).


## Generating xcode files
------

```
mkdir xcode
cd xcode
cmake -G "Xcode" ..
```

## Generating sublime files

```
mkdir xcode
cd xcode
cmake -G "Sublime Text 2 - Unix Makefiles" ..
```

## Building

```
cd xcode
make
```

## Running

The debug binary is located at

```
xcode/Debug/DisplayOpenCVHero
```
## Using it

> Type numbers from 1 to 5 in order to change different visualisations modes.
