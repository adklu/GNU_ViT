v109

## GNU_ViT - Video Editor Tool



### Content

A) REQUIRED

B) INSTALL

C) LICENSE


------------------

### A) REQUIRED

- Linux (tested with Debian 9)

- Qt5, qt5-default

build-essential

qmake

GNU Autotools (automake, autoconf, configure, make)

mesa-common-dev

libgl1-mesa-dev, libglu1-mesa-dev

----------

- qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5

- ffmpeg (tested with ffmpeg 3.3.6)

----------

(gtk2: install qt5-style-plugins -> echo "export QT_QPA_PLATFORMTHEME=gtk2" >> ~/.profile) 


### B) INSTALL

- Copy Source into (replace [username]): /home/[username]/GNU_ViT

- mark all .sh and .desktop files as executables

- ./INSTALL.sh

- Edit Desktop file (GNU_ViT.desktop):

replace [username] in:

Exec=/home/[username]/GNU_ViT/GNU_ViT %F 

Icon=/home/[username]/GNU_ViT/Icon1.png

(To start GNU_ViT via command (e.g. for debug output in terminal): /home/[username]/GNU_ViT/GNU_ViT)


### C) LICENSE

GNU_ViT - Video Editor Tool
       
Copyright (c) 2021 A.D.Klumpp

This program is free software; you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by 
the Free Software Foundation; either version 2 of the License, or 
(at your option) any later version.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details.




