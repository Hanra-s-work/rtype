/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Rect.cpp
*/

#include "MyRecodes/Rect.hpp"

template <typename T>
MyRecodes::Rect<T>::Rect() : position({ 0,0 }), size({ 0,0 }) {};

template <typename T>
MyRecodes::Rect<T>::Rect(std::pair<T, T> position, std::pair<T, T> size)
    : position(position), size(size)
{
}

template <typename T>
template <typename U>
constexpr MyRecodes::Rect<T>::operator Rect<U>() const
{
    return Rect<U>(
        std::pair<U, U>(static_cast<U>(position.first), static_cast<U>(position.second)),
        std::pair<U, U>(static_cast<U>(size.first), static_cast<U>(size.second))
    );
}

template <typename T>
constexpr bool MyRecodes::Rect<T>::contains(std::pair<T, T> point) const
{
    return point.first > position.first && point.first < (position.first + size.first) &&
        point.second > position.second && point.second < (position.second + size.second);
}

template <typename T>
std::optional<MyRecodes::Rect<T>> MyRecodes::Rect<T>::findIntersection(const Rect<T> &rect) const
{
    T x_intersection_min = std::max(position.first, rect.position.first);
    T y_intersection_min = std::max(position.second, rect.position.second);
    T x_intersection_max = std::min(position.first + size.first, rect.position.first + rect.size.first);
    T y_intersection_max = std::min(position.second + size.second, rect.position.second + rect.size.second);

    if (x_intersection_min < x_intersection_max && y_intersection_min < y_intersection_max) {
        PRECISE_INFO << "Intersection found, returning new rect instance." << std::endl;
        return Rect<T>(
            std::pair<T, T>(x_intersection_min, y_intersection_min),
            std::pair<T, T>(x_intersection_max - x_intersection_min, y_intersection_max - y_intersection_min)
        );
    } else {
        PRECISE_WARNING << "No Intersections were found." << std::endl;
        return std::nullopt;
    }
}

template <typename T>
std::pair<T, T> MyRecodes::Rect<T>::getCenter() const
{
    return { position.first + size.first / 2, position.second + size.second / 2 };
}

template <typename T>
constexpr bool MyRecodes::operator==(const MyRecodes::Rect<T> &lhs, const MyRecodes::Rect<T> &rhs)
{
    return lhs.position == rhs.position && lhs.size == rhs.size;
}

template <typename T>
constexpr bool MyRecodes::operator!=(const MyRecodes::Rect<T> &lhs, const MyRecodes::Rect<T> &rhs)
{
    return !(lhs == rhs);
}

template class MyRecodes::Rect<int>;
template bool MyRecodes::operator==(const MyRecodes::Rect<int> &lhs, const MyRecodes::Rect<int> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<int> &lhs, const MyRecodes::Rect<int> &rhs);

template class MyRecodes::Rect<long int>;
template bool MyRecodes::operator==(const MyRecodes::Rect<long int> &lhs, const MyRecodes::Rect<long int> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<long int> &lhs, const MyRecodes::Rect<long int> &rhs);

template class MyRecodes::Rect<long long int>;
template bool MyRecodes::operator==(const MyRecodes::Rect<long long int> &lhs, const MyRecodes::Rect<long long int> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<long long int> &lhs, const MyRecodes::Rect<long long int> &rhs);

template class MyRecodes::Rect<unsigned int>;
template bool MyRecodes::operator==(const MyRecodes::Rect<unsigned int> &lhs, const MyRecodes::Rect<unsigned int> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<unsigned int> &lhs, const MyRecodes::Rect<unsigned int> &rhs);

template class MyRecodes::Rect<unsigned long int>;
template bool MyRecodes::operator==(const MyRecodes::Rect<unsigned long int> &lhs, const MyRecodes::Rect<unsigned long int> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<unsigned long int> &lhs, const MyRecodes::Rect<unsigned long int> &rhs);

template class MyRecodes::Rect<unsigned long long int>;
template bool MyRecodes::operator==(const MyRecodes::Rect<unsigned long long int> &lhs, const MyRecodes::Rect<unsigned long long int> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<unsigned long long int> &lhs, const MyRecodes::Rect<unsigned long long int> &rhs);

template class MyRecodes::Rect<float>;
template bool MyRecodes::operator==(const MyRecodes::Rect<float> &lhs, const MyRecodes::Rect<float> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<float> &lhs, const MyRecodes::Rect<float> &rhs);

template class MyRecodes::Rect<double>;
template bool MyRecodes::operator==(const MyRecodes::Rect<double> &lhs, const MyRecodes::Rect<double> &rhs);
template bool MyRecodes::operator!=(const MyRecodes::Rect<double> &lhs, const MyRecodes::Rect<double> &rhs);
