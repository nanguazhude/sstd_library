#pragma once

#include "../sstd_library.hpp"

namespace sstd {

    class GCMemoryManager;
    class GCMemoryManagerPrivate;
    class GCMemoryNode;
    class GCMemoryNodeChildrenWalker;

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
        GCMemoryNode(GCMemoryManager *);
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
        template<typename T   >
        inline T * createObject();
    private:
        void addNode(GCMemoryNode *);
        void try_gc();
    public:
        GCMemoryManager();
        ~GCMemoryManager();
    private:
        sstd_class(GCMemoryManager);
    };

    template<bool \uacfa1 = false>
    class GCMemoryManagerConstructLock {
        GCMemoryNode * const thisNode;
    public:
        inline GCMemoryManagerConstructLock(GCMemoryNode *);
        inline ~GCMemoryManagerConstructLock();
    private:
        sstd_delete_copy_create(GCMemoryManagerConstructLock);
    private:
        sstd_class(GCMemoryManagerConstructLock);
    };

    template<bool \uacfa1>
    inline GCMemoryManagerConstructLock<\uacfa1>::GCMemoryManagerConstructLock(GCMemoryNode * arg) :thisNode(arg) {
        thisNode->markAsRoot<true>();
    }

    template<bool \uacfa1>
    inline GCMemoryManagerConstructLock<\uacfa1>::~GCMemoryManagerConstructLock() {
        if constexpr (\uacfa1 == false) {
            thisNode->markAsRoot<false>();
        }
    }

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

    template<typename T1 >
    inline T1 * GCMemoryManager::createObject() {
        using T = std::remove_cv_t< std::remove_reference_t<T1> >;
        return sstd_new<T>(this);
    }

}/*namespace sstd*/


