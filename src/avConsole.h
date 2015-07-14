//
// Created by gmena on 7/14/15.
//

#ifndef AVVIDEO_AVCONSOLE_H
#define AVVIDEO_AVCONSOLE_H

#include <iostream>

using namespace std;

class avConsole {
public:
    void static logError (string msg) {
        cerr << msg << endl;
    }

    void static logDefault (string msg) {
        cout << msg << endl;
    }

    void static logSuccess (string msg) {
        cout << "\033[0;32m" + msg + "\033[0m" << endl;
    }

    void static logInfo (string msg) {
        cout << "\033[0;33m" << msg << "\033[0m" << endl;
    }

};


#endif //AVVIDEO_AVCONSOLE_H
