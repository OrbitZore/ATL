template <class T, class IT = int> struct segtree {
  const IT l, r;
  IT mid;
  T fadd, fmul, fsum;
  unique_ptr<segtree> ch[2];
  segtree(const int l, const int r)
      : l(l), r(r), mid(INF), fadd(0), fmul(1), fsum(0) {
    		// if (l!=r) wake();
    		// else fsum=v[l];
  }
  bool unwake() { return mid == (IT)INF; }
  bool wake() {
    if (unwake()) {
      mid = (l + r) / 2;
      ch[0] = (new segtree(l, mid));
      ch[1] = (new segtree(mid + 1, r));
      upload();
      return true;
    }
    return false;
  }
  void dmul(const T &v) {
    fmul *= v;
    fadd *= v;
    fsum *= v;
  }
  void dadd(const T &v) {
    fadd += v;
    fsum += v * (r - l + 1);
  }
  void download() {
    if (fmul != 1) {
      ch[0]->dmul(fmul);
      ch[1]->dmul(fmul);
      fmul = 1;
    }
    if (fadd != 0) {
      ch[0]->dadd(fadd);
      ch[1]->dadd(fadd);
      fadd = 0;
    }
  }
  T sum_op() { return fsum; }

  static T sum_merge1(T a) { return a; }

  static T sum_merge2(T a, T b) { return a + b; }
  static T sum_merge2(T a) { return a; }
  void upload() { fsum = sum_merge2(ch[0]->sum_op(), ch[1]->sum_op()); }
};
#define def_tree_edit(tag)                                                     \
  template <class T0, class T2, class T3 = decltype(declval<T0>().l)>          \
  void tag(T0 &tree, const T3 &L, const T3 &R, const T2 &v) {                  \
    if (L <= tree.l && tree.r <= R)                                            \
      return tree.d##tag(v);                                                   \
    if (!tree.wake())                                                          \
      tree.download();                                                         \
    if (L <= tree.mid)                                                         \
      tag(*tree.ch[0], L, R, v);                                               \
    if (tree.mid + 1 <= R)                                                     \
      tag(*tree.ch[1], L, R, v);                                               \
    tree.upload();                                                             \
  }                                                                            \
  template <class T0, class T2, class T3 = decltype(declval<T0>().l)>          \
  void tag(T0 &tree, const T3 &LR, const T2 &v) {                              \
    if (LR <= tree.l && tree.r <= LR)                                          \
      return tree.d##tag(v);                                                   \
    if (!tree.wake())                                                          \
      tree.download();                                                         \
    tag(*tree.ch[tree.mid + 1 <= LR], LR, v);                                  \
    tree.upload();                                                             \
  }
#define def_tree_query(tag)                                                    \
  template <class T0, class T3 = decltype(declval<T0>().l),                    \
            class T2 =                                                         \
                typename decay<decltype(declval<T0>().tag##_op())>::type>      \
  T2 tag(T0 &tree, const T3 &L, const T3 &R) {                                 \
    if (L <= tree.l && tree.r <= R || tree.unwake())                           \
      return tree.tag##_op();                                                  \
    tree.wake();                                                               \
    tree.download();                                                           \
    bool l = L <= tree.mid, r = tree.mid + 1 <= R;                             \
    if (l && r)                                                                \
      return tree.tag##_merge2(tag(*tree.ch[0], L, R),                         \
                               tag(*tree.ch[1], L, R));                        \
    if (l)                                                                     \
      return tree.tag##_merge2(tag(*tree.ch[0], L, R));                        \
    return tree.tag##_merge2(tag(*tree.ch[1], L, R));                          \
  }                                                                            \
  template <class T0, class T3 = decltype(declval<T0>().l),                    \
            class T2 =                                                         \
                typename decay<decltype(declval<T0>().tag##_op())>::type>      \
  T2 tag(T0 &tree, const T3 &LR) {                                             \
    if (LR == tree.l && tree.r == LR || tree.unwake())                         \
      return tree.tag##_op();                                                  \
    tree.wake();                                                               \
    tree.download();                                                           \
    if (LR <= tree.mid)                                                        \
      return tree.tag##_merge1(tag(*tree.ch[0], LR));                          \
    else                                                                       \
      return tree.tag##_merge1(tag(*tree.ch[1], LR));                          \
  }
def_tree_edit(add) def_tree_edit(mul) def_tree_query(sum)