

// template<class T, int SIZE>
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
// template<>
// constexpr T find<T,0>(const T* cont const T&searched)
//{
//    return T{};//find<T>(cont, size -1, searched);
//}
#include <array>
#include <iostream>
#include <ostream>
#include <tuple>
template <int SIZE> struct Loop {

  template <class T>
  constexpr void iterate(const T *array, const T &search) const {
    for (int i = 0; i < SIZE; i++) {
      if (array[i] == search) {
        std::cout << "Jest na " << i << " ";
      }
    }
  }
};

template <size_t SIZE, class T> struct Array {
  T _array[SIZE ? SIZE : 1];

  constexpr const T &operator[](size_t __n) const { return _array[__n]; }
  T &operator[](size_t __n) { return _array[__n]; }

  constexpr const T &begin(void) const { return _array[0]; }
  constexpr T begin(void) { return _array[0]; }

  constexpr const T &end(void) const { return _array[SIZE - 1]; }
  constexpr T end(void) { return _array[SIZE - 1]; }
};
/*Operators*/
template <size_t SIZE, typename T>
std::ostream &operator<<(std::ostream &out, const Array<SIZE, T> &c) {
  out << "Array = [";
  for (auto i = c.begin(); i != c.end(); i++) {
    out << i << "\n";
  }
  out << " ]";
  return out;
}
template <size_t SIZE, typename T>
constexpr bool operator==(const Array<SIZE, T> &rhs,
                          const Array<SIZE, T> &lhs) {
  constexpr auto i_rhs = rhs.begin();
  constexpr auto i_lhs = lhs.begin();
  constexpr auto e_rhs = rhs.end();
  constexpr auto e_lhs = lhs.end();
  for (; i_rhs != i_rhs, i_lhs != e_lhs; i_rhs++, e_rhs++) {
    constexpr bool same = ((i_rhs) == (i_lhs));
    if (!same) {
      return false;
    }
  }
  return true;
}

template <size_t index, std::size_t _size, typename _Type>
constexpr const _Type &get(const Array<_size, _Type> &array) {
  return array[index];
}

template <size_t index, std::size_t _size, typename _Type>
constexpr _Type &get(Array<_size, _Type> &array) {
  return array[index];
}
/*~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!*/
template <class KeyType, class ValueType> struct Pair {
  constexpr Pair(KeyType key, ValueType value) : key(key), value(value){};
  KeyType key;
  ValueType value;
};
// template <typename T1, typename T2>
// bool &operator
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &out, const Pair<T1, T2> &p) {
  out << "Pair[ key=" << p.key << "| value=" << p.value << "]";
  return out;
}

template <typename T1, typename T2>
constexpr bool operator==(const Pair<T1, T2> &rhs, const Pair<T1, T2> &lhs) {
  constexpr auto same_key = (rhs.key == lhs.key);
  constexpr auto same_value = (rhs.value == lhs.value);
  return (same_key & same_value);
}
template <typename T1, typename T2>
constexpr bool operator!=(const Pair<T1, T2> &rhs, const Pair<T1, T2> &lhs) {
  return !(rhs == lhs);
}
template <typename _T1, typename _T2>
constexpr Pair<_T1, _T2> make_pair(_T1 &&t1, _T2 &&t2) {
  return Pair<_T1, _T2>(static_cast<_T1 &&>(t1), static_cast<_T2 &&>(t2));
}

struct C {
  int a;
  float f;
  double g;
  constexpr C(int _a, float _f, double _g) : a(_a), f(_f), g(_g){};
};
std::ostream &operator<<(std::ostream &out, const C &c) {
  out << "C[a=" << c.a << "| f=" << c.f << "| g=" << c.g << "]";
  return out;
}
constexpr bool operator==(const C &rhs, const C &lhs) {
  auto same_a = (rhs.a == lhs.a);
  auto same_f = (rhs.f == lhs.f);
  auto same_g = (rhs.g == lhs.g);
  return (same_a & same_g & same_f);
}
template <typename T1, typename T2>
constexpr bool operator!=(const Pair<T1, T2> &rhs, const Pair<T1, T2> &lhs) {
  return !(rhs == lhs);
}
int main() {

  constexpr size_t size = 2;
  constexpr Array<size, int> array = {1, 2};
  for (size_t i = 0; i < size; i++) {
    const auto a = i + 1;
    if ((array[i] != a)) {
      std::cout << "array[i] != i | " << array[i] << " != " << a << "\n";
      return -1;
    }
  }
  using IntPair = Pair<int, int>;
  constexpr Array<size, IntPair> pair_array = {make_pair(1, 2),
                                               make_pair(3, 4)};
  std::cout << pair_array[0].key << " " << pair_array[0].value << " \n";
  std::cout << pair_array[1].key << " " << pair_array[1].value << " \n";

  using CPair = Pair<C, C>;
  constexpr auto abc = make_pair(C(1, 2, 3), C(4, 5, 6));
  {
    constexpr Array<size, CPair> c_pair = {
        make_pair(C(1, 2, 3), C(4, 5, 6)),
        make_pair(C(7, 8, 9), C(10, 11, 12))};

    constexpr Array<size, CPair> c_pair2 = {
        make_pair(C(1, 2, 3), C(4, 5, 6)),
        make_pair(C(7, 8, 9), C(10, 11, 12))};
    std::cout << (c_pair == c_pair2);
  }
  // std::cout << c_pair;
  return 0;
}
