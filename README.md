## Dependencies

Before using this code, please ensure you have the following dependencies installed:

- **Qt6**: Required for the GUI framework
- **xclip** (X11) or **wl-copy** (Wayland): Required for clipboard functionality

### Installation

#### Ubuntu/Debian
```bash
sudo apt install qt6-base-dev xclip
```

#### Fedora
```bash
sudo dnf install qt6-qtbase-devel xclip
```

#### Arch Linux
```bash
sudo pacman -S qt6-base xclip
```

## Installation

```bash
git clone https://github.com/Nomix17/Arabic-Keyboard
cd Arabic-Keyboard
chmod +x source/build.sh
cd source
sudo ./build.sh $HOME
```
