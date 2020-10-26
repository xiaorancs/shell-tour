# 字符串匹配

## 问题描述：

字符串匹配是基本一个问题，我们考虑这样的一个问题：给定一个字符串T和一个模式串P，判断P是否是T的字符，如果是返回第一次出现的位置。

这个字符串匹配的问题，在很多领域遇到过。例如最长的公共DNA串；文本编辑器的查找功能。

## 朴素解法

我们直观的解法是，T字符串的每一个串进行比较|P|长字符串，以此和P的每个字符进行比较。这个算法的运行时间是O(|T|*|P|)。

这个算法在T每一个位置都要比较|P|次P字符串的每个位置，最坏情况下需要比较|T|-|P|次，因此时间复杂度是O(|T|*|P|)。

<img src=./naive_string.png>

```
int naive_match(string t, string p) {
    int ans = -1;
    int t_size = t.size();
    int p_size = p.size();
    if (t_size == 0) {
        return -1;
    }
    if (p_size == 0) {
        return 0;
    }
    if (p_size > t_size) {
        return -1;
    }
    for (int i = 0; i <= t_size - p_size; i ++) {
        int j = 0;
        for (j = 0; j < p_size; j ++) {
            if (t[i + j] != p[j]) {
                break;
            }
        }
        // cout << j << endl;
        if (j == p_size) {
            ans = i;
            break;
        }
    }
    return ans;
}
```

## Rabin-Karp String Matching

Rabin-Karp算法的想法是，我们能否找到一种方式，在O(1)时间比较字符串P和T中的|P|长的子串是否相等，就能在O(T)的时间解决字符串匹配问题。

O(1)时间比较两个字符串，我们会想到hash函数f，对每个字符串hash一个唯一的指纹编码，对字符串x和y，如果有：
$$f(x) = f(y) => x = y$$

我们的主要目标是找到一个映射函数f(x)，保证当x=y时，f(x)=f(y)；当f(x)=f(y)时，大概率存在x=y。

f(P)只需要计算一次，每次都要计算f(T[i: i + p - 1])，为了减少计算量，我们可以使用滑动窗口的方式，计算每个字符串的映射值：
$$f(T[i: i + |P|]) = f(T[i + 1: i + |P| - 1]) + calu(T[|P|]) - calu(T[i])$$

其中，calu(x)表示计算计算x的值，一般情况是转换成数字。

所以，我们可以使用下面的公式计算f(P)，设置一个素数p(一般稍微大点)，减小hash函数f(x)的碰撞几率。为了保证总能得到正确的结果，我们可以稍微牺牲点时间：当存在f(x)=f(y)的时候，单独比较x和y是否完全相等。

**伪代码：**
```
f_p = 0
const int p = 907; // 一个素数
const int BASE = 256; // 一共256个字符，这里可以使用其他数字
for i to |P|:
    f_p = (f_p * BASE + int(P[i])) % p;
output f_p

// 迭代计算T中|P|长度的字符串的指纹值
h = pow(BASE, |P| - 1) % p;
f_t[i: i + |P|] = (f_t[i - 1 : i + |P| - 1] - (h * int(T[i - 1])) + T[|P|]) % p;

```

**Coding：**
```
const int BASE = 256;
const int MOD = 101;
int rabin_karp_match(string t, string p) {
    int ans = -1;
    int t_size = t.size();
    int p_size = p.size();
    if (t_size == 0) {
        return -1;
    }
    if (p_size == 0) {
        return 0;
    }
    if (p_size > t_size) {
        return -1;
    }
    int t_hash = 0;
    int p_hash = 0;
    int h = 1;
    for (int i = 0; i < p_size; i ++) {
        if (i < p_size - 1) {
            h = h * BASE % MOD;
        }
        t_hash = (t_hash * BASE + int(t[i])) % MOD;
        p_hash = (p_hash * BASE + int(p[i])) % MOD;
    }
    for (int i = 0; i <= t_size - p_size; i ++) {
        if (t_hash == p_hash) { // 再次确认
            int j = 0;
            for (j = 0; j < p_size; j ++) {
                if (t[j + i] != p[j]) {
                    break;
                }
            }
            if (j == p_size) {
                ans = i;
                break;
            }
        }
        // 迭代更新
        t_hash = ((t_hash - (h * int(t[i]))) * BASE + int(t[i + p_size])) % MOD;
        if (t_hash < 0) {
            t_hash = t_hash + MOD;
        }
    }
    return ans;
}
```

## KMP算法

Knuth-Morris-Pratt 字符串查找算法，简称为 “KMP 算法”，常用于在一个文本串 S 内查找一个模式串 P 的出现位置，这个算法由 Donald Knuth、Vaughan Pratt、James H. Morris 三人于 1977 年联合发表，故取这三人的姓氏命名此算法。

KMP算法的思路是，当P字符串在T字符串中进行匹配的过程中，T上的后移指针不进行回退，而是和P的一个合适的位置进行比较，KMP算法我们从例子来看。

文本串T = CABCDAB_ABCDABCDABDE

模式串P = ABCDABD

使用朴素的思想进行字符串比较: 

> Step 1: t_index=0, p_index=0
> 
> <font color='red'>C</font>ABCDAB_ABCDABCDABDE
> 
> <font color='yellow'>A</font>BCDABD

由于C != A, T串后移一位index=1，p_index=0，进行下一次比较：

> Step 2: t_index=1, p_index=0
> 
> C<font color='green'>ABCDAB</font><font color='red'>_</font>ABCDABCDABDE
> 
> &nbsp;&nbsp;<font color='green'>ABCDAB</font><font color='yellow'>D</font>

由于 _ != D, 正常的朴素比较的方式，T串从t_index=6后移一位index=2，p_index=0，进行下一次比较，但是通过观察模式串P，我们其实可以不用回退t_index的，因为我们可以直观的看到，只需要将PC串向后移动4个位置，继续AB的比较即可。

> Step 3.1[朴素比较方式]: t_index=2, p_index=0
> 
> CA<font color='red'>B</font>CDAB_ABCDABCDABDE
> 
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color='yellow'>A</font>BCDABD

可以看出朴素的比较方式做了很多无用的操作，我们通过已经匹配成功的子串<font color='green'>ABCDAB</font>，可以从这个子串中看到，AB是这个子串的前缀，又是这个子串的后缀，前缀和后缀的长度是2。我们只要让这个前缀和后缀进行比较就可以得到正确的结果，而且不用回退t_index，直接比较接下来的字符就可以。P字符串向后移动4个位置，这个移动的距离4 = len(<font color='green'>ABCDAB</font>) - len(AB) = 6 - 2。所以得到 p_index = len(ABCDAB) - 4[移动距离] = 2。

应该执行如下步骤：

> Step 3.2: t_index=7, p_index=2
> 
> CABCD<font color='green'>AB</font><font color='red'>_</font>ABCDABCDABDE
> 
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color='green'>AB</font><font color='yellow'>C</font>DABD

根据已经匹配的子串的前缀和后缀的信息，我们继续进行一次操作，此时 _ != C，已经匹配的子串是AB，这个子串没有即是前缀又是后缀的子串，前缀后缀的长度是0，因此我们不用关注已经匹配的串AB，可以将模式串P之间向后移动2个位置，移动距离2 = len(AB) - len("") = 2 - 0 = 2，所以得到 p_index = len(AB) - 2[移动距离] = 0

> Step 4: t_index=7, p_index=0
> 
> CABCDAB<font color='red'>_</font>ABCDABCDABDE
> 
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color='yellow'>A</font>BCDABD


在进行模式匹配的过程中，朴素的匹配方式是遍历T中的每一个位置，一旦遇到P[i]!=T[j]，直接从头比较，下次从T[j-i+1]和P[0]进行比较，我们没有利用已经匹配成功的P[0, i-1]这个子串的信息，从上面的Step3.2和Step4中发现，我们可以利用已经匹配成功的子串的信息，分析前缀和后缀的最大公共长度，我们就可以不用回溯j，通过已经匹配子串的前缀和后缀的最大公共长度，可以移动P串的具体位置k，进行接下来的比较T[j] = P[k]?。

其实，我们可以从一个子串的最大前缀和后缀的公共长度，求得下次匹配的位置，这就是kmp算法中next的数组，我们通过next数据进行字符串的匹配，就得到了kmp算法，下面我们看下怎么求最大前缀和后缀的公共长度。

字符串：ABCDAB的最大前缀和最大后缀是AB，长度是2。
> <font color='green'>AB</font>CD<font color='green'>AB</font>

我们根据这个规则，可以求出模式串P的从i=0开始的，所有子串的最大的公共前后缀和长度。

|Index|P[0:0]|P[0:1]|P[0:2]|P[0:3]|P[0:4]|P[0:5]|P[0:6]|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|Substr|A|AB|ABC|ABCD|ABCDA|ABCDAB|ABCDABD|
|前后缀|||||A|AB||
|长度|0|0|0|0|1|2|0|
|next|-1|0|0|0|0|1|2|

next数组的计算方式，公共长度的整体右移一位，最左边的位置使用-1填充，这个移动的距离是根据匹配错误时，已经匹配成功的子串的长度减去这个子串的最大前缀和后缀的长度，Step4中我们有提到。下面是我们如何计算next数组：

我们可以维护两个变量进行递推求解，k表示前缀，j表示当前子串的后缀的最后位置。因此求next[j+1]，存在两种情况。
1. P[k] = P[j+1], next[j+1] = next[j] + 1 = k + j,
2. P[k] != P[j+1], 当前前后缀不匹配，此时的k是无意义的，进行回退，k = next[k]，回退到有意义的值或者最开始的位置。

```
void getNext(string p, vector<int>& next) {
    int n = p.size(), k = -1, j = 0;
    next.resize(n);
    std::fill(next.begin(), next.end(), -1);
    while (j < n - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++k; ++j;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
    return next;
}
```
上面这种计算next数组的方式可以进一步的优化，可以优化的原因是因为上面的方法存在一个小小的问题，如果用这种方法求模式串ABAB，会得到next数组为[-1 0 0 1]，我们用这个模式串去匹配ABACABABC:

> Step 1. t_index=0, p_index=0
> 
> <font color='green'>ABA</font><font color='red'>C</font>ABABC
> 
> <font color='green'>ABA</font><font color='red'>B</font>

我们使用next数据进行移动，需要右移2位=3-1，得到下面的比较，依然是B和C进行比较。为什么会出现这个情况，因为AB=AB，所以当我们进行next数组比较的时候，如果发现P[j] = P[k]，应该尽可能得到靠前的p_index，这有匹配的时候，P串可能更向后移动，next[j] = next[k] + 1 = next[next[k]] + 1，因此之前已经存在过相同的前后缀串。

> Step 2. t_index=3, p_index=1
> 
> <font color='green'>ABA</font><font color='red'>C</font>ABABC
> 
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color='green'>A</font><font color='red'>B</font>AB

通过优化，得到优化后的next数组计算code：

```
void get_next(string p, vector<int>& next) {
    int n = p.size(), k = -1, j = 0;
    next.resize(n);
    std::fill(next.begin(), next.end(), -1);
    while (j < n - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++k; ++j;
            if (p[j] != p[k]) {
                next[j] = k;
            }
            else {
                next[j] = next[k];
            }
        } else {
            k = next[k];
        }
    }
}
```

得到next数组之后，我们得到kmp算法如下：
```
int kmp_match(string t, string p) {
    int ans = -1; 
    int t_size = t.size();
    int p_size = p.size();
    if (t_size == 0) {
        return -1;
    }
    if (p_size == 0) {
        return 0;
    }
    if (p_size > t_size) {
        return -1;
    }
    int i = 0;
    int j = 0;
    vector<int> next;
    get_next(p, next);
    while (i < t_size && j < p_size) {
        if (j == - 1 || t[i] == p[j]) {
            ++i; ++j;
        } else {
            j = next[j];
        }
    }
    return (j == p_size) ? i - j : ans;
}
```

## 总结
字符串匹配的三个算法，细细品味别有一番味道。

## Ref
1. https://www.cnblogs.com/grandyang/p/6992403.html
2. https://blog.csdn.net/v_JULY_v/article/details/7041827
3. https://github.com/Jopo97/Rabin-Karp/blob/master/Source.cpp


