from src.Counter import Counter


def main():
    x = int(input('>>> 请输入一元纸币的数量'))
    y = int(input('>>> 请输入两元纸币的数量'))
    z = int(input('>>> 请输入五元纸币的数量'))
    counter = Counter(x, y, z)
    print(len(counter))
    print(counter.count())
    counter.print_all_solutions()


if __name__ == '__main__':
    # main()
    counter = Counter(4, 2, 2)
    print(len(counter))
    print(counter.expr.seq)
    print(counter.count())
    counter.print_all_solutions()
    while True:
        if_exit = input("按EXIT退出，其他键继续")
        if if_exit.lower() == "exit":
            break
        else:
            try:
                main()
            except e:
                print("你的输入有误！")
    print("程序结束，欢迎下次使用")
