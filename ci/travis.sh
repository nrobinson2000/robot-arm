#!/bin/bash

# Install po-util
sudo curl -fsSLo /usr/local/share/po-common https://raw.githubusercontent.com/nrobinson2000/po/master/share/po-common
sudo curl -fsSLo /usr/local/share/po-linux https://raw.githubusercontent.com/nrobinson2000/po/master/share/po-linux
sudo curl -fsSLo /usr/local/bin/po https://raw.githubusercontent.com/nrobinson2000/po/master/bin/po
sudo chmod +x /usr/local/bin/po

# Configure and compile
po config v0.8.0-rc.14
po install
po P1 run compile-user