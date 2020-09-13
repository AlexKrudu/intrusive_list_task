#pragma once

#include <type_traits>

namespace intrusive
{
    /*
    Тег по-умолчанию чтобы пользователям не нужно было
    придумывать теги, если они используют лишь одну базу
    list_element.
    */
    struct default_tag;

    template <typename Tag = default_tag>
    struct list_element
    {
        list_element(){
            prev = nullptr;
            next = nullptr;
        };


        /* Отвязывает элемент из списка в котором он находится. */
        void unlink(){
            return;
        };
        list_element* prev;
        list_element* next;

    };



    template <typename T, typename Tag = default_tag>
    struct list
    {
        list_element<Tag> _head;
        list_element<Tag> _tail;

        //typedef /*определяется реализацией*/ iterator;
        //typedef /*определяется реализацией*/ const_iterator;

        static_assert(std::is_convertible_v<T&, list_element<Tag>&>,
        "value type is not convertible to list_element");

        list() noexcept = default;
        list(list const&) = delete;
        list(list&&) noexcept;
        ~list(){
            _head = list_element<Tag>();
            _tail = list_element<Tag>();
        };

        list& operator=(list const&) = delete;
        list& operator=(list&&) noexcept;

        void clear() noexcept;

        /*
        Поскольку вставка изменяет данные в list_element
        мы принимаем неконстантный T&.
        */
        void push_back(T& elem) noexcept{
            auto node = static_cast<list_element<Tag>>(elem);
            if (_head == nullptr) {
                _head = &elem;
                _tail = &elem;
            } else {
                auto tail = static_cast<list_element<Tag>>(*_tail);
                tail.next = &node;
                node.prev = &tail;
                node.next = nullptr;
                _tail = &elem;
            }
        };
        void pop_back() noexcept;
        T& back() noexcept{
            return _tail;
        };
        T const& back() const noexcept;

        void push_front(T&) noexcept;
        void pop_front() noexcept;
        T& front() noexcept;
        T const& front() const noexcept;

        bool empty() const noexcept{
            return _head == nullptr;
        };

        //iterator begin() noexcept;
        //const_iterator begin() const noexcept;

        //iterator end() noexcept;
        //const_iterator end() const noexcept;

        //iterator insert(const_iterator pos, T&) noexcept;
        //iterator erase(const_iterator pos) noexcept;
        //void splice(const_iterator pos, list&, const_iterator first, const_iterator last) noexcept;
    };


}