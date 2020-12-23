#ifndef SINGLETON_H
#define SINGLETON_H

#include <cassert>
#include <iostream>

template<typename Type> //Type es la clase
class Singleton
{
    static Type* Instance;

public:
    Singleton()
    {
        /*assert( Instance == nullptr );// no se ha creado un objeto todavia!!
        Instance = static_cast<Type*>(this); //crear singleton
        std::cout<<"Crating Singleton [OK]\n";*/
    }

    static Type& GetSingleton()
    {
        if(Instance == nullptr)
            Instance = new Type();
        return *Instance;
    }
    static Type* GetSingletonPointer()
    {
        if(Instance == nullptr)
            Instance = new Type();
        return Instance;
    }
    virtual ~Singleton()
    {
        Instance = nullptr;
    }

};

template <typename Type>
Type* Singleton<Type>::Instance = nullptr;

#define SINGLETON(T) Singleton< T >::GetSingleton()
#define SINGLETON_DESTROY(T) Singleton< T >::~Singleton()



//#define SINGLETON(T) singleton< T >::mf_sr_get_instance()
//#define SINGLETON_DELETE(T) singleton< T >::mf_s_destroy_singleton()
//template< typename T>T* singleton<T>::md_p_instance = 0;
//#define SINGLETON(T) singleton< T >::mf_sr_get_instance()

#endif // SINGLETON_H
