//
// Created by 付旭炜 on 2017/10/11.
//

#include "FmailyTree.h"

#include <iostream>

/*
 * 得到需要处理的成员并判断异常
 */
//Member* get_processing_father(const std::string&function_name, const std::string& cannot_found,
//                              Member* ances, const std::string& to_find) {
//    auto processing = ances->find(to_find);
//    if (processing == nullptr) {
//        std::cout <<
//    }
//}

void FmailyTree::add_child(Member *father, const std::string &name) {
    if (father == nullptr) {
        std::cout << "Father in Family::addchild is empty\n";
        exit(-1);
    }
    father->add_child(name);
}

void FmailyTree::create_family() {
    std::string father_name; // 祖先的名称
    std::cout << "选择要建立家族的人的姓名\n";
    std::cin >> father_name;

//    auto father_ptr = ancestor->find(father_name);
    auto father_ptr = find(ancestor, father_name);
    // father_ptr情况分支处理
    if (father_ptr == nullptr) {
        std::cout << "要创建家庭的成员不存在" << std::endl;
        return;
    } else if (father_ptr->childs) {
        // 已经存在家庭
        std::cout << father_ptr->name << "已经存在家庭\n";
    }

    std::cout << "请输入" <<  father_name << "的子女人数";
    int family_members;
    std::cin >> family_members;

    std::cout << "依次输入儿女姓名: ";
    std::vector<std::string> childs;
    for (int i = 0; i < family_members; ++i) {
        std::string cur_name;
        std::cin >> cur_name;
        father_ptr->add_child(cur_name);
        childs.push_back(cur_name);
    }

    // output
    std::cout << father_name <<"的子女是：";
    for (const auto&s: childs) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
}

void FmailyTree::add_children() {
    std::string father_name;
    std::cout << "请选择要添加儿女的人的姓名\n";
    std::cin >> father_name;

    auto father_ptr = find(ancestor, father_name);
    // father_ptr情况分支处理
    if (father_ptr == nullptr) {
        std::cout << "要添加子女的成员不存在" << std::endl;
        return;
    }

    std::cout << "请填入" <<  father_name << "新添加的儿女的姓名\n";
    std::string new_child;
    std::cin >> new_child;
    father_ptr->add_child(new_child);
    std::cout << father_name << "新添加的儿女的姓名是" << new_child;
}

void FmailyTree::modify_name() {
    std::cout << "请输入要更名的人目前的姓名\n";
    std::string processing_name;
    std::cin >> processing_name;
    auto processing_ptr = find(ancestor, processing_name);
    if (processing_ptr == nullptr) {
        std::cout << "要更名的成员不存在" << std::endl;
        return;
    }
    std::cout << "请输入要更名的人("<<processing_name<<")目前的姓名\n";
    std::string new_name;
    std::cin >> new_name;

    std::cout <<processing_name<<"已经更名为"<<new_name;
    processing_ptr->change_name(new_name);
}

void FmailyTree::break_family() {
    std::string processing_name;
    std::cout << "请输入要解散家族的人的姓名";
    std::cin >> processing_name;
    std::cout << "要解散家族的人的姓名是: " << processing_name;

    auto processing_ptr = find(ancestor, processing_name);
    if (processing_ptr == nullptr) {
        std::cout << "要解散家庭的成员不存在" << std::endl;
        return;
    }

    if (processing_ptr->childs == nullptr) {
        std::cout << "这个可怜的孩子已经没家庭了，请放过他吧\n";
        return;
    }
#ifdef FAMILY_TREE_DEBUG
    show_family();
#endif
    processing_ptr->clear_childs_recursive();
}

FmailyTree *FmailyTree::build_family_tree() {
    std::string ances_name;
    std::cout << "请输入祖先的姓名\n";
    std::cin >> ances_name;
    auto family_tree = new FmailyTree(ances_name);
    std::cout << "此家谱的祖先是" << family_tree->ancestor->name << '\n';
    return family_tree;
}

Member *FmailyTree::find(Member *member_ptr, const std::string &name) {
    auto ptr = member_ptr;
    while (ptr) {
        // 在自身上查找
        if (ptr->name == name) {
            return ptr;
        }
        // 在节点中查找
        if (!(ptr->isLeaf())) {
//            auto search = ptr->childs->find(name);
            auto search = find(ptr->childs, name);
            if (search) {
                return search;
            }
        }
        ptr = ptr->siblings;
    }
    // 没找到
    return nullptr;
}

void FmailyTree::show_family(Member *father) {
    auto ptr = father;
    // 本层输出
    while (ptr) {
        std::cout << ptr->name << ' ';
        ptr = ptr->siblings;
    }
    std::cout << '\n';
    ptr = father;
    while (ptr) {
        if (!(ptr->isLeaf()))
            show_family(ptr->childs);
        ptr = ptr->siblings;
    }
}

void FmailyTree::clear_children_recursively(Member *father) {
    if (father == nullptr || father->isLeaf()) {
        return;
    } else {
        auto child = father->childs;
        // 迭代 + 递归，有儿子就先删除所有儿子再删除自身，走向下一个兄弟
        while (child) {
//            child->clear_childs_recursive();
            clear_children_recursively(child);
            auto next_sibling = child->siblings;
            delete child;
            child = next_sibling;
        }
    }
}


/*
 * 输入可以保证合理
 */
Member *Member::add_child(const std::string &name) {
    auto new_child = new Member(this, name);
    if (childs == nullptr) {
        childs = new_child;
    } else {
        auto old_childs = childs;
        childs = new_child;
        new_child->siblings = old_childs;
    }
    return new_child;
}

/*
 * 由于这可能是一个带有多兄弟的节点，所以可能不要这样查找
 */
//Member *Member::find_sibling(const std::string &name) {
//    auto curp = this;
//    while (curp) {
//        if (curp->name == name) {
//            break;
//        } else {
//            curp = curp->siblings;
//        }
//    }
//    return curp;
//}

/*
 * 从儿子节点返回目标(返回的是查找到的第一个)
 */
//Member *Member::find_from_childs(const std::string &name) {
//    if (this->childs) {
//        return this->childs->find(name);
//    } else {
//        return nullptr;
//    }
//}

void Member::clear_childs_recursive() {
    if (isLeaf()) {
        return;
    } else {
        auto child = childs;
        // 迭代 + 递归，有儿子就先删除所有儿子再删除自身，走向下一个兄弟
        while (child) {
            child->clear_childs_recursive();
            auto next_sibling = child->siblings;
            delete child;
            child = next_sibling;
        }
    }
    childs = nullptr;
}

void Member::show_family() {
    auto ptr = this;
    // 本层输出
    while (ptr) {
        std::cout << ptr->name << ' ';
        ptr = ptr->siblings;
    }
    std::cout << '\n';
    ptr = this;
    while (ptr) {
        if (!isLeaf())
            ptr->childs->show_family();
        ptr = ptr->siblings;
    }
}
