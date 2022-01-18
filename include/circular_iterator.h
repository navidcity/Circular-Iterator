#ifndef CIRCULAR_ITERATOR_H
#define CIRCULAR_ITERATOR_H

#include <boost/iterator_adaptors.hpp>
#include <boost/iterator.hpp>

template<class Iterator>
class cycle_iterator
        : public boost::iterator_adaptor<
        cycle_iterator<Iterator>,     // the derived class overriding iterator behavior
        Iterator,       // the base class providing default behavior
        boost::use_default, // iterator value type, will be IteratorBase::value_type
        std::forward_iterator_tag, // iterator category
        boost::use_default  // iterator reference type
        >
{
private:
    using typename boost::iterator_adaptor<cycle_iterator<Iterator>, Iterator, boost::use_default, std::forward_iterator_tag, boost::use_default>::iterator_adaptor_;
    using iterator_adaptor_::base_reference;

    Iterator m_itBegin;
    Iterator m_itEnd;

public:
    cycle_iterator( Iterator itBegin, Iterator itEnd )
        : iterator_adaptor_(itBegin),
          m_itBegin(itBegin),
          m_itEnd(itEnd)
    {}

    auto increment()
    {
        /* Increment the base reference pointer. */
        ++base_reference();

        /* Check if past-the-end element is reached and bring back the base reference to the beginning. */
        if(base_reference() == m_itEnd)
            base_reference() = m_itBegin;
    }

    auto decrement()
    {
        /* Increment the base reference pointer. */
        --base_reference();

        /* Check if past-the-end element is reached and bring back the base reference to the beginning. */
        if(base_reference() == m_itBegin)
            base_reference() = m_itEnd;
    }
};

#endif //CIRCULAR_ITERATOR_H
