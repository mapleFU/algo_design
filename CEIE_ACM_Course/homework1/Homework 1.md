# Homework 1

1. ​

   1. \<2,3,8,6,1\>中，逆序对有\<2, 1\>, \<3, 1\>, \<8, 1\>, \<6, 1\>, \<8, 6\>

   2. {n, n-1, n-2, …, 1} 这样的有n个元素且A[i] == n - i 的数组有最多的逆序对，很容易知道，对于任意 i, j < n, i > j, A[i] < A[j]. 任两个数组成的数对都是逆序对。

      共有C(n, 2) = n(n - 1) / 2个数对，所以有n(n - 1) / 2组

   3. 设逆序对\<a, b\>中，以i结尾的逆序对数目为pi, 逆序对数目为M. 显然p0 + p1 + p2 + … + pn == M 且p0 == 0。

      假设我们对第j个元素进行插入排序，显然0 — j - 1个元素已经保证有序。显然 0 — j-1中有pj个元素小于它，他们的索引分别是 j - 1, j - 2, …, j - pj. 第j个元素要进行 pj 次交换操作。
      所以总共要进行 p1 + p2 + … + pj == M次交换操作。
      故交换的次数等于逆序数的数目。

   4. 把原数组拷贝到一个新数组中(O(n)), 在新数组中，先进行归并排序，同时计算出左侧和右侧的逆序数，再在归并中间数组的时候把左侧-右侧的逆序数求出。总逆序数 = 左侧数组逆序数 + 右侧数组逆序数 + 左-右逆序数

      ```c++
      // 排序并计算A[lo, hi)的逆序数数目
      COUNT-INVERTION(A, lo, hi)
      	// hi - lo <= 1的递归基处理
      	if hi - lo < 1
      		return 0
      	elseif hi - lo == 1
      		if A[lo] > A[hi]
      			// 交换A[lo] A[hi]
      			swap(A[lo], A[hi])
      			return 1
      		else
      			return 0
      	
      	// 让invertion表示逆序数，初始化为0
          invertion <- 0
      	invertion += COUNT-INVERTION(A, lo, (lo + hi) / 2)
          invertion += COUNT-INVERTION(A, (lo + hi) / 2, hi)
      	invertion += MERGE-AND-COUNT(A, lo, (lo + hi) / 2, hi)
      	
          return invertion
      ```

      A[lo,mid), A[mid, hi)逆序数计算

      ```python
      MERGE-AND-COUNT(A, lo, mid, hi)
        	left_cursor = lo
          right_cursor = mid
          inverse = 0
          aux_index = 0
          // 让aux为长度为hi - lo的辅助数组

          if mid - lo > 0 and hi - mid > 0:
              while left_cursor < mid and right_cursor < hi:
                  if A[left_cursor] <= A[right_cursor]:
                      // <left, right>不构成逆序数, 故left...mid内任何一个数都不和right构成逆序
                      // A[left] = A[right], 此时右边的应该后移直到不重复，
      				// 情况与LEFT < RIGHT相同
                      aux[aux_index] = A[right_cursor]
                      aux_index += 1
                      right_cursor += 1
                  elif A[left_cursor] > A[right_cursor]:
                      // <left, right>构成逆序数，<left-mid, right>都不构成逆序数
                      // <left, right...hi>都构成逆序数
                      inverse += hi - right_cursor
                      aux[aux_index] = A[left_cursor]
                      left_cursor += 1
                      aux_index += 1

          // 只有左侧右侧需要考虑逆序数，此处只需要写回

          while left_cursor < mid:
              aux[aux_index] = A[left_cursor]
              aux_index += 1
              left_cursor += 1
          while right_cursor < hi:
              aux[l_index] = A[right_cursor]
              aux_index += 1
              right_cursor += 1

          A = aux
          return inverse
      ```

2.   ​

   1.   mergesort将数组切分分别mergesort, 再对两段分别归并到一个新数组中，再回写, 设归并的时间为比较时间+, 写入和回写需要拷贝n个元素，操作时间2n, 比较时间为f(n)
      g(n) = 2g(n / 2) + f(n) + 2n, g(1) = 1
      f(n)最小时，右边数组指针不移动, 比较1/2n次就可以完成f(n) = 1/2 n
      g(n) = 2g(n / 2) + 2.5n
      ​

      ​

      ​

      g(n) = 2g(n / 2) + ø(n), g(n) = ø(nlogn)

   2. ​

      ```
      NOTE-BIGOK(array)
          让note成为一个标记的布尔数组，初始化全部为True，符合条件可能无序的标记为False
      	使None为一个状态，表示0号元素的钱去远
          last_pre = None
          (pre, cur) <- (0, 1)
          while cur < array.size
              if pre > cur:
                  note[pre] = note[cur] = False
                  if last_pre is None:
                      pre += 2
                      cur += 2
                  else:
                      pre = last_pre
                      cur += 1
              else:
                  last_pre = pre
                  pre, cur = cur, cur + 1
      	return note
      ```

      ​

      ```
      对于p[pre], p[cur], 若p[pre] < p[cur], 则p[pre], p[cur]两数必定有一个在k内，标记cur pre即可.
      pre, cur会遍历任何的数字，所以任意没有排序的数字都在选出的集合内，最多有k个排过序的数字会被标记，所以最多标记2k个(满足O(k))。算法正确
      cur递增且不会会退，复杂度是O(n)
      ```

   3. 对于选出的O(k)个数字进行排序，复杂度为O(klogk).
      对于剩下的排序好数字和这O(n)个未排序的数字进行归并排序那样的merge操作，时间复杂度是O(n).
      故总复杂度是O(n + klogk)

      ```
      K-SOMEWHAT-SORT(A)
      	K = NOTE-BIGOK(A)
      	// 对K进行排序，O(klogk)
      	sort(K)
      	让aux成为一个长度为n的辅助数组
      	// i, j表示在A和K的位置
      	i, j <- (0, 0)
      	aux_index <- 0

          while A.size > i and K.size > j::
              if A[i] <= K[j]:
                  aux[aux_index] = A[i]
                  aux_index += 1
                  i += 1
         		else:
                 aux[aux_index] = K[j]
      	       aux_index += 1
      		   k += 1
          // 只有左侧右侧需要考虑逆序数，此处只需要写回

          while i < A.size:
              aux[aux_index] = A[i]
              aux_index += 1
              i += 1
          while j < K.size:
              aux[l_index] = K[j]
              aux_index += 1
              j += 1
      ```

      ​

      ​

3. 设n个排序好的队列分别为q1, q2, q3…qn. 这些队列内部保证有序。
   设计一个优先队列，pq_q, 按照每个队列q顶端元素的大小，存入指向队列的指针或者引用。
   每次取出优先队列顶端的队列，并且取出队列首元素，再按队列顶部元素大小将其返回优先队列，当取出的队列为空时，不再返回优先队列
   建立优先队列花费时间O(nlgn), 每次操作话费时间O(logn), 共有k个元素迭代k次，复杂度大约为
   O((k+n)logn)

   ```
   sort_queues(queues):
   	let pq to be the priority queue of queues order by the front of each queue
   	while pq.size != 0
   		// 取出priority_queue顶端元素
   		top_queue <- pq.pop()
   		value <- top_queue.pop()
   		if top_queue.size() != 0
   			pq.push(top_queue)
   ```

   ​

4. 使用一个数组dp，dp[i]表示A[0] + A[1] +… +A[i -1], dp[0] = 0.这个数组可以线性时间内求得(O(n))

   dp[i] - dp[j] 等价于 A[j] + A[j + 1] +… +A[i - 1].
   使(cur, pre) = (1, 0)，当cur <= n进行以下操作

   1. dp[cur] - dp[pre] < s时，cur自增直到dp[cur] - dp[pre] >= s,
   2. dp[cur] - dp[pre] >= s时，记录此时的cur-pre, 同时pre自增，直到dp[cur] - dp[pre] < s ，再回到(1)

   以上求的cur - pre最小值就是所求目标min
   ​

   正确性：可以看到，对于每个可能的A[j] — A[i]且满足差值大于s的序列A[x] — A[y], 都被枚举, 所以他们的最小值就是总序列长度的最小值
   若A[m] — A[n]满足条件，那么必定会出现cur == n的情况，若dp[cur] - dp[m - 1] > s, 下一步会计算dp[cur] - dp[m], 从而使min = n - m.所以每个满足条件的序列都会被枚举。

   复杂度：dp构建耗时O(n)， cur pre不会会退, cur到n则停止，所以求值耗时O(n).
   算法复杂度ø(n)

   以下为伪代码

   ```
   MIN-SUBSEQUNENCE(A, s)
   	使dp为长度为n + 1的数组，初始化所有值为0
   	// 初始化dp
   	for i <- 1 to n
   		dp[i] = A[i - 1] + dp[i - 1]
   	
   	(pre, cur) = (0, 1)
   	// 所求的min初始化为一个极大的值
   	min = n + 1
   	while cur < n + 1:
           while cur < n + 1 and dp[cur] - dp[pre] < s:
               cur += 1
           if cur >= len(dp):
               continue
           while pre_index < cur and dp[cur] - dp[pre] >= s:
               pre_index += 1
           // 此时dp[cur] - dp[pre] < s 而且恰好dp[cur] - dp[pre - 1] >= s
   		if min > cur - pre + 1:
   			min = cur - pre + 1
       return min
   ```

5. 如果数据都是整数，可以开辟一份桶数组，拷贝原数组到其中并且用桶排序或者基数排序(复杂度O(n))，以O(n)的时间复杂度得出新桶中相邻两个数的差值，求出其中消耗的时间


   如果是非整数但是任然是全序集，拷贝到桶中之后可以用快速排序等算法，消耗时间O(nlogn)

   假设所有数字都是整数，可以把他们映射到一个长度为max - min的桶中，把他们的数值映射为在桶子中的序号。

   ```
   BUILD-BULKET(A)
   	// 构造min,max
   	min, max = A[0]
   	for i <- 0 to n
   		if A[i] < min
   			min = A[i]
   		if max < A[i]
   			max = A[i]
   	
   	使bulket成为一个max - min大小的整形数组并初始化为0
   	for i <- 0 to n
   		bulket[A[i] - min]++ 
   	return bulket
   ```

   对于已有的bulket若bulket[i] != 0, bulket[j] != 0, 且对于任意k, i < k < j, bulket[k] == 0, 此时j - i代表相邻两个元素的差值. 用pre代表前一个满足bulket[i] != 0, cur <- j+1,并且cur == 0时进行自增来运算

   ```
   MAX-DISTINCT(A)
   	bulket = BUILD-BULKET(A)
   	// 已知min,即bulket[0]必定有元素, 借此初始化pre cur
   	pre = 0
   	// 初始化max为一个极小的值
    	max = 0
   	while pre < bulket.size:
   		for cur <- pre + 1 to n:	
   			if A[cur] == 0
   				cur = cur + 1
   			if cur - pre > max
   				max = pre - cur
   		pre = cur
   	return pre
   ```

   得到桶的情况下，cur pre不会回退的在bulket中运行一次，复杂度相当bulket的大小，即max - min。所以总共相当于O(n) + O(max - min)

      2. 也可以采取类似基数排序的方法构建桶，复杂度为O(n).


