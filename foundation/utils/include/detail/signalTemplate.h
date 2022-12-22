
#define SIGNAL_FUNCTION         BASE_JOIN(TSignal, SIGNAL_NUMBER)
#define DELEGATE_FUNCTION       BASE_JOIN(TDelegate, SIGNAL_NUMBER)

template <SIGNAL_CLASS_TYPES>
class SIGNAL_FUNCTION {
public:
    typedef DELEGATE_FUNCTION<void SIGNAL_TYPES_COMMA > Proc;

private:
    typedef struct Slot_{
        Proc proc;
    } Slot;

    typedef std::list<Slot> SlotList;
    typedef typename SlotList::const_iterator SlotIterator;
    SlotList                mSlotList;
    SlotIterator            mCurrentSlot;
    std::recursive_mutex    mSlotMutex;
public:
    SIGNAL_FUNCTION(int32_t maxSlots = 1) : mCurrentSlot(mSlotList.end()) {
    }

    SIGNAL_FUNCTION(const SIGNAL_FUNCTION &rhs) {
        mSlotList = rhs.mSlotList;
        mCurrentSlot = mSlotList.end();
    }

    SIGNAL_FUNCTION& operator = (const SIGNAL_FUNCTION & rhs) {
        if (this == &rhs) {
            return *this;
        }
        mSlotList = rhs.mSlotList;
        mCurrentSlot = mSlotList.end();
        return *this;
    }

    int32_t attach(const Proc &proc) {
        if (isAttached(proc)) {
            return -1;
        }

        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        Slot slot;
        slot.proc = proc;
        mSlotList.push_back(slot);
        return mSlotList.size();
    }

    int32_t attach (void (*method)(SIGNAL_TYPE_ARGS)) {
        Proc proc(method);
        return attach(proc);
    }

    template< class X, class Y>
    int32_t attach(void (X::*func)( SIGNAL_TYPE_ARGS ), Y * obj) {
        Proc proc(func, obj);
        return attach(proc);
    }

    template< class X, class Y >
    int32_t attach( void (X::*func)( SIGNAL_TYPE_ARGS ) const,  Y * obj) {
        Proc proc(func, obj);
        return attach(proc);
    }

    int32_t detach(const Proc &proc, bool wait = false) {

        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        SlotIterator iter = mSlotList.begin();
        
        while (iter != mSlotList.end()) {
            if (iter->proc != proc) {
                iter++;
                continue;
            }
            if (iter == mCurrentSlot) {
                mCurrentSlot = mSlotList.erase(iter);
            } else {
                mSlotList.erase(iter);
            }
            return mSlotList.size();
        }
        
        return -1;
    }

    int32_t detach (void (*method)(SIGNAL_TYPE_ARGS), bool wait = false) {
        Proc proc(method);
        return detach(proc, wait);
    }

    template< class X, class Y >
    int32_t detach(Y * obj, void (X::*func)( SIGNAL_TYPE_ARGS), bool wait = false) {
        Proc proc(func, obj);
        return detach(proc, wait);
    }

    template< class X, class Y >
    int32_t detach(Y * obj, void (X::*func)( SIGNAL_TYPE_ARGS ) const, bool wait = false) {
        Proc proc(func, obj);
        return detach(proc, wait);
    }

    void clear() {
        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        mSlotList.clear();
        mCurrentSlot = mSlotList.end();
    }

    void invoke( SIGNAL_TYPE_ARGS ) {
        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        mCurrentSlot = mSlotList.begin();
        while (mCurrentSlot != mSlotList.end()) {
            const Slot &slot = *mCurrentSlot++;
            slot.proc(SIGNAL_ARGS);
        }
    }

    void operator() ( SIGNAL_TYPE_ARGS ) {
        invoke( SIGNAL_ARGS );
    }

    bool empty() {
        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        return mSlotList.empty();
    }

    int32_t size() {
        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        return mSlotList.size();
    }

    bool isAttached(const Proc &proc) {
        std::lock_guard<std::recursive_mutex> guard(mSlotMutex);
        SlotIterator iter = mSlotList.begin();
        while (iter != mSlotList.end()) {
            if (iter++->proc == proc) {
                return true;
            }
        }
        
        return false;
    }
};

#undef  DELEGATE_FUNCTION
#undef  SIGNAL_FUNCTION
#undef  SIGNAL_NUMBER
#undef  SIGNAL_CLASS_TYPES
#undef  SIGNAL_TYPES_COMMA
#undef  SIGNAL_TYPE_ARGS
#undef  SIGNAL_ARGS