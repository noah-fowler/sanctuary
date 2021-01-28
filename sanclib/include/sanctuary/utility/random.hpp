#pragma once
#include <random>


namespace snc::Static {

static std::random_device random_device;
static std::mt19937       random_generator{ random_device() };

}


namespace snc {

inline unsigned random_int(unsigned min, unsigned max) {
    std::uniform_int_distribution<unsigned> dist{ min, max };
    return dist(snc::Static::random_generator);
}

inline float random_float(float min, float max) {
    std::uniform_real_distribution<float> dist{ min, max };
    return dist(snc::Static::random_generator);
}

}
