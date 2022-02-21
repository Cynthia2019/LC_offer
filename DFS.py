"""
79.单词搜索
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
"""
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        def dfs(borad, i, j, k, word, visited): 
            #边界条件
            if i < 0 or i >= len(borad) or j < 0 or j >= len(borad[0]):
                return False
            #不满足条件
            if board[i][j] != word[k] or visited[i][j]:
                return False
            #防止重复
            visited[i][j] = True
            #k == len(word)
            if k == len(word) - 1:
                return True
            #继续match word
            ans = dfs(board, i+1, j, k+1, word, visited) or dfs(board, i-1, j, k+1, word, visited) or dfs(board, i, j+1, k+1, word, visited) or dfs(board, i, j-1, k+1, word, visited)
            visited[i][j] = False
            return ans
        rows = len(board)
        cols = len(board[0])
        visited = [[False for _ in range(cols)] for _ in range(rows)]
        for i in range(rows): 
            for j in range(cols): 
                if dfs(board, i, j, 0, word, visited): 
                    return True
        return False