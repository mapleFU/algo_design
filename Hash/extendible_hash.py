PAGE_SZ = 200


class Page(object):

    def __init__(self):
        self.m = {}
        # depth of page
        self.d = 0

    def full(self):
        return len(self.m) >= PAGE_SZ

    def put(self, k, v):
        self.m[k] = v

    def get(self, k):
        return self.m.get(k)


class EH(object):

    def __init__(self):
        self.gd = 0
        p = Page()
        self.pp = [p]

    def get_page(self, k):
        h = hash(k)
        # 获取最低的 self.gd 位
        # 2^(self.gd) - 1 ===> 1111(self.gd 个)
        p = self.pp[h & ((1 << self.gd) - 1)]
        return p

    def put(self, k, v):
        p = self.get_page(k)
        if p.full() and p.d == self.gd:
            # 整体扩展，全部爆破
            self.pp *= 2
            self.gd += 1

        if p.full() and p.d < self.gd:
            p.put(k, v)
            p1 = Page()
            p2 = Page()
            for k2, v2 in p.m.items():
                h = hash(k2)
                h = h & ((1 << self.gd) - 1)
                # 页满且 最低几位比对p.d
                if (h >> p.d) & 1 == 1:
                    p2.put(k2, v2)
                else:
                    p1.put(k2, v2)
            for i, x in enumerate(self.pp):
                if x == p:
                    if (i >> p.d) & 1 == 1:
                        self.pp[i] = p2
                    else:
                        self.pp[i] = p1

            p2.d = p1.d = p.d + 1
        else:
            p.put(k, v)

    def get(self, k):
        p = self.get_page(k)
        return p.get(k)


if __name__ == "__main__":
    eh = EH()
    N = 10088
    l = list(range(N))

    import random

    random.shuffle(l)
    for x in l:
        eh.put(x, x)
    print(l)

    for i in range(N):
        print(eh.get(i))
