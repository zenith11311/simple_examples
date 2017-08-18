#!/bin/bash

if [ -z "${DEV_HOME}" ]; then
    echo "Environment variable \"DEV_HOME\" is missing..."
    echo "Please check wheather you've configured SdlDevEnv script to your command line..."
    exit
fi

SDL_SRC_HOME="${DEV_HOME}/tools/SDL2-2.0.5"
#echo "$SDL_SRC_HOME"

function clean_tool_sdl() {
    echo "clean up sdl...."
        rm -rf ${SDL_SRC_HOME}
    echo "finished cleaning...."
}

function clean_tool() {
    clean_tool_sdl
}

build_tool
