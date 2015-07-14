#include <iostream>
#include "video.h"

using namespace std;

int main () {
    avVideo video = avVideo ();

    if ( video.setCodec (video.CODEC_FLV)) {
        video.setBitRate (10);
        video.setFps (25);
    }
    return 0;
}