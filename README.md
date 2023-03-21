# Team9：
# 阶段1：初步实现游戏界面和简单逻辑

> DDL：2023-04-04

## 任务

不围棋的规则见 [`guidance/nogo/nogo.md`](../guidance/nogo/nogo.md)

1. 图形化界面：展示棋盘、棋子、其他游戏操作按钮（认输）、玩家信息。不提供素材，网络上搜集或自己设计即可。
2. 能在本地轮流落子（即PVP），能基本判断获胜（自杀，吃对方，认输，超时）。
3. 能“再来一局”，而不是退出重开。

> 原则上，我们第一阶段的最低要求是能轮流落子，且妥善记录了下棋的位置以便之后设计判断逻辑。但我们的任务进度是考虑到课程进度和其他考试（各科期中期末）安排设计的，所以我强烈推荐按照文档中的进度完成大作业，以便你们平衡学习压力。
> 
> 请把超时时长设为一个可以被软件设置的参数，不要硬编码它。之后所有的参数都是如此。

## 提交

无论你是否在截止时间前完成这一阶段的全部开发任务，请在 `submission/` 下你的小组文件夹中上传你第一阶段的阶段性报告，在报告中请简要描述你的小组分工、代码框架设计、遇到的问题及解决方法和其他你认为有必要的内容，并展示客户端运行截图。
