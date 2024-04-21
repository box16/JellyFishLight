#pragma once

class RGB{
public:
    RGB(uint8_t red, uint8_t green, uint8_t blue) : red_(red), green_(green), blue_(blue){};
    uint32_t GRB() const {
            return
            (static_cast<uint32_t>(green_) << 16) |
            (static_cast<uint32_t>(red_) << 8) |
            (static_cast<uint32_t>(blue_));
    }
private:
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
};