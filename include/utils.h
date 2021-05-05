#include <stdlib.h>

static int random(int min=0, int max=RAND_MAX) {
    return min + (rand() % static_cast<int>(max - min + 1));
}

template<typename T1, typename T2>
static T1 get_random_key(std::map<T1, T2> map) {
    int idx = random(0, map.size() - 1);
    int i = 0;
    
    for (auto x : map) {
        if (i == idx) {
            return x.first;
        }
        i++;
    }

    throw std::runtime_error("Internal error: failed to find matched element in the map.");
}
