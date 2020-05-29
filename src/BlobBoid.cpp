#include <vector>
#include "Blob.h"
#include "BlobBoid.h"
#include <iostream>
#include <unistd.h>

using namespace std;

BlobBoid::BlobBoid(){
}

BlobBoid::BlobBoid(int n, int x, int y, float knn_size, float bin_size){
    //int lens = int (x / bin_size);
    _bin_size = bin_size;
    //_gridbins[num_bins][num_bins] = {};
    for (int i = 0; i < _num_bins; ++i){
        
    }

    for (int i = 0; i < n; ++i){
        Blob* new_blob = new Blob(x*randFloat(), y*randFloat(), 10*randFloat() - 5, 10, 10*randFloat() - 5, 10*randFloat() - 5, Color(randFloat(), randFloat(), randFloat()));
        _blobs.push_back(new_blob); 
        
        _gridbins[int(new_blob->get_pos().y / _bin_size)][int(new_blob->get_pos().x / _bin_size)].push_back(new_blob);
       /* 
        cout << "Boid " << i << " pos: " << new_blob->get_pos() << "\n";
        cout << "Bin: " << new_blob->get_pos().y / _bin_size << "\n";
        cout << "Boid " << i << " initialized" << "\n";
        */
    }

    for (auto b : _blobs){
        b->set_nn(this->findNN(b, 1));
    }
}

vector<Blob*> BlobBoid::findNN(Blob* b, int r){
    vector<Blob*> nn;
    int x_bin = b->get_pos().x / _bin_size;
    int y_bin = b->get_pos().y / _bin_size;

    if (y_bin != 0 && x_bin != 0) 
        for (auto n : _gridbins[y_bin - 1][x_bin - 1]) nn.push_back(n);

    if (y_bin != 0 && x_bin != _num_bins - r)
        for (auto n : _gridbins[y_bin - 1][x_bin + 1]) nn.push_back(n);

    if (y_bin != _num_bins - r && x_bin != 0)
        for (auto n : _gridbins[y_bin + 1][x_bin - 1]) nn.push_back(n);

    if (y_bin != _num_bins - r && x_bin != _num_bins - r) 
        for (auto n : _gridbins[y_bin + 1][x_bin + 1]) nn.push_back(n);

    if (y_bin != 0) 
        for (auto n : _gridbins[y_bin - 1][x_bin]) nn.push_back(n);
    if (y_bin != _num_bins - r)
        for (auto n : _gridbins[y_bin + 1][x_bin]) nn.push_back(n);
    if (x_bin != 0) 
        for (auto n : _gridbins[y_bin][x_bin - 1]) nn.push_back(n);
    if (x_bin != _num_bins - r) 
        for (auto n : _gridbins[y_bin][x_bin + 1]) nn.push_back(n);

    if (x_bin > 0 && x_bin < _num_bins && y_bin > 0 && y_bin < _num_bins){
        for (auto n : _gridbins[y_bin][x_bin]){
            nn.push_back(n);
        }
    }

    return nn;
} 

void BlobBoid::update(){
    
    vector<vec2> vels;
    vec2 v1, v2, v3, v4, v5;
    int x_min, y_min, x_max, y_max;
    x_min = y_min = 0;
    x_max = y_max = 900;
    int x_b, y_b;
    x_b = y_b = 150;
    int v_b = 5;
    int v_m = 15;


    for (auto b : _blobs){
        int nums = this->findNN(b,1).size();
        v1 = vec2(0, 0);
        v2 = vec2(0, 0);
        v3 = vec2(0, 0);
        v4 = vec2(0, 0);
        v5 = vec2(0, 0);

        for (auto n : this->findNN(b, 1)){
                
            v1 += n->get_pos() * (1.0f / nums);        
            
            if (b != n){

                int x = b->get_pos().x - n->get_pos().x;
                int y = b->get_pos().y - n->get_pos().y;
                if ( x*x + y*y < 225 ) v2 -= (n->get_pos() - b->get_pos());
            
                v3 += n->get_vel() * (1.0f / nums);
            }
        }

        if (b->get_pos().x > (x_max - x_b)){
            v4 += vec2( -v_b, 0 );
        }
        if (b->get_pos().x < (x_min + x_b)){
            v4 += vec2( v_b, 0 );
        }
        if (b->get_pos().y > (y_max - y_b)){
            v4 += vec2( 0, -v_b );
        }
        if (b->get_pos().y < (y_min + y_b)){
            v4 += vec2( 0, v_b );
        }

        v1 = 0.01f * (v1 - b->get_pos());
        v3 = 0.13f * v3;
        //vels.push_back(v1);
        //vels.push_back(v2);
        //vels.push_back(v3);
        //vels.push_back(v4);
        //b->update(vels);
        
        float bx = (v1 + v2 + v3 + v4 + b->get_vel()).x;
        float by = (v1 + v2 + v3 + v4 + b->get_vel()).y;
        if (bx > v_m) v5 += vec2(v_m/2, 0);
        if (bx < -v_m) v5 += vec2(-v_m/2, 0);
        if (by > v_m) v5 += vec2(0, v_m/2);
        if (by < -v_m) v5 += vec2(0, -v_m/2);
        
        if (v5.x == 0) v5 += vec2(bx, 0);
        if (v5.y == 0) v5 += vec2(0, by);
        b->set_vel(v5);
        b->update();
        
        /* 
        cout << "Boid " << b << " updated" << "\n";
        cout << "V1: " << v1 << " V2: " << v2 << " V3: " << v3 << " V4: " << v4 << "\n";
        cout << "Pos: " << b->get_pos() << " ; Vel: " << b->get_vel() << "\n"; 
        //usleep(200000);
        //*/
    }

    //update gridbins
    for (int i = 0; i < _num_bins; ++i){
        for (int j = 0; j < _num_bins; ++j){
            if (!_gridbins[i][j].empty()) _gridbins[i][j].clear();
        }
    }

    for (auto b : _blobs){
        int bx = b->get_pos().x;
        int by = b->get_pos().y;
        if (bx > x_min && bx < x_max && by > y_min && by < y_max)
            _gridbins[int(b->get_pos().y / _bin_size)][int(b->get_pos().x / _bin_size)].push_back(b);
    }

    for (auto b : _blobs){
        b->set_nn(this->findNN(b, 1));
    }

    //cout << "\n";
}

void BlobBoid::draw(){
    for (auto b : _blobs){
        b->draw();
    }
}


