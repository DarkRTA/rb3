SZBE69
=============

A decompilation of SZBE69.

This repository builds the following DOLs:

```
189b001188a2f8ab769e72364440022407fe09d2  build/SZBE69/main.dol 
```

<!-- If you'd like to contribute, see [CONTRIBUTING.md](CONTRIBUTING.md). -->

Dependencies
============

Windows:
--------
- Install [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- (Optional) Run `Add-Exclusion.ps1` (Right click -> "Run with PowerShell") to avoid degraded performance from Windows Defender scans.

macOS:
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):
  ```
  brew install ninja
  ```
- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):
  ```
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

Linux:
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- Install wine from your package manager.
  - Faster alternative: [WiBo](https://github.com/decompals/WiBo), a minimal 32-bit Windows binary wrapper.  
    Ensure the binary is in `PATH`.

Building
========

- Checkout the repository:
  ```
  git clone https://github.com/DarkRTA/rb3.git
  ```
- Download [GC_WII_COMPILERS.zip](https://cdn.discordapp.com/attachments/727918646525165659/1129759991696457728/GC_WII_COMPILERS.zip)
- Extract the _contents_ of the zip file to `tools/mwcc_compiler`.
  - Resulting structure should be (for example) `tools/mwcc_compiler/GC/1.3.2/mwcceppc.exe`
- Using [Dolphin Emulator](https://dolphin-emu.org/), extract your game to `orig/SZBE69`.  
![](assets/dolphin-extract.png)
- Configure:
  ```
  python configure.py
  ```
- Build:
  ```
  ninja
  ```
