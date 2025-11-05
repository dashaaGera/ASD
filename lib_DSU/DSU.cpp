#include <stdexcept>
#include "../lib_DSU/DSU.h"

DSU::DSU(size_t size): _size(size){
	_parent = new int[_size];
	_rank = new int[_size];
	for (size_t i = 0;i < _size; i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}

}
DSU::~DSU() {
	delete[] _parent;
	delete[] _rank;
}

int DSU::find(int x) {
	if (_parent[x] != x) {
		_parent[x] = find(_parent[x]); 
	}
	return _parent[x];
}

void DSU::unite(int x1, int x2) {
    int rank_x1 = find(x1);
    int  rank_x2 = find(x2);

    if (rank_x1 == rank_x2) return;

    if (_rank[rank_x1] < _rank[rank_x2]) {
        _parent[rank_x1] = rank_x2;
    }
    else if (_rank[rank_x1] > _rank[rank_x2]) {
        _parent[rank_x2] = rank_x1;
    }
    else {
        _parent[rank_x2] = rank_x1;
        _rank[rank_x1]++;
    }
}