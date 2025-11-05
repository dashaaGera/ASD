#ifndef LIB_DSU_H_
#define  LIB_DSU_H_
class DSU {
	int* _parent;
	size_t _size;
	int* _rank;
public:
	DSU(size_t size);
	~DSU();
	inline size_t size() const;
	inline int parent_index(int) const;
	inline int rank_index(int) const;
	void unite(int, int);
	int find(int);
};

inline size_t DSU::size() const {
	return _size;
}

inline int DSU::parent_index(int i) const {
	return _parent[i];
}
inline int DSU::rank_index(int i) const {
	return _rank[i];
}

#endif  