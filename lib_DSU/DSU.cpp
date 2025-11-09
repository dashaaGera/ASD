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
    int parent_x1 = find(x1);
    int  parent_x2 = find(x2);

    if (parent_x1 == parent_x2) return;

    if (_rank[parent_x1] < _rank[parent_x2]) {
        _parent[parent_x1] = parent_x2;
    }
    else if (_rank[parent_x1] > _rank[parent_x2]) {
        _parent[parent_x2] = parent_x1;
    }
    else {
        _parent[parent_x2] = parent_x1;
        _rank[parent_x1]++;
    }
}