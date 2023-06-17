/**
* @AUTHOR: Elad Shoham
*/

#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {

    bool MagicalContainer::isPrime(int val) const {
        if (val <= 1) {
            return false;
        }
        
        for (int i = 2; i <= (val / 2); ++i) {
            if (val % i == 0) {
                return false;
            }
        }
        return true;
    }

    int MagicalContainer::size() const {   
        return this->elements.size();
    }

    void MagicalContainer::addElement(int val) {
        auto it = find(elements.begin(), elements.end(), val);
        
        if (it != elements.end()) {
            // Element already exist
            cout << val << "already exist" << endl;
            return;
        }

        auto insertIt = elements.begin();
        while ((insertIt != elements.end())) {
            if ((*insertIt) > val) {
                break;
            }
            ++insertIt;
        }
        int ind = (insertIt - elements.begin());
        elements.insert(insertIt, val);

        if (isPrime(val)) {
            auto primeIt = primes.begin();
            while ((primeIt != primes.end())) {
                if ((*primeIt) > val) {
                    break;
                }
                ++primeIt;
            }
            // int ind = (primeIt - primes.begin());
            primes.insert(primeIt, val);
        }
        
        for(Iterator* obs : observers) {
            obs->elementAdded(ind);
        }
    }

    void MagicalContainer::removeElement(int val) {
        auto it = find(elements.begin(), elements.end(), val);
        if (it == elements.end()) {
            throw runtime_error("No such element: " + to_string(val));
        }
        int ind = it - elements.begin();
        
        for (Iterator* obs : observers) {
            obs->elementRemoved(ind);
        }

        elements.erase(it);
        
        auto primeIt = find(primes.begin(), primes.end(), val);
        if (primeIt != primes.end()) {
            primes.erase(primeIt);
        }
    }
    
    MagicalContainer* MagicalContainer::addObserver(Iterator* iter) {
        observers.push_back(iter);
        return this;
    }

    void MagicalContainer::removeObserver(Iterator* iter) {
        auto it = find(observers.begin(), observers.end(), iter);
        if (it == observers.end()) {
            throw runtime_error("No such observer");
        }
        observers.erase(it);
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator= (const AscendingIterator& other) {
        if (this != &other) {
            if (container != other.container) {
                throw runtime_error("different containers");
            }

            index = other.index;
        }
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator== (const AscendingIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!= (const AscendingIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index != other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index < other.index;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index > other.index;
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if (container == nullptr) {
            throw runtime_error("no container...");
        }
        if (index >= container->size()) {
            throw runtime_error("out of range iterator");
        }
        return container->elements[(size_t)index];
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if (index >= container->size()) {
            throw runtime_error("out of range");
        }
        ++index;
        return *this;
    }

    void  MagicalContainer::AscendingIterator::elementAdded(int ind) {
        /*if (isEnd) {
            ++index;
            return;
        }

        if (container->size() == 1 && index == 0) {
            return;
        }*/
        
        if (ind <= index) {
            ++index;
        }
    }

    void MagicalContainer::AscendingIterator::elementRemoved(int ind) {
        if (ind < index) {
            --index;
        }
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator= (const PrimeIterator& other) {
        if (this != &other) {
            if (container != other.container) {
                throw runtime_error("different containers");
            }
            
            index = other.index;
        }
        return *this;
     }

    bool MagicalContainer::PrimeIterator::operator== (const PrimeIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index == other.index;
    }

    bool MagicalContainer::PrimeIterator::operator!= (const PrimeIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index != other.index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index < other.index;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        if (container != other.container) {
            throw runtime_error("different containers");
        }

        return index > other.index;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if (index >= container->primes.size()) {
            throw runtime_error("out of range");
        }
        ++index;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
         if (container == nullptr) {
            throw runtime_error("no container...");
        }
        if (index >= container->primes.size()) {
            throw runtime_error("out of range iterator");
        }

        return container->primes[(size_t)index];
    }

    void MagicalContainer::PrimeIterator::elementAdded(int ind) {
        int val = container->elements[(size_t)ind];
        auto it = find(container->primes.begin(), container->primes.end(), val);
        if (it != container->primes.end()) {
            /*if (isEnd) {
                ++index;
                return;
            }*/
            auto primeIndex = it - container->primes.begin();

            /*if (container.primes.size() == 1 && index == 0) {
                return;
            }*/
            
            if (primeIndex <= index) {
                ++index;
            }
        }
    }

    void MagicalContainer::PrimeIterator::elementRemoved(int ind) {
        int val = container->elements[(size_t)ind];
        auto it = find(container->primes.begin(), container->primes.end(), val);

        if (it != container->primes.end()) {
            auto primeIndex = it - container->primes.begin();
            if (primeIndex < index) {
                --index;
            }
        }
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator= (const SideCrossIterator& other) {
        if (container != other.container) {
            throw runtime_error("different containers");
        }
        forwardIndex = other.forwardIndex;
        backwardIndex = other.backwardIndex;
        isForward = other.isForward;

        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator== (const SideCrossIterator& other) const {
        if (other.container != container) {
            throw runtime_error("different containers ");
        }
        
        return (forwardIndex == other.forwardIndex) && (backwardIndex == other.backwardIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator!= (const SideCrossIterator& other) const {
        if (other.container != container) {
            throw runtime_error("different containers ");
        }

        return (forwardIndex != other.forwardIndex) || (backwardIndex != other.backwardIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        if (other.container != container) {
            throw runtime_error("different containers ");
        }
        
        return (forwardIndex < other.forwardIndex) || (backwardIndex > other.backwardIndex);
    }
    
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        if (other.container != container) {
            throw runtime_error("different containers ");
        }
        
        return (forwardIndex > other.forwardIndex) || (backwardIndex < other.backwardIndex);
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (container == nullptr) {
            throw runtime_error("no container...");
        }
        
        if (forwardIndex > backwardIndex) {
            throw runtime_error("out of range");
        }

        if (isForward) {
            return container->elements[(size_t)forwardIndex];
        }
        else {
            return container->elements[(size_t)backwardIndex];
        }
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (forwardIndex > backwardIndex) {
            throw runtime_error("out of range");
        }

        if (isForward) {
            ++forwardIndex;
            isForward = false;
        } else {
            --backwardIndex;
            isForward = true;
        }
        return *this;
    }
}