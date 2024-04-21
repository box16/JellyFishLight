#pragma once
#include <algorithm>

class RGB {
public:
    RGB(uint8_t red, uint8_t green, uint8_t blue)
        : red_(red), green_(green), blue_(blue)
    {  
    }

    uint32_t GRB() const {
        return
            (static_cast<uint32_t>(green_) << 16) |
            (static_cast<uint32_t>(red_) << 8) |
            (static_cast<uint32_t>(blue_));
    }

    RGB operator+(const RGB& other) const {
        return RGB(
            std::min(static_cast<int>(red_) + other.red_, MAX),
            std::min(static_cast<int>(green_) + other.green_, MAX),
            std::min(static_cast<int>(blue_) + other.blue_, MAX)
        );
    }

    RGB operator*(const uint8_t coefficient) const {
        return RGB(
            std::min(static_cast<int>(red_) * coefficient, MAX),
            std::min(static_cast<int>(green_) * coefficient, MAX),
            std::min(static_cast<int>(blue_) * coefficient, MAX)
        );
    }

private:
    static constexpr int MAX = 255;
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
};