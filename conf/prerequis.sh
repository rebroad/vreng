#! /bin/sh
#
# prerequis.sh
#
# Check and install needed requirements from scratch
#
# Note 1:
#       This script has been tested on MacOS and Ubuntu.
#
# Note 2:
#       If you don't trust this script to do sudo in your place
#       then initialize do_sudo to "no"
#
#       do_sudo="no"
#
# Philippe Dax - 2024
#
do_sudo="yes"		# change to "yes" if you trust this scipt to do sudo

#if [ -f ../configure ];     then exit 0 ; fi	# assume that vreng is configured

dist=""			# os distribution
cmd=""			# command to install
pfx=/usr		# prefix for libs
sfx=so			# suffix for libs
dev=""			# suffix for libs
ret=0			# return code
log=log/by_hand.log	# log to install by hand


# name of this script
p=$(basename $0)
if [ ! -d log ]; then mkdir log; fi
cp /dev/null $log

install_packages() {
  echo "$p: installing packages: $@"
  echo "$cmd $@" >>$log
  $cmd "$@" >>$log
}

#
# choose sudo
#
if [ "$do_sudo" = "no" ]; then
  sudo=""
else
  sudo=sudo
fi

###################
# select os
#
case $(uname -s) in

Darwin)		# macos
  dist=macos
  echo "$p: $dist !"

  ## brew
  if which brew > /dev/null; then
    echo "$p: brew !"
    sfx=dylib
    dev=
  else
    echo "$p: get brew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    echo "install brew" >>$log
  fi
  cmd="brew install"

  ## X11
  if which xquartz > /dev/null; then
    echo "$p: xquartz !"
  else
    install_packages --cask xquartz
  fi
  ret=0
  ;;

Linux)		# debian, ubuntu, mint, fedora, centos, arch
  dist=$(cat /etc/*-release | grep ID | head -n1 | cut -d '=' -f2)
  if [ $dist != "" ]; then
    echo "$p: $dist !"
    ret=0
  else
    dist=$(uname -s)
  fi
  echo "$p: have $dist !"

  case $dist in
  ubuntu|debian|linuxmint)
    if [ -n "$sudo" ]; then
        $sudo apt-get update
    fi
    pkg="apt-get"
    echo "$p: apt-get !"
    cmd="$sudo apt-get install -y"
    packages="build-essential autoconf automake libtool libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxmu-dev libxpm-dev libjpeg-dev libtiff-dev default-jdk doxygen graphviz libgif-dev giflib-tools libcurl4-openssl-dev bison libfreetype6-dev freeglut3-dev"
    install_packages $packages
    exit $?
    ;;
  *)
    if which apt-get > /dev/null; then
      cmd="$sudo apt-get install -y"
      dev="-dev"
      pfx=/usr
      sfx=so
      java="default-jdk"
    elif which dnf > /dev/null; then
      pkg="dnf"
      echo "$p: dnf !"
      cmd="$sudo dnf install"
      dev="-devel"
      pfx=/usr
      sfx=so
      java="java-1.8.0-openjdk.x86_64"
    elif which yum > /dev/null; then
      pkg="yum"
      echo "$p: yum !"
      cmd="$sudo yum install"
      dev="-devel"
      pfx=/usr
      sfx=so
      java="java-1.8.0-openjdk.x86_64"	# not sure
    elif which pacman > /dev/null; then
      dist=arch
      pkg="pacman"
      echo "$p: pacman !"
      cmd="$sudo pacman -S"
      pfx=/usr
      sfx=so
      java=java	# not sure
    else
      echo "$p: unknown linux distrib"
      pkg=""
      ret=1
      exit $ret
    fi
	;;
  esac
  ret=0
  ;;

*bsd|*BSD)	# freeBSD, netBSD, openBSD
  echo "$p: bsd distrib !"
  cmd="$sudo pkg"
  pfx=/usr
  sfx=so
  java=java	# not sure
  ret=0
  ;;

*)		# others to be completed
  echo "$p: unknown system"
  exit 1
  ;;
esac

###################
# Autotools : autoconf, automake, aclocal, autoreconf
#

## autoconf
if which autoconf > /dev/null; then
  echo "$p: autoconf !"
else
  install_packages autoconf
fi

## automake
if which automake > /dev/null; then
  echo "$p: automake !"
else
  install_packages automake
fi

## libtool
if which libtool > /dev/null; then
  echo "$p: libtool !"
else
  install_packages libtool
fi

## aclocal
if which aclocal > /dev/null; then
  echo "$p: aclocal !"
else
  install_packages aclocal
fi

## autoreconf
if which autoreconf > /dev/null; then
  echo "$p: autoreconf !"
else
  install_packages autoreconf
fi

###################
# Compilers : g++, gcc
#

## g++
if which g++ > /dev/null; then
  echo "$p: g++ !"
else
  install_packages g++
fi

## gcc
if which gcc > /dev/null; then
  echo "$p: gcc !"
else
  install_packages gcc
fi

###################
# Libs : libGL, libGLU, libX11, libXmu, libXpm, libgif, libpng, libjpeg, libtiff, libfreetype
#

## libGL
pfx=$(which xinit | cut -d '/' -f 1,2,3)	# assume X11 is installed
if [ -f $pfx/lib/libGL.$sfx ]; then
  echo "$p: libGL !"
else
  install_packages libgl$dev
  install_packages libGL$dev
  install_packages libgl1-mesa$dev # Ubuntu 24.04.1 LTS
fi

## libGLU
pfx=$(which xinit | cut -d '/' -f 1,2,3)	# assume X11 is installed
if [ -f $pfx/lib/libGLU.$sfx ]; then
  echo "$p: libGLU !"
else
  install_packages libglu$dev
  install_packages libGLU$dev
  install_packages libgl1-mesa$dev # Ubuntu 24.04.1 LTS
fi

## libX11
pfx=$(which xinit | cut -d '/' -f 1,2,3)	# assume X11 is installed
if [ -f $pfx/lib/libX11.$sfx ]; then
  echo "$p: libX11 !"
else
  install_packages libX11$dev
fi

## libXmu
pfx=$(which xinit | cut -d '/' -f 1,2,3)	# assume X11 is installed
if [ -f $pfx/lib/libXmu.$sfx ]; then
  echo "$p: libXmu !"
else
  install_packages libXmu$dev
fi

## libXpm
pfx=$(which xinit | cut -d '/' -f 1,2,3)	# assume X11 is installed
if [ -f $pfx/lib/libXpm.$sfx ]; then
  echo "$p: libXpm !"
else
  install_packages libXpm$dev
fi

## libgif
pfx=/usr/local
if [ -f $pfx/lib/libgif.$sfx -o -f $pfx/lib/x86_64-linux-gnu/libgif.$dyl ]; then
  echo "$p: libgif !"
else
  install_packages libgif$dev
fi

## libpng
pfx=/usr/local
if [ -f $pfx/lib/libpng.$sfx -o -f $pfx/lib/x86_64-linux-gnu/libpng.$dyl ]; then
  echo "$p: libpng !"
else
  install_packages libpng$dev
fi

## libjpeg
pfx=/usr/local
if [ -f $pfx/lib/libjpeg.$sfx -o -f $pfx/lib/x86_64-linux-gnu/libjpeg.$dyl ]; then
  echo "$p: libjpeg !"
else
  install_packages libjpeg$dev || install_packages jpeg$dev
fi

## libtiff
pfx=/usr/local
if [ -f $pfx/lib/libtiff.$sfx -o -f $pfx/lib/x86_64-linux-gnu/libtiff.so ]; then
  echo "$p: libtiff !"
else
  install_packages libtiff$dev || install_packages tiff$dev
fi

## libfreetype
pfx=$(freetype-config --prefix)
if [ -f $pfx/lib/libfreetype.$sfx -o -f /usr/local/lib/x86_64-linux-gnu/libfreetype.$dyl ]; then
  echo "$p: freetype !"
else
  install_packages freetype$dev
fi

####################
# Optional : ocaml, sqlite3, java
#

## ocaml
if [ $(which ocaml) ]; then
  echo "$p: ocaml !"
else
  install_packages ocaml
fi

## sqlite3
if [ $(which sqlite3) ]; then
  echo "$p: sqlite3 !"
else
  install_packages sqlite3
fi

## java
if [ $(which java) ]; then
  echo "$p: java !"
else
  install_packages $java
fi

####################
# Finish
#

ret=0
if [ $do_sudo != "yes" ]; then
  if [ -s $log ]; then
    echo "$p: the following operations must to do manually"
    cat $log
  fi
fi

exit $ret
