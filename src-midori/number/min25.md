符号与记号：

​		$p_k$：第 k 个整数，$p_1 = 2$

​		$lpf(i)$：$i$ 的最小素因子，约定 $lpf(1) = 1$

​		$p^e \parallel m$ ：素因子 $p$ 恰好整除 $m$，即 $p^e \mid m$ 且 $p^{e+1} \nmid m$

​		$pf_k$：$f$ 在前 k 个素数上的取值之和，即 $\sum_{i=1}^kf(p_i)$

​		$Fprime(n)$：$f$ 在 $[1, n]$ 中所有素数上的取值之和。

第一部分：扩展埃氏筛，比较好理解。

第二部分：求 $F_{k}(n)$

定义：
$$
F_{k}(n) = \sum_{i=2}^n{[p_k\leq lpf(i)]f(i)}
$$
为了方便，接下来用 $p$ 代替 $p_k$
$$
F_{k}(n) = \sum_{p^e\leq n,e\geq 0}^n\sum_{i=2}^n{[p^e\parallel i][p\leq lpf(i)]f(i)}
$$

$$
F_{k}(n) = F_{k+1}(n)+\sum_{p^e\leq n,e\geq 1}^n\sum_{i=2}^n{[p^e\parallel i][p\leq lpf(i)]f(i)}
$$

$$
因为[p^e\parallel i]f(i)=[p^e\parallel i]f(p^e)*f(i/p^e)
$$

$$
所以\sum_{i=2}^n{[p^e\parallel i][p\leq lpf(i)]f(i)} = f(p^e)*(1+\sum_{i=2}^{n/p^e}[p_{k+1}\leq lpf(i)]f(i))
$$

$$
=f(p^e)*(1+F_{k+1}(n/p^e))
$$

于是
$$
F_{k}(n) = F_{k+1}(n)+\sum_{p^e\leq n,e\geq 1}^nf(p^e)*(1+F_{k+1}(n/p^e))
$$
我们发现，当 $p^{e+1} > n$，即 $n/p^e < p$ 时，$F_{k+1}(n/p^e) = 0$

所以
$$
F_{k}(n) = F_{k+1}(n)+\sum_{p^{e+1}\leq n,e\geq 1}^nf(p^e)*F_{k+1}(n/p^e)+\sum_{p^{e}\leq n,e\geq 1}f(p^e)
$$
在最右的求和号中，用 $e + 1$ 代替 $e$
$$
F_{k}(n) = F_{k+1}(n)+\sum_{p^{e+1}\leq n,e\geq 1}^n(f(p^e)*F_{k+1}(n/p^e)+f(p^{e+1})) + f(p)
$$
降低复杂度的根源是：仅当 $n\geq p^2$ 时，才进行转移，而此时有一个棘手的 $f(p)$

我们可以微调 $F_k$ 的定义来实现：把等式两边同时加上 $pf_{k-1}$ 
$$
F_{k}(n)+pf_{k-1} = F_{k+1}(n)+pf_k+\sum_{p^{e+1}\leq n,e\geq 1}^n(f(p^e)*F_{k+1}(n/p^e)+f(p^{e+1}))
$$
定义 $F'_k(n) = F_k(n) + pf_{k-1}$，得到转移方程：
$$
F'_{k}(n) = F'_{k+1}(n)+\sum_{p^{e+1}\leq n,e\geq 1}^n(f(p^e)*(F'_{k+1}(n/p^e)-pf_k)+f(p^{e+1}))
$$
初值：当 $p_k^2 > n$ 时，$F_k(n)=Fprime(n) -pf_{k-1}$，$F'_k(n)=Fprime(n)$

使用该方程进行转移，就可以得到 $O(n^{\frac34}/\log n)$ 的复杂度。



