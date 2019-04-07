
#pragma once

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

    class GCMemoryNodeChildrenWalker {
        void * data;
    public:
        GCMemoryNodeChildrenWalker(void *);
        void findChild(GCMemoryNode *);
    };

    class GCMemoryNodeWatcher {
        friend class GCMemoryManager;
        friend class GCMemoryManagerPrivate;
        friend class GCMemoryNode;
        friend class GCMemoryNodeChildrenWalker;
    private:
        GCMemoryManager * manager{ nullptr };
        GCMemoryNode * node{ nullptr };
        GCMemoryNodeState state;
    public:
        inline GCMemoryManager * getManager() const {
            return manager;
        }
        inline GCMemoryNodeState getState() const {
            return state;
        }
    };

    class GCMemoryNode {
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
        GCMemoryNode(GCMemoryNode *parent);
        virtual void directChildren(GCMemoryNodeChildrenWalker *);
        inline GCMemoryNodeWatcher * getGCMemoryWatcher()const {
            return thisWatcher;
        }
        template<bool = true>
        inline void markAsRoot();
        inline void markAsDeleted();
    };

    class GCMemoryManager {
        GCMemoryManagerPrivate * const thisPrivate;
        GCMemoryManager(const GCMemoryManager &) = delete;
        GCMemoryManager(GCMemoryManager&&) = delete;
        GCMemoryManager&operator=(const GCMemoryManager &) = delete;
        GCMemoryManager&operator=(GCMemoryManager&&) = delete;
        friend class GCMemoryNode;
    public:
        void markAsRoot(GCMemoryNode *);
        void removeFromRoot(GCMemoryNode *);
        void gc();
        void markAsDeleted(GCMemoryNode *);
        void moveToAnotherGCManager(GCMemoryManager *);
    private:
        void addNode(GCMemoryNode *);
    public:
        GCMemoryManager();
        ~GCMemoryManager();
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


