#ifndef VIRTUALBLOCKDEVICE_H
#define VIRTUALBLOCKDEVICE_H


class virtualblockdevice
{
public:
    virtualblockdevice();
    virtual void input() = 0;
    virtual void output() = 0;
};

#endif // VIRTUALBLOCKDEVICE_H
