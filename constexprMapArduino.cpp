


//template<class T, int SIZE>
// constexpr T find(const T* cont ,const T&searched)
//{
//    if(cont[SIZE] == searched)
//    {
//        return cont[SIZE];
//    }
//    else
//    {
//        return find<T,SIZE-1>(cont, searched);
//    }
//}
//template<>
// constexpr T find<T,0>(const T* cont const T&searched)
//{
//    return T{};//find<T>(cont, size -1, searched);
//}
#include <array>
#include <iostream>
template<int SIZE>
struct Loop
{

    template<class T>
        constexpr void iterate(const T* array, const T&search) const
        {
            for(int i =0;i<SIZE;i++)
            {
                if (array[i] == search)
                {
                    std::cout<<"Jest na " <<i <<" ";
                }
            }
        }

};


template <size_t SIZE, class T>
struct Array
{
    public:
        T _array[SIZE ? SIZE : 1];
    constexpr const T& operator[](size_t __n) const
    {
        return _array[__n];
    }
    T& operator[](size_t __n)
    {
        return _array[__n];
    }
};


template <class KeyType, class ValueType>
class Pair
{
    public:
    constexpr Pair (KeyType key, ValueType value):key(key), value(value){};
    KeyType key{};
    ValueType value{};
    Pair() = default;
    Pair(Pair&) = default;
};

template<int SIZE, class T>
class ConstexprMap
{
    public:
    /*constexpr    ConstexprMap(){}
    constexpr ConstexprMap(Pair<T,T> p):map_(p){}
    constexpr ConstexprMap(Array<SIZE,T> p):map(p){}>*/
    Array<SIZE, T> map;
    //Pair<T,T> map_;//[SIZE];

    constexpr const T& operator[](size_t __n) const
    {
        return map[__n];
    }
    T& operator[](size_t __n)
    {
        return map[__n];
    }

};
/*
template<size_t index, std::size_t _size,  typename _Type>
const _Type& get(const Array<_size, _Type> &array)
{
    return array[index];
}

template<size_t index, std::size_t _size,  typename _Type>
_Type& get(Array<_size, _Type> &array)
{
    return array[index];
}
*/
int main()
{

    constexpr size_t size = 2;
    constexpr Array<size, int> array = {1,2};
    constexpr auto a = array[0];
    constexpr ConstexprMap<size , Array<size,int> >  map = {{1,2}  }; //map(array);
    constexpr auto b = map[1];
    std::cout<<a<<" "<<b[0];
    //constexpr auto a = get<1, 2, int>(map);
    //std::cout<<a;
    //constexpr ConstexprMap<size ,Pair<int,int> > _map(a2);

    return 0;
}
