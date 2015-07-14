//
// Created by gmena on 7/14/15.
//

#ifndef AVVIDEO_AVENCODER_H
#define AVVIDEO_AVENCODER_H

#include "avVideo.h"

class avEncoder : public avVideo {
public:
    //Is allocated? Flag
    bool allocated = false;

    bool allocate ();

    bool encode (string file);
};


#endif //AVVIDEO_AVENCODER_H
