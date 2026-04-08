# Cetraminos
A tetris clone
# How to compile:
First, install the dependencies SDL2, SDL2_TTF and SDL2_Mixer.
For Debian and Debian-based distros (Ubuntu, Linux Mint, Pop_OS...):
```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
```
For Fedora and Fedora-based distros (Nobara, Ultramarine, RisiOS, QubesOS...)
```bash
sudo dnf install SDL2-devel SDL2_ttf-devel SDL2_mixer-devel
```
For Arch and Arch-based distros (Manjaro, ChachyOS, EndeavourOS, Garuda Linux...)
```
sudo pacman -S sdl2 sdl2_ttf sdl2_mixer
```
After it, just do
```
make
```
For the music, you must have a CetraminosMusic.mp3 file. I have not found yet a good recording of Odeon (Ernesto Nazareth) without having authorial problems, but I strongly recommend you to do so if you can. There's an intentional delay of 7 seconds until the start.

# How to play
* ← and → for going left or right.
* Upper arrow key: Spinning.
* ↓ : Drops the piece faster
* Space : Drops the piece instantly
* Esc : Returns to Menu
