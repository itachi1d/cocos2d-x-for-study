#ifndef _TSINGLETON_H_
#define _TSINGLETON_H_

using namespace std; 
template <typename T>
class TSingleton
{
public:
    static T& Instance()
    {
        static T s_Instance;
        return s_Instance;
    }

protected: 
    TSingleton(void) {}
    ~TSingleton(void) {}

private:
    TSingleton(const TSingleton& rhs) {}
    TSingleton& operator = (const TSingleton& rhs) {}
};

#endif