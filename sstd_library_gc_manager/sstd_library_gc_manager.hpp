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
        GCMemoryNode(GCMemoryNode *);
        virtual void directChildren(GCMemoryNodeChildrenWalker *);
        inline GCMemoryNodeWatcher * getGCMemoryWatcher()const {
            return thisWatcher;
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

}/*namespace sstd*/


