int getLowerBound(int key){
    if(mm.size() == 0) return -1;
    auto it = mm.lower_bound(key);
    if(it ==mm.end() || it->first > key) it--;
    if(it->first > key) return -1;
    return it->second;
}

int getUpperBound(int key){
    if(mm.size() == 0) return -1;
    auto it = mm.lower_bound(key);
    if(it ==mm.end()) return -1;
    return it->second;
}