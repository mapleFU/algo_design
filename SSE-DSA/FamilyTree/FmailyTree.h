//
// Created by 付旭炜 on 2017/10/11.
//

#ifndef FAMILYTREE_FMAILYTREE_H
#define FAMILYTREE_FMAILYTREE_H

#define FAMILY_TREE_DEBUG

#include <vector>
#include <string>

class Member {
public:
    friend class FmailyTree;

    const Member* father;
    std::string name;
    /*
     * is it a leaf node
     */
    inline bool isLeaf() {
        return childs == nullptr;
    }
    Member(const Member* _father, const std::string& _name): father(_father), name(_name){
        siblings = childs = nullptr;
    }
    Member(const Member* _father, std::string&& _name): father(_father), name(_name){
        siblings = childs = nullptr;
    }

    /*
     * 为本个MEMBER更名
     */
    void change_name(const std::string& new_name) {
        name = new_name;
    }
private:
//    Member* find_from_childs(const std::string& name);
//    Member* find_sibling(const std::string&name);
    Member* add_child(const std::string&name);
    Member* siblings;
    Member* childs;
    /*
     * 递归清除自己的子节点
     */
    void clear_childs_recursive();

    void show_family();
};


class FmailyTree {
private:

    // 家族祖先
    Member* ancestor;

    Member* find(Member* member_ptr, const std::string&name);
    void add_child(Member* father, const std::string& name);
    void show_family(Member* father);
    /*
     * 递归删除所有子节点
     */
    void clear_children_recursively(Member* father);
public:
#ifdef FAMILY_TREE_DEBUG
    void show_family() { ancestor->show_family();}
#endif

    explicit FmailyTree(const std::string& ancestor_name) {
        ancestor = new Member(nullptr, ancestor_name);
    }
    /*
     * 创建家庭
     */
    void create_family();
    /*
     * 添加子女
     */
    void add_children();
    /*
     * 修改指定人名
     */
    void modify_name();
    /*
     * 解散家庭
     */
    void break_family();

    ~FmailyTree() {
        ancestor->clear_childs_recursive();
        delete ancestor;
    }
    /*
     * 从输入中构建一颗FamilyTree
     */
    static FmailyTree* build_family_tree();

    /*
     * 根据给出的字符串查找子节点,不能找到则返回nullptr
     */
    Member* find(const std::string& name) { return find(ancestor, name);}
};


#endif //FAMILYTREE_FMAILYTREE_H
