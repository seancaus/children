//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_SINGLETON_H
#define GATESERVER_SINGLETON_H

#include <assert.h>

template <typename T>
class Singleton
{

public:
    Singleton()
    {
        assert(!instance);
        instance = static_cast<T*>(this);
    }

    virtual ~Singleton()
    {
        assert(instance);
        instance = nullptr;
    }

    static T& getInstance()
    {
        return *instance;
    }

    static T* getInstancePtr()
    {
        return instance;
    }

private:
    Singleton(const Singleton<T> &);
    Singleton& operator=(const Singleton<T> &);

protected:
    static T* instance;
};

#endif //GATESERVER_SINGLETON_H
