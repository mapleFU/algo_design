1. 模拟二叉树需要准备一个数组，每个元素**anode**拥有储存值(.value)，父节点在数组的索引(.father)，是父节点的左节点\右节点(是右节点则anode.left_right == LEFT, 否则anode.left_right == RIGHT)。anode(value, father, LEFT)创建一个值为value，父节点索引为father, 是父节点左子叶的节点。
   操作的时候维护一个队列，存放数组的元素，每次把队首元素top取出，加到数组中，并根据它的索引信息，把左右节点放入队列中，左右节点的值等于他们本身的值，左右节点父索引等于top在数组的索引。
   对于根节点，创建的father== -1, 表示没有节点，且父节点出现在数组第0位。

   ```
   PUSH_LEFT_RIGHT(node, index, que):
       if node.left is not NIL:
           que.append(anode(node.left.value, index, LEFT))
       if node.right is not NIL:
           que.append(anode(node.right.value, index, RIGHT))
   ```

   ​

   ```python
   TO_ARRAY(tree_node, index=0):
       // 让que表示树节点的队列，每次取出一个节点，并把它的子节点放入队列
       // 队列拥有anode的信息
   	que = Queue()
       //使arr成为长度和bst元素个数一样的anode数组
       
       // 父节点father字段为-1
       arr[index] = anode(tree_node.value, -1, None)
       // 把正在处理节点的左右节点放入队列
       PUSH_LEFT_RIGHT(tree_node, index, que)
       while not que.empty():
         	// 取出节点，处理节点并把它的子节点放入
           top = que.get()
           index += 1
           arr[index] = top
           PUSH_LEFT_RIGHT(top, index, que)
       return arr
   ```

   这样构成的树，保存有父节点索引和是父节点的左/右。每个节点要在循环中被拿出-操作一次。所以**时间复杂度O(n)**, 返回数组大小为n，有储存值，父节点索引，是左子叶还是右子叶的字段。所以**空间复杂度O(n).**

   ​

   变回二叉树的操作：
   根据数组按顺序恢复，由于之前是按父节点-子节点放入数组的，所以一旦按顺序取出非根节点，它的父节点一定已经被取出了。让**ptrs**为一个大小等同给定二叉树数组，存储二叉树节点的数组，新取出的节点可以根据这个数组找到自己的父节点，并被放到这个数组中，索引和在二叉树数组的索引相同。

   ```
   TO_BINARY_TREE(arr):
       // 初始化一个二叉树节点
       bst = node()
       index = 0
       # 初始化
       让ptrs为一个大小等同给定二叉树数组
       // 处理根节点
       bst.value = arr[index].value
       ptrs[index] = bst

       for index <- 1 upto len(bst)):
           new_node = node()
           new_node.value = arr[index].value
           father_index = arr[index].father
           if arr[index].left_right == RIGHT:
               ptrs[father_index].right = new_node
           else:
               ptrs[father_index].left = new_node
   		// 把新构成的节点放入ptrs数组
   		ptrs[index] = new_node
   ```

   ​


2. (B)现在视作已知左右的高度，如果左侧右侧高度差绝对值小于2，那么显然无需做任何调整。
   如果差大于二，可以进行双旋转或者单旋转，下面进行讨论:
   可以定义两种双旋转(假设已经给出左右单旋转代码)

   ```python
   double_rotate_with_left(node):
       single_rotate_with_right(node.left)
       single_rotate_with_left(node)
   ```


      double_rotate_with_right(node):
      		single_rotate_with_left(node.right)
          single_rotate_with_right(node)

          
    
      ```
    
      为方便操作，自定义一个get_height函数，如果得到的输入是NIL,则返回0，其他返回树高
      GET_HEIGHT(node):
          if node is None:
              return 0
          return node.h
      ```
    
      根据之前讨论，可以直接书写代码：

   ```python
   ADJUST_AVL(bst: Node):
       hl = GET_HEIGHT(bst.left)
       hr = GET_HEIGHT(bst.right)
       // 满足条件，左右绝对值差小于2
       if ABS(hl - hr) < 2:
           return
       elif hl > hr:
           if GET_HEIGHT(bst.left.left) > GET_HEIGHT(bst.left.right):
               single_rotate_with_left(bst)
           else:
               double_rotate_with_left(bst)
       else:
           if GET_HEIGHT(bst.right.right) > gGET_HEIGHT(bst.right.left):
               single_rotate_with_left(bst)
           else:
               double_rotate_with_right(bst)
       // 再次调整树高
       bst.h = MAX(GET_HEIGHT(bst.left), GET_HEIGHT(bst.right)) + 1
   ```

   单旋转时间复杂度O(1), 双旋转重复两次单旋转，同样为O(1).

   每次ADJUST_AVL高度差最低减少2，对新产生的根节点多次进行ADJUST_AVL,  直到得到的两边树高差小于2.

   (c) 1. 如果左右子树都是平衡的AVL树，调用`ADJUST_AVL`可以让整个树平衡。 2. 已知avl树在插入之前本身是平衡的。
   通过以上两个条件可以知道，avl树插入后，需要调整的是它的父节点，我们可以在插入后递归的做对父节点的调整。

   ```
   INSERT(node, z):
       if node is None:
           return z
       if node.value < z.value:
           node.right = INSERT(node.right, z)
       elif node.value > z.value:
           node.left = INSERT(node.left, z)
       ADJUST_AVL(node)
       return node
   ```

   (d) 插入耗时相当于 直接找到节点插入(O(lgn)) + 旋转耗时。
​	利用ADJUST平衡后，子AVL树平衡，树的高度最多可能变大1.由于整棵树已经是AVL树，已知只要一次单旋转或者双旋转（2次）就能平衡。需要O(1)次旋转。   

3. 如果两个长方形重合，一定有：两个长方形横坐标区间，纵坐标区间都重合
   为点添加一组附加信息start_end，把最小x, y轴点当成起始点(point.start_end==END)，把最大的x, y点当成终点(point.start_end==START)。给点再添加一组链接字段interval，表示\<[x1, x2]区间, [y1, y2]区间\>。
   对所有的点，以x的大小为参数进行排序，耗时O((2nlg(2n)))即O(nlg(n))
   构造一刻空区间树，按顺序进行如下操作:

   1. 如果新找的点是起始点，则把对应的\<y1, y2\>区间在区间树中查找，如果有重叠 则 有重叠的矩形
   2. 如果查找的是结尾点，则把对应的\<y1, y2\>区间在区间树中删除

   ```python
   FIND_OVERLAP(arr):
   	// 按x为关键字排序
       SORT(arr)
       使interval_tree成为一颗新的区间树
       for i <-0 upto arr.size():
       	if arr[i].start_end == END:
       		interval_tree.DELETE_INTERVAL(arr[i].interval)
       	else:
             	// 如果是表示开始的点
       		if interval_tree.FIND_INTERVAL(arr[i].interval):
       			// 如果区间树找到这个点的区间
       			return True
               else:
               	interval.INSERT_INTERVAL(arr[i].interval)
       // 如果整个循环没有找到，则没有重复
       return False
   ```

   ​

4. 在同一片区域，如果有同样的x，则取最大的y。即维护一个优先队列，在其中压入0作为没有任何建筑物的默认值，按照高度进行排序。
   对于长方形的楼，对字段begin_end标注好起始(BEGIN)和终点(END)，然后按x值排序。在循环中，读到一个点，如果是起始点，即把它的高度放入优先队列。这一片区域的高度等于优先队列的最大高度；如果是末点，则在优先队列中删除等同于楼高的值。

   ```python
   DRAW_EDGE(nodes):
   	让pq成为存放点的y值为关键字的优先队列
       pq.push(0)	// 优先队列有默认的最小值0
      	pre_x = 0 	// 用pre_x表示之前出现的x轴值
       使line为高度线，line[a:b] = y表示a-b之间高度为y
   	for i <- 0 upto nodes.size():
           if nodes[i].begin_end == BEGIN:
   			pq.push(nodes[i].y)
   		else:
   			pq.pop(nodes[i].y)
           // 之前一个点到现在取出的点之间y为pq中的最大值
           line[pre:nodes[i].x] = pq.top()
           
   ```

   需要消耗的时间中，区间树的操作是O(lgn), 对2n点操作，故时间复杂度O(nlgn)