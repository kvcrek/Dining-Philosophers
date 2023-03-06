#pragma once

#include <memory>

class Fork : public std::enable_shared_from_this<Fork> {
public:
    std::mutex mutex;

    std::shared_ptr<Fork> getptr();

    [[nodiscard]] static std::shared_ptr<Fork> create();

private:
    Fork() = default;
};
