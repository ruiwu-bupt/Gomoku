# alphago
- 策略网络: 输出走子概率
- 价值网络: 预测胜负结果
- 结合MCTS提供前向搜索.使用策略网络缩小搜索树宽度;使用价值网络连接蒙塔卡洛快速走子评估搜索树中节点的价值

# alphago zero
## 与alphago的不同点
- 由随机下子开始;只有黑白子位置信息;只使用一个神经网络;更简单的树节点价值评估算法,无蒙特卡洛快速走子

## 自对弈增强学习
- 流程: 自对弈一局产生一系列Pi(落子概率分布)与z(最终结果)作为多个训练样本, Pi由经过神经网络narrow down的蒙特卡洛搜索生成, z由游戏规则生成;训练过程就是将神经网络产生的落子概率+vt与经过增强算子的pi+z进行拟合.

- 蒙特卡洛模拟

- conv转为resnet, sep转为dual均有巨大提升

## Methods
- MCTS的选择参数由高斯过程优化
### 优化器
- mini-batch size 32, 从最近500000次自对弈中均匀采样
- SGD with momentum and learning rate annealing, m = 0.9
- 每1000 training step 一个checkpoint, 给evaluator
### 评估器
- 每个checkpoint在被许可用于自对弈前要进行评估, 以确保生成高质量训练数据
- 400 games, MCTS with 1600 simulations, temperature -> 0, win by a margin of > 55%
### 自对弈
- 初始30步temperature->1, 探索尽可能多的局面
- 后面对节点的先验概率增加狄利克雷噪声
- 当一方明显要输时会认输,节省计算量
