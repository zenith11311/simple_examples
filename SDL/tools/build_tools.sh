#!/bin/bash

if [ -z "${DEV_HOME}" ]; then
    echo "Environment variable \"DEV_HOME\" is missing..."
    echo "Please check wheather you've configured SdlDevEnv script to your command line..."
    exit
fi

SDL_SRC_HOME="${DEV_HOME}/tools/SDL2-2.0.5"
#echo "$SDL_SRC_HOME"

function build_tool_sdl() {
    echo "building sdl...."
    tar xzvf ${DEV_HOME}/tools/SDL2-2.0.5.tar.gz -C ${DEV_HOME}/tools
    cd $SDL_SRC_HOME ; ./configure ; make all ; make install
    echo "finished building...."
}

function build_tool() {
    build_tool_sdl
}

build_tool
