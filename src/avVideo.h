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



#ifndef VIDEO_H
#define    VIDEO_H

#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#ifdef __cplusplus
}
#endif

using namespace std;

class avVideo {

protected:

    AVCodec *codec = nullptr;
    AVCodecContext *codec_context = nullptr;
    AVFrame *frame = nullptr;
    FILE *file = nullptr;
    string source_file;
    bool codec_open = false;

    AVPacket packet ;

    /** Set the video file directory
     * @param filename The full file directory
     * @return void
     * **/
    bool setVideoFile (string filename) {
        this->source_file = filename;
        this->file = fopen (filename.c_str (), "wb");

        if ( !this->file ) {
            cerr << ":: Could not open file: ";
            return false;
        }

        return true;
    }

public:

    //The codecs
    enum Codecs {
        CODEC_MPEG2VIDEO = AV_CODEC_ID_MPEG2VIDEO,
        CODEC_MPEG4 = AV_CODEC_ID_MPEG4,
        CODEC_FLV = AV_CODEC_ID_FLV1,
        CODEC_H264 = AV_CODEC_ID_H264,
        CODEC_THEORA = AV_CODEC_ID_THEORA
    };

    //The pixels format
    //http://www.qnx.com/developers/docs/660/index.jsp?topic=%2Fcom.qnx.doc.screen%2Ftopic%2Fmanual%2Frscreen_window_pixel.html
    enum PXFormat {
        PXF_RGBA = AV_PIX_FMT_RGBA,
        PXF_RGB24 = AV_PIX_FMT_RGB24,
        PXF_YUV420 = AV_PIX_FMT_YUV420P,
        PXF_YUV422 = AV_PIX_FMT_YUV422P,
        PXF_MONOBLACK = AV_PIX_FMT_MONOBLACK,
        PXF_MONOWHITE = AV_PIX_FMT_MONOWHITE,
    };

    avVideo () {
        cout << "** Starting Process **" << endl << endl;
        avcodec_register_all ();
        av_register_all ();
    }

    ~avVideo () {
        cout << "** Proccess end **";
    }

    /** Set the new video codec
     * @param codec_id The codec number
     * @return bool
     * **/
    bool setCodec (int codec_id) {

        if ( !(this->codec = avcodec_find_encoder (( AVCodecID ) codec_id))) {
            cerr << ":: Codec not found" << endl;
            return false;
        }

        cout << "-? Setting context for codec " << this->codec << endl;
        if ( !(this->codec_context = avcodec_alloc_context3 (this->codec))) {
            cerr << ":: Could not allocate codec context \n" << endl;
            return false;
        }

        //Initial private config
        this->codec_context->max_b_frames = 1;
        this->setWidth (0x258);
        this->setHeight (0x190);
        this->setPixelFormat (this->PXF_YUV420);
        this->setGroupFrameSize (0xA); // Constant Group Frames Size

        cout << "-> Context ready " << this->codec << endl << endl;
        return true;
    }

    /**
     * Initialize AvContext to use Codec
     * @param bit_rate The bit rate
     * @return void
     */
    virtual bool openCodec () {

        if ( !this->codec_context ) {
            cerr << ":: No codec context is set" << endl;
            return false;
        }

        cout << "-? Opening codec " << this->codec << endl;
        if ( !(this->codec_open = (avcodec_open2 (this->codec_context, this->codec, NULL) >= 0))) {
            cerr << ":: Could not open codec: " << this->codec << endl;
            return false;
        }

        if ( !(this->frame = avcodec_alloc_frame ())) {
            cerr << ":: Could not allocate video frame" << endl;
            return false;
        }

        this->frame->format = this->codec_context->pix_fmt;
        this->frame->width = this->codec_context->width;
        this->frame->height = this->codec_context->height;

        cout << "-> Codec Open " << this->codec << endl << endl;
        return true;
    }

    /**
     * Set video bit rate time based
     * @param bit_rate The bit rate
     * @return void
     */
    void setBitRate (int bit_rate) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->bit_rate = bit_rate;

        } catch ( const char *msg ) {
            cerr << ":: " << msg << endl;
            exit (1);
        }
    }

    /**
    * Set video width
    * @param w The width
    * @return void
    */
    void setWidth (int w) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->width = w;

        } catch ( const char *msg ) {
            cerr << ":: " << msg << endl;
            exit (1);
        }
    }

    /**
    * Set video width
    * @param w The width
    * @return void
    */
    void setHeight (int h) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->height = h;

        } catch ( const char *msg ) {
            cerr << ":: " << msg << endl;
            exit (1);
        }
    }

    /**
    * Set video frames per second
    * @param second The time in seconds
    * @param frames The frames needed at each second
    * @return void
    */
    void setFps (int seconds, int frames = 1) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->time_base = ( AVRational ) {frames, seconds};

        } catch ( const char *msg ) {
            cerr << ":: " << msg << endl;
            exit (1);
        }
    }

    /**
    * Set video frames group size
    * @param gop_size The frames group size
    * @return void
    */
    void setGroupFrameSize (int gop_size) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->gop_size = gop_size;

        } catch ( const char *msg ) {
            cerr << ":: " << msg << endl;
            exit (1);
        }
    }

    /**
    * Set the pixel format
    * @param second The time in seconds
    * @param frames The frames needed at each second
    * @return void
    */
    void setPixelFormat (int fmt) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->pix_fmt = ( AVPixelFormat ) fmt;

        } catch ( const char *msg ) {
            cerr << ":: " << msg << endl;
            exit (1);
        }

    }

    /** Return Video codec
     * @return AVCodec
     * **/
    AVCodec *getCodec () {
        return this->codec;
    }

};


#endif