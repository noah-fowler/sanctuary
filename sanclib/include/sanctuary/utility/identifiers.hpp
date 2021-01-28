#pragma once
#include <atomic>

#include <sanctuary/utility/random.hpp>


namespace snc {


static size_t unique_id() {
    static std::atomic<size_t> last_id{ 0U };
    return (++last_id);
}


}
