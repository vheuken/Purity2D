// I took this code out of SFML and put it in the Purity Namespace
// SFML is under the zlib license. You can check it out at: www.sfml-dev.org

#ifndef PURITY_VECTOR_2_H
#define PURITY_VECTOR_2_H

namespace Purity
{
    template <T>
    class Vector2
    {
    public:
        Vector2();
        Vector2(T x, T y);

        T x;
        T y;
    };

    typedef Vector2<int>          Vector2i;
    typedef Vector2<unsigned int> Vector2u;
    typedef Vector2<float>        Vector2f;

    template <typename T>
    Vector2<T> operator -(const Vector2<T>& right);

    template <typename T>
    Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

    template <typename T>
    Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

    template <typename T>
    Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

    template <typename T>
    Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

    template <typename T>
    Vector2<T> operator *(const Vector2<T>& left, T right);

    template <typename T>
    Vector2<T> operator *(T left, const Vector2<T>& right);

    template <typename T>
    Vector2<T>& operator *=(Vector2<T>& left, T right);

    template <typename T>
    Vector2<T> operator /(const Vector2<T>& left, T right);

    template <typename T>
    Vector2<T>& operator /=(Vector2<T>& left, T right);

    template <typename T>
    bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

    template <typename T>
    bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

    #include "vector2.inl"
}

#endif // PURITY_VECTOR_2_H
