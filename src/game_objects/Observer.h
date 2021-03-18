#ifndef OBSERVER_H
#define OBSERVER_H

template<class... Targs>
class iObserver {
public:
        virtual ~iObserver() = default;
        virtual void on_notify(Targs...) = 0;
};

#endif /* OBSERVER_H */ 