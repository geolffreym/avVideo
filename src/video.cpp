#include "video.h"

void avVideo::setVideoFile (const char filename) {
    this->source_file = filename;
}

void avVideo::setCodec (enum AVCodecID codec_id) {
    this->codec = avcodec_find_encoder (codec_id);
}

AVCodec *avVideo::getCodec () {
    return this->codec;
}