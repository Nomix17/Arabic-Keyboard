#!/bin/bash

set -e 

BASE_NAME=$(basename *.pro .pro)

if [ ! -d "../bin" ]; then
  mkdir ../bin
fi

cd ../bin

qmake6 ../source/*.pro
make clean
make

# ./"$BASE_NAME"

mkdir -p /opt/ArabicKeyboard
cp -r ../cache /opt/ArabicKeyboard/
cp -r ../bin /opt/ArabicKeyboard/

chmod +x /opt/ArabicKeyboard/bin/VKeyboard

ln -s /opt/ArabicKeyboard/bin/VKeyboard /usr/bin/VKeyboard
cp /opt/ArabicKeyboard/cache/ArabicKeyboard.desktop $1/.local/share/applications
