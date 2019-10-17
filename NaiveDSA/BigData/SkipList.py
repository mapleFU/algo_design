"""
https://stackoverflow.com/questions/256511/skip-list-vs-binary-search-tree
"""
from random import random
from typing import List


class SingleSkipListNode:
    def __init__(self, level: int, cur_node: 'SkipListNode' =None, next_node: SingleSkipListNode=None):
        self._cur: 'SkipListNode' = cur_node
        self.level = level
        self._next: SingleSkipListNode = next_node

    def has_next(self) -> bool:
        return self._next is not None
        # if self._cur.next is not None and self._cur.next.level >= self.level:
        #     return True

    def next_node(self) -> 'SingleSkipListNode':
        if self.has_next():
            return self._next
        raise IndexError('Next un exists')

    def lower_node(self) -> 'SingleSkipListNode':
        if self.level >= 0:
            return self._cur.nodes[self.level - 1]
        else:
            raise IndexError("Un Exists")

    def value(self):
        return self._cur.value

    def get_group(self) -> 'SkipListNode':
        return self._cur


class SkipListNode:
    def __init__(self, value, level=1, next_node: SkipListNode=None):
        self.value = value
        self.level: int = level
        self.nodes: List[SingleSkipListNode] = [None for _ in range(level)]
        self.next: SkipListNode = next_node

    def has_next_node(self):
        return self.next is not None


class SkipList:
    _RAND_UPPER: int = 1
    _MAX_LEVEL: int = 5
    _GO_UPPER: float = 0.5

    @staticmethod
    def _random_level() -> int:
        cur_level = 1
        while cur_level < SkipList._MAX_LEVEL and random() > SkipList._GO_UPPER:
            cur_level += 1
        return cur_level

    def __init__(self):
        self.head: SkipListNode = None

    def search_value(self, search_key) -> SkipListNode:
        cur_node_group: SkipListNode = self.head
        level = cur_node_group.level - 1
        cur_node = cur_node_group.nodes[level]
        while level >= 0:
            if cur_node.value() == search_key:
                return cur_node.get_group()
            while cur_node.has_next() and cur_node.next_node().value() <= search_key:
                cur_node = cur_node.next_node()
            else:
                level -= 1
                cur_node = cur_node.lower_node()
        return cur_node.get_group()

    def search(self, search_key) -> SkipListNode:
        cur: SkipListNode = self.head
        if cur is None:
            return None
        level = cur.level - 1
        while search_key <= cur.value:
            if search_key == cur.value:
                return cur
            # 确保有下一个
            if cur.has_next_node():
                node = cur.nodes[level]
                if node.has_next():
                    n_node = node.next_node()
                    if n_node.value() > cur.value:
                        # down grade
                        level -= 1
                    else:
                        cur = cur.next
                else:
                    # down grade
                    level -= 1
            else:
                # None exists
                return None



