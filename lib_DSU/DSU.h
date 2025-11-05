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
	inline int* parent() const;
	inline int* rank() const;
	void unite(int, int);
	int find(int);
};

inline size_t DSU::size() const {
	return _size;
}

inline int* DSU::parent() const {
	return _parent;
}
inline int* DSU::rank() const {
	return _rank;
}

#endif  