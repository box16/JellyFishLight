#pragma once
class SwitchIF
{
public:
    virtual void CheckPress() = 0;
    virtual bool IsSwitched() const = 0;
};