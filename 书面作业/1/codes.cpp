/*
 * @Descripttion:
 * @version:
 * @Author: Mao Shunyu
 * @Date: 2022-10-16 16:01:49
 * @LastEditors: Do not edit
 * @LastEditTime: 2022-10-16 18:16:41
 */
// 1.1
int sum(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++) {
        int p = 1;
        for (int j = 1; j <= i; j++)
            p *= j;
        s += p;
    }
    return s;
}
// 1.2
int fac(int n) {
    int p = 1, s = 0;
    for (int i = 1; i <= n; i++) {
        p *= i;
        s += p;
    }
    return s;
}

// 2.1
void f(int n) {
    int s, i = 0;
    while (s <= n) {
        ++i;
        s += i;
        printf("*");
    }
}
// 2.2
void f(int n) {
    int i, j, k, count = 0;
    for (i = n / 2; i <= n; i++)
        for (j = 1; j < n; j *= 2)
            for (k = 1; k <= n; k *= 2)
                count++;
}
// 4
struct SNode *FindMiddle(LinkList &HA) {
    // 结点数据类型为
    //  struct SNode{
    //      int data;
    //      SNode *next;
    //      SNode():data(0),next(NULL){}
    //  }
    struct node *h = HA.head;
    int length = 0;
    if (h = nullptr)
        return nullptr;
    while (h != nullptr) {
        length++;
        h = h->next;
    }
    length /= 2;
    h = HA.head;
    while (length-- > 0) {
        h = h->next;
    }
    return h;
}
// 5.1

void mergeList(LinkList &HA, LinkList &HB, LinkList &HC) {
    struct SNode *i = HA.head;
    struct SNode *j = HB.head;
    struct SNode *s = HC.head;
    while (i != nullptr && j != nullptr) {
        struct SNode *n = new SNode;

        if (i->data <= j->data) {
            n->data = i->data;
            struct SNode *t = i;
            i = i->next;
            delete t;
        } else {
            n->data = j->data;
            struct SNode *t = j;
            j = j->next;
            delete t;
        }
        if (s == nullptr)
            HC.head = n;
        else {
            s->next = n;
            s = s->next;
        }
    }
    if (i == nullptr) {
        while (j != nullptr) {
            struct SNode *n = new SNode;
            n->data = j->data;
            struct SNode *t = j;
            j = j->next;
            delete t;
            if (s == nullptr)
                HC.head = n;
            else {
                s->next = n;
                s = s->next;
            }
        }
    } else {
        while (i != nullptr) {
            struct SNode *n = new SNode;
            n->data = i->data;
            struct SNode *t = i;
            i = i->next;
            delete t;
            if (s == nullptr)
                HC.head = n;
            else {
                s->next = n;
                s = s->next;
            }
        }
    }
}

// 6.1
class SeqList {
public:
    int length;
    int *list;
    SeqList(int n) {
        length = 0;
        list = new int[n]; //分配一个足够大的空间
    }
};
void inverList(SeqList &L) {
    int n = L.length;
    for (int i = 0; i < n / 2; i++) {
        int t = L.list[i];
        L.list[i] = L.list[n - i - 1];
        L.list[n - i - 1] = t;
    }
}
// 6.2
void invertLinkList(LinkList &HL) {
    struct SNode *h = HL.head;
    struct SNode *prev = nullptr;
    while (h != nullptr) {
        struct SNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
}
// 8
struct NODE {
    ElemType data;
    NODE *next;
    NODE() : data(0), next(NULL) {}
};
NODE *list_find(NODE *current, ElemType x) {}
// 9
void writ(int n) {
    if (n != 0) {
        writ(n - 1);
        cout << n << endl;
        return;
    }
}