#pragma once

#include <mutex>
#include "../sstd_library.hpp"

namespace sstd {

    class GCMemoryManager;
    class GCMemoryManagerPrivate;
    class GCMemoryNode;
    class GCMemoryNodeChildrenWalker;

    class gc_lock{
        GCMemoryManager * thisData;
    public:
        gc_lock(const gc_lock &)=delete;
        gc_lock(gc_lock &&)=delete;
        gc_lock&operator=(const gc_lock &)=delete;
        gc_lock&operator=(gc_lock&&)=delete;
    public:
        inline ~gc_lock();
        template<typename T>
        inline gc_lock(T &&);
    private:
        sstd_class(gc_lock);
    };

    enum class GCMemoryNodeState : unsigned char {
        Black = 2,
        Gray,
        White,
        IsDeleted
    };

    class SSTD_SYMBOL_DECL GCMemoryNodeChildrenWalker final {
        void * data;
        friend class GCMemoryManagerPrivate;
    private:
        GCMemoryNodeChildrenWalker(void *);
    public:
        void findChild(GCMemoryNode *);
    };

    class ReallyGCMemoryNodeWatcher;
    class SSTD_SYMBOL_DECL GCMemoryNodeWatcher {
        friend class GCMemoryManager;
        friend class GCMemoryManagerPrivate;
        friend class GCMemoryNode;
        friend class GCMemoryNodeChildrenWalker;
    private:
        GCMemoryManager * manager;
        GCMemoryNode * node;
        GCMemoryNodeState state;
    public:
        inline GCMemoryManager * getManager() const {
            return manager;
        }
        inline GCMemoryNodeState getState() const {
            return state;
        }
        ~GCMemoryNodeWatcher();
        GCMemoryNodeWatcher();
    private:
        sstd_class(GCMemoryNodeWatcher);
    };

    class SSTD_SYMBOL_DECL GCMemoryNode {
        GCMemoryNodeWatcher * thisWatcher{ nullptr };
        friend class GCMemoryManager;
    private:
        GCMemoryNode(GCMemoryNode&&) = delete;
        GCMemoryNode(const GCMemoryNode&) = delete;
        GCMemoryNode&operator=(GCMemoryNode&&) = delete;
        GCMemoryNode&operator=(const GCMemoryNode &) = delete;
    public:
        virtual ~GCMemoryNode();
        GCMemoryNode(const std::unique_lock<GCMemoryManager> &);
        virtual void directChildren(GCMemoryNodeChildrenWalker *);
        inline GCMemoryNodeWatcher * getGCMemoryWatcher()const {
            return thisWatcher;
        }
        inline GCMemoryManager * getGCMemoryManager() const {
            return thisWatcher->getManager();
        }
        template<bool = true>
        inline void markAsRoot();
        inline void markAsDeleted();
    private:
        sstd_class(GCMemoryNode);
    };

    class SSTD_SYMBOL_DECL GCMemoryManager {
        GCMemoryManagerPrivate * const thisPrivate;
        GCMemoryManager(const GCMemoryManager &) = delete;
        GCMemoryManager(GCMemoryManager&&) = delete;
        GCMemoryManager&operator=(const GCMemoryManager &) = delete;
        GCMemoryManager&operator=(GCMemoryManager&&) = delete;
        friend class GCMemoryNode;
        friend class ReallyGCMemoryNodeWatcher;
    public:
        void markAsRoot(GCMemoryNode *);
        void removeFromRoot(GCMemoryNode *);
        void gc();
        void markAsDeleted(GCMemoryNode *);
        void moveToAnotherGCManager(GCMemoryManager *);
        void moveToAnotherGCManager(GCMemoryNode *, GCMemoryManager *);
    public:
        void lock()/*暂停gc*/;
        void unlock()/*继续gc*/;
    public:
        template<typename T >
        inline static T * createObject(const std::unique_lock<GCMemoryManager> &);
    private:
        void addNode(GCMemoryNode *);
        void try_gc();
    public:
        GCMemoryManager();
        ~GCMemoryManager();
    private:
        sstd_class(GCMemoryManager);
    };

    template<bool arg>
    inline void GCMemoryNode::markAsRoot() {
        if constexpr (arg) {
            thisWatcher->getManager()->markAsRoot(this);
        } else {
            thisWatcher->getManager()->removeFromRoot(this);
        }
    }

    inline void GCMemoryNode::markAsDeleted() {
        thisWatcher->getManager()->markAsDeleted(this);
    }

    template<typename T1>
    inline T1 * GCMemoryManager::createObject(const std::unique_lock<GCMemoryManager>&arg) {
        using T = std::remove_cv_t< std::remove_reference_t<T1> >;
        return sstd_new<T>(arg);
    }

    inline gc_lock::~gc_lock(){
        thisData->unlock();
    }

    template<typename T1>
    inline gc_lock::gc_lock(T1 && arg){
        using T = std::remove_cv_t< std::remove_reference_t< T1 > > ;
        if constexpr(  ){}
        thisData->lock();
    }

}/*namespace sstd*/


