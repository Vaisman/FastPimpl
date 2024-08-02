#pragma once

#include <cstddef>
#include <utility>
#include <type_traits>

namespace utils
{
    template <class T, std::size_t Size, std::size_t Alignment>
    class FastPimpl {
    public:
        FastPimpl(FastPimpl const& pimpl) noexcept(std::is_nothrow_copy_constructible_v<T>)
            : FastPimpl(*pimpl)
        {
        }

        FastPimpl(FastPimpl&& pimpl) noexcept(std::is_nothrow_copy_constructible_v<T>)
            : FastPimpl(std::move(*pimpl))
        {
        }

        template <typename... Args>
        explicit FastPimpl(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args...>)
        {
            ::new (Wrapper()) T(std::forward<Args>(args)...);
        }

        FastPimpl& operator=(FastPimpl const& pimpl) noexcept(std::is_nothrow_copy_constructible_v<T>)
        {
            if (this != &pimpl) {
                *Wrapper() = *pimpl;
            }
            return *this;
        }

        FastPimpl& operator=(FastPimpl&& pimpl) noexcept(std::is_nothrow_copy_constructible_v<T>)
        {
            if (this != &pimpl) {
                *Wrapper() = std::move(*pimpl);
            }
            return *this;
        }

        T* operator->() noexcept
        {
            return Wrapper();
        }

        T const* operator->() const noexcept
        {
            return Wrapper();
        }

        T& operator*() noexcept
        {
            return *Wrapper();
        }

        T const& operator*() const noexcept
        {
            return *Wrapper();
        }

        ~FastPimpl() noexcept
        {
            Validate<sizeof(T), alignof(T)>();
            Wrapper()->~T();
        }

    private:
        template <std::size_t RealSize, std::size_t RealAlignment>
        static void Validate() noexcept
        {
            static_assert((Alignment % RealAlignment) == 0);
            static_assert(Size >= RealSize);
        }

        T* Wrapper() noexcept
        {
            return reinterpret_cast<T*>(&m_wrapper);
        }

        T const* Wrapper() const noexcept
        {
            return reinterpret_cast<T const*>(&m_wrapper);
        }

    private:
        alignas(Alignment) std::byte m_wrapper[Size];
    };
}