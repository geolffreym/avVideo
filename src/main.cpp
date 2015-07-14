#include <iostream>
#include "avEncoder.h"

using namespace std;

int main () {
    int my[10] = {22, 3};
    const int *p1 = my; // Value immutable and pointer mutable
    int *const p2 = my; // Pointer immutable and value mutable
    const int *const p3 = my; // Pointer immutable and value immutable

    string filename = "test.mpg";

    avEncoder video = avEncoder ();

    if ( video.setCodec (video.CODEC_MPEG4)) {
        video.setBitRate (10);
        video.setFps (25);
        video.setVideoFile (filename);
    }

    video.openCodec ();

    return 0;
}