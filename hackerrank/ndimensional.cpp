template <typename T>
struct NDimensional {
private:
    vector<int> dimensionSz;
    vector<T> data;
    
public:
    NDimensional() {
    }
    
    NDimensional(const vector<int>& dimensions, T def) {
        if (dimensions.empty()) throw exception();
        
        dimensionSz = vector<int>(dimensions.size());
        dimensionSz[dimensionSz.size() - 1] = 1;
        for (int i = dimensions.size() - 2; i >= 0; --i) {
            dimensionSz[i] = dimensions[i + 1] * dimensionSz[i + 1];
        }
        
        data = vector<T>(dimensions[0] * dimensionSz[0], def);
    }
    
    T& get(const vector<int>& pos) {
        int idx = 0;
        
        for (int i = 0; i < pos.size(); ++i) {
            idx += pos[i] * dimensionSz[i];
        }

        return data[idx];
    }
};
