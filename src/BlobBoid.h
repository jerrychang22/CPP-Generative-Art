#ifndef BLOBBOID_H
#define BLOBBOID_H

#include <vector>
#include "Blob.h"
#include "cinder/Rand.h"

using namespace std;

class BlobBoid {
    public :
        BlobBoid();
        BlobBoid(int n, int x, int y, float knn_size, float bin_size);

        vector<Blob*> findNN(Blob* b, int r);
        void update();
        void draw();
    private :
        int _num_bins = 15;
        int _bin_size;
        vector<Blob*> _blobs;
        vector<Blob*> _gridbins[15][15];
        //Blob controller
};

#endif
