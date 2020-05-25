#ifndef BLOBBOID.H
#define BLOBBOID.H

#include <vector>
#include "Blob.h"

using namespace std;

class BlobBoid {
    public :
        BlobBoid();

        void update();
        void draw();
    private :
        vector<Blob> bloblets;

};


#endif
