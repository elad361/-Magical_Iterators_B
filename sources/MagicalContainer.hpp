/**
* AUTHOR: Elad Shoham
*/
#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace ariel {

    class MagicalContainer {
    
    public:
    
       // Basic class of iterator
        class Iterator {
        private:
        public:
            Iterator() {}
            Iterator(const Iterator& other) {};
            Iterator(Iterator&& other) = delete;
            Iterator& operator=(Iterator&& other) = delete;
            Iterator& operator=(const Iterator& other) {return *this;}
            virtual ~Iterator() {}

            // Notify an element added to the container
            virtual void elementAdded(int ind) = 0;

            // Notify an element was removed from the container
            virtual void elementRemoved(int ind) = 0;
        };

        class AscendingIterator : public Iterator {
        private:
            MagicalContainer* container;
            int index;
        public:
            // Constructors
            AscendingIterator() : container(nullptr), index(0) {}
            AscendingIterator(MagicalContainer& cont, int ind = 0) : container(cont.addObserver(this)), index(ind) {}

            AscendingIterator(const AscendingIterator& other) : container(other.container), index(other.index) {
                if (container != nullptr) {
                    container->addObserver(this);
                }
            }

            AscendingIterator(AscendingIterator&& other) = delete;
            AscendingIterator& operator= (AscendingIterator&& other) = delete;

            // Destructor
            ~AscendingIterator() override {
                if (container != nullptr) {
                    container->removeObserver(this);
                }
            }

            AscendingIterator& operator= (const AscendingIterator& other) ;
            
            bool operator== (const AscendingIterator& other) const ;

            bool operator!= (const AscendingIterator& other) const ;

            bool operator<(const AscendingIterator& other) const ;
            
            bool operator>(const AscendingIterator& other) const ;

            int operator*() const ;

            AscendingIterator& operator++() ;

            int getIndex() const {return index;}

            // Notify an element added to the container
            void elementAdded(int ind) override;

            // Notify an element was removed from the container
            void elementRemoved(int ind) override;
            
            AscendingIterator begin() {return AscendingIterator(*container);}

            AscendingIterator end() {return AscendingIterator(*container, container->size());}
        protected:
            MagicalContainer* getContainer() const {return container;}

        };

        class SideCrossIterator : public Iterator {
        private:
            MagicalContainer* container;
            int forwardIndex, backwardIndex;
            bool isForward;
        public:
            // Constructors
            SideCrossIterator() : container(nullptr), forwardIndex(0), backwardIndex(0), isForward(true) {}
            //Flag = 1 means end iterator
            SideCrossIterator(MagicalContainer& cont, ushort flag = 0) : container(cont.addObserver(this)), forwardIndex(0), backwardIndex(cont.size() - 1), isForward(true) {
                if (flag == 1) {
                    if (container->size() % 2 == 0) {
                        forwardIndex = container->size() / 2;
                        backwardIndex = (container->size() / 2) - 1;
                    }
                    else {
                        forwardIndex = (container->size() / 2) + 1;
                        backwardIndex = (container->size() / 2);
                    }
                }
            }

            SideCrossIterator(const SideCrossIterator& other) : container(other.container), forwardIndex(other.forwardIndex), backwardIndex(other.backwardIndex), isForward(other.isForward) {
                if (container != nullptr) {
                    container->addObserver(this);
                }
            }

            SideCrossIterator(SideCrossIterator&& other) = delete;
            SideCrossIterator& operator= (SideCrossIterator&& other) = delete;

            // Destructors
            ~SideCrossIterator() override {
                if (container != nullptr) {
                    container->removeObserver(this);
                }
            }

            SideCrossIterator& operator= (const SideCrossIterator& other) ;
            
            bool operator== (const SideCrossIterator& other) const ;

            bool operator!= (const SideCrossIterator& other) const ;

            bool operator<(const SideCrossIterator& other) const ;
            
            bool operator>(const SideCrossIterator& other) const ;

            int operator*() const ;

            SideCrossIterator& operator++() ;
            
            SideCrossIterator begin() {return SideCrossIterator(*container);}

            SideCrossIterator end() {return SideCrossIterator(*container, 1);}

            void elementAdded(int ind) override {}

            void elementRemoved(int ind) override {}
        };

        class PrimeIterator : public Iterator {
        private:
            MagicalContainer* container;
            int index;
        
        public:
            // Constructors
            PrimeIterator() : container(nullptr), index(0) {}
            PrimeIterator(MagicalContainer& cont, int ind = 0) : container(cont.addObserver(this)), index(ind){}
            PrimeIterator(const PrimeIterator& other) : container(other.container), index(other.index) {
                if (container != nullptr) {
                    container->addObserver(this);
                }
            }

            PrimeIterator(PrimeIterator&& other) = delete;
            PrimeIterator& operator= (PrimeIterator&& other) = delete;

            // Destructor
            ~PrimeIterator() override {
                if (container != nullptr) {
                    container->removeObserver(this);
                }
            }

            
            PrimeIterator& operator= (const PrimeIterator& other) ;
            bool operator== (const PrimeIterator& other) const ;
            bool operator!= (const PrimeIterator& other) const ;
            bool operator<(const PrimeIterator& other) const ;
            bool operator>(const PrimeIterator& other) const ;
            PrimeIterator& operator++() ;
            int operator*() const ;

            void elementAdded(int ind) override;

            void elementRemoved(int ind) override;

            PrimeIterator begin() {return PrimeIterator(*container);}
            PrimeIterator end() {return PrimeIterator(*container, (int)container->primes.size());}
        };
        
        void addElement(int val);

        void removeElement(int val);

        int size() const;

        void print() {
            for (const auto& val : elements) {
                cout << val << " ";
            }
            cout << endl;
        }

        void printPrimes() {
            for (const auto& val : primes) {
                cout << val << " ";
            }
            cout << endl;
        }
        
        MagicalContainer* addObserver(Iterator* iter);
        void removeObserver(Iterator* iter);
        
    private:
       vector<int> elements;
       vector<int> primes;
       vector<MagicalContainer::Iterator *> observers;

       bool isPrime(int val) const;
    };
};