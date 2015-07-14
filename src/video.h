/**
    Video
    video.h
    Purpose: Base class video ffmpeg encoder for PHP extension

    For you My Brother Ruperma
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
#include <cstddef>
#include <stddef.h>
#include <map>
#include <exception>

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

private:

    AVCodec *codec = nullptr;
    AVCodecContext *codec_context = nullptr;
    AVFrame *frame = nullptr;
    AVPacket *packet = nullptr;
    FILE *file = nullptr;
    string source_file;

    bool codec_open = false;


public:

    enum Codecs {
        CODEC_MPEG2VIDEO = AV_CODEC_ID_MPEG2VIDEO,
        CODEC_MPEG4 = AV_CODEC_ID_MPEG4,
        CODEC_FLV = AV_CODEC_ID_FLV1,
        CODEC_H264 = AV_CODEC_ID_H264,
        CODEC_THEORA = AV_CODEC_ID_THEORA
    };

    enum PXFormat {
        PXF_RGBA = AV_PIX_FMT_RGBA,
        PXF_RGB24 = AV_PIX_FMT_RGB24,
        PXF_YUV420 = AV_PIX_FMT_YUV420P,
        PXF_YUV422 = AV_PIX_FMT_YUV422P,
        PXF_MONOBLACK = AV_PIX_FMT_MONOBLACK,
        PXF_MONOWHITE = AV_PIX_FMT_MONOWHITE,
    };

    avVideo () {
        avcodec_register_all ();
        av_register_all ();
    }

    /** Set the video file directory
     * @param filename The full file directory
     * @return void
     * **/
    bool setVideoFile (const char filename) {
        this->source_file = filename;
        this->file = fopen (filename, 'wb');
        if ( !this->file ) {
            cerr << "Could not open file: " << filename;
            return false;
        }

        return true;
    }

    /** Set the new video codec
     * @param codec_id The codec number
     * @return bool
     * **/
    bool setCodec (int codec_id) {
        this->codec = avcodec_find_encoder (( AVCodecID ) codec_id);

        if ( !this->codec ) {
            cerr << ("Codec not found \n");
            return false;
        }

        cout << "Setting Context for codec " << this->codec << endl;
        this->codec_context = avcodec_alloc_context3 (this->codec);

        if ( !this->codec_context ) {
            cerr << "Could not allocate codec context \n" << endl;
            return false;
        }

        //Initial private config
        this->codec_context->max_b_frames = 1;
        this->setPixelFormat (this->PXF_RGBA);
        this->setGroupFrameSize (10); // Constant Group Frames Size

        return true;
    }

    bool initCodec () {
        cout << "Opening codec " << this->codec << endl;
        return (this->codec_open = (avcodec_open2 (this->codec_context, this->codec, NULL) > 0));
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
            cerr << msg << endl;
        }
    }

    void setWidth (int w) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->width = w;

        } catch ( const char *msg ) {
            cerr << msg << endl;
        }
    }

    void setHeight (int h) {
        try {
            if ( !this->codec_context ) {
                throw "No codec context is set";
            }

            this->codec_context->height = h;

        } catch ( const char *msg ) {
            cerr << msg << endl;
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
            cerr << msg << endl;
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
            cerr << msg << endl;
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
            cerr << msg << endl;
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