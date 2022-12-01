/*
 * @Descripttion:
 * @version:
 * @Author: Mao Shunyu
 * @Date: 2022-11-18 17:24:08
 * @LastEditors: Do not edit
 * @LastEditTime: 2022-11-19 22:00:19
 */
template <class ElemType>
void CyQueue<ElemType>::EnQueue(CyQueue &Q, ElemType x) {
    if (flag && rear == front)
        cout << "Queue Full!!" << endl;
    Q.queue[rear] = x;
    rear = (rear + 1) % MaxSize;
    if (!flag)
        flag = 1;
}
template <class ElemType> ElemType CyQueue<ElemType>::OutQueue(CyQueue &Q) {
    if (!flag)
        cout << "Queue Empty!!" << endl;
    ElemType e = array[front];
    front = (front + 1) % Q.MaxSize;
    if (front == rear)
        flag = 0;
    return e;
}
void interLeavingQueque(struct Queue *q) {
    if (size(q) % 2 != 0)
        return;
    struct Stack *s = CreateStack();
    inthalfSize = size(q) / 2;
    for (int i = 0; i < halfSize; i++)
        Push(s, DeQueue(q));
    While(!isEmptyStack(s)) EnQueue(q, Pop(s));
    for (int i = 0; i < halfSize; i++)
        EnQueue(q, DeQueue(q));

    For(int i = 0; i < halfSize; i++) Push(s, Deque(q));

    While(!isEmptyStack(s)) {
        EnQueue(q, Pop(s));
        EnQueue(q, DeQue(q));
    }
}
void reverseQueueFirstKElements(int k, struct Queue *q) {
    if (q == NULL || k > size(q))
        return;
    else if (k > 0) {
        struct Stack *s = CreateStack();
        for (int i = 0; i < k; i++)
            Push(s, DeQueue(q));
        while (!isEmptyStack(s))
            EnQueue(q, Pop(s));
        EnQueue(q, DeQue(q));
    }
}
void next(char *P, int N[]) {
    int m = strlen(P);
    N[0] = 0;
    int i = 1, j = 0;
    while (i < m) {
        if (P[i] == P[j]) {
            N[i] = j + 1;
            i++;
            j++;
        } else if (j > 0)
            j = N[j - 1];
        else {
            N[i++] = 0;
        }
    }
}

int BinaryTree::FindMax(TNODE *root) {
    int root_val, left, right, max = INT_MIN;
    if (root != NULL) {
        root_val = root.value;
        left = FindMax(root.left);
        right = FindMax(root.right);
        max = max(left, right, root_val);
    }
    return max
}

int BinaryTree::FindLevelwithMaxSum(BinaryTree *root) {
    TNODE *temp;
    int level = 0, maxLevel = 0;
    struct Queue Q;
    int currentSum = 0, maxSum = 0;
    if (!root)
        return 0;
    InitQueue(Q);
    EnQueue(Q, root);
    while (!Q.isEmpty()) {
        int size = Q.size();
        while (size-- > 0) {
            temp = DeQueue(Q);
            currentSum += temp.value;

            if (temp.left)
                EnQueue(Q, temp.left);
            if (temp.right)
                EnQueue(Q, temp.right);
        }
        if (maxSum < currentSum)
            maxSum = currentSum;
        currentSum = 0;
    }
    return maxSum;
}
Graph *ReverseTheDirectedGraph(Graph *G) {
    Graph *Gr;
    if (G == NULL) {
        Gr = NULL;
        return NULL;
    }
    Initialize(Gr, Vcnt(G), NULL);
    int n = Vcnt(G);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G->edge(i, j))
                Gr->insert(j, i);
        }
    }
}