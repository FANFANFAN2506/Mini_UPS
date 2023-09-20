#include <queue>
#include <unordered_set>
/** 
Support seqnum quick look up, and automatic evict the smallest seqnum if this cache exceeds certain capacity
*/
class seqnum_cache {
 private:
  size_t capacity;
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t> > min_pq;
  std::unordered_set<int64_t> seqnums;

 public:
  seqnum_cache(size_t cap) : capacity(cap) {}
  /** 
      Precondition: contains() return false;
   */
  void add(int64_t seqnum) {
    min_pq.push(seqnum);
    seqnums.emplace(seqnum);
    if (min_pq.size() > capacity) {
      int smallest = min_pq.top();
      min_pq.pop();
      seqnums.erase(smallest);
    }
  }

  bool contains(int64_t seqnum) { return seqnums.count(seqnum) == 1; }
};
