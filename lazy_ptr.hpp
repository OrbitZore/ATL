template<class T>
struct lazy_ptr:public unique_ptr<T>{
  using unique_ptr<T>::unique_ptr;
  T*& operator->(){
      if (*this==nullptr) this->reset(new T());
      return this->get();
    }
  T& operator*(){
      if (*this==nullptr) this->reset(new T());
      return *(this->get());
    }
};
