#pragma once

class RGB
{
public:
    RGB(const uint8_t red,
        const uint8_t green,
        const uint8_t blue)
        : red_(red), green_(green), blue_(blue)
    {
    }

    RGB()
        : red_(0xFF), green_(0xFF), blue_(0xFF)
    {
    }

    RGB operator+(const RGB &other) const
    {
        return RGB(red_ + other.GetRed(),
                   green_ + other.GetGreen(),
                   blue_ + other.GetBlue());
    }

    uint8_t GetRed() const
    {
        return red_;
    }

    uint8_t GetGreen() const
    {
        return green_;
    }

    uint8_t GetBlue() const
    {
        return blue_;
    }

private:
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
};