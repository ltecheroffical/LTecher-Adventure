# LTecher Adventure
LTecher Adventure is a WIP proceedially generated game made with C++ and raylib.

## Building

### Cloning the repo

To build the application, you must get the source code.
```bash
git clone https://github.com/ltecheroffical/LTecher-Adventure.git
cd LTecher-Adventure
```

### Release

Use this mode if you want to distrobute the game.
```bash
mkdir build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=true -DCMAKE_BUILD_TYPE=Release
make
make bundle # For OSX
```

### Debug

Use this mode for testing and debugging purposes.
```bash
mkdir build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=true -DCMAKE_BUILD_TYPE=Debug
make
```

Note: The game will crash if you don't pack the assets. Pack them using this command
```bash
python3 pack_assets.py
```
