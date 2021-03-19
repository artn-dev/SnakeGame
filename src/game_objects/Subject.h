#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"


template<class... Targs>
class iSubject {
public:
        virtual ~iSubject() = default;
        virtual void notify(Targs... args) = 0;
        virtual void subscribe(iObserver<Targs...>* observer) = 0;
};

#endif /* SUBJECT_H */