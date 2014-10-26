#!/bin/bash

BINUTILS_VERSION=2.24
GCC_VERSION=4.9.1
GMP_VERSION=6.0.0a
MPFR_VERSION=3.1.2
MPC_VERSION=1.0.2
NEWLIB_VERSION=2.1.0

PREFIX="$(pwd)/toolchain"
TARGET=i686-elf

# build binutils
wget -nc "http://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz"
tar xvzf "binutils-$BINUTILS_VERSION.tar.gz"
rm -rf binutils-build
mkdir binutils-build
cd binutils-build
"../binutils-$BINUTILS_VERSION/configure" "--prefix=$PREFIX" \
    "--target=$TARGET" --disable-nls --disable-werror --with-sysroot
make
make install
cd ..

wget -nc "http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz" \
    "https://gmplib.org/download/gmp/gmp-$GMP_VERSION.tar.bz2" \
    "http://www.mpfr.org/mpfr-current/mpfr-$MPFR_VERSION.tar.gz" \
    "ftp://ftp.gnu.org/gnu/mpc/mpc-$MPC_VERSION.tar.gz"

tar xvzf "gcc-$GCC_VERSION.tar.gz"
tar xvjf "gmp-$GMP_VERSION.tar.bz2"
tar xvzf "mpfr-$MPFR_VERSION.tar.gz"
tar xvzf "mpc-$MPC_VERSION.tar.gz"

cp -r "gmp-6.0.0" "gcc-$GCC_VERSION/gmp"
cp -r "mpfr-$MPFR_VERSION" "gcc-$GCC_VERSION/mpfr"
cp -r "mpc-$MPC_VERSION" "gcc-$GCC_VERSION/mpc"

rm -rf gcc-build
mkdir gcc-build
cd gcc-build
"../gcc-$GCC_VERSION/configure" "--prefix=$PREFIX" "--target=$TARGET" \
    --disable-nls --enable-languages=c --without-headers --disable-shared \
    --with-newlib

make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

cd ..

wget -nc "ftp://sourceware.org/pub/newlib/newlib-$NEWLIB_VERSION.tar.gz"
tar xvzf "newlib-$NEWLIB_VERSION.tar.gz"
rm -rf newlib-build
mkdir newlib-build
cd newlib-build
../newlib-2.1.0/configure "--target=$TARGET" "--prefix=$PREFIX"
make all
make install

