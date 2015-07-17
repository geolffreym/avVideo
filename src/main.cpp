/**
*   Created by gmena on 7/14/15.
*   Video
*   Purpose: Base class video ffmpeg encoder for PHP extension
*   For you My Brother Ruperma
** */



/**CODECS ID
* AV_CODEC_ID_MPEG2VIDEO 2
* AV_CODEC_ID_MPEG4 13
* AV_CODEC_ID_FLV1  22
* AV_CODEC_ID_H264 28
* AV_CODEC_ID_THEORA 31
** */

#include <iostream>
#include "avEncoder.h"

using namespace std;

int main () {
    //int my[10] = {22, 3};
    //const int *p1 = my; // Value immutable and pointer mutable
    //int *const p2 = my; // Pointer immutable and value mutable
    //const int *const p3 = my; // Pointer immutable and value immutable

//    int *x, y[5], *ptx; // Pointers
//
//    x = ( int * ) malloc (10); //Alloc ten block in memory for integer
//    ptx = x; // Pointer ptx point to x
//
//    ptx[ 0 ] = 5; // ptx[0] == x[0]
//    ptx[ 1 ] = 2; // ptx[1] == x[1]
//    x[ 2 ] = 3; // x[2] == ptx[2]
//
//    ptx = y; // Change pointer to array
//    ptx[ 2 ] = 3; // ptx[2] == y[2]
//
//
//    cout << x[ 0 ] << endl;
//    cout << x[ 1 ] << endl;
//    cout << *(ptx + 2); // Is like y[2] | (ptx+2) is the direction for position 2 in memory block for Y

    string filename = "test.mpg";

    avEncoder video = avEncoder ();

    if ( video.setCodec (video.CODEC_MPEG4)) {

        //The basic Conf
        video.setBitRate (10);
        video.setFps (25);

        //Open the codec
        if ( video.openCodec ()) {
            if ( video.allocate ()) {
                video.encode (filename);
            }
        }
    }


    return 0;
}