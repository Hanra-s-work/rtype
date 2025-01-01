/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Rect.cpp
*/

#include "Recoded/Rect.hpp"

template <typename T>
Recoded::Rect<T>::Rect() : position({ 0,0 }), size({ 0,0 }) {};

template <typename T>
Recoded::Rect<T>::Rect(std::pair<T, T> position, std::pair<T, T> size)
    : position(position), size(size)
{
}

template <typename T>
template <typename U>
constexpr Recoded::Rect<T>::operator Rect<U>() const
{
    return Rect<U>(
        std::pair<U, U>(static_cast<U>(position.first), static_cast<U>(position.second)),
        std::pair<U, U>(static_cast<U>(size.first), static_cast<U>(size.second))
    );
}

template <typename T>
constexpr bool Recoded::Rect<T>::contains(std::pair<T, T> point) const
{
    return point.first > position.first && point.first < (position.first + size.first) &&
        point.second > position.second && point.second < (position.second + size.second);
}

template <typename T>
std::optional<Recoded::Rect<T>> Recoded::Rect<T>::findIntersection(const Rect<T> &rect) const
{
    T x_intersection_min = std::max(position.first, rect.position.first);
    T y_intersection_min = std::max(position.second, rect.position.second);
    T x_intersection_max = std::min(position.first + size.first, rect.position.first + rect.size.first);
    T y_intersection_max = std::min(position.second + size.second, rect.position.second + rect.size.second);

    if (x_intersection_min < x_intersection_max && y_intersection_min < y_intersection_max) {
        PRETTY_INFO << "Intersection found, returning new rect instance." << std::endl;
        return Rect<T>(
            std::pair<T, T>(x_intersection_min, y_intersection_min),
            std::pair<T, T>(x_intersection_max - x_intersection_min, y_intersection_max - y_intersection_min)
        );
    } else {
        PRETTY_WARNING << "No Intersections were found." << std::endl;
        return std::nullopt;
    }
}

template <typename T>
std::pair<T, T> Recoded::Rect<T>::getCenter() const
{
    return { position.first + size.first / 2, position.second + size.second / 2 };
}

template <typename T>
constexpr bool Recoded::operator==(const Recoded::Rect<T> &lhs, const Recoded::Rect<T> &rhs)
{
    return lhs.position == rhs.position && lhs.size == rhs.size;
}

template <typename T>
constexpr bool Recoded::operator!=(const Recoded::Rect<T> &lhs, const Recoded::Rect<T> &rhs)
{
    return !(lhs == rhs);
}

template class Recoded::Rect<int>;
template bool Recoded::operator==(const Recoded::Rect<int> &lhs, const Recoded::Rect<int> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<int> &lhs, const Recoded::Rect<int> &rhs);

template class Recoded::Rect<long int>;
template bool Recoded::operator==(const Recoded::Rect<long int> &lhs, const Recoded::Rect<long int> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<long int> &lhs, const Recoded::Rect<long int> &rhs);

template class Recoded::Rect<long long int>;
template bool Recoded::operator==(const Recoded::Rect<long long int> &lhs, const Recoded::Rect<long long int> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<long long int> &lhs, const Recoded::Rect<long long int> &rhs);

template class Recoded::Rect<unsigned int>;
template bool Recoded::operator==(const Recoded::Rect<unsigned int> &lhs, const Recoded::Rect<unsigned int> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<unsigned int> &lhs, const Recoded::Rect<unsigned int> &rhs);

template class Recoded::Rect<unsigned long int>;
template bool Recoded::operator==(const Recoded::Rect<unsigned long int> &lhs, const Recoded::Rect<unsigned long int> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<unsigned long int> &lhs, const Recoded::Rect<unsigned long int> &rhs);

template class Recoded::Rect<unsigned long long int>;
template bool Recoded::operator==(const Recoded::Rect<unsigned long long int> &lhs, const Recoded::Rect<unsigned long long int> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<unsigned long long int> &lhs, const Recoded::Rect<unsigned long long int> &rhs);

template class Recoded::Rect<float>;
template bool Recoded::operator==(const Recoded::Rect<float> &lhs, const Recoded::Rect<float> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<float> &lhs, const Recoded::Rect<float> &rhs);

template class Recoded::Rect<double>;
template bool Recoded::operator==(const Recoded::Rect<double> &lhs, const Recoded::Rect<double> &rhs);
template bool Recoded::operator!=(const Recoded::Rect<double> &lhs, const Recoded::Rect<double> &rhs);
