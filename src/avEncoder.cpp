//
// Created by gmena on 7/14/15.
//

#include "avEncoder.h"

/* Allocate an image with size w and h and pixel format pix_fmt,
 * and fill pointers and linesizes accordingly
 *
 * @return bool
 * **/
bool avEncoder::allocate () {
    cout << "-? Allocating frames in buffer " << endl;
    if ( !av_image_alloc (
            this->frame->data,
            this->frame->linesize,
            this->codec_context->width,
            this->codec_context->height,
            this->codec_context->pix_fmt, 32
    ) < 0 ) {
        cerr << "Could not allocate raw picture buffer" << endl;
        return false;
    }

    cout << "-> Allocated frames in buffer " << endl << endl;
    this->allocated = true;
    return true;

}

/* Start Encoding
 *
 * @return bool
 * **/
bool avEncoder::encode (string file) {
    if ( !this->allocated ) {
        cerr << "Buffer not allocated" << endl;
        return false;
    }

    cout << "-? Encoding " << endl;
    if ( this->setVideoFile (file)) {

    }

    return true;
}