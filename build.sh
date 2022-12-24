#!/bin/bash

set -e
BASE_PATH=$(dirname $(readlink -f $0))
BUILD_PATH="$BASE_PATH/build"

function usage()
{
  echo "usage: ./build.sh chip_id"
  echo "example: ./build.sh m64x86"
  echo "chip_id: m64x86 dv300"
  echo ""
}

function buildSingle()
{
  PLATFORM=$1
  if [ -d "$BUILD_PATH/$PLATFORM" ]; then
    rm -r "$BUILD_PATH/$PLATFORM"
  fi
  mkdir -pv "$BUILD_PATH/$PLATFORM"
  echo "buildSingle $PLATFORM"

  cd $BUILD_PATH/$PLATFORM
  cmake $BASE_PATH -B$BUILD_PATH/$PLATFORM -DCHIP_ID=$PLATFORM
  make -j
}

if [[ ! $# -eq 1 ]]; then
  usage
  exit 0
fi

case $1 in
  m64x86|dv300)
    buildSingle $1
    ;;
  *)
    usage
    ;;
esac