#!/bin/bash

if [ -z "${DEV_HOME}" ]; then
    echo "Environment variable \"DEV_HOME\" is missing..."
    echo "Please check wheather you've configured SdlDevEnv script to your command line..."
    exit
fi

SDL_SRC_HOME="${DEV_HOME}/tools/SDL2-2.0.5"
#echo "$SDL_SRC_HOME"

#  configure ; make all ; make install 중 아래와 같은 에러 발생....
#  LTLINK build/libSDL2.la
#  build/.libs/SDL_mirvideo.o: In function `MIR_InitDisplayFromOutput':
#  /home/caelum/workspace/simple_workspace/SDL/tools/SDL2-2.0.5/src/video/mir/SDL_mirvideo.c:258: undefined reference to `mir_output_get_current_mode'
#  collect2: error: ld returned 1 exit status
#  Makefile:147: 'build/libSDL2.la' 타겟에 대한 명령이 실패했습니다
#  make: *** [build/libSDL2.la] 오류 1
#  /bin/bash build-scripts/updaterev.sh
#     LTLINK build/libSDL2.la
#     build/.libs/SDL_mirvideo.o: In function `MIR_InitDisplayFromOutput':
#     /home/caelum/workspace/simple_workspace/SDL/tools/SDL2-2.0.5/src/video/mir/SDL_mirvideo.c:258: undefined reference to `mir_output_get_current_mode'
#     collect2: error: ld returned 1 exit status
#     Makefile:147: 'build/libSDL2.la' 타겟에 대한 명령이 실패했습니다
#     make: *** [build/libSDL2.la] 오류 1




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
