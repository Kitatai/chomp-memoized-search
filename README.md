# Chomp 必勝手列挙

2D Chomp の全長方形盤面 (最大 20×20) に対し、初手の先手必勝手を完全列挙するプログラムです。
メモ化 Negamax + αβ 枝刈り + Ferrers 図形ハッシュで探索します。

## 使い方

```bash
# リポジトリをクローン
git clone https://github.com/Kitatai/chomp-memoized-search.git
cd chomp-memoized-search

# ビルド
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# 実行して結果をファイルへ出力，最初に使用メモリの見積もりが出るため，実行可能ならEnterで続行
./chomp_enum
```

## 注意
20×20 以下の長方形盤面を探索するためには34GB程度のメモリとストレージが必要です。

[`include/config.hpp`](include/config.hpp) の `N_GRID_SIZE` と `M_GRID_SIZE` を小さくすることで，使用メモリ・ストレージを減らすことができますが，探索可能な盤面のサイズも小さくなります。

## 探索結果

![chomp_winning_moves_color.png](images/chomp_winning_moves_color.png)

先手必勝手が 3 つ以上存在する 20×20 以下の長方形盤面は存在しないことがわかりました。
