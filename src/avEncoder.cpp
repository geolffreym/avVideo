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

    if ( !this->frame ) {
        cerr << ":: No frame is set. Please open the codec" << endl;
        return false;
    }

    int i = 0, y = 0, x = 0, ret = 0, output;

    cout << "-? Encoding " << endl;
    if ( this->setVideoFile (file)) {

        /* encode 1 second of video */
        for ( ; i < 25; i++ ) {
            av_init_packet (&this->packet);
            this->packet.data = NULL;    // packet data will be allocated by the encoder
            this->packet.size = 0;
            fflush (stdout);

            /* Y */
            for ( y = 0; y < this->codec_context->height; y++ ) {
                for ( x = 0; x < this->codec_context->width; x++ ) {
                    this->frame->data[ 0 ][ y * frame->linesize[ 0 ] + x ] = x + y + i * 3;
                }
            }
            /* Cb and Cr */
            for ( y = 0; y < this->codec_context->height / 2; y++ ) {
                for ( x = 0; x < this->codec_context->width / 2; x++ ) {
                    this->frame->data[ 1 ][ y * frame->linesize[ 1 ] + x ] = 128 + y + i * 2;
                    this->frame->data[ 2 ][ y * frame->linesize[ 2 ] + x ] = 64 + x + i * 5;
                }
            }

            this->frame->pts = i;
            /* encode the image */
            ret = avcodec_encode_video2 (this->codec_context, &this->packet, this->frame, &output);

            if ( ret < 0 ) {
                fprintf (stderr, "Error encoding frame\n");
                exit (1);
            }
            if ( output ) {
                printf ("Write frame %3d (size=%5d)\n", i, this->packet.size);
                fwrite (this->packet.data, 1, this->packet.size, this->file);
                av_free_packet (&this->packet);
            }
        }
    }

    return true;
}